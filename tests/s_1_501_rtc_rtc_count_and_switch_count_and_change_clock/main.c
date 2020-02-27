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


static  bool verify_rtcApp(bool st)
{
    uint32_t cut[3]={0,0,0};
    bool sut = true;

    for(uint8_t i=0;i<3;i++)
    {
        cut[i]=RTC_CurrentValue();
        c_printf("RTC [%d],cut[%X]\r\n",i,cut[i]);
    }
    c_printf("RTCl\r\n");
    if(st){
        if(!(cut[0] == cut[1] && cut[1] == cut[2]))
            sut = false;}
    else{
        if(cut[0] == cut[1] && cut[1] == cut[2])
            sut = false;}

    return sut;
}


int main (void)
{
    bool sut = true;
    sysTimeUpdataClk(SystemCoreClock);
    Verrify_SendPinConnect(UART0_OUTPUT);
    LOGUartInit();
    c_printf("s_1_501_rtc_rtc_count_and_switch_count_and_change_clock case \r\n");
    {
        RTC_InitInfo_Type RTC_InitStru;
        RTC_InitStru.RTC_Interrpt = RTC_INTERRUPT_DISABLE ;
        RTC_InitStru.RTC_InterruptValue   = SEC(1);
        RTC_InitStru.RTC_StartValue  = 0;
        
        SystemDevClockCtl(RTC_CKEn,true);
        RTC_Init(&RTC_InitStru);
        
        c_printf("H Clock RTC 26M\r\n");
#if  defined(BR002)||defined(BR003)
        SCU_PClkSelect(HCLK_DIV_2_PCLK);
        SCU_PClkPreSelect(HCLK_2_PLCK_PRE);
#endif         
        
        sut = verify_rtcApp(false);
        
        if(sut)
        {
            RTC_Run(false);
            verify_rtcApp(true);
        }
        if(sut)
        {
            RTC_Run(true);
            verify_rtcApp(false);
        }
        if(sut)
        {
            RTC_Run(false);
            verify_rtcApp(true);
        }
        if(sut)
        {
            RTC_Run(true);
            verify_rtcApp(false);
        }
                   
        RTC_DeInit();
   
#if  defined(BR002)||defined(BR003)
        SCU_PClkSelect(HCLK_DIV_2_PCLK);
        SCU_PClkPreSelect(HCLK_DIV16);
#endif   
        c_printf("L Clock RTC 32K\r\n");
        RTC_InitStru.RTC_InterruptValue   = LMEC(5);
        RTC_Init(&RTC_InitStru);
        sut = verify_rtcApp(false);
        if(sut)
        {
            RTC_Run(false);
            verify_rtcApp(true);
        }
        if(sut)
        {
            RTC_Run(true);
            verify_rtcApp(false);
        }
        if(sut)
        {
            RTC_Run(false);
            verify_rtcApp(true);
        }
        if(sut)
        {
            RTC_Run(true);
            verify_rtcApp(false);
        }

    }
    c_printf("s_1_501_rtc_rtc_count_and_switch_count_and_change_clock case completed \r\n");
	MCU_Sleep(1);
    SimulationEnd();
    while(1){     
    };
}
















