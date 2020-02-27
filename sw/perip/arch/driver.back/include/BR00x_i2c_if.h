/*
 *++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 * Copyright (c) 1999-2018 Barrot Technology Limited
 *
 * All rights reserved.
 *
 *------------------------------------------------------------------------------
 */
/**
 * @file    BR1051Axx_i2c_if.h
 * @brief   This file provides all the i2c register parameter.
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

#ifndef  __BT1051Axx_I2C_IF_H__
#define  __BT1051Axx_I2C_IF_H__



#define I2C_APB_DATA_WIDTH_POS          0x00ul
#define I2C_MAX_SPEED_MODE_POS         0x02ul
#define I2C_HC_COUNT_VALUES_POS        0x04ul
#define I2C_INTR_IO_POS                         0x05ul
#define I2C_HAS_DMA_POS                       0x06ul
#define I2C_ADD_ENCODE_PARANS_POS    0x07ul
#define I2C_RX_BUFFER_DEPTH_POS         0x08ul
#define I2C_TX_BUFFER_DEPTH_POS         0x10ul



/* Peripheral: I2C */
/* Description: Inter-Integrated Circuit. */

/* Register: IC_CON  */
/* Description: : I2C Control Register. */

/*bit 0 :This bit controls whether the DW_apb_i2c master is enabled */
#define I2C_IC_CON_MASTER_MODE_POS (0ul) /*!< Position of MASTER_MODE field. */
#define I2C_IC_CON_MASTER_MODE_MSK (0x01ul << I2C_IC_CON_MASTER_MODE_POS) /*!< Bit mask of MASTER_MODE field. */

/*bit 1-2 :These bits control at which speed the DW_apb_i2c operates*/
#define I2C_IC_CON_SPEED_POS (1ul) /*!< Position of SPEED field. */
#define I2C_IC_CON_SPEED_MSK (0x03ul << I2C_IC_CON_SPEED_POS) /*!< Bit mask of SPEED field. */

/*bit 3 :When acting as a slave, this bit controls whether the DW_apb_i2c responds to 7- or 10-bit addresses*/
#define I2C_IC_CON_IC_10BITADDR_SLAVE_POS (3ul) /*!< Position of IC_10BITADDR_SLAVE field. */
#define I2C_IC_CON_IC_10BITADDR_SLAVE_MSK (0x01ul << I2C_IC_CON_IC_10BITADDR_SLAVE_POS) /*!< Bit mask of IC_10BITADDR_SLAVE field. */

/*bit 4 :IC_10BITADDR_MASTER configuration*/
#define I2C_IC_CON_IC_10BITADDR_MASTER_POS (4ul) /*!< Position of IC_10BITADDR_MASTER field. */
#define I2C_IC_CON_IC_10BITADDR_MASTER_MSK (0x01ul << I2C_IC_CON_IC_10BITADDR_MASTER_POS) /*!< Bit mask of IC_10BITADDR_MASTER field. */

/*bit 5 :IC_RESTART_EN configuration*/
#define I2C_IC_CON_IC_RESTART_EN_POS (5ul) /*!< Position of IC_RESTART_EN field. */
#define I2C_IC_CON_IC_RESTART_EN_MSK (0x01ul << I2C_IC_CON_IC_RESTART_EN_POS) /*!< Bit mask of IC_RESTART_EN field. */

/*bit 6 :IC_SLAVE_DISABLE configuration*/
#define I2C_IC_CON_IC_SLAVE_DISABLE_POS (6ul) /*!< Position of IC_SLAVE_DISABLE field. */
#define I2C_IC_CON_IC_SLAVE_DISABLE_MSK (0x01ul << I2C_IC_CON_IC_SLAVE_DISABLE_POS) /*!< Bit mask of IC_SLAVE_DISABLE field. */

/*bit 7 :STOP_DET_IFADDRESSED configuration*/
#define I2C_IC_CON_STOP_DET_IFADDRESSED_POS (7ul) /*!< Position of STOP_DET_IFADDRESSED field. */
#define I2C_IC_CON_STOP_DET_IFADDRESSED_MSK (0x01ul << I2C_IC_CON_STOP_DET_IFADDRESSED_POS) /*!< Bit mask of STOP_DET_IFADDRESSED field. */

