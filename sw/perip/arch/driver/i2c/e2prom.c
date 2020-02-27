/*
 *++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 * Copyright (c) 1999-2018 Barrot Technology Limited
 *
 * All rights reserved.
 *
 *------------------------------------------------------------------------------
 */
/**
 * @file    e2prom.c
 * @brief   This file provides the i2c_eeprom firmware functions.
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

#include <string.h>
#include "system_BR00x.h"
#include "i2c_api.h"
#include "e2prom_api.h"

extern  void MCU_Sleep(unsigned int ms);

#define EEPROM_DEVIVE_ADDRESS               (0x50)
#define EEPROM_DEVIVE_PAGE_SIZE             (0x20)

bool eeprom_init(void)
{
    uint8_t epdata[1]={0};
    i2cm_UpdateDeviceAddr(EEPROM_DEVIVE_ADDRESS);
    MCU_Sleep(5);
    return eeprom_cur_addr_read(epdata,1);
}

//no need
bool eeprom_reset(void)
{
    return true;
}

bool eeprom_byte_write(uint16_t addr, uint8_t data)
{
    uint8_t epdata[3] = {(addr>>8)&0xff,addr&0xff,data};
    return i2cm_Write(epdata,sizeof(epdata));
}

bool eeprom_page_write(uint16_t addr, uint8_t *buffer, uint16_t length)
{
    uint8_t epdata[2] = {(addr>>8)&0xff,addr&0xff};
 
    if(buffer==0 ||length == 0)
        return false;
    
    if(i2cm_Write(epdata,sizeof(epdata)))
        return i2cm_Write(buffer,length);
    else
        return false;   
}

bool eeprom_block_write(uint16_t addr, uint8_t *buffer, uint16_t length)
{
    uint16_t real_len;
    int16_t retrise;
    bool ret = false;
    
    if(buffer==0 ||length == 0)
        return false;
    
    while(length>0){
        real_len = length>=EEPROM_DEVIVE_PAGE_SIZE? EEPROM_DEVIVE_PAGE_SIZE:length;
        for(retrise=50;retrise>0;retrise--){
            ret = eeprom_page_write(addr,buffer,real_len);
            if(ret)
                break;
            MCU_Sleep(3);
        }
        if(!ret)
            break;
        addr   +=real_len;
        buffer +=real_len;
        length -=real_len;
        
        //wait for Stop Condition, i.e: Tx fifo empty
        if(length>0){ 
            MCU_Sleep(5);
        }
    }
    return ret;    
}

bool eeprom_cur_addr_read(uint8_t *buffer, uint16_t length)
{
    if(buffer==0 ||length == 0)
        return false;
    return i2cm_Read(buffer,length);
}


bool eeprom_random_addr_read(uint16_t addr, uint8_t *buffer, uint16_t length)
{
    uint8_t epdata[2] = {(addr>>8)&0xff,addr&0xff};
 
    if(buffer==0 ||length == 0)
        return false;
    
    if(i2cm_Write(epdata,sizeof(epdata)))
        return i2cm_Read(buffer,length);
    else
        return false;  
}







