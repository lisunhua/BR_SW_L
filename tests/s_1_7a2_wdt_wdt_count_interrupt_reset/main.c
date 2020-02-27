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

static  uint8_t  WDT_Run_Test=0;

int main (void)
{
    sysTimeUpdataClk(SystemCoreClock);
    Verrify_SendPinConnect(UART0_OUTPUT);
    LOGUartInit();
    c_printf("s_1_7a2_wdt_wdt_count_interrupt_reset case \r\n");
    {
        WDT_InitInfo_Type Wdt_InitStru;
        
        Wdt_InitStru.response_mode = WDT_RESPONSE_INTRTRUPT_RESET;
        Wdt_InitStru.timeout_init_period = 0;       //Cannot Set
                
        SystemDevClockCtl(WDT_CKEn,true); 
        
        for(uint32_t pd = 0; pd<3 ;pd++)   //Select parameter tests that are easy to test
        {
            Wdt_InitStru.timeout_period   = pd; // CLOCK Width   = timeout period +16 
            
            uint32_t max_pck = pd+1;
            if (max_pck>WDT_256PCLK_CYCLES)
                max_pck = WDT_256PCLK_CYCLES;
            
            for(WDT_PclkCycles_Type pct =WDT_2PCLK_CYCLES;pct<=max_pck;pct++)
            {
                Wdt_InitStru.pclk_cycles = pct;
                WDT_Run_Test++;
               
                WDT_Init(&Wdt_InitStru);
                c_printf("wdt:pd[%d],pct[%d]\r\n",pd,pct);
                while(WDT_Run_Test);
            }   
        }            

    }
    c_printf("s_1_7a2_wdt_wdt_count_interrupt_reset case completed \r\n");
	MCU_Sleep(3);
    SimulationEnd();
    while(1){     
    };
}


void NMI_Handler(void)
{
    if(WDT_Run_Test)
        wdt_ClearInterrupt();
    
    c_printf("WDT Int[%d]\r\n",WDT_Run_Test);
    WDT_Run_Test=0;
}