/*bit 8 :TX_EMPTY_CTRL configuration*/
#define I2C_IC_CON_TX_EMPTY_CTRL_POS (8ul) /*!< Position of TX_EMPTY_CTRL field. */
#define I2C_IC_CON_TX_EMPTY_CTRL_MSK (0x01ul << I2C_IC_CON_TX_EMPTY_CTRL_POS) /*!< Bit mask of TX_EMPTY_CTRL field. */

/*bit 9 :RX_FIFO_FULL_HLD_CTRL configuration*/
#define I2C_IC_CON_RX_FIFO_FULL_HLD_CTRL_POS (9ul) /*!< Position of RX_FIFO_FULL_HLD_CTRL field. */
#define I2C_IC_CON_RX_FIFO_FULL_HLD_CTRL_MSK (0x01ul << I2C_IC_CON_RX_FIFO_FULL_HLD_CTRL_POS) /*!< Bit mask of RX_FIFO_FULL_HLD_CTRL field. */

/*bit 10 :STOP_DET_IF_MASTER_ACTIVE configuration*/
#define I2C_IC_CON_STOP_DET_IF_MASTER_ACTIVE_POS (10ul) /*!< Position of STOP_DET_IF_MASTER_ACTIVE field. */
#define I2C_IC_CON_STOP_DET_IF_MASTER_ACTIVE_MSK (0x01ul << I2C_IC_CON_STOP_DET_IF_MASTER_ACTIVE_POS) /*!< Bit mask of STOP_DET_IF_MASTER_ACTIVE field. */


/*bit 11 :BUS_CLEAR_FEATURE_CTRL configuration*/
#define I2C_IC_CON_BUS_CLEAR_FEATURE_CTRL_POS (11ul) /*!< Position of BUS_CLEAR_FEATURE_CTRL field. */
#define I2C_IC_CON_BUS_CLEAR_FEATURE_CTRL_MSK (0x01ul << I2C_IC_CON_BUS_CLEAR_FEATURE_CTRL_POS) /*!< Bit mask of BUS_CLEAR_FEATURE_CTRL field. */

/*bit 16 :OPTIONAL_SAR_CTRL configuration*/
#define I2C_IC_CON_OPTIONAL_SAR_CTRL_POS (16ul) /*!< Position of OPTIONAL_SAR_CTRL field. */
#define I2C_IC_CON_OPTIONAL_SAR_CTRL_MSK (0x01ul << I2C_IC_CON_OPTIONAL_SAR_CTRL_POS) /*!< Bit mask of OPTIONAL_SAR_CTRL field. */

/*bit 17 :SMBUS_SLAVE_QUICK_EN configuration*/
#define I2C_IC_CON_SMBUS_SLAVE_QUICK_EN_POS (17ul) /*!< Position of SMBUS_SLAVE_QUICK_EN field. */
#define I2C_IC_CON_SMBUS_SLAVE_QUICK_EN_MSK (0x01ul << I2C_IC_CON_SMBUS_SLAVE_QUICK_EN_POS) /*!< Bit mask of SMBUS_SLAVE_QUICK_EN field. */

/*bit 19 :SMBUS_ARP_EN configuration*/
#define I2C_IC_CON_SMBUS_ARP_EN_POS (18ul) /*!< Position of SMBUS_ARP_EN field. */
#define I2C_IC_CON_SMBUS_ARP_EN_MSK (0x01ul << I2C_IC_CON_SMBUS_ARP_EN_POS) /*!< Bit mask of SMBUS_ARP_EN field. */

/*bit 19 :SMBUS_PERSISTENT_SLV_ADDR_EN configuration*/
#define I2C_IC_CON_SMBUS_PERSISTENT_SLV_ADDR_EN_POS (19ul) /*!< Position of SMBUS_PERSISTENT_SLV_ADDR_EN field. */
#define I2C_IC_CON_SMBUS_PERSISTENT_SLV_ADDR_EN_MSK (0x01ul << I2C_IC_CON_SMBUS_PERSISTENT_SLV_ADDR_EN_POS) /*!< Bit mask of SMBUS_PERSISTENT_SLV_ADDR_EN field. */



/* Register:  IC_TAR  */
/* Description: :I2C Target Address Register. */

