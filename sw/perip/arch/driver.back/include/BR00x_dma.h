/*
 *++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 * Copyright (c) 1999-2018 Barrot Technology Limited
 *
 * All rights reserved.
 *
 *------------------------------------------------------------------------------
 */
/**
 * @file    BR00x_dma.h
 * @brief   This file provides all the DMA firmware functions.
 * @attention
 *
 * THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
 * WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE
 * TIME. AS A RESULT, STMICROELECTRONICS SHALL NOT BE HELD LIABLE FOR ANY
 * DIRECT, INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING
 * FROM THE CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE
 * CODING INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
 *
 * @date    11-Augest-2018
 * @version V1.0.0
 * @author  Asher
*/

#ifndef __BR00x_DMA_H__
#define __BR00x_DMA_H__

#include "BR00x_config.h"

typedef enum {
    DMA_CH_0,
    DMA_CH_1,
    DMA_CH_2,
    DMA_CH_3,
    DMA_CH_4,
    DMA_CH_5,
    DMA_CH_6,
    DMA_CH_7,
    DMA_CH_END,
} DMA_ChNum_Type;

#define IS_DMA_CHANNEL(_ch)             (_ch < DMA_CH_END ? SET : RESET)

/*!< Transfer Type and Flow Control: 
        Flow control can be assigned to the DMA, the source peripheral, or the destination peripheral. For more information on transfer
      types and flow control, refer to "Setup/Operation of the DMA Transfers".
    Dependencies: If the configuration parameter
        DMA_CHx_FC is set to DMA_FC_ONLY, then TT_FC[2] does not exist and TT_FC[2] always reads back 0. If DMA_CHx_FC is set to SRC_FC_ONLY, 
      then TT_FC[2:1] does not exist and TT_FC[2:1] always reads back 2'b10. If DMA_CHx_FC is set to DST_FC_ONLY, then TT_FC[2:1] does 
      not exist and TT_FC[2:1] always reads back 2'b11.
        For multi-block transfers using linked list operation, TT_FC
      must be constant for all blocks of this multi-block transfer. */
typedef enum {
    DMA_TT_M2M_TC_D,                    /*!< Transfer type is Memory to Memory and Flow Controller is DMA. */
    DMA_TT_M2P_TC_D,                    /*!< Transfer type is Memory to Peripheral and Flow Controller is DMA. */
    DMA_TT_P2M_TC_D,                    /*!< Transfer type is Peripheral to Memory and Flow Controller is DMA. */
    DMA_TT_P2P_TC_D,                    /*!< Transfer type is Peripheral to Peripheral and Flow Controller is DMA. */
    DMA_TT_P2M_TC_P,                    /*!< Transfer type is Peripheral to Memory and Flow Controller is Peripheral. */
    DMA_TT_P2P_TC_SP,                   /*!< Transfer type is Peripheral to Peripheral and Flow Controller is Source Peripheral. */
    DMA_TT_M2P_TC_P,                    /*!< Transfer type is Memory to Peripheral and Flow Controller is Peripheral. */
    DMA_TT_P2P_TC_DP,                   /*!< Transfer type is Peripheral to Peripheral and Flow Controller is Destination Peripheral. */
} DMA_TTTC_Type;

/*!< Burst Transaction Length: 
    Number of data items, each of width, to be read from the source every time a burst transferred request is made from either the corresponding 
  hardware or software handshaking interface. */
typedef enum {
    DMA_MSIZE_1,                        /*!< Number of data items to be transferred is 1 */
    DMA_MSIZE_4,                        /*!< Number of data items to be transferred is 4 */
    DMA_MSIZE_8,                        /*!< Number of data items to be transferred is 8 */
    DMA_MSIZE_16,                       /*!< Number of data items to be transferred is 16 */
    DMA_MSIZE_32,                       /*!< Number of data items to be transferred is 32 */
} DMA_MSize_Type;

/*!< Address Increment: 
    Indicates whether to increment or decrement the source/destination address on every source transfer. If the device is fetching data from/to
  a source/destination peripheral FIFO with a fixed address, then set this field to "No change". */
typedef enum {
    DMA_IM_INC,                         /*!< Increments the address */
    DMA_IM_DEC,                         /*!< Decrements the address */
    DMA_IM_NO_CHANGE_0,                 /*!< No change in the address */
    DMA_IM_NO_CHANGE_1,                 /*!< No change in the address */
} DMA_INCMode_Type;

