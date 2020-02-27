/*
 *++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 * Copyright (c) 1999-2018 Barrot Technology Limited
 *
 * All rights reserved.
 *
 *------------------------------------------------------------------------------
 */
/**
 * @file    BR00x_i2s.c
 * @brief    This file provides the i2s firmware functions.
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
#include "BR00x_i2s.h"
#include "system_BR00x.h"



#define I2S_REG_CONFIG(X,Y,Z)    ((Y) ? (X |= Z) : (X &= ~Z))
#define ENABLE    1
#define DISABLE   0


#define I2S_IS_RX_MODE(X)  (X & DATA_RX )
#define I2S_IS_TX_MODE(X)  ((X & DATA_TX) >> 1)

#define I2S_CCR_WSS_Pos (3ul) /*!< Position of WSS field. */
#define I2S_CCR_WSS_Msk (0x03ul << I2S_CCR_WSS_Pos) /*!< Bit mask of WSS field. */ 

/*  Interrupt Mask Register */
#define I2S_IMR_RX_DAM_Pos (0ul) /*!< Position of RX_DAM field. */
#define I2S_IMR_RX_DAM_Msk (0x01ul << I2S_IMR_RX_DAM_Pos) /*!< Bit mask of RX_DAM field. */ 

#define I2S_IMR_RX_FIFO_OVERRUN_Pos (1ul) /*!< Position of FIFO_OVERRUN field. */
#define I2S_IMR_RX_FIFO_OVERRUN_Msk (0x01ul << I2S_IMR_RX_FIFO_OVERRUN_Pos) /*!< Bit mask of FIFO_OVERRUN field. */ 

#define I2S_IMR_TX_FIFO_EMPTY_Pos (4ul) /*!< Position of FIFO_EMPTY field. */
#define I2S_IMR_TX_FIFO_EMPTY_Msk (0x01ul << I2S_IMR_TX_FIFO_EMPTY_Pos) /*!< Bit mask of FIFO_EMPTY field. */

#define I2S_IMR_TX_FIFO_OVERRUN_Pos (5ul) /*!< Position of FIFO_OVERRUN field. */
#define I2S_IMR_TX_FIFO_OVERRUN_Msk (0x01ul << I2S_IMR_TX_FIFO_OVERRUN_Pos) /*!< Bit mask of FIFO_OVERRUN field. */ 


static I2S_Chn_TypeDef  * I2S_SeletDevice(I2S_TypeDef *I2Sx)
{
    if(I2SM == I2Sx)
        return &I2SM->I2S_Ch;
    else
       return &I2SS->I2S_Ch;
}


void I2S_DeInit(I2S_TypeDef  *I2Sx)
{
    #if  defined(BR002)||defined(BR003)
    if(I2Sx==I2SM)
    {
        SystemDevRstCtl(I2SM_SwRst);
    }
    else
    {
        SystemDevRstCtl(I2SS_SwRst);
    }
    #endif
    memset(I2Sx, 0, sizeof(DMA_TypeDef));
}


uint32_t  I2S_GetLeftReceiveData(I2S_TypeDef *I2Sx)
{
    return I2S_SeletDevice(I2Sx)->LRBR;
}

uint32_t  I2S_GetRightReceiveData(I2S_TypeDef *I2Sx )
{
    return I2S_SeletDevice(I2Sx)->RRBR;
}

void  I2S_SetLeftTransmitData(I2S_TypeDef *I2Sx ,uint32_t data)
{
    I2S_SeletDevice(I2Sx)->LTHR = data;
}
void  I2S_SetRightTransmitData(I2S_TypeDef *I2Sx ,uint32_t data)
{
    I2S_SeletDevice(I2Sx)->RTHR = data;
}

void  I2S_ReceiveFifoReset(I2S_TypeDef *I2Sx )
{
    I2S_SeletDevice(I2Sx)->RFF= ENABLE;
}
void  I2S_TransmitFifoReset( I2S_TypeDef *I2Sx )
{
    I2S_SeletDevice(I2Sx)->TFF= ENABLE;
}


void I2S_GeneratrClock(I2S_TypeDef *I2Sx,bool status)
{
    if(status)
        I2Sx->CER  = ENABLE;
    else
        I2Sx->CER  = DISABLE;
    
}

