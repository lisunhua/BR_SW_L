/*
 *++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 * Copyright (c) 1999-2018 Barrot Technology Limited
 *
 * All rights reserved.
 *
 *------------------------------------------------------------------------------
 */
/**
 * @file verify_slave_dma.c
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
#include "verify_slave_dma.h"
#include "verify_message.h"
#include "verify_register_handle.h"

#include "BR00x_config.h"
#include "BR00x_dma.h"
#include "BR00x_uart.h"
#include "BR00x_ssi.h"
#include "BR00x_ssic.h"

#ifdef DMA_DEBUG_LOG
#define dmaprf(format, ...) cm_printf(format, ##__VA_ARGS__)
#else
#define dmaprf(format, ...)
#endif


#define dmau1prf(format, ...) cm_printf_Uart1(format, ##__VA_ARGS__)


const RegisterCell dma_RegList[]=
{
#if  defined(BR002)||defined(BR003)
#if 1
//  {read,  write,  Register ID ,register_attr, Register},
    //DMA_Ch0
    {true,  true,   1,   0xFFFFFFFF,      &DMA->CHR[0].SAR},
    {true,  true,   2,   0xFFFFFFFF,      &DMA->CHR[0].DAR},
    {true,  true,   3,   0xFFFFFFFC,      &DMA->CHR[0].LLP},
    {true,  true,   4,   0x1871FFFF,      &DMA->CHR[0].CTL0},
    {true,  true,   5,   0x00001FFF,      &DMA->CHR[0].CTL1},
//    {true,  true,   6,   0xFFFFFFFF,      &DMA->CHR[0].SSTAT},
//    {true,  true,   7,   0xFFFFFFFF,      &DMA->CHR[0].DSTAT},
//    {true,  true,   8,   0xFFFFFFFF,      &DMA->CHR[0].SSTATAR},
//    {true,  true,   9,   0xFFFFFFFF,      &DMA->CHR[0].DSTATAR},
    {true,  true,   10,  0XC00C0FE0,      &DMA->CHR[0].CFG0},
    {true,  true,   11,  0x00007F9F,      &DMA->CHR[0].CFG1},
    
    //DMA_Ch1
    {true,  true,   12,  0xFFFFFFFF,      &DMA->CHR[1].SAR},
    {true,  true,   13,  0xFFFFFFFF,      &DMA->CHR[1].DAR},
    {true,  true,   14,  0xFFFFFFFC,      &DMA->CHR[1].LLP},
    {true,  true,   15,  0x1871FFFF,      &DMA->CHR[1].CTL0},
    {true,  true,   16,  0x00001FFF,      &DMA->CHR[1].CTL1},
//    {true,  true,   17,  0xFFFFFFFF,      &DMA->CHR[1].SSTAT},
//    {true,  true,   18,  0xFFFFFFFF,      &DMA->CHR[1].DSTAT},
//    {true,  true,   19,  0xFFFFFFFF,      &DMA->CHR[1].SSTATAR},
//    {true,  true,   20,  0xFFFFFFFF,      &DMA->CHR[1].DSTATAR},
    {true,  true,   21,  0XC00C0FE0,      &DMA->CHR[1].CFG0},
    {true,  true,   22,  0x00007F9F,      &DMA->CHR[1].CFG1},
    //DMA_Ch2
    {true,  true,   23,  0xFFFFFFFF,      &DMA->CHR[2].SAR},
    {true,  true,   24,  0xFFFFFFFF,      &DMA->CHR[2].DAR},
    {true,  true,   25,  0xFFFFFFFC,      &DMA->CHR[2].LLP},
    {true,  true,   26,  0x1871FFFF,      &DMA->CHR[2].CTL0},
    {true,  true,   27,  0x00001FFF,      &DMA->CHR[2].CTL1},
//    {true,  true,   28,  0xFFFFFFFF,      &DMA->CHR[2].SSTAT},
//    {true,  true,   29,  0xFFFFFFFF,      &DMA->CHR[2].DSTAT},
//    {true,  true,   30,  0xFFFFFFFF,      &DMA->CHR[2].SSTATAR},
//    {true,  true,   31,  0xFFFFFFFF,      &DMA->CHR[2].DSTATAR},
    {true,  true,   32,  0XC00C0FE0,      &DMA->CHR[2].CFG0},
    {true,  true,   33,  0x00007F9F,      &DMA->CHR[2].CFG1},
    //DMA_Ch3
    {true,  true,   34,  0xFFFFFFFF,      &DMA->CHR[3].SAR},
    {true,  true,   35,  0xFFFFFFFF,      &DMA->CHR[3].DAR},
    {true,  true,   36,  0xFFFFFFFC,      &DMA->CHR[3].LLP},
    {true,  true,   37,  0x1871FFFF,      &DMA->CHR[3].CTL0},
    {true,  true,   38,  0x00001FFF,      &DMA->CHR[3].CTL1},
//    {true,  true,   39,  0xFFFFFFFF,      &DMA->CHR[3].SSTAT},
//    {true,  true,   40,  0xFFFFFFFF,      &DMA->CHR[3].DSTAT},
//    {true,  true,   41,  0xFFFFFFFF,      &DMA->CHR[3].SSTATAR},
//    {true,  true,   42,  0xFFFFFFFF,      &DMA->CHR[3].DSTATAR},
    {true,  true,   43,  0XC00C0FE0,      &DMA->CHR[3].CFG0},
    {true,  true,   44,  0x00007F9F,      &DMA->CHR[3].CFG1},
    //DMA_Ch4
    {true,  true,   45,  0xFFFFFFFF,      &DMA->CHR[4].SAR},
    {true,  true,   46,  0xFFFFFFFF,      &DMA->CHR[4].DAR},
    {true,  true,   47,  0xFFFFFFFC,      &DMA->CHR[4].LLP},
    {true,  true,   48,  0x1871FFFF,      &DMA->CHR[4].CTL0},
    {true,  true,   49,  0x00001FFF,      &DMA->CHR[4].CTL1},
//    {true,  true,   50,  0xFFFFFFFF,      &DMA->CHR[4].SSTAT},
//    {true,  true,   51,  0xFFFFFFFF,      &DMA->CHR[4].DSTAT},
//    {true,  true,   52,  0xFFFFFFFF,      &DMA->CHR[4].SSTATAR},
//    {true,  true,   53,  0xFFFFFFFF,      &DMA->CHR[4].DSTATAR},
    {true,  true,   54,  0XC00C0FE0,      &DMA->CHR[4].CFG0},
    {true,  true,   55,  0x00007F9F,      &DMA->CHR[4].CFG1},
    //DMA_Ch5
    {true,  true,   56,  0xFFFFFFFF,      &DMA->CHR[5].SAR},
    {true,  true,   57,  0xFFFFFFFF,      &DMA->CHR[5].DAR},
    {true,  true,   58,  0xFFFFFFFC,      &DMA->CHR[5].LLP},
    {true,  true,   59,  0x1871FFFF,      &DMA->CHR[5].CTL0},
    {true,  true,   60,  0x00001FFF,      &DMA->CHR[5].CTL1},
//    {true,  true,   61,  0xFFFFFFFF,      &DMA->CHR[5].SSTAT},
//    {true,  true,   62,  0xFFFFFFFF,      &DMA->CHR[5].DSTAT},
//    {true,  true,   63,  0xFFFFFFFF,      &DMA->CHR[5].SSTATAR},
//    {true,  true,   64,  0xFFFFFFFF,      &DMA->CHR[5].DSTATAR},
    {true,  true,   65,  0XC00C0FE0,      &DMA->CHR[5].CFG0},
    {true,  true,   66,  0x00007F9F,      &DMA->CHR[5].CFG1},
    //DMA_Ch6
    {true,  true,   67,  0xFFFFFFFF,      &DMA->CHR[6].SAR},
    {true,  true,   68,  0xFFFFFFFF,      &DMA->CHR[6].DAR},
    {true,  true,   69,  0xFFFFFFFC,      &DMA->CHR[6].LLP},
    {true,  true,   70,  0x1871FFFF,      &DMA->CHR[6].CTL0},
    {true,  true,   71,  0x00001FFF,      &DMA->CHR[6].CTL1},
//    {true,  true,   72,  0xFFFFFFFF,      &DMA->CHR[6].SSTAT},
//    {true,  true,   73,  0xFFFFFFFF,      &DMA->CHR[6].DSTAT},
//    {true,  true,   74,  0xFFFFFFFF,      &DMA->CHR[6].SSTATAR},
//    {true,  true,   75,  0xFFFFFFFF,      &DMA->CHR[6].DSTATAR},
    {true,  true,   76,  0XC00C0FE0,      &DMA->CHR[6].CFG0},
    {true,  true,   77,  0x00007F9F,      &DMA->CHR[6].CFG1},
    //DMA_Ch7
    {true,  true,   78,  0xFFFFFFFF,      &DMA->CHR[7].SAR},
    {true,  true,   79,  0xFFFFFFFF,      &DMA->CHR[7].DAR},
    {true,  true,   80,  0xFFFFFFFC,      &DMA->CHR[7].LLP},
    {true,  true,   81,  0x1871FFFF,      &DMA->CHR[7].CTL0},
    {true,  true,   82,  0x00001FFF,      &DMA->CHR[7].CTL1},
//    {true,  true,   83,  0xFFFFFFFF,      &DMA->CHR[7].SSTAT},
//    {true,  true,   84,  0xFFFFFFFF,      &DMA->CHR[7].DSTAT},
//    {true,  true,   85,  0xFFFFFFFF,      &DMA->CHR[7].SSTATAR},
//    {true,  true,   86,  0xFFFFFFFF,      &DMA->CHR[7].DSTATAR},
    {true,  true,   87,  0XC00C0FE0,      &DMA->CHR[7].CFG0},
    {true,  true,   88,  0x00007F9F,      &DMA->CHR[7].CFG1},
 #endif   
    {true,  false,  89,  0x000000FF,      (volatile uint32_t *)&DMA->IR.RST},
    {true,  false,  90,  0x000000FF,      (volatile uint32_t *)&DMA->IR.RSB},
    {true,  false,  91,  0x000000FF,      (volatile uint32_t *)&DMA->IR.RSST},
    {true,  false,  92,  0x000000FF,      (volatile uint32_t *)&DMA->IR.RSDT},
    {true,  false,  93,  0x000000FF,      (volatile uint32_t *)&DMA->IR.RSER},
    
    {true,  false,  94,  0x000000FF,      (volatile uint32_t *)&DMA->IR.ST},
    {true,  false,  95,  0x000000FF,      (volatile uint32_t *)&DMA->IR.SB},
    {true,  false,  96,  0x000000FF,      (volatile uint32_t *)&DMA->IR.SST},
    {true,  false,  97,  0x000000FF,      (volatile uint32_t *)&DMA->IR.SDT},
    {true,  false,  98,  0x000000FF,      (volatile uint32_t *)&DMA->IR.SER},
  
    {true,  true,   99 ,  0x000000FF,      &DMA->IR.MT},
    {true,  true,   100,  0x000000FF,      &DMA->IR.MB},
    {true,  true,   101,  0x000000FF,      &DMA->IR.MST},
    {true,  true,   102,  0x000000FF,      &DMA->IR.MDT},
    {true,  true,   103,  0x000000FF,      &DMA->IR.MR},
    
    {true,  true,   104,  0x000000FF,      &DMA->IR.CT},
    {true,  true,   105,  0x000000FF,      &DMA->IR.CB},
    {true,  true,   106,  0x000000FF,      &DMA->IR.CST},
    {true,  true,   107,  0x000000FF,      &DMA->IR.CDT},
    {true,  true,   108,  0x000000FF,      &DMA->IR.CER},
    {true,  false,  109,  0x0000001F,      (volatile uint32_t *)&DMA->IR.SI},

//    {true,  true,   110,  0x000000FF,      &DMA->SR.RSR},
//    {true,  true,   111,  0x000000FF,      &DMA->SR.RDR},
//    {true,  true,   112,  0x000000FF,      &DMA->SR.SRSR},
//    {true,  true,   113,  0x000000FF,      &DMA->SR.SRDR},
//    {true,  true,   114,  0x000000FF,      &DMA->SR.LSR},
//    {true,  true,   115,  0x000000FF,      &DMA->SR.LDR},
    
    {true,  true,   116,  0x00000001,      &DMA->MR.CFG}, 
    //{true,  true,   117,  0x0000FFFF,      &DMA->MR.EN},//Enable Bit Cannot
#else    
    {true,  true,   117,  0x0000FFFF,      NULL },
#endif
};

/***********************************************************
                        Register
************************************************************/
bool cmd_VerifyRegisterDMACase1(uint32_t cmd, uint8_t *param_line,uint16_t len)
{
    bool sut = true;
    uint32_t idx=0;
    dmaprf("DMA Register case base\r\n");
    verify_SendCid(cmd,&idx); 
    SystemDevClockCtl(DMA_CKEn,true);
   for (uint8_t index=0;index < 8; index++)
   {
//DMA->CHR[index].SAR  Source Address Register
    if(sut)
        sut = verify_step_SendCheckOneData(BRCASE_STOP1,&DMA->CHR[index].SAR,0x55);
    if(sut)
        sut = verify_step_ReceiveCheckOneData(BRCASE_STOP2,&DMA->CHR[index].SAR);

//DMA->CHR[index].DAR  Destination Address Register
    if(sut)
        sut = verify_step_SendCheckOneData(BRCASE_STOP1,&DMA->CHR[index].DAR,0x55);
    if(sut)
        sut = verify_step_ReceiveCheckOneData(BRCASE_STOP2,&DMA->CHR[index].DAR);

//DMA->CHR[index].LLP  Linked List Pointer  Register
    if(sut)
        sut = verify_step_SendCheckOneData(BRCASE_STOP1,&DMA->CHR[index].LLP,0x55);
    if(sut)
        sut = verify_step_ReceiveCheckOneData(BRCASE_STOP2,&DMA->CHR[index].LLP);
 
//DMA->CHR[index].CTL0  Control 0 Register Register 
    if(sut)
        sut = verify_step_SendCheckOneData(BRCASE_STOP1,&DMA->CHR[index].CTL0,0x55);
    if(sut)
        sut = verify_step_ReceiveCheckOneData(BRCASE_STOP2,&DMA->CHR[index].CTL0);    
    
//DMA->CHR[index].CTL1  Control 1 Register Register 
    if(sut)
    {
        uint32_t step = BRCASE_STOP2;
        uint32_t val = 0x33;
        
        uint32_t cd=0,va=0;
        
        dmaprf("Setp %d Send \r\n",step-0x20);
        DMA->CHR[index].CTL1 = val;
        Verify_messageSend(step,val);
        Verify_messageReceive(&cd,&va);
        if(!(cd == BRCASE_STOP2 && va == 1))
            sut =false;
    }
    if(sut)
    {
        uint32_t step = BRCASE_STOP2;
        
        uint32_t cd=0,va=0;

        dmaprf("Setp %d Receive\r\n",step-0x20);
        Verify_messageReceive(&cd,&va);
        if(!(cd == step && va == DMA->CHR[index].CTL1))
            sut =false;
        Verify_messageSend(step,sut);
    }
//DMA->CHR[index].SSTAT   Source Status Register
    if(sut)
        sut = verify_step_SendCheckOneData(BRCASE_STOP1,&DMA->CHR[index].SSTAT,0x55);
    if(sut)
        sut = verify_step_ReceiveCheckOneData(BRCASE_STOP2,&DMA->CHR[index].SSTAT);        
    
//DMA->CHR[index].DSTAT   Source Status Register
    if(sut)
        sut = verify_step_SendCheckOneData(BRCASE_STOP1,&DMA->CHR[index].DSTAT,0x55);
    if(sut)
        sut = verify_step_ReceiveCheckOneData(BRCASE_STOP2,&DMA->CHR[index].DSTAT);     
    
//DMA->CHR[index].SSTATAR   Source Status Register
    if(sut)
        sut = verify_step_SendCheckOneData(BRCASE_STOP1,&DMA->CHR[index].DSTAT,0x55);
    if(sut)
        sut = verify_step_ReceiveCheckOneData(BRCASE_STOP2,&DMA->CHR[index].DSTAT);     
//DMA->CHR[index].DSTATAR   Source Status Register
    if(sut)
        sut = verify_step_SendCheckOneData(BRCASE_STOP1,&DMA->CHR[index].DSTAT,0x55);
    if(sut)
        sut = verify_step_ReceiveCheckOneData(BRCASE_STOP2,&DMA->CHR[index].DSTAT);     
        
//DMA->CHR[index].CFG0   Configuration 1 Register 
    if(sut)
        sut = verify_step_SendCheckOneData(BRCASE_STOP1,&DMA->CHR[index].DSTAT,0x55);
    if(sut)
        sut = verify_step_ReceiveCheckOneData(BRCASE_STOP2,&DMA->CHR[index].DSTAT);     
//DMA->CHR[index].CFG1  Configuration 1 Register 
    if(sut)
    {
        uint32_t step = BRCASE_STOP2;
        uint32_t val = 0x33;
        
        uint32_t cd=0,va=0;
  
        dmaprf("Setp %d Send \r\n",step-0x20);
        DMA->CHR[index].CTL1 = val;
        Verify_messageSend(step,val);
        Verify_messageReceive(&cd,&va);
        if(!(cd == BRCASE_STOP2 && va == 1))
            sut =false;
    }
    if(sut)
    {
        uint32_t step = BRCASE_STOP2;
        
        uint32_t cd=0,va=0;

        dmaprf("Setp %d Receive\r\n",step-0x20);
        Verify_messageReceive(&cd,&va);
        if(!(cd == step && va == DMA->CHR[index].CTL1))
        sut =false;
        Verify_messageSend(step,sut);
    }         
   } 
    Verify_SendCResult(BRCASE_RESULT,sut);
    return sut;


}


