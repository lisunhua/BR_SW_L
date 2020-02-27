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


int main (void)
{
    sysTimeUpdataClk(SystemCoreClock);
    Verrify_SendPinConnect(UART0_OUTPUT);
    LOGUartInit();
    c_printf("s_1_654_scu_test_mode_32k_sleep_awaken case \r\n");
    c_printf("Test Mode 0 Sleep and WK \n"); 
    {
        Verrify_SendPinConnect(TMODE_0);
        Verrify_SendPinConnect(TMODE_DIS);
        Verrify_SendPinConnect(TMODE_EN);
        c_printf("IO S[%X]\n",SCU->IO_STATUS);  
        MCU_Sleep(3);
        SCU_32KClkSelect(CLK_RCO_32K);      
        SCU_HClkSelect(CLK_32K_MUX_HCLK);
        for(uint16_t i=0;i<100;i++){};
            
        {
            RTC_InitInfo_Type RTC_InitStru;               
            RTC_InitStru.RTC_Interrpt = RTC_INTERRUPT_ENABLE ;
            RTC_InitStru.RTC_InterruptValue   = (10*32);
            RTC_InitStru.RTC_StartValue  = 0;
            SystemDevClockCtl(RTC_CKEn,true);
            RTC_Init(&RTC_InitStru);
            NVIC_EnableIRQ(RTC_IRQn);
        }
         SCU->ANA_CTL0   = 0xC0200000|0x01<<5 ;
         SCU->SLEEP_EN   = 0xffffffff;
    }

	MCU_Sleep(10);
    c_printf("s_1_654_scu_test_mode_32k_sleep_awaken case completed \r\n");
    SimulationEnd();
    while(1){     
    };
}
















