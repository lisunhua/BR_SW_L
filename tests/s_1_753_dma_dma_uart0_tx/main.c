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

#include "BR00x_dma.h"
#include "BR00x_uart.h"
#include "BR00x_ssi.h"
#include "BR00x_ssic.h"



uint8_t DMA_UART_Tx_data[50] = {'1','2','3','4','5','6','7','8','9','\n',\
                                '1','2','3','4','5','6','7','8','9','\n',\
                                '1','2','3','4','5','6','7','8','9','\n',\
                                '1','2','3','4','5','6','7','8','9','\n',\
                                '1','2','3','4','5','6','7','8','9','\n'};

uint8_t DMA_UART_Rx_data[50] = {0};
static  uint8_t dmaUartBlockFlag = 0;


int main (void)
{
    bool sut = true;
    DMA_ChNum_Type UART0_tx_ch = DMA_CH_1;

    sysTimeUpdataClk(SystemCoreClock);
    SystemDevClockCtl(DMA_CKEn,true);
    Verrify_SendPinConnect(UART0_OUTPUT);
    LOGUartInit();
    c_printf("s_1_753_dma_dma_uart0_tx case \r\n");

    for(UART0_tx_ch = DMA_CH_0;UART0_tx_ch<DMA_CH_END; UART0_tx_ch++)
    {

        DMA_InitInfo_Type DMA_InitStru;

        memset(&DMA_InitStru,0,sizeof(DMA_InitInfo_Type));     
        /* dma rx*/

        DMA_InitStru.src_addr       = (uint32_t)DMA_UART_Tx_data;
        DMA_InitStru.dst_addr       = (uint32_t)&UART0->THR;
        DMA_InitStru.block_size     = 50;
        DMA_InitStru.src_llp_en     = DISABLE;
        DMA_InitStru.dst_llp_en     = DISABLE;
        DMA_InitStru.tt_tc_mode     = DMA_TT_M2P_TC_D;
        DMA_InitStru.src_msize      = DMA_MSIZE_4;
        DMA_InitStru.dst_msize      = DMA_MSIZE_4;
        DMA_InitStru.src_inc_mode   = DMA_IM_INC;
        DMA_InitStru.dst_inc_mode   = DMA_IM_NO_CHANGE_0 ;

        DMA_InitStru.src_trans_w    = DMA_TW_8;
        DMA_InitStru.dst_trans_w    = DMA_TW_8;
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
        DMA_InitStru.dst_per        = (DMA_HardInterface_Type)0;
        DMA_InitStru.src_per        = (DMA_HardInterface_Type)0;

        DMA_EnableCh(UART0_tx_ch,DISABLE);
        DMA_Enable(DISABLE);
        DMA_Init(UART0_tx_ch,&DMA_InitStru);
        
        DMA_Enable(ENABLE);
        DMA_SetIntMask(UART0_tx_ch,DMA_IT_TFR,SET);    
        DMA_SetIntMask(UART0_tx_ch,DMA_IT_BLOCK,SET);   
        DMA_SetIntMask(UART0_tx_ch,DMA_IT_SRCTRAN,SET); 
        DMA_SetIntMask(UART0_tx_ch,DMA_IT_DSTTRAN,SET); 
        DMA_SetIntMask(UART0_tx_ch,DMA_IT_ERR,SET);     
               
        NVIC_ClearPendingIRQ(DMA_IRQn);
        NVIC_EnableIRQ(DMA_IRQn);
        
        dmaUartBlockFlag=3;
        DMA_EnableCh(UART0_tx_ch,ENABLE);
        c_printf("DMA tx[%d] En\n",UART0_tx_ch);
        while(dmaUartBlockFlag);

    }
    c_printf("s_1_753_dma_dma_uart0_tx case completed \r\n");
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
                // if(IntType ==DMA_IT_DSTTRAN)
                //     dma_Int_Flag=0;
               
                if(IntType ==DMA_IT_BLOCK)
                    dmaUartBlockFlag=0;
                
                // if(IntType ==DMA_IT_DSTTRAN)
                //     dmaUartDstFlag=0;
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

















