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

#define SetAnaReg(x,y,z)  y?(x |= 0x01ul<<z ):(x &= ~(0x01ul<<z)) 

int main (void)
{
    sysTimeUpdataClk(SystemCoreClock);
    Verrify_SendPinConnect(UART0_OUTPUT);
    LOGUartInit();
    c_printf("s_1_602_scu_set_ana_register case \r\n");

    {
        SCU->CLK_EN = 0xffffffff;
        {
            c_printf("[%X]\n",SCU->ANA_CTL0);
            c_printf("[%X]\n",SCU->ANA_CTL1);
            c_printf("[%X]\n",SCU->ANA_CTL2);
            c_printf("[%X]\n",SCU->ANA_CTL3);
            c_printf("[%X]\n",SCU->ANA_CTL4);
        }
//############ANA_CTL0############################################				
        //uint32_t ctl = 0xFFFFF800;
        uint32_t ctl = 0xFFFFFFEF;
		//bit4:CLK-26M_EN
        uint32_t setd= 0x0FFF80F0;
        
        for(uint16_t idx=0;idx<32;idx++)
        {
            if((ctl>>idx & 0x01))
            {
                if((setd>>idx & 0x01))
                {
                    c_printf("ANA_CTL0[%X],[%d]\n",idx,0);
                    SetAnaReg(SCU->ANA_CTL0,0,idx);
                    c_printf("ANA_CTL0[%X],[%d]\n",idx,1);
                    SetAnaReg(SCU->ANA_CTL0,1,idx);
                }
                else
                {
                    c_printf("ANA_CTL0[%X],[%d]\n",idx,1);
                    SetAnaReg(SCU->ANA_CTL0,1,idx);
                    c_printf("ANA_CTL0[%X],[%d]\n",idx,0);
                    SetAnaReg(SCU->ANA_CTL0,0,idx);
                }
            }
            
        }
//############ANA_CTL1############################################			
            //ctl = 0xFCC79FFF;
        ctl = 0xFFFFFFFF; 
        setd= 0x89942452;
        
        for(uint16_t idx=0;idx<32;idx++)
        {
            if((ctl>>idx & 0x01))
            {
                if((setd>>idx & 0x01))
                {
                    c_printf("ANA_CTL1[%X],[%d]\n",idx,0);
                    SetAnaReg(SCU->ANA_CTL1,0,idx);
                    c_printf("ANA_CTL1[%X],[%d]\n",idx,1);
                    SetAnaReg(SCU->ANA_CTL1,1,idx);
                }
                else
                {
                    c_printf("ANA_CTL1[%X],[%d]\n",idx,1);
                    SetAnaReg(SCU->ANA_CTL1,1,idx);
                    c_printf("ANA_CTL1[%X],[%d]\n",idx,0);
                    SetAnaReg(SCU->ANA_CTL1,0,idx);
                }
            }
            
        }
//############ANA_CTL2############################################				
        //ctl = 0xFFFFF01F;
        ctl = 0xFFFFFFFF;
        setd= 0x0F20AAA4;
        
        for(uint16_t idx=0;idx<32;idx++)
        {
            if((ctl>>idx & 0x01))
            {
                if((setd>>idx & 0x01))
                {
                    c_printf("ANA_CTL2[%X],[%d]\n",idx,0);
                    SetAnaReg(SCU->ANA_CTL2,0,idx);
                    c_printf("ANA_CTL2[%X],[%d]\n",idx,1);
                    SetAnaReg(SCU->ANA_CTL2,1,idx);
                }
                else
                {
                    c_printf("ANA_CTL2[%X],[%d]\n",idx,1);
                    SetAnaReg(SCU->ANA_CTL2,1,idx);
                    c_printf("ANA_CTL2[%X],[%d]\n",idx,0);
                    SetAnaReg(SCU->ANA_CTL2,0,idx);
                }
            }
            
        }
//############ANA_CTL3############################################				
        //ctl = 0x1FFFFFFF;
        ctl = 0xFFFFFFFF;
        setd= 0x08608238;
        
        for(uint16_t idx=0;idx<32;idx++)
        {
            if((ctl>>idx & 0x01))
            {
                if((setd>>idx & 0x01))
                {
                    c_printf("ANA_CTL3[%X],[%d]\n",idx,0);
                    SetAnaReg(SCU->ANA_CTL3,0,idx);
                    c_printf("ANA_CTL3[%X],[%d]\n",idx,1);
                    SetAnaReg(SCU->ANA_CTL3,1,idx);
                }
                else
                {
                    c_printf("ANA_CTL3[%X],[%d]\n",idx,1);
                    SetAnaReg(SCU->ANA_CTL3,1,idx);
                    c_printf("ANA_CTL3[%X],[%d]\n",idx,0);
                    SetAnaReg(SCU->ANA_CTL3,0,idx);
                }
            }
            
        }
//############ANA_CTL4############################################				
        //ctl = 0xFFFFFFF8;
        ctl = 0xFFFFFFFF;
        setd= 0x92722800;
        
        for(uint16_t idx=0;idx<32;idx++)
        {
            if((ctl>>idx & 0x01))
            {
                if((setd>>idx & 0x01))
                {
                    c_printf("ANA_CTL4[%X],[%d]\n",idx,0);
                    SetAnaReg(SCU->ANA_CTL4,0,idx);
                    c_printf("ANA_CTL4[%X],[%d]\n",idx,1);
                    SetAnaReg(SCU->ANA_CTL4,1,idx);
                }
                else
                {
                    c_printf("ANA_CTL4[%X],[%d]\n",idx,1);
                    SetAnaReg(SCU->ANA_CTL4,1,idx);
                    c_printf("ANA_CTL4[%X],[%d]\n",idx,0);
                    SetAnaReg(SCU->ANA_CTL4,0,idx);
                }
            }	
        }
        c_printf("[%X]\n",SCU->ANA_CTL0);
        c_printf("[%X]\n",SCU->ANA_CTL1);
        c_printf("[%X]\n",SCU->ANA_CTL2);
        c_printf("[%X]\n",SCU->ANA_CTL3);
        c_printf("[%X]\n",SCU->ANA_CTL4);
//
	//c_printf("ANA_CTL0[%X],[%d]\n",4,1);
	//SetAnaReg(SCU->ANA_CTL0,1,4);
	//c_printf("ANA_CTL0[%X],[%d]\n",4,0);
		//simulation stoped!
	//SetAnaReg(SCU->ANA_CTL0,0,4);
    }
	MCU_Sleep(3);
    c_printf("s_1_602_scu_set_ana_register case completed \r\n");
    SimulationEnd();
    while(1){     
    };
}
















