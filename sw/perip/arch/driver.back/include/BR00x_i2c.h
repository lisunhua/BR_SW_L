/*
 *++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 * Copyright (c) 1999-2018 Barrot Technology Limited
 *
 * All rights reserved.
 *
 *------------------------------------------------------------------------------
 */
/**
 * @file    BR00x_i2c.h
 * @brief    This file provides all the i2c firmware functions.
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

#ifndef __BT1051Axx_I2C_H__
#define __BT1051Axx_I2C_H__

#ifdef __cplusplus
 extern "C" {
#endif

#include "BR00x_config.h"


#define   I2C0_COMP_TYPE()   I2C0->IC_COMP_TYPE
#define   I2C1_COMP_TYPE()   I2C1->C_COMP_TYPE

#define   I2C0_COMP_VERSION()   I2C0->IC_COMP_VERSION
#define   I2C1_COMP_VERSION()   I2C1->IC_COMP_VERSION

#define read 1
#define write 0



typedef enum /*This is a list of interrupt vectors that cannot be modified  */
{
/*00*/    RX_UNDER_TYPE,
/*01*/    RX_OVER_TYPE,
/*02*/    RX_FULL_TYPE,
/*03*/    TX_OVER_TYPE,
/*04*/    TX_EMPTY_TYPE,
/*05*/    RD_REQ_TYPE,
/*06*/    TX_ABRT_TYPE,
/*07*/    RX_DONE_TYPE,
/*08*/    ACTIVITY_TPYE,
/*09*/    STOP_DET_TYPE,
/*10*/    START_DET_TYPE,
/*11*/    GEN_CALL_TYPE,
/*12*/    RESTART_DET_TYPE,
/*13*/    MASTER_ON_HOLD_TYPE,
/*14*/    SLC_STUCK_AT_LOW,
    
}I2C_Interrupt_Type;


 typedef enum /*This is a list of interrupt vectors that cannot be modified  */
 {
/*00*/    SMBUS_SLAVE_CLOCK_EXTND_TIMOUTE,
/*01*/    SMBUS_MASTER_CLOCK_EXTND_TIMOUT,
/*02*/    SMBUS_QUICK_CMD_DET,
/*03*/    SMBUS_HOST_NOTIFY_MST_DET,
/*04*/    SMBUS_ARP_PREPARE_CMD_DET,
/*05*/    SMBUS_ARP_RST_CMD_DET,
/*06*/    SMBUS_GET_UDIO_CMD_DET,
/*07*/    SMBUS_ARP_ASSGN_ADDR_CMD_DET,
/*08*/    SMBUS_SLAVE_RX_PRC_NACK,
/*09*/    SMBUS_SUSPEND_DET,
/*10*/    SMBUS_ALERT_DET,
 }I2C_SMBUSInterrupt_Type;

typedef enum
{
/*00*/    SPEEDS_STD_100k,
/*01*/    SPEEDS_FAT_400K_OR_FAT_PLUS_1000K,
/*02*/    SPEEDS_HGH_3_4M
}I2C_SpeedsMode_Type;



typedef enum /*This is a list of I2C status that cannot be modified  */
{
/*00*/    STATUS_ACTIVITY,
/*01*/    STATUS_TX_FIFO_NOT_FULL,
/*02*/    STATUS_TX_FIFO_EMPTY,
/*03*/    STATUS_RX_FIFO_NOT_EMPTY,
/*04*/    STATUS_RX_FIFO_FULL ,
/*05*/    STATUS_MASTER_NOT_IDLE,
/*06*/    STATUS_SLAVE_NOT_IDLE,
/*07*/    STATUS_MASTER_HOLD_TX_FIFO_EMPTY,  /* Master holds the bus due to Tx FIFO is empty*/
/*08*/    STATUS_MASTER_HOLD_RX_FIFO_FULL,    /* Master holds the bus due to Rx FIFO is full */
/*09*/    STATUS_SLAVE_HOLD_TX_FIFO_EMPTY,    /* Slave holds the bus due to Tx FIFO is empty*/
/*10*/    STATUS_SLAVE_HOLD_RX_FIFO_FILL,       /*Slave holds the bus due to Rx FIFO is full  */ 
/*11*/    STATUS_SDA_STUCK_NOT_RECOVERED,     /* SDA Stuck at low is recovered after recovery mechanism.*/
/*XX*/
/*16*/    STATUS_SMBUS_QUICK_CMD_BIT,             /* SMBUS QUICK CMD Read/write is set to 1.*/
/*17*/    STATUS_SMBUS_SLAVE_ADDR_VALID,       /*  SMBUS Slave Address is Valid.*/
/*18*/    STATUS_SMBUS_SLAVE_ADDR_RESOLVED, /* SMBUS Slave Address is Resolved */
/*19*/    STATUS_SMBUS_SUSPEND_STATUS,           /*  SMBUS System is in Suspended mode */
/*20*/    STATUS_SMBUS_ALERT_STATUS,               /* SMBUS Alert is asserted*/


}I2C_Status_Type;


