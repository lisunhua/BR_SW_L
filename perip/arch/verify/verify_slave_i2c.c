/*
 *++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 * Copyright (c) 1999-2018 Barrot Technology Limited
 *
 * All rights reserved.
 *
 *------------------------------------------------------------------------------
 */
/**
 * @file verify_slave_i2c.c
 * @brief
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

#include "cm_printf.h"
#include "verify_slave_i2c.h"
#include "verify_message.h"
#include "verify_register_handle.h"

#include "system_BR00x.h"
#include "BR00x_config.h"
#include "BR00x_i2c.h"
#include "BR00x_i2c_erom.h"

#ifdef I2C_DEBUG_LOG
#define i2cprf(format, ...) cm_printf(format, ##__VA_ARGS__)
#else
#define i2cprf(format, ...)
#endif


const RegisterCell i2C0_RegList[]=
{
//  {read,  write,  Register ID ,register_attr, Register},
    {true,  true,   1,  0x000001FF,     &I2C0->IC_CON},
    {true,  true,   2,  0x00000FFF,     &I2C0->IC_TAR},
    {true,  true,   3,  0x000003FF,     &I2C0->IC_SAR},
    {true,  true,   4,  0x00000007,     &I2C0->IC_HS_MADDR},
    {true,  true,   5,  0x000007FF,     &I2C0->DATA_CMD},

    //Speed I2C CLOCK COUNT REGISTER
    {true,  true,   6,  0x0000FFFC,     &I2C0->IC_SS_SCL_HCNT},     //IC_ULTRA_FAST_MODE==0 NotUltra-Fase Speed
//  {true,  true,   7,  0x0000FFFC,     &I2C0->IC_UFM_SCL_HCNT},    //IC_ULTRA_FAST_MODE==0 NotUltra-Fase Speed
    {true,  true,   8,  0x0000FFF8,     &I2C0->IC_SS_SCL_LCNT},
//  {true,  true,   9,  0x0000FFF8,     &I2C0->IC_UFM_SCL_LCNT},    //IC_ULTRA_FAST_MODE==0 Not Ultra-Fase Speed
    {true,  true,   10, 0x0000FFFC,     &I2C0->IC_FS_SCL_HCNT},     //IC_MAX_SPEED_MODE =3
//  {true,  true,   11, 0x0000FFFC,     &I2C0->IC_UFM_TBUF_CNT},    //IC_ULTRA_FAST_MODE==0 Not Ultra-Fase Speed
    {true,  true,   12, 0x0000FFF8,     &I2C0->IC_FS_SCL_LCNT},
    {true,  true,   13, 0x0000FFF8,     &I2C0->IC_HS_SCL_HCNT},
    {true,  true,   14, 0x0000FFF8,     &I2C0->IC_HS_SCL_LCNT},
    
    {true,  false,  15, 0x00000FFF,     (volatile uint32_t*)&I2C0->INTR_STAT},
    {true,  true,   16, 0x00000FFF,      &I2C0->INTR_MASK},
    {true,  false,  17, 0x00000FFF,     (volatile uint32_t*)&I2C0->RAW_INTR_STAT},
    {true,  true,   18, 0x00000007,     &I2C0->RX_TL},
    {true,  true,   19, 0x00000007,     &I2C0->TX_TL},
    
    //Read Clear Interrupt register
    {true,  false,  20, 0x00000001,     (volatile uint32_t*)&I2C0->IC_CLR_INTR},
    {true,  false,  21, 0x00000001,     (volatile uint32_t*)&I2C0->IC_CLR_RX_UNDER},
    {true,  false,  22, 0x00000001,     (volatile uint32_t*)&I2C0->IC_CLR_RX_OVER},
    {true,  false,  23, 0x00000001,     (volatile uint32_t*)&I2C0->IC_CLR_TX_OVER},
    {true,  false,  24, 0x00000001,     (volatile uint32_t*)&I2C0->IC_CLR_RD_REQ},
    {true,  false,  25, 0x00000001,     (volatile uint32_t*)&I2C0->IC_CLR_TX_ABRT},
    {true,  false,  26, 0x00000001,     (volatile uint32_t*)&I2C0->IC_CLR_RX_DONE},
    {true,  false,  27, 0x00000001,     (volatile uint32_t*)&I2C0->IC_CLR_ACTIVITY},
    {true,  false,  28, 0x00000001,     (volatile uint32_t*)&I2C0->IC_CLR_STOP_DET},
    {true,  false,  29, 0x00000001,     (volatile uint32_t*)&I2C0->IC_CLR_START_DET},
    {true,  false,  30, 0x00000001,     (volatile uint32_t*)&I2C0->IC_CLR_GEN_CALL},
    
   // {true,  true,   31, 0x0000000E,     &I2C0->IC_ENABLE},// Enable (Bit0)Cannot Set
    {true,  false,  32, 0x001F0FFF,     (volatile uint32_t*)&I2C0->IC_STATUS},
    
    {true,  false,  33, 0x00000007,     (volatile uint32_t*)&I2C0->IC_TXFLR},
    {true,  false,  34, 0x00000007,     (volatile uint32_t*)&I2C0->IC_TXFLR},
    
    
    
};


/***********************************************************
                        Register
************************************************************/
bool cmd_VerifyRegisterI2CCase2(uint32_t cmd, uint8_t *param_line,uint16_t len)
{
    bool sut = true;
    #if  defined(BR002)||defined(BR003)
    uint32_t cid = cmd;
    uint32_t idx=0;
    
    i2cprf("i2c0 Register case2\r\n");
    SystemDevClockCtl(I2C_CKEn,true);
    verify_SendCid(cid,&idx);
    sut =Verify_RegisterHandle(i2C0_RegList,sizeof(i2C0_RegList),idx);
    Verify_SendCResult(BRCASE_RESULT,sut);
    #endif
    return sut;
}