bool cmd_VerifyRegisterDMACase2(uint32_t cmd, uint8_t *param_line,uint16_t len)
{
    bool sut = true;
    uint32_t idx=0;
    dmaprf("DMA Register case2\r\n");
    verify_SendCid(cmd,&idx);
    SystemDevClockCtl(DMA_CKEn,true);
    sut =Verify_RegisterDAMHandle(dma_RegList,sizeof(dma_RegList),idx);
    Verify_SendCResult(BRCASE_RESULT,sut);
    return sut;
}
/***********************************************************
                        APP
************************************************************/

uint8_t Tx_data[50] = {9,0,2,3,4,6,3,5,67,8,2,2,4,6,4,6,67,78,2};
uint8_t Rx_data[50] = {0};
uint8_t dma_Int_Flag =1;

bool cmd_VerifyAppDMACase1(uint32_t cmd, uint8_t *param_line,uint16_t len)
{
    bool sut = true;
    uint32_t idx=0;
    dmaprf("DMA App case1\r\n");
    verify_SendCid(cmd,&idx);
    SystemDevClockCtl(DMA_CKEn,true);
    {
        DMA_InitInfo_Type DMA_InitStru;
        dmaprf("dma test mem to mem  S=[%p],D=[%p]\r\n",Tx_data,Rx_data);
  
        DMA_InitStru.src_addr       = (uint32_t)Tx_data;
        DMA_InitStru.dst_addr       = (uint32_t)Rx_data;
        DMA_InitStru.block_size     = 20;
        DMA_InitStru.src_llp_en     = ENABLE;
        DMA_InitStru.dst_llp_en     = ENABLE;
        DMA_InitStru.tt_tc_mode     = DMA_TT_M2M_TC_D;
        DMA_InitStru.src_msize      = DMA_MSIZE_4;
        DMA_InitStru.dst_msize      = DMA_MSIZE_4;
        DMA_InitStru.src_inc_mode   = DMA_IM_INC;
        DMA_InitStru.dst_inc_mode   = DMA_IM_INC;

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
        DMA_InitStru.ch_priority    = DMA_CP_PRIOR_0;

       // SystemDevClockCtl(DMA_CKEn, ENABLE);
        
        for(uint16_t i=0;i<20;i++)
            Tx_data[i] = i;

        for(DMA_ChNum_Type ch = DMA_CH_0;ch<DMA_CH_END;ch++)
        {
            dma_Int_Flag++;
            DMA_Enable(DISABLE);
            DMA_Init(ch,&DMA_InitStru);
            DMA_SetIntMask(ch,DMA_IT_TFR,SET);    /*?????? */
            DMA_SetIntMask(ch,DMA_IT_BLOCK,SET);  /*????????*/
            DMA_SetIntMask(ch,DMA_IT_SRCTRAN,SET);/*??????*/
            DMA_SetIntMask(ch,DMA_IT_DSTTRAN,SET);/*???????*/
            DMA_SetIntMask(ch,DMA_IT_ERR,SET);    /*????*/
            DMA_Enable(ENABLE);
            DMA_EnableCh(ch,ENABLE);
            NVIC_EnableIRQ(DMA_IRQn);
            while(dma_Int_Flag);
            
            for(uint16_t i=0;i<20;i++)
                if(Rx_data[i] != i)
                    sut=false;
                    
            memset(Rx_data,0,20);
            dmaprf("DMA Start stf [%d]\r\n",sut);
        }
    }
    Verify_SendCResult(BRCASE_RESULT,sut);
    return sut;
}

