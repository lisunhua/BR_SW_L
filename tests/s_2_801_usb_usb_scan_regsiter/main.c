/*
 *++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 * Copyright (c) 1999-2018 Barrot Technology Limited
 *
 * All rights reserved.
 *
 *------------------------------------------------------------------------------
 */
/**
 * @file main.c
 * @brief Main program entry
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

#include <stdio.h>
#include "BR00x_uart.h"
#include "BR00x_clock.h"
#include "BR00x_config.h"
#include "verify_message.h"
#include "verify_register_handle.h"
#include "log_uart_config.h"

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


int main (void)
{
    sysTimeUpdataClk(SystemCoreClock);
    Verrify_SendPinConnect(UART0_OUTPUT);
    LOGUartInit();
    c_printf("s_2_801_usb_usb_scan_regsiter case \r\n");
    {
        uint32_t idx=0;
        bool sut = true;
        c_printf("s_2_801_usb_usb_scan_regsiter case completed \r\n");
        SystemDevClockCtl(USB_HCKEn,true);

        sut =Verify_RegisterHandle(USB_RegList,sizeof(USB_RegList),idx);
        Verify_SendCResult(BRCASE_RESULT,sut);
    }
    SimulationEnd();
    while(1){     
    };
}
















