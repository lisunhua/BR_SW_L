/*
 *++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 * Copyright (c) 1999-2018 Barrot Technology Limited
 *
 * All rights reserved.
 *
 *------------------------------------------------------------------------------
 */
/**
 * @file    BR00x_spi_flash.c
 * @brief    This file provides  the falsh  firmware functions.
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
#include "BR00x_spi_flash.h"
#include "system_BR00x.h"

#include "cm_printf.h"

#define SPI_DEBUGxx


SSI_TypeDef   *SPI_FLASH = SPIM0;


uint8_t  spi_ProgramBuff[256+4] = {0};

/**
  * @brief Spi delay function -about one ns.
  * @param  None.
  * @retval None
  */
static void SPI_DelayNs(void)
{
    uint32_t i;
    for( i=0;i<2;i++);
}

/**
  * @brief Spi delay function -about one ms.
  * @param  time:This data represents the time delay required.
  * @retval None
  */
static void SPI_DelayMs(uint32_t time)
{    
   uint32_t i ,count=time*1000;
   for(i=0;i<count;i++)
        SPI_DelayNs();

}

void  FLASH_SetSpi(SSI_TypeDef   *SSIx)
{
    SPI_FLASH =  SSIx; 
}


/**
  * @brief  This function is used to send the SPI command.
  * @param  instruction:The command code.
  * @param tx:The data pointer will be write to the SPI 
  * @param tlen:The data length
  * @param rx:The data pointer will be read to the SPI 
  * @param rlen:The data length
  * @retval None
  */
static void SPI_FlashCommand(uint8_t instruction,uint8_t *tx,uint16_t tlen,uint8_t *rx,uint16_t rlen)
{
   tx[0] = instruction;
   if(! SSI_Transfer(SPI_FLASH,tx,tlen,rx,rlen))
    {
        cm_printf("SPIM0 : error\r\n");
        return;
    }

   
#ifdef SPI_DEBUG
    cm_printf("SPIM0 :");
    for (uint16_t i=0;i<rlen;i++)
    {
        cm_printf("0x%2x,",rx[i]);
    }
    cm_printf("\r\n");
#endif
}

/**
  * @brief The Write Enable (WREN) instruction is for setting Write Enable Latch (WEL) .
  * @param  :None.
  * @retval None
  */
void FLASH_WriteEnable(void)
{
    uint8_t tx_buff[1];
    uint8_t rx_buff[1] ={0};
   
    do
    {
        SPI_FlashCommand(FLASH_WRITE_ENBALE,tx_buff,1,NULL,0);
        SPI_DelayMs(1);
        SPI_FlashCommand(FLASH_READ_STATUS_REG1,tx_buff,1,rx_buff,1);
    }while(!(rx_buff[0]&0x02));
}

/**
  * @brief The Write Disable (WRDI) instruction is for resetting Write Enable Latch (WEL) .
  * @param  :None.
  * @retval None
  */
void FLASH_WriteDisable(void)
{
    uint8_t tx_buff[1] = {0};
    uint8_t rx_buff[1] ={0};
    
    do
    {
        SPI_FlashCommand(FLASH_WRITE_DISABLE,tx_buff,1,NULL,0);
        SPI_DelayMs(1);
        SPI_FlashCommand(FLASH_READ_STATUS_REG1,tx_buff,1,rx_buff,1);
    }while(rx_buff[0]&0x02);
}


/**
  * @brief The Write in Progress (WIP) bit indicates whether 
  * the memory is busy in program/erase/write status register progress .
  * @param  None.
  * @retval None
  */
void FLASH_WaitBusy(void)
{
    uint8_t rx_buff[1] ={0};
    uint8_t tx_buff[1] ={0};
    do
    {
        SPI_DelayMs(1);
        SPI_FlashCommand(FLASH_READ_STATUS_REG1,tx_buff,1,rx_buff,1);
    }while(rx_buff[0]&0x01);

}


/**
  * @brief The Software Reset operation of flash.
  * @param :None.
  * @retval None
  */
void FLASH_ResetFlash(void)
{
    uint8_t rx_buff[1];
    SPI_FlashCommand(FLASH_ENABLE_RESET,rx_buff,1,NULL,0);
    SPI_FlashCommand(FLASH_RESET_DEVICE,rx_buff,1,NULL,0);
}


/**
  * @brief  Write the FLASH status registers 1 and registers 2.
  * @param reg1config:Writes the value of state register 1. 
  * @param reg2config:Writes the value of state register 2
  * @retval None
  */
