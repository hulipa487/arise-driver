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


#include "CBios_Arise.h"
#include "CBiosFlash_Arise.h"

#define TRANSFER_DELAY 0 //us

CBIOS_VOID cbSF_Init(PCBIOS_VOID pvcbe)
{
    PCBIOS_EXTENSION_COMMON pcbe = (PCBIOS_EXTENSION_COMMON)pvcbe;

    cb_WriteU8(pcbe->pAdapterContext, 0xa0024, 0x80);
}
CBIOS_STATUS cbSF_Address_Check(PCBIOS_VOID pvcbe, CBIOS_U32 Addr, CBIOS_U32 Size)
{
    PCBIOS_EXTENSION_COMMON pcbe = (PCBIOS_EXTENSION_COMMON)pvcbe;
    CBIOS_STATUS status = CBIOS_ER_INTERNAL;

    if(Addr < SF_START_ADDR)//if start addr is under the 704K, maybe cover the firmware
    {
        cbDebugPrint((MAKE_LEVEL(GENERIC, ERROR), "%s: addr is under the SF_START_ADDR!\n", FUNCTION_NAME));
        return status;
    }
    if((Addr > ROM_SIZE) || (Addr + Size > ROM_SIZE))//if addr or addr + size is above 1M, exceed the rom size
    {
        cbDebugPrint((MAKE_LEVEL(GENERIC, ERROR), "%s: addr is exceed the rom size!\n", FUNCTION_NAME));
        return status;
    }
    return CBIOS_OK;
}
CBIOS_VOID cbSF_Read_Data(PCBIOS_VOID pvcbe, CBIOS_U32 Addr, PCBIOS_UCHAR Buffer, CBIOS_U8 Len)
{
    PCBIOS_EXTENSION_COMMON pcbe = (PCBIOS_EXTENSION_COMMON)pvcbe;
    CBIOS_SF_Control Sf_Ctrl = {0};
    CBIOS_SF_Cmd_Addr Sf_Cmd_Addr = {0};
    CBIOS_U32 Sf_Data[1] = {0};
    CBIOS_U32 i = 0;

    Sf_Cmd_Addr.Comamd = 0x03;
    Sf_Cmd_Addr.Addr = Addr;
    cb_WriteU32(pcbe->pAdapterContext, SF_CMD_ADDR, Sf_Cmd_Addr.Value);

    Sf_Ctrl.Data_len = Len;
    Sf_Ctrl.Addr_en = 1;
    Sf_Ctrl.Rw = 0;
    Sf_Ctrl.En_flag = 1;
    if(Sf_Ctrl.Data_len > 4)
    {
        Sf_Ctrl.Data_len = 4;
    }
    cb_DelayMicroSeconds(TRANSFER_DELAY);
    cb_WriteU8(pcbe->pAdapterContext, SF_CONTROL, Sf_Ctrl.Value);

    //waitting for transfer have finished
    do{
        Sf_Ctrl.Value = cb_ReadU8(pcbe->pAdapterContext, SF_CONTROL);
        i++;
        if(i > TIME_OUT_COUNTER)
        {
            cbDebugPrint((MAKE_LEVEL(GENERIC, ERROR), "%s: waitting for transfer timeout\n", FUNCTION_NAME));
            return;
        }
        cb_DelayMicroSeconds(TRANSFER_DELAY);
    }while(Sf_Ctrl.En_flag);

    Sf_Data[0] = cb_ReadU32(pcbe->pAdapterContext, SF_RDATA);
    //Clear the data over Len
    for(i = Len; i < 4; i++)
    {
        *((PCBIOS_U8)(Sf_Data) + i) = 0x00;
    }
    cb_memcpy(Buffer, (PCBIOS_U8)(Sf_Data), Len);

}