/***********************************************************
                        APP
************************************************************/
bool cmd_VerifyAppI2CCase1(uint32_t cmd, uint8_t *param_line,uint16_t len)
{
    bool sut = true;
    uint32_t idx=0;
    i2cprf("I2C App case1\r\n");
    verify_SendCid(cmd,&idx);
    {
        I2C_InitInof_Type   I2C_InitStru;
        PADConfig_Type      PAG_InitStru;

        PAG_InitStru.set        = 0;
        PAG_InitStru.ie         = PAD_IE_ENABLE;
        PAG_InitStru.oen        = PAD_OEN_ENABLE;
        PAG_InitStru.ren        = PAD_REN_ENABLE;
        PAG_InitStru.pad_ctl    = PAD_MODE1;
        
        SystemPADConfig(PADID21,&PAG_InitStru);
        SystemPADConfig(PADID22,&PAG_InitStru);
        
        I2C_InitStru.master_en = MASTER_MODE_ENABLE;
        I2C_InitStru.slave_en = SLAVE_MODE_DISABLE;
        I2C_InitStru.restart_en = MASTER_RESTART_DISABLE;
        I2C_InitStru.slave_addr_type = SLAVE_7BIT_ADDR;
        I2C_InitStru.master_addr_type = MASTER_7BIT_ADDR;

        I2C_InitStru.max_speed =PARAM_MAX_SPEED_STANDARD;

        I2C_InitStru.slave_stop_det_if_addressed_en = SLAVE_STOP_DET_IFADDRESSED_DISABLE;
        I2C_InitStru.master_stop_det_if_addressed_en = MASTER_STOP_DET_IFACTIVE_DISABLE; 
        I2C_InitStru.tx_empty_intr_en = TX_EMPTY_INTERRUPT_DISABLE;
        I2C_InitStru.rx_fifo_full_hold_control_en = RX_FIFO_FULL_HOLD_DISABLE;
        I2C_InitStru.master_bus_clear_feature_en = MASTER_BUS_CLEAR_FEATURE_DISABLE;
        I2C_InitStru.optional_SAR_address_en = OPTIONAL_SAR_ADDRESS_DISABLE;

        I2C_InitStru.SMBUS_slave_quick_en = SMBUS_SLAVE_QUICK_DISABLE;
        I2C_InitStru.SMBUS_ARP_contral_en = SMBUS_ARP_CONTRAL_DISABLE;
        I2C_InitStru.SMBUS_persistent_slave_addr_en = SMBUS_PERSISTENT_SLV_ADDR_DISABLE;


        I2C_InitStru.I2C_target_address = 0x50;
        //I2C_InitStru.slc_h  = 500;
        //I2C_InitStru.slc_l  = 500;
        
        I2C_InitStru.slc_h  = 20;
        I2C_InitStru.slc_l  = 20;
        
        I2C_InitStru.targer_address_type = MASTER_7BIT_ADDR;
        I2C_InitStru.general_call_or_start_byte = GENERAL_CALL;
        I2C_InitStru.general_call_or_start_byte_en = GENERAL_CALL_OR_START_BYTE_DISABLE;

        I2C_InitStru.programming_device_id_en = PROGRAMMING_DEVICE_ID_DISABLE;
        I2C_InitStru.programming_SMBUS_quick_cmd_en = PROGRAMMING_SMBUS_QUICK_CMD_DISABLE;


        I2C_InitStru.salve_address = 0x2a;
        I2C_InitStru.interrupt_unmask =  0x78e1;

        I2C_InitStru.fifo_receive_threshold_level =  6;
        I2C_InitStru.fifo_transmit_threshold_level = 6;

        I2C_InitStru.dma_rx_en = false;
        I2C_InitStru.dma_tx_en = false;
        I2C_InitStru.dma_tx_data_level =  2; 
        I2C_InitStru.dma_rx_data_level =  2;
        #if  defined(BR002)||defined(BR003)
        SystemDevClockCtl(I2C_CKEn,true);
        #endif
        I2C_Init(I2C0,&I2C_InitStru);

        //NVIC_EnableIRQ(I2C0_IRQn);
        {
            #define MaxLendata  50
            static  uint8_t data_se[MaxLendata]= {0};
            static  uint8_t data_buff[MaxLendata]={0};
            
            EEPROM_WritePage (0,data_se,MaxLendata);
            EEPROM_SequentialRead(0,data_buff,MaxLendata);

            i2cprf("eeprom Read : ");
            for(uint16_t i=0;i<MaxLendata;i++)
                cm_printf("%X,",data_buff[i]);
            i2cprf("\r\n");
            

            for(uint16_t i=0;i<MaxLendata;i++)
                data_se[i] = i;

            EEPROM_WritePage (0,data_se,MaxLendata);
            
            i2cprf("eeprom Write:");
            for(uint16_t i=0;i<MaxLendata;i++)
                cm_printf("%X,",data_se[i]);
            i2cprf("\r\n");
            
            for(uint32_t i=0;i<50000;i++);
            
            EEPROM_SequentialRead(0,data_buff,MaxLendata);

            i2cprf("eeprom Read : ");
            for(uint16_t i=0;i<MaxLendata;i++)
            {
                cm_printf("%X,",data_buff[i]);
            }
            i2cprf("\r\n");
            i2cprf("test i2c complete \r\n ");

            }


        
        
    }
    
    
    Verify_SendCResult(BRCASE_RESULT,sut);
    return sut;
}