/*!< Transfer Width: 
    Mapped to AHB bus hsize. For a non-memory peripheral, typically the peripheral (source) FIFO width. */
typedef enum {
    DMA_TW_8,                           /*!< transfer width is 8 bits */
    DMA_TW_16,                          /*!< transfer width is 16 bits */
    DMA_TW_32,                          /*!< transfer width is 32 bits */
} DMA_TransWidth_Type;

/*!< FIFO Mode Select:
    Determines how much space or data needs to be available in the FIFO before a burst transaction request is serviced. */
typedef enum {
    DMA_FM_MODE_0,                      /*!< Space/data available for single AHB transfer of the specified transfer width. */
    DMA_FM_MODE_1,                      /*!< Data available is greater than or equal to half the FIFO depth for destination transfers and
                                            space available is greater than half the fifo depth for source transfers. The exceptions are at the end
                                            of a burst transaction request or at the end of a block transfer. */
} DMA_FifoMode_Type;

/*!< Flow Control Mode:
    Determines when source transaction requests are serviced when the Destination Peripheral is the flow controller. */
typedef enum {
    DMA_FC_MODE_0,                      /*!< Source transaction requests are serviced when they occur. Data pre-fetching is enabled. */
    DMA_FC_MODE_1,                      /*!< Source transaction requests are not serviced until a destination transaction request occurs. 
                                            In this mode, the amount of data transferred from the source is limited so that it is guaranteed to be
                                            transferred to the destination prior to block termination by the destination. Data pre-fetching is disabled. */
} DMA_FCMode_Type;

/*!< Handshaking Interface Polarity. */
typedef enum {
    DMA_HP_ACTIVE_HIGH,                 /*!< Source Handshaking Interface Polarity is Active high. */
    DMA_HP_ACTIVE_LOW,                  /*!< Source Handshaking Interface Polarity is Active low. */
} DMA_HSPolMode_Type;

/*!< Software or Hardware Handshaking Select:
    This register selects which of the handshaking interfaces - hardware or software - is active for source requests on this channel. 
    If the source peripheral is memory, then this bit is ignored.*/
typedef enum {
    DMA_HS_HARDWARE,                    /*!< Hardware handshaking interface. Software initiated transaction requests are ignored. */
    DMA_HS_SOFTWARE,                    /*!< Software handshaking interface. Hardware initiated transaction requests are ignored. */
} DMA_HSSelMode_Type;

/*!< Channel Priority:
    A priority of 7 is the highest priority, and 0 is the lowest. */
typedef enum {
    DMA_CP_PRIOR_0,                     /*!< Channel priority is 0. */
    DMA_CP_PRIOR_1,                     /*!< Channel priority is 1. */
    DMA_CP_PRIOR_2,                     /*!< Channel priority is 2. */
    DMA_CP_PRIOR_3,                     /*!< Channel priority is 3. */
    DMA_CP_PRIOR_4,                     /*!< Channel priority is 4. */
    DMA_CP_PRIOR_5,                     /*!< Channel priority is 5. */
    DMA_CP_PRIOR_6,                     /*!< Channel priority is 6. */
    DMA_CP_PRIOR_7,                     /*!< Channel priority is 7. */
} DMA_ChPriority_Type;

/*!< Interrupt Type:
    There are several groups of interrupt-related registers:
        | RawBlock, RawDstTran, RawErr, RawSrcTran, RawTfr
        | StatusBlock, StatusDstTran, StatusErr, StatusSrcTran, StatusTfr
        | MaskBlock, MaskDstTran, MaskErr, MaskSrcTran, MaskTfr
        | ClearBlock, ClearDstTran, ClearErr, ClearSrcTran, ClearTfr
        | StatusInt
    When a channel has been enabled to generate interrupts, the following is true:
        | Interrupt events are stored in the Raw Status registers.
        | The contents of the Raw Status registers are masked with the contents of the Mask registers.
        | The masked interrupts are stored in the Status registers.
        | The contents of the Status registers are used to drive the int_* port signals.
        | Writing to the appropriate bit in the Clear registers clears an interrupt in the Raw Status registers and
      the Status registers on the same clock cycle.
    The contents of each of the five Status registers is ORed to produce a single bit for each interrupt type in the
    Combined Status register; that is, StatusInt. */
