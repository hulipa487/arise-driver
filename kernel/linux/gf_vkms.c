//*****************************************************************************
//  Copyright (c) 2021 Glenfly Tech Co., Ltd..
//  All Rights Reserved.
//
//  This is UNPUBLISHED PROPRIETARY SOURCE CODE of Glenfly Tech Co., Ltd..;
//  the contents of this file may not be disclosed to third parties, copied or
//  duplicated in any form, in whole or in part, without the prior written
//  permission of Glenfly Tech Co., Ltd..
//
//  The copyright of the source code is protected by the copyright laws of the People's
//  Republic of China and the related laws promulgated by the People's Republic of China
//  and the international covenant(s) ratified by the People's Republic of China.
//*****************************************************************************

#include <drm/drm_edid.h>

#include "gf_kms.h"
#include "gf_driver.h"
#include "gf_vkms.h"
#include "gf_fence.h"
#include "gf_irq.h"
#include "gf_drmfb.h"

#if DRM_VERSION_CODE >= KERNEL_VERSION(4, 19, 0)

void gf_load_memory_timing_tbl(adapter_info_t*  adp);

static const int gf_vkms_formats[] = {
    DRM_FORMAT_XRGB8888,
};

static struct drm_crtc* gf_vkms_get_crtc_by_pipe(struct drm_device *dev, unsigned int pipe)
{
    struct drm_crtc *crtc = NULL;

    list_for_each_entry(crtc, &(dev->mode_config.crtc_list), head)
    {
        if (crtc->index == pipe)
        {
            return crtc;
        }
    }

    return NULL;
}


static enum hrtimer_restart gf_vkms_vblank_simulate(struct hrtimer *timer)
{
    gf_vkms_output_t *vkms_output = container_of(timer, gf_vkms_output_t, vblank_hrtimer);
    struct drm_crtc *crtc = &vkms_output->crtc.base_crtc;

    u64 ret_overrun;
    bool ret;

    ret_overrun = hrtimer_forward_now(&vkms_output->vblank_hrtimer,
                                      vkms_output->period_ns);
    if (ret_overrun != 1)
    {
        DRM_WARN("%s: vblank timer overrun\n", __func__);
    }

    ret = drm_crtc_handle_vblank(crtc);
    /* Vblank irq handling disabled, don't queue timer. */
    if (!ret)
    {
        DRM_ERROR("gf vkms failure on handling vblank");
        return HRTIMER_NORESTART;
    }

    return HRTIMER_RESTART;
}

static const struct drm_plane_funcs gf_vkms_plane_funcs = {
    .update_plane = drm_atomic_helper_update_plane,
    .disable_plane = drm_atomic_helper_disable_plane,
    .destroy = drm_plane_cleanup,
    .reset = drm_atomic_helper_plane_reset,
    .atomic_duplicate_state = drm_atomic_helper_plane_duplicate_state,
    .atomic_destroy_state = drm_atomic_helper_plane_destroy_state,
};

#if DRM_VERSION_CODE >= KERNEL_VERSION(5, 13, 0)
static void gf_vkms_plane_atomic_update(struct drm_plane* plane, struct drm_atomic_state* state)
#else
static void gf_vkms_plane_atomic_update(struct drm_plane* plane, struct drm_plane_state* old_state)
#endif
{
    DRM_DEBUG_KMS("Update plane=%d\n", plane->index);

    return;
}

#if DRM_VERSION_CODE >= KERNEL_VERSION(5, 13, 0)
static int gf_vkms_plane_atomic_check(struct drm_plane *plane, struct drm_atomic_state *state)
#else
static int gf_vkms_plane_atomic_check(struct drm_plane *plane, struct drm_plane_state *new_state)
#endif
{
#if DRM_VERSION_CODE >= KERNEL_VERSION(5, 13, 0)
    struct drm_plane_state *new_state = NULL;
#endif
    unsigned int src_w, src_h, dst_w, dst_h;
    int  status = 0;

#if DRM_VERSION_CODE >= KERNEL_VERSION(5, 13, 0)
    new_state = drm_atomic_get_new_plane_state(state, plane);
#endif

    src_w = (new_state->src_w >> 16) & 0xFFFF;
    src_h = (new_state->src_h >> 16) & 0xFFFF;

    dst_w = new_state->crtc_w;
    dst_h = new_state->crtc_h;

    if(new_state->crtc_x != 0 || new_state->crtc_y != 0)
    {
        status = -EINVAL;
        goto END;
    }

    if((src_w > dst_w) || (src_h > dst_h))
    {
        status = -EINVAL;
        goto END;
    }
END:
    return  status;
}

