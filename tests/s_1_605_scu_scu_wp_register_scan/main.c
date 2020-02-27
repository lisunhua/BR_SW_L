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
    c_printf("s_1_605_scu_scu_wp_register_scan case \r\n");
    c_printf("SCU SCU WP Reg Scan\n");
    {
        uint32_t ctl = 0xFFFFFFFF;
        SCU->BB_WAKEUP_MASK_L = 0;
        c_printf("SCU BB_WAKEUP_MASK_L\n");
        for(uint16_t idx=0;idx<32;idx++)
        {
            if((ctl>>idx & 0x01))
            {
                SetAnaReg(SCU->BB_WAKEUP_MASK_L,1,idx);
                SetAnaReg(SCU->BB_WAKEUP_MASK_L,0,idx);
            }	
        }
        SCU->BB_WAKEUP_MASK_H = 0;
        c_printf("SCU BB_WAKEUP_MASK_H\n");
        for(uint16_t idx=0;idx<32;idx++)
        {
            if((ctl>>idx & 0x01))
            {
                SetAnaReg(SCU->BB_WAKEUP_MASK_H,1,idx);
                SetAnaReg(SCU->BB_WAKEUP_MASK_H,0,idx);
            }	
        }
        c_printf("SCU BB_WAKEUP_MASK_SEL\n");
        for(uint16_t idx=0;idx<32;idx++)
        {
            if((ctl>>idx & 0x01))
            {
                SetAnaReg(SCU->BB_WAKEUP_MASK_SEL,1,idx);
                SetAnaReg(SCU->BB_WAKEUP_MASK_SEL,0,idx);
            }	
        }
        c_printf("SCU IO CONMFIG\n");
        for(uint16_t idx=0;idx<32;idx++)
        {
            if((ctl>>idx & 0x01))
            {
                SetAnaReg(SCU->IO_CONFIG,1,idx);
                SetAnaReg(SCU->IO_CONFIG,0,idx);
            }	
        }
        c_printf("SCU SYS_CONFIG\n");
        for(uint16_t idx=4;idx<32;idx++)
        {
            if((ctl>>idx & 0x01))
            {
                SetAnaReg(SCU->SYS_CONFIG,1,idx);
                SetAnaReg(SCU->SYS_CONFIG,0,idx);
            }	
        }        
       
        c_printf("SCU BB Reg\n");
        memset((void *)&BB->BB_CTL,0,sizeof(BB->BB_CTL));
        MCU_Sleep(2);
        memset((void *)&BB->BB_CTL,0xFFFFFFFF,sizeof(BB->BB_CTL));
        MCU_Sleep(2);
        memset((void *)&BB->BB_CTL,0,sizeof(BB->BB_CTL));
        
        //MCU_Sleep(2);
        //c_printf("SCU SYS RST\n");
        //SCU->SW_RST =0xFFFFFFFF;   
    }

	MCU_Sleep(3);
    c_printf("s_1_605_scu_scu_wp_register_scan case completed \r\n");
    SimulationEnd();
    while(1){     
    };
}
















