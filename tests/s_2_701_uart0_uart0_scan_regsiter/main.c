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

const RegisterCell UART0_RegList[]=
{
//  {read,  write,  Register ID ,register_attr, Register},
    {true,  false,  1,  0x000000FF,     (volatile uint32_t *)&UART0->RBR},//LCR[7] cleared
    {false, true,   2,  0x000000FF,     &UART0->THR},//LCR[7] cleared
    {true,  true,   3,  0x0000000F,     &UART0->IER},//LCR[7] cleared
    {true,  true,   4,  0x000000FF,     &UART0->DLL},//LCR[7] set
    {true,  true,   5,  0x000000FF,     &UART0->DLH},//LCR[7] set
    {false, true,   6,  0x000000FF,     &UART0->FCR},
    {true,  false,  7,  0x000000CF,     (volatile uint32_t *)&UART0->IIR},
    {true,  true,   8,  0x000000FF,     &UART0->LCR},
    {true,  true,   9,  0x0000007F,     &UART0->MCR},
    {true,  false,  10, 0x000000FF,     (volatile uint32_t *)&UART0->LSR},
    {true,  false,  11, 0x0000001F,     (volatile uint32_t *)&UART0->USR},
    {true,  false,  12, 0x0000000F,     (volatile uint32_t *)&UART0->TFL},
    {true,  false,  13, 0x0000000F,     (volatile uint32_t *)&UART0->RFL},
    {true,  true,   14, 0x0000000F,     &UART0->DLF},
};


int main (void)
{
    sysTimeUpdataClk(SystemCoreClock);
    Verrify_SendPinConnect(UART1_OUTPUT);
    LOGUartSel(UART1);
    LOGUartInit();
    c_printf("s_2_701_uart0_uart0_scan_regsiter case \r\n");
    {
        bool sut = true;
        uint32_t idx=0;
        
        SystemDevClockCtl(UART0_CKEn,true);
        sut =Verify_RegisterUARTHandle(UART0_RegList,sizeof(UART0_RegList),&UART0->LCR,false,idx);
        Verify_SendCResult(BRCASE_RESULT,sut);
    }
    SimulationEnd();
    while(1){     
    };
}
















