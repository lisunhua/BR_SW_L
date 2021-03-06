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
#include "BR00x_dma.h"
#include "BR00x_ssi_common.h"
#include "BR00x_ssi.h"
#include "BR00x_ssic.h"
#include "BR00x_config.h"
#include "verify_message.h"
#include "log_uart_config.h"


uint8_t DMA_UART_Tx_data[50] = {'1','2','3','4','5','6','7','8','9','\n',\
                                '1','2','3','4','5','6','7','8','9','\n',\
                                '1','2','3','4','5','6','7','8','9','\n',\
                                '1','2','3','4','5','6','7','8','9','\n',\
                                '1','2','3','4','5','6','7','8','9','\n'};

uint8_t DMA_UART_Rx_data[50] = {0};


uint16_t DMA_UART_Tx_data16[50]={'1','2','3','4','5','6','7','8','9','\n',\
                                 '1','2','3','4','5','6','7','8','9','\n',\
                                 '1','2','3','4','5','6','7','8','9','\n',\
                                 '1','2','3','4','5','6','7','8','9','\n',\
                                 '1','2','3','4','5','6','7','8','9','\n'};

uint16_t DMA_UART_Rx_data16[50] = {0};

uint32_t DMA_UART_Tx_data32[50]={'1','2','3','4','5','6','7','8','9','\n',\
                                 '1','2','3','4','5','6','7','8','9','\n',\
                                 '1','2','3','4','5','6','7','8','9','\n',\
                                 '1','2','3','4','5','6','7','8','9','\n',\
                                 '1','2','3','4','5','6','7','8','9','\n'};

uint32_t DMA_UART_Rx_data32[50] = {0};

uint8_t Tx_data[50] = {9,0,2,3,4,6,3,5,67,8,2,2,4,6,4,6,67,78,2};
uint8_t Rx_data[50] = {0};
uint8_t dma_Int_Flag =1;


static  uint8_t dmaUartDstFlag = 0;
static  uint8_t dmaUartBlockFlag = 0;

// bool GetStepIsOk(verify_caseCmd_type step)
// {
//     uint32_t cd=0,va=0;
//     Verify_messageReceive(&cd,&va);
//     if(!(cd == step && va == 1))
//         return false;
//     else
//         return true;
// }

bool GetStepIsOk(verify_caseCmd_type step)
{
    uint32_t cd=0,va=0;
SPIISOK_TEST: 
        Verify_messageGetRData(&cd,&va);
    // Verify_messageReceive(&cd,&va);
    if(!(cd == step && va == 1))
        // return false;
        goto SPIISOK_TEST;
    else
        return true;
}

