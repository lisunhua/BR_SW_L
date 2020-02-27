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

void osc32KEnable(void)
{
    PADConfig_Type      PAD_InitStru; 
    memset(&PAD_InitStru, 0,sizeof(PADConfig_Type));
    PAD_InitStru.pad_ctl = PAD_MODE1;
    SystemPADConfig(PADID7,&PAD_InitStru);
    SCU->SEND_DATA = 0xE020;                 // TODO  SH //TB Need
}


int main (void)
{
    sysTimeUpdataClk(SystemCoreClock);
    Verrify_SendPinConnect(UART0_OUTPUT);
    LOGUartInit();
    c_printf("s_1_656_scu_change_pclk_async_uart0_tx case \r\n");
    c_printf("Set HCLK=PCLK=SCLK = osc_24M\n");
    osc32KEnable();
    MCU_Sleep(1);
    {

        /***************************************************************/
        SCU_UART0ClkSelect(CLK_OSC_26M);
        c_printf("Set HCLK=PCLK=osc_24M,SCLK = osc_24M\n");
        MCU_Sleep(1);

        /***************************************************************/
        SCU_ClockSelectDivControl(CLK_24M);
        SCU_HClkSelect(CLK_HCLK_MUX);
        c_printf("Set HCLK=PCLK=DPLL 24M,SCLK = osc_24M\n");
        MCU_Sleep(1);

        /***************************************************************/
        SCU_PClkPreSelect(HCLK_DIV02);
        SCU_PClkSelect(HCLK_DIV_2_PCLK);
        c_printf("Set HCLK=DPLL 24M,PCLK=DPLL 12M,SCLK = osc_24M\n");
        MCU_Sleep(1);

        /***************************************************************/
        SCU_PClkSelect(HCLK_2_PLCK);
        SCU_32KDiv(4);
        SCU_32KClkSelect(CLK_RCO_32K);
        SCU_HClkSelect(CLK_32K_MUX_HCLK);
        c_printf("Set HCLK=PCLK=roc_32K,SCLK = osc_24M\n");
        for(uint16_t i=0;i<10;i++){};

        /***************************************************************/
        SCU_32KClkSelect(CLK_OSC_32K);
        c_printf("Set HCLK=PCLK=osc_32K,SCLK = osc_24M\n");
        for(uint16_t i=0;i<10;i++){};

        /***************************************************************/

        SCU_32KClkSelect(clk_DIV_32K);
        c_printf("Set HCLK=PCLK=div_32K,SCLK = osc_24M\n");
        for(uint16_t i=0;i<10;i++){};

        /***************************************************************/
        SCU_PClkSelect(HCLK_2_PLCK);
        SCU_HClkSelect(CLK_OSC26m);
        c_printf("Set HCLK=PCLK=osc_24M, SCLK = osc_24M\n");
    }

	MCU_Sleep(3);
    c_printf("s_1_656_scu_change_pclk_async_uart0_tx case completed \r\n");
    SimulationEnd();
    while(1){     
    };
}
















