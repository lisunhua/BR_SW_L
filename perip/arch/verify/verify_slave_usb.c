/*
 *++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 * Copyright (c) 1999-2018 Barrot Technology Limited
 *
 * All rights reserved.
 *
 *------------------------------------------------------------------------------
 */
/**
 * @file verify_slave_usb.c
 * @brief
 * @attention
 *
 * THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
 * WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE
 * TIME. AS A RESULT, STMICROELECTRONICS SHALL NOT BE HELD LIABLE FOR ANY
 * DIRECT, INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING
 * FROM THE CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE
 * CODING INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
 *
 * @date    14. Augest 2019
 * @version V1.0.0
 * @author  MEIGER
*/

#include "cm_printf.h"
#include "verify_slave_usb.h"
#include "verify_message.h"
#include "verify_register_handle.h"
#include "BR00x_config.h"


#ifdef USB_DEBUG_LOG
#define usbprf(format, ...) cm_printf(format, ##__VA_ARGS__)
#else
#define usbprf(format, ...)
#endif

const RegisterCell USB_RegList[]=
{
#if  defined(BR002)||defined(BR003)
//  {read,  write,  Register ID ,register_attr, Register},
    {true,  true,   1,  0x0000003E,     &USB->GOTGCTL},
    {true,  true,   2,  0x01e001bf,     &USB->GAHBCFG},
    {true,  true,   3,  0xfbfebc87,     &USB->GUSBCFG},
    {true,  true,   4,  0x000007c0,     &USB->GRSTCTL},
    {true,  true,   5,  0xfffffffE,     &USB->GINTMSK},
    {true,  true,   6,  0x007fffff,     &USB->GPVNDCTL},
#else
    {true,  true,   6,  0x007fffff,     0},
#endif

};

/***********************************************************
                        Register
************************************************************/


bool cmd_VerifyRegisterUSBCase2(uint32_t cmd, uint8_t *param_line,uint16_t len)
{
    bool sut = true;
    
#if  defined(BR002)||defined(BR003)
    uint32_t cid = cmd;
    uint32_t idx=0;
    usbprf("USB Reg case2\r\n");
    SystemDevClockCtl(USB_HCKEn,true);
    verify_SendCid(cid,&idx);
    sut =Verify_RegisterHandle(USB_RegList,sizeof(USB_RegList),idx);
    Verify_SendCResult(BRCASE_RESULT,sut);
#endif
    return sut;

}



/***********************************************************
                        APP
************************************************************/



