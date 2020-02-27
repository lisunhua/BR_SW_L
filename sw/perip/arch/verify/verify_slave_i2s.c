/*
 *++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 * Copyright (c) 1999-2018 Barrot Technology Limited
 *
 * All rights reserved.
 *
 *------------------------------------------------------------------------------
 */
/**
 * @file verify_slave_i2s.c
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
#include "verify_slave_i2s.h"
#include "verify_message.h"
#include "verify_register_handle.h"

#include "BR00x_config.h"
#include "BR00x_i2s.h"

#ifdef I2S_DEBUG_LOG
#define i2sprf(format, ...) cm_printf(format, ##__VA_ARGS__)
#else
#define i2sprf(format, ...)
#endif

const RegisterCell i2SM_RegList[]=
{
//  {read,  write,  Register ID ,register_attr, Register},
//  {true,  true,   1,  0x00000001,     &I2SM->IER},//ENABLE BIT CANNOT SET
    {true,  true,   2,  0x00000001,     &I2SM->IRER},
    {true,  true,   3,  0x00000001,     &I2SM->ITER},
    {true,  true,   4,  0x00000001,     &I2SM->CER},
    {true,  true,   5,  0x0000001F,     &I2SM->CCR},
    
    {false, true,   6,  0x00000001,     &I2SM->RXFFR},
    {false, true,   7,  0x00000001,     &I2SM->TXFFR},
    
    //DMA REGISTER
    {true,  false,  8,  0xFFFFFFFF,     (volatile uint32_t*)&I2SM->RXDMA},
    {false, true,   9,  0x00000001,     &I2SM->RRXDMA},
    {false, true,   10, 0xFFFFFFFF,     &I2SM->TXDMA},
    {false, true,   11, 0x00000001,     &I2SM->RTXDMA},
    
    {true,  false,  12, 0xFFFFFFFF,     (volatile uint32_t*)&I2SM->I2S_Ch.LRBR},
    {false, true,   13, 0xFFFFFFFF,     &I2SM->I2S_Ch.LTHR},
    {true,  false,  14, 0xFFFFFFFF,     (volatile uint32_t*)&I2SM->I2S_Ch.RRBR},
    {false, true,   15, 0xFFFFFFFF,     &I2SM->I2S_Ch.RTHR},
    {true,  true,   16, 0x00000001,     &I2SM->I2S_Ch.RER},
    {true,  true,   17, 0x00000001,     &I2SM->I2S_Ch.TER},
    {true,  true,   18, 0x00000007,     &I2SM->I2S_Ch.RCR},
    {true,  true,   19, 0x00000007,     &I2SM->I2S_Ch.TCR},
    
    {true,  false,  20, 0x0000003F,     (volatile uint32_t*)&I2SM->I2S_Ch.ISR},
    {true,  true,   21, 0x00000033,     &I2SM->I2S_Ch.IMR},
    
    {true,  false,  22, 0x00000001,     (volatile uint32_t*)&I2SM->I2S_Ch.ROR},
    {true,  false,  23, 0x00000001,     (volatile uint32_t*)&I2SM->I2S_Ch.TOR},
    
    {true,  true,   24, 0x0000000F,     &I2SM->I2S_Ch.RFCR},
    {true,  true,   25, 0x0000000F,     &I2SM->I2S_Ch.TFCR},
    
    {false, true,   26, 0x0000000F,     &I2SM->I2S_Ch.RFF},
    {false, true,   27, 0x0000000F,     &I2SM->I2S_Ch.TFF},
};


const RegisterCell i2SS_RegList[]=
{
//  {read,  write,  Register ID ,register_attr, Register},
//  {true,  true,   1,  0x00000001,     &I2SS->IER},//ENABLE BIT CANNOT SET
    {true,  true,   2,  0x00000001,     &I2SS->IRER},
    {true,  true,   3,  0x00000001,     &I2SS->ITER},
//    {true,  true,   4,  0x00000001,     &I2SS->CER},
//    {true,  true,   5,  0x0000001F,     &I2SS->CCR},
    
    {false, true,   6,  0x00000001,     &I2SS->RXFFR},
    {false, true,   7,  0x00000001,     &I2SS->TXFFR},
    
    //DMA REGISTER
    {true,  false,  8,  0xFFFFFFFF,     (volatile uint32_t*)&I2SS->RXDMA},
    {false, true,   9,  0x00000001,     &I2SS->RRXDMA},
    {false, true,   10, 0xFFFFFFFF,     &I2SS->TXDMA},
    {false, true,   11, 0x00000001,     &I2SS->RTXDMA},
    
    {true,  false,  12, 0xFFFFFFFF,     (volatile uint32_t*)&I2SS->I2S_Ch.LRBR},
    {false, true,   13, 0xFFFFFFFF,     &I2SS->I2S_Ch.LTHR},
    {true,  false,  14, 0xFFFFFFFF,     (volatile uint32_t*)&I2SS->I2S_Ch.RRBR},
    {false, true,   15, 0xFFFFFFFF,     &I2SS->I2S_Ch.RTHR},
    {true,  true,   16, 0x00000001,     &I2SS->I2S_Ch.RER},
    {true,  true,   17, 0x00000001,     &I2SS->I2S_Ch.TER},
    {true,  true,   18, 0x00000007,     &I2SS->I2S_Ch.RCR},
    {true,  true,   19, 0x00000007,     &I2SS->I2S_Ch.TCR},
    
    {true,  false,  20, 0x0000003F,     (volatile uint32_t*)&I2SS->I2S_Ch.ISR},
    {true,  true,   21, 0x00000033,     &I2SS->I2S_Ch.IMR},
    
    {true,  false,  22, 0x00000001,     (volatile uint32_t*)&I2SS->I2S_Ch.ROR},
    {true,  false,  23, 0x00000001,     (volatile uint32_t*)&I2SS->I2S_Ch.TOR},
    
    {true,  true,   24, 0x0000000F,     &I2SS->I2S_Ch.RFCR},
    {true,  true,   25, 0x0000000F,     &I2SS->I2S_Ch.TFCR},
    
    {false, true,   26, 0x0000000F,     &I2SS->I2S_Ch.RFF},
    {false, true,   27, 0x0000000F,     &I2SS->I2S_Ch.TFF},
};


/***********************************************************
                        Register
************************************************************/
bool cmd_VerifyRegisterI2smCase2(uint32_t cmd, uint8_t *param_line,uint16_t len)
{
    bool sut = true;
    uint32_t idx=0;
    i2sprf("i2sM Register case2\r\n");
    verify_SendCid(cmd,&idx);
    SystemDevClockCtl(I2SM_CKEn,true);
    sut =Verify_RegisterHandle(i2SM_RegList,sizeof(i2SM_RegList),idx);

    Verify_SendCResult(BRCASE_RESULT,sut);
    return sut;
}