void I2S_SetInterruptMask(I2S_TypeDef *I2Sx, I2S_IntCtlMask *IntCtlMask)
{
    I2S_Chn_TypeDef *device_chn = I2S_SeletDevice(I2Sx);

    device_chn->IMR = ((IntCtlMask->rx_dma_available_interrupt_mask<<I2S_IMR_RX_DAM_Pos)|
        (IntCtlMask->rx_fifo_overrun_interrupt_mask<<I2S_IMR_RX_FIFO_OVERRUN_Pos)|
        (IntCtlMask->tx_fifo_empty_interrupt_mask<<I2S_IMR_TX_FIFO_EMPTY_Pos)|
        (IntCtlMask->tx_fifo_overrun_interrupt_mask<<I2S_IMR_TX_FIFO_OVERRUN_Pos)); 

}


void I2S_Init(I2S_TypeDef *I2Sx , I2S_InitInof_Type  *I2S_InitStru)
{
    I2S_Chn_TypeDef *device_chn = I2S_SeletDevice(I2Sx);
    I2Sx->IER = DISABLE;
    I2S_GeneratrClock(I2Sx,false);
    I2Sx->CCR = (I2S_InitStru->clock_gating_type | I2S_InitStru->clock_type<<I2S_CCR_WSS_Pos);
  
    if(I2S_IS_RX_MODE(I2S_InitStru->dirct_type))
    {   
        device_chn->RER  = DISABLE;
        device_chn->RCR  = I2S_InitStru->data_resl_type ;
        device_chn->RFCR = I2S_InitStru->interrupt_level;
        
        device_chn->RER = ENABLE; 
        I2Sx->IRER  = ENABLE;
        I2Sx->RXFFR = ENABLE;     
    }

    if(I2S_IS_TX_MODE(I2S_InitStru->dirct_type))
    {
        device_chn->TER = DISABLE;
        device_chn->TCR=  I2S_InitStru->data_resl_type;
        device_chn->TFCR= I2S_InitStru->interrupt_level;
        
        device_chn->TER=ENABLE;
        I2Sx->ITER  = ENABLE;
        I2Sx->TXFFR = ENABLE;
    }
    
    I2S_SetInterruptMask(I2Sx,&I2S_InitStru->IntCtlMask);
    I2Sx->IER = ENABLE;
    I2S_ReceiveFifoReset(I2Sx);
    I2S_TransmitFifoReset(I2Sx);
        

}

bool  I2S_GetInterruptStatus(I2S_TypeDef *I2Sx,I2S_Interrupt_Type  interrupt_type)
{
    switch(interrupt_type)
    {
        case I2S_RX_AVAILABLE_DAM:
            return(( I2S_SeletDevice(I2Sx)->ISR>>I2S_IMR_RX_DAM_Pos)&0x01);
        case I2S_RX_FIFO_OVERRUN:
            return(( I2S_SeletDevice(I2Sx)->ISR>>I2S_IMR_RX_FIFO_OVERRUN_Pos)&0x01);
        case I2S_TX_FIFO_EMPTY:
            return(( I2S_SeletDevice(I2Sx)->ISR>>I2S_IMR_TX_FIFO_EMPTY_Pos)&0x01);
        case I2S_TX_FIFO_OVERRUN:
            return(( I2S_SeletDevice(I2Sx)->ISR>>I2S_IMR_TX_FIFO_OVERRUN_Pos)&0x01);
    }
    return false;
}


bool  I2S_ClearRxOverrunInterrupt(I2S_TypeDef *I2Sx)
{
    return( I2S_SeletDevice(I2Sx)->ROR&0x01);
}

bool  I2S_ClearTxOverrunInterrupt(I2S_TypeDef *I2Sx)
{
    return( I2S_SeletDevice(I2Sx)->TOR&0x01);
}


void I2S_ResetTxDma(I2S_TypeDef *I2Sx )
{
    I2Sx->RTXDMA = ENABLE;
}

void I2S_ResetRxDma(I2S_TypeDef *I2Sx )
{
    I2Sx->RRXDMA=ENABLE;
}

uint32_t I2S_GetTxDmaPr(I2S_TypeDef *I2Sx)
{
    return (uint32_t)&(I2Sx->TXDMA);
}

uint32_t  I2S_GetRxDmaPr(I2S_TypeDef *I2Sx )
{
    return (uint32_t)&(I2Sx->RXDMA);
}