static void gf_vkms_set_fence_for_plane(struct drm_plane_state *plane_state, dma_fence_t *fence)
{
    if (plane_state->fence) {
        dma_fence_put(fence);

        return;
    }

    plane_state->fence = fence;
}

static int gf_vkms_prepare_fb(struct drm_plane *plane, struct drm_plane_state *new_state)
{
    struct drm_framebuffer *fb = new_state->fb;
    struct drm_gf_framebuffer *gfb = to_gfb(fb);
    gf_card_t *gf = (gf_card_t *)plane->dev->dev_private;

    if (!fb || !gfb->obj)
    {
        return 0;
    }

    /* resident */
    gf_core_interface->prepare_and_mark_unpagable(gf->adapter, gfb->obj->core_handle, &gfb->obj->info);

    if (plane->state->fb != fb)
    {
        dma_fence_t *fence = gf_reservation_object_get_excl_rcu(gfb->obj->resv);
        if (fence)
        {
            gf_vkms_set_fence_for_plane(new_state, fence);
        }
    }

    return  0;
}

static void gf_vkms_cleanup_fb(struct drm_plane *plane, struct drm_plane_state *old_state)
{
    gf_card_t *gf = plane->dev->dev_private;
    struct drm_framebuffer *fb = old_state->fb;

    if (fb && to_gfb(fb)->obj)
    {
        gf_core_interface->mark_pagable(gf->adapter, to_gfb(fb)->obj->core_handle);
    }
}

static const struct drm_plane_helper_funcs gf_vkms_primary_helper_funcs = {
    .atomic_update = gf_vkms_plane_atomic_update,
    .atomic_check = gf_vkms_plane_atomic_check,
    .prepare_fb = gf_vkms_prepare_fb,
    .cleanup_fb = gf_vkms_cleanup_fb,
};

#if DRM_VERSION_CODE >= KERNEL_VERSION(5, 7, 0)
static int gf_vkms_enable_vblank(struct drm_crtc *crtc)
#else
static int gf_vkms_enable_vblank(struct drm_device *dev, unsigned int pipe)
#endif
{
#if DRM_VERSION_CODE < KERNEL_VERSION(5, 7, 0)
    struct drm_crtc *crtc = gf_vkms_get_crtc_by_pipe(dev, pipe);
#else
    struct drm_device *dev = crtc->dev;
#endif
    struct drm_vblank_crtc *vblank = &dev->vblank[drm_crtc_index(crtc)];
    gf_vkms_output_t *vkms_output = drm_crtc_to_gf_vkms_output(crtc);

    drm_calc_timestamping_constants(crtc, &crtc->mode);

    vkms_output->period_ns = ktime_set(0, vblank->framedur_ns);
    hrtimer_start(&vkms_output->vblank_hrtimer, vkms_output->period_ns, HRTIMER_MODE_REL);

    return 0;
}

#if DRM_VERSION_CODE >= KERNEL_VERSION(5, 7, 0)
static void gf_vkms_disable_vblank(struct drm_crtc *crtc)
#else
static void gf_vkms_disable_vblank(struct drm_device *ddev, unsigned int pipe)
#endif
{
#if DRM_VERSION_CODE < KERNEL_VERSION(5, 7, 0)
    struct drm_crtc *crtc = gf_vkms_get_crtc_by_pipe(ddev, pipe);
#endif
    gf_vkms_output_t *vkms_output = drm_crtc_to_gf_vkms_output(crtc);

    /* avoid deadlock in disable vblank while hrtimer callback involves. */
    hrtimer_try_to_cancel(&vkms_output->vblank_hrtimer);
}