bool cmd_VerifyRegisterI2ssCase2(uint32_t cmd, uint8_t *param_line,uint16_t len)
{
    bool sut = true;
    uint32_t idx=0;
    i2sprf("i2sS Register case2\r\n");
    verify_SendCid(cmd,&idx);
    SystemDevClockCtl(I2SS_CKEn,true);
    sut =Verify_RegisterHandle(i2SS_RegList,sizeof(i2SS_RegList),idx);

    Verify_SendCResult(BRCASE_RESULT,sut);
    return sut;
}


/***********************************************************
                        APP
************************************************************/

void i2sm_SendData(void)
{
    uint32_t data   = 0xaaaaaaa0;
    uint32_t data1  = 0x55555550;
    while(0== I2S_GetInterruptStatus(I2SM,I2S_TX_FIFO_OVERRUN))
    {
        data++;
        data1++;
        I2S_SetLeftTransmitData(I2SM,data);
        I2S_SetRightTransmitData(I2SM,data1);
    }
    {
        I2S_IntCtlMask  IntCtlMask;
        IntCtlMask.rx_dma_available_interrupt_mask    =  false;
        IntCtlMask.rx_fifo_overrun_interrupt_mask     =  false;
        IntCtlMask.tx_fifo_empty_interrupt_mask       =  false;
        IntCtlMask.tx_fifo_overrun_interrupt_mask     =  false;
        I2S_SetInterruptMask(I2SM ,&IntCtlMask);
    }

    I2S_GeneratrClock(I2SM,true);
    
}

void i2ss_SendData(void)
{
    uint32_t data   = 0x66666660;
    uint32_t data1  = 0x99999990;
    while(0== I2S_GetInterruptStatus(I2SS,I2S_TX_FIFO_OVERRUN))
    {
        data++;
        data1++;
        I2S_SetLeftTransmitData(I2SS,data);
        I2S_SetRightTransmitData(I2SS,data1);
    }
    {
        I2S_IntCtlMask  IntCtlMask;
        IntCtlMask.rx_dma_available_interrupt_mask    =  false;
        IntCtlMask.rx_fifo_overrun_interrupt_mask     =  false;
        IntCtlMask.tx_fifo_empty_interrupt_mask       =  false;
        IntCtlMask.tx_fifo_overrun_interrupt_mask     =  false;
        I2S_SetInterruptMask(I2SS ,&IntCtlMask);
    }
}


bool cmd_VerifyAppI2SMCase1(uint32_t cmd, uint8_t *param_line,uint16_t len)
{
    bool sut = true;
    uint32_t idx=0;
    i2sprf("I2S App case1\r\n");
    verify_SendCid(cmd,&idx);

    {
        I2S_InitInof_Type   I2S_InitStru;
        PADConfig_Type      PAG_InitStru;

        memset(&PAG_InitStru,0,sizeof(PADConfig_Type));
        PAG_InitStru.set        = 0;
        PAG_InitStru.pad_ctl    = PAD_MODE2;

        SystemPADConfig(PADID17,&PAG_InitStru); //interface 1
        SystemPADConfig(PADID18,&PAG_InitStru);
        SystemPADConfig(PADID19,&PAG_InitStru);
        SystemPADConfig(PADID20,&PAG_InitStru);
        
        
        SystemPADConfig(PADID2,&PAG_InitStru); //interface 2
        SystemPADConfig(PADID3,&PAG_InitStru);
        SystemPADConfig(PADID4,&PAG_InitStru);
        SystemPADConfig(PADID5,&PAG_InitStru);
        
        I2S_InitStru.dirct_type= DATA_TX;
        
        I2S_InitStru.clock_gating_type  =  NO_CLOCK_GATING;
        I2S_InitStru.clock_type         =  CLOCK_CYCLES_32;
        I2S_InitStru.data_resl_type     =  RESOLUTION_32_BIT;
        SCU->IO_CONFIG |=0x10;
        SCU->IO_CONFIG |=0x20;
        I2S_InitStru.interrupt_level    = TRIGGER_LEVEL_1;
        I2S_InitStru.IntCtlMask.rx_dma_available_interrupt_mask     =  true;
        I2S_InitStru.IntCtlMask.rx_fifo_overrun_interrupt_mask      =  true;
        I2S_InitStru.IntCtlMask.tx_fifo_empty_interrupt_mask        =  true;
        I2S_InitStru.IntCtlMask.tx_fifo_overrun_interrupt_mask      =  true;

        SystemDevClockCtl(I2SM_CKEn,true);

        I2S_Init(I2SM, &I2S_InitStru);
        NVIC_EnableIRQ(I2SM_IRQn);
        i2sm_SendData();    
    }
    Verify_SendCResult(BRCASE_RESULT,sut);
    return sut;
}


// dual CPU
bool cmd_VerifyDualAppI2SCase1(uint32_t cmd, uint8_t *param_line,uint16_t len)
{
    bool sut = true;
    //uint32_t idx=0;
    //verify_SendCid(cmd,&idx);
    i2sprf("I2S Dual App case1\r\n");
    {
#if    defined(BR_MASTER) || defined(BR_SLAVE)
        I2S_InitInof_Type   I2S_InitStru;
        PADConfig_Type      PAG_InitStru;

        PAG_InitStru.set        = 0;
        PAG_InitStru.ie         = PAD_IE_ENABLE;
        PAG_InitStru.oen        = PAD_OEN_ENABLE;
        PAG_InitStru.ren        = PAD_REN_ENABLE;
        PAG_InitStru.pad_ctl    = PAD_MODE2;

        SystemPADConfig(PADID17,&PAG_InitStru);
        SystemPADConfig(PADID18,&PAG_InitStru);
        SystemPADConfig(PADID19,&PAG_InitStru);
        SystemPADConfig(PADID20,&PAG_InitStru);
        
        I2S_InitStru.clock_gating_type      =  NO_CLOCK_GATING;
        I2S_InitStru.clock_type             =  CLOCK_CYCLES_32;
        I2S_InitStru.data_resl_type         =  RESOLUTION_32_BIT;
        I2S_InitStru.interrupt_level        =  TRIGGER_LEVEL_1;
        
#ifdef BR_SLAVE  
#ifdef BR_DUAL
        if(!GetSocRole())
#endif
        {
            I2S_InitStru.dirct_type= DATA_RX;
            I2S_InitStru.IntCtlMask.rx_dma_available_interrupt_mask     =  false;//Enable
            I2S_InitStru.IntCtlMask.rx_fifo_overrun_interrupt_mask      =  false;//Enable
            I2S_InitStru.IntCtlMask.tx_fifo_empty_interrupt_mask        =  true; //Disable
            I2S_InitStru.IntCtlMask.tx_fifo_overrun_interrupt_mask      =  false;//Enable
            
            SCU->IO_CONFIG &=~0x20;
            
            SystemDevClockCtl(I2SS_CKEn,true);
            
            I2S_Init(I2SS, &I2S_InitStru);
            NVIC_ClearPendingIRQ(I2SS_IRQn);
            NVIC_EnableIRQ(I2SS_IRQn);
            Verify_messageSend(BRCASE_STOP1,true);
            i2sprf("I2S slave\n"); 
        }            
#endif


#ifdef BR_MASTER 
#ifdef BR_DUAL
        if(GetSocRole())
#endif
        {
            I2S_InitStru.dirct_type= DATA_TX;
            I2S_InitStru.IntCtlMask.rx_dma_available_interrupt_mask     =  true;
            I2S_InitStru.IntCtlMask.rx_fifo_overrun_interrupt_mask      =  true;
            I2S_InitStru.IntCtlMask.tx_fifo_empty_interrupt_mask        =  true;
            I2S_InitStru.IntCtlMask.tx_fifo_overrun_interrupt_mask      =  true;

            SystemDevClockCtl(I2SM_CKEn,true);
            
            SCU->IO_CONFIG |=0x20;
            I2S_Init(I2SM, &I2S_InitStru);
            NVIC_ClearPendingIRQ(I2SM_IRQn);
            NVIC_EnableIRQ(I2SM_IRQn);
            {
                uint32_t cd=0,va=0;
                Verify_messageReceive(&cd,&va);
                if(!(cd == BRCASE_STOP1 && va == 1))
                    sut =false;
                i2sprf("I2S master[%d]\r\n",sut);
                if(sut)   
                     i2sm_SendData();
            }
        }
            
#endif      
#endif            
    }
    MCU_Sleep(20);
    Verify_SendCResult(BRCASE_RESULT,sut);
    return sut;
}

