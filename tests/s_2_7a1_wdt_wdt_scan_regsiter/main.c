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

const RegisterCell WDT_RegList[]=
{
//  {read,  write,  Register ID ,register_attr, Register},
    {true,  true,   1,  0x0000003E,     &WDT->CR},
    {true,  true,   2,  0x0000000F,     &WDT->TORR},
    {true,  false,  3,  0xFFFFFFFF,     (volatile uint32_t*)&WDT->CCVR},
    {false, true,   4,  0x000000FF,     &WDT->CRR}, 
    {true,  false,  5,  0x00000001,     (volatile uint32_t*)&WDT->STAT},
    {true,  false,  6,  0x00000001,     (volatile uint32_t*)&WDT->EIO},
};

int main (void)
{
    sysTimeUpdataClk(SystemCoreClock);
    Verrify_SendPinConnect(UART0_OUTPUT);
    LOGUartInit();
    c_printf("s_2_7a1_wdt_wdt_scan_regsiter case \r\n");
    {
        bool sut = true;
        uint32_t idx=0;
        SystemDevClockCtl(WDT_CKEn,true);
        sut =Verify_RegisterHandle(WDT_RegList,sizeof(WDT_RegList),idx);
        Verify_SendCResult(BRCASE_RESULT,sut);
    }
    SimulationEnd();
    while(1){     
    };
}
