typedef enum {
    DMA_IT_TFR,                         /*!< DMA Transfer Complete Interrupt:
                                            This interrupt is generated on DMA transfer completion to the destination peripheral. */
    DMA_IT_BLOCK,                       /*!< Block Transfer Complete Interrupt:
                                            This interrupt is generated on DMA block transfer completion to the destination peripheral. */
    DMA_IT_SRCTRAN,                     /*!<  Source Transaction Complete Interrupt:
                                            This interrupt is generated after completion of the last AHB transfer of the requested single/burst transaction 
                                            from the handshaking interface (either the hardware or software handshaking interface) on the source side. */
    DMA_IT_DSTTRAN,                     /*!< Destination Transaction Complete Interrupt:
                                            This interrupt is generated after completion of the last AHB transfer of the requested single/burst transaction 
                                            from the handshaking interface (either the hardware or software handshaking interface) on the destination side. */
    DMA_IT_ERR                          /*!< Error Interrupt:
                                            This interrupt is generated when an ERROR response is received from an AHB slave on the HRESP bus during a DMA 
                                            transfer. In addition, the DMA transfer is cancelled and the channel is disabled. */
} DMA_IntType_Type;


/*!< hardware interface>*/
typedef enum{
    DMA_UART0_TX,   
    DMA_UART0_RX,
    DMA_SPIM0_TX,
    DMA_SPIM0_RX,
    DMA_SPIM1_TX,
    DMA_SPIM1_RX,
    DMA_SPIS1_TX,
    DMA_SPIS1_RX,
    DMA_I2C_TX,
    DMA_I2C_RX,
    DMA_USB_CH0,
    DMA_USB_CH1,
    DMA_USB_CH2,
    DMA_USB_CH3,
    DMA_USB_CH4,
    DMA_USB_CH5,
}DMA_HardInterface_Type;


typedef struct {
    uint32_t src_addr;                  /*!< The source address. */
    uint32_t dst_addr;                  /*!< The destination address. */
    uint16_t block_size;                /*!< Block Transfer Size. */
    FunctionalState src_llp_en;         /*!< Block chaining is enabled/disabled on the source side. */
    FunctionalState dst_llp_en;         /*!< Block chaining is enabled/disabled on the destination side. */
    DMA_TTTC_Type tt_tc_mode;           /*!< Transfer Type and Flow Control. */
    DMA_MSize_Type src_msize;           /*!< Burst Transaction Length on the source side. */
    DMA_MSize_Type dst_msize;           /*!< Burst Transaction Length on the destination side. */
    DMA_INCMode_Type src_inc_mode;      /*!< Address increment mode on the source side. */
    DMA_INCMode_Type dst_inc_mode;      /*!< Address increment mode on the destination side. */
    DMA_TransWidth_Type src_trans_w;    /*!< Transfer Width on the source side. */
    DMA_TransWidth_Type dst_trans_w;    /*!< Transfer Width on the destination side. */
    FunctionalState int_en;             /*!< Interrupt enable. */

    //Configuration
    DMA_FifoMode_Type fifo_mode;        /*!< FIFO Mode Select. */
    DMA_FCMode_Type fc_mode;            /*!< Flow Control Mode. */
    FunctionalState src_reload_en;      /*!< Automatic source reload enable. */
    FunctionalState dst_reload_en;      /*!< Automatic destination reload enable. */
    uint16_t max_abrst;                 /*!< Maximum Burst Length:
                                            Maximum burst length that is used for DMA transfers on this channel. A value of 0 indicates that software 
                                            is not limiting the maximum burst length for DMA transfers on this channel. */
    DMA_HSPolMode_Type src_hs_pol;      /* Source handshaking interface polarity. */
    DMA_HSPolMode_Type dst_hs_pol;      /* Destination handshaking interface polarity. */
    DMA_HSSelMode_Type src_hs_sel;      /* Source software or hardware handshaking select. */
    DMA_HSSelMode_Type dst_hs_sel;      /* Destination software or hardware handshaking select. */
    FunctionalState ch_suspend;         /*!< Channel suspend:
                                            Suspends all DMA data transfers from the source until this bit is cleared. There is no guarantee that the 
                                            current transaction will complete. Can also be used in conjunction with CFGx.FIFO_EMPTY to cleanly disable 
                                            a channel without losing any data.*/
    DMA_ChPriority_Type ch_priority;    /*!< Channel priority. */
    
    DMA_HardInterface_Type src_per;
    DMA_HardInterface_Type dst_per;
    
} DMA_InitInfo_Type;

