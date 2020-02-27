/*
 *++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 * Copyright (c) 1999-2018 Barrot Technology Limited
 *
 * All rights reserved.
 *
 *------------------------------------------------------------------------------
 */
/**
 * @file    BR00x_ssi_common.c
 * @brief    This file provides the ssi and ssic firmware functions.
 * @attention
 *
 * THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
 * WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE
 * TIME. AS A RESULT, STMICROELECTRONICS SHALL NOT BE HELD LIABLE FOR ANY
 * DIRECT, INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING
 * FROM THE CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE
 * CODING INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
 *
 * @date    14. Augest 2018
 * @version V1.0.0
 * @author  MEIGER
*/
#include "BR00x_ssi_common.h"
#include "BR00x_ssic.h"
#include "BR00x_ssic_if.h"
#include "BR00x_ssi_if.h"
#include "BR00x_ssi.h"
#include "system_BR00x.h"

#define IS_SPIM0(X)    ((X == SPIM0) ? true : false) 

#define MAX_SPIM0_FIFO_DEP   32
#define MAX_SPIM1_FIFO_DEP   8

bool SSI_SendData(SSI_TypeDef   *SSIx,uint8_t *data,uint16_t len)
{
    uint16_t i=0;
    for(i=0;i<len;i++)
        SSIx->DR[i] = data[i];
    return true;
}

bool SSI_ReadData(SSI_TypeDef   *SSIx,uint8_t *data,uint16_t len)
{
    uint16_t i=0;
    for(i=0;i<len;i++)
         data[i]= SSIx->DR[i];
    return true;
}

bool SSI_SendData32(SSI_TypeDef   *SSIx,uint32_t *data,uint16_t len)
{
    uint32_t i=0;
    for(i=0;i<len;i++)
        SSIx->DR[i] = data[i];
    return true;
}

bool SSI_ReadData32(SSI_TypeDef   *SSIx,uint32_t *data,uint16_t len)
{
    uint32_t i=0;
    for(i=0;i<len;i++)
         data[i]= SSIx->DR[i];
    return true;
}


/**
  * @brief  Write to SSI peripheral with byte.
  *
  * @param  SSIx: pointer to a SSI.
  * @param  data: The data pointer will be write to the SSI fifo or data register.
  * @param  len: The data length.
  * @retval  true(succeed)/false(defeated)
  */
bool SSI_Send(SSI_TypeDef   *SSIx,uint8_t *data,uint16_t len)
{
    uint16_t  idx = 0;
    uint8_t fifo_depth = IS_SPIM0(SSIx) ? MAX_SPIM0_FIFO_DEP : MAX_SPIM1_FIFO_DEP;
    
    if(!data)
        return false;
    
    while(len>fifo_depth)
    {
        SSI_SendData(SSIx,&data[idx],fifo_depth);
        while(!(SSIx->SR >>SSI_tx_fifo_empty &0x01));
        len -=fifo_depth;
        idx+=fifo_depth;
    }
    SSI_SendData(SSIx,&data[idx],len);
    while(!(SSIx->SR >>SSI_tx_fifo_empty &0x01));
    return true;
        
}

/**
  * @brief   Read from SSI peripheral..
  *
  * @param  SSIx: pointer to a SSI.
  * @trigger Triggers a write start.
  * @param  data: The data pointer will be read to the SSI fifo or data register.
  * @param  len: The data length.
  * @retval  true(succeed)/false(defeated)
  */

bool SSI_Receive(SSI_TypeDef   *SSIx,bool trigger ,uint8_t *data,uint16_t len)
{
    uint16_t  idx = 0,rxed_num;
    int16_t data_len = len;
    data[0] = 0;

    if(!data)
        return false;
    
    while (data_len >0)
    {
        if(trigger)
            SSI_SendData(SSIx,data,1);
        
        while(!(SSIx->SR >>SSI_rx_fifo_not_empty & 0x01));
        rxed_num = SSI_RX_FIFO_LEVEL(SSIx);
        SSI_ReadData(SSIx,&data[idx],rxed_num);
        idx      += rxed_num;   
        data_len -= rxed_num;
    }
    
    return true;
}


