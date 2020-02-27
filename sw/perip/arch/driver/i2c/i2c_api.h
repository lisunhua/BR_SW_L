/*
 *++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 * Copyright (c) 1999-2018 Barrot Technology Limited
 *
 * All rights reserved.
 *
 *------------------------------------------------------------------------------
 */
/**
 * @file    i2c_api.h
 * @brief   This file provides the i2c api functions.
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

#ifndef __I2C_API_H__
#define __I2C_API_H__

#ifdef __cplusplus
 extern "C" {
#endif

#include <stdbool.h>
#include <stdio.h>
#include <stdint.h>

typedef enum /*This is a list of I2C status that cannot be modified  */
{
/*00*/    STATUS_ACTIVITY,
/*01*/    STATUS_TX_FIFO_NOT_FULL,
/*02*/    STATUS_TX_FIFO_EMPTY,
/*03*/    STATUS_RX_FIFO_NOT_EMPTY,
/*04*/    STATUS_RX_FIFO_FULL ,
/*05*/    STATUS_MASTER_NOT_IDLE,
/*06*/    STATUS_SLAVE_NOT_IDLE,
/*07*/    STATUS_MASTER_HOLD_TX_FIFO_EMPTY,                  /* Master holds the bus due to Tx FIFO is empty*/
/*08*/    STATUS_MASTER_HOLD_RX_FIFO_FULL,                   /* Master holds the bus due to Rx FIFO is full */
/*09*/    STATUS_SLAVE_HOLD_TX_FIFO_EMPTY,                   /* Slave holds the bus due to Tx FIFO is empty*/
/*10*/    STATUS_SLAVE_HOLD_RX_FIFO_FILL,                    /* Slave holds the bus due to Rx FIFO is full  */ 
/*11*/    STATUS_SDA_STUCK_NOT_RECOVERED,                    /* SDA Stuck at low is recovered after recovery mechanism.*/
/*XX*/
/*16*/    STATUS_SMBUS_QUICK_CMD_BIT,                        /* SMBUS QUICK CMD Read/write is set to 1.*/
/*17*/    STATUS_SMBUS_SLAVE_ADDR_VALID,                     /* SMBUS Slave Address is Valid.*/
/*18*/    STATUS_SMBUS_SLAVE_ADDR_RESOLVED,                  /* SMBUS Slave Address is Resolved */
/*19*/    STATUS_SMBUS_SUSPEND_STATUS,                       /* SMBUS System is in Suspended mode */
/*20*/    STATUS_SMBUS_ALERT_STATUS,                         /* SMBUS Alert is asserted*/


}I2C_Status_Type;

typedef enum
{
    I2C_SPEED_STANDARD = 1,
    I2C_SPEED_FAST,
    I2C_SPEED_HIGH
}I2C_SpeedMode;
/*
1: standard mode   (100 kbit/s)
2: fast mode       (<=400 kbit/s) or fast mode plus (<=1000Kbit/s)
3: high speed mode (3.4 Mbit/s)
*/
typedef struct
{
    I2C_SpeedMode   Smode;
    uint16_t        slc_l;        //This data sets the SCL clock low -period count. slc_l=(PCLK/baud/2)
    uint16_t        slc_h;        //This data sets the SCL clock high-period count. slc_h=(PCLK/baud/2)
  
}I2CM_InitStruct;

extern const I2CM_InitStruct i2cm_default_cfg;  //standard mode   (100 kbit/s)

/**
  * @brief  Initializes the I2C peripheral according to the specified
  *         parameters in the I2C_InitInfo_Type.
  *
  * @param  cfg: pointer to a I2CM_InitStruct structure that
  *         contains the configuration information for the specified I2C peripheral.
  * @retval None
  */
void i2cm_init(const I2CM_InitStruct *cfg);

/**
    * @brief  I2c update Target Device addr
    * @param  device_addr: Target Device addr
    * @retval None
    */
void i2cm_UpdateDeviceAddr(uint8_t device_addr);

/**
    * @brief  I2c Read data continuously
    * @param  buffer: This data pointer will be read from FIFO
    * @param  size: The data length
    * @retval None
    */
bool i2cm_Read (uint8_t *buffer,uint16_t size);

/**
    * @brief  I2c write data continuously
    * @param  buffer: The data pointer will be write to the fifo
    * @param  size: The data length
    * @retval None
    */
bool i2cm_Write(uint8_t *buffer,uint16_t size);

#ifdef __cplusplus
}
#endif

#endif /* __I2C_API_H__ */