/*bit 0-9 :IC_TAR configuration*/
#define I2C_IC_TAR_IC_TAR_POS (0ul) /*!< Position of IC_TAR field. */
#define I2C_IC_TAR_IC_TAR_MSK (0x03FFul << I2C_IC_TAR_IC_TAR_POS) /*!< Bit mask of IC_TAR field. */

/*bit 10 :GC_OR_START configuration*/
#define I2C_IC_TAR_GC_OR_START_POS (10ul) /*!< Position of GC_OR_START field. */
#define I2C_IC_TAR_GC_OR_START_MSK (0x1ul << I2C_IC_TAR_GC_OR_START_POS) /*!< Bit mask of GC_OR_START field. */

/*bit 11 :SPECIAL configuration*/
#define I2C_IC_TAR_SPECIAL_POS (11ul) /*!< Position of SPECIAL field. */
#define I2C_IC_TAR_SPECIAL_MSK (0x1ul << I2C_IC_TAR_SPECIAL_POS) /*!< Bit mask of SPECIAL field. */

/*bit 12 :IC_10BITADDR_MASTER configuration*/
#define I2C_IC_TAR_IC_10BITADDR_MASTER_POS (12ul) /*!< Position of IC_10BITADDR_MASTER field. */
#define I2C_IC_TAR_IC_10BITADDR_MASTER_MSK (0x1ul << I2C_IC_TAR_IC_10BITADDR_MASTER_POS) /*!< Bit mask of IC_10BITADDR_MASTER field. */


/*bit 13 :DEVICE_ID configuration*/
#define I2C_IC_TAR_DEVICE_ID_POS (13ul) /*!< Position of DEVICE_ID field. */
#define I2C_IC_TAR_DEVICE_ID_MSK (0x1ul << I2C_IC_TAR_DEVICE_ID_POS) /*!< Bit mask of DEVICE_ID field. */

/*bit 16 :SMBUS_QUICK_CMD configuration*/
#define I2C_IC_TAR_SMBUS_QUICK_CMD_POS (16ul) /*!< Position of SMBUS_QUICK_CMD field. */
#define I2C_IC_TAR_SMBUS_QUICK_CMD_MSK (0x1ul << I2C_IC_TAR_SMBUS_QUICK_CMD_POS) /*!< Bit mask of SMBUS_QUICK_CMD field. */

/**************/
/* Register:  IC_SAR  */
/* Description: :I2C Slave Address Register. */


/*bit 0-9 :IC_SAR configuration*/
#define I2C_IC_SAR_IC_SAR_POS (0ul) /*!< Position of IC_SAR field. */
#define I2C_IC_SAR_IC_SAR_MSK (0x03FFul << I2C_IC_SAR_IC_SAR_POS) /*!< Bit mask of IC_SAR field. */



/* Register:  IC_HS_MADDR  */
/* Description:  I2C High Speed Master Mode Code Address Register */

/*bit 0-2 :IC_HS_MAR configuration*/
#define I2C_IC_HS_MADDR_IC_HS_MAR_POS (0ul) /*!< Position of IC_HS_MAR field. */
#define I2C_IC_HS_MADDR_IC_HS_MAR_MSK (0x07ul << I2C_IC_HS_MADDR_IC_HS_MAR_POS) /*!< Bit mask of IC_HS_MAR field. */


/* Register:  IC_DATA_CMD  */
/* Description: I2C Rx/Tx Data Buffer and Command Register. */

/*bit 0-7 :DAT configuration*/
#define I2C_IC_DATA_CMD_DAT_POS (0ul) /*!< Position of DAT field. */
#define I2C_IC_DATA_CMD_DAT_MSK (0x0FFul << I2C_IC_DATA_CMD_DAT_POS) /*!< Bit mask of DAT field. */

/*bit 8 :CMD configuration*/
#define I2C_IC_DATA_CMD_CMD_POS (8ul) /*!< Position of CMD field. */
#define I2C_IC_DATA_CMD_CMD_MSK (0x01ul << I2C_IC_DATA_CMD_CMD_POS) /*!< Bit mask of CMD field. */

/*bit 9 :STOP configuration*/
#define I2C_IC_DATA_CMD_STOP_POS (9ul) /*!< Position of STOP field. */
#define I2C_IC_DATA_CMD_STOP_MSK (0x01ul << I2C_IC_DATA_CMD_STOP_POS) /*!< Bit mask of STOP field. */

