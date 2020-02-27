/*
 *++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 * Copyright (c) 1999-2018 Barrot Technology Limited
 *
 * All rights reserved.
 *
 *------------------------------------------------------------------------------
 */
/**
 * @file    cm_printf.c
 * @brief   This file provides all the STDOUT functions.
 * @attention
 *
 * THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
 * WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE
 * TIME. AS A RESULT, STMICROELECTRONICS SHALL NOT BE HELD LIABLE FOR ANY
 * DIRECT, INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING
 * FROM THE CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE
 * CODING INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
 *
 * @date    11-Augest-2018
 * @version V1.0.0
 * @author  Asher
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include "BR00x_uart.h"

//#pragma import(__use_no_semihosting)    

//struct __FILE { 
//    int handle; 
//}; 

//FILE __stdout;   

//int _sys_exit(int x) 
//{ 
//    return x;
//}

//int fputc(int ch, FILE* stream)
//{
//    uint8_t dat = ch;
//    UART_WriteData(UART0, &dat,1);
//    return ch;
//}


int cm_printf(const char *fmt, ...)
{
    static unsigned char s_tmp_buf[128];
    int r;
    va_list arglist;
    
    va_start(arglist, fmt);
    r = vsprintf((char *)s_tmp_buf, fmt, arglist);
    UART_WriteData(UART0, s_tmp_buf, r);
    va_end(arglist);
    
    return r;
}

int at_eventInd(const char *fmt, ...)
{
    static unsigned char s_dbg_tmp_buf[128];
    int r;
    va_list arglist;
    va_start(arglist, fmt);
    r = vsprintf((char *)s_dbg_tmp_buf, fmt, arglist);
    UART_WriteData(UART0, s_dbg_tmp_buf, r);
    va_end(arglist);
    return r;
}

int cm_printf_Uart1(const char *fmt, ...)
{
    static unsigned char s_dbg_tmp_buf[128];
    int r;
    va_list arglist;
    va_start(arglist, fmt);
    r = vsprintf((char *)s_dbg_tmp_buf, fmt, arglist);
    UART_WriteData(UART1, s_dbg_tmp_buf, r);
    va_end(arglist);
    return r;
}