#if DRM_VERSION_CODE < KERNEL_VERSION(5, 7, 0)
static bool gf_vkms_get_vblank_timestamp(struct drm_device *ddev, unsigned int pipe,
                                             int *max_error, ktime_t *vblank_time,
                                             bool in_vblank_irq)
#else
static bool gf_vkms_get_vblank_timestamp(struct drm_crtc *crtc,
                                      int *max_error, ktime_t *vblank_time,
                                      bool in_vblank_irq)
#endif
{
#if DRM_VERSION_CODE >= KERNEL_VERSION(5, 7, 0)
    struct drm_device *ddev = crtc->dev;
    unsigned int pipe = crtc->index;
#else
    struct drm_crtc *crtc = gf_vkms_get_crtc_by_pipe(ddev, pipe);
#endif

    gf_vkms_output_t *vkms_output = drm_crtc_to_gf_vkms_output(crtc);

    struct drm_vblank_crtc *vblank = &ddev->vblank[pipe];

    if (!READ_ONCE(vblank->enabled)) {
        *vblank_time = ktime_get();
        return true;
    }

    *vblank_time = READ_ONCE(vkms_output->vblank_hrtimer.node.expires);

    if (WARN_ON(*vblank_time == vblank->time))
    {
        return true;
    }

/*
 * To prevent races we roll the hrtimer forward before we do any
 * interrupt processing - this is how real hw works (the interrupt is
 * only generated after all the vblank registers are updated) and what
 * the vblank core expects. Therefore we need to always correct the
 * timestampe by one frame.
 */
    *vblank_time -= vkms_output->period_ns;

    return true;
}

static const struct drm_crtc_funcs gf_vkms_crtc_funcs = {
    .set_config             = drm_atomic_helper_set_config,
    .destroy                = drm_crtc_cleanup,
    .page_flip              = drm_atomic_helper_page_flip,
    .reset                  = drm_atomic_helper_crtc_reset,
    .atomic_duplicate_state = drm_atomic_helper_crtc_duplicate_state,
    .atomic_destroy_state   = drm_atomic_helper_crtc_destroy_state,
#if DRM_VERSION_CODE >= KERNEL_VERSION(5, 7, 0)
    .enable_vblank = gf_vkms_enable_vblank,
    .disable_vblank = gf_vkms_disable_vblank,
    .get_vblank_timestamp = gf_vkms_get_vblank_timestamp,
#endif
};

static struct drm_plane *gf_vkms_plane_init(struct drm_device *ddev,
                                            enum drm_plane_type type, int index)
{
    gf_plane_t *gf_plane;
    int ret;

    gf_plane = gf_calloc(sizeof(gf_plane_t));
    if (!gf_plane)
        return ERR_PTR(-ENOMEM);


    ret = drm_universal_plane_init(ddev, &gf_plane->base_plane,
                                   (1 << index), &gf_vkms_plane_funcs,
                                   gf_vkms_formats, ARRAY_SIZE(gf_vkms_formats), NULL,
                                   type,
                                   NULL);
    if (ret)
    {
        gf_free(gf_plane);
        return ERR_PTR(ret);
    }

    drm_plane_helper_add(&gf_plane->base_plane, &gf_vkms_primary_helper_funcs);

    return &gf_plane->base_plane;
}

#if DRM_VERSION_CODE >= KERNEL_VERSION(5, 11, 0)
void gf_vkms_crtc_atomic_flush(struct drm_crtc *crtc, struct drm_atomic_state *state)
#else
void gf_vkms_crtc_atomic_flush(struct drm_crtc *crtc, struct drm_crtc_state *old_crtc_state)
#endif
{
    struct drm_pending_vblank_event *event = crtc->state->event;
    unsigned long flags;

    if (event) {
        spin_lock_irqsave(&crtc->dev->event_lock, flags);

        if (drm_crtc_vblank_get(crtc) != 0)
        {
            drm_crtc_send_vblank_event(crtc, crtc->state->event);
        }
        else
        {
            drm_crtc_arm_vblank_event(crtc, crtc->state->event);
        }

        spin_unlock_irqrestore(&crtc->dev->event_lock, flags);

        crtc->state->event = NULL;
    }
}

