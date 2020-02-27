/*
 *++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 * Copyright (c) 1999-2018 Barrot Technology Limited
 *
 * All rights reserved.
 *
 *------------------------------------------------------------------------------
 */
/**
 * @file    BR1051Axx_spi_falsh.h
 * @brief   This file provides all the spi_flash  config.
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

#ifndef __BT1051Axx_SPI_FLASH_H__
#define __BT1051Axx_SPI_FLASH_H__

/*  flash  Commands listing   */
#define   FLASH_WRITE_ENBALE  0X06
#define   FLASH_WRITE_ENABLE_OF_STATUS_REG  0X50
#define   FLASH_WRITE_DISABLE 0X04

#define   FLASH_READ_STATUS_REG1 0X05
#define   FLASH_READ_STATUS_REG2 0X35
#define   FLASH_READ_STATUS_REG3 0X15

#define   FLASH_WRITE_STATUS_REG1 0X01
#define   FLASH_WRITE_STATUS_REG2 0X31
#define   FLASH_WRITE_STATUS_REG3 0X11

#define   FLASH_READ_DATA   0X03
#define   FLASH_FAST_READ   0X0B
#define   FLASH_FAST_READ_DUAL_OUT   0X3B
#define   FLASH_FAST_READ_QUAD_OUT   0X6B
#define   FLASH_FAST_READ_DUAL_IO      0XBB
#define   FLASH_FAST_READ_QUAD_IO      0XEB
#define   FLASH_WORD_READ_QUAD_IO      0XE7
#define   FLASH_OCTAL_WORD_READ_QUAD_IO      0XE3
#define   FLASH_SET_BURST_WITH_WRAP  0X77
#define   FLASH_PAGE_PROGRAM 0X02
#define   FLASH_QUAL_INPUT_PAGE_PROGRAM 0X32
#define   FLASH_SECTOR_ERASE 0X20
#define   FLASH_32K_BLOCK_ERASE 0X52
#define   FLASH_64K_BLOCK_ERASE 0xd8
#define   FLASH_CHIP_ERASW 0XC7
#define   FLASH_CHIP_ERASW1 0X60
#define   FLASH_ERASE_PROGRAM_SUSPEND 0X75
#define   FLASH_ERASE_PROGRAM_RESUME  0X7A

#define   FLASH_POWER_DOEM 0XB9
#define   FLASH_RELEASE_POWER_DOWN_OR_DEVICEID 0XAB
#define   FLASH_READ_MANUFACTURER_OR_DEVICE_ID 0X90
#define   FLASH_READ_MANUFACTURER_OR_DEVICE_ID_DUAL_IO 0X92
#define   FLASH_READ_MANUFACTURER_OR_DEVICE_ID_QUAD_ID 0X94
#define   FLASH_UNIQUE_ID_NUMBER 0X4B
#define   FLASH_READ_JEDEC  0X9F
#define   FLASH_READ_SFDP_REG 0X5A

#define   FLASH_ERASE_SECURITY_REG 0X44
#define   FLASH_PROGRAM_SECURITY 0X42
#define   FLASH_READ_SECURITY 0X48
#define   FLASH_SET_READ_PARAM 0XC0

#define   FLASH_BURST_READ_WITH_WRAP 0X0C
#define   FLASH_ENTER_QIP_MODE 0X38
#define   FLASH_EXIT_QIP_MODE 0XFF

#define   FLASH_INDIVIDUAL_BLOCK_OR_SECTOR_LOCK 0X36
#define   FLASH_INDIVIDUAL_BLOCK_OR_SECTOR_UNLOCK 0X39

#define   FLASH_READ_BLOCK_OR_SECTOR_LOCK 0X3D
#define   FLASH_GLOBAL_BLOCK_OR_SECTOR_LOCK 0X7E
#define   FLASH_GLOBAL_BLOCK_OR_SECTOR_UNLOCK 0X98
 
#define   FLASH_ENABLE_RESET 0X66
#define   FLASH_RESET_DEVICE 0X99

#include <stdint.h>

/**
  * @brief The Write Enable (WREN) instruction is for setting Write Enable Latch (WEL) .
  * @param  :None.
  * @retval None
  */
void FLASH_WriteEnable(void);

/**
  * @brief The Write Disable (WRDI) instruction is for resetting Write Enable Latch (WEL) .
  * @param  :None.
  * @retval None
  */
void FLASH_WriteDisable(void);

