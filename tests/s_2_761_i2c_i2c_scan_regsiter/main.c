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


const RegisterCell i2C0_RegList[]=
{
//  {read,  write,  Register ID ,register_attr, Register},
    {true,  true,   1,  0x000001FF,     &I2C0->IC_CON},
    {true,  true,   2,  0x00000FFF,     &I2C0->IC_TAR},
    {true,  true,   3,  0x000003FF,     &I2C0->IC_SAR},
    {true,  true,   4,  0x00000007,     &I2C0->IC_HS_MADDR},
    {true,  true,   5,  0x000007FF,     &I2C0->DATA_CMD},

    //Speed I2C CLOCK COUNT REGISTER
    {true,  true,   6,  0x0000FFFC,     &I2C0->IC_SS_SCL_HCNT},     //IC_ULTRA_FAST_MODE==0 NotUltra-Fase Speed
//  {true,  true,   7,  0x0000FFFC,     &I2C0->IC_UFM_SCL_HCNT},    //IC_ULTRA_FAST_MODE==0 NotUltra-Fase Speed
    {true,  true,   8,  0x0000FFF8,     &I2C0->IC_SS_SCL_LCNT},
//  {true,  true,   9,  0x0000FFF8,     &I2C0->IC_UFM_SCL_LCNT},    //IC_ULTRA_FAST_MODE==0 Not Ultra-Fase Speed
    {true,  true,   10, 0x0000FFFC,     &I2C0->IC_FS_SCL_HCNT},     //IC_MAX_SPEED_MODE =3
//  {true,  true,   11, 0x0000FFFC,     &I2C0->IC_UFM_TBUF_CNT},    //IC_ULTRA_FAST_MODE==0 Not Ultra-Fase Speed
    {true,  true,   12, 0x0000FFF8,     &I2C0->IC_FS_SCL_LCNT},
    {true,  true,   13, 0x0000FFF8,     &I2C0->IC_HS_SCL_HCNT},
    {true,  true,   14, 0x0000FFF8,     &I2C0->IC_HS_SCL_LCNT},
    
    {true,  false,  15, 0x00000FFF,     (volatile uint32_t*)&I2C0->INTR_STAT},
    {true,  true,   16, 0x00000FFF,      &I2C0->INTR_MASK},
    {true,  false,  17, 0x00000FFF,     (volatile uint32_t*)&I2C0->RAW_INTR_STAT},
    {true,  true,   18, 0x00000007,     &I2C0->RX_TL},
    {true,  true,   19, 0x00000007,     &I2C0->TX_TL},
    
    //Read Clear Interrupt register
    {true,  false,  20, 0x00000001,     (volatile uint32_t*)&I2C0->IC_CLR_INTR},
    {true,  false,  21, 0x00000001,     (volatile uint32_t*)&I2C0->IC_CLR_RX_UNDER},
    {true,  false,  22, 0x00000001,     (volatile uint32_t*)&I2C0->IC_CLR_RX_OVER},
    {true,  false,  23, 0x00000001,     (volatile uint32_t*)&I2C0->IC_CLR_TX_OVER},
    {true,  false,  24, 0x00000001,     (volatile uint32_t*)&I2C0->IC_CLR_RD_REQ},
    {true,  false,  25, 0x00000001,     (volatile uint32_t*)&I2C0->IC_CLR_TX_ABRT},
    {true,  false,  26, 0x00000001,     (volatile uint32_t*)&I2C0->IC_CLR_RX_DONE},
    {true,  false,  27, 0x00000001,     (volatile uint32_t*)&I2C0->IC_CLR_ACTIVITY},
    {true,  false,  28, 0x00000001,     (volatile uint32_t*)&I2C0->IC_CLR_STOP_DET},
    {true,  false,  29, 0x00000001,     (volatile uint32_t*)&I2C0->IC_CLR_START_DET},
    {true,  false,  30, 0x00000001,     (volatile uint32_t*)&I2C0->IC_CLR_GEN_CALL},
    
   // {true,  true,   31, 0x0000000E,     &I2C0->IC_ENABLE},// Enable (Bit0)Cannot Set
    {true,  false,  32, 0x001F0FFF,     (volatile uint32_t*)&I2C0->IC_STATUS},
    
    {true,  false,  33, 0x00000007,     (volatile uint32_t*)&I2C0->IC_TXFLR},
    {true,  false,  34, 0x00000007,     (volatile uint32_t*)&I2C0->IC_TXFLR},
    
    
    
};

int main (void)
{
    sysTimeUpdataClk(SystemCoreClock);
    Verrify_SendPinConnect(UART0_OUTPUT);
    LOGUartInit();
    c_printf("s_2_761_i2c_i2c_scan_regsiter case \r\n");
    {
        bool sut = true;
        uint32_t idx=0;
        SystemDevClockCtl(I2C_CKEn,true);
        sut =Verify_RegisterHandle(i2C0_RegList,sizeof(i2C0_RegList),idx);
        Verify_SendCResult(BRCASE_RESULT,sut);
    }
    SimulationEnd();
    while(1){     
    };
}
