#if DRM_VERSION_CODE >= KERNEL_VERSION(5, 11, 0)
static void gf_vkms_crtc_atomic_enable(struct drm_crtc *crtc, struct drm_atomic_state *state)
#else
static void gf_vkms_crtc_atomic_enable(struct drm_crtc *crtc, struct drm_crtc_state *old_crtc_state)
#endif
{
    drm_crtc_vblank_on(crtc);
}

#if DRM_VERSION_CODE >= KERNEL_VERSION(5, 11, 0)
static void gf_vkms_crtc_atomic_disable(struct drm_crtc *crtc, struct drm_atomic_state *state)
#else
static void gf_vkms_crtc_atomic_disable(struct drm_crtc *crtc, struct drm_crtc_state *old_crtc_state)
#endif
{
    drm_crtc_vblank_off(crtc);
}

static const struct drm_crtc_helper_funcs gf_vkms_crtc_helper_funcs = {
    .atomic_flush = gf_vkms_crtc_atomic_flush,
    .atomic_enable = gf_vkms_crtc_atomic_enable,
    .atomic_disable = gf_vkms_crtc_atomic_disable,
};

static int gf_vkms_crtc_init(struct drm_device *ddev, struct drm_crtc *crtc,
                             struct drm_plane *primary, struct drm_plane *cursor)
{
    gf_vkms_output_t *vkms_output = drm_crtc_to_gf_vkms_output(crtc);
    gf_crtc_t *gf_crtc = to_gf_crtc(crtc);
    int ret;

    ret = drm_crtc_init_with_planes(ddev, crtc, primary, cursor,
                                    &gf_vkms_crtc_funcs, NULL);
    if (ret)
    {
        DRM_ERROR("Failed to init CRTC\n");
        return ret;
    }

    drm_crtc_helper_add(crtc, &gf_vkms_crtc_helper_funcs);

    gf_crtc->pipe = crtc->index;

#if DRM_VERSION_CODE >= KERNEL_VERSION(6, 15, 0)
    hrtimer_setup(&vkms_output->vblank_hrtimer, gf_vkms_vblank_simulate, CLOCK_MONOTONIC, HRTIMER_MODE_REL);
#else
    hrtimer_init(&vkms_output->vblank_hrtimer, CLOCK_MONOTONIC, HRTIMER_MODE_REL);
    vkms_output->vblank_hrtimer.function = &gf_vkms_vblank_simulate;
#endif

    return ret;
}

static const struct drm_connector_funcs gf_vkms_connector_funcs = {
    .fill_modes = drm_helper_probe_single_connector_modes,
    .destroy = drm_connector_cleanup,
    .reset = drm_atomic_helper_connector_reset,
    .atomic_duplicate_state = drm_atomic_helper_connector_duplicate_state,
    .atomic_destroy_state = drm_atomic_helper_connector_destroy_state,
};

static int gf_vkms_conn_get_modes(struct drm_connector *connector)
{
    int count;

    count = drm_add_modes_noedid(connector, XRES_MAX, YRES_MAX);
    drm_set_preferred_mode(connector, XRES_DEF, YRES_DEF);

    return count;
}

static const struct drm_connector_helper_funcs gf_vkms_conn_helper_funcs = {
    .get_modes    = gf_vkms_conn_get_modes,
};

static const struct drm_encoder_funcs gf_vkms_encoder_funcs = {
    .destroy = drm_encoder_cleanup,
};

