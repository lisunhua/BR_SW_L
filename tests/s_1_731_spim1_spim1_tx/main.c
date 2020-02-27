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
#include "BR00x_spi_flash.h"
#include "verify_message.h"
#include "log_uart_config.h"

int main (void)
{
    // LOG UART INIT
    sysTimeUpdataClk(SystemCoreClock);
    Verrify_SendPinConnect(UART0_OUTPUT);
    LOGUartInit();
    c_printf("s_1_731_spim1_spim1_tx case \r\n");
    {
        SSI_InitInof_Type SSI_InitStru ;       
        PADConfig_Type PAG_InitStru;
        memset(&PAG_InitStru,0,sizeof(PADConfig_Type));

        memset(&SSI_InitStru,0,sizeof(SSI_InitInof_Type));
        
        PAG_InitStru.pad_ctl    = PAD_MODE1;
        
        SystemPADConfig(PADID19,&PAG_InitStru);
        SystemPADConfig(PADID20,&PAG_InitStru);
        SystemPADConfig(PADID21,&PAG_InitStru);
        SystemPADConfig(PADID22,&PAG_InitStru);

        SystemDevClockCtl(SPIM1_CKEn,true);
        #ifdef BR005
        SystemDevClockCtl(SPIM1_SCKEn,true);
        #endif
        
        SSI_InitStru.clock_divider          = 0x10;
        SSI_InitStru.SSI_frame_format       = SSI_FRAME_FORMAT_MOTOROLA_SPI;
        SSI_InitStru.clock_phase            = SSI_CLOCK_TOGGLES_MIDDLE;
        SSI_InitStru.clock_polarity         = SSI_INACTIVE_STATE_LOW;
        SSI_InitStru.transfer_mode          = SSI_TRANSMIT_AND_RECEIVE;
        SSI_InitStru.slave_output_enable    = SSI_SLAVE_TXD_IS_DISABLE;
        SSI_InitStru.operation_mode         = SSI_NORMAL_MODE;

        SSI_InitStru.control_farme_size     = SSI_CONTROL_FRAME_8BIT_WORD;
        SSI_InitStru.frame_format_size_16   = SSI_DATA_FRAME_SIZE_8BIT;
        SSI_InitStru.spi_frame_format       = STANDARD_SPI_FORMAT;

        SSI_InitStru.data_frame_num         = 6;
        SSI_InitStru.unmask_interrupt       = RX_FIFO_FULL_UNMASK;

        
        SSI_Init(SPIM1 ,&SSI_InitStru);
        {
            uint8_t data[8] = {0x69,0x55,0x23,0x89,0x67,0x54};
            SSI_SendData(SPIM1,&data[0],6);
            c_printf("ssi send data: ");
            for (uint16_t i=0;i<6;i++)
            {
                c_printf("%X ,",data[i]);
            }
            c_printf("\r\n");     
        }    
    }
    c_printf("s_1_731_spim1_spim1_tx case completed \r\n");
	MCU_Sleep(3);
    SimulationEnd();
    while(1){     
    };
}















