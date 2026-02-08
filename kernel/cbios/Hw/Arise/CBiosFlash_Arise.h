/*
 * Copyright © 2021 Glenfly Tech Co., Ltd.
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

#ifndef _CBIOS_FLASH_ARISE_H_
#define _CBIOS_FLASH_ARISE_H_

#define FP_SECTOR_SIZE 4096 //size of flash part sector (in bytes)

//#define SF_BASE_ADDR 	0x0000
#define SF_CONTROL    0x8a33 // one byte
#define SF_CMD_ADDR   0x8a34 // byte0: cmd, byte1`byte3: addr
#define SF_WDATA      0x8a38
#define SF_RDATA      0x8a3c

#define TIME_OUT_COUNTER 100000

#define SF_START_ADDR    0xb0000  //704k
#define ROM_SIZE         0x100000 //1M

typedef union
{
    CBIOS_U8 Value;
    struct
    {
        CBIOS_U8 Nop0       :2;
        CBIOS_U8 Data_len   :3; // data length:0-4 bytes
        CBIOS_U8 Rw         :1; // 0:read, 1:write
        CBIOS_U8 Addr_en    :1; // 0: not send 3 bytes address, 1: send 3 bytes address.
        CBIOS_U8 En_flag    :1; // write: write one to start once transform; read: 0: free, 1: busy
    };
}CBIOS_SF_Control;

typedef union
{
    CBIOS_U32 Value;
    struct
    {
        CBIOS_U32 Comamd        :8; // nor flash command
        CBIOS_U32 Addr          :24; // nor flash 24 bits address
    };
}CBIOS_SF_Cmd_Addr;

typedef union
{
    CBIOS_U32 Value;
    struct
    {
        CBIOS_U32 Byte0     :8;
        CBIOS_U32 Byte1     :8;
        CBIOS_U32 Byte2     :8;
        CBIOS_U32 Byte3     :8;
    };
}CBIOS_SF_Data;

CBIOS_VOID   cbSF_Init(PCBIOS_VOID pvcbe);
CBIOS_STATUS cbSF_Address_Check(PCBIOS_VOID pvcbe, CBIOS_U32 Addr, CBIOS_U32 Size);
CBIOS_VOID   cbSF_Read_Data(PCBIOS_VOID pvcbe, CBIOS_U32 Addr, PCBIOS_UCHAR Buffer, CBIOS_U8 Len);
CBIOS_U16    cbSF_Read_Status(PCBIOS_VOID pvcbe);
CBIOS_VOID   cbSF_Write_Enable(PCBIOS_VOID pvcbe);
CBIOS_VOID   cbSF_Write_Data(PCBIOS_VOID pvcbe, CBIOS_U32 Addr, PCBIOS_UCHAR Buffer, CBIOS_U8 Len);
CBIOS_VOID   cbSF_Sector_Erase(PCBIOS_VOID pvcbe, CBIOS_U32 Addr);


#endif
