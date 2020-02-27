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
#include "log_uart_config.h"


int main (void)
{
    bool sut = true;
    sysTimeUpdataClk(SystemCoreClock);
    Verrify_SendPinConnect(UART0_OUTPUT);
    LOGUartInit();
    c_printf("s_1_62b_scu_change_clock case \r\n");

    {
        SCU->CLK_EN = 0xffffffff;
         /***SCU_ClockSelectDivControl**********************************/
        if(sut)
            for(SCU_96MDIVCtl_Type clk = CLK_12M ;clk<=CLK_96M;clk++)
            {
                SCU_ClockSelectDivControl(clk);
                c_printf("SCU_ClockSelectDivControl=[%d]\n",clk);
                // sut = Verify_SendAppStep(BRCASE_STOP1+step,SCU->CLK_CTL);step++;
                // if(!sut)
                //     break;
            }
        SCU_ClockSelectDivControl(CLK_12M);
        /***SCU_SPIM0ClkSelect**********************************/
        // if(sut)
        //     for(SCU_SPIM0Select_Type clk = CLK_HCLK_MAIN ;clk<=CLK_SPIM0_104M;clk++)
        //     {
        //         SCU_SPIM0ClkSelect(clk);
        //         c_printf("SCU_SPIM0ClkSelect=[%d]\n",clk);
        //         // sut = Verify_SendAppStep(BRCASE_STOP1+step,SCU->CLK_CTL);step++;
        //         // if(!sut)
        //         //     break;
        //     }
        // SCU_SPIM0ClkSelect(CLK_HCLK_MAIN);
        /***SCU_32KClkSelect**********************************/
        if(sut)
            for(SCU_32KSelect_Type clk = CLK_RCO_32K ;clk<=clk_DIV_32K;clk++)
            {
                SCU_32KClkSelect(clk);
                c_printf("SCU_32KClkSelect=[%d]\n",clk);
                // sut = Verify_SendAppStep(BRCASE_STOP1+step,SCU->CLK_CTL);step++;
                // if(!sut)
                //     break;
            }
        SCU_32KClkSelect(CLK_RCO_32K);

        /***SCU_USBClkSelect**********************************/
        if(sut)
            for(SCU_USBSelect_Type clk = CLK_RCO_48M ;clk<=CLK_DIV_48M;clk++)
            {
                SCU_USBClkSelect(clk);
                c_printf("Div 13M_control=[%d]\n",clk);
                // sut = Verify_SendAppStep(BRCASE_STOP1+step,SCU->CLK_CTL);step++;
                // if(!sut)
                //     break;
            }
        SCU_USBClkSelect(CLK_RCO_48M); 

        /***SCU_HCLK_ClkSelect**********************************/
        if(sut)
            for(SCU_HclkSelect_Type hclk = CLK_OSC26m; hclk<=CLK_32K_MUX_HCLK; hclk++)
            {
                SCU_HClkSelect(hclk);
                for(uint16_t i=0;i<10;i++){};
                // sut = Verify_SendAppStep(BRCASE_STOP1+step,SCU->CLK_CTL);step++;

            }  
        SCU_HClkSelect(CLK_OSC26m);
        /*******************************************************/ 
        if(sut)
        {
            SCU_UART0ClkSelect(CLK_OSC_26M);
            MCU_Sleep(1);
        }
        SCU_UART0ClkSelect(CLK_PCLK);
        /*******************************************************/
        if(sut)
        {
            SCU_BB_MEM_ADC_ClkSelect(1);
            MCU_Sleep(1);
        }
        SCU_BB_MEM_ADC_ClkSelect(0);
        /*******************************************************/
        if(sut)
            for(uint32_t clk = 0; clk<=3; clk++)
            {
                SCU_RF_ADC_ClkSelect(clk);
                MCU_Sleep(1);

            }
        


    }

	MCU_Sleep(3);
    c_printf("s_1_62b_scu_change_clock case completed \r\n");
    SimulationEnd();
    while(1){     
    };
}