typedef enum /*This is a list of  Transmit Abort Source that cannot be modified  */
{
/*00*/    TX_ABRT_SOURCE_ABRT_7B_ADDR_NOACK, /*This abort is generated because of NOACK for 7-bit address*/
/*01*/    TX_ABRT_SOURCE_ABRT_10ADDR1_NOACK, /*Byte 1 of 10Bit Address not ACKed by any slave*/
/*02*/    TX_ABRT_SOURCE_ABRT_10ADDR2_NOACK, /*Byte 2 of 10Bit Address not ACKed by any slave*/
/*03*/    TX_ABRT_SOURCE_ABRT_TXDATA_NOACK,   /*Transmitted data not ACKed by addressed slave*/
/*04*/    TX_ABRT_SOURCE_ABRT_GCALL_NOACK,     /* GCALL not ACKed by any slave*/
/*05*/    TX_ABRT_SOURCE_ABRT_GCALL_READ,        /* GCALL is  followed by read from bus*/
/*06*/    TX_ABRT_SOURCE_ABRT_HS_ACKDE,          /* HS Master code ACKed in HS Mode*/
/*07*/    TX_ABRT_SOURCE_ABRT_SBYTE_ACKDET,  /* ACKdetected for START byte*/
/*08*/    TX_ABRT_SOURCE_ABRT_HS_NORSTRT,    /* User trying to switch Master to HS mode when RESTART disabled */
/*09*/    TX_ABRT_SOURCE_ABRT_SBYTE_NORSTRT,    /*User trying to send START byte when RESTART disabled*/
/*10*/    TX_ABRT_SOURCE_ABRT_10B_RD_NORSTRT,       /* Master trying to read in 10Bit addressing mode when RESTART disabled*/ 
/*11*/    TX_ABRT_SOURCE_ABRT_MASTER_DIS,               /*  User intitating master operation when MASTER disabled.*/
/*12*/    TX_ABRT_SOURCE_ARB_LOST,                            /* Master or SlaveTransmitter lost arbitration*/
/*13*/    TX_ABRT_SOURCE_ABRT_SLVFLUSH_TXFIFO,      /* Slave flushes existing data in TX-FIFO upon getting read command*/
/*14*/    TX_ABRT_SOURCE_ABRT_SLV_ARBLOST,             /* Slave lost arbitration to remote master*/ 
/*15*/    TX_ABRT_SOURCE_ABRT_SLVRD_INTX,                /*: Slave trying to transmit to remote master in read mode*/ 
/*16*/    TX_ABRT_SOURCE_ABRT_USER_ABRT,                 /* Transfer abort detected by master.*/
/*17*/    TX_ABRT_SOURCE_ABRT_SDA_STUCK_AT_LOW,   /*  This abort is generated because of Sda stuck at low for IC_SDA_STUCK_AT_LOW_TIMEOUT value of ic_clks.*/
/*18*/    TX_ABRT_SOURCE_ABRT_DEVICE_NOACK,           /* This abort is generated because of NOACK for DEVICE-ID */
/*19*/    TX_ABRT_SOURCE_ABRT_DEVICE_SLVADDR_NOACK,    /* This abort is generated because of NOACK for Slave address */
/*20*/    TX_ABRT_SOURCE_ABRT_DEVICE_WRITE,               /* This abort is generated because of NOACK for Slave address*/

}I2C_TxAbrtSource_Type;