/**
  * @brief The Write in Progress (WIP) bit indicates whether 
  * the memory is busy in program/erase/write status register progress .

    NOTE: When FLASH operations are needed, it is necessary to determine whether 
    FLASH exists. If FLASH does not exist, the call will appear in an infinite loop
  
  * @param  :None.
  * @retval None
  */
void FLASH_WaitBusy(void);

/**
  * @brief The Software Reset operation of flash.
  * @param :None.
  * @retval None
  */
void FLASH_ResetFlash(void);



void FLASH_SetSpi(SSI_TypeDef   *SSIx);
/**
  * @brief  Write the FLASH status registers 1 and registers 2.
  * @param reg1config:Writes the value of state register 1. 
  * @param reg2config:Writes the value of state register 2
  * @retval None
  */
void FLASH_WriteStatusReg(uint8_t *reg1config,uint8_t *reg2config);

/**
  * @brief  Read the FLASH status registers 1.
  * @param config:This pointer value is the value of the return status register 1. 
  * @retval None
  */
void FLASH_ReadStatusReg1(uint8_t *config);

/**
  * @brief  Read the FLASH status registers 2.
  * @param config:This pointer value is the value of the return status register 2. 
  * @retval None
  */
void FLASH_ReadStatusReg2(uint8_t *config);

/**
  * @brief  This function is used to read the value of FALSH.
  * @param addr:The first address byte can be at any location. The address is 
  *    automatically increased to the next higher address after each byte data is shifted out. 
  * @param data:The data pointer will be write to the FALSH
  * @param len:The data length
  * @retval None
  */
void FLASH_ReadData(uint32_t addr,uint8_t *data,uint16_t len);

/**
  * @brief  This function is used to double read the value of FALSH.
  * @param addr:The first address byte can be at any location. The address is 
  *    automatically increased to the next higher address after each byte data is shifted out. 
  * @param data:The data pointer will be read to the FALSH
  * @param len:The data length
  * @retval None
  */
void FLASH_ReadDualData(uint32_t addr,uint8_t *data,uint16_t len);

/**
  * @brief  The Sector Erase (PE) instruction is for erasing the data of the chosen sector to be "1". 
  * A Write Enable (WREN) instruction must execute to set the Write Enable Latch (WEL) bit 
  * before sending the sector Erase (PE).
  * @param addr:The first address of memory that needs to be erased. 
  * @retval None
  */
void FLASH_SectorErase(uint32_t addr);

/**
  * @brief  The Block Erase (PE) instruction is for erasing the data of the chosen Block to be "1". 
  * A Write Enable (WREN) instruction must execute to set the Write Enable Latch (WEL) bit 
  * before sending the Block Erase (PE).
  * @param addr:The first address of memory that needs to be erased. 
  * @retval None
  */
void FLASH_32kBlackErase(uint32_t addr);

/**
  * @brief  The Block Erase (PE) instruction is for erasing the data of the chosen Block to be "1". 
  * A Write Enable (WREN) instruction must execute to set the Write Enable Latch (WEL) bit 
  * before sending the Block Erase (PE).
  * @param addr:The first address of memory that needs to be erased. 
  * @retval None
  */
void FLASH_64kBlackErase(uint32_t addr);

/**
  * @brief  The Block Chip (PE) instruction is for erasing the data of the chosen Chip to be "1". 
  * A Write Enable (WREN) instruction must execute to set the Write Enable Latch (WEL) bit 
  * @retval None
  */
void FLASH_ChipErase(void);

/**
  * @brief The Page Program (PP) instruction is for programming the memory. 
  * @param addr:The first address of the data writer
  * @param data:The data pointer will be write to the FALSH
  * @param len:The data length
  * @retval None
  */
void FLASH_PageProgram(uint32_t addr,uint8_t *data,uint16_t len);

/**
  * @brief  The RDID instruction is for reading the manufacturer ID of 1-byte and
  *  followed by Device ID of 1-byte. 
  * @retval manufacturer ID[15:8]/Device ID[7:0]
  */
uint16_t FLASH_ReadManufDeviceId(void);

/**
  * @brief  The Quad Enable (QE)  is a non-volatile read/write 
  * bit in the status that allows Quad SPI and QPI operation . 
  * @param status: 1: Enable/ 0:Disable EQ Mode
  * @retval None
  */
void  FLASH_EnableEQI(bool status);


//void FLASH_EnterQpiMode(void);
//void FLASH_ExitQpiMode(void);
//void spi_FLASH_read_unique_id_number(uint32_t *data,uint16_t len);
//void spi_FLASH_read_JEDEC_ID(uint32_t *data,uint16_t len);

#endif /*__BT1051Axx_SPI_FLASH_H__ */



