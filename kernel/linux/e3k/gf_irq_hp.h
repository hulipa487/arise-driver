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
#ifndef _GF_IRQ_HP_
#define _GF_IRQ_HP_

#include "../gf_irq.h"

#define GFX_INT_BASE_ADDR       0x140000
#define GFX_INT_SIP_MASK_LOW    (GFX_INT_BASE_ADDR + 0x0)
#define GFX_INT_SIP_MASK_HIGH   (GFX_INT_BASE_ADDR + 0x4)
#define GFX_INT_CTRL_REG        (GFX_INT_BASE_ADDR + 0x14)
#define GFX_INT_SIP_ACTIVE_LOW  (GFX_INT_BASE_ADDR + 0x48)
#define GFX_INT_SIP_ACTIVE_HIGH (GFX_INT_BASE_ADDR + 0x4C)



typedef enum _SIP_INT_BIT_LOW
{
    ENGINE_FENCE_INT = 0x1,
    VSYNC1_INT  = 0x10,
    VSYNC2_INT  = 0x40,
    VSYNC3_INT  = 0x80,
    VSYNC4_INT  = 0x100,
    DP1_INT     = 0x800,
    DP2_INT     = 0x1000,
    DP3_INT     = 0x100000,
    DP4_INT     = 0x200000,
}SIP_INT_BIT_LOW;

typedef enum _SIP_INT_BIT_HIGH
{
    HDCODEC_INT = 0x2,
}SIP_INT_BIT_HIGH;

typedef struct _intr_info
{
    unsigned int sip_intr_lbits;
    unsigned int sip_intr_hbits;
}intr_info_t;

#endif