typedef enum /*This is a list of  I2C Enable Status  that cannot be modified  */
{
/*00*/    EN_ENABLE,                               /* I2C enabled*/
/*01*/    SLAVE_DISABLE_WHILE_BUSY,   /* Slave is disabled when it is active */
/*02*/    SLAVE_RX_DATA_LOST,              /*Slave RX Data is lost */


}I2C_EnableStatus_Type;



typedef enum
{
    ROLE_MODE_SLAVE,
    ROLE_MODE_MASTER
}I2C_RoleMode_Type;


typedef enum
{
    PARAM_MAX_SPEED_RESERVED,
    PARAM_MAX_SPEED_STANDARD,
    PARAM_MAX_SPEED_FAST,
    PARAM_MAX_SPEED_HIGH

}I2C_ParamMaxSpeedMode;


typedef enum
{

    MASTER_MODE_DISABLE,
    MASTER_MODE_ENABLE,
}I2C_MasterModeEn;


typedef enum
{

    SLAVE_MODE_ENABLE,
    SLAVE_MODE_DISABLE,
}I2C_SlaveModeEn;


typedef enum
{
    SPEED_STANDARD = 1, /* standard mode (100 kbit/s) */
    SPEED_FAST,              /*fast mode (<=400 kbit/s) or fast mode plus (<=1000Kbit/s) */
    SPEED_HIGH              /* high speed mode (3.4 Mbit/s) */

}I2C_SpeedConfig;


/**
 when acting as a slave,
**/
typedef enum
{
    SLAVE_7BIT_ADDR,
    SLAVE_10BIT_ADDR
}I2C_AddrSlave;

typedef enum
{
    MASTER_7BIT_ADDR,
    MASTER_10BIT_ADDR
}I2C_AddrMaster;


typedef enum
{
    MASTER_RESTART_DISABLE,
    MASTER_RESTART_ENABLE,
}I2C_MasterRestart;

typedef enum
{
    SLAVE_STOP_DET_IFADDRESSED_DISABLE,
    SLAVE_STOP_DET_IFADDRESSED_ENABLE
}I2C_SlaveStopDetIfAddressed;


typedef enum
{
    TX_EMPTY_INTERRUPT_DISABLE,
    TX_EMPTY_INTERRUPT_ENABLE
}I2C_TxEmptyInterrupt;


/*DW_apb_i2c should hold the bus
when the Rx FIFO is physically full to its*/
typedef enum
{
    RX_FIFO_FULL_HOLD_DISABLE, /*Hold bus when RX_FIFO is full */
    RX_FIFO_FULL_HOLD_ENABLE,  /*Overflow when RX_FIFO is full*/
}I2C_RxFifoFullHold;

typedef enum
{
    MASTER_STOP_DET_IFACTIVE_DISABLE, /* issues the STOP_DET interrupt only when master is active.*/
    MASTER_STOP_DET_IFACTIVE_ENABLE   /* issues the STOP_DET irrespective of whether master is active or not*/
}I2C_MasterStopDetIfAddressed;

typedef enum
{
    MASTER_BUS_CLEAR_FEATURE_DISABLE,
    MASTER_BUS_CLEAR_FEATURE_ENABLE
    
}I2C_MasterBusClearFeature;

typedef enum
{
    OPTIONAL_SAR_ADDRESS_DISABLE,
    OPTIONAL_SAR_ADDRESS_ENABLE
}I2C_OptionalSARAddress;

typedef enum
{
    SMBUS_SLAVE_QUICK_DISABLE,
    SMBUS_SLAVE_QUICK_ENABLE
}I2C_SMBUSSlaveQuick;

typedef enum
{
    SMBUS_ARP_CONTRAL_DISABLE,
    SMBUS_ARP_CONTRAL_ENABLE
    
}I2C_SMBUS_ARPControl;

typedef enum
{
    SMBUS_PERSISTENT_SLV_ADDR_DISABLE,
    SMBUS_PERSISTENT_SLV_ADDR_ENBALE
}I2C_SMBUSPersistentSlaveAddrss;