bool cmd_VerifyDualAppI2CCase1(uint32_t cmd, uint8_t *param_line,uint16_t len)
{
    bool sut = true;
    
#if defined(BR_MASTER) || defined(BR_SLAVE)
    
    //uint32_t idx=0;
    //verify_SendCid(cmd,&idx);
    i2cprf("I2C Dual App case1\r\n");
    {
        I2C_InitInof_Type   I2C_InitStru;
        PADConfig_Type      PAG_InitStru;

        PAG_InitStru.set        = 0;
        PAG_InitStru.ie         = PAD_IE_ENABLE;
        PAG_InitStru.oen        = PAD_OEN_ENABLE;
        PAG_InitStru.ren        = PAD_REN_ENABLE;
        PAG_InitStru.pad_ctl    = PAD_MODE1;
        
        SystemPADConfig(PADID21,&PAG_InitStru);
        SystemPADConfig(PADID22,&PAG_InitStru);
        
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
        I2C_InitStru.slc_h  = 500;
        I2C_InitStru.slc_l  = 500;
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
        I2C_InitStru.interrupt_unmask =     ((0x01<<RX_FULL_TYPE)|
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

        I2C_InitStru.fifo_receive_threshold_level =  0;
        I2C_InitStru.fifo_transmit_threshold_level = 0;

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
                '1','2','3','4','5','6','7','8','9','0',\
                '1','2','3','4','5','6','7','8','9','0',\
                '1','2','3','4','5','6','7','8','9','0',\
                '1','2','3','4','5','6','7','8','9','0',\
                '1','2','3','4','5','6','7','8','9','0'};
            
            uint32_t cd=0,va=0;
            Verify_messageReceive(&cd,&va);
            if(!(cd == BRCASE_STOP1 && va == 1))
                sut =false;
            i2cprf("I2C master[%d]\r\n",sut);
            if(sut)   
                I2C_WriteDate(I2C0,data_buff,10,1);

        }
#endif

#ifdef BR_SLAVE
#ifdef BR_DUAL
        if(!GetSocRole())
#endif
        {
            NVIC_ClearPendingIRQ(I2C0_IRQn);
            NVIC_EnableIRQ(I2C0_IRQn);
            i2cprf("I2C slave.\r\n");  
            Verify_messageSend(BRCASE_STOP1,true);  
        }
#endif                
            
        } 


        
        
    }
    
    MCU_Sleep(15);
    Verify_SendCResult(BRCASE_RESULT,sut);