void DMA_SendDataHandle(uint32_t dst,DMA_ChNum_Type tx_ch,uint16_t ack_ch)
{
        DMA_InitInfo_Type DMA_InitStru;
        memset(&DMA_InitStru,0,sizeof(DMA_InitInfo_Type));     
        /* dma rx*/
        c_printf("DMA tx ch[%d],ack[%x]\n",tx_ch,ack_ch);
    
        if(ack_ch == 2)
            DMA_InitStru.src_addr       = (uint32_t)DMA_UART_Tx_data32;
        else
            DMA_InitStru.src_addr       = (uint32_t)DMA_UART_Tx_data16;
        
        DMA_InitStru.dst_addr       = dst;
        DMA_InitStru.block_size     = 20;
        DMA_InitStru.src_llp_en     = DISABLE;
        DMA_InitStru.dst_llp_en     = DISABLE;
        DMA_InitStru.tt_tc_mode     = DMA_TT_M2P_TC_D;
        DMA_InitStru.src_msize      = DMA_MSIZE_4;
        DMA_InitStru.dst_msize      = DMA_MSIZE_4;
        DMA_InitStru.src_inc_mode   = DMA_IM_INC;
        DMA_InitStru.dst_inc_mode   = DMA_IM_NO_CHANGE_0 ;

        if(ack_ch == 2)
        {
            DMA_InitStru.src_trans_w    = DMA_TW_32;
            DMA_InitStru.dst_trans_w    = DMA_TW_32;
        }
        else
        {
            DMA_InitStru.src_trans_w    = DMA_TW_16;
            DMA_InitStru.dst_trans_w    = DMA_TW_16;
        }
        DMA_InitStru.int_en         = ENABLE;   
        DMA_InitStru.fifo_mode      = DMA_FM_MODE_0;
        DMA_InitStru.fc_mode        = DMA_FC_MODE_0;
        DMA_InitStru.src_reload_en  = DISABLE;
        DMA_InitStru.dst_reload_en  = DISABLE;
        DMA_InitStru.max_abrst      = 100;

        DMA_InitStru.src_hs_pol     = DMA_HP_ACTIVE_HIGH;
        DMA_InitStru.dst_hs_pol     = DMA_HP_ACTIVE_HIGH;
        DMA_InitStru.src_hs_sel     = DMA_HS_HARDWARE;
        DMA_InitStru.dst_hs_sel     = DMA_HS_HARDWARE;  
        DMA_InitStru.ch_suspend     = DISABLE;
        DMA_InitStru.ch_priority    = DMA_CP_PRIOR_3;
        DMA_InitStru.dst_per        = (DMA_HardInterface_Type)ack_ch;
        DMA_InitStru.src_per        = (DMA_HardInterface_Type)ack_ch;

        if(tx_ch!=DMA_CH_0)
            DMA_EnableCh((DMA_ChNum_Type)(tx_ch-1),DISABLE);
        
        DMA_Enable(DISABLE);
        DMA_Init(tx_ch,&DMA_InitStru);

        DMA_Enable(ENABLE);
        DMA_SetIntMask(tx_ch,DMA_IT_TFR,SET);
        DMA_SetIntMask(tx_ch,DMA_IT_BLOCK,SET);
        DMA_SetIntMask(tx_ch,DMA_IT_SRCTRAN,SET);
        DMA_SetIntMask(tx_ch,DMA_IT_DSTTRAN,SET);
        DMA_SetIntMask(tx_ch,DMA_IT_ERR,SET);    
               
        NVIC_ClearPendingIRQ(DMA_IRQn);
        NVIC_EnableIRQ(DMA_IRQn);
        
        dmaUartBlockFlag=3;
        DMA_EnableCh(tx_ch,ENABLE);
        c_printf("DMA tx[%d] En\n",tx_ch);
        while(dmaUartBlockFlag);
}