/*bit 10 :RESTART configuration*/
#define I2C_IC_DATA_CMD_RESTART_POS (10ul) /*!< Position of RESTART field. */
#define I2C_IC_DATA_CMD_RESTART_MSK (0x01ul << I2C_IC_DATA_CMD_RESTART_POS) /*!< Bit mask of RESTART field. */

/*bit 11 :FIRST_DATA_BYTE configuration*/
#define I2C_IC_DATA_CMD_FIRST_DATA_BYTE_POS (11ul) /*!< Position of FIRST_DATA_BYTE field. */
#define I2C_IC_DATA_CMD_FIRST_DATA_BYTE_MSK (0x01ul << I2C_IC_DATA_CMD_FIRST_DATA_BYTE_POS) /*!< Bit mask of FIRST_DATA_BYTE field. */



/* Register:  IC_SS_SCL_HCNT  */
/* Description: Standard Speed I2C Clock SCL High Count Register. */

/*bit 0-15 :IC_SS_SCL_HCNT configuration*/
#define I2C_IC_IC_SS_SCL_HCNT_POS (0ul) /*!< Position of IC_SS_SCL_HCNT field. */
#define I2C_IC_IC_SS_SCL_HCNT_MSK (0x0fffful << I2C_IC_IC_SS_SCL_HCNT_POS) /*!< Bit mask of IC_SS_SCL_HCNT field. */

/* Register:  IC_UFM_SCL_HCNT  */
/* Description:  Ultra-Fast  I2C Clock SCL High Count Register. */

/*bit 0-15 :IC_UFM_SCL_HCNT configuration*/
#define I2C_IC_IC_UFM_SCL_HCNT_POS (0ul) /*!< Position of IC_UFM_SCL_HCNT field. */
#define I2C_IC_IC_UFM_SCL_HCNT_MSK (0x0fffful << I2C_IC_IC_UFM_SCL_HCNT_POS) /*!< Bit mask of IC_UFM_SCL_HCNT field. */

/* Register:  IC_SS_SCL_LCNT  */
/* Description: Standard Speed I2C Clock SCL Low Count Register. */

/*bit 0-15 :IC_SS_SCL_LCNT configuration*/
#define I2C_IC_IC_SS_SCL_LCNT_POS (0ul) /*!< Position of IC_SS_SCL_LCNT field. */
#define I2C_IC_IC_SS_SCL_LCNT_MSK (0x0fffful << I2C_IC_IC_SS_SCL_LCNT_POS) /*!< Bit mask of IC_SS_SCL_LCNT field. */

/* Register:  IC_UFM_SCL_LCNT  */
/* Description:  Ultra-Fast Speed I2C Clock SCL Low Count Register. */

/*bit 0-15 :IC_UFM_SCL_LCNT configuration*/
#define I2C_IC_IC_UFM_SCL_LCNT_POS (0ul) /*!< Position of IC_UFM_SCL_LCNT field. */
#define I2C_IC_IC_UFM_SCL_LCNT_MSK (0x0fffful << I2C_IC_IC_UFM_SCL_LCNT_POS) /*!< Bit mask of IC_UFM_SCL_LCNT field. */

/* Register:   IC_FS_SCL_HCNT  */
/* Description:  Fast Mode or Fast Mode Plus I2C Clock SCL High Count Register. */

/*bit 0-15 : IC_FS_SCL_HCNT configuration*/
#define I2C_IC_IC_FS_SCL_HCNT_POS (0ul) /*!< Position of  IC_FS_SCL_HCNT field. */
#define I2C_IC_IC_FS_SCL_HCNT_MSK (0x0fffful << I2C_IC_IC_FS_SCL_HCNT_POS) /*!< Bit mask of  IC_FS_SCL_HCNT field. */

/* Register:   IC_UFM_TBUF_CNT  */
/* Description:   Ultra-Fast Speed mode TBuf Idle Count Register. */

/*bit 0-15 : IC_UFM_TBUF_CNT configuration*/
#define I2C_IC_IC_UFM_TBUF_CNT_POS (0ul) /*!< Position of  IC_UFM_TBUF_CNT field. */
#define I2C_IC_IC_UFM_TBUF_CNT_MSK (0x0fffful << I2C_IC_IC_UFM_TBUF_CNT_POS) /*!< Bit mask of  IC_UFM_TBUF_CNT field. */

