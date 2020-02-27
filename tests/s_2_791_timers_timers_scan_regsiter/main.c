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


const RegisterCell Timers_RegList[]=
{
//  {read,  write,  Register ID ,register_attr, Register},
    
    //timer0
    {true,  true,   1,  0xFFFFFFFF,      &TIMERS->TIMER[0].LOAD_COUNT},
    {true,  false,  2,  0xFFFFFFFF,     (volatile uint32_t *)&TIMERS->TIMER[0].CURRENT_COUNT},
    {true,  true,   3,  0x0000000E,      &TIMERS->TIMER[0].CONTROL_REG},//enable not Cannot set
    {true,  false,  4,  0x00000001,     (volatile uint32_t *)&TIMERS->TIMER[0].EOI},
    {true,  false,  5,  0x00000001,     (volatile uint32_t *)&TIMERS->TIMER[0].INTSTATUS},
    
    //timer1
    {true,  true,   6,  0xFFFFFFFF,      &TIMERS->TIMER[1].LOAD_COUNT},
    {true,  false,  7,  0xFFFFFFFF,     (volatile uint32_t *)&TIMERS->TIMER[1].CURRENT_COUNT},
    {true,  true,   8,  0x0000000E,      &TIMERS->TIMER[1].CONTROL_REG},//enable not Cannot set
    {true,  false,  9,  0x00000001,     (volatile uint32_t *)&TIMERS->TIMER[1].EOI},
    {true,  false,  10,  0x00000001,     (volatile uint32_t *)&TIMERS->TIMER[1].INTSTATUS},
    
    //timer2
    {true,  true,   11,  0xFFFFFFFF,      &TIMERS->TIMER[2].LOAD_COUNT},
    {true,  false,  12,  0xFFFFFFFF,     (volatile uint32_t *)&TIMERS->TIMER[2].CURRENT_COUNT},
    {true,  true,   13,  0x0000000E,      &TIMERS->TIMER[2].CONTROL_REG},//enable not Cannot set
    {true,  false,  14,  0x00000001,     (volatile uint32_t *)&TIMERS->TIMER[2].EOI},
    {true,  false,  15,  0x00000001,     (volatile uint32_t *)&TIMERS->TIMER[2].INTSTATUS},
    
    //timer3
    {true,  true,   16,  0xFFFFFFFF,      &TIMERS->TIMER[3].LOAD_COUNT},
    {true,  false,  17,  0xFFFFFFFF,     (volatile uint32_t *)&TIMERS->TIMER[3].CURRENT_COUNT},
    {true,  true,   18,  0x0000000E,      &TIMERS->TIMER[3].CONTROL_REG},//enable not Cannot set
    {true,  false,  19,  0x00000001,     (volatile uint32_t *)&TIMERS->TIMER[3].EOI},
    {true,  false,  20,  0x00000001,     (volatile uint32_t *)&TIMERS->TIMER[3].INTSTATUS},
    
    //timer4
    {true,  true,   21,  0xFFFFFFFF,      &TIMERS->TIMER[4].LOAD_COUNT},
    {true,  false,  22,  0xFFFFFFFF,     (volatile uint32_t *)&TIMERS->TIMER[4].CURRENT_COUNT},
    {true,  true,   23,  0x0000000E,      &TIMERS->TIMER[4].CONTROL_REG},//enable not Cannot set
    {true,  false,  24,  0x00000001,     (volatile uint32_t *)&TIMERS->TIMER[4].EOI},
    {true,  false,  25,  0x00000001,     (volatile uint32_t *)&TIMERS->TIMER[4].INTSTATUS},
    
    //timer5
    {true,  true,   26,  0xFFFFFFFF,      &TIMERS->TIMER[5].LOAD_COUNT},
    {true,  false,  27,  0xFFFFFFFF,     (volatile uint32_t *)&TIMERS->TIMER[5].CURRENT_COUNT},
    {true,  true,   28,  0x0000000E,      &TIMERS->TIMER[5].CONTROL_REG},//enable not Cannot set
    {true,  false,  29,  0x00000001,     (volatile uint32_t *)&TIMERS->TIMER[5].EOI},
    {true,  false,  30,  0x00000001,     (volatile uint32_t *)&TIMERS->TIMER[5].INTSTATUS},
    
    //timer6
    {true,  true,   31,  0xFFFFFFFF,      &TIMERS->TIMER[6].LOAD_COUNT},
    {true,  false,  32,  0xFFFFFFFF,     (volatile uint32_t *)&TIMERS->TIMER[6].CURRENT_COUNT},
    {true,  true,   33,  0x0000000E,      &TIMERS->TIMER[6].CONTROL_REG},//enable not Cannot set
    {true,  false,  34,  0x00000001,     (volatile uint32_t *)&TIMERS->TIMER[6].EOI},
    {true,  false,  35,  0x00000001,     (volatile uint32_t *)&TIMERS->TIMER[6].INTSTATUS},
    
    //timer7
    {true,  true,   36,  0xFFFFFFFF,      &TIMERS->TIMER[7].LOAD_COUNT},
    {true,  false,  37,  0xFFFFFFFF,     (volatile uint32_t *)&TIMERS->TIMER[7].CURRENT_COUNT},
    {true,  true,   38,  0x0000000E,      &TIMERS->TIMER[7].CONTROL_REG},//enable not Cannot set
    {true,  false,  39,  0x00000001,     (volatile uint32_t *)&TIMERS->TIMER[7].EOI},
    {true,  false,  40,  0x00000001,     (volatile uint32_t *)&TIMERS->TIMER[7].INTSTATUS},
    
    {true,  false,  41,  0x00000007,     (volatile uint32_t *)&TIMERS->INT_STATUS},
    {true,  false,  42,  0x00000007,     (volatile uint32_t *)&TIMERS->EOI},
    {true,  false,  43,  0x00000007,     (volatile uint32_t *)&TIMERS->RAW_INT_STATUS},
    
    {true,  true,   44,  0xFFFFFFFF,      &TIMERS->TIMER1_LOAD_COUNT2},
    {true,  true,   45,  0xFFFFFFFF,      &TIMERS->TIMER2_LOAD_COUNT2},
    {true,  true,   46,  0xFFFFFFFF,      &TIMERS->TIMER3_LOAD_COUNT2},
    {true,  true,   47,  0xFFFFFFFF,      &TIMERS->TIMER4_LOAD_COUNT2},
    {true,  true,   48,  0xFFFFFFFF,      &TIMERS->TIMER5_LOAD_COUNT2},
    {true,  true,   49,  0xFFFFFFFF,      &TIMERS->TIMER6_LOAD_COUNT2},
    {true,  true,   50,  0xFFFFFFFF,      &TIMERS->TIMER7_LOAD_COUNT2},
    {true,  true,   51,  0xFFFFFFFF,      &TIMERS->TIMER8_LOAD_COUNT2},
   
};


int main (void)
{
    sysTimeUpdataClk(SystemCoreClock);
    Verrify_SendPinConnect(UART0_OUTPUT);
    LOGUartInit();
    c_printf("s_2_791_timers_timers_scan_regsiter case \r\n");
    {
        bool sut = true;
        uint32_t idx=0;
        SystemDevClockCtl(TIMER_CKEn,true);
        sut =Verify_RegisterHandle(Timers_RegList,sizeof(Timers_RegList),idx);
        Verify_SendCResult(BRCASE_RESULT,sut);
    }
    SimulationEnd();
    while(1){     
    };
}
