void DMA_ReceiveDataHandle(uint32_t src,DMA_ChNum_Type rx_ch,uint16_t ack_ch,verify_caseCmd_type step)
{
        DMA_InitInfo_Type DMA_InitStru;
        memset(&DMA_InitStru,0,sizeof(DMA_InitInfo_Type));   
        /* dma rx*/
        c_printf("DMA rx ch[%d],ack[%x]\n",rx_ch,ack_ch);
        DMA_InitStru.src_addr       = src;
        DMA_InitStru.dst_addr       = (uint32_t)DMA_UART_Rx_data16;
        DMA_InitStru.block_size     = 50;
        DMA_InitStru.src_llp_en     = DISABLE;
        DMA_InitStru.dst_llp_en     = DISABLE;
        DMA_InitStru.tt_tc_mode     = DMA_TT_P2M_TC_P;
        DMA_InitStru.src_msize      = DMA_MSIZE_1;
        DMA_InitStru.dst_msize      = DMA_MSIZE_1;
        DMA_InitStru.src_inc_mode   = DMA_IM_NO_CHANGE_0;
        DMA_InitStru.dst_inc_mode   = DMA_IM_INC;

        DMA_InitStru.src_trans_w    = DMA_TW_16;
        DMA_InitStru.dst_trans_w    = DMA_TW_16;
        DMA_InitStru.int_en         = ENABLE;   
        DMA_InitStru.fifo_mode      = DMA_FM_MODE_0;
        DMA_InitStru.fc_mode        = DMA_FC_MODE_0;
        DMA_InitStru.src_reload_en  = DISABLE;
        DMA_InitStru.dst_reload_en  = DISABLE;
        DMA_InitStru.max_abrst      = 0;

        DMA_InitStru.src_hs_pol     = DMA_HP_ACTIVE_HIGH;
        DMA_InitStru.dst_hs_pol     = DMA_HP_ACTIVE_HIGH;
        DMA_InitStru.src_hs_sel     = DMA_HS_HARDWARE;
        DMA_InitStru.dst_hs_sel     = DMA_HS_HARDWARE;  
        DMA_InitStru.ch_suspend     = DISABLE;
        DMA_InitStru.ch_priority    = DMA_CP_PRIOR_3;
        DMA_InitStru.dst_per        = (DMA_HardInterface_Type)ack_ch;
        DMA_InitStru.src_per        = (DMA_HardInterface_Type)ack_ch;

        DMA_Enable(DISABLE);
        DMA_Init(rx_ch,&DMA_InitStru);
        DMA_SetIntMask(rx_ch,DMA_IT_TFR,SET);   
        DMA_SetIntMask(rx_ch,DMA_IT_BLOCK,SET);  
        DMA_SetIntMask(rx_ch,DMA_IT_SRCTRAN,SET);
        DMA_SetIntMask(rx_ch,DMA_IT_DSTTRAN,SET);
        DMA_SetIntMask(rx_ch,DMA_IT_ERR,SET);   

        DMA_Enable(ENABLE);
        NVIC_ClearPendingIRQ(DMA_IRQn);
        NVIC_EnableIRQ(DMA_IRQn);
        DMA_EnableCh(rx_ch,ENABLE);
        c_printf("DMA[%d]En\n",rx_ch);
        
        if(ack_ch == 5)
        {
             uint32_t data[1]; /* Start Spim1 Read*/
             SSI_SendData32(SPIM1,data,1); 
        }
        
        if(ack_ch == 3)
        {
             uint32_t data[1]; /* Start Spim1 Read*/
             SSI_SendData32(SPIM0,data,1); 
        }
        
        Verify_messageSend(step ,true); 
        while(DMA_UART_Rx_data16[19] != '\n'); 
        
        for(uint16_t idx =0 ;idx<20;idx++)
            DMA_UART_Rx_data[idx] =DMA_UART_Rx_data16[idx];
        
        UART_WriteData(UART0,DMA_UART_Rx_data,20); c_printf("|\n");
        memset(DMA_UART_Rx_data,0,30);
        memset(DMA_UART_Rx_data16,0,sizeof(DMA_UART_Rx_data16));
        DMA_EnableCh(rx_ch,DISABLE);
}