bool SSI_Dirtransfer(SSI_TypeDef   *SSIx,uint8_t *tx,uint16_t tlen,uint8_t *rx,uint16_t rlen)
{
     if(!tx || !rx)
        return false;
     
     SSI_Send(SSIx,tx,tlen);
     SSI_Receive(SSIx,false,rx,rlen);

     return true;
}



bool SSI_Transfer(SSI_TypeDef   *SSIx,uint8_t *tx,uint16_t tlen,uint8_t *rx,uint16_t rlen)
{
      uint16_t receive_num;
      uint16_t transmit_num;
      uint8_t fifo_depth = IS_SPIM0(SSIx) ? MAX_SPIM0_FIFO_DEP : MAX_SPIM1_FIFO_DEP;
      
     if((!SSIx) ||(!tx && !rx)||(tlen==0 && rlen ==0))
        return false;    

    if(tx && tlen>0 && rlen ==0)
    {
        if(IS_SPIM0(SSIx))
            SSIC_SetTransferMode(SSI_ONLY_TRANSMIT);
        else
            SSI_SetTransferMode(SSIx,SSI_ONLY_TRANSMIT);
        
        SSI_UpdataReceiveTransmitFifoThreshold(SSIx,0,0);
        SSI_Send(SSIx,tx,tlen);     
        return true;
    }
    if(rx && rlen>0 && tx && tlen==0)
    {
        receive_num = (rlen && rlen<=fifo_depth) ?   rlen-1 : fifo_depth-1;
        if(IS_SPIM0(SSIx))
            SSIC_SetTransferMode(SSI_ONLY_RECEIVE);   
        else
            SSI_SetTransferMode(SSIx,SSI_ONLY_RECEIVE);   
        
        SSI_UpdataReceiveTransmitFifoThreshold(SSIx,receive_num,0);
        SSI_UpdataReceiveNumber(SSIx,rlen);
        SSI_Receive(SSIx,true,rx,rlen);
       
        return true;
    }
    if(rx && rlen>0 && tx && tlen>0)
    {

        receive_num = (rlen && rlen<=fifo_depth) ?   rlen-1 : fifo_depth-1;
        transmit_num  = (tlen && tlen<=fifo_depth) ?   tlen-1 : fifo_depth-1;
        
         if(IS_SPIM0(SSIx))
            SSIC_SetTransferMode(SSI_EEPROM_READ);   
         else
            SSI_SetTransferMode(SSIx,SSI_EEPROM_READ); 
        
        SSI_UpdataReceiveTransmitFifoThreshold(SSIx,receive_num,transmit_num);
        SSI_UpdataReceiveNumber(SSIx,rlen-1);
        SSI_Dirtransfer(SSIx,tx,tlen,rx,rlen);    
        return true;
    }
    else
        return false;    
    
}



/**
  * @brief   Controls the level of entries (or above) at which the receive/transmit
  *   FIFO controller triggers an interrupt. The FIFO depth is
  *   configurable in the range 0-8/32. ti  is sized to the
  *   number of address bits needed to access the FIFO. If you
  *   attempt to set this value greater than the depth of the FIFO,
  *  this field is not written and retains its current value. When the
  *  number of receive FIFO entries is greater than or equal to
  *  this value + 1, the receive FIFO full interrupt is triggered
  
  * @param  SSIx: pointer to a SSI.
  * @param  rx_thd:Receive FIFO Threshold
  * @param  tx_thd:Transmit FIFO Threshold
  * @retval  None
  */
void SSI_UpdataReceiveTransmitFifoThreshold(SSI_TypeDef   *SSIx,uint16_t rx_threshold,uint16_t tx_threshold)
{
    SSIx->SSIENR = DISABLE;
    SSI_ClearInterrupt(SSIx);
    SSIx->RXFTLR =  rx_threshold;
    SSIx->TXFTLR = tx_threshold;
    SSIx->SSIENR = ENABLE;
}

