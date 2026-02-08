/*
 * Copyright © 2025 Glenfly Tech Co., Ltd.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice (including the next
 * paragraph) shall be included in all copies or substantial portions of the
 * Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL
 * THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
 * IN THE SOFTWARE.
 *
 */
#include "gf_irq_hp.h"

static void gf_translate_interrupt_bits(disp_info_t* disp_info, int sw2hw, intr_info_t* info, int* masks)
{
    adapter_info_t*  adapter = disp_info->adp_info;

    if (!info || !masks)
    {
        return;
    }

    if (sw2hw)
    {
        info->sip_intr_lbits = 0;
        info->sip_intr_hbits = 0;

        info->sip_intr_lbits |= (*masks & INT_FENCE) ? ENGINE_FENCE_INT : 0;

        info->sip_intr_lbits |= (*masks & INT_VSYNC1) ? VSYNC1_INT : 0;
        info->sip_intr_lbits |= (*masks & INT_VSYNC2) ? VSYNC2_INT : 0;
        info->sip_intr_lbits |= (*masks & INT_VSYNC3) ? VSYNC3_INT : 0;
        info->sip_intr_lbits |= (*masks & INT_VSYNC4) ? VSYNC4_INT : 0;
        info->sip_intr_lbits |= (*masks & INT_DP1) ? DP1_INT : 0;
        info->sip_intr_lbits |= (*masks & INT_DP2) ? DP2_INT : 0;
        info->sip_intr_lbits |= (*masks & INT_DP3) ? DP3_INT : 0;
        info->sip_intr_lbits |= (*masks & INT_DP4) ? DP4_INT : 0;

        info->sip_intr_hbits |= (*masks & INT_HDCODEC) ? HDCODEC_INT : 0;
    }
    else
    {
        *masks = 0;
        *masks |= (info->sip_intr_lbits & ENGINE_FENCE_INT) ? INT_FENCE : 0;

        *masks |= (info->sip_intr_lbits & VSYNC1_INT) ? INT_VSYNC1 : 0;
        *masks |= (info->sip_intr_lbits & VSYNC2_INT) ? INT_VSYNC2 : 0;
        *masks |= (info->sip_intr_lbits & VSYNC3_INT) ? INT_VSYNC3 : 0;
        *masks |= (info->sip_intr_lbits & VSYNC4_INT) ? INT_VSYNC4 : 0;
        *masks |= (info->sip_intr_lbits & DP1_INT) ? INT_DP1 : 0;
        *masks |= (info->sip_intr_lbits & DP2_INT) ? INT_DP2 : 0;
        *masks |= (info->sip_intr_lbits & DP3_INT) ? INT_DP3 : 0;
        *masks |= (info->sip_intr_lbits & DP4_INT) ? INT_DP4 : 0;

        *masks |= (info->sip_intr_hbits & HDCODEC_INT) ? INT_HDCODEC : 0;
    }
}

static int gf_get_intr_enable_mask_hp(disp_info_t* disp_info)
{
    adapter_info_t *adapter = disp_info->adp_info;
    intr_info_t intr_info = {0};
    int masks = 0;

    intr_info.sip_intr_lbits = ~(gf_read32(adapter->mmio + GFX_INT_SIP_MASK_LOW));
    intr_info.sip_intr_hbits = ~(gf_read32(adapter->mmio + GFX_INT_SIP_MASK_HIGH));

    gf_translate_interrupt_bits(disp_info, 0, &intr_info, &masks);

    return masks;
}

static void gf_set_intr_enable_mask_hp(disp_info_t* disp_info, int masks)
{
    adapter_info_t *adapter = disp_info->adp_info;
    intr_info_t intr_info = {0};

    gf_translate_interrupt_bits(disp_info, 1, &intr_info, &masks);

    gf_write32(adapter->mmio + GFX_INT_SIP_MASK_LOW, ~(intr_info.sip_intr_lbits));
    gf_write32(adapter->mmio + GFX_INT_SIP_MASK_HIGH, ~(intr_info.sip_intr_hbits));
}

