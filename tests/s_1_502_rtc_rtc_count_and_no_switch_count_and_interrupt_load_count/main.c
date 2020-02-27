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
#include "BR00x_rtc.h"
#include "BR00x_config.h"
#include "verify_message.h"
#include "log_uart_config.h"


extern unsigned long int SystemCoreClock;
#define SEC(x)      (x*SystemCoreClock)
#define MEC(x)      (x*(SystemCoreClock/1000))
#define LMEC(x)     (x*(32000UL/1000))


static  uint8_t RCT_APP_CASE = 0;
static uint8_t RTC_Case2IntCount =0;

int main (void)
{
    bool sut = true;
    sysTimeUpdataClk(SystemCoreClock);
    Verrify_SendPinConnect(UART0_OUTPUT);
    LOGUartInit();
    c_printf("s_1_502_rtc_rtc_count_and_no_switch_count_and_interrupt_load_count case \r\n");
    {
        RTC_InitInfo_Type RTC_InitStru;
        uint32_t budat= RTC_Case2IntCount;
           
        c_printf("H Clock RTC\r\n");
        RTC_InitStru.RTC_Interrpt = RTC_INTERRUPT_ENABLE ;
        RTC_InitStru.RTC_InterruptValue   = MEC(3);
        RTC_InitStru.RTC_StartValue  = 0;
        
        SystemDevClockCtl(RTC_CKEn,true);
        
        RTC_Init(&RTC_InitStru);
        RCT_APP_CASE = 2;
        RTC_Case2IntCount = 0;
        NVIC_EnableIRQ(RTC_IRQn);
        
        while(RTC_Case2IntCount<3)//There may be a problem
        {
            if(budat!=RTC_Case2IntCount)
            {
                c_printf("RTC cut[%X]\r\n",RTC_CurrentValue());
                budat = RTC_Case2IntCount;
            }
        };  

    }
    c_printf("s_1_502_rtc_rtc_count_and_no_switch_count_and_interrupt_load_count case completed \r\n");
	MCU_Sleep(3);
    SimulationEnd();
    while(1){     
    };
}

void RTC_IRQHandler(void)       
{     
    RTC_ClearInterrupt();
    
    if(RCT_APP_CASE==2)
    {
        RTC_Case2IntCount++;
        RTC_SET_LOAD_COUNTER_VALUE(0);
    }
    c_printf("RTC [%d]Int,[%d]\r\n",RCT_APP_CASE,RTC_Case2IntCount);
}  

















