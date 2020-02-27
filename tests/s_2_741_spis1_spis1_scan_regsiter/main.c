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


const RegisterCell SPIS1_RegList[]=
{
//  {read,  write,  Register ID ,register_attr, Register},
    {true,  true,   1,   0x0000F7FC,     &SPIS1->CTRLR0},
//    {true,  true,   2,   0x000000FF,     &SPIS1->CTRLR1},
//    {true,  true,   3,   0x00000001,     &SPIS1->SSIENR},//Enable Bit Cannot set
//    {true,  true,   4,   0x00000007,     &SPIS1->MWCR},//SSIC_IS_MASTER == 0 
//    {true,  true,   5,   0x00000001,     &SPIS1->SER},//SSIC_NUM_SLAVES == 1
//    {true,  true,   6,   0x0000FFFF,     &SPIS1->BAUDR},
    {true,  true,   7,   0x00000007,     &SPIS1->TXFTLR},// TX_ABW=2
    {true,  true,   8,   0x00000007,     &SPIS1->RXFTLR},// TX_ABW=2
    {true,  false,  9,   0x00000007,     (volatile uint32_t*)&SPIS1->TXFLR}, // TX_ABW=2
    {true,  false,  10,  0x00000007,     (volatile uint32_t*)&SPIS1->RXFLR}, // TX_ABW=2
    {true,  false,  11,  0x00000007,     (volatile uint32_t*)&SPIS1->SR},
    {true,  true,   12,  0x0000001F,     &SPIS1->IMR},
    {true,  false,  13,  0x0000001F,     (volatile uint32_t*)&SPIS1->ISR},
    {true,  false,  14,  0x0000001F,     (volatile uint32_t*)&SPIS1->RISR},
    //Read Clear Interrupt
    {true,  false,  15,  0x00000001,     (volatile uint32_t*)&SPIS1->TXOICR},
    {true,  false,  16,  0x00000001,     (volatile uint32_t*)&SPIS1->RXOICR},
    {true,  false,  17,  0x00000001,     (volatile uint32_t*)&SPIS1->RXUICR},
    {true,  false,  18,  0x00000001,     (volatile uint32_t*)&SPIS1->MSTICR},
    {true,  false,  19,  0x00000001,     (volatile uint32_t*)&SPIS1->ICR},
    
    {true,  true,   20,  0x00000003,     (volatile uint32_t*)&SPIS1->DMACR},
    {true,  true,   21,  0x00000007,     &SPIS1->DMATDLR}, // TX_ABW=2
    {true,  true,   22,  0x00000007,     &SPIS1->DMARDLR}, // TX_ABW=2
    
    {true,  true,   23,  0xFFFFFFFF,     &SPIS1->DR[0]}, // TX_ABW=2
   
};




int main (void)
{
    sysTimeUpdataClk(SystemCoreClock);
    Verrify_SendPinConnect(UART0_OUTPUT);
    LOGUartInit();
    c_printf("s_2_741_spis1_spis1_scan_regsiter case \r\n");
    {
        bool sut = true;
        uint32_t idx=0;
        
        SystemDevClockCtl(SPIS1_CKEn,true);
        SPIS1->SSIENR = DISABLE;
        sut =Verify_RegisterHandle(SPIS1_RegList,sizeof(SPIS1_RegList),idx);
        Verify_SendCResult(BRCASE_RESULT,sut);
    }
    SimulationEnd();
    while(1){     
    };
}
