int main (void)
{
    LOGUartInit();
    sysTimeUpdataClk(SystemCoreClock);
    Verrify_SendPinConnect(UART0_OUTPUT);
    VerifyDualGetRoleHandler();
    c_printf("d_1_753_dma_dam_spis1_to_spim1_to_spis1_8_ch_data_16bit case \r\n");
    SystemDevClockCtl(DMA_CKEn,true);
    SystemDevClockCtl(SPIM1_CKEn,true);
    SystemDevClockCtl(SPIM0_CKEn,true);
    SystemDevClockCtl(SPIS1_CKEn,true);
    MCU_Sleep(1);
    Verrify_SendPinConnect(DUAL_SPI0TO1_PIN_EN);

    {
    SCU->SEND_DATA = 0xe002;
#if (defined(BR_MASTER) || defined(BR_SLAVE))
#ifdef BR_MASTER 
#ifdef BR_DUAL
        if(GetSocRole())
#endif  
        {        
            SSIC_InitInfo_Type  SSIC_InitStru ;
            PADConfig_Type      PAD_InitStru;

            memset(&PAD_InitStru ,0,sizeof(PADConfig_Type));
            PAD_InitStru.pad_ctl = PAD_MODE0;
            SystemPADConfig(PADID29,&PAD_InitStru);
            SystemPADConfig(PADID30,&PAD_InitStru);
            SystemPADConfig(PADID31,&PAD_InitStru);
            SystemPADConfig(PADID32,&PAD_InitStru);

            SCUQspiConfig(QSPI_PIN29,QSPI_CLK);
            SCUQspiConfig(QSPI_PIN30,QSPI_CS);
            SCUQspiConfig(QSPI_PIN31,QSPI_D0);
            SCUQspiConfig(QSPI_PIN32,QSPI_D1);
            SCUQspiConfig(QSPI_PIN33,QSPI_D2);
            SCUQspiConfig(QSPI_PIN34,QSPI_D3);

            memset(&SSIC_InitStru,0,sizeof(SSIC_InitInfo_Type));

            SSIC_InitStru.clock_divider             =  0x10;
            SSIC_InitStru.frame_format_size         =  SSI_DATA_FRAME_SIZE_16BIT;
            SSIC_InitStru.ssi_frame_format          =  SSI_FRAME_FORMAT_MOTOROLA_SPI ;
            SSIC_InitStru.clock_phase               =  SSI_CLOCK_TOGGLES_MIDDLE ;
            SSIC_InitStru.clock_polarity            =  SSI_INACTIVE_STATE_LOW;
            SSIC_InitStru.transfer_mode             =  SSI_ONLY_RECEIVE;
            SSIC_InitStru.slave_output_enable       =  SSI_SLAVE_TXD_IS_ENABLE;
            SSIC_InitStru.operation_mode            =  SSI_NORMAL_MODE ;
            SSIC_InitStru.slave_select_toggle_en    =  SSIC_SLAVE_SELECT_TOHHLE_DISABLE;
            SSIC_InitStru.control_farme_size        =  SSI_CONTROL_FRAME_1BIT_WORD;
            SSIC_InitStru.spi_frame_format          =  STANDARD_SPI_FORMAT;
            SSIC_InitStru.spi_hyperbus_en           =  SSIC_SPI_HYPERBUS_DISABLE;

            SSIC_InitStru.slaves_select             = 1 ;
            SSIC_InitStru.tx_fifo_threshold_level   = 3;
            SSIC_InitStru.tx_fifo_start_fifo_level  = 0;
            SSIC_InitStru.rx_fifo_threshold_level   = 3;
            
            SSIC_InitStru.dma_rx_en                 = 1;
            SSIC_InitStru.dma_tx_en                 = 1;
            SSIC_InitStru.dma_rx_data_level         = 0;
            SSIC_InitStru.dma_tx_data_level         = 0;
            
            SSIC_InitStru.data_frames_number        = 20-1;
            SSIC_InitStru.unmask_interrupt          =FIFO_MASK_ALL;
           
            c_printf("SPIM0 Ok\n");     
            {
                DMA_ChNum_Type ch = DMA_CH_0;
                verify_caseCmd_type step = BRCASE_STOP1;
                for(ch = DMA_CH_0;ch<DMA_CH_END; ch++) 
                {
                    while(!GetStepIsOk(step)){};
                    {
                       SSIC_Init(&SSIC_InitStru);
                       DMA_ReceiveDataHandle((uint32_t)SPIM0->DR,ch,3,step);
                    } 
                    step++;
                }            
            }   
        }
        
         
#endif

#ifdef BR_SLAVE 
#ifdef BR_DUAL
        if(!GetSocRole())
#endif          
        {
            SSI_InitInof_Type   SSI_InitStru ;
            PADConfig_Type PAG_InitStru;

            memset(&PAG_InitStru ,0,sizeof(PADConfig_Type));
            memset(&SSI_InitStru ,0,sizeof(SSI_InitInof_Type));
      
            PAG_InitStru.pad_ctl    = PAD_MODE2;
            SystemPADConfig(PADID11,&PAG_InitStru);
            SystemPADConfig(PADID12,&PAG_InitStru);
            SystemPADConfig(PADID13,&PAG_InitStru);
            SystemPADConfig(PADID14,&PAG_InitStru);
            
            SSI_InitStru.clock_divider          = 0x10;
            SSI_InitStru.SSI_frame_format       = SSI_FRAME_FORMAT_MOTOROLA_SPI;
            SSI_InitStru.clock_phase            = SSI_CLOCK_TOGGLES_MIDDLE;
            SSI_InitStru.clock_polarity         = SSI_INACTIVE_STATE_LOW;
            SSI_InitStru.slave_output_enable    = SSI_SLAVE_TXD_IS_DISABLE;
            SSI_InitStru.operation_mode         = SSI_NORMAL_MODE;
            SSI_InitStru.control_farme_size     = SSI_CONTROL_FRAME_1BIT_WORD;
            SSI_InitStru.frame_format_size_16   = SSI_DATA_FRAME_SIZE_16BIT;
            //SSI_InitStru.frame_format_size_32   = SSI_DATA_FRAME_SIZE_32BIT;
            SSI_InitStru.spi_frame_format       = STANDARD_SPI_FORMAT;
            SSI_InitStru.unmask_interrupt       = RX_FIFO_FULL_UNMASK; 
            
            SSI_InitStru.tx_fifo_threshold_level    = 3;
            SSI_InitStru.tx_fifo_start_fifo_level   = 0;
            SSI_InitStru.rx_fifo_threshold_level    = 3;
            
            SSI_InitStru.dma_tx_en              = 1;
            SSI_InitStru.dma_rx_en              = 1;
            
            SSI_InitStru.dma_tx_data_level      = 3;
            SSI_InitStru.dma_rx_data_level      = 3;
            SSI_InitStru.data_frame_num         = 0;
                                       
            SSI_InitStru.transfer_mode          = SSI_ONLY_TRANSMIT;   

            SSI_Init(SPIS1 ,&SSI_InitStru);
            {
                DMA_ChNum_Type ch = DMA_CH_0;
                verify_caseCmd_type step = BRCASE_STOP1;
                for(ch = DMA_CH_0;ch<DMA_CH_END; ch++) 
                {
                    c_printf("SPIS Send:");
                    Verify_messageSend(step,true); step++;
                    DMA_SendDataHandle((uint32_t)SPIS1->DR,ch,6);
                                    
                }
            }
        }
#endif      
#endif 
    }
    c_printf("d_1_753_dma_dam_spis1_to_spim1_to_spis1_8_ch_data_16bit case \r\n");
	MCU_Sleep(3);
    SimulationEnd();
    while(1){     
    };
}