/* Register:   IC_FS_SCL_LCNT  */
/* Description:    Fast Mode or Fast Mode Plus I2C Clock SCL Low Count Register. */

/*bit 0-15 : IC_FS_SCL_LCNT configuration*/
#define I2C_IC_IC_FS_SCL_LCNT_POS (0ul) /*!< Position of  IC_FS_SCL_LCNT field. */
#define I2C_IC_IC_FS_SCL_LCNT_MSK (0x0fffful << I2C_IC_IC_FS_SCL_LCNT_POS) /*!< Bit mask of  IC_FS_SCL_LCNT field. */

/* Register:    IC_HS_SCL_HCNT  */
/* Description: High Speed I2C Clock SCL High Count Register. */

/*bit 0-15 :  IC_HS_SCL_HCNT configuration*/
#define I2C_IC_IC_HS_SCL_HCNT_POS (0ul) /*!< Position of   IC_HS_SCL_HCNT field. */
#define I2C_IC_IC_HS_SCL_HCNT_MSK (0x0fffful << I2C_IC_IC_HS_SCL_HCNT_POS) /*!< Bit mask of   IC_HS_SCL_HCNT field. */

/* Register:    IC_HS_SCL_LCNT  */
/* Description: High Speed I2C Clock SCL Low Count Register. */

/*bit 0-15 :  IC_HS_SCL_LCNT configuration*/
#define I2C_IC_IC_HS_SCL_LCNT_POS (0ul) /*!< Position of   IC_HS_SCL_LCNT field. */
#define I2C_IC_IC_HS_SCL_LCNT_MSK (0x0fffful << I2C_IC_IC_HS_SCL_LCNT_POS) /*!< Bit mask of   IC_HS_SCL_LCNT field. */




/* Register:    IC_RX_TL  */
/* Description: I2C Receive FIFO Threshold Register. */

/*bit 0-7 :  IC_RX_TL configuration*/
#define I2C_IC_IC_RX_TL_POS (0ul) /*!< Position of   IC_RX_TL field. */
#define I2C_IC_IC_RX_TL_MSK (0x0fful << I2C_IC_IC_RX_TL_POS) /*!< Bit mask of   IC_RX_TL field. */

/* Register:    IC_TX_TL  */
/* Description: I2C Transmit FIFO Threshold Register. */

/*bit 0-7 :  IC_TX_TL configuration*/
#define I2C_IC_IC_TX_TL_POS (0ul) /*!< Position of   IC_TX_TL field. */
#define I2C_IC_IC_TX_TL_MSK (0x0fful << I2C_IC_IC_TX_TL_POS) /*!< Bit mask of   IC_TX_TL field. */

/* Register:    IC_ENABLE  */
/* Description: I2C ENABLE Register . */

/*bit 0 :  ENABLE configuration*/
#define I2C_IC_IC_ENABLE_ENBALE_POS (0ul) /*!< Position of  ENBALE field. */
#define I2C_IC_IC_ENABLE_ENBALE_MSK (0x01ul << I2C_IC_IC_ENABLE_ENBALE_POS) /*!< Bit mask of   ENBALE field. */

/*bit 1 :  ABORT configuration*/
#define I2C_IC_IC_ENABLE_ABORT_POS (1ul) /*!< Position of  ABORT field. */
#define I2C_IC_IC_ENABLE_ABORT_MSK (0x01ul << I2C_IC_IC_ENABLE_ABORT_POS) /*!< Bit mask of   ABORT field. */

/*bit 2 :  TX_CMD_BLOCK configuration*/
#define I2C_IC_IC_ENABLE_TX_CMD_BLOCK_POS (2ul) /*!< Position of  TX_CMD_BLOCK field. */
#define I2C_IC_IC_ENABLE_TX_CMD_BLOCK_MSK (0x01ul << I2C_IC_IC_ENABLE_TX_CMD_BLOCK_POS) /*!< Bit mask of   TX_CMD_BLOCK field. */

