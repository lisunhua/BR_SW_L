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
#include "BR00x_ssi.h"
#include "BR00x_ssi_common.h"
#include "BR00x_config.h"
#include "verify_message.h"
#include "log_uart_config.h"


//HCLK Pre Select
uint32_t P_scu_HClkSelect(SCU_HclkSelect_Type st, uint32_t clk)
{
	clk &= ~(0x03<<3);
	clk |=  (st&0x03)<<3;
    return clk;
}

//PCLK Pre Select
uint32_t P_scu_PClkPreSelect(SCU_Pclk_Pre_Select_Type st,uint32_t clk)
{
    clk &= ~(0x0f<<10);
    clk |=  (st&0x0f)<<10;
    return clk;  
}
//96M DIV Select
uint32_t P_scu_ClockSelectDivControl(SCU_96MDIVCtl_Type st,uint32_t clk)
{   
    clk &= ~0x03;
    clk |= st&0x03;
    return clk;
}


uint32_t P_scu_PClkSelect(SCU_PclkSelect_Type st,uint32_t clk)
{
    clk &= ~(0x01<<2);
    clk |=  (st&0x01)<<2;
    return clk;
}


void  delay_ms(uint32_t clk,uint32_t timer)
{
    uint32_t cot= clk/10000;
    for(uint16_t k=0;k<timer;k++)
        for(uint32_t i = 0; i<cot;i++)
        {}
}





int main (void)
{
    uint32_t clk;
    sysTimeUpdataClk(SystemCoreClock);
    Verrify_SendPinConnect(UART0_OUTPUT);
    LOGUartInit();
    c_printf("s_1_655_scu_change_clk_fask_rw_reg case \r\n");
    {
        SCU_PClkSelect(HCLK_2_PLCK);
        MCU_Sleep(1); 
        SCU->SEND_CMD   = 0;
        SCU->SEND_DATA  = 0;
        SCU->READ_CMD   = 0;
        SCU->READ_DATA  = 0;
        MCU_Sleep(1); 
        
        clk = SCU->CLK_CTL;
        clk = P_scu_PClkPreSelect(HCLK_DIV16,clk);
        SCU->CLK_CTL = clk;
        clk = P_scu_PClkSelect(HCLK_DIV_2_PCLK,clk);
        SCU->CLK_CTL = clk;
        MCU_Sleep(1);


        for(uint32_t i=0;i<32;i++)
        {
            SCU->SEND_CMD  |= 0x01ul<<i;
            SCU->SEND_DATA |= 0x01ul<<i;
            SCU->READ_CMD  |= 0x01ul<<i;
            SCU->READ_DATA |= 0x01ul<<i;
        }
        
        
        MCU_Sleep(1);
        clk = SCU->CLK_CTL;
        clk = P_scu_PClkPreSelect(HCLK_2_PLCK_PRE,clk);
        SCU->CLK_CTL = clk; 
        MCU_Sleep(1);
    }

	MCU_Sleep(3);
    c_printf("s_1_655_scu_change_clk_fask_rw_reg case completed \r\n");
    SimulationEnd();
    while(1){     
    };
}















