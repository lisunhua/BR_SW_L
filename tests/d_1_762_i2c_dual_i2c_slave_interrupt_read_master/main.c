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
#include "BR00x_config.h"
#include "verify_message.h"
#include "log_uart_config.h"

int main (void)
{
    bool sut = true;
    LOGUartInit();
    sysTimeUpdataClk(SystemCoreClock);
    Verrify_SendPinConnect(UART0_OUTPUT);
    VerifyDualGetRoleHandler();
    c_printf("d_1_762_i2c_dual_i2c_slave_interrupt_read_master case \r\n");
    MCU_Sleep(1);
    Verrify_SendPinConnect(DUAL_I2C_PIN_EN);

    {
#if defined(BR_MASTER) || defined(BR_SLAVE)
        I2C_InitInof_Type   I2C_InitStru;
        PADConfig_Type      PAG_InitStru;

        memset(&PAG_InitStru,0,sizeof(PADConfig_Type));
        PAG_InitStru.ren        = PAD_REN_ENABLE;
        PAG_InitStru.pad_ctl    = PAD_MODE1;
        
        SystemPADConfig(PADID17,&PAG_InitStru);
        SystemPADConfig(PADID18,&PAG_InitStru);
        SystemDevClockCtl(I2C_CKEn,true);
        
#ifdef BR_MASTER
#ifdef BR_DUAL
        if(GetSocRole())
#endif
        {
            I2C_InitStru.master_en          = MASTER_MODE_ENABLE;
            I2C_InitStru.slave_en           = SLAVE_MODE_DISABLE;
        }
#endif
    
#ifdef BR_SLAVE
#ifdef BR_DUAL
        if(!GetSocRole())
#endif
        {
            I2C_InitStru.master_en          = MASTER_MODE_DISABLE;
            I2C_InitStru.slave_en           = SLAVE_MODE_ENABLE;
        }
#endif
        
        I2C_InitStru.restart_en         = MASTER_RESTART_DISABLE;
        I2C_InitStru.slave_addr_type    = SLAVE_7BIT_ADDR;
        I2C_InitStru.master_addr_type   = MASTER_7BIT_ADDR;

        I2C_InitStru.max_speed          = PARAM_MAX_SPEED_STANDARD;

        I2C_InitStru.slave_stop_det_if_addressed_en         = SLAVE_STOP_DET_IFADDRESSED_DISABLE;
        I2C_InitStru.master_stop_det_if_addressed_en        = MASTER_STOP_DET_IFACTIVE_DISABLE; 
        I2C_InitStru.tx_empty_intr_en                       = TX_EMPTY_INTERRUPT_DISABLE;
        I2C_InitStru.rx_fifo_full_hold_control_en           = RX_FIFO_FULL_HOLD_DISABLE;
        I2C_InitStru.master_bus_clear_feature_en            = MASTER_BUS_CLEAR_FEATURE_DISABLE;
        I2C_InitStru.optional_SAR_address_en                = OPTIONAL_SAR_ADDRESS_DISABLE;

        I2C_InitStru.SMBUS_slave_quick_en                   = SMBUS_SLAVE_QUICK_DISABLE;
        I2C_InitStru.SMBUS_ARP_contral_en                   = SMBUS_ARP_CONTRAL_DISABLE;
        I2C_InitStru.SMBUS_persistent_slave_addr_en         = SMBUS_PERSISTENT_SLV_ADDR_DISABLE;


        I2C_InitStru.I2C_target_address = 0x68;
#ifdef FPGA_OUT
        //I2C_InitStru.slc_h  = 500;
        //I2C_InitStru.slc_l  = 500;
#else
        I2C_InitStru.slc_h  = 20;
        I2C_InitStru.slc_l  = 20;
#endif
        
        I2C_InitStru.targer_address_type                = MASTER_7BIT_ADDR;
        I2C_InitStru.general_call_or_start_byte         = GENERAL_CALL;
        I2C_InitStru.general_call_or_start_byte_en      = GENERAL_CALL_OR_START_BYTE_DISABLE;

        I2C_InitStru.programming_device_id_en           = PROGRAMMING_DEVICE_ID_DISABLE;
        I2C_InitStru.programming_SMBUS_quick_cmd_en     = PROGRAMMING_SMBUS_QUICK_CMD_DISABLE;


        I2C_InitStru.salve_address = 0x68;
        
#ifdef BR_SLAVE
#ifdef BR_DUAL
        if(!GetSocRole())
#endif
        I2C_InitStru.interrupt_unmask = ((0x01<<RX_FULL_TYPE)|
                                         (0x01<<RX_OVER_TYPE)|
                                         (0x01<<RX_FULL_TYPE)|
                                         (0x01<<RD_REQ_TYPE));
#endif 

#ifdef BR_MASTER 
#ifdef BR_DUAL
        if(GetSocRole())
#endif
        I2C_InitStru.interrupt_unmask = 0;
#endif

        I2C_InitStru.fifo_receive_threshold_level   =  0;
        I2C_InitStru.fifo_transmit_threshold_level  =  0;

        I2C_InitStru.dma_rx_en = false;
        I2C_InitStru.dma_tx_en = false;
        I2C_InitStru.dma_tx_data_level =  2; 
        I2C_InitStru.dma_rx_data_level =  2;

        I2C_Init(I2C0,&I2C_InitStru);

        {
#ifdef BR_MASTER  
#ifdef BR_DUAL
        if(GetSocRole())
#endif            
        {
            uint8_t data_buff[50] = {\
                '1','2','3','4','5','6','7','8','9','\n',\
                '1','2','3','4','5','6','7','8','9','\n',\
                '1','2','3','4','5','6','7','8','9','\n',\
                '1','2','3','4','5','6','7','8','9','\n',\
                '1','2','3','4','5','6','7','8','9','\n'};
            
            uint32_t cd=0,va=0;
            // Verify_messageReceive(&cd,&va);
        MASTER_TEST: 
            Verify_messageGetRData(&cd,&va);

            if(!(cd == BRCASE_STOP1 && va == 1))
                // sut =false;
                goto MASTER_TEST;

            c_printf("I2C master[%d]\r\n",sut);
            if(sut)   
                I2C_ReadDate(I2C0,data_buff,12,1);

            for(uint16_t i = 0;i<12;i++)
                c_printf("[%X] ",data_buff[i]);
            c_printf("\n");
            
        }
#endif

#ifdef BR_SLAVE
#ifdef BR_DUAL
        if(!GetSocRole())
#endif
        {
            NVIC_ClearPendingIRQ(I2C0_IRQn);
            NVIC_EnableIRQ(I2C0_IRQn);
            c_printf("I2C slave.\r\n");  
            Verify_messageSend(BRCASE_STOP1,true); 
            
        }        
#endif                       
        }       
#endif  
    }
	MCU_Sleep(15);
    c_printf("d_1_762_i2c_dual_i2c_slave_interrupt_read_master case completed \r\n");
    SimulationEnd();
    while(1){     
    };
}


