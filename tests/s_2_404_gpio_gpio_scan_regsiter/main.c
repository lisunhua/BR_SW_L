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

const RegisterCell GPIO_RegList[]=
{
//  {read,  write,  Register ID ,register_attr, Register},
    {true,  true,   1,  0x000FFFFF,     &GPIO->DR0},
    {true,  true,   2,  0x000FFFFF,     &GPIO->DDR0},
    {true,  true,   3,  0x000FFFFF,     &GPIO->IE},
    {true,  true,   4,  0x000FFFFF,     &GPIO->IM},
    {true,  true,   5,  0x000FFFFF,     &GPIO->ITL},
    {true,  true,   6,  0x000FFFFF,     &GPIO->IP},
    {true,  false,  7,  0x000FFFFF,     (volatile uint32_t *)&GPIO->IS},
    {true,  false,  8,  0x000FFFFF,     (volatile uint32_t *)&GPIO->RIS},
    {true,  true,   9,  0x000FFFFF,     &GPIO->DB},
    {true,  false,  10, 0x000FFFFF,     (volatile uint32_t *)&GPIO->EXTDR0},
    {false, true,   11, 0x000FFFFF,     &GPIO->EOI},
};


int main (void)
{
    sysTimeUpdataClk(SystemCoreClock);
    Verrify_SendPinConnect(UART0_OUTPUT);
    LOGUartInit();
    c_printf("s_2_404_gpio_gpio_scan_regsiter case \r\n");
    {
        bool sut = true;
        uint32_t idx=0;
        
        SystemDevClockCtl(GPIO_CKEn,true);
        sut =Verify_RegisterHandle(GPIO_RegList,sizeof(GPIO_RegList),idx);
        Verify_SendCResult(BRCASE_RESULT,sut);
    }
    SimulationEnd();
    while(1){     
    };
}
















