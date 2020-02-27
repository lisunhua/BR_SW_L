/*
 *++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 * Copyright (c) 1999-2018 Barrot Technology Limited
 *
 * All rights reserved.
 *
 *------------------------------------------------------------------------------
 */
/**
 * @file    BR1051Axx_dma_if.h
 * @brief   This file provides all the dma register parameter.
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


#ifndef  __BR1051Axx_DMA_IF_H_
#define  __BR1051Axx_DMA_IF_H_


/* Peripheral: DMAC */
/* Description:  Direct Memory Access . */

/* Register: LLP  */
/* Description:   Linked List Pointer Register for Channel x. */

/*bit 0-1 : Identifies the AHB layer/interface where the memory device that stores the next linked list item resides.*/
#define DMAC_LLP_LMS_POS  (0ull) /*!< Position of LMS field. */
#define DMAC_LLP_LMS_MSK  (0x03ull << DMAC_LLP_LMS_POS) /*!< Bit mask of LMS field. */

/*bit 2-31 : Starting Address In Memory of next LLI if block chaining is
enabled. Note that the two LSBs of the starting address are
not stored because the address is assumed to be aligned to
a 32-bit boundary. LLI accesses are always 32-bit accesses
(Hsize=2) aligned to 32-bit boundaries and cannot be
changed or programmed to anything other than 32-bit.*/
#define DMAC_LLP_LOC_POS  (2ull) /*!< Position of LOC field. */
#define DMAC_LLP_LOC_MSK  (0x3FFFFFFFull << DMAC_LLP_LMS_POS) /*!< Bit mask of LOC field. */


/* Register: CTL  */
/* Description: Control Register for Channel x */
/*bit 0 : Interrupt Enable Bit.*/
#define DMAC_CTL_INT_EN_POS  (0ull) /*!< Position of  INT_EN field. */
#define DMAC_CTL_INT_EN_MSK  (0x01ull << DMAC_CTL_INT_EN_POS) /*!< Bit mask of  INT_EN field. */

/*bit 1-3 : Destination Transfer Width.*/
#define DMAC_CTL_DST_TR_WIDTH_POS  (1ull) /*!< Position of  DST_TR_WIDTH field. */
#define DMAC_CTL_DST_TR_WIDTH_MSK  (0x07ull << DMAC_CTL_DST_TR_WIDTH_POS) /*!< Bit mask of  DST_TR_WIDTH field. */

/*bit 4-6 : SRC_TR_WIDTH.*/
#define DMAC_CTL_SRC_TR_WIDTH_POS  (4ull) /*!< Position of  SRC_TR_WIDTH field. */
#define DMAC_CTL_SRC_TR_WIDTH_MSK  (0x07ull << DMAC_CTL_SRC_TR_WIDTH_POS) /*!< Bit mask of  SRC_TR_WIDTH field. */

/*bit 7-8 : Destination Address Increment.*/
#define DMAC_CTL_DINC_POS  (7ull) /*!< Position of  DINC field. */
#define DMAC_CTL_DINC_MSK  (0x03ull << DMAC_CTL_DINC_POS) /*!< Bit mask of  DINC field. */

/*bit 9-10 : Source Address Increment.*/
#define DMAC_CTL_SINC_POS  (9ull) /*!< Position of  SINC field. */
#define DMAC_CTL_SINC_MSK  (0x03ull << DMAC_CTL_SINC_POS) /*!< Bit mask of  SINC field. */

/*bit 11-13 : Destination Burst Transaction Length.*/
#define DMAC_CTL_DEST_MSIZE_POS  (11ull) /*!< Position of  DEST_MSIZE field. */
#define DMAC_CTL_DEST_MSIZE_MSK  (0x07ull << DMAC_CTL_DEST_MSIZE_POS) /*!< Bit mask of  DEST_MSIZE field. */

/*bit 14-16 : Source Burst Transaction Length.*/
#define DMAC_CTL_SRC_MSIZE_POS  (14ull) /*!< Position of  SRC_MSIZE field. */
#define DMAC_CTL_SRC_MSIZE_MSK  (0x07ull << DMAC_CTL_SRC_MSIZE_POS) /*!< Bit mask of  SRC_MSIZE field. */

