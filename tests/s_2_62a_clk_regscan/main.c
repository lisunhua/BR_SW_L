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



bool SystemDevClockGet(CKEnId_Type id)
{
		uint32_t reg = SCU->CLK_EN;
		if(reg &= (0x01ul << id))
			return true;
		else
			return false;      
}


uint8_t clock_str[][20]={"SCU_CKEn",\
                         "GPIO_CKEn",\
                         "WDT_CKEn",\
                         "RTC_CKEn",\
                         "UART0_CKEn",\
                         "UART1_CKEn",\
                         "SPIM1_CKEn",\
                         "SPIS1_CKEn",\
                         "I2SM_CKEn",\
                         "I2SS_CKEn",\
                         "TIMER_CKEn",\
                         "I2C_CKEn",\
                         "QDEC_CKEn",\
                         "RF_CKEn",\
                         "BB_CKEn",\
                         "DMA_CKEn",\
                         "SPIM0_CKEn",\
                         "CPU_TRACE_CKEn",\
                         "USB_CKEn"};       


int main (void)
{
    uint32_t pin =0;
    bool sut = true;
    sysTimeUpdataClk(SystemCoreClock);
    Verrify_SendPinConnect(UART0_OUTPUT);
    LOGUartInit();
    c_printf("s_2_62a_clk_regscan case \r\n");
    {
        uint32_t Mask   = 0xffffffff;
        SCU->CLK_EN     = 0xffffffff;
        for(CKEnId_Type clk = (CKEnId_Type)0; clk < (CKEnId_Type)32; clk++)
        {
            if(!(Mask>>clk&0x01))
                //break;
                continue;

            SystemDevClockCtl(clk,false);
            c_printf("clock[%d]=[%d]\n",clk,SystemDevClockGet(clk));
            sut = Verify_SendAppStep(BRCASE_STOP1+pin,1);pin++; // open interaction 
             if(!sut)
                 break;                                         // open interaction   
            for(uint32_t i=0;i<1000;i++){};
            SystemDevClockCtl(clk,true);

            c_printf("clock[%d]=[%d]\n",clk,SystemDevClockGet(clk));
            sut = Verify_SendAppStep(BRCASE_STOP1+pin,1);pin++;// open interaction       
             if(!sut)                                          // open interaction   
                 break;                                        // open interaction 
            for(uint32_t i=0;i<1000;i++){};
        }
        c_printf("SCU clock complete\n"); //
        Verify_SendCResult(BRCASE_RESULT,sut);
    }

	MCU_Sleep(3);
    c_printf("s_2_62a_clk_regscan case completed \r\n");
    SimulationEnd();
    while(1){     
    };
}