bool cmd_VerifyDualAppI2SCase2(uint32_t cmd, uint8_t *param_line,uint16_t len)
{
    bool sut = true;
    //uint32_t idx=0;
    //verify_SendCid(cmd,&idx);
    i2sprf("I2S Dual App case2\r\n");
    {
#if (defined(BR_MASTER) || defined(BR_SLAVE))
        I2S_InitInof_Type   I2S_InitStru;
        PADConfig_Type      PAG_InitStru;

        PAG_InitStru.set        = 0;
        PAG_InitStru.ie         = PAD_IE_ENABLE;
        PAG_InitStru.oen        = PAD_OEN_ENABLE;
        PAG_InitStru.ren        = PAD_REN_ENABLE;
        PAG_InitStru.pad_ctl    = PAD_MODE2;

        SystemPADConfig(PADID17,&PAG_InitStru);
        SystemPADConfig(PADID18,&PAG_InitStru);
        SystemPADConfig(PADID19,&PAG_InitStru);
        SystemPADConfig(PADID20,&PAG_InitStru);
        
        I2S_InitStru.clock_gating_type      =  NO_CLOCK_GATING;
        I2S_InitStru.clock_type             =  CLOCK_CYCLES_32;
        I2S_InitStru.data_resl_type         =  RESOLUTION_32_BIT;
        I2S_InitStru.interrupt_level        =  TRIGGER_LEVEL_1;
        
#ifdef BR_SLAVE 
#ifdef BR_DUAL
        if(!GetSocRole())
#endif
        {
            I2S_InitStru.dirct_type= DATA_TX;
            I2S_InitStru.IntCtlMask.rx_dma_available_interrupt_mask     =  true;//Disable
            I2S_InitStru.IntCtlMask.rx_fifo_overrun_interrupt_mask      =  true;//Disable
            I2S_InitStru.IntCtlMask.tx_fifo_empty_interrupt_mask        =  true;//Disable
            I2S_InitStru.IntCtlMask.tx_fifo_overrun_interrupt_mask      =  true;//Disable
            
            SystemDevClockCtl(I2SS_CKEn,true);
            SCU->IO_CONFIG &=~0x20;
            I2S_Init(I2SS, &I2S_InitStru);
            NVIC_ClearPendingIRQ(I2SS_IRQn);
            NVIC_EnableIRQ(I2SS_IRQn);
            {
                uint32_t cd=0,va=0;
                Verify_messageReceive(&cd,&va);
                if(!(cd == BRCASE_STOP1 && va == 1))
                    sut =false;
                i2sprf("I2S slave[%d]\r\n",sut);
                if(sut)   
                     i2ss_SendData();
            }
            
            Verify_messageSend(BRCASE_STOP2,true);
        }
           
#endif


#ifdef BR_MASTER 
#ifdef BR_DUAL
        if(GetSocRole())
#endif
        {
            I2S_InitStru.dirct_type= DATA_RX;
            I2S_InitStru.IntCtlMask.rx_dma_available_interrupt_mask     =  false;
            I2S_InitStru.IntCtlMask.rx_fifo_overrun_interrupt_mask      =  false;
            I2S_InitStru.IntCtlMask.tx_fifo_empty_interrupt_mask        =  true;
            I2S_InitStru.IntCtlMask.tx_fifo_overrun_interrupt_mask      =  false;

            SystemDevClockCtl(I2SM_CKEn,true);
            SCU->IO_CONFIG |=0x20;
            I2S_Init(I2SM, &I2S_InitStru);
            NVIC_ClearPendingIRQ(I2SM_IRQn);
            NVIC_EnableIRQ(I2SM_IRQn);
            i2sprf("I2S Master\n");
            Verify_messageSend(BRCASE_STOP1,true);
            {
                uint32_t cd=0,va=0;
                Verify_messageReceive(&cd,&va);
                if(!(cd == BRCASE_STOP2 && va == 1))
                    sut =false;
                i2sprf("I2S master[%d]\r\n",sut);
                if(sut)   
                    I2S_GeneratrClock(I2SM,true);
            }
        }     
#endif 
#endif        
    }
    MCU_Sleep(20);
    Verify_SendCResult(BRCASE_RESULT,sut);
    return sut;
}