typedef enum
{
    GENERAL_CALL, /* General Call Address  */
    START_BYTR,   /* START byte transmission */

}I2C_GeneralCallOrStart;


typedef enum
{
    GENERAL_CALL_OR_START_BYTE_DISABLE, /* ignore  GC_OR_START and use IC_TAR normally*/
    GENERAL_CALL_OR_START_BYTE_ENABLE,  /*perform special I2C command as specified in Device_ID or GC_OR_START bit*/
    
}I2C_ProgrammingGeneralCallOrStart;


typedef enum
{
    PROGRAMMING_DEVICE_ID_DISABLE,/* Enables programming of DEVICE-ID transmission*/
    PROGRAMMING_DEVICE_ID_ENBALE,
}I2C_ProgrammingDeviceIdEn;

typedef enum
{
    PROGRAMMING_SMBUS_QUICK_CMD_DISABLE,/* Enables programming of DEVICE-ID transmission*/
    PROGRAMMING_SMBUS_QUICK_CMD_ENBALE,
}I2C_ProgrammingSMBUSQuickCmdEn;


typedef struct
{
    unsigned  data:8;
    unsigned  com:1;
    unsigned  stop:1;
    unsigned  restart:1;
    unsigned  non_seq:1;
   
}i2c_DataCmd;


typedef struct
{
 //   I2C_role_mode_type_t  role_mode;
    I2C_MasterModeEn         master_en;
    I2C_ParamMaxSpeedMode    max_speed;
    I2C_AddrSlave            slave_addr_type;
    I2C_AddrMaster           master_addr_type;
    I2C_MasterRestart        restart_en;
    I2C_SlaveModeEn          slave_en;

    /*ven if the slave responds to the general call address by generating ACK. 
    The STOP_DET interrupt is generated only when the transmitted address 
    matches the slave address (SAR)*/
    I2C_SlaveStopDetIfAddressed   slave_stop_det_if_addressed_en;    /*slave issues STOP_DET intr only if addressed*/
    I2C_MasterStopDetIfAddressed master_stop_det_if_addressed_en; /*master  issues STOP_DET intr only if addressed*/
    I2C_TxEmptyInterrupt    tx_empty_intr_en; /* Controlled generation of TX_EMPTY interrupt*/
    I2C_RxFifoFullHold    rx_fifo_full_hold_control_en;/* Hold bus when RX_FIFO is full */

    I2C_MasterBusClearFeature  master_bus_clear_feature_en; /* Bus Clear Feature is enabled or disable.*/
    I2C_OptionalSARAddress  optional_SAR_address_en;                           /*Optional SAR Address is enable and disable*/
    
    I2C_SMBUSSlaveQuick     SMBUS_slave_quick_en;                               /*  SMBus SLave is enabled to receive Quick command.*/
    I2C_SMBUS_ARPControl     SMBUS_ARP_contral_en;                              /*SMBus ARP control */
    I2C_SMBUSPersistentSlaveAddrss  SMBUS_persistent_slave_addr_en;  /* SMBus Persistent Slave address control*/

    uint16_t I2C_target_address;
    I2C_AddrMaster  targer_address_type;/* This bit controls whether the DW_apb_i2c starts its transfers in 7- or 10-bit addressing mode when acting as a master*/
    I2C_GeneralCallOrStart general_call_or_start_byte;
    I2C_ProgrammingGeneralCallOrStart  general_call_or_start_byte_en;
    I2C_ProgrammingDeviceIdEn programming_device_id_en;
    I2C_ProgrammingSMBUSQuickCmdEn  programming_SMBUS_quick_cmd_en;
    
    
    
    uint16_t salve_address;
    uint32_t slc_h;
    uint32_t slc_l;

    uint32_t interrupt_unmask;
    uint8_t   fifo_receive_threshold_level;
    uint8_t   fifo_transmit_threshold_level;

    bool dma_rx_en;
    bool dma_tx_en;
    uint32_t dma_tx_data_level;
    uint32_t dma_rx_data_level;

    
}I2C_InitInof_Type;


