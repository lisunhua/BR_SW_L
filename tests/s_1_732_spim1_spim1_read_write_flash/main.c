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


#define F_PIN_GROUP   2 



int main (void)
{
    // LOG UART INIT
    sysTimeUpdataClk(SystemCoreClock);
    Verrify_SendPinConnect(UART0_OUTPUT);

    #ifdef BR005
    Verrify_SendPinConnect(SPIM1_FLASH);
    #endif

    LOGUartInit();
    c_printf("s_1_732_spim1_spim1_read_write_flash case \r\n");
    {
        uint32_t Fid;
        SSI_InitInof_Type SSI_InitStru ;       
        PADConfig_Type PAD_InitStru;

        memset(&PAD_InitStru,0,sizeof(PADConfig_Type));
        memset(&SSI_InitStru,0,sizeof(SSI_InitInof_Type));
        
       

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
        
        for(uint8_t c = 0;c < F_PIN_GROUP; c++){ 

            if(c == 0){ 
                Verrify_SendPinConnect(SPIM1_FH_DIS);
                Verrify_SendPinConnect(SPIM1_FL_EN);
                PAD_InitStru.pad_ctl    = PAD_MODE2;
                SystemPADConfig(PADID15 ,&PAD_InitStru);
                SystemPADConfig(PADID16 ,&PAD_InitStru);
                SystemPADConfig(PADID17 ,&PAD_InitStru);
                SystemPADConfig(PADID18 ,&PAD_InitStru);

                PAD_InitStru.pad_ctl    = PAD_MODE0;
                SystemPADConfig(PADID23,&PAD_InitStru);
                SystemPADConfig(PADID24,&PAD_InitStru);
                SystemPADConfig(PADID25,&PAD_InitStru);
                SystemPADConfig(PADID26,&PAD_InitStru);
            }
            else if(c == 1){
                Verrify_SendPinConnect(SPIM1_FL_DIS);
                Verrify_SendPinConnect(SPIM1_FH_EN);
                PAD_InitStru.pad_ctl    = PAD_MODE0;
                SystemPADConfig(PADID15 ,&PAD_InitStru);
                SystemPADConfig(PADID16 ,&PAD_InitStru);
                SystemPADConfig(PADID17 ,&PAD_InitStru);
                SystemPADConfig(PADID18 ,&PAD_InitStru);

                PAD_InitStru.pad_ctl    = PAD_MODE1;
                SystemPADConfig(PADID23,&PAD_InitStru);
                SystemPADConfig(PADID24,&PAD_InitStru);
                SystemPADConfig(PADID25,&PAD_InitStru);
                SystemPADConfig(PADID26,&PAD_InitStru);
            }

            FLASH_SetSpi(SPIM1);
            Fid = FLASH_ReadManufDeviceId();
            c_printf("FLASH id:[%X]\r\n",Fid);
            {
                uint8_t data[50]={0};
                FLASH_SectorErase(0);
                FLASH_ReadData(0,data,50);

                for(uint16_t i=0;i<50;i++)
                {
                    if(data[i] !=0xff){
                        c_printf("FLASH Erase false\r\n");
                        break;
                    }
                }

                for(uint16_t i=0;i<50;i++)
                    data[i] = i;

                FLASH_PageProgram(0,data,50);
                FLASH_WaitBusy();

                {
                    uint8_t date[50]={0};

                    memset(date,0,sizeof(date));
                    FLASH_ReadData(0,date,50);
                    FLASH_WaitBusy();
                    c_printf("Read:");
                    for(uint16_t i=0;i<sizeof(date);i++)
                    {
                        c_printf("%x,",date[i]);
                    }
                    c_printf("\n");
                }

                MCU_Sleep(3);
            }
                
        }
     
        
    }
    c_printf("s_1_732_spim1_spim1_read_write_flash case completed \r\n");
	MCU_Sleep(3);
    SimulationEnd();
    while(1){     
    };
}