uint32_t rep=0x76;
void I2C0_IRQHandler(void)      
{    
    c_printf("IRQ[%x]\n",I2C0->INTR_STAT);
    if(I2C0->INTR_STAT & (0x01<<RD_REQ_TYPE))
    {
        I2C_ClearInterrupt(I2C0,RD_REQ_TYPE);
        c_printf("R\n");
        I2C_SetCmdData(I2C0,rep);
        rep++;
       
    }
    //c_printf("I2C[%x]\n",I2C0->INTR_STAT);
    if(I2C0->INTR_STAT & (0x01 << RX_OVER_TYPE))
    {
        I2C_ClearInterrupt(I2C0,RX_OVER_TYPE);
        c_printf("G:OVER\n");
        
    }
    if(I2C0->INTR_STAT & (0x01<<RX_FULL_TYPE))
    {
        uint32_t rxtl=0,txtl=0;
        I2C_ClearInterrupt(I2C0,RX_FULL_TYPE);
        I2C_GetRxTxThreshold(I2C0,&txtl,&rxtl);
        c_printf("GF");
        for(uint16_t i=0;i<rxtl;i++)
        {
            c_printf("[%X],",I2C0->DATA_CMD);
        }
        c_printf("\n");
        
    }
    //c_printf("I2CEnd[%x]\n",I2C0->INTR_STAT);
}   

















