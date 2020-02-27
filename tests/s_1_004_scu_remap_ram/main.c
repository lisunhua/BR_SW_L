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


#include "BR00x_uart.h"
#include "BR00x_clock.h"
#include "BR00x_ssi.h"
#include "BR00x_ssic.h"
#include "BR00x_spi_flash.h"
#include "BR00x_timers.h"
#include "BR00x_rtc.h"

#include "BR00x_rom.h"

#include "qspi_icfg.h"

int main (void)
{
    sysTimeUpdataClk(SystemCoreClock);
    Verrify_SendPinConnect(UART0_OUTPUT);
    LOGUartInit();
    c_printf("s_1_004_scu_remap_ram case \r\n");

    {
        volatile uint8_t  *addr     = (uint8_t  *)CODE_SRAM_BASE1;
        for(uint16_t i=0;i<sizeof(ram_data);i++)
        {
            *(addr +i) = ram_data[i];
        } 
        
#ifdef BR_FPGA
        for(uint32_t i=0;i<10000000;i++){};
#else
        for(uint32_t i=0;i<1000;i++){};
#endif                  
        SCU->SYS_CONFIG = 1;


    }

	MCU_Sleep(3);
    c_printf("s_1_004_scu_remap_ram case completed \r\n");
    SimulationEnd();
    while(1){     
    };
}
