/**
  * @brief    this  sets the  number of data frames to be continuously received by the
  *  ssi. The ssi continues to receive serial data until
  *  the number of data frames received is equal to this register
  *  value plus 1, which enables you to receive up to 64 KB of
  *  data in a continuous transfer. When the ssi is 
  *  configured as a serial slave, the transfer continues for as
  *  long as the slave is selected. Therefore, this register serves
  *  no purpose and is not present when the ssi is 
  *  configured as a serial slave.
  *
  * @param  SSIx: pointer to a SSI.
  * @param  len:Number of Data Frames
  * @retval  None
  */

void SSI_UpdataReceiveNumber(SSI_TypeDef   *SSIx,uint16_t len)
{
    SSIx->SSIENR = DISABLE;
    SSI_ClearInterrupt(SSIx);
    SSIx->CTRLR1 =  len;
    SSIx->SSIENR = ENABLE;
}



void SSI_UpdataDataFarmeSize(SSI_TypeDef   *SSIx,SSI_DataFarmeSize_Type cfg)
{
    uint32_t CTL_CFG= SSIx->CTRLR0;
    
    SSIx->SSIENR = DISABLE;
    SSI_ClearInterrupt(SSIx);

    if(IS_SPIM0(SSIx))
    {
        CTL_CFG &= (~SSIC_CTRLR0_DFS_MSK);
        CTL_CFG |= (cfg<< SSIC_CTRLR0_DFS_POS);
    }
    else
    {
        if(cfg > SSI_DATA_FRAME_SIZE_16BIT)
        {
            CTL_CFG &= (~SSI_CTRLR0_DFS_32_MSK);
            CTL_CFG &= (~SSI_CTRLR0_DFS_MSK);
            CTL_CFG |= (cfg<< SSI_CTRLR0_DFS_32_POS| cfg << SSI_CTRLR0_DFS_POS) ;   
        }
        else
        {
            CTL_CFG &= (~SSI_CTRLR0_DFS_32_MSK);
            CTL_CFG |= (cfg<< SSI_CTRLR0_DFS_32_POS);
        }   
    }
    SSIx->CTRLR0 = CTL_CFG;
    SSIx->SSIENR = ENABLE;
}


void SSI_UpdateDmaControl(SSI_TypeDef   *SSIx,bool rx_en,uint16_t rx_thd,bool tx_en,uint16_t tx_thd)
{
    
    SSIx->SSIENR = DISABLE;
    SSI_ClearInterrupt(SSIx);
    
    if(rx_en)
    {
        SSIx->DMACR |= SSI_DMACR_RDMAE_MSK;
        SSIx->DMARDLR = rx_thd;
    }
    else   
        SSIx->DMACR &= ~SSI_DMACR_RDMAE_MSK;

    if(tx_en)
    {
        SSIx->DMACR |= SSI_DMACR_TDMAE_MSK;
        SSIx->DMATDLR = tx_thd;
    }
    else   
        SSIx->DMACR &= ~SSI_DMACR_TDMAE_MSK;
    

}


void SSI_UpdateClock(SSI_TypeDef   *SSIx ,uint16_t clock_div)
{
    SSIx->SSIENR = DISABLE;
    SSI_ClearInterrupt(SSIx);
    /*
     Fsclk_out = Fssiclk/clock_div
    */
    SSIx->BAUDR =  clock_div;
    SSIx->SSIENR = ENABLE;
}



/**
*name: SSI_is_busy
*
**/
bool SSI_IsBusy(SSI_TypeDef   *SSIx)
{
    return ((SSIx->SR & SSI_SR_BUSY_MSK)? true : false);
}

/**
*name: SSI_ClearInterrupt
*
**/
uint32_t  SSI_ClearInterrupt(SSI_TypeDef   *SSIx)
{
    return SSIx->ICR;
}
uint32_t SSI_ClearTxFifoOverflowInterrupt(SSI_TypeDef   *SSIx)
{
    return SSIx->TXOICR;
}
uint32_t SSI_ClearRxFifoOverflowInterrupt(SSI_TypeDef   *SSIx)
{
    return SSIx->RXOICR;
}
uint32_t SSI_ClearRxFifoUnderflowInterrupt(SSI_TypeDef   *SSIx)
{
    return SSIx->RXUICR;
}