bool cmd_VerifyDualAppI2SCase3(uint32_t cmd, uint8_t *param_line,uint16_t len)
{
    bool sut = true;
    //uint32_t idx=0;
    //verify_SendCid(cmd,&idx);
    i2sprf("I2S Dual App case3\r\n");
    {
#if (defined(BR_MASTER) || defined(BR_SLAVE))
        I2S_InitInof_Type   I2S_InitStru;
        PADConfig_Type      PAG_InitStru;

        PAG_InitStru.set        = 0;
        PAG_InitStru.ie         = PAD_IE_ENABLE;
        PAG_InitStru.oen        = PAD_OEN_ENABLE;
        PAG_InitStru.ren        = PAD_REN_ENABLE;
        PAG_InitStru.pad_ctl    = PAD_MODE2;

        SystemPADConfig(PADID17,&PAG_InitStru);
        SystemPADConfig(PADID18,&PAG_InitStru);
        SystemPADConfig(PADID19,&PAG_InitStru);
        SystemPADConfig(PADID20,&PAG_InitStru);
        
        I2S_InitStru.clock_gating_type      =  NO_CLOCK_GATING;
        I2S_InitStru.clock_type             =  CLOCK_CYCLES_32;
        I2S_InitStru.data_resl_type         =  RESOLUTION_32_BIT;
        I2S_InitStru.interrupt_level        =  TRIGGER_LEVEL_1;
        
#ifdef BR_SLAVE
#ifdef BR_DUAL
        if(!GetSocRole())
#endif
        {
            I2S_InitStru.dirct_type= DATA_TX_RX;
            I2S_InitStru.IntCtlMask.rx_dma_available_interrupt_mask     =  true;//Disable
            I2S_InitStru.IntCtlMask.rx_fifo_overrun_interrupt_mask      =  true;//Disable
            I2S_InitStru.IntCtlMask.tx_fifo_empty_interrupt_mask        =  true;//Disable
            I2S_InitStru.IntCtlMask.tx_fifo_overrun_interrupt_mask      =  true;//Disable
            
            SystemDevClockCtl(I2SS_CKEn,true);
            SCU->IO_CONFIG &=~0x20;
            I2S_Init(I2SS, &I2S_InitStru);
            NVIC_ClearPendingIRQ(I2SS_IRQn);
            NVIC_EnableIRQ(I2SS_IRQn);
            Verify_messageSend(BRCASE_STOP1,true);
            i2sprf("I2S slave idl\n");
            
            {
                uint32_t cd=0,va=0;
                Verify_messageReceive(&cd,&va);
                if(!(cd == BRCASE_STOP2 && va == 1))
                    sut =false;
                i2sprf("I2S slave[%d]\r\n",sut);
                if(sut)   
                     i2ss_SendData();
            }
        }
           
#endif


#ifdef BR_MASTER 
#ifdef BR_DUAL
        if(GetSocRole())
#endif
        {
            I2S_InitStru.dirct_type= DATA_TX_RX;
            I2S_InitStru.IntCtlMask.rx_dma_available_interrupt_mask     =  true;
            I2S_InitStru.IntCtlMask.rx_fifo_overrun_interrupt_mask      =  true;
            I2S_InitStru.IntCtlMask.tx_fifo_empty_interrupt_mask        =  true;
            I2S_InitStru.IntCtlMask.tx_fifo_overrun_interrupt_mask      =  true;

            SystemDevClockCtl(I2SM_CKEn,true);
            SCU->IO_CONFIG |=0x20;
            I2S_Init(I2SM, &I2S_InitStru);
            NVIC_ClearPendingIRQ(I2SM_IRQn);
            NVIC_EnableIRQ(I2SM_IRQn);
            
            Verify_messageSend(BRCASE_STOP2,true);
            i2sprf("I2S Master idl\n");  
            
            {
                uint32_t cd=0,va=0;
                Verify_messageReceive(&cd,&va);
                if(!(cd == BRCASE_STOP1 && va == 1))
                    sut =false;
                i2sprf("I2S Master[%d] \n",sut);
                if(sut)   
                     i2sm_SendData();
            }
        }
#endif  
#endif        
    }
    MCU_Sleep(20);
    Verify_SendCResult(BRCASE_RESULT,sut);
    return sut;
}



bool cmd_VerifyDualAppI2SCase4(uint32_t cmd, uint8_t *param_line,uint16_t len)
{
    bool sut = true;
    //uint32_t idx=0;
    //verify_SendCid(cmd,&idx);
    i2sprf("I2S Dual App case4 2-5 Pin\r\n");
    {
#if (defined(BR_MASTER) || defined(BR_SLAVE))
        I2S_InitInof_Type   I2S_InitStru;
        PADConfig_Type      PAG_InitStru;

        PAG_InitStru.set        = 0;
        PAG_InitStru.ie         = PAD_IE_ENABLE;
        PAG_InitStru.oen        = PAD_OEN_ENABLE;
        PAG_InitStru.ren        = PAD_REN_ENABLE;
        PAG_InitStru.pad_ctl    = PAD_MODE2;

        SystemPADConfig(PADID2,&PAG_InitStru);
        SystemPADConfig(PADID3,&PAG_InitStru);
        SystemPADConfig(PADID4,&PAG_InitStru);
        SystemPADConfig(PADID5,&PAG_InitStru);
        
        I2S_InitStru.clock_gating_type      =  NO_CLOCK_GATING;
        I2S_InitStru.clock_type             =  CLOCK_CYCLES_32;
        I2S_InitStru.data_resl_type         =  RESOLUTION_32_BIT;
        I2S_InitStru.interrupt_level        =  TRIGGER_LEVEL_1;
        
#ifdef BR_SLAVE  
#ifdef BR_DUAL
        if(!GetSocRole())
#endif
        {
            I2S_InitStru.dirct_type= DATA_TX_RX;
            I2S_InitStru.IntCtlMask.rx_dma_available_interrupt_mask     =  true;//Disable
            I2S_InitStru.IntCtlMask.rx_fifo_overrun_interrupt_mask      =  true;//Disable
            I2S_InitStru.IntCtlMask.tx_fifo_empty_interrupt_mask        =  true;//Disable
            I2S_InitStru.IntCtlMask.tx_fifo_overrun_interrupt_mask      =  true;//Disable
            
            SystemDevClockCtl(I2SS_CKEn,true);
            SCU->IO_CONFIG &=~0x10;
            I2S_Init(I2SS, &I2S_InitStru);
            NVIC_ClearPendingIRQ(I2SS_IRQn);
            NVIC_EnableIRQ(I2SS_IRQn);
            Verify_messageSend(BRCASE_STOP1,true);
            i2sprf("I2S slave idl\n");
            
            {
                uint32_t cd=0,va=0;
                Verify_messageReceive(&cd,&va);
                if(!(cd == BRCASE_STOP2 && va == 1))
                    sut =false;
                i2sprf("I2S slave[%d]\r\n",sut);
                if(sut)   
                     i2ss_SendData();
            }
        }
           
#endif


#ifdef BR_MASTER 
#ifdef BR_DUAL
        if(GetSocRole())
#endif
        {
            I2S_InitStru.dirct_type= DATA_TX_RX;
            I2S_InitStru.IntCtlMask.rx_dma_available_interrupt_mask     =  true;
            I2S_InitStru.IntCtlMask.rx_fifo_overrun_interrupt_mask      =  true;
            I2S_InitStru.IntCtlMask.tx_fifo_empty_interrupt_mask        =  true;
            I2S_InitStru.IntCtlMask.tx_fifo_overrun_interrupt_mask      =  true;

            SystemDevClockCtl(I2SM_CKEn,true);
            SCU->IO_CONFIG |=0x10;
            I2S_Init(I2SM, &I2S_InitStru);
            NVIC_ClearPendingIRQ(I2SM_IRQn);
            NVIC_EnableIRQ(I2SM_IRQn);
            
            Verify_messageSend(BRCASE_STOP2,true);
            i2sprf("I2S Master idl\n");  
            
            {
                uint32_t cd=0,va=0;
                Verify_messageReceive(&cd,&va);
                if(!(cd == BRCASE_STOP1 && va == 1))
                    sut =false;
                i2sprf("I2S Master[%d] \n",sut);
                if(sut)   
                     i2sm_SendData();
            } 
        }            
#endif  
#endif        
    }
    MCU_Sleep(20);
    Verify_SendCResult(BRCASE_RESULT,sut);
    return sut;
}