void FLASH_WriteStatusReg(uint8_t *reg1config,uint8_t *reg2config)
{
    uint8_t tx_buff[3];
    tx_buff[1] = *reg1config;
    tx_buff[2] = *reg2config;
    SPI_FlashCommand(FLASH_WRITE_STATUS_REG1,tx_buff,3,NULL,0);
    SPI_DelayMs(5);
    FLASH_WaitBusy();
}

/**
  * @brief  Read the FLASH status registers 1 .
  * @param config:This pointer value is the value of the return status register 1. 
  * @retval None
  */
void FLASH_ReadStatusReg1(uint8_t *config)
{
    uint8_t tx_buff[1];
    SPI_FlashCommand(FLASH_READ_STATUS_REG1,tx_buff,1,config,1);
}

/**
  * @brief  Read the FLASH status registers 2.
  * @param config:This pointer value is the value of the return status register 2. 
  * @retval None
  */
void FLASH_ReadStatusReg2(uint8_t *config)
{
    uint8_t tx_buff[1];
    SPI_FlashCommand(FLASH_READ_STATUS_REG2,tx_buff,1,config,1);
}



/**
  * @brief  This function is used to read the value of FALSH.
  * @param addr:The first address byte can be at any location. The address is 
  *    automatically increased to the next higher address after each byte data is shifted out. 
  * @param data:The data pointer will be write to the FALSH
  * @param len:The data length
  * @retval None
  */
void FLASH_ReadData(uint32_t addr,uint8_t *data,uint16_t len)
{
    uint8_t tx_buff[4];
    tx_buff[1]  =  addr>>16 &0xff;
    tx_buff[2]  =  addr>>8&0xff;
    tx_buff[3]  =  addr&0xff;
    
    SPI_FlashCommand(FLASH_READ_DATA,tx_buff,4,data,len);
}

/**
  * @brief  This function is used to double read the value of FALSH.
  * @param addr:The first address byte can be at any location. The address is 
  *    automatically increased to the next higher address after each byte data is shifted out. 
  * @param data:The data pointer will be read to the FALSH
  * @param len:The data length
  * @retval None
  */
void FLASH_ReadDualData(uint32_t addr,uint8_t *data,uint16_t len)
{
    uint8_t tx_buff[5];
    tx_buff[1]  =  addr>>16 &0xff;
    tx_buff[2]  =  addr>>8&0xff;
    tx_buff[3]  =  addr&0xff;
    tx_buff[4]  =  0;
    
    SPI_FlashCommand(FLASH_FAST_READ_DUAL_OUT,tx_buff,5,data,len);
}

/**
  * @brief  The Sector Erase (PE) instruction is for erasing the data of the chosen sector to be "1". 
  * A Write Enable (WREN) instruction must execute to set the Write Enable Latch (WEL) bit 
  * before sending the sector Erase (PE).
  * @param addr:The first address of memory that needs to be erased. 
  * @retval None
  */
void FLASH_SectorErase(uint32_t addr)
{
    uint8_t tx_buff[4];
    
    FLASH_WriteEnable();
    SPI_DelayMs(5);
    FLASH_WaitBusy();
    tx_buff[1]  =  addr>>16 &0xff;
    tx_buff[2]  =  addr>>8&0xff;
    tx_buff[3]  =  addr&0xff;
    SPI_FlashCommand(FLASH_SECTOR_ERASE,tx_buff,4,NULL,0);
    SPI_DelayMs(5);
    FLASH_WaitBusy();
}

/**
  * @brief  The Block Erase (PE) instruction is for erasing the data of the chosen Block to be "1". 
  * A Write Enable (WREN) instruction must execute to set the Write Enable Latch (WEL) bit 
  * before sending the Block Erase (PE).
  * @param addr:The first address of memory that needs to be erased. 
  * @retval None
  */
void FLASH_32kBlackErase(uint32_t addr)
{
    uint8_t tx_buff[4];
    
    FLASH_WriteEnable();
    SPI_DelayMs(5);
    FLASH_WaitBusy();
    tx_buff[1]  =  addr>>16 &0xff;
    tx_buff[2]  =  addr>>8&0xff;
    tx_buff[3]  =  addr&0xff;
    SPI_FlashCommand(FLASH_32K_BLOCK_ERASE,tx_buff,4,NULL,0);
    SPI_DelayMs(5);
    FLASH_WaitBusy();
}

/**
  * @brief  The Block Erase (PE) instruction is for erasing the data of the chosen Block to be "1". 
  * A Write Enable (WREN) instruction must execute to set the Write Enable Latch (WEL) bit 
  * before sending the Block Erase (PE).
  * @param addr:The first address of memory that needs to be erased. 
  * @retval None
  */
