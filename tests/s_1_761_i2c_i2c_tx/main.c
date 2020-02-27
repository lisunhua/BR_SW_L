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
#include "BR00x_i2c.h"
#include "BR00x_i2c_erom.h"
#include "BR00x_config.h"
#include "verify_message.h"
#include "log_uart_config.h"


int main (void)
{
    // LOG UART INIT
    sysTimeUpdataClk(SystemCoreClock);
    Verrify_SendPinConnect(UART0_OUTPUT);
    LOGUartInit();
    c_printf("s_1_761_i2c_i2c_tx case \r\n");
    {
        I2C_InitInof_Type   I2C_InitStru;
        PADConfig_Type      PAG_InitStru;

        memset(&PAG_InitStru,0,sizeof(PADConfig_Type));

        PAG_InitStru.ie         = PAD_IE_ENABLE;
        PAG_InitStru.oen        = PAD_OEN_ENABLE;
        PAG_InitStru.ren        = PAD_REN_ENABLE;
        PAG_InitStru.pad_ctl    = PAD_MODE1;
        
        SystemPADConfig(PADID17,&PAG_InitStru);
        SystemPADConfig(PADID18,&PAG_InitStru);

        // PAG_InitStru.pad_ctl    = PAD_MODE3;
        // SystemPADConfig(PADID4,&PAG_InitStru);
        // SystemPADConfig(PADID5,&PAG_InitStru);
        // SystemPADConfig(PADID27,&PAG_InitStru);
        // SystemPADConfig(PADID28,&PAG_InitStru);
        
        I2C_InitStru.master_en                  = MASTER_MODE_ENABLE;
        I2C_InitStru.slave_en                   = SLAVE_MODE_DISABLE;
        I2C_InitStru.restart_en                 = MASTER_RESTART_DISABLE;
        I2C_InitStru.slave_addr_type            = SLAVE_7BIT_ADDR;
        I2C_InitStru.master_addr_type           = MASTER_7BIT_ADDR;

        I2C_InitStru.max_speed                  = PARAM_MAX_SPEED_STANDARD;

        I2C_InitStru.slave_stop_det_if_addressed_en = SLAVE_STOP_DET_IFADDRESSED_DISABLE;
        I2C_InitStru.master_stop_det_if_addressed_en = MASTER_STOP_DET_IFACTIVE_DISABLE; 
        I2C_InitStru.tx_empty_intr_en           = TX_EMPTY_INTERRUPT_DISABLE;
        I2C_InitStru.rx_fifo_full_hold_control_en = RX_FIFO_FULL_HOLD_DISABLE;
        I2C_InitStru.master_bus_clear_feature_en = MASTER_BUS_CLEAR_FEATURE_DISABLE;
        I2C_InitStru.optional_SAR_address_en    = OPTIONAL_SAR_ADDRESS_DISABLE;

        I2C_InitStru.SMBUS_slave_quick_en       = SMBUS_SLAVE_QUICK_DISABLE;
        I2C_InitStru.SMBUS_ARP_contral_en       = SMBUS_ARP_CONTRAL_DISABLE;
        I2C_InitStru.SMBUS_persistent_slave_addr_en = SMBUS_PERSISTENT_SLV_ADDR_DISABLE;


        I2C_InitStru.I2C_target_address         = 0x50;
        I2C_InitStru.slc_h  = 500;
        I2C_InitStru.slc_l  = 500;
        
        I2C_InitStru.targer_address_type        = MASTER_7BIT_ADDR;
        I2C_InitStru.general_call_or_start_byte = GENERAL_CALL;
        I2C_InitStru.general_call_or_start_byte_en = GENERAL_CALL_OR_START_BYTE_DISABLE;

        I2C_InitStru.programming_device_id_en   = PROGRAMMING_DEVICE_ID_DISABLE;
        I2C_InitStru.programming_SMBUS_quick_cmd_en = PROGRAMMING_SMBUS_QUICK_CMD_DISABLE;


        I2C_InitStru.salve_address              = 0x2a;
        I2C_InitStru.interrupt_unmask           =  0x78e1;

        I2C_InitStru.fifo_receive_threshold_level =  6;
        I2C_InitStru.fifo_transmit_threshold_level = 6;

        I2C_InitStru.dma_rx_en                  = false;
        I2C_InitStru.dma_tx_en                  = false;
        I2C_InitStru.dma_tx_data_level          =  2; 
        I2C_InitStru.dma_rx_data_level          =  2;


        #if  defined(BR002)||defined(BR003) ||defined(BR005) 
        SystemDevClockCtl(I2C_CKEn,true);
        #endif

        I2C_Init(I2C0,&I2C_InitStru);

        //NVIC_EnableIRQ(I2C0_IRQn);
        {
            #define MaxLendata  5
            static  uint8_t data_se[MaxLendata]= {0};
            static  uint8_t data_buff[MaxLendata]={0};
            
            EEPROM_WritePage (0,data_se,MaxLendata);
            MCU_Sleep(3);
            EEPROM_SequentialRead(0,data_buff,MaxLendata);

            c_printf("eeprom Read : ");
            for(uint16_t i=0;i<MaxLendata;i++)
                c_printf("%X,",data_buff[i]);
            c_printf("\r\n");
            

            for(uint16_t i=0;i<MaxLendata;i++)
                data_se[i] = i;

            EEPROM_WritePage (0,data_se,MaxLendata);
            
            c_printf("eeprom Write:");
            for(uint16_t i=0;i<MaxLendata;i++)
                c_printf("%X,",data_se[i]);
            c_printf("\r\n");
            
            for(uint32_t i=0;i<50000;i++);
            
            EEPROM_SequentialRead(0,data_buff,MaxLendata);

            c_printf("eeprom Read : ");
            for(uint16_t i=0;i<MaxLendata;i++)
            {
                c_printf("%X,",data_buff[i]);
            }
            c_printf("\r\n");
            c_printf("test i2c complete \r\n ");

        }

    }
	MCU_Sleep(3);
    c_printf("s_1_761_i2c_i2c_tx case completed \r\n");
    SimulationEnd();
    while(1){     
    };
}
