bool cmd_VerifyAppDMACase2(uint32_t cmd, uint8_t *param_line,uint16_t len)
{
    bool sut = true;
    uint32_t idx=0;
    dmaprf("DMA App case2\r\n");
    verify_SendCid(cmd,&idx);
    SystemDevClockCtl(DMA_CKEn,true);
    {
        DMA_InitInfo_Type DMA_InitStru;
        dmaprf("dma test mem to mem  S=[%p],D=[%p]\r\n",Tx_data,Rx_data);
  
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
                    DMA_SetIntMask(ch,DMA_IT_TFR,SET);    /*?????? */
                    DMA_SetIntMask(ch,DMA_IT_BLOCK,SET);  /*????????*/
                    DMA_SetIntMask(ch,DMA_IT_SRCTRAN,SET);/*??????*/
                    DMA_SetIntMask(ch,DMA_IT_DSTTRAN,SET);/*???????*/
                    DMA_SetIntMask(ch,DMA_IT_ERR,SET);    /*????*/
                    DMA_Enable(ENABLE);
                    DMA_EnableCh(ch,ENABLE);
                    NVIC_EnableIRQ(DMA_IRQn);
                    while(dma_Int_Flag);
                    
                    for(uint16_t i=0;i<20;i++)
                        if(Rx_data[i] != i)
                            sut=false;
                            
                    memset(Rx_data,0,20);
                    dmaprf("DMA Start stf [%d]\r\n",sut);
                }
            }
        }}}}
    }
    Verify_SendCResult(BRCASE_RESULT,sut);
    return sut;
}
uint8_t DMA_UART_Tx_data[50] = {'1','2','3','4','5','6','7','8','9','\n',\
                                '1','2','3','4','5','6','7','8','9','\n',\
                                '1','2','3','4','5','6','7','8','9','\n',\
                                '1','2','3','4','5','6','7','8','9','\n',\
                                '1','2','3','4','5','6','7','8','9','\n'};

