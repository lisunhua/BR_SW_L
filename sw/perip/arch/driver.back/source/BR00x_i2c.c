/*
 *++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 * Copyright (c) 1999-2018 Barrot Technology Limited
 *
 * All rights reserved.
 *
 *------------------------------------------------------------------------------
 */
/**
 * @file    BR00x_i2c.c
 * @brief    This file provides the i2c firmware functions.
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
#include "BR00x_i2c.h"
#include "BR00x_i2c_if.h"
#include "system_BR00x.h"
#include "cm_printf.h"



#define  I2C_ENABLE_BIT   1
#define  I2C_DISABLE_BIT  0

static uint32_t I2C_GetControlParams(I2C_InitInof_Type  *I2C_InitStru);
static void I2C_SetClockSclCountParams(I2C_TypeDef  *I2Cx , I2C_ParamMaxSpeedMode max_speed, uint32_t sclH,uint32_t sclL);
static uint32_t I2C_SetTargerAddressConfigParams(I2C_InitInof_Type *I2C_InitStru);


static  uint32_t   i2c_SubData(i2c_DataCmd data)
{
    return (data.data|data.com<<8|data.stop<<9|data.restart<<10|data.non_seq <<11);
}


/*This function is primarily used to get a parameter by returning the configuration that is worth to the register */
static uint32_t I2C_GetControlParams(I2C_InitInof_Type  *I2C_InitStru)
{
    uint32_t reg_control_mask = (\
    ((I2C_InitStru->master_en << I2C_IC_CON_MASTER_MODE_POS)&I2C_IC_CON_MASTER_MODE_MSK )|
    ((I2C_InitStru->max_speed<< I2C_IC_CON_SPEED_POS)&I2C_IC_CON_SPEED_MSK) |
    ((I2C_InitStru->slave_addr_type << I2C_IC_CON_IC_10BITADDR_SLAVE_POS)&I2C_IC_CON_IC_10BITADDR_SLAVE_MSK) |
    ((I2C_InitStru->master_addr_type << I2C_IC_CON_IC_10BITADDR_MASTER_POS)&I2C_IC_CON_IC_10BITADDR_MASTER_MSK) |
    ((I2C_InitStru->restart_en << I2C_IC_CON_IC_RESTART_EN_POS) &I2C_IC_CON_IC_RESTART_EN_MSK)|
    ((I2C_InitStru->slave_en << I2C_IC_CON_IC_SLAVE_DISABLE_POS) &I2C_IC_CON_IC_SLAVE_DISABLE_MSK)|

    ((I2C_InitStru->slave_stop_det_if_addressed_en   << I2C_IC_CON_STOP_DET_IFADDRESSED_POS) &I2C_IC_CON_STOP_DET_IFADDRESSED_MSK)|
    ((I2C_InitStru->master_stop_det_if_addressed_en << I2C_IC_CON_STOP_DET_IF_MASTER_ACTIVE_POS)&I2C_IC_CON_STOP_DET_IF_MASTER_ACTIVE_MSK) |
    ((I2C_InitStru->tx_empty_intr_en << I2C_IC_CON_TX_EMPTY_CTRL_POS) &I2C_IC_CON_TX_EMPTY_CTRL_MSK)|
    ((I2C_InitStru->rx_fifo_full_hold_control_en << I2C_IC_CON_RX_FIFO_FULL_HLD_CTRL_POS) &I2C_IC_CON_RX_FIFO_FULL_HLD_CTRL_MSK)|

    ((I2C_InitStru->master_bus_clear_feature_en << I2C_IC_CON_BUS_CLEAR_FEATURE_CTRL_POS) &I2C_IC_CON_BUS_CLEAR_FEATURE_CTRL_MSK)|
    ((I2C_InitStru->optional_SAR_address_en << I2C_IC_CON_OPTIONAL_SAR_CTRL_POS) &I2C_IC_CON_OPTIONAL_SAR_CTRL_MSK)|
    ((I2C_InitStru->SMBUS_slave_quick_en << I2C_IC_CON_SMBUS_SLAVE_QUICK_EN_POS)&I2C_IC_CON_SMBUS_SLAVE_QUICK_EN_MSK) |
    ((I2C_InitStru->SMBUS_ARP_contral_en << I2C_IC_CON_SMBUS_ARP_EN_POS)&I2C_IC_CON_SMBUS_ARP_EN_MSK) |
    ((I2C_InitStru->SMBUS_persistent_slave_addr_en << I2C_IC_CON_SMBUS_PERSISTENT_SLV_ADDR_EN_POS)&I2C_IC_CON_SMBUS_PERSISTENT_SLV_ADDR_EN_MSK));
                                   
    return reg_control_mask;
}