/*bit 3 :  SDA_STUCK_RECOVERY_ENABLE configuration*/
#define I2C_IC_IC_ENABLE_SDA_STUCK_RECOVERY_ENABLE_POS (3ul) /*!< Position of  SDA_STUCK_RECOVERY_ENABLE field. */
#define I2C_IC_IC_ENABLE_SDA_STUCK_RECOVERY_ENABLE_MSK (0x01ul << I2C_IC_IC_ENABLE_SDA_STUCK_RECOVERY_ENABLE_POS) /*!< Bit mask of   SDA_STUCK_RECOVERY_ENABLE field. */

/*bit 16 :  SMBUS_CLK_RESET configuration*/
#define I2C_IC_IC_ENABLE_SMBUS_CLK_RESET_POS (16ul) /*!< Position of  SMBUS_CLK_RESET field. */
#define I2C_IC_IC_ENABLE_SMBUS_CLK_RESET_MSK (0x01ul << I2C_IC_IC_ENABLE_SMBUS_CLK_RESET_POS) /*!< Bit mask of   SMBUS_CLK_RESET field. */

/*bit 17 :  SMBUS_SUSPEND_EN configuration*/
#define I2C_IC_IC_ENABLE_SMBUS_SUSPEND_EN_POS (17ul) /*!< Position of  SMBUS_SUSPEND_EN field. */
#define I2C_IC_IC_ENABLE_SMBUS_SUSPEND_EN_MSK (0x01ul << I2C_IC_IC_ENABLE_SMBUS_SUSPEND_EN_POS) /*!< Bit mask of   SMBUS_SUSPEND_EN field. */

/*bit 18 :  SMBUS_ALERT_EN configuration*/
#define I2C_IC_IC_ENABLE_SMBUS_ALERT_EN_POS (18ul) /*!< Position of  SMBUS_ALERT_EN field. */
#define I2C_IC_IC_ENABLE_SMBUS_ALERT_EN_MSK (0x01ul << I2C_IC_IC_ENABLE_SMBUS_ALERT_EN_POS) /*!< Bit mask of   SMBUS_ALERT_EN field. */



/* Register:    IC_SDA_HOLD  */
/* Description: I2C SDA Hold Time Length Register. */

/*bit 0 -15:  IC_SDA_TX_HOLD configuration*/
#define I2C_IC_SDA_HOLD_IC_SDA_TX_HOLD_POS (0ul) /*!< Position of  IC_SDA_TX_HOLD field. */
#define I2C_IC_SDA_HOLD_IC_SDA_TX_HOLD_MSK (0xfffful << I2C_IC_SDA_HOLD_IC_SDA_TX_HOLD_POS) /*!< Bit mask of   IC_SDA_TX_HOLD field. */
/*bit 16 - 23 :  IC_SDA_RX_HOLD configuration*/
#define I2C_IC_SDA_HOLD_IC_SDA_RX_HOLD_POS (0ul) /*!< Position of  IC_SDA_RX_HOLD field. */
#define I2C_IC_SDA_HOLD_IC_SDA_RX_HOLD_MSK (0xfful << I2C_IC_SDA_HOLD_IC_SDA_RX_HOLD_POS) /*!< Bit mask of   IC_SDA_RX_HOLD field. */


/* Register:    IC_TX_ABRT_SOURCE  */
/* Description: I2C Transmit Abort Source Register. */

/*bit 23 -31:  TX_FLUSH_CNT configuration*/
#define I2C_IC_TX_ABRT_SOURCE_TX_FLUSH_CNT_POS (23ul) /*!< Position of  TX_FLUSH_CNT field. */
#define I2C_IC_TX_ABRT_SOURCE_TX_FLUSH_CNT_MSK (0xfful << I2C_IC_TX_ABRT_SOURCE_TX_FLUSH_CNT_POS) /*!< Bit mask of   TX_FLUSH_CNT field. */


/* Register:     IC_SLV_DATA_NACK_ONLY  */
/* Description: Generate Slave Data NACK Register. */

/*bit 0:  NACK configuration*/
#define I2C_IC_SLV_DATA_NACK_ONLY_NACK_POS (0ul) /*!< Position of  NACK field. */
#define I2C_IC_SLV_DATA_NACK_ONLY_NACK_MSK (0x1ul << I2C_IC_SLV_DATA_NACK_ONLY_NACK_POS) /*!< Bit mask of   NACK field. */