uint8_t DMA_UART_Rx_data[50] = {0};
static  uint8_t dmaUartBlockFlag = 0;
bool cmd_VerifyAppDMACase3(uint32_t cmd, uint8_t *param_line,uint16_t len)
{
    bool sut = true;
    //uint32_t idx=0;
    //verify_SendCid(cmd,&idx);
    DMA_ChNum_Type UART0_tx_ch = DMA_CH_1;
    dmaprf("DMA UART case3\r\n");
    SystemDevClockCtl(DMA_CKEn,true);
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
        DMA_SetIntMask(UART0_tx_ch,DMA_IT_TFR,SET);    /*?????? */
        DMA_SetIntMask(UART0_tx_ch,DMA_IT_BLOCK,SET);  /*????????*/
        DMA_SetIntMask(UART0_tx_ch,DMA_IT_SRCTRAN,SET);/*??????*/
        DMA_SetIntMask(UART0_tx_ch,DMA_IT_DSTTRAN,SET);/*???????*/
        DMA_SetIntMask(UART0_tx_ch,DMA_IT_ERR,SET);    /*????*/
               
        NVIC_ClearPendingIRQ(DMA_IRQn);
        NVIC_EnableIRQ(DMA_IRQn);
        
        dmaUartBlockFlag=3;
        DMA_EnableCh(UART0_tx_ch,ENABLE);
        dmaprf("DMA tx[%d] En\n",UART0_tx_ch);
        while(dmaUartBlockFlag);
        
    }
    
    Verify_SendCResult(BRCASE_RESULT,sut);
    return sut;
}