bool cmd_VerifyDualAppI2SCase5(uint32_t cmd, uint8_t *param_line,uint16_t len)
{
    bool sut = true;
    //uint32_t idx=0;
    //verify_SendCid(cmd,&idx);
    i2sprf("I2S Dual App case5 PAD Only TX\r\n");
    {
#if    defined(BR_MASTER) || defined(BR_SLAVE)
        I2S_InitInof_Type   I2S_InitStru;
        PADConfig_Type      PAG_InitStru;

        PAG_InitStru.set        = 0;
        PAG_InitStru.ie         = PAD_IE_ENABLE;
        PAG_InitStru.oen        = PAD_OEN_ENABLE;
        PAG_InitStru.ren        = PAD_REN_ENABLE;
        PAG_InitStru.pad_ctl    = PAD_MODE2;

        SystemPADConfig(PADID17,&PAG_InitStru);
        SystemPADConfig(PADID18,&PAG_InitStru);
        SystemPADConfig(PADID19,&PAG_InitStru);
//        SystemPADConfig(PADID20,&PAG_InitStru);
        
        I2S_InitStru.clock_gating_type      =  NO_CLOCK_GATING;
        I2S_InitStru.clock_type             =  CLOCK_CYCLES_32;
        I2S_InitStru.data_resl_type         =  RESOLUTION_32_BIT;
        I2S_InitStru.interrupt_level        =  TRIGGER_LEVEL_1;
        
#ifdef BR_SLAVE  
#ifdef BR_DUAL
        if(!GetSocRole())
#endif
        {
            I2S_InitStru.dirct_type= DATA_RX;
            I2S_InitStru.IntCtlMask.rx_dma_available_interrupt_mask     =  false;//Enable
            I2S_InitStru.IntCtlMask.rx_fifo_overrun_interrupt_mask      =  false;//Enable
            I2S_InitStru.IntCtlMask.tx_fifo_empty_interrupt_mask        =  true; //Disable
            I2S_InitStru.IntCtlMask.tx_fifo_overrun_interrupt_mask      =  false;//Enable
            
            SCU->IO_CONFIG &=~0x20;
            
            SystemDevClockCtl(I2SS_CKEn,true);
            
            I2S_Init(I2SS, &I2S_InitStru);
            NVIC_ClearPendingIRQ(I2SS_IRQn);
            NVIC_EnableIRQ(I2SS_IRQn);
            Verify_messageSend(BRCASE_STOP1,true);
            i2sprf("I2S slave\n"); 
        }            
#endif


#ifdef BR_MASTER 
#ifdef BR_DUAL
        if(GetSocRole())
#endif
        {
            I2S_InitStru.dirct_type= DATA_TX;
            I2S_InitStru.IntCtlMask.rx_dma_available_interrupt_mask     =  true;
            I2S_InitStru.IntCtlMask.rx_fifo_overrun_interrupt_mask      =  true;
            I2S_InitStru.IntCtlMask.tx_fifo_empty_interrupt_mask        =  true;
            I2S_InitStru.IntCtlMask.tx_fifo_overrun_interrupt_mask      =  true;

            SystemDevClockCtl(I2SM_CKEn,true);
            
            SCU->IO_CONFIG |=0x20;
            I2S_Init(I2SM, &I2S_InitStru);
            NVIC_ClearPendingIRQ(I2SM_IRQn);
            NVIC_EnableIRQ(I2SM_IRQn);
            {
                uint32_t cd=0,va=0;
                Verify_messageReceive(&cd,&va);
                if(!(cd == BRCASE_STOP1 && va == 1))
                    sut =false;
                i2sprf("I2S master[%d]\r\n",sut);
                if(sut)   
                     i2sm_SendData();
            }
        }
            
#endif      
#endif            
    }
    MCU_Sleep(20);
    Verify_SendCResult(BRCASE_RESULT,sut);
    return sut;
}

bool cmd_VerifyDualAppI2SCase6(uint32_t cmd, uint8_t *param_line,uint16_t len)
{
    bool sut = true;
    //uint32_t idx=0;
    //verify_SendCid(cmd,&idx);
    i2sprf("I2S Dual App case6 PAD Only RX\r\n");
    {
#if (defined(BR_MASTER) || defined(BR_SLAVE))
        I2S_InitInof_Type   I2S_InitStru;
        PADConfig_Type      PAG_InitStru;

        PAG_InitStru.set        = 0;
        PAG_InitStru.ie         = PAD_IE_ENABLE;
        PAG_InitStru.oen        = PAD_OEN_ENABLE;
        PAG_InitStru.ren        = PAD_REN_ENABLE;
        PAG_InitStru.pad_ctl    = PAD_MODE2;

        SystemPADConfig(PADID17,&PAG_InitStru);
        SystemPADConfig(PADID18,&PAG_InitStru);
//        SystemPADConfig(PADID19,&PAG_InitStru);
        SystemPADConfig(PADID20,&PAG_InitStru);
        
        I2S_InitStru.clock_gating_type      =  NO_CLOCK_GATING;
        I2S_InitStru.clock_type             =  CLOCK_CYCLES_32;
        I2S_InitStru.data_resl_type         =  RESOLUTION_32_BIT;
        I2S_InitStru.interrupt_level        =  TRIGGER_LEVEL_1;
        
#ifdef BR_SLAVE 
#ifdef BR_DUAL
        if(!GetSocRole())
#endif
        {
            I2S_InitStru.dirct_type= DATA_TX;
            I2S_InitStru.IntCtlMask.rx_dma_available_interrupt_mask     =  true;//Disable
            I2S_InitStru.IntCtlMask.rx_fifo_overrun_interrupt_mask      =  true;//Disable
            I2S_InitStru.IntCtlMask.tx_fifo_empty_interrupt_mask        =  true;//Disable
            I2S_InitStru.IntCtlMask.tx_fifo_overrun_interrupt_mask      =  true;//Disable
            
            SystemDevClockCtl(I2SS_CKEn,true);
            SCU->IO_CONFIG &=~0x20;
            I2S_Init(I2SS, &I2S_InitStru);
            NVIC_ClearPendingIRQ(I2SS_IRQn);
            NVIC_EnableIRQ(I2SS_IRQn);
            {
                uint32_t cd=0,va=0;
                Verify_messageReceive(&cd,&va);
                if(!(cd == BRCASE_STOP1 && va == 1))
                    sut =false;
                i2sprf("I2S slave[%d]\r\n",sut);
                if(sut)   
                     i2ss_SendData();
            }
            
            Verify_messageSend(BRCASE_STOP2,true);
        }
           
#endif


#ifdef BR_MASTER 
#ifdef BR_DUAL
        if(GetSocRole())
#endif
        {
            I2S_InitStru.dirct_type= DATA_RX;
            I2S_InitStru.IntCtlMask.rx_dma_available_interrupt_mask     =  false;
            I2S_InitStru.IntCtlMask.rx_fifo_overrun_interrupt_mask      =  false;
            I2S_InitStru.IntCtlMask.tx_fifo_empty_interrupt_mask        =  true;
            I2S_InitStru.IntCtlMask.tx_fifo_overrun_interrupt_mask      =  false;

            SystemDevClockCtl(I2SM_CKEn,true);
            SCU->IO_CONFIG |=0x20;
            I2S_Init(I2SM, &I2S_InitStru);
            NVIC_ClearPendingIRQ(I2SM_IRQn);
            NVIC_EnableIRQ(I2SM_IRQn);
            i2sprf("I2S Master\n");
            Verify_messageSend(BRCASE_STOP1,true);
            {
                uint32_t cd=0,va=0;
                Verify_messageReceive(&cd,&va);
                if(!(cd == BRCASE_STOP2 && va == 1))
                    sut =false;
                i2sprf("I2S master[%d]\r\n",sut);
                if(sut)   
                    I2S_GeneratrClock(I2SM,true);
            }
        }     
#endif 
#endif        
    }
    MCU_Sleep(20);
    Verify_SendCResult(BRCASE_RESULT,sut);
    return sut;
}