static void I2C_SetClockSclCountParams(I2C_TypeDef  *I2Cx , I2C_ParamMaxSpeedMode max_speed, uint32_t sclH,uint32_t sclL)
{
    switch(max_speed)
    {
        case PARAM_MAX_SPEED_RESERVED:
            break;
        case PARAM_MAX_SPEED_STANDARD:
            I2Cx->IC_SS_SCL_HCNT =  (sclH)&I2C_IC_IC_SS_SCL_HCNT_MSK;
            I2Cx->IC_SS_SCL_LCNT  = (sclL)&I2C_IC_IC_SS_SCL_LCNT_MSK;
            break;
        case PARAM_MAX_SPEED_FAST:
            I2Cx->IC_FS_SCL_HCNT =  (sclH)&I2C_IC_IC_FS_SCL_HCNT_MSK;
            I2Cx->IC_FS_SCL_LCNT  = (sclL)&I2C_IC_IC_FS_SCL_LCNT_MSK;
            break;
        case PARAM_MAX_SPEED_HIGH:
            I2Cx->IC_HS_SCL_HCNT =  (sclH)&I2C_IC_IC_HS_SCL_HCNT_MSK;
            I2Cx->IC_HS_SCL_LCNT  = (sclL)&I2C_IC_IC_HS_SCL_LCNT_MSK;
            break;
    }

}



static uint32_t I2C_SetTargerAddressConfigParams(I2C_InitInof_Type  *I2C_InitStru) 
{
    uint32_t targer_address_mask  =  ((( I2C_InitStru->I2C_target_address & I2C_IC_TAR_IC_TAR_MSK))<<I2C_IC_TAR_IC_TAR_POS |
    (I2C_InitStru->general_call_or_start_byte<<I2C_IC_TAR_GC_OR_START_POS)|
    (I2C_InitStru->general_call_or_start_byte_en<<I2C_IC_TAR_SPECIAL_POS)|
    (I2C_InitStru->targer_address_type<<I2C_IC_TAR_IC_10BITADDR_MASTER_POS)|
    (I2C_InitStru->programming_device_id_en<<I2C_IC_TAR_DEVICE_ID_POS)|
    (I2C_InitStru->programming_SMBUS_quick_cmd_en<<I2C_IC_TAR_SMBUS_QUICK_CMD_POS));

    return targer_address_mask;
     
}

void I2C_DeInit(I2C_TypeDef  *I2Cx)
{
#ifdef BR1051Axx
    if(I2Cx==I2C0)
    {
        SystemDevRstCtl(I2C0_SwRst);
    }
    else
    {
        SystemDevRstCtl(I2C1_SwRst);
    }
#endif
    
#if  defined(BR002)||defined(BR003)

    SystemDevRstCtl(I2C_SwRst);
    
#endif
    memset(I2Cx, 0, sizeof(DMA_TypeDef));
}


void I2C_ReadingDeviceId(I2C_TypeDef  *I2Cx )
{
    I2Cx->IC_ENABLE  &= ~I2C_IC_IC_ENABLE_ENBALE_MSK;
    I2Cx->IC_TAR   |= I2C_IC_TAR_SPECIAL_MSK|I2C_IC_TAR_DEVICE_ID_MSK;
    I2Cx->IC_ENABLE  |= I2C_IC_IC_ENABLE_ENBALE_MSK;
    I2Cx->IC_ENABLE =0x03;
}


