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

#include <stdarg.h>
#include <stdio.h>
#include "BR00x_uart.h"
#include "BR00x_clock.h"
#include "BR00x_config.h"
#include "verify_message.h"
#include "log_uart_config.h"

void  UART1_Init()
{
    UART_InitInfo_Type UART_InitStru; 
    PADConfig_Type PAD_Config;

    //ENABLE CLOCK
    SystemDevClockCtl(UART1_CKEn,true);
    memset(&UART_InitStru,0,sizeof(UART_InitInfo_Type));
    memset(&PAD_Config,0,sizeof(PADConfig_Type));
    
    UART_InitStru.UART_BaudRate             = 921600;
    UART_InitStru.UART_WordLength           = UART_WL_8BITS;
    UART_InitStru.UART_StopBits             = UART_SB_1BIT;
    UART_InitStru.UART_ParityMode           = UART_PM_NONE;
    UART_InitStru.UART_HardwareFlowControl  = UART_FC_NONE;
    UART_InitStru.UART_FIFOMode             = UART_FM_ENABLE;
    UART_InitStru.UART_DMAMode              = UART_DM_MODE_0;
    UART_InitStru.UART_TX_FIFOTriggerMode   = UART_TT_EMPTY;
    UART_InitStru.UART_RX_FIFOTriggerMode   = UART_RT_1_CHARACTER;

    PAD_Config.set                          = 0;
    PAD_Config.pad_ctl                      = PAD_MODE1; 
    //CONFIG IOMUX
    
#ifdef BR005 
    SystemPADConfig(PADID10,&PAD_Config);
#endif

#ifdef BR003 
    SystemPADConfig(PADID15,&PAD_Config);
#endif

    //SystemPADConfig(PADID11,&PAD_Config);
    //INIT UART1      
    UART_Init(UART1, &UART_InitStru); 

}


int u1_printf(const char *fmt, ...)
{
    static unsigned char s_tmp_buf[128];
    int r;
    va_list arglist;
    
    va_start(arglist, fmt);
    r = vsprintf((char *)s_tmp_buf, fmt, arglist);
    UART_WriteData(UART1, s_tmp_buf, r);
    va_end(arglist);
    
    return r;
}


void  u1SimulationEnd(void)
{
    while(!UART_LSRCheckBits(UART1,UART_LSR_BIT_THRE));
    UART_WriteByte(UART1,0x04);
}



int main (void)
{
    // LOG UART INIT
    sysTimeUpdataClk(SystemCoreClock);
    Verrify_SendPinConnect(UART1_OUTPUT);
    UART1_Init();
    u1_printf("Hello Word! \r\n"); 
	MCU_Sleep(3);
    u1SimulationEnd();

    while(1){     
    };
}
