static  uint8_t dmaUartDstFlag = 0;
bool cmd_VerifyAppDMACase4(uint32_t cmd, uint8_t *param_line,uint16_t len)
{
    bool sut = true;
    UART_InitInfo_Type UART_Str;
    //verify_SendCid(cmd);
    DMA_ChNum_Type UART0_Rx_ch = DMA_CH_0; 
    UART_Str.UART_BaudRate             = 500000;
    UART_Str.UART_WordLength           = UART_WL_8BITS;
    UART_Str.UART_StopBits             = UART_SB_1BIT;
    UART_Str.UART_ParityMode           = UART_PM_NONE;
    UART_Str.UART_HardwareFlowControl  = UART_FC_NONE;
    UART_Str.UART_FIFOMode             = UART_FM_ENABLE;
    UART_Str.UART_DMAMode              = UART_DM_MODE_0;
    UART_Str.UART_TX_FIFOTriggerMode   = UART_TT_EMPTY;
    UART_Str.UART_RX_FIFOTriggerMode   = UART_RT_1_CHARACTER;
        
    UART_Init(UART0, &UART_Str); 
    dmaprf("DMA UART case4\r\n");
    SystemDevClockCtl(DMA_CKEn,true);
    for(UART0_Rx_ch = DMA_CH_0;UART0_Rx_ch<DMA_CH_END; UART0_Rx_ch++) 
    {
        DMA_InitInfo_Type DMA_InitStru;
        /* dma rx*/
        DMA_InitStru.src_addr       = (uint32_t)&UART0->RBR;
        DMA_InitStru.dst_addr       = (uint32_t)DMA_UART_Rx_data;
        DMA_InitStru.block_size     = 50;
        DMA_InitStru.src_llp_en     = DISABLE;
        DMA_InitStru.dst_llp_en     = DISABLE;
        DMA_InitStru.tt_tc_mode     = DMA_TT_P2M_TC_P;
        DMA_InitStru.src_msize      = DMA_MSIZE_1;
        DMA_InitStru.dst_msize      = DMA_MSIZE_1;
        DMA_InitStru.src_inc_mode   = DMA_IM_NO_CHANGE_0;
        DMA_InitStru.dst_inc_mode   = DMA_IM_INC;

        DMA_InitStru.src_trans_w    = DMA_TW_8;
        DMA_InitStru.dst_trans_w    = DMA_TW_8;
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
        DMA_InitStru.dst_per        = (DMA_HardInterface_Type)1;
        DMA_InitStru.src_per        = (DMA_HardInterface_Type)1;

       // SystemDevClockCtl(DMA_CKEn, ENABLE);
        DMA_Enable(DISABLE);
        DMA_Init(UART0_Rx_ch,&DMA_InitStru);
        DMA_SetIntMask(UART0_Rx_ch,DMA_IT_TFR,SET);    /*?????? */
        DMA_SetIntMask(UART0_Rx_ch,DMA_IT_BLOCK,SET);  /*????????*/
        DMA_SetIntMask(UART0_Rx_ch,DMA_IT_SRCTRAN,SET);/*??????*/
        DMA_SetIntMask(UART0_Rx_ch,DMA_IT_DSTTRAN,SET);/*???????*/
        DMA_SetIntMask(UART0_Rx_ch,DMA_IT_ERR,SET);    /*????*/ 

        Verrify_SendPinConnect(UART1_UART0_EN);
        
        {
            UART_InitInfo_Type UART_InitStru;
            PADConfig_Type PAG_InitStru;          
            memset(&PAG_InitStru,0,sizeof(PADConfig_Type));
            PAG_InitStru.set        = 0;
            PAG_InitStru.pad_ctl    = PAD_MODE1;

#ifdef BR002
            SystemPADConfig(PADID6,&PAG_InitStru);
            SystemPADConfig(PADID7,&PAG_InitStru);
#endif
#ifdef BR003
            SystemPADConfig(PADID15,&PAG_InitStru);
            SystemPADConfig(PADID16,&PAG_InitStru);
        
#endif
            UART_InitStru.UART_BaudRate = 500000;
            UART_InitStru.UART_WordLength = UART_WL_8BITS;
            UART_InitStru.UART_StopBits = UART_SB_1BIT;
            UART_InitStru.UART_ParityMode = UART_PM_NONE;
            UART_InitStru.UART_HardwareFlowControl = UART_FC_NONE;
            UART_InitStru.UART_FIFOMode = UART_FM_ENABLE;
            UART_InitStru.UART_DMAMode = UART_DM_MODE_0;
            UART_InitStru.UART_TX_FIFOTriggerMode = UART_TT_EMPTY;
            UART_InitStru.UART_RX_FIFOTriggerMode = UART_RT_1_CHARACTER;  
            SystemDevClockCtl(UART1_CKEn,true);            
            UART_Init(UART1, &UART_InitStru);     
            cm_printf_Uart1("UART1 Verify Output\r\n");
        }
        
        dmaUartDstFlag=3;
        DMA_Enable(ENABLE);
        NVIC_ClearPendingIRQ(DMA_IRQn);
        NVIC_EnableIRQ(DMA_IRQn);
        DMA_EnableCh(UART0_Rx_ch,ENABLE);
        dmaprf("DMA[%d]En\n",UART0_Rx_ch);
        while(dmaUartDstFlag);
        UART_WriteData(UART0, DMA_UART_Rx_data,21);
    }
     
    for(uint16_t i=0;i<1000;i++);
    Verify_SendCResult(BRCASE_RESULT,sut);
    return sut;
}



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