CBIOS_U16 cbSF_Read_Status(PCBIOS_VOID pvcbe)
{
    PCBIOS_EXTENSION_COMMON pcbe = (PCBIOS_EXTENSION_COMMON)pvcbe;
    CBIOS_SF_Control Sf_Ctrl = {0};
    CBIOS_SF_Cmd_Addr Sf_Cmd_Addr = {0};
    CBIOS_U32 Read_Data = 0;
    CBIOS_U32 i = 0;

    Sf_Cmd_Addr.Comamd = 0x05;
    //Sf_Cmd_Addr.Addr = addr;
    cb_WriteU32(pcbe->pAdapterContext, SF_CMD_ADDR, Sf_Cmd_Addr.Value);

    Sf_Ctrl.Data_len = 2;
    Sf_Ctrl.Addr_en = 0;
    Sf_Ctrl.Rw = 0;
    Sf_Ctrl.En_flag = 1;
    cb_DelayMicroSeconds(TRANSFER_DELAY);
    cb_WriteU8(pcbe->pAdapterContext, SF_CONTROL, Sf_Ctrl.Value);
    //waitting for transfer have finished
    do{
        Sf_Ctrl.Value = cb_ReadU8(pcbe->pAdapterContext, SF_CONTROL);
        i++;
        if(i > TIME_OUT_COUNTER)
        {
            cbDebugPrint((MAKE_LEVEL(GENERIC, ERROR), "%s: waitting for transfer timeout\n", FUNCTION_NAME));
            return 0;
        }
    }while(Sf_Ctrl.En_flag);

    Read_Data = cb_ReadU32(pcbe->pAdapterContext, SF_RDATA);

    return Read_Data & 0xffff;
 }

CBIOS_VOID cbSF_Write_Enable(PCBIOS_VOID pvcbe)
{
    PCBIOS_EXTENSION_COMMON pcbe = (PCBIOS_EXTENSION_COMMON)pvcbe;
    CBIOS_SF_Control Sf_Ctrl = {0};
    CBIOS_SF_Cmd_Addr Sf_Cmd_Addr = {0};
    CBIOS_U32 i= 0;

    Sf_Cmd_Addr.Comamd = 0x06;
    cb_WriteU32(pcbe->pAdapterContext, SF_CMD_ADDR, Sf_Cmd_Addr.Value);

    Sf_Ctrl.Data_len = 0;
    Sf_Ctrl.Addr_en = 0;
    Sf_Ctrl.Rw = 1;
    Sf_Ctrl.En_flag = 1;
    cb_DelayMicroSeconds(TRANSFER_DELAY);
    cb_WriteU8(pcbe->pAdapterContext, SF_CONTROL, Sf_Ctrl.Value);

    //waitting for transfer have finished
    do{
        Sf_Ctrl.Value = cb_ReadU8(pcbe->pAdapterContext, SF_CONTROL);
        i++;
        if(i > TIME_OUT_COUNTER)
        {
            cbDebugPrint((MAKE_LEVEL(GENERIC, ERROR), "%s: waitting for transfer timeout\n", FUNCTION_NAME));
            break;
        }
    }while(Sf_Ctrl.En_flag);
}