void FLASH_64kBlackErase(uint32_t addr)
{
    uint8_t tx_buff[4];
    
    FLASH_WriteEnable();
    SPI_DelayMs(5);
    FLASH_WaitBusy();
    tx_buff[1]  =  addr>>16 &0xff;
    tx_buff[2]  =  addr>>8&0xff;
    tx_buff[3]  =  addr&0xff;
    SPI_FlashCommand(FLASH_64K_BLOCK_ERASE,tx_buff,4,NULL,0);
    SPI_DelayMs(5);
    FLASH_WaitBusy();
}

/**
  * @brief  The Block Chip (PE) instruction is for erasing the data of the chosen Chip to be "1". 
  * A Write Enable (WREN) instruction must execute to set the Write Enable Latch (WEL) bit 
  * @retval None
  */
void FLASH_ChipErase(void)
{
    uint8_t tx_buff[1];
    FLASH_WriteEnable();
    SPI_DelayMs(5);
    SPI_FlashCommand(FLASH_CHIP_ERASW1,tx_buff,1,NULL,0);
    SPI_DelayMs(5);
    FLASH_WaitBusy();
}

/**
  * @brief The Page Program (PP) instruction is for programming the memory. 
  * @param addr:The first address of the data writer
  * @param data:The data pointer will be write to the FALSH
  * @param len:The data length
  * @retval None
  */
void FLASH_PageProgram(uint32_t addr,uint8_t *data,uint16_t len)
{
    uint16_t i;

    for(i=0;i<len;i++)
        spi_ProgramBuff[4+i] = data[i];
    
    FLASH_WriteEnable();
    spi_ProgramBuff[1]  =  addr>>16 &0xff;
    spi_ProgramBuff[2]  =  addr>>8&0xff;
    spi_ProgramBuff[3]  =  addr&0xff;
    SPI_FlashCommand(FLASH_PAGE_PROGRAM,spi_ProgramBuff,len+4,NULL,0);
}

/**
  * @brief  The RDID instruction is for reading the manufacturer ID of 1-byte and
  *  followed by Device ID of 1-byte. 
  * @retval manufacturer ID[15:8]/Device ID[7:0]
  */
uint16_t FLASH_ReadManufDeviceId(void) /*must len = 2 */
{
    uint8_t tx_buff[4];
    uint8_t id_buff[2]; 
    tx_buff[0] = FLASH_READ_MANUFACTURER_OR_DEVICE_ID;
    tx_buff[1] = 0;
    tx_buff[2] = 0;
    tx_buff[3] = 0;
    SPI_FlashCommand(FLASH_READ_MANUFACTURER_OR_DEVICE_ID,tx_buff,4,id_buff,2);

    return (uint16_t)(id_buff[1]|(id_buff[0]<<8));
}



/**
  * @brief  The Quad Enable (QE)  is a non-volatile read/write 
  * bit in the status that allows Quad SPI and QPI operation . 
  * @param status: 1: Enable/ 0:Disable EQ Mode
  * @retval None
  */
void  FLASH_EnableEQI(bool status)
{
    uint8_t config_data2 = 0;
    uint8_t config_data1 = 0;
    
    FLASH_ReadStatusReg2(&config_data2);

    if((status && (config_data2>>1)&0x01)||
        (status == false && ((config_data2>>1)&0x01)== 0))
        return;    
    
    if(status)
        config_data2 = config_data2|0x02;
    else 
        config_data2 = config_data2 &(~0x02);
    
    FLASH_WriteEnable();
    FLASH_WaitBusy();
    FLASH_WriteStatusReg(&config_data1,&config_data2);
    FLASH_WaitBusy();
}


#if 0

void FLASH_EnterQpiMode(void)
{
    uint32_t tx_buff[1];
    SPI_FlashCommand(FLASH_ENTER_QIP_MODE,tx_buff,1,NULL,0);
}
void FLASH_ExitQpiMode(void)
{
    uint32_t tx_buff[1];
    SPI_FlashCommand(FLASH_EXIT_QIP_MODE,tx_buff,1,NULL,0);
}
void spi_FLASH_read_unique_id_number(uint32_t *data,uint16_t len) /*must len = 8 */
{
    uint32_t tx_buff[5];
    tx_buff[0] = FLASH_UNIQUE_ID_NUMBER;
    SPI_FlashCommand(FLASH_UNIQUE_ID_NUMBER,tx_buff,5,data,len);
}

void spi_FLASH_read_JEDEC_ID(uint32_t *data,uint16_t len) /*must len = 3 */
{
    uint32_t tx_buff[1];
    SPI_FlashCommand(FLASH_READ_JEDEC,tx_buff,1,data,len);
}
#endif









