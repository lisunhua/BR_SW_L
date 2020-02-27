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


const RegisterCell i2SS_RegList[]=
{
//  {read,  write,  Register ID ,register_attr, Register},
//  {true,  true,   1,  0x00000001,     &I2SS->IER},//ENABLE BIT CANNOT SET
    {true,  true,   2,  0x00000001,     &I2SS->IRER},
    {true,  true,   3,  0x00000001,     &I2SS->ITER},
//    {true,  true,   4,  0x00000001,     &I2SS->CER},
//    {true,  true,   5,  0x0000001F,     &I2SS->CCR},
    
    {false, true,   6,  0x00000001,     &I2SS->RXFFR},
    {false, true,   7,  0x00000001,     &I2SS->TXFFR},
    
    //DMA REGISTER
    {true,  false,  8,  0xFFFFFFFF,     (volatile uint32_t*)&I2SS->RXDMA},
    {false, true,   9,  0x00000001,     &I2SS->RRXDMA},
    {false, true,   10, 0xFFFFFFFF,     &I2SS->TXDMA},
    {false, true,   11, 0x00000001,     &I2SS->RTXDMA},
    
    {true,  false,  12, 0xFFFFFFFF,     (volatile uint32_t*)&I2SS->I2S_Ch.LRBR},
    {false, true,   13, 0xFFFFFFFF,     &I2SS->I2S_Ch.LTHR},
    {true,  false,  14, 0xFFFFFFFF,     (volatile uint32_t*)&I2SS->I2S_Ch.RRBR},
    {false, true,   15, 0xFFFFFFFF,     &I2SS->I2S_Ch.RTHR},
    {true,  true,   16, 0x00000001,     &I2SS->I2S_Ch.RER},
    {true,  true,   17, 0x00000001,     &I2SS->I2S_Ch.TER},
    {true,  true,   18, 0x00000007,     &I2SS->I2S_Ch.RCR},
    {true,  true,   19, 0x00000007,     &I2SS->I2S_Ch.TCR},
    
    {true,  false,  20, 0x0000003F,     (volatile uint32_t*)&I2SS->I2S_Ch.ISR},
    {true,  true,   21, 0x00000033,     &I2SS->I2S_Ch.IMR},
    
    {true,  false,  22, 0x00000001,     (volatile uint32_t*)&I2SS->I2S_Ch.ROR},
    {true,  false,  23, 0x00000001,     (volatile uint32_t*)&I2SS->I2S_Ch.TOR},
    
    {true,  true,   24, 0x0000000F,     &I2SS->I2S_Ch.RFCR},
    {true,  true,   25, 0x0000000F,     &I2SS->I2S_Ch.TFCR},
    
    {false, true,   26, 0x0000000F,     &I2SS->I2S_Ch.RFF},
    {false, true,   27, 0x0000000F,     &I2SS->I2S_Ch.TFF},
};


int main (void)
{
    sysTimeUpdataClk(SystemCoreClock);
    Verrify_SendPinConnect(UART0_OUTPUT);
    LOGUartInit();
    c_printf("s_2_781_i2ss_i2ss_scan_regsiter case \r\n");
    {
        bool sut = true;
        uint32_t idx=0;
        
        SystemDevClockCtl(I2SS_CKEn,true);
        sut =Verify_RegisterHandle(i2SS_RegList,sizeof(i2SS_RegList),idx);

        Verify_SendCResult(BRCASE_RESULT,sut);
    }
    SimulationEnd();
    while(1){     
    };
}
















