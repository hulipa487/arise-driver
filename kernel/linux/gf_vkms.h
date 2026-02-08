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

#ifndef _GF_VKMS_H_
#define _GF_VKMS_H_

#define XRES_DEF  1024
#define YRES_DEF   768

#define XRES_MAX  16384
#define YRES_MAX  8640

#define drm_crtc_to_gf_vkms_output(target)             \
    container_of(target, gf_vkms_output_t, crtc.base_crtc)

typedef struct {
    gf_crtc_t crtc;
    gf_encoder_t encoder;
    gf_connector_t connector;
    struct hrtimer vblank_hrtimer;
    ktime_t period_ns;
    struct drm_pending_vblank_event *event;
}gf_vkms_output_t;

#endif /* _GF_VKMS_H_ */