CBIOS_VOID cbSF_Write_Data(PCBIOS_VOID pvcbe, CBIOS_U32 Addr, PCBIOS_UCHAR Buffer, CBIOS_U8 Len)
{
    PCBIOS_EXTENSION_COMMON pcbe = (PCBIOS_EXTENSION_COMMON)pvcbe;
    CBIOS_SF_Control Sf_Ctrl = {0};
    CBIOS_SF_Cmd_Addr Sf_Cmd_Addr = {0};
    CBIOS_U32 Sf_Data[1] = {0};
    CBIOS_U32 i = 0;

    cbSF_Write_Enable(pcbe);
    Sf_Cmd_Addr.Comamd = 0x02;
    Sf_Cmd_Addr.Addr = Addr;
    cb_WriteU32(pcbe->pAdapterContext, SF_CMD_ADDR, Sf_Cmd_Addr.Value);

    cb_memcpy((PCBIOS_U8)(Sf_Data), Buffer, Len);
    //Clear the data over Len
    for(i = Len; i< 4; i++)
    {
        *((PCBIOS_U8)(Sf_Data) + i) = 0x00;
    }
    cb_WriteU32(pcbe->pAdapterContext, SF_WDATA, Sf_Data[0]);

    Sf_Ctrl.Data_len = Len;
    Sf_Ctrl.Addr_en = 1;
    Sf_Ctrl.Rw = 1;
    Sf_Ctrl.En_flag = 1;
    if(Sf_Ctrl.Data_len > 4)
    {
        Sf_Ctrl.Data_len = 4;
    }
    cb_DelayMicroSeconds(10);
    cb_WriteU8(pcbe->pAdapterContext, SF_CONTROL, Sf_Ctrl.Value);

    //waitting for transfer have finished
    do{
        Sf_Ctrl.Value = cb_ReadU8(pcbe->pAdapterContext, SF_CONTROL);
        i++;
        if(i > TIME_OUT_COUNTER)
        {
            cbDebugPrint((MAKE_LEVEL(GENERIC, ERROR), "%s: waitting for transfer timeout\n", FUNCTION_NAME));
            break;
        }
        cb_DelayMicroSeconds(5);
    }while(Sf_Ctrl.En_flag);

    i=0;
    while(cbSF_Read_Status(pcbe)& 0x01)
    {
        //cb_DelayMicroSeconds(10);
        i++;
        if(i > TIME_OUT_COUNTER)
        {
            cbDebugPrint((MAKE_LEVEL(GENERIC, ERROR), "%s: waitting for sf free(cbSF_Read_Status) timeout\n", FUNCTION_NAME));
            break;
        }
    }

 }
 CBIOS_VOID cbSF_Sector_Erase(PCBIOS_VOID pvcbe, CBIOS_U32 Addr)
 {
    PCBIOS_EXTENSION_COMMON pcbe = (PCBIOS_EXTENSION_COMMON)pvcbe;
    CBIOS_SF_Control Sf_Ctrl = {0};
    CBIOS_SF_Cmd_Addr Sf_Cmd_Addr = {0};
    CBIOS_U32 i = 0;

    //cb_DelayMicroSeconds(10);
    cbSF_Write_Enable(pcbe);
    Sf_Cmd_Addr.Comamd = 0x20;
    Sf_Cmd_Addr.Addr = Addr;
    cb_WriteU32(pcbe->pAdapterContext, SF_CMD_ADDR, Sf_Cmd_Addr.Value);

    Sf_Ctrl.Data_len=0;
    Sf_Ctrl.Addr_en = 1;
    Sf_Ctrl.Rw = 1;
    Sf_Ctrl.En_flag = 1;
    if(Sf_Ctrl.Data_len > 4)
    {
        Sf_Ctrl.Data_len = 4;
    }
    cb_DelayMicroSeconds(10);
    cb_WriteU8(pcbe->pAdapterContext, SF_CONTROL, Sf_Ctrl.Value);

    //waitting for transfer have finished
    do{
        Sf_Ctrl.Value = cb_ReadU8(pcbe->pAdapterContext, SF_CONTROL);
        i++;
        if(i > TIME_OUT_COUNTER)
        {
            cbDebugPrint((MAKE_LEVEL(GENERIC, ERROR), "%s: waitting for transfer timeout\n", FUNCTION_NAME));
            break;
        }
    }while(Sf_Ctrl.En_flag);

    // waitting for sf free
    cb_DelayMicroSeconds(500);

    i=0;
    while(cbSF_Read_Status(pcbe)&0x01)
    {
        i++;
        if(i > TIME_OUT_COUNTER*20)
        {
            cbDebugPrint((MAKE_LEVEL(GENERIC, ERROR), "%s: waitting for sf free(cbSF_Read_Status) timeout\n", FUNCTION_NAME));
            break;
        }
        cb_DelayMicroSeconds(500);
    }
}

