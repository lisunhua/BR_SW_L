/*
 *++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 * Copyright (c) 1999-2018 Barrot Technology Limited
 *
 * All rights reserved.
 *
 *------------------------------------------------------------------------------
 */
/**
 * @file    i2c.c
 * @brief   This file provides the i2c firmware functions.
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

#include "BR00x_config.h"
#include "system_BR00x.h"
#include "i2c_api.h"
#include "cm_printf.h"

#define  READ                   0x01ul
#define  WRITE                  0x00ul
#define  I2C_CMD_BIT            8
#define  RETRY_TIMES            (100000) 

#define  I2C_SETDATA(X)         (I2C->DATA_CMD =(uint32_t)X)
#define  I2C_GETDATA()          (I2C->DATA_CMD)

#define  I2C_WAIT_TIMEOUT(X)            while(X){\
    int32_t tep = 0;  if( tep > RETRY_TIMES ) return false; else tep++;\
}
static I2C_TypeDef   *I2C       = I2C0;

const I2CM_InitStruct i2cm_default_cfg= {
    .Smode = I2C_SPEED_STANDARD,
    .slc_l = 120,
    .slc_h = 120,
};

static void I2C_SetClockSclCountParams(I2C_SpeedMode max_speed, uint32_t sclH,uint32_t sclL)
{
    switch(max_speed)
    {
        case I2C_SPEED_STANDARD:
            I2C->IC_SS_SCL_HCNT =  (sclH)&0x0fffful;
            I2C->IC_SS_SCL_LCNT  = (sclL)&0x0fffful;
            break;
        case I2C_SPEED_FAST:
            I2C->IC_FS_SCL_HCNT =  (sclH)&0x0fffful;
            I2C->IC_FS_SCL_LCNT  = (sclL)&0x0fffful;
            break;
        case I2C_SPEED_HIGH:
            I2C->IC_HS_SCL_HCNT =  (sclH)&0x0fffful;
            I2C->IC_HS_SCL_LCNT  = (sclL)&0x0fffful;
            break;
    }

}

void I2C_DeInit(void)
{
    SystemDevRstCtl(I2C_SwRst);
}

/**
  * @brief  Initializes the I2C peripheral according to the specified
  *         parameters in the I2C_InitInfo_Type.
  *
  * @param  cfg: pointer to a I2CM_InitStruct structure that
  *         contains the configuration information for the specified I2C peripheral.
  * @retval None
  */
void i2cm_init(const I2CM_InitStruct *cfg)
{
    /* Clear Combined Interrupt;                            */
    ((void )(I2C->IC_CLR_INTR &0x01));
    /* Write to IC_ENABLE  register to disable              */
    I2C->IC_ENABLE      &= ~0x01ul ;
    /* Program IC_CON register fields -> master             */ 
    I2C->IC_CON         = 0x01ul |((cfg->Smode<<0x01)&0x03ul);
    /*Set address of target Slave by writing it to SAR      */
    I2C->IC_TAR         = 0; //default is 0, Must be updated before use 
    I2C->IC_SAR         = 0;
    /* Write to IC_SS_HCNT to set HIGH and LOW  period of SCL*/
    I2C_SetClockSclCountParams(cfg->Smode,cfg->slc_h,cfg->slc_l);
    /* Write to IC_INTR_MASK to enable all interrupts       */
    I2C->INTR_MASK      = 0xFFFFFFFF;
    /*configuration  RX /TX threshold level                 */
    I2C->RX_TL          = 0;
    I2C->TX_TL          = 0;
    /*configuration DMA                                     */
    I2C->IC_DMA_CR      = 0;
    I2C->IC_DMA_TDLR    = 0;
    I2C->IC_DMA_RDLR    = 0;
    /* enable i2c                                           */
    I2C->IC_ENABLE     |= 0x01ul;
}

/**
    * @brief  I2c update Target Device addr
    * @param  device_addr: Target Device addr
    * @retval None
    */
void i2cm_UpdateDeviceAddr(uint8_t device_addr)
{
    uint32_t tc_tar = I2C->IC_TAR;
    /* Write to IC_ENABLE  register to disable*/
    I2C->IC_ENABLE  &= ~0x01ul;
    tc_tar          |= (device_addr & 0xFFul);
    /*Update Device Addr*/
    I2C->IC_TAR      = tc_tar; 
    /* enable i2c */
    I2C->IC_ENABLE  |= 0x01ul;
}

/**
    * @brief  I2c write data continuously
    * @param  buffer: The data pointer will be write to the fifo
    * @param  size: The data length
    * @retval None
    */
bool i2cm_Read (uint8_t *buffer,uint16_t size)
{    
    int32_t i=0,timeout=0;
    uint16_t rx_idx=size,st_idx=0;
    if(buffer == 0 || size == 0 )
        return false;
    
    while(rx_idx>0)
    {
        if(st_idx < size && 
            (I2C->IC_STATUS & (0x01ul << STATUS_TX_FIFO_NOT_FULL)) && 
            (!(I2C->IC_STATUS & (0x01ul << STATUS_RX_FIFO_FULL))))
        {
            I2C_SETDATA(READ<<I2C_CMD_BIT);       
            st_idx++;
            timeout = 0;
        } 
        if(I2C->IC_STATUS & (0x01ul << STATUS_RX_FIFO_NOT_EMPTY)){
            buffer[i++] = I2C_GETDATA() & 0x00ff;
            rx_idx--;
            timeout = 0;
        }
        timeout++;
        if(timeout >RETRY_TIMES){
            //c_printf("debug %d,%d,sta=%X\r\n",st_idx,rx_idx,I2C->IC_STATUS);
            return false;
            
        }
    }
    
    return true;
}

/**
    * @brief  I2c Read data continuously
    * @param  buffer: This data pointer will be read from FIFO
    * @param  size: The data length
    * @retval None
    */
bool i2cm_Write(uint8_t *buffer,uint16_t size)
{
    int32_t i;
    if(buffer == 0 || size == 0 )
        return false;
        
    for(i=0;i<size;i++)
    {
        I2C_WAIT_TIMEOUT(!(I2C->IC_STATUS & 0x01 << STATUS_TX_FIFO_NOT_FULL));
        I2C_SETDATA(buffer[i]|WRITE<<I2C_CMD_BIT);
    }
    return true;
}