/*bit 17 : Source gather enable.*/
#define DMAC_CTL_SRC_GATHER_EN_POS  (17ull) /*!< Position of  SRC_GATHER_EN field. */
#define DMAC_CTL_SRC_GATHER_EN_MSK  (0x01ull << DMAC_CTL_SRC_GATHER_EN_POS) /*!< Bit mask of  SRC_GATHER_EN field. */

/*bit 18 : Destination scatter enable.*/
#define DMAC_CTL_DST_SCATTER_EN_POS  (18ull) /*!< Position of  DST_SCATTER_EN field. */
#define DMAC_CTL_DST_SCATTER_EN_MSK  (0x01ull << DMAC_CTL_DST_SCATTER_EN_POS) /*!< Bit mask of  DST_SCATTER_EN field. */

/*bit 20 -22 :Transfer Type and Flow Control .*/
#define DMAC_CTL_TT_FC_POS  (20ull) /*!< Position of  TT_FC field. */
#define DMAC_CTL_TT_FC_MSK  (0x07ull << DMAC_CTL_TT_FC_POS) /*!< Bit mask of  TT_FC field. */

/*bit 23 -24 :Destination Master Select .*/
#define DMAC_CTL_DMS_POS  (23ull) /*!< Position of  DMS field. */
#define DMAC_CTL_DMS_MSK  (0x03ull << DMAC_CTL_DMS_POS) /*!< Bit mask of  DMS field. */

/*bit 25 -26 :Source Master Select .*/
#define DMAC_CTL_SMS_POS  (25ull) /*!< Position of  SMS field. */
#define DMAC_CTL_SMS_MSK  (0x03ull << DMAC_CTL_SMS_POS) /*!< Bit mask of  SMS field. */

/*bit 27 :Block chaining is enabled on the destination side only if LLP_DST_EN field is high and LLPx.LOC is non-zero .*/
#define DMAC_CTL_LLP_DST_EN_POS  (27ull) /*!< Position of  LLP_DST_ENfield. */
#define DMAC_CTL_LLP_DST_EN_MSK  (0x01ull << DMAC_CTL_LLP_DST_EN_POS) /*!< Bit mask of  LLP_DST_ENfield. */

/*bit 28 :Block chaining is enabled on the source side only if the LLP_SRC_EN field is high and LLPx.LOC is non-zero. .*/
#define DMAC_CTL_LLP_SRC_EN_POS  (28ull) /*!< Position of  LLP_SRC_ENfield. */
#define DMAC_CTL_LLP_SRC_EN_MSK  (0x01ull << DMAC_CTL_LLP_SRC_EN_POS) /*!< Bit mask of  LLP_SRC_ENfield. */

/*bit 32-43 :Block Transfer Size.*/
#define DMAC_CTL_BLOCK_TS_POS  (32ull-32ull) /*!< Position of  BLOCK_TSfield. */
#define DMAC_CTL_BLOCK_TS_MSK  (0xfffull << DMAC_CTL_BLOCK_TS_POS) /*!< Bit mask of  BLOCK_TSfield. */

/*bit 44 :Done bit.*/
#define DMAC_CTL_DONE_POS  (44ull-32ull) /*!< Position of  DONEfield. */
#define DMAC_CTL_DONE_MSK  (0x01ull << DMAC_CTL_DONE_POS) /*!< Bit mask of  DONEfield. */



/* Register: CFG  */
/* Description: Configuration Register for Channel x*/
/*bit 5-7 : Channel Priority.*/
#define DMAC_CFG_CH_PRIOR_POS  (5ull) /*!< Position of  CH_PRIOR field. */
#define DMAC_CFG_CH_PRIOR_MSK  (0x07ull << DMAC_CFG_CH_PRIOR_POS) /*!< Bit mask of  CH_PRIOR field. */

/*bit 8 : Channel Suspend.*/
#define DMAC_CFG_CH_SUSP_POS  (8ull) /*!< Position of  CH_SUSP field. */
#define DMAC_CFG_CH_SUSP_MSK  (0x01ull << DMAC_CFG_CH_SUSP_POS) /*!< Bit mask of  CH_SUSP field. */