bool GetStepIsOk(verify_caseCmd_type step)
{
    uint32_t cd=0,va=0;
    Verify_messageReceive(&cd,&va);
    if(!(cd == step && va == 1))
        return false;
    else
        return true;
}

void DMA_SendDataHandle(uint32_t dst,DMA_ChNum_Type tx_ch,uint16_t ack_ch)
{
        DMA_InitInfo_Type DMA_InitStru;
        memset(&DMA_InitStru,0,sizeof(DMA_InitInfo_Type));     
        /* dma rx*/
        dmaprf("DMA tx ch[%d],ack[%x]\n",tx_ch,ack_ch);
    
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
        dmaprf("DMA tx[%d] En\n",tx_ch);
        while(dmaUartBlockFlag);
}

void DMA_ReceiveDataHandle(uint32_t src,DMA_ChNum_Type rx_ch,uint16_t ack_ch,verify_caseCmd_type step)
{
        DMA_InitInfo_Type DMA_InitStru;
        /* dma rx*/
        dmaprf("DMA rx ch[%d],ack[%x]\n",rx_ch,ack_ch);
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
        dmaprf("DMA[%d]En\n",rx_ch);
        
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
        
        UART_WriteData(UART0,DMA_UART_Rx_data,20); dmaprf("|\n");
        memset(DMA_UART_Rx_data,0,30);
        memset(DMA_UART_Rx_data16,0,sizeof(DMA_UART_Rx_data16));
        DMA_EnableCh(rx_ch,DISABLE);
}