/**
  * @brief  Deinitializes the i2c peripheral registers to their default reset values.
  * @param  I2Cx: pointer to a I2C.
  * @retval None
  */
void I2C_DeInit(I2C_TypeDef  *I2Cx);

/**
  * @brief  Initializes the I2C peripheral according to the specified
  *         parameters in the I2C_InitInfo_Type.
  * @param  I2Cx: pointer to a I2C.
  * @param  I2C_InitStru: pointer to a I2C_InitInfo_Type structure that
  *         contains the configuration information for the specified I2C peripheral.
  * @retval None
  */
void I2C_Init(I2C_TypeDef  *I2Cx,I2C_InitInof_Type  *I2C_InitStru);


/**
    * @brief  I2c Read data continuously
    * @param  I2Cx: pointer to a I2C.
    * @param rx: This data pointer will be read from FIFO
    * @param rlen: The data length
    * @param rstop:Send end whether send stop bit
    * @retval None
    */
bool  I2C_ReadDate(I2C_TypeDef  *I2Cx  ,uint8_t *rx, uint16_t rlen,bool rstop);


/**
    * @brief  I2c write data continuously
    * @param  I2Cx: pointer to a I2C.
    * @param tx: The data pointer will be write to the fifo
    * @param tlen: The data length
    * @param tstop: Send end whether send stop bit
    * @retval None
    */
bool  I2C_WriteDate(I2C_TypeDef  *I2Cx  ,uint8_t *tx, uint16_t tlen,bool tstop);



/**
    * @brief  Set the data to be transmitted or received, until it's done
    *
    * @param  I2Cx: pointer to a I2C.
    * @param data: I2C Rx/Tx Data Buffer and Command
    * @retval  None
    */
void I2C_WriteByte(I2C_TypeDef  *I2Cx  , uint32_t data);


void I2C_GetRxTxThreshold(I2C_TypeDef  *I2Cx,uint32_t *TX_TL,uint32_t *RX_TL);
/**
  * @brief  Get the data to be transmitted or received, until it's done
  *
  * @param  I2Cx: pointer to a I2C.
  * @param cmd: I2C Rx/Tx Data  Command
  * @retval the data to be transmitted or received
  */
uint8_t  I2C_ReadByte(I2C_TypeDef  *I2Cx  , uint32_t cmd);

/**
    * @brief  Set the data to be transmitted or received
    *
    * @param  I2Cx: pointer to a I2C.
    * @param data: I2C Rx/Tx Data Buffer and Command
    * @retval  None
    */
void I2C_SetCmdData(I2C_TypeDef  *I2Cx  , uint32_t data);

/**
    * @brief  Get the data to be transmitted or received
    *
    * @param  I2Cx: pointer to a I2C.
    * @retval  the data to be transmitted or received
    */
uint32_t  I2C_GetCmdData(I2C_TypeDef  *I2Cx);

/**
  * @brief  Clear SMBus Interrupt
  *
  * @param  I2Cx: pointer to a I2C.
  * @param type:Select the I2C_SMBUSInterrupt_Type you want to set
  * @retval  It makes no sense
  */
bool I2C_ClearSMBUSInterrupt(I2C_TypeDef  *I2Cx, I2C_SMBUSInterrupt_Type  type);

/**
  * @brief  Clear i2c Interrupt
  *
  * @param  I2Cx: pointer to a I2C.
  * @param type:Select the I2C_Interrupt_Type you want to set
  * @retval It makes no sense
  */
bool   I2C_ClearInterrupt(I2C_TypeDef  *I2Cx, I2C_Interrupt_Type type);

/**
  * @brief   Clear Combined and Individual Interrupt .
  *  all individual interrupts, and the IC_TX_ABRT_SOURCE
      register. This bit does not clear hardware clearable interrupts
      but software clearable interrupts.
  * @param  I2Cx: pointer to a I2C.
  * @retval It makes no sense
  */
bool I2C_ClearCombinedInterruptAll(I2C_TypeDef *I2Cx);




#ifdef __cplusplus
}
#endif

#endif /* __BT1051Axx_I2C_H__ */