void DMA_IRQHandler(void)       
{    
    //c_printf("DMA_IRQ\r\n");
    DMA_ChNum_Type ChNum = DMA_CH_0;
    DMA_IntType_Type IntType = DMA_IT_TFR;
    
    for(ChNum =DMA_CH_0;ChNum<DMA_CH_END; ChNum++)
    {
        for(IntType = DMA_IT_TFR ; IntType <= DMA_IT_ERR ;IntType++)
        {
            if(DMA_GetIntStatus(ChNum,IntType))
            {
                DMA_ClearInt(ChNum,IntType);
                if(IntType ==DMA_IT_DSTTRAN)
                    dma_Int_Flag=0;
               
                if(IntType ==DMA_IT_BLOCK)
                    dmaUartBlockFlag=0;
                
                if(IntType ==DMA_IT_DSTTRAN)
                    dmaUartDstFlag=0;
#ifdef BR_SLAVE  
#ifdef BR_DUAL
        if(!GetSocRole())
#endif  
                c_printf("SD:[%d],t:[%d]\n",ChNum,IntType);
#endif
#ifdef BR_MASTER 
#ifdef BR_DUAL
        if(GetSocRole())
#endif  
                c_printf("MD:[%d],t:[%d]\n",ChNum,IntType);
#endif

#if  !(defined(BR_SLAVE) ||  defined(BR_MASTER))              
                c_printf("D:[%d],t:[%d]\n",ChNum,IntType);
#endif
            }
        }
    }
}     




