/**
  * @brief  Deinitializes the DMA peripheral registers to their default reset values.
  * @param  None
  * @retval None
  */
void DMA_DeInit(void);

/**
  * @brief  Initializes the DMA peripheral according to the specified
  *         parameters in the DMA_InitInfo_Type.
  * @param  ch: pointer to a DMA channel.
  * @param  DMA_InitStru: pointer to a UART_InitInfo_Type structure that
  *         contains the configuration information for the specified DMA peripheral.
  * @retval None
  */
void DMA_Init(DMA_ChNum_Type ch, DMA_InitInfo_Type *DMA_InitStru);

/**
  * @brief  Enable/Disable the DMA peripheral.
  * @param  st: New status for DMA peripheral.
  * @retval None
  */
void DMA_Enable(FunctionalState st);

/**
  * @brief  Enable/Disable the specified channel of DMA peripheral.
  * @param  ch: pointer to a DMA channel.
  * @param  st: New status for DMA peripheral channel.
  * @retval None
  */
void DMA_EnableCh(DMA_ChNum_Type ch, FunctionalState st);

/**
  * @brief  Get the fifo empty status for specified channel of DMA peripheral.
  * @param  ch: pointer to a DMA channel.
  * @retval Status (SET mean empty, RESET mean not.)
  */
FlagStatus DMA_IsFifoEmpty(DMA_ChNum_Type ch);

/**
  * @brief  Enable/Disable suspend the specified channel of DMA peripheral.
  * @param  ch: pointer to a DMA channel.
  * @param  st: New suspend status for DMA peripheral channel.
  * @retval None
  */
void DMA_SuspendEn(DMA_ChNum_Type ch, FunctionalState st);

/**
  * @brief  Get the interrupt RAW status for specified channel and interruot type of DMA peripheral.
  * @param  ch: pointer to a DMA channel.
  * @param  type: which interrupt type RAW status will be got.
  * @retval Status (SET/RESET).
  */
ITStatus DMA_GetIntRawStatus(DMA_ChNum_Type ch, DMA_IntType_Type type);

/**
  * @brief  Set the interrupt RAW status for specified channel and interruot type of DMA peripheral. Write access is available to this register 
  *         or software testing purposes only. Under normal operation, writes to this register are not recommended.
  * @param  ch: pointer to a DMA channel.
  * @param  type: which interrupt type RAW status will be got.
  * @param  flag: new status.
  * @retval None.
  */
void DMA_SetIntRawStatus(DMA_ChNum_Type ch, DMA_IntType_Type type, FlagStatus flag);

/**
  * @brief  Get the interrupt status after masking for specified channel and interruot type of DMA peripheral.
  * @param  ch: pointer to a DMA channel.
  * @param  type: which interrupt type status will be got.
  * @retval Status (SET/RESET).
  */
ITStatus DMA_GetIntStatus(DMA_ChNum_Type ch, DMA_IntType_Type type);

/**
  * @brief  Set the interrupt mask for specified channel and interruot type of DMA peripheral.
  * @ref    Interrupt Type.
  * @param  ch: pointer to a DMA channel.
  * @param  type: which interrupt mask will be set.
  * @param  flag: new status. (SET: unmask the interrupts, RESET: mask the interrupts)
  * @retval None.
  */
void DMA_SetIntMask(DMA_ChNum_Type ch, DMA_IntType_Type type, FlagStatus flag);

/**
  * @brief  Get the interrupt mask for specified channel and interruot type of DMA peripheral.
  * @param  ch: pointer to a DMA channel.
  * @param  type: which interrupt type status will be got.
  * @retval Status (SET/RESET).
  */
ITStatus DMA_GetIntMask(DMA_ChNum_Type ch, DMA_IntType_Type type);

/**
  * @brief  Clear the interrupt status from RAW/STATUS register for specified channel and interruot type of DMA peripheral.
  * @ref    Interrupt Type.
  * @param  ch: pointer to a DMA channel.
  * @param  type: which interrupt mask will be cleared.
  * @retval None.
  */
void DMA_ClearInt(DMA_ChNum_Type ch, DMA_IntType_Type type);

#endif /* __BR00x_DMA_H__ */