bool cmd_VerifyAppDMACase5(uint32_t cmd, uint8_t *param_line,uint16_t len)
{
    bool sut = true;
    dmaprf("DMA SPIM0 case5\r\n");
    SystemDevClockCtl(DMA_CKEn,true);
    {
        SSIC_InitInfo_Type  SSIC_InitStru ;
        
        SSIC_InitStru.clock_divider             =  0x10;
        SSIC_InitStru.frame_format_size         =  SSI_DATA_FRAME_SIZE_32BIT;
        SSIC_InitStru.ssi_frame_format          =  SSI_FRAME_FORMAT_MOTOROLA_SPI ;
        SSIC_InitStru.clock_phase               =  SSI_CLOCK_TOGGLES_MIDDLE ;
        SSIC_InitStru.clock_polarity            =  SSI_INACTIVE_STATE_LOW;
        SSIC_InitStru.transfer_mode             =  SSI_ONLY_TRANSMIT;
        SSIC_InitStru.slave_output_enable       =  SSI_SLAVE_TXD_IS_ENABLE;
        SSIC_InitStru.operation_mode            =  SSI_NORMAL_MODE ;
        SSIC_InitStru.slave_select_toggle_en    =  SSIC_SLAVE_SELECT_TOHHLE_DISABLE;
        SSIC_InitStru.control_farme_size        =  SSI_CONTROL_FRAME_1BIT_WORD;
        SSIC_InitStru.spi_frame_format          =  STANDARD_SPI_FORMAT;
        SSIC_InitStru.spi_hyperbus_en           =  SSIC_SPI_HYPERBUS_DISABLE;

        SSIC_InitStru.data_frames_number        = 0;
        SSIC_InitStru.slaves_select             = 1 ;
        SSIC_InitStru.tx_fifo_threshold_level   = 3;
        SSIC_InitStru.tx_fifo_start_fifo_level  = 0;
        SSIC_InitStru.rx_fifo_threshold_level   = 3;
        
        SSIC_InitStru.dma_rx_en                 = 1;
        SSIC_InitStru.dma_tx_en                 = 1;
        SSIC_InitStru.dma_rx_data_level         = 0;
        SSIC_InitStru.dma_tx_data_level         = 0;
        SSIC_InitStru.unmask_interrupt          =FIFO_MASK_ALL;
        SystemDevClockCtl(SPIM0_CKEn,true);
        SSIC_Init(&SSIC_InitStru);
        
        {
           
            DMA_ChNum_Type ch = DMA_CH_0;
            for(ch = DMA_CH_0;ch<DMA_CH_END; ch++) 
            {
                dmaprf("SPIM0 DMA:[%d]\n",ch);
                DMA_SendDataHandle((uint32_t)SPIM0->DR,ch,2);
            }
        }
    }
    
    Verify_SendCResult(BRCASE_RESULT,sut);
    return sut;
}


bool cmd_VerifyDualAppDMACase1(uint32_t cmd, uint8_t *param_line,uint16_t len)
{
    bool sut = true;
    dmaprf("DMA SPIM1/S1 case1\r\n");
    SystemDevClockCtl(DMA_CKEn,true);
    SystemDevClockCtl(SPIM1_CKEn,true);
    SystemDevClockCtl(SPIS1_CKEn,true);
    {
#if (defined(BR_MASTER) || defined(BR_SLAVE))
        SSI_InitInof_Type SSI_InitStru ;
        PADConfig_Type PAG_InitStru;
        memset(&PAG_InitStru ,0,sizeof(PADConfig_Type));
        PAG_InitStru.set        = 0;        
#ifdef BR_MASTER
#ifdef BR_DUAL
        if(GetSocRole())
#endif  
        PAG_InitStru.pad_ctl    = PAD_MODE1;
#endif
#ifdef BR_SLAVE 
#ifdef BR_DUAL
        if(!GetSocRole())
#endif  
        PAG_InitStru.pad_ctl    = PAD_MODE2;
#endif
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
        SSI_InitStru.spi_frame_format       = STANDARD_SPI_FORMAT;
        SSI_InitStru.unmask_interrupt       = RX_FIFO_FULL_UNMASK; 
        
        SSI_InitStru.data_frame_num         = 0;
        SSI_InitStru.dma_tx_en              = 1;
        SSI_InitStru.dma_rx_en              = 1;
        
        SSI_InitStru.dma_tx_data_level      = 3;
        SSI_InitStru.dma_rx_data_level      = 3;

#ifdef BR_MASTER
#ifdef BR_DUAL
        if(GetSocRole())
#endif  
        {
            SSI_InitStru.transfer_mode          = SSI_ONLY_TRANSMIT;
            SSI_Init(SPIM1 ,&SSI_InitStru);
            {
               
                DMA_ChNum_Type ch = DMA_CH_0;
                verify_caseCmd_type step = BRCASE_STOP1;
                for(ch = DMA_CH_0;ch<DMA_CH_END; ch++) 
                {
                    while(!GetStepIsOk(step)){};step++;
                    DMA_SendDataHandle((uint32_t)SPIM1->DR,ch,4);
                }
            }
        }
#endif
#ifdef BR_SLAVE  
#ifdef BR_DUAL
        if(!GetSocRole())
#endif      
        {        
            SSI_InitStru.tx_fifo_threshold_level    = 3;
            SSI_InitStru.rx_fifo_threshold_level    = 3;
            SSI_InitStru.tx_fifo_start_fifo_level   = 0;
            SSI_InitStru.dma_tx_data_level          = 1;
            SSI_InitStru.dma_rx_data_level          = 0;
            SSI_InitStru.transfer_mode              = SSI_ONLY_RECEIVE;
            SSI_Init(SPIS1 ,&SSI_InitStru);
            dmaprf("SPIS1 Ok\n");     
            {
                DMA_ChNum_Type ch = DMA_CH_0;
                verify_caseCmd_type step = BRCASE_STOP1;
                for(ch = DMA_CH_0;ch<DMA_CH_END; ch++) 
                {
                    DMA_ReceiveDataHandle((uint32_t)SPIS1->DR,ch,7,step);
                    step++;
                }
            }
        }
            
#endif   
#endif 

    }
    
    Verify_SendCResult(BRCASE_RESULT,sut);
    return sut;
}


