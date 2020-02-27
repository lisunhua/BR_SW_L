/*
 *++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 * Copyright (c) 1999-2018 Barrot Technology Limited
 *
 * All rights reserved.
 *
 *------------------------------------------------------------------------------
 */
/**
 * @file    BR00x_i2c_eeprom.c
 * @brief    This file provides the i2c_eeprom firmware functions.
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
#include "BR00x_i2c_erom.h"
#include "system_BR00x.h"
#include "BR00x_i2c.h"
#include <string.h>

void  EEPROM_WriteByte(uint16_t addr ,uint8_t data)
{

    uint8_t data_buff[2+1];

    data_buff[0]= addr>>8;
    data_buff[1]=addr&0x00ff;
    data_buff[2] =data;
    I2C_WriteDate(I2C0,data_buff,3,1);

}


void  EEPROM_WritePage(uint16_t addr ,uint8_t *data,uint16_t dlen)
{

    uint8_t data_buff[2+dlen];
    data_buff[0]= addr>>8;
    data_buff[1]=addr&0x00ff;
    memcpy(&data_buff[2],data,dlen); 
    I2C_WriteDate(I2C0,data_buff,2+dlen,1);

}


uint8_t  EEPROM_ReadCurrentByte(void)
{
    uint8_t data;
    I2C_ReadDate(I2C0,&data,1,1);
    return data;
}


uint16_t  EEPROM_ReadByte(uint16_t addr )
{

    uint8_t data_buff[2];
    data_buff[0]= addr>>8;
    data_buff[1]=addr&0x00ff;
    I2C_WriteDate(I2C0,data_buff,2,0);
    return EEPROM_ReadCurrentByte();
}


void EEPROM_SequentialRead(uint16_t addr,uint8_t *data,uint16_t len)
{
    uint8_t data_buff[2];
    data_buff[0]= addr>>8;
    data_buff[1]=addr&0x00ff;
    I2C_WriteDate(I2C0,data_buff,2,0);
    I2C_ReadDate(I2C0,data,len,1);
}