bool cmd_VerifyDualAppI2SCase7(uint32_t cmd, uint8_t *param_line,uint16_t len)
{
    bool sut = true;
    //uint32_t idx=0;
    //verify_SendCid(cmd,&idx);
    i2sprf("I2S Dual App case7 PAD Only TX\r\n");
    {
#if    defined(BR_MASTER) || defined(BR_SLAVE)
        I2S_InitInof_Type   I2S_InitStru;
        PADConfig_Type      PAG_InitStru;

        PAG_InitStru.set        = 0;
        PAG_InitStru.ie         = PAD_IE_ENABLE;
        PAG_InitStru.oen        = PAD_OEN_ENABLE;
        PAG_InitStru.ren        = PAD_REN_ENABLE;
        PAG_InitStru.pad_ctl    = PAD_MODE2;

        SystemPADConfig(PADID2,&PAG_InitStru);
        SystemPADConfig(PADID3,&PAG_InitStru);
        SystemPADConfig(PADID4,&PAG_InitStru);
//        SystemPADConfig(PADID5,&PAG_InitStru);
        
        I2S_InitStru.clock_gating_type      =  NO_CLOCK_GATING;
        I2S_InitStru.clock_type             =  CLOCK_CYCLES_32;
        I2S_InitStru.data_resl_type         =  RESOLUTION_32_BIT;
        I2S_InitStru.interrupt_level        =  TRIGGER_LEVEL_1;
        
#ifdef BR_SLAVE  
#ifdef BR_DUAL
        if(!GetSocRole())
#endif
        {
            I2S_InitStru.dirct_type= DATA_RX;
            I2S_InitStru.IntCtlMask.rx_dma_available_interrupt_mask     =  false;//Enable
            I2S_InitStru.IntCtlMask.rx_fifo_overrun_interrupt_mask      =  false;//Enable
            I2S_InitStru.IntCtlMask.tx_fifo_empty_interrupt_mask        =  true; //Disable
            I2S_InitStru.IntCtlMask.tx_fifo_overrun_interrupt_mask      =  false;//Enable
            
            SCU->IO_CONFIG &=~0x10;
            
            SystemDevClockCtl(I2SS_CKEn,true);
            
            I2S_Init(I2SS, &I2S_InitStru);
            NVIC_ClearPendingIRQ(I2SS_IRQn);
            NVIC_EnableIRQ(I2SS_IRQn);
            Verify_messageSend(BRCASE_STOP1,true);
            i2sprf("I2S slave\n"); 
        }            
#endif


#ifdef BR_MASTER 
#ifdef BR_DUAL
        if(GetSocRole())
#endif
        {
            I2S_InitStru.dirct_type= DATA_TX;
            I2S_InitStru.IntCtlMask.rx_dma_available_interrupt_mask     =  true;
            I2S_InitStru.IntCtlMask.rx_fifo_overrun_interrupt_mask      =  true;
            I2S_InitStru.IntCtlMask.tx_fifo_empty_interrupt_mask        =  true;
            I2S_InitStru.IntCtlMask.tx_fifo_overrun_interrupt_mask      =  true;

            SystemDevClockCtl(I2SM_CKEn,true);
            
            SCU->IO_CONFIG |=0x10;
            I2S_Init(I2SM, &I2S_InitStru);
            NVIC_ClearPendingIRQ(I2SM_IRQn);
            NVIC_EnableIRQ(I2SM_IRQn);
            {
                uint32_t cd=0,va=0;
                Verify_messageReceive(&cd,&va);
                if(!(cd == BRCASE_STOP1 && va == 1))
                    sut =false;
                i2sprf("I2S master[%d]\r\n",sut);
                if(sut)   
                     i2sm_SendData();
            }
        }
            
#endif      
#endif            
    }
    MCU_Sleep(20);
    Verify_SendCResult(BRCASE_RESULT,sut);
    return sut;
}

