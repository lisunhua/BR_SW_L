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

uint8_t Tx_data[50] = {9,0,2,3,4,6,3,5,67,8,2,2,4,6,4,6,67,78,2};
uint8_t Rx_data[50] = {0};
uint8_t dma_Int_Flag =1;


int main (void)
{
    bool sut = true;
    sysTimeUpdataClk(SystemCoreClock);
    SystemDevClockCtl(DMA_CKEn,true);
    Verrify_SendPinConnect(UART0_OUTPUT);
    LOGUartInit();
    c_printf("s_1_752_dma_dma_mem_traverse_parameter case \r\n");
    {

        DMA_InitInfo_Type DMA_InitStru;

        memset(&DMA_InitStru,0,sizeof(DMA_InitInfo_Type));
        
        c_printf("dma test mem to mem  S=[%p],D=[%p]\r\n",Tx_data,Rx_data);
  
        DMA_InitStru.src_addr       = (uint32_t)Tx_data;
        DMA_InitStru.dst_addr       = (uint32_t)Rx_data;
        DMA_InitStru.block_size     = 50;
        DMA_InitStru.src_llp_en     = ENABLE;
        DMA_InitStru.dst_llp_en     = ENABLE;
        DMA_InitStru.tt_tc_mode     = DMA_TT_M2M_TC_D;
        
        DMA_InitStru.src_inc_mode   = DMA_IM_INC;
        DMA_InitStru.dst_inc_mode   = DMA_IM_INC;   
        DMA_InitStru.int_en         = ENABLE;
        
        
        DMA_InitStru.src_reload_en  = DISABLE;
        DMA_InitStru.dst_reload_en  = DISABLE;
        DMA_InitStru.max_abrst      = 100;

        DMA_InitStru.src_hs_pol     = DMA_HP_ACTIVE_HIGH;
        DMA_InitStru.dst_hs_pol     = DMA_HP_ACTIVE_HIGH;
        DMA_InitStru.src_hs_sel     = DMA_HS_HARDWARE;
        DMA_InitStru.dst_hs_sel     = DMA_HS_HARDWARE;  
        DMA_InitStru.ch_suspend     = DISABLE;
        DMA_InitStru.ch_priority    = DMA_CP_PRIOR_0;

       // SystemDevClockCtl(DMA_CKEn, ENABLE);
        
        for(uint16_t i=0;i<20;i++)
            Tx_data[i] = i;
            
        for(DMA_FifoMode_Type fm = DMA_FM_MODE_0;fm<=DMA_FC_MODE_1;fm++)
        {
            DMA_InitStru.fifo_mode      = fm;
        for(DMA_FCMode_Type fc = DMA_FC_MODE_0;fc<=DMA_FC_MODE_1;fc++)
        {
            DMA_InitStru.fc_mode        = fc;
        for(DMA_ChPriority_Type cpp = DMA_CP_PRIOR_0;cpp<=DMA_CP_PRIOR_7;cpp++)
        {
            DMA_InitStru.ch_priority    = cpp;
        
        for(DMA_MSize_Type ms = DMA_MSIZE_1;ms<=DMA_MSIZE_32;ms++)
        {
            DMA_InitStru.src_msize      = ms;
            DMA_InitStru.dst_msize      = ms;
            for(DMA_TransWidth_Type tw = DMA_TW_8;tw<=DMA_TW_32;tw++)
            {
                DMA_InitStru.src_trans_w    = DMA_TW_8;
                DMA_InitStru.dst_trans_w    = DMA_TW_8;
                
                for(DMA_ChNum_Type ch = DMA_CH_0;ch<DMA_CH_END;ch++)
                {
                    dma_Int_Flag++;
                    DMA_Enable(DISABLE);
                    DMA_Init(ch,&DMA_InitStru);
                    DMA_SetIntMask(ch,DMA_IT_TFR,SET);     
                    DMA_SetIntMask(ch,DMA_IT_BLOCK,SET);   
                    DMA_SetIntMask(ch,DMA_IT_SRCTRAN,SET); 
                    DMA_SetIntMask(ch,DMA_IT_DSTTRAN,SET); 
                    DMA_SetIntMask(ch,DMA_IT_ERR,SET);    
                    DMA_Enable(ENABLE);
                    DMA_EnableCh(ch,ENABLE);
                    NVIC_EnableIRQ(DMA_IRQn);
                    while(dma_Int_Flag);
                    
                    for(uint16_t i=0;i<20;i++)
                        if(Rx_data[i] != i)
                            sut=false;
                            
                    memset(Rx_data,0,20);
                    c_printf("DMA Start stf [%d]\r\n",sut);
                }
            }
        }}}}


    }
    c_printf("s_1_752_dma_dma_mem_traverse_parameter case completed \r\n");
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
               
                // if(IntType ==DMA_IT_BLOCK)
                //     dmaUartBlockFlag=0;
                
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

