/**
  * @brief  Initializes the I2C peripheral according to the specified
  *         parameters in the I2C_InitInfo_Type.
  *
  * @param  I2C_InitStru: pointer to a I2C_InitInfo_Type structure that
  *         contains the configuration information for the specified I2C peripheral.
  * @retval None
  */
void I2C_Init(I2C_TypeDef  *I2Cx,I2C_InitInof_Type  *I2C_InitStru)
{
    I2C_ClearCombinedInterruptAll(I2Cx);
 
    /* Write to IC_ENABLE  register to disable*/
    I2Cx->IC_ENABLE  &= ~I2C_IC_IC_ENABLE_ENBALE_MSK;

    /* Program IC_CON register fields  */ 
    I2Cx->IC_CON  = I2C_GetControlParams(I2C_InitStru);

    /*Set address of target Slave by writing it to SAR*/
    I2Cx->IC_TAR  = I2C_SetTargerAddressConfigParams(I2C_InitStru);
    I2Cx->IC_SAR  =(I2C_InitStru->salve_address &I2C_IC_SAR_IC_SAR_MSK);

    /* Write to IC_SS_HCNT to set HIGH and LOW  period of SCL*/
    I2C_SetClockSclCountParams(I2Cx,I2C_InitStru->max_speed,I2C_InitStru->slc_h,I2C_InitStru->slc_l);
    
    /* Write to IC_INTR_MASK to enable all interrupts*/
    I2Cx->INTR_MASK  = I2C_InitStru->interrupt_unmask;

    /*configuration  RX /TX threshold level*/
    I2Cx->RX_TL  = I2C_InitStru->fifo_receive_threshold_level;
    I2Cx->TX_TL  = I2C_InitStru->fifo_transmit_threshold_level;

    /*configuration DMA */
    I2Cx->IC_DMA_CR  |= ((I2C_InitStru->dma_rx_en & 0x01) <<I2C_IC_DMA_CR_RDMAE_POS ) |
        ((I2C_InitStru->dma_tx_en & 0x01 )<<I2C_IC_DMA_CR_TDMAE_POS);
    
    I2Cx->IC_DMA_TDLR |= I2C_InitStru->dma_tx_data_level;
    I2Cx->IC_DMA_RDLR |= I2C_InitStru->dma_rx_data_level;

    /* enable i2c */
    I2Cx->IC_ENABLE |= I2C_IC_IC_ENABLE_ENBALE_MSK;
   
}


bool  I2C_ReadDate(I2C_TypeDef  *I2Cx  ,uint8_t *rx, uint16_t rlen,bool rstop)
{
    uint16_t i = 0;
    bool success =false;
    i2c_DataCmd  data;
    
    if((!rx)||(rlen ==0))
        success = false ;
    else
    {
        for(i=0;i<rlen;i++)
        {
            data.com = read;
            data.non_seq = 0;
            data.stop = 0;
            data.restart = 1;
            data.data=0;

            for(i=0;i<rlen;i++)
            {
                if(i==rlen-1 && rstop)
                data.stop = 1;
                rx[i] =  I2C_ReadByte(I2Cx,i2c_SubData(data));
                data.restart = 0;
             }

        }
    }

    return success;

}

bool  I2C_WriteDate(I2C_TypeDef  *I2Cx  ,uint8_t *tx, uint16_t tlen,bool tstop)
{
    uint16_t i = 0;
    bool success =false;
    i2c_DataCmd  data;
   
    if((!tx )|| (tlen ==0 ))
        success = false ;
    else
    {
        data.com = write;
        data.non_seq = 0;
        data.stop = 0;
        data.restart = 1;
        
        for(i=0;i<tlen;i++)
        {
            data.data = tx[i];
            if(i==tlen-1  && tstop)
                data.stop = 1;
            I2C_WriteByte(I2Cx,i2c_SubData(data));
            data.restart = 0;
        }
    }

     return success;

}