bool cmd_VerifyDualAppI2SCase8(uint32_t cmd, uint8_t *param_line,uint16_t len)
{
    bool sut = true;
    //uint32_t idx=0;
    //verify_SendCid(cmd,&idx);
    i2sprf("I2S Dual App case8 PAD Only RX\r\n");
    {
#if (defined(BR_MASTER) || defined(BR_SLAVE))
        I2S_InitInof_Type   I2S_InitStru;
        PADConfig_Type      PAG_InitStru;

        PAG_InitStru.set        = 0;
        PAG_InitStru.ie         = PAD_IE_ENABLE;
        PAG_InitStru.oen        = PAD_OEN_ENABLE;
        PAG_InitStru.ren        = PAD_REN_ENABLE;
        PAG_InitStru.pad_ctl    = PAD_MODE2;

        SystemPADConfig(PADID2,&PAG_InitStru);
        SystemPADConfig(PADID3,&PAG_InitStru);
//        SystemPADConfig(PADID4,&PAG_InitStru);
        SystemPADConfig(PADID5,&PAG_InitStru);
        
        I2S_InitStru.clock_gating_type      =  NO_CLOCK_GATING;
        I2S_InitStru.clock_type             =  CLOCK_CYCLES_32;
        I2S_InitStru.data_resl_type         =  RESOLUTION_32_BIT;
        I2S_InitStru.interrupt_level        =  TRIGGER_LEVEL_1;
        
#ifdef BR_SLAVE 
#ifdef BR_DUAL
        if(!GetSocRole())
#endif
        {
            I2S_InitStru.dirct_type= DATA_TX;
            I2S_InitStru.IntCtlMask.rx_dma_available_interrupt_mask     =  true;//Disable
            I2S_InitStru.IntCtlMask.rx_fifo_overrun_interrupt_mask      =  true;//Disable
            I2S_InitStru.IntCtlMask.tx_fifo_empty_interrupt_mask        =  true;//Disable
            I2S_InitStru.IntCtlMask.tx_fifo_overrun_interrupt_mask      =  true;//Disable
            
            SystemDevClockCtl(I2SS_CKEn,true);
            SCU->IO_CONFIG &=~0x10;
            I2S_Init(I2SS, &I2S_InitStru);
            NVIC_ClearPendingIRQ(I2SS_IRQn);
            NVIC_EnableIRQ(I2SS_IRQn);
            {
                uint32_t cd=0,va=0;
                Verify_messageReceive(&cd,&va);
                if(!(cd == BRCASE_STOP1 && va == 1))
                    sut =false;
                i2sprf("I2S slave[%d]\r\n",sut);
                if(sut)   
                     i2ss_SendData();
            }
            
            Verify_messageSend(BRCASE_STOP2,true);
        }
           
#endif


#ifdef BR_MASTER 
#ifdef BR_DUAL
        if(GetSocRole())
#endif
        {
            I2S_InitStru.dirct_type= DATA_RX;
            I2S_InitStru.IntCtlMask.rx_dma_available_interrupt_mask     =  false;
            I2S_InitStru.IntCtlMask.rx_fifo_overrun_interrupt_mask      =  false;
            I2S_InitStru.IntCtlMask.tx_fifo_empty_interrupt_mask        =  true;
            I2S_InitStru.IntCtlMask.tx_fifo_overrun_interrupt_mask      =  false;

            SystemDevClockCtl(I2SM_CKEn,true);
            SCU->IO_CONFIG |=0x10;
            I2S_Init(I2SM, &I2S_InitStru);
            NVIC_ClearPendingIRQ(I2SM_IRQn);
            NVIC_EnableIRQ(I2SM_IRQn);
            i2sprf("I2S Master\n");
            Verify_messageSend(BRCASE_STOP1,true);
            {
                uint32_t cd=0,va=0;
                Verify_messageReceive(&cd,&va);
                if(!(cd == BRCASE_STOP2 && va == 1))
                    sut =false;
                i2sprf("I2S master[%d]\r\n",sut);
                if(sut)   
                    I2S_GeneratrClock(I2SM,true);
            }
        }     
#endif 
#endif        
    }
    MCU_Sleep(20);
    Verify_SendCResult(BRCASE_RESULT,sut);
    return sut;
}

#include "BR00x_clock.h"
bool cmd_VerifyDualAppI2SCase9(uint32_t cmd, uint8_t *param_line,uint16_t len)
{
    bool sut = true;
    //uint32_t idx=0;
    //verify_SendCid(cmd,&idx);
    i2sprf("I2S Dual App case4 2-5 Pin i2s div2\r\n");
    SCU_I2SDiv(2);
    {
#if (defined(BR_MASTER) || defined(BR_SLAVE))
        I2S_InitInof_Type   I2S_InitStru;
        PADConfig_Type      PAG_InitStru;

        PAG_InitStru.set        = 0;
        PAG_InitStru.ie         = PAD_IE_ENABLE;
        PAG_InitStru.oen        = PAD_OEN_ENABLE;
        PAG_InitStru.ren        = PAD_REN_ENABLE;
        PAG_InitStru.pad_ctl    = PAD_MODE2;

        SystemPADConfig(PADID2,&PAG_InitStru);
        SystemPADConfig(PADID3,&PAG_InitStru);
        SystemPADConfig(PADID4,&PAG_InitStru);
        SystemPADConfig(PADID5,&PAG_InitStru);
        
        I2S_InitStru.clock_gating_type      =  NO_CLOCK_GATING;
        I2S_InitStru.clock_type             =  CLOCK_CYCLES_32;
        I2S_InitStru.data_resl_type         =  RESOLUTION_32_BIT;
        I2S_InitStru.interrupt_level        =  TRIGGER_LEVEL_1;
        
#ifdef BR_SLAVE  
#ifdef BR_DUAL
        if(!GetSocRole())
#endif
        {
            I2S_InitStru.dirct_type= DATA_TX_RX;
            I2S_InitStru.IntCtlMask.rx_dma_available_interrupt_mask     =  true;//Disable
            I2S_InitStru.IntCtlMask.rx_fifo_overrun_interrupt_mask      =  true;//Disable
            I2S_InitStru.IntCtlMask.tx_fifo_empty_interrupt_mask        =  true;//Disable
            I2S_InitStru.IntCtlMask.tx_fifo_overrun_interrupt_mask      =  true;//Disable
            
            SystemDevClockCtl(I2SS_CKEn,true);
            SCU->IO_CONFIG &=~0x10;
            I2S_Init(I2SS, &I2S_InitStru);
            NVIC_ClearPendingIRQ(I2SS_IRQn);
            NVIC_EnableIRQ(I2SS_IRQn);
            Verify_messageSend(BRCASE_STOP1,true);
            i2sprf("I2S slave idl\n");
            
            {
                uint32_t cd=0,va=0;
                Verify_messageReceive(&cd,&va);
                if(!(cd == BRCASE_STOP2 && va == 1))
                    sut =false;
                i2sprf("I2S slave[%d]\r\n",sut);
                if(sut)   
                     i2ss_SendData();
            }
        }
           
#endif


#ifdef BR_MASTER 
#ifdef BR_DUAL
        if(GetSocRole())
#endif
        {
            I2S_InitStru.dirct_type= DATA_TX_RX;
            I2S_InitStru.IntCtlMask.rx_dma_available_interrupt_mask     =  true;
            I2S_InitStru.IntCtlMask.rx_fifo_overrun_interrupt_mask      =  true;
            I2S_InitStru.IntCtlMask.tx_fifo_empty_interrupt_mask        =  true;
            I2S_InitStru.IntCtlMask.tx_fifo_overrun_interrupt_mask      =  true;

            SystemDevClockCtl(I2SM_CKEn,true);
            SCU->IO_CONFIG |=0x10;
            I2S_Init(I2SM, &I2S_InitStru);
            NVIC_ClearPendingIRQ(I2SM_IRQn);
            NVIC_EnableIRQ(I2SM_IRQn);
            
            Verify_messageSend(BRCASE_STOP2,true);
            i2sprf("I2S Master idl\n");  
            
            {
                uint32_t cd=0,va=0;
                Verify_messageReceive(&cd,&va);
                if(!(cd == BRCASE_STOP1 && va == 1))
                    sut =false;
                i2sprf("I2S Master[%d] \n",sut);
                if(sut)   
                     i2sm_SendData();
            } 
        }            
#endif  
#endif        
    }
    MCU_Sleep(20);
    Verify_SendCResult(BRCASE_RESULT,sut);
    return sut;
}


