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

//{"SCU_CKEn","GPIO_CKEn","WDT_CKEn","RTC_CKEn","UART0_CKEn","UART1_CKEn","SPIM1_CKEn",\
"SPIS1_CKEn","I2SM_CKEn","I2SS_CKEn","TIMER_CKEn","I2C_CKEn","QDEC_CKEn","RF_CKEn","BB_CKEn","DMA_CKEn",\
"SPIM0_CKEn","CPU_TRACE_CKEn","USB_CKEn"};   
typedef struct clock_test_data
{
    bool   flg;
    uint8_t name[20];
    
}clock_testdb;

clock_testdb clock_str[]=    
{
   true,  "SCU_CKEn",
   true,  "GPIO_CKEn",
   true,  "WDT_CKEn",
   true,  "RTC_CKEn",
   true,  "UART0_CKEn ",
   true,  "UART1_CKEn",
   true,  "SPIM1_CKEn ",
   true,  "SPIM1_SCKEn",
   true,  "UART0_SCKEn",
   false,  "09",
   false,  "10",
   true,  "I2C_CKEn",
   true,  "12",
   true,  "RF_CKEn",        
   true,  "BB_PCKEn",         
   true,  "BB_HCKEn ",
   false,  "16",
   false,  "17",     
   true,  "CPU_TRACE_CKEn ",
   false,  "19",
   false,  "20",
   false,  "21",    
   false,  "22",
   false,  "23",
   false,  "24",
   false,  "25",
   false,  "26",
   false,  "27", 
   false,  "28", 
   true,  "IFCLK_BB_CKEn",   
   true,  "IFCLK_GPIO_CKEn "
};

int main (void)
{
    sysTimeUpdataClk(SystemCoreClock);
    Verrify_SendPinConnect(UART0_OUTPUT);
    LOGUartInit();
    c_printf("s_1_62a_scu_clock_switch_all_ip case \r\n");
    {
        SCU->CLK_EN = 0xffffffff;
        for(CKEnId_Type clk = (CKEnId_Type)0; clk < (CKEnId_Type)32; clk++)
        {
            if(!clock_str[clk].flg)
                continue;

            SystemDevClockCtl(clk,false);

            if (clk != 8)
                c_printf("clock[%s]=[%d]\n",clock_str[clk].name,SystemDevClockGet(clk));
            //sut = Verify_SendAppStep(BRCASE_STOP1+pin,1);pin++;
            // if(!sut)
            //     break;
            for(uint32_t i=0;i<1000;i++){};
            SystemDevClockCtl(clk,true);

            c_printf("clock[%s]=[%d]\n",clock_str[clk].name,SystemDevClockGet(clk));
            //sut = Verify_SendAppStep(BRCASE_STOP1+pin,1);pin++;
            // if(!sut)
            //     break;
            for(uint32_t i=0;i<1000;i++){};
        }
        c_printf("SCU clock complete\n");
    }

	MCU_Sleep(3);
    c_printf("s_1_62a_scu_clock_switch_all_ip case completed \r\n");
    SimulationEnd();
    while(1){     
    };
}















