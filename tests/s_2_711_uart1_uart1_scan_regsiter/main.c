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
#include "verify_register_handle.h"
#include "log_uart_config.h"

const RegisterCell UART1_RegList[]=
{
//  {read,  write,  Register ID ,register_attr, Register},
    {true,  false,  1,  0x000000FF,     (volatile uint32_t *)&UART1->RBR},//LCR[7] cleared
    {false, true,   2,  0x000000FF,     &UART1->THR},//LCR[7] cleared
    {true,  true,   3,  0x0000000F,     &UART1->IER},//LCR[7] cleared
    {true,  true,   4,  0x000000FF,     &UART1->DLL},//LCR[7] set
    {true,  true,   5,  0x000000FF,     &UART1->DLH},//LCR[7] set
    {false, true,   6,  0x000000FF,     &UART1->FCR},
    {true,  false,  7,  0x000000CF,     (volatile uint32_t *)&UART1->IIR},
    {true,  true,   8,  0x000000FF,     &UART1->LCR},
    {true,  true,   9,  0x0000007F,     &UART1->MCR},
    {true,  false,  10, 0x000000FF,     (volatile uint32_t *)&UART1->LSR},
    {true,  false,  11, 0x0000001F,     (volatile uint32_t *)&UART1->USR},
    {true,  false,  12, 0x0000000F,     (volatile uint32_t *)&UART1->TFL},
    {true,  false,  13, 0x0000000F,     (volatile uint32_t *)&UART1->RFL},
    {true,  true,   14, 0x0000000F,     &UART1->DLF},
};


int main (void)
{
    sysTimeUpdataClk(SystemCoreClock);
    Verrify_SendPinConnect(UART0_OUTPUT);
    LOGUartInit();
    c_printf("s_2_711_uart1_uart1_scan_regsiter case \r\n");
    {
        bool sut = true;
        uint32_t idx=0;
        
        SystemDevClockCtl(UART1_CKEn,true);
        sut =Verify_RegisterUARTHandle(UART1_RegList,sizeof(UART1_RegList),&UART1->LCR,true,idx);
        Verify_SendCResult(BRCASE_RESULT,sut);
    }
    SimulationEnd();
    while(1){     
    };
}
















