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

const RegisterCell RTC_RegList[]=
{
//  {read,  write,  Register ID ,register_attr, Register},
    {true,  false,  1,  0xFFFFFFFF,     (volatile uint32_t *)&RTC->DR},
    {true,  true,   2,  0xFFFFFFFF,     &RTC->CMR},
    {true,  true,   3,  0xFFFFFFFF,     &RTC->CLR},
    //{true,  true,   4,  0x00000001,     &RTC->CCR}, //Enable Bit ,Cannot Enable
    {true,  true,   5,  0x00000001,     &RTC->IMSC},
    {true,  false,  6,  0x00000001,     (volatile uint32_t *)&RTC->RIS},
    {true,  false,  7,  0x00000001,     (volatile uint32_t *)&RTC->MIS},
    {false, true,   8,  0x00000001,     &RTC->ICR},

};

int main (void)
{
    sysTimeUpdataClk(SystemCoreClock);
    Verrify_SendPinConnect(UART0_OUTPUT);
    LOGUartInit();
    c_printf("s_2_501_rtc_rtc_scan_regsiter case \r\n");
    {
        bool sut = true;
        uint32_t idx=0;
        
        SystemDevClockCtl(RTC_CKEn,true);
        sut =Verify_RegisterHandle(RTC_RegList,sizeof(RTC_RegList),idx);
        Verify_SendCResult(BRCASE_RESULT,sut);
    }
    SimulationEnd();
    while(1){     
    };
}
















