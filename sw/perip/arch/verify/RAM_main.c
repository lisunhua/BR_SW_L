/*
 *++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 * Copyright (c) 1999-2018 Barrot Technology Limited
 *
 * All rights reserved.
 *
 *------------------------------------------------------------------------------
 */
/**
 * @file RAM_main.c
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

#include <stdio.h>
#include "BR00x_config.h"
#include "cm_printf.h"
#include "BR00x_uart.h"


void UartDebugOutput(void)
{
    UART_InitInfo_Type UART_InitStru;
    UART_InitStru.UART_BaudRate = 500000;
    UART_InitStru.UART_WordLength = UART_WL_8BITS;
    UART_InitStru.UART_StopBits = UART_SB_1BIT;
    UART_InitStru.UART_ParityMode = UART_PM_NONE;
    UART_InitStru.UART_HardwareFlowControl = UART_FC_NONE;
    UART_InitStru.UART_FIFOMode = UART_FM_ENABLE;
    UART_InitStru.UART_DMAMode = UART_DM_MODE_0;
    UART_InitStru.UART_TX_FIFOTriggerMode = UART_TT_EMPTY;
    UART_InitStru.UART_RX_FIFOTriggerMode = UART_RT_1_CHARACTER;
     
    UART_Init(UART0, &UART_InitStru); 
    UART_InterruptSet(UART0,0x01ul<<UART_ERBFI);
    NVIC_ClearPendingIRQ(UART0_IRQn);
    NVIC_EnableIRQ(UART0_IRQn);
    
}


int main(void)
{
    UartDebugOutput();
    cm_printf("ROM Start ...\r\n");
    cm_printf("ROM Test 1 \r\n");
    cm_printf("ROM Test 2 \r\n");
    cm_printf("ROM Test 3 \r\n");
    cm_printf("ROM Test 4 \r\n");
    
    SCU->SEND_DATA  = 1;
    SCU->SEND_CMD   = 3;
}