bool cmd_VerifyDualAppDMACase2(uint32_t cmd, uint8_t *param_line,uint16_t len)
{
    bool sut = true;
    dmaprf("DMA SPIM1/S1 case2\r\n");
    SystemDevClockCtl(DMA_CKEn,true);
    SystemDevClockCtl(SPIM1_CKEn,true);
    SystemDevClockCtl(SPIS1_CKEn,true);
    {
#if (defined(BR_MASTER) || defined(BR_SLAVE))
        SSI_InitInof_Type SSI_InitStru ;
        PADConfig_Type PAG_InitStru;
        memset(&PAG_InitStru ,0,sizeof(PADConfig_Type));
        PAG_InitStru.set        = 0;        
#ifdef BR_MASTER
#ifdef BR_DUAL
        if(GetSocRole())
#endif  
        PAG_InitStru.pad_ctl    = PAD_MODE1;
#endif
#ifdef BR_SLAVE 
#ifdef BR_DUAL
        if(!GetSocRole())
#endif  
        PAG_InitStru.pad_ctl    = PAD_MODE2;
#endif
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
        SSI_InitStru.spi_frame_format       = STANDARD_SPI_FORMAT;
        SSI_InitStru.unmask_interrupt       = RX_FIFO_FULL_UNMASK; 
        
        SSI_InitStru.data_frame_num         = 0;
        SSI_InitStru.dma_tx_en              = 1;
        SSI_InitStru.dma_rx_en              = 1;
        
        SSI_InitStru.dma_tx_data_level      = 3;
        SSI_InitStru.dma_rx_data_level      = 3;
        
#ifdef BR_SLAVE   
#ifdef BR_DUAL
        if(!GetSocRole())
#endif  
        {
            SSI_InitStru.transfer_mode              = SSI_ONLY_TRANSMIT;     
            SSI_InitStru.tx_fifo_threshold_level    = 3;
            SSI_InitStru.tx_fifo_start_fifo_level   = 0;
            SSI_InitStru.rx_fifo_threshold_level    = 3;
            
            SSI_Init(SPIS1 ,&SSI_InitStru);
            
            {
                DMA_ChNum_Type ch = DMA_CH_0;
                verify_caseCmd_type step = BRCASE_STOP1;
                for(ch = DMA_CH_0;ch<DMA_CH_END; ch++) 
                {
                    dmaprf("SPIS Send:");
                    Verify_messageSend(step,true); step++;
                    DMA_SendDataHandle((uint32_t)SPIS1->DR,ch,6);
                                    
                }
            }
        }
#endif
#ifdef BR_MASTER 
#ifdef BR_DUAL
        if(GetSocRole())
#endif  
        {
            SSI_InitStru.tx_fifo_threshold_level    = 3;
            SSI_InitStru.rx_fifo_threshold_level    = 3;
            SSI_InitStru.tx_fifo_start_fifo_level   = 0;
            SSI_InitStru.dma_tx_data_level          = 0;
            SSI_InitStru.dma_rx_data_level          = 0;
            
            SSI_InitStru.data_frame_num             = 20-1;
            SSI_InitStru.transfer_mode              = SSI_ONLY_RECEIVE;
            //SSI_Init(SPIM1 ,&SSI_InitStru);    

            dmaprf("SPIM1 Ok\n");     
            {
                DMA_ChNum_Type ch = DMA_CH_0;
                verify_caseCmd_type step = BRCASE_STOP1;
                for(ch = DMA_CH_0;ch<DMA_CH_END; ch++) 
                {
                    while(!GetStepIsOk(step)){};
                    {
                       SSI_Init(SPIM1 ,&SSI_InitStru);
                       DMA_ReceiveDataHandle((uint32_t)SPIM1->DR,ch,5,step);
                    } 
                    step++;
                }            
            }  
        } 
#endif
        
#endif 

    }
    
    Verify_SendCResult(BRCASE_RESULT,sut);
    return sut;
}

bool cmd_VerifyDualAppDMACase3(uint32_t cmd, uint8_t *param_line,uint16_t len)
{
    bool sut = true;
    dmaprf("DMA SPIM0/S1 case3\r\n");
    SystemDevClockCtl(DMA_CKEn,true);
    SystemDevClockCtl(SPIS1_CKEn,true);
    SystemDevClockCtl(SPIM1_CKEn,true);
    SystemDevClockCtl(SPIM0_CKEn,true);
    {
        
     SCU->SEND_DATA = 0xe002;
        
#if (defined(BR_MASTER) || defined(BR_SLAVE))
           
#ifdef BR_MASTER 
#ifdef BR_DUAL
        if(GetSocRole())
#endif  
        {        
            SSIC_InitInfo_Type  SSIC_InitStru ;
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
           
            dmaprf("SPIM0 Ok\n");     
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
            PAG_InitStru.set        = 0;        
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
                    dmaprf("SPIS Send:");
                    Verify_messageSend(step,true); step++;
                    DMA_SendDataHandle((uint32_t)SPIS1->DR,ch,6);
                                    
                }
            }
        }
#endif      
#endif 
    }
  
    Verify_SendCResult(BRCASE_RESULT,sut);
    return sut;
}


void DMA_IRQHandler(void)       
{    
    //dmaprf("DMA_IRQ\r\n");
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
                dmaprf("SD:[%d],t:[%d]\n",ChNum,IntType);
#endif
#ifdef BR_MASTER 
#ifdef BR_DUAL
        if(GetSocRole())
#endif  
                dmaprf("MD:[%d],t:[%d]\n",ChNum,IntType);
#endif

#if  !(defined(BR_SLAVE) ||  defined(BR_MASTER))              
                dmaprf("D:[%d],t:[%d]\n",ChNum,IntType);
#endif
            }
        }
    }
}     





