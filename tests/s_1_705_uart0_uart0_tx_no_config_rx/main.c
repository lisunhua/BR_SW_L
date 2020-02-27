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
#include "BR00x_gpio.h"
#include "BR00x_config.h"
#include "verify_message.h"
#include "log_uart_config.h"

int main (void)
{
    sysTimeUpdataClk(SystemCoreClock);
    Verrify_SendPinConnect(UART0_OUTPUT);
    LOGUartInit();
    c_printf("s_1_705_uart0_uart0_tx_no_config_rx case \r\n");
    {
        PADConfig_Type PAG_InitStru;
        memset(&PAG_InitStru,0,sizeof(PADConfig_Type));  
        
        for(uint16_t mode =0;mode<=5;mode++)
        {
            
            PAG_InitStru.pad_ctl    = mode;
            SystemPADConfig(PADID0,&PAG_InitStru);
            SystemPADConfig(PADID1,&PAG_InitStru);
            c_printf("UART0 PAD CTL %d Mode\r\n",mode);
            while(UART_GetStatus(UART0)&0x01);
            MCU_Sleep(1);
            
            PAG_InitStru.pad_ctl    = PAD_MODE1;
            SystemPADConfig(PADID1,&PAG_InitStru);
            
            while(UART_GetStatus(UART0)&0x01);
            MCU_Sleep(1);
            c_printf("UART0 only TX\r\n");
            while(UART_GetStatus(UART0)&0x01);
            MCU_Sleep(1);
            
            PAG_InitStru.pad_ctl    = mode;
            SystemPADConfig(PADID0,&PAG_InitStru);
            SystemPADConfig(PADID1,&PAG_InitStru);
            PAG_InitStru.pad_ctl    = PAD_MODE1;
            SystemPADConfig(PADID0,&PAG_InitStru);
            
            while(UART_GetStatus(UART0)&0x01);
            MCU_Sleep(1);
            c_printf("UART0 only RX\r\n");
            while(UART_GetStatus(UART0)&0x01);
            MCU_Sleep(1);
            
            PAG_InitStru.pad_ctl    = mode;
            SystemPADConfig(PADID0,&PAG_InitStru);
            SystemPADConfig(PADID1,&PAG_InitStru);       
            c_printf("UART0 completed\r\n");
            while(UART_GetStatus(UART0)&0x01);
            MCU_Sleep(1);
        }    

    }
    c_printf("s_1_705_uart0_uart0_tx_no_config_rx case completed \r\n");
	MCU_Sleep(3);
    SimulationEnd();
    while(1){     
    };
}















