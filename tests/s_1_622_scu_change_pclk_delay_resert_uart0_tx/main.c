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
#include "log_uart_config.h"

void ScuOutput(void)
{
    UART_InitInfo_Type UART_InitStru;
    UART_InitStru.UART_BaudRate = 1200;
    UART_InitStru.UART_WordLength = UART_WL_8BITS;
    UART_InitStru.UART_StopBits = UART_SB_1BIT;
    UART_InitStru.UART_ParityMode = UART_PM_NONE;
    UART_InitStru.UART_HardwareFlowControl = UART_FC_NONE;
    UART_InitStru.UART_FIFOMode = UART_FM_ENABLE;
    UART_InitStru.UART_DMAMode = UART_DM_MODE_0;
    UART_InitStru.UART_TX_FIFOTriggerMode = UART_TT_EMPTY;
    UART_InitStru.UART_RX_FIFOTriggerMode = UART_RT_1_CHARACTER;
    UART_Init(UART0, &UART_InitStru); 
    
}

int main (void)
{
    sysTimeUpdataClk(SystemCoreClock);
    Verrify_SendPinConnect(UART0_OUTPUT);
    LOGUartInit();
    c_printf("s_1_622_scu_change_pclk_delay_resert_uart0_tx case \r\n");

    {
        c_printf("SCU pclk 26M [%ld]\n",SystemCoreClock); 
        SystemCoreClock = 32768;	
        c_printf("SCU pclk 32.768k [%ld]\n",SystemCoreClock);  
        while(UART_GetStatus(UART0)& 0x01){};
        for(uint16_t i=0;i<1000;i++){};
        SCU_HClkSelect(CLK_32K_MUX_HCLK);
        for(uint16_t i=0;i<100;i++){};
        ScuOutput();
        c_printf("67890\n");
    }
	//MCU_Sleep(3);
    //c_printf("s_1_622_scu_change_pclk_delay_resert_uart0_tx case completed \r\n");
    SimulationEnd();
    while(1){     
    };
}
















