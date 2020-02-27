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
#include "BR00x_wdt.h"
#include "BR00x_config.h"
#include "verify_message.h"
#include "log_uart_config.h"


int main (void)
{
    // LOG UART INIT
    sysTimeUpdataClk(SystemCoreClock);
    Verrify_SendPinConnect(UART0_OUTPUT);
    LOGUartInit();
    c_printf("s_1_7a3_wdt_wdt_reset case \r\n");
    {
        WDT_InitInfo_Type Wdt_InitStru;
        Wdt_InitStru.response_mode = WDT_RESPONSE_RESET;
        Wdt_InitStru.timeout_init_period = 0;       //Cannot Set
        
        SystemDevClockCtl(WDT_CKEn,true); 
        Wdt_InitStru.timeout_period = 0;
        Wdt_InitStru.pclk_cycles = WDT_8PCLK_CYCLES;
        WDT_Init(&Wdt_InitStru);        


    }
    c_printf("s_1_7a3_wdt_wdt_reset case completed \r\n");
    MCU_Sleep(1);
    SimulationEnd();
    while(1){     
    };
}