bool cmd_VerifyDualAppI2SCase10(uint32_t cmd, uint8_t *param_line,uint16_t len)
{
    bool sut = true;
    //uint32_t idx=0;
    //verify_SendCid(cmd,&idx);
    i2sprf("I2S Dual App case8 PAD Only RX i2s div2\r\n");
    SCU_I2SDiv(2);
    {
#if (defined(BR_MASTER) || defined(BR_SLAVE))
        I2S_InitInof_Type   I2S_InitStru;
        PADConfig_Type      PAG_InitStru;

        PAG_InitStru.set        = 0;
        PAG_InitStru.ie         = PAD_IE_ENABLE;
        PAG_InitStru.oen        = PAD_OEN_ENABLE;
        PAG_InitStru.ren        = PAD_REN_ENABLE;
        PAG_InitStru.pad_ctl    = PAD_MODE2;

        SystemPADConfig(PADID2,&PAG_InitStru);
        SystemPADConfig(PADID3,&PAG_InitStru);
//        SystemPADConfig(PADID4,&PAG_InitStru);
        SystemPADConfig(PADID5,&PAG_InitStru);
        
        I2S_InitStru.clock_gating_type      =  NO_CLOCK_GATING;
        I2S_InitStru.clock_type             =  CLOCK_CYCLES_32;
        I2S_InitStru.data_resl_type         =  RESOLUTION_32_BIT;
        I2S_InitStru.interrupt_level        =  TRIGGER_LEVEL_1;
        
#ifdef BR_SLAVE 
#ifdef BR_DUAL
        if(!GetSocRole())
#endif
        {
            I2S_InitStru.dirct_type= DATA_TX;
            I2S_InitStru.IntCtlMask.rx_dma_available_interrupt_mask     =  true;//Disable
            I2S_InitStru.IntCtlMask.rx_fifo_overrun_interrupt_mask      =  true;//Disable
            I2S_InitStru.IntCtlMask.tx_fifo_empty_interrupt_mask        =  true;//Disable
            I2S_InitStru.IntCtlMask.tx_fifo_overrun_interrupt_mask      =  true;//Disable
            
            SystemDevClockCtl(I2SS_CKEn,true);
            SCU->IO_CONFIG &=~0x10;
            I2S_Init(I2SS, &I2S_InitStru);
            NVIC_ClearPendingIRQ(I2SS_IRQn);
            NVIC_EnableIRQ(I2SS_IRQn);
            {
                uint32_t cd=0,va=0;
                Verify_messageReceive(&cd,&va);
                if(!(cd == BRCASE_STOP1 && va == 1))
                    sut =false;
                i2sprf("I2S slave[%d]\r\n",sut);
                if(sut)   
                     i2ss_SendData();
            }
            
            Verify_messageSend(BRCASE_STOP2,true);
        }
           
#endif


#ifdef BR_MASTER 
#ifdef BR_DUAL
        if(GetSocRole())
#endif
        {
            I2S_InitStru.dirct_type= DATA_RX;
            I2S_InitStru.IntCtlMask.rx_dma_available_interrupt_mask     =  false;
            I2S_InitStru.IntCtlMask.rx_fifo_overrun_interrupt_mask      =  false;
            I2S_InitStru.IntCtlMask.tx_fifo_empty_interrupt_mask        =  true;
            I2S_InitStru.IntCtlMask.tx_fifo_overrun_interrupt_mask      =  false;

            SystemDevClockCtl(I2SM_CKEn,true);
            SCU->IO_CONFIG |=0x10;
            I2S_Init(I2SM, &I2S_InitStru);
            NVIC_ClearPendingIRQ(I2SM_IRQn);
            NVIC_EnableIRQ(I2SM_IRQn);
            i2sprf("I2S Master\n");
            Verify_messageSend(BRCASE_STOP1,true);
            {
                uint32_t cd=0,va=0;
                Verify_messageReceive(&cd,&va);
                if(!(cd == BRCASE_STOP2 && va == 1))
                    sut =false;
                i2sprf("I2S master[%d]\r\n",sut);
                if(sut)   
                    I2S_GeneratrClock(I2SM,true);
            }
        }     
#endif 
#endif        
    }
    MCU_Sleep(20);
    Verify_SendCResult(BRCASE_RESULT,sut);
    return sut;
}



void I2SM_IRQHandler(void)      
{     
  
    i2sprf("I2SM_IRQ\n"); 

    if( I2S_GetInterruptStatus(I2SM,I2S_RX_AVAILABLE_DAM))
    {
        i2sprf("MRX_ADAM r[%X],l[%X]\n",\
            I2S_GetRightReceiveData(I2SM),\
            I2S_GetLeftReceiveData(I2SM));
    }
    if( I2S_GetInterruptStatus(I2SM,I2S_RX_FIFO_OVERRUN))
    {
        I2S_ClearRxOverrunInterrupt(I2SM);
        i2sprf("RX_OVERRUN\r\n");
    }
    if( I2S_GetInterruptStatus(I2SM,I2S_TX_FIFO_EMPTY))
    {
        {
            I2S_IntCtlMask  IntCtlMask;

            IntCtlMask.rx_dma_available_interrupt_mask    =  false;
            IntCtlMask.rx_fifo_overrun_interrupt_mask     =  true;
            IntCtlMask.tx_fifo_empty_interrupt_mask       =  true;
            IntCtlMask.tx_fifo_overrun_interrupt_mask     =  true;
            I2S_SetInterruptMask(I2SM,&IntCtlMask);

        }
        I2S_GeneratrClock(I2SM,false);
        //i2sm_SendData();
        i2sprf("TX_EMPTY\r\n");
    }
    if( I2S_GetInterruptStatus(I2SM,I2S_TX_FIFO_OVERRUN))
    {
        I2S_ClearTxOverrunInterrupt(I2SM);
        i2sprf("TX_OVERRUN\r\n");
        I2S_GeneratrClock(I2SM,false);
    }
}    




void I2SS_IRQHandler(void)      
{     
    i2sprf("I2SS_IRQ\n"); 
    if( I2S_GetInterruptStatus(I2SS,I2S_RX_AVAILABLE_DAM))
    {
        i2sprf("SRX_ADAM r[%X],l[%X]\n",\
            I2S_GetRightReceiveData(I2SS),\
            I2S_GetLeftReceiveData(I2SS));       
    }
    if( I2S_GetInterruptStatus(I2SS,I2S_RX_FIFO_OVERRUN))
    {
        I2S_ClearRxOverrunInterrupt(I2SS);
        i2sprf("RX_OVERRUN\r\n");
    }
    if( I2S_GetInterruptStatus(I2SS,I2S_TX_FIFO_EMPTY))
    {
        {
            I2S_IntCtlMask  IntCtlMask;
            IntCtlMask.rx_dma_available_interrupt_mask    =  false;
            IntCtlMask.rx_fifo_overrun_interrupt_mask     =  true;
            IntCtlMask.tx_fifo_empty_interrupt_mask       =  true;
            IntCtlMask.tx_fifo_overrun_interrupt_mask     =  true;
            I2S_SetInterruptMask(I2SS,&IntCtlMask);

        }
        i2sprf("TX_EMPTY\r\n");
    }
    if( I2S_GetInterruptStatus(I2SS,I2S_TX_FIFO_OVERRUN))
    {
        I2S_ClearTxOverrunInterrupt(I2SS);
        i2sprf("TX_OVERRUN\r\n");
    }
   
}   