#endif
    return sut;
}


bool cmd_VerifyDualAppI2CCase2(uint32_t cmd, uint8_t *param_line,uint16_t len)
{
    bool sut = true;
    
#if defined(BR_MASTER) || defined(BR_SLAVE)
    //uint32_t idx=0;
    //verify_SendCid(cmd,&idx);
    
    i2cprf("I2C Dual App case2\r\n");
    {
        I2C_InitInof_Type   I2C_InitStru;
        PADConfig_Type      PAG_InitStru;

        PAG_InitStru.set        = 0;
        PAG_InitStru.ie         = PAD_IE_ENABLE;
        PAG_InitStru.oen        = PAD_OEN_ENABLE;
        PAG_InitStru.ren        = PAD_REN_ENABLE;
        PAG_InitStru.pad_ctl    = PAD_MODE1;
        
        SystemPADConfig(PADID21,&PAG_InitStru);
        SystemPADConfig(PADID22,&PAG_InitStru);
        
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
        I2C_InitStru.interrupt_unmask =     ((0x01<<RX_FULL_TYPE)|
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
            Verify_messageReceive(&cd,&va);
            if(!(cd == BRCASE_STOP1 && va == 1))
                sut =false;
            i2cprf("I2C master[%d]\r\n",sut);
            if(sut)   
                I2C_ReadDate(I2C0,data_buff,12,1);
            for(uint16_t i = 0;i<12;i++)
                i2cprf("[%X] ",data_buff[i]);
            i2cprf("\n");
            
        }
#endif

#ifdef BR_SLAVE
#ifdef BR_DUAL
        if(!GetSocRole())
#endif
        {
            NVIC_ClearPendingIRQ(I2C0_IRQn);
            NVIC_EnableIRQ(I2C0_IRQn);
            i2cprf("I2C slave.\r\n");  
            Verify_messageSend(BRCASE_STOP1,true); 
            
        }        
#endif                       
        }       
    }
    
    MCU_Sleep(15);
    Verify_SendCResult(BRCASE_RESULT,sut);
#endif
    return sut;
}


uint32_t rep=0x76;

void I2C0_IRQHandler(void)      
{    
    i2cprf("IRQ[%x]\n",I2C0->INTR_STAT);
    if(I2C0->INTR_STAT & (0x01<<RD_REQ_TYPE))
    {
        I2C_ClearInterrupt(I2C0,RD_REQ_TYPE);
        cm_printf("R\n");
        I2C_SetCmdData(I2C0,rep);
        rep++;
       
    }
    //i2cprf("I2C[%x]\n",I2C0->INTR_STAT);
    if(I2C0->INTR_STAT & (0x01 << RX_OVER_TYPE))
    {
        I2C_ClearInterrupt(I2C0,RX_OVER_TYPE);
        i2cprf("G:OVER\n");
        
    }
    if(I2C0->INTR_STAT & (0x01<<RX_FULL_TYPE))
    {
        uint32_t rxtl=0,txtl=0;
        I2C_ClearInterrupt(I2C0,RX_FULL_TYPE);
        I2C_GetRxTxThreshold(I2C0,&txtl,&rxtl);
        i2cprf("GF");
        for(uint16_t i=0;i<rxtl;i++)
        {
            i2cprf("[%X],",I2C0->DATA_CMD);
        }
        i2cprf("\n");
        
    }
    //i2cprf("I2CEnd[%x]\n",I2C0->INTR_STAT);
}   

 