/*bit 9 : Channel FIFO status.*/
#define DMAC_CFG_FIFO_EMPTY_POS  (9ull) /*!< Position of  FIFO_EMPTY field. */
#define DMAC_CFG_FIFO_EMPTY_MSK  (0x01ull << DMAC_CFG_FIFO_EMPTY_POS) /*!< Bit mask of  FIFO_EMPTY field. */

/*bit 10 : Destination Software or Hardware Handshaking Select */
#define DMAC_CFG_HS_SEL_DST_POS  (10ull) /*!< Position of  HS_SEL_DST field. */
#define DMAC_CFG_HS_SEL_DST_MSK  (0x01ull << DMAC_CFG_HS_SEL_DST_POS) /*!< Bit mask of  HS_SEL_DST field. */

/*bit 11 : Source Software or Hardware Handshaking Select. */
#define DMAC_CFG_HS_SEL_SRC_POS  (11ull) /*!< Position of  HS_SEL_SRC field. */
#define DMAC_CFG_HS_SEL_SRC_MSK  (0x01ull << DMAC_CFG_HS_SEL_SRC_POS) /*!< Bit mask of  HS_SEL_SRC field. */

/*bit 12-13 : Channel Local Level . */
#define DMAC_CFG_LOCK_CH_L_POS  (12ull) /*!< Position of  LOCK_CH_L field. */
#define DMAC_CFG_LOCK_CH_L_MSK  (0x03ull << DMAC_CFG_LOCK_CH_L_POS) /*!< Bit mask of  LOCK_CH_L field. */

/*bit 14-15 : Bus lock level . */
#define DMAC_CFG_LOCK_B_L_POS  (14ull) /*!< Position of  LOCK_B_L field. */
#define DMAC_CFG_LOCK_B_L_MSK  (0x03ull << DMAC_CFG_LOCK_B_L_POS) /*!< Bit mask of  LOCK_B_L field. */

/*bit 16 : Channel Lock Bit. */
#define DMAC_CFG_LOCK_CH_POS  (16ull) /*!< Position of  LOCK_CH field. */
#define DMAC_CFG_LOCK_CH_MSK  (0x01ull << DMAC_CFG_LOCK_CH_POS) /*!< Bit mask of  LOCK_CH field. */

/*bit 17 : Bus Lock Bit . */
#define DMAC_CFG_LOCK_B_POS  (17ull) /*!< Position of  LOCK_B field. */
#define DMAC_CFG_LOCK_B_MSK  (0x01ull << DMAC_CFG_LOCK_B_POS) /*!< Bit mask of  LOCK_B field. */

/*bit 18 : Destination Handshaking Interface Polarity. */
#define DMAC_CFG_DST_HS_POL_POS  (18ull) /*!< Position of  DST_HS_POL field. */
#define DMAC_CFG_DST_HS_POL_MSK  (0x01ull << DMAC_CFG_DST_HS_POL_POS) /*!< Bit mask of  DST_HS_POL field. */

/*bit 19 : Source Handshaking Interface Polarity. */
#define DMAC_CFG_SRC_HS_POL_POS  (19ull) /*!< Position of  SRC_HS_POL field. */
#define DMAC_CFG_SRC_HS_POL_MSK  (0x01ull << DMAC_CFG_SRC_HS_POL_POS) /*!< Bit mask of  SRC_HS_POL field. */

/*bit 20-29 : Maximum AMBA Burst Length . */
#define DMAC_CFG_MAX_ABRST_POS  (20ull) /*!< Position of  MAX_ABRST field. */
#define DMAC_CFG_MAX_ABRST_MSK  (0x03FFull << DMAC_CFG_MAX_ABRST_POS) /*!< Bit mask of  MAX_ABRST field. */

/*bit 30 : Automatic Source Reload. */
#define DMAC_CFG_RELOAD_SRC_POS  (30ull) /*!< Position of  RELOAD_SRC field. */
#define DMAC_CFG_RELOAD_SRC_MSK  (0x01ull << DMAC_CFG_RELOAD_SRC_POS) /*!< Bit mask of  RELOAD_SRC field. */