void I2C_WriteByte(I2C_TypeDef  *I2Cx  , uint32_t data)
{
    uint16_t i=10000;
    I2Cx->DATA_CMD = data;
    while((!((I2Cx->IC_STATUS>>STATUS_TX_FIFO_EMPTY) & 0x01)) && i>0){i--;}
}

uint8_t  I2C_ReadByte(I2C_TypeDef  *I2Cx  , uint32_t cmd)
{
    uint16_t i=10000;
    I2Cx->DATA_CMD =cmd;
    while((!((I2Cx->IC_STATUS>>STATUS_RX_FIFO_NOT_EMPTY) & 0x01))&& i>0){i--;}
    return  (uint8_t )(I2Cx->DATA_CMD &0x00ff);    
}


void I2C_GetRxTxThreshold(I2C_TypeDef  *I2Cx,uint32_t *TX_TL,uint32_t *RX_TL)
{
    *TX_TL = I2Cx->IC_TXFLR;
    *RX_TL = I2Cx->IC_RXFLR;
}


void I2C_SetCmdData(I2C_TypeDef  *I2Cx  , uint32_t data)
{
    I2Cx->DATA_CMD = data;
}


uint32_t  I2C_GetCmdData(I2C_TypeDef  *I2Cx)
{
    return I2Cx->DATA_CMD;    
}


bool I2C_ClearSMBUSInterrupt(I2C_TypeDef  *I2Cx  , I2C_SMBUSInterrupt_Type type)
{
    if(I2Cx->IC_CLR_SMBUS_INTR>>type & 0x01)
    {
           return  I2Cx->IC_CLR_SMBUS_INTR  =  (0x01ul)<<type; 
    }
    else
    return false;
}

bool   I2C_ClearInterrupt(I2C_TypeDef  *I2Cx  , I2C_Interrupt_Type type)   
{
    switch(type)
    {
        case RX_UNDER_TYPE: 
            return  (I2Cx->IC_CLR_RX_UNDER &0x01);
        case RX_OVER_TYPE:
            return  (I2Cx->IC_CLR_RX_OVER &0x01);
        //case RX_FULL_TYPE: /* no support*/
        case TX_OVER_TYPE:
            return  (I2Cx->IC_CLR_TX_OVER &0x01);
        //case TX_EMPTY_TYPE:/* no support*/
        case RD_REQ_TYPE:
            return  (I2Cx->IC_CLR_RD_REQ &0x01);
        case TX_ABRT_TYPE:
            return  (I2Cx->IC_CLR_TX_ABRT &0x01);
        case RX_DONE_TYPE:
            return  (I2Cx->IC_CLR_RX_DONE &0x01);
        case ACTIVITY_TPYE:
            return  (I2Cx->IC_CLR_ACTIVITY &0x01);
        case STOP_DET_TYPE:
            return  (I2Cx->IC_CLR_STOP_DET &0x01);
        case START_DET_TYPE:
            return  (I2Cx->IC_CLR_START_DET &0x01);
        case GEN_CALL_TYPE:
            return  (I2Cx->IC_CLR_GEN_CALL &0x01);
        case RESTART_DET_TYPE:
            return  (I2Cx->IC_CLR_RESTART_DET &0x01);
       // case MASTER_ON_HOLD_TYPE:/* no support*/	
        case SLC_STUCK_AT_LOW:
            return  (I2Cx->IC_CLR_SCL_STUCK_DET &0x01);
         default:
            break;
    }
    return false;
}



bool I2C_ClearCombinedInterruptAll(I2C_TypeDef  *I2Cx)
{
    return  (I2Cx->IC_CLR_INTR &0x01);
}


bool I2C_ClearRestartInterruptDet(I2C_TypeDef  *I2Cx)
{
   return  (I2Cx->IC_CLR_RESTART_DET&0x01);
}

bool I2C_ClearSclStuckInterruptDet(I2C_TypeDef  *I2Cx)
{
   return  (I2Cx->IC_CLR_SCL_STUCK_DET&0x01);
}