static int gf_vkms_output_init(disp_info_t *disp_info, int index)
{
    gf_vkms_output_t *vkms_output = &disp_info->vkms_output[index];
    gf_card_t *gf_card = (gf_card_t *)disp_info->gf_card;
    struct drm_device *ddev = gf_card->drm_dev;
    struct drm_connector *connector = &vkms_output->connector.base_connector;
    struct drm_encoder *encoder = &vkms_output->encoder.base_encoder;
    struct drm_crtc *crtc = &vkms_output->crtc.base_crtc;
    struct drm_plane *primary, *cursor = NULL;
    int ret;

    primary = gf_vkms_plane_init(ddev, DRM_PLANE_TYPE_PRIMARY, index);
    if (IS_ERR(primary))
    {
        return PTR_ERR(primary);
    }

    ret = gf_vkms_crtc_init(ddev, crtc, primary, cursor);
    if (ret)
    {
        goto err_crtc;
    }

    ret = drm_connector_init(ddev, connector, &gf_vkms_connector_funcs,
                             DRM_MODE_CONNECTOR_VIRTUAL);
    if (ret)
    {
        DRM_ERROR("Failed to init connector\n");
        goto err_connector;
    }

    drm_connector_helper_add(connector, &gf_vkms_conn_helper_funcs);

    ret = drm_encoder_init(ddev, encoder, &gf_vkms_encoder_funcs,
                           DRM_MODE_ENCODER_VIRTUAL, NULL);
    if (ret)
    {
        DRM_ERROR("Failed to init encoder\n");
        goto err_encoder;
    }
    encoder->possible_crtcs = 1 << index;

    ret = drm_connector_attach_encoder(connector, encoder);
    if (ret)
    {
        DRM_ERROR("Failed to attach connector to encoder\n");
        goto err_attach;
    }

    drm_mode_config_reset(ddev);

    return 0;

err_attach:
    drm_encoder_cleanup(encoder);

err_encoder:
    drm_connector_cleanup(connector);

err_connector:
    drm_crtc_cleanup(crtc);

err_crtc:
    drm_plane_cleanup(primary);

    return ret;
}

const struct drm_mode_config_funcs gf_vkms_mode_funcs = {
    .fb_create = gf_fb_create,
    .atomic_check = drm_atomic_helper_check,
    .atomic_commit = drm_atomic_helper_commit,
};


static void gf_vkms_mode_config_init(struct drm_device *ddev)
{
    drm_mode_config_init(ddev);

    ddev->mode_config.funcs = &gf_vkms_mode_funcs;

    ddev->mode_config.min_width = 0;
    ddev->mode_config.min_height = 0;
    ddev->mode_config.max_width = XRES_MAX;   // 4*4k
    ddev->mode_config.max_height = YRES_MAX;
    ddev->mode_config.cursor_width = 64;
    ddev->mode_config.cursor_height = 64;
    ddev->mode_config.preferred_depth = 24;
    ddev->mode_config.prefer_shadow = 1;

#if DRM_VERSION_CODE >= KERNEL_VERSION(5, 18, 0)
    ddev->mode_config.fb_modifiers_not_supported = TRUE;
#elif DRM_VERSION_CODE < KERNEL_VERSION(5, 14, 0)
    ddev->mode_config.allow_fb_modifiers = TRUE;
#endif
}

static void gf_vkms_get_adapter_info(disp_info_t *disp_info)
{
    gf_card_t *gf_card = (gf_card_t *)disp_info->gf_card;

    gf_core_interface->get_adapter_info(gf_card->adapter, disp_info->adp_info);
}

static void gf_vkms_update_adapter_info(disp_info_t *disp_info)
{
    gf_card_t *gf_card = (gf_card_t *)disp_info->gf_card;
    adapter_info_t* adapter_info = disp_info->adp_info;
    krnl_adapter_init_info_t* a_info = &gf_card->a_info;

    gf_core_interface->update_adapter_info(gf_card->adapter, adapter_info, a_info);

}

static void gf_vkms_init_cbios(disp_info_t *disp_info)
{
    gf_card_t *gf_card = (gf_card_t *)disp_info->gf_card;
    adapter_info_t* adapter_info = disp_info->adp_info;

    disp_info_pre_init(disp_info);

    if (adapter_info->run_on_qt)
    {
        //gf_load_memory_timing_tbl(adapter_info);
    }

    //disp_init_cbios(disp_info);

    //disp_cbios_init_hw(disp_info);

    //disp_cbios_query_vbeinfo(disp_info);

    //disp_cbios_get_slice_num(disp_info);
}