/*bit 31 : Automatic Destination Reload. */
#define DMAC_CFG_RELOAD_DST_POS  (31ull) /*!< Position of  RELOAD_DST field. */
#define DMAC_CFG_RELOAD_DST_MSK  (0x01ull << DMAC_CFG_RELOAD_DST_POS) /*!< Bit mask of  RELOAD_DST field. */

/*bit 32 : Flow Control Mode. */
#define DMAC_CFG_FCMODE_POS  (32ull - 32ul) /*!< Position of  FCMODE field. */
#define DMAC_CFG_FCMODE_MSK  (0x01ull << DMAC_CFG_FCMODE_POS) /*!< Bit mask of  FCMODE field. */

/*bit 33 : FIFO Mode Select. */
#define DMAC_CFG_FIFO_MODE_POS  (33ull - 32ul) /*!< Position of  FIFO_MODE field. */
#define DMAC_CFG_FIFO_MODE_MSK  (0x01ull << DMAC_CFG_FIFO_MODE_POS) /*!< Bit mask of  FIFO_MODE field. */

/*bit 34-36 : Protection Control . */
#define DMAC_CFG_PROTCTL_POS  (34ull - 32ul) /*!< Position of  PROTCTL field. */
#define DMAC_CFG_PROTCTL_MSK  (0x07ull << DMAC_CFG_PROTCTL_POS) /*!< Bit mask of  PROTCTL field. */

/*bit 37 : Destination Status Update Enable. */
#define DMAC_CFG_DS_UPD_EN_POS  (37ull - 32ul) /*!< Position of  DS_UPD_EN field. */
#define DMAC_CFG_DS_UPD_EN_MSK  (0x01ull << DMAC_CFG_DS_UPD_EN_POS) /*!< Bit mask of  DS_UPD_EN field. */

/*bit 38 : Source Status Update Enable. */
#define DMAC_CFG_SS_UPD_EN_POS  (38ull - 32ul) /*!< Position of  SS_UPD_EN field. */
#define DMAC_CFG_SS_UPD_EN_MSK  (0x01ull << DMAC_CFG_SS_UPD_EN_POS) /*!< Bit mask of  SS_UPD_EN field. */

/*bit 39-42 : Source Hardware Interface. */
#define DMAC_CFG_SRC_PER_POS  (39ull - 32ul) /*!< Position of  SRC_PER field. */
#define DMAC_CFG_SRC_PER_MSK  (0x0Full << DMAC_CFG_SRC_PER_POS) /*!< Bit mask of  SRC_PER field. */

/*bit 43-46 : Destination Hardware Interface. */
#define DMAC_CFG_DEST_PER_POS  (43ull - 32ul) /*!< Position of  DEST_PER field. */
#define DMAC_CFG_DEST_PER_MSK  (0x0Full << DMAC_CFG_DEST_PER_POS) /*!< Bit mask of  DEST_PER field. */




/* Register: SGR  */
/* Description: Source Gather Register for Channelx*/

/*bit 0-19 :Source Gather Interval. */
#define DMAC_SGR_SGI_POS  (0ull) /*!< Position of  SGI field. */
#define DMAC_SGR_SGI_MSK  (0x0FFFFFull << DMAC_SGR_SGI_POS) /*!< Bit mask of  SGI field. */

/*bit 20-31 :Source Gather Count.  */
#define DMAC_SGR_SGC_POS  (20ull) /*!< Position of  SGC field. */
#define DMAC_SGR_SGC_MSK  (0x0FFFull << DMAC_SGR_SGC_POS) /*!< Bit mask of  SGC field. */


/* Register: DSR  */
/* Description: Destination Scatter Register for Channel x */

/*bit 0-19 :Destination Gather Interval. */
#define DMAC_DSR_DSI_POS  (0ull) /*!< Position of  DSI field. */
#define DMAC_DSR_DSI_MSK  (0x0FFFFFull << DMAC_SGR_SGI_POS) /*!< Bit mask of  DSI field. */

/*bit 20-31 :Destination Gather Count.  */
#define DMAC_DSR_DSC_POS  (20ull) /*!< Position of   DSC field. */
#define DMAC_DSR_DSC_MSK  (0x0FFFull << DMAC_DSR_DSC_POS) /*!< Bit mask of   DSC field. */



#endif /*__BR1051Axx_DMA_IF_H_*/