static void gf_enable_msi_hp(disp_info_t* disp_info)
{
#if 0
    unsigned int        tmp;
    adapter_info_t*  adapter = disp_info->adp_info;

    //when MSI is turned on from registry,the MSI address should have be written here by OS
    tmp = gf_read32(adapter->mmio + 0x804C);

    if (tmp != 0)
    {
        tmp = gf_read32(adapter->mmio + 0x8048);
        if ((tmp & 0x10000) == 0)
        {
            // Before turn on MSI we need clear all pending interrupts, clear all BIU interrupts
            gf_write32(adapter->mmio + INTR_SHADOW_REG, 0);

            gf_write32(adapter->mmio + 0x8048, tmp | 0x10000);
        }
    }
#endif
}

static void gf_disable_msi_hp(disp_info_t* disp_info)
{
#if 0
    unsigned int        temp;
    adapter_info_t*  adapter = disp_info->adp_info;

    temp = gf_read32(adapter->mmio + 0x8048);
    temp &= ~0x10000;

    gf_write32(adapter->mmio + 0x8048, temp);
#endif
}

static int gf_disable_interrupt_hp(disp_info_t* disp_info)
{
    adapter_info_t *adapter = disp_info->adp_info;
    int intr_masks;

    //save enabled interrupts, later will restore it in enable_interrupt
    intr_masks = gf_get_intr_enable_mask_hp(disp_info);

    //trigger eoi to clear pending int and disable interrupt
    gf_write32(adapter->mmio + GFX_INT_CTRL_REG, 0x80000000);

    return intr_masks;
}

static void gf_enable_interrupt_hp(disp_info_t* disp_info, int intr_masks)
{
    adapter_info_t *adapter = disp_info->adp_info;
    intr_info_t intr_info = {0};

    gf_translate_interrupt_bits(disp_info, 1, &intr_info, &intr_masks);

    gf_write32(adapter->mmio + GFX_INT_SIP_MASK_LOW, ~(intr_info.sip_intr_lbits));
    gf_write32(adapter->mmio + GFX_INT_SIP_MASK_HIGH, ~(intr_info.sip_intr_hbits));

    //trigger eoi to clear pendint int and enable interrupt
    gf_write32(adapter->mmio + GFX_INT_CTRL_REG, 0xA0000003);
}

static int gf_get_interrupt_mask_hp(disp_info_t* disp_info)
{
    adapter_info_t *adapter = disp_info->adp_info;
    intr_info_t intr_info = {0};
    int intr_masks = 0, intc_ctrl = 0, i = 0;

    intr_info.sip_intr_lbits = gf_read32(adapter->mmio + GFX_INT_SIP_ACTIVE_LOW);
    intr_info.sip_intr_hbits = gf_read32(adapter->mmio + GFX_INT_SIP_ACTIVE_HIGH);

    gf_translate_interrupt_bits(disp_info, 0, &intr_info, &intr_masks);

    intc_ctrl = gf_read32(adapter->mmio + GFX_INT_CTRL_REG);
    gf_write32(adapter->mmio + GFX_INT_CTRL_REG, intc_ctrl & 0xDFFFFFFF);

    intc_ctrl = gf_read32(adapter->mmio + GFX_INT_CTRL_REG);
    //trigger eoi to update active from pending
    gf_write32(adapter->mmio + GFX_INT_CTRL_REG, intc_ctrl | 0xA0000000);

    while (i < 10)
    {
        intc_ctrl = gf_read32(adapter->mmio + GFX_INT_CTRL_REG);
        //eoi switch done
        if (intc_ctrl & 0x40000000)
        {
            break;
        }

        i++;
    }

    if (i == 10)
    {
        gf_warning("interrupt check EOI status timeout!!!\n");
    }

    return intr_masks;
}

irq_chip_funcs_t irq_hp_chip_funcs =
{
    .get_intr_enable_mask = gf_get_intr_enable_mask_hp,
    .set_intr_enable_mask = gf_set_intr_enable_mask_hp,
    .enable_msi = gf_enable_msi_hp,
    .disable_msi = gf_disable_msi_hp,
    .disable_interrupt = gf_disable_interrupt_hp,
    .enable_interrupt = gf_enable_interrupt_hp,
    .get_interrupt_mask = gf_get_interrupt_mask_hp,
};