static void gf_vkms_deinit_cbios(disp_info_t *disp_info)
{

   // disp_cbios_cleanup(disp_info);

    disp_info_deinit(disp_info);
}

int gf_vkms_init_modeset(struct drm_device *ddev)
{
    int ret, i;
    gf_card_t *gf_card = ddev->dev_private;
    adapter_info_t* adapter_info = &gf_card->adapter_info;
    disp_info_t *disp_info = NULL;

#if DRM_VERSION_CODE < KERNEL_VERSION(4, 19, 0)
    gf_info("gf vkms only support drm version >= 4.19.0\n");
    return 0;
#endif

    disp_info = gf_calloc(sizeof(disp_info_t));
    if (!disp_info)
    {
        return -ENOMEM;
    }

    gf_card->disp_info = disp_info;
    disp_info->gf_card = gf_card;
    disp_info->adp_info = adapter_info;

#if DRM_VERSION_CODE < KERNEL_VERSION(5, 7, 0)
    ddev->driver->enable_vblank = gf_vkms_enable_vblank;
    ddev->driver->disable_vblank = gf_vkms_disable_vblank;
    ddev->driver->get_vblank_timestamp = gf_vkms_get_vblank_timestamp;
#endif

    gf_vkms_get_adapter_info(disp_info);

    gf_vkms_init_cbios(disp_info);

    gf_vkms_update_adapter_info(disp_info);

    gf_vkms_mode_config_init(ddev);

    if (adapter_info->chip_id == CHIP_ARISE1020 && adapter_info->revision_id == 0x10)
    {
        disp_info->irq_chip_func = &irq_hp_chip_funcs;
    }
    else
    {
        disp_info->irq_chip_func = &irq_e3k_chip_funcs;
    }

    if(gf_card->support_msi && !gf_card->pdev->msi_enabled)
    {
        pci_enable_msi(gf_card->pdev);
    }

    /* set to 1 for vkms */
    disp_info->num_crtc = 1;

    ret = drm_vblank_init(ddev, disp_info->num_crtc);
    if (ret)
    {
        return ret;
    }

    disp_info->vkms_output = gf_calloc(disp_info->num_crtc * sizeof(gf_vkms_output_t));
    if (!disp_info->vkms_output)
    {
        return -ENOMEM;
    }

    for (i = 0; i < disp_info->num_crtc; i ++)
    {
        ret = gf_vkms_output_init(disp_info, i);
        if (ret)
        {
            return ret;
        }
    }

    return 0;
}

void gf_vkms_deinit_modeset(struct drm_device *ddev)
{
    gf_card_t *gf_card = (gf_card_t *)ddev->dev_private;
    disp_info_t *disp_info = (disp_info_t*)gf_card->disp_info;
    int i = 0;

    if (!disp_info)
    {
        return;
    }

    drm_atomic_helper_shutdown(ddev);

    if (disp_info->vkms_output)
    {
        for (i = 0; i < disp_info->num_crtc; i++)
        {
            hrtimer_cancel(&disp_info->vkms_output[i].vblank_hrtimer);
        }
    }


    if(gf_card->pdev->msi_enabled)
    {
        pci_disable_msi(gf_card->pdev);
    }

    drm_mode_config_cleanup(ddev);

    if (disp_info->vkms_output)
    {
        gf_free(disp_info->vkms_output);
    }

    gf_vkms_deinit_cbios(disp_info);

    gf_free(disp_info);

    gf_card->disp_info = NULL;
}

#else

int gf_vkms_init_modeset(struct drm_device *ddev)
{
    gf_info("gf vkms only support drm version >= 4.19.0\n");
    return 0;
}

void gf_vkms_deinit_modeset(struct drm_device *ddev)
{

}
#endif
