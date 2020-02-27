/*
 *++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 * Copyright (c) 1999-2018 Barrot Technology Limited
 *
 * All rights reserved.
 *
 *------------------------------------------------------------------------------
 */
/**
 * @file    log_uart_config.c
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
 * @date    14. Augest 2018
 * @version V1.0.0
 * @author  MEIGER
*/

#include <stdio.h>
#include <stdarg.h>
#include "BR00x_uart.h"
#include "BR00x_clock.h"
#include "BR00x_config.h"


//#define logUart UART0
UART_TypeDef *logUart = UART0;


void  LOGUartSel(UART_TypeDef *Ux)
{
    logUart = Ux;
}

void LOGUartInit(void)
{
    UART_InitInfo_Type  UART_InitStru;
    PADConfig_Type      PAD_InitStru;
    
    memset(&PAD_InitStru, 0,sizeof(PADConfig_Type));
    memset(&UART_InitStru,0,sizeof(UART_InitInfo_Type));

    if(logUart == UART0) {
        SystemDevClockCtl(UART0_CKEn,true);
#if defined(BR005)
        SystemDevClockCtl(UART0_SCKEn,true);
#endif
    }else{
        SystemDevClockCtl(UART1_CKEn,true);
    }
    if(logUart == UART0) {
        PAD_InitStru.pad_ctl = PAD_MODE0;
        SystemPADConfig(PADID0,&PAD_InitStru);
        SystemPADConfig(PADID1,&PAD_InitStru);
        SystemPADConfig(PADID2,&PAD_InitStru);
        SystemPADConfig(PADID3,&PAD_InitStru);
    }else{
        PAD_InitStru.pad_ctl = PAD_MODE1;
        SystemPADConfig(PADID15,&PAD_InitStru);
        SystemPADConfig(PADID16,&PAD_InitStru);
        SystemPADConfig(PADID27,&PAD_InitStru);
        SystemPADConfig(PADID28,&PAD_InitStru);

    }

    UART_InitStru.UART_BaudRate             = 921600;
    UART_InitStru.UART_WordLength           = UART_WL_8BITS;
    UART_InitStru.UART_StopBits             = UART_SB_1BIT;
    UART_InitStru.UART_ParityMode           = UART_PM_NONE;
    UART_InitStru.UART_HardwareFlowControl  = UART_FC_NONE;
    UART_InitStru.UART_FIFOMode             = UART_FM_ENABLE;
    UART_InitStru.UART_DMAMode              = UART_DM_MODE_0;
    UART_InitStru.UART_TX_FIFOTriggerMode   = UART_TT_EMPTY;
    UART_InitStru.UART_RX_FIFOTriggerMode   = UART_RT_1_CHARACTER; 
    UART_Init(logUart, &UART_InitStru); 
}

int c_printf(const char *fmt, ...)
{
    static unsigned char s_tmp_buf[128];
    int r;
    va_list arglist;
    
    va_start(arglist, fmt);
    r = vsprintf((char *)s_tmp_buf, fmt, arglist);
    UART_WriteData(logUart, s_tmp_buf, r);
    va_end(arglist);
    
    return r;
}

void  SimulationEnd(void)
{
    while(!UART_LSRCheckBits(logUart,UART_LSR_BIT_THRE));
    UART_WriteByte(logUart,0x04);
}