/* Register:     IC_DMA_CR  */
/* Description: DMA Control Register. */

/*bit 0:  RDMAE configuration*/
#define I2C_IC_DMA_CR_RDMAE_POS (0ul) /*!< Position of  RDMAE field. */
#define I2C_IC_DMA_CR_RDMAE_MSK (0x1ul << I2C_IC_DMA_CR_RDMAE_POS) /*!< Bit mask of   RDMAE field. */

/*bit 1:  TDMAE configuration*/
#define I2C_IC_DMA_CR_TDMAE_POS (1ul) /*!< Position of  TDMAE field. */
#define I2C_IC_DMA_CR_TDMAE_MSK (0x1ul << I2C_IC_DMA_CR_TDMAE_POS) /*!< Bit mask of   TDMAE field. */


/* Register:     IC_SDA_SETUP  */
/* Description: I2C SDA Setup Register. */

/*bit 0 - 7 :  SDA_SETUP configuration*/
#define I2C_IC_SDA_SETUP_SDA_SETUP_POS (0ul) /*!< Position of  SDA_SETUP field. */
#define I2C_IC_SDA_SETUP_SDA_SETUP_MSK (0xfful << I2C_IC_SDA_SETUP_SDA_SETUP_POS) /*!< Bit mask of   SDA_SETUP field. */


/* Register:     IC_ACK_GENERAL_CALL  */
/* Description: DMA Control Register. */

/*bit 0:  ACK_GEN_CALL configuration*/
#define I2C_IC_ACK_GENERAL_ACK_GEN_CALL_POS (0ul) /*!< Position of  ACK_GEN_CALL field. */
#define I2C_IC_ACK_GENERAL_ACK_GEN_CALL_MSK (0x1ul << I2C_IC_ACK_GENERAL_ACK_GEN_CALL_POS) /*!< Bit mask of   ACK_GEN_CALL field. */


/* Register:     IC_FS_SPKLEN  */
/* Description:  I2C SS, FS or FM+ spike suppression limit. */

/*bit 0 - 7:  IC_FS_SPKLEN configuration*/
#define I2C_IC_FS_SPKLEN_POS (0ul) /*!< Position of  IC_FS_SPKLEN field. */
#define I2C_FS_SPKLEN_MSK (0xFFul << I2C_IC_FS_SPKLEN_POS) /*!< Bit mask of   IC_FS_SPKLEN field. */

/* Register:     IC_UFM_SPKLEN  */
/* Description:  I2C Ultra-Fast mode spike suppression limit. */

/*bit 0 - 7:  IC_UFM_SPKLEN configuration*/
#define I2C_IC_UFM_SPKLEN_POS (0ul) /*!< Position of  IC_UFM_SPKLEN field. */
#define I2C_IC_UFM_SPKLEN_MSK (0xFFul << I2C_IC_UFM_SPKLEN_POS) /*!< Bit mask of   IC_UFM_SPKLEN field. */


/* Register:     IC_HS_SPKLEN  */
/* Description:  I2C HS spike suppression limit register. */

/*bit 0 - 7:  IC_HS_SPKLEN configuration*/
#define I2C_IC_HS_SPKLEN_POS (0ul) /*!< Position of  IC_HS_SPKLEN field. */
#define I2C_IC_HS_SPKLEN_MSK (0xFFul << I2C_IC_HS_SPKLEN_POS) /*!< Bit mask of   IC_HS_SPKLEN field. */


/* Register:     IC_SMBUS_THIGH_MAX_IDLE_COUNT  */
/* Description:   SMBus Master THigh MAX Bus-idle count Register. */

/*bit 0 - 15:  IC_SMBUS_THIGH_MAX_IDLE_COUNT configuration*/
#define I2C_IC_SMBUS_THIGH_MAX_IDLE_COUNT_POS (0ul) /*!< Position of  IC_SMBUS_THIGH_MAX_IDLE_COUNT field. */
#define I2C_IC_SMBUS_THIGH_MAX_IDLE_COUNT_MSK (0xFFFFul << I2C_IC_SMBUS_THIGH_MAX_IDLE_COUNT_POS) /*!< Bit mask of   IC_SMBUS_THIGH_MAX_IDLE_COUNT field. */



#endif

