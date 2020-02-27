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
#include "BR00x_ssic.h"
#include "BR00x_ssi.h"
#include "BR00x_ssi_common.h"
#include "verify_message.h"
#include "verify_register_handle.h"
#include "log_uart_config.h"


const RegisterCell SPIM0_RegList[]=
{
//  {read,  write,  Register ID ,register_attr, Register},
    {true,  true,   1,   0x000F77DC,     &SPIM0->CTRLR0},
    {true,  true,   2,   0x000000FF,     &SPIM0->CTRLR1},
//    {true,  true,   3,   0x00000001,     &SPIM0->SSIENR},//Enable Bit Cannot set
    {true,  true,   4,   0x00000007,     &SPIM0->MWCR},//SSIC_IS_MASTER == 1 
    {true,  true,   5,   0x00000001,     &SPIM0->SER},//SSIC_NUM_SLAVES == 1
    {true,  true,   6,   0x0000FFFE,     &SPIM0->BAUDR},
    {true,  true,   7,   0x0000001F,     &SPIM0->TXFTLR},// TX_ABW=4
    {true,  true,   8,   0x0000001F,     &SPIM0->RXFTLR},// TX_ABW=4
    {true,  false,  9,   0x0000001F,     (volatile uint32_t*)&SPIM0->TXFLR}, // TX_ABW=4
    {true,  false,  10,  0x0000001F,     (volatile uint32_t*)&SPIM0->RXFLR}, // TX_ABW=4
    {true,  false,  11,  0x0000007F,     (volatile uint32_t*)&SPIM0->SR},
    {true,  true,   12,  0x0000007F,     &SPIM0->IMR},
    {true,  false,  13,  0x0000007F,     (volatile uint32_t*)&SPIM0->ISR},
    {true,  false,  14,  0x0000007F,     (volatile uint32_t*)&SPIM0->RISR},
    //Read Clear Interrupt
    {true,  false,  15,  0x00000001,     (volatile uint32_t*)&SPIM0->TXOICR},
    {true,  false,  16,  0x00000001,     (volatile uint32_t*)&SPIM0->RXOICR},
    {true,  false,  17,  0x00000001,     (volatile uint32_t*)&SPIM0->RXUICR},
    {true,  false,  18,  0x00000001,     (volatile uint32_t*)&SPIM0->MSTICR},
    {true,  false,  19,  0x00000001,     (volatile uint32_t*)&SPIM0->ICR},
    
    {true,  true,   20,  0x00000003,     (volatile uint32_t*)&SPIM0->DMACR},
    {true,  true,   21,  0x0000001F,     &SPIM0->DMATDLR}, // TX_ABW=4
    {true,  true,   22,  0x0000001F,     &SPIM0->DMARDLR}, // TX_ABW=4
    
    {true,  true,   23,  0xFFFFFFFF,     &SPIM0->DR[0]}, // TX_ABW=4
    {true,  true,   24,  0x000000FF,     &SPIM0->RX_SAMPLE_DLY},//SSIC_HAS_RX_SAMPLE_DELAY=1
    
    {true,  true,   25,  0x0000FBBF,     &SPIM0->SPI_CTRLR0},
    
    {true,  true,   26,  0x0000FFFF,     &SPIM0->XIP_INCR_INST},
    {true,  true,   27,  0x0000FFFF,     &SPIM0->XIP_WRAP_INST},
    {true,  true,   28,  0x00C7F6FF,     &SPIM0->XIP_CTRL},
    {true,  true,   29,  0x00000001,     &SPIM0->XIP_SER},
    {true,  false,  30,  0x00000001,     (volatile uint32_t*)&SPIM0->XRXOICR},
    {true,  true,   31,  0x000000FF,     &SPIM0->XIP_CNT_TIME_OUT},
};


int main (void)
{
    sysTimeUpdataClk(SystemCoreClock);
    Verrify_SendPinConnect(UART0_OUTPUT);
    LOGUartInit();
    c_printf("s_2_721_spim0_spim0_scan_regsiter case \r\n");
    {
        bool sut = true;
        uint32_t idx=0;
        
        SystemDevClockCtl(SPIM0_CKEn,true);
        SPIM0->SSIENR = DISABLE;
        SSI_ClearInterrupt(SPIM0);
        SPIM0->IMR = DISABLE;
        NVIC_ClearPendingIRQ(SPIM0_IRQn);
        
        sut =Verify_RegisterHandle(SPIM0_RegList,sizeof(SPIM0_RegList),idx);

        Verify_SendCResult(BRCASE_RESULT,sut);
    }
    SimulationEnd();
    while(1){     
    };
}
















