/*
 *++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 * Copyright (c) 1999-2018 Barrot Technology Limited
 *
 * All rights reserved.
 *
 *------------------------------------------------------------------------------
 */
/**
 * @file    BR1051Axx_ssic_if.c
 * @brief    This file provides all the ssic register parameter.
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

#ifndef __BT1051Axx_SSIC_IF_H__
#define __BT1051Axx_SSIC_IF_H__


/* Peripheral: SSI */
/* Description:Synchronous Serial Interface */

/* Register: CTRLR0 */
/* Description: Control Register 0*/

/*bit 0-4 :Data Frame Size*/
#define SSIC_CTRLR0_DFS_POS (0ul) /*!< Position of DFS field. */
#define SSIC_CTRLR0_DFS_MSK (0x1Ful << SSIC_CTRLR0_DFS_POS) /*!< Bit mask of DFS field. */

/*bit 6-7 :Frame Format*/
#define SSIC_CTRLR0_FRF_POS (6ul) /*!< Position of FRF field. */
#define SSIC_CTRLR0_FRF_MSK (0x3ul << SSIC_CTRLR0_FRF_POS) /*!< Bit mask of FRF field. */

/*bit 8 :Serial Clock Phase*/
#define SSIC_CTRLR0_SCPH_POS (8ul) /*!< Position of SCPH field. */
#define SSIC_CTRLR0_SCPH_MSK (0x1ul << SSIC_CTRLR0_SCPH_POS) /*!< Bit mask of SCPH field. */

/*bit 9 :Serial Clock Polarity*/
#define SSIC_CTRLR0_SCPOL_POS (9ul) /*!< Position of SCPOL field. */
#define SSIC_CTRLR0_SCPOL_MSK (0x1ul << SSIC_CTRLR0_SCPOL_POS) /*!< Bit mask of SCPOL field. */

/*bit 10-11  :Transfer Mode*/
#define SSIC_CTRLR0_TMOD_POS (10ul) /*!< Position of TMOD field. */
#define SSIC_CTRLR0_TMOD_MSK (0x3ul << SSIC_CTRLR0_TMOD_POS) /*!< Bit mask of TMOD field. */

/*bit 12  :Slave Output Enable*/
#define SSIC_CTRLR0_SLV_OE_POS (12ul) /*!< Position of SLV_OE field. */
#define SSIC_CTRLR0_SLV_OE_MSK (0x1ul << SSIC_CTRLR0_SLV_OE_POS) /*!< Bit mask of SLV_OE field. */

/*bit 13  :Shift Register Loop*/
#define SSIC_CTRLR0_SRL_POS (13ul) /*!< Position of SRL field. */
#define SSIC_CTRLR0_SRL_MSK (0x1ul << SSIC_CTRLR0_SRL_POS) /*!< Bit mask of SRL field. */


/*bit 14  :Slave Select Toggle Enable*/
#define SSIC_CTRLR0_SSTE_POS (14ul) /*!< Position of SSTE field. */
#define SSIC_CTRLR0_SSTE_MSK (0x1ul << SSIC_CTRLR0_SSTE_POS) /*!< Bit mask of SSTE field. */

/*bit 16-19  :Control Frame Size*/
#define SSIC_CTRLR0_CFS_POS (16ul) /*!< Position of CFS field. */
#define SSIC_CTRLR0_CFS_MSK (0xFul << SSIC_CTRLR0_CFS_POS) /*!< Bit mask of CFS field. */


/*bit 22-23  :SPI Frame Format*/
#define SSIC_CTRLR0_SPI_FRF_POS (22ul) /*!< Position of SPI_FRF field. */
#define SSIC_CTRLR0_SPI_FRF_MSK (0x3ul << SSIC_CTRLR0_SPI_FRF_POS) /*!< Bit mask of SPI_FRF field. */


/*bit 24  :SPI Hyperbus Frame format enable.*/
#define SSIC_CTRLR0_SPI_HYPERBUS_EN_POS (24ul) /*!< Position of SPI_HYPERBUS_EN field. */
#define SSIC_CTRLR0_SPI_HYPERBUS_EN_MSK (0x1ul << SSIC_CTRLR0_SPI_HYPERBUS_EN_POS) /*!< Bit mask of SPI_HYPERBUS_EN field. */


/* Register: CTRLR1 */
/* Description: Control Register 1 */

/*bit 0-15 :Data Frame Size*/
#define SSIC_CTRLR1_NDF_POS (0ul) /*!< Position of NDF field. */
#define SSIC_CTRLR1_NDF_MSK (0xFFFFul << SSIC_CTRLR1_NDF_POS) /*!< Bit mask of NDF field. */

/* Register: DWCSSIENR */
/* Description: DWCSSI Enable Register */

/*bit 0 :DWCSSI Enable*/
#define SSIC_DWCSSIENR_SSIC_EN_POS (0ul) /*!< Position of SSIC_EN field. */
#define SSIC_DWCSSIENR_SSIC_EN_MSK (0x1ul << SSIC_DWCSSIENR_SSIC_EN_POS) /*!< Bit mask of SSIC_EN field. */


/* Register: MWCR */
/* Description: Microwire Control Register*/

/*bit 0 : Microwire Transfer Mode */
#define SSIC_MWCR_MWMOD_POS (0ul) /*!< Position of MWMOD field. */
#define SSIC_MWCR_MWMOD_MSK (0x1ul << SSIC_MWCR_MWMOD_POS) /*!< Bit mask of MWMOD field. */

/*bit 1 : Microwire Control*/
#define SSIC_MWCR_MDD_POS (1ul) /*!< Position of MDD field. */
#define SSIC_MWCR_MDD_MSK (0x1ul << SSIC_MWCR_MDD_POS) /*!< Bit mask of MDD field. */

/*bit 2 : Microwire Handshaking*/
#define SSIC_MWCR_MHS_POS (2ul) /*!< Position of MHS field. */
#define SSIC_MWCR_MHS_MSK (0x1ul << SSIC_MWCR_MHS_POS) /*!< Bit mask of MHS field. */


/* Register: SER */
/* Description: Slave Enable Register */

/*bit 0 :Slave Select Enable Flag */
#define SSIC_SER_SSIC_NUM_SLAVES_1_POS (0ul) /*!< Position of SSIC_NUM_SLAVES_1 field. */
#define SSIC_SER_SSIC_NUM_SLAVES_1_MSK (0x1ul << SSIC_SER_SSIC_NUM_SLAVES_1_POS) /*!< Bit mask of SSIC_NUM_SLAVES_1 field. */


/* Register: BAUDR */
/* Description: Baud Rate Select */

/*bit 0-15 :SSI Clock Divider*/
#define SSIC_BAUDR_SCKDV_POS (0ul) /*!< Position of SCKDV field. */
#define SSIC_BAUDR_SCKDV_MSK (0xfffful << SSIC_BAUDR_SCKDV_POS) /*!< Bit mask of SCKDV field. */





/* Register: SR */
/* Description: Status Register */

/*bit 0 :Slave Select Enable Flag */
#define SSIC_SR_BUSY_POS (0ul) /*!< Position of BUSY field. */
#define SSIC_SR_BUSY_MSK (0x1ul << SSIC_SR_BUSY_POS) /*!< Bit mask of BUSY field. */

/*bit 1 :Transmit FIFO Not Full */
#define SSIC_SR_TFNF_POS (1ul) /*!< Position of TFNF field. */
#define SSIC_SR_TFNF_MSK (0x1ul << SSIC_SR_TFNF_POS) /*!< Bit mask of TFNF field. */

/*bit 2 :Transmit FIFO Empty */
#define SSIC_SR_TFE_POS (2ul) /*!< Position of TFE field. */
#define SSIC_SR_TFE_MSK (0x1ul << SSIC_SR_TFE_POS) /*!< Bit mask of TFE field. */

/*bit 3 :Receive FIFO Not Empty*/
#define SSIC_SR_RFNE_POS (3ul) /*!< Position of RFNE field. */
#define SSIC_SR_RFNE_MSK (0x1ul << SSIC_SR_RFNE_POS) /*!< Bit mask of RFNE field. */

/*bit 4 :Receive FIFO Full */
#define SSIC_SR_RFF_POS (4ul) /*!< Position of RFF field. */
#define SSIC_SR_RFF_MSK (0x1ul << SSIC_SR_RFF_POS) /*!< Bit mask of RFF field. */

/*bit 5 :Transmission Error */
#define SSIC_SR_TXE_POS (5ul) /*!< Position of TXE field. */
#define SSIC_SR_TXE_MSK (0x1ul << SSIC_SR_TXE_POS) /*!< Bit mask of TXE field. */

/*bit 6 :Data Collision Error*/
#define SSIC_SR_DCOL_POS (6ul) /*!< Position of DCOL field. */
#define SSIC_SR_DCOL_MSK (0x1ul << SSIC_SR_DCOL_POS) /*!< Bit mask of DCOL field. */





/* Register: IMR */
/* Description:  Interrupt Mask Register */

/*bit 0 :Transmit FIFO Empty Interrupt Mask */
#define SSIC_IMR_TXEIM_POS (0ul) /*!< Position of TXEIM field. */
#define SSIC_IMR_TXEIM_MSK (0x1ul << SSIC_IMR_TXEIM_POS) /*!< Bit mask of TXEIM field. */

/*bit 1 :Transmit FIFO Overflow Interrupt Mask */
#define SSIC_IMR_TXOIM_POS (1ul) /*!< Position of TXOIM field. */
#define SSIC_IMR_TXOIM_MSK (0x1ul << SSIC_IMR_TXOIM_POS) /*!< Bit mask of TXOIM field. */

/*bit 2 :Receive FIFO Underflow Interrupt Mask*/
#define SSIC_IMR_RXUIM_POS (2ul) /*!< Position of RXUIM field. */
#define SSIC_IMR_RXUIM_MSK (0x1ul << SSIC_IMR_RXUIM_POS) /*!< Bit mask of RXUIM field. */

/*bit 3 :Receive FIFO Overflow Interrupt Mask*/
#define SSIC_IMR_RXOIM_POS (3ul) /*!< Position of RXOIM field. */
#define SSIC_IMR_RXOIM_MSK (0x1ul << SSIC_IMR_RXOIM_POS) /*!< Bit mask of RXOIM field. */

/*bit 4 : Receive FIFO Full Interrupt Mask */
#define SSIC_IMR_RXFIM_POS (4ul) /*!< Position of RXFIM field. */
#define SSIC_IMR_RXFIM_MSK (0x1ul << SSIC_IMR_RXFIM_POS) /*!< Bit mask of RXFIM field. */

/*bit 5 :Multi-Master Contention Interrupt Mask */
#define SSIC_IMR_MSTIM_POS (5ul) /*!< XIP Receive FIFO Overflow Interrupt Mask. */
#define SSIC_IMR_MSTIM_MSK (0x1ul << SSIC_IMR_MSTIM_POS) /*!< Bit mask of MSTIM field. */

/*bit 6 :Multi-Master Contention Interrupt Mask */
#define SSIC_IMR_XRXOIM_POS (6ul) /*!< Position of XRXOIM field. */
#define SSIC_IMR_XRXOIM_MSK (0x1ul << SSIC_IMR_XRXOIM_POS) /*!< Bit mask of XRXOIM field. */



/* Register: ISR */
/* Description:  Interrupt Status Register */

/*bit 0 :Transmit FIFO Empty Interrupt Status */
#define SSIC_ISR_TXEIS_POS (0ul) /*!< Position of TXEIS field. */
#define SSIC_ISR_TXEIS_MSK (0x1ul << SSIC_ISR_TXEIS_POS) /*!< Bit mask of TXEIS field. */

/*bit 1 :Transmit FIFO Overflow Interrupt Status */
#define SSIC_ISR_TXOIS_POS (1ul) /*!< Position of TXOIS field. */
#define SSIC_ISR_TXOIS_MSK (0x1ul << SSIC_ISR_TXOIS_POS) /*!< Bit mask of TXOIS field. */

/*bit 2 :Receive FIFO Underflow Interrupt Status*/
#define SSIC_ISR_RXUIS_POS (2ul) /*!< Position of RXUIS field. */
#define SSIC_ISR_RXUIS_MSK (0x1ul << SSIC_ISR_RXUIS_POS) /*!< Bit mask of RXUIS field. */

/*bit 3 :Receive FIFO Overflow Interrupt Status*/
#define SSIC_ISR_RXOIS_POS (3ul) /*!< Position of RXOIS field. */
#define SSIC_ISR_RXOIS_MSK (0x1ul << SSIC_ISR_RXOIS_POS) /*!< Bit mask of RXOIS field. */

/*bit 4 : Receive FIFO Full Interrupt Status */
#define SSIC_ISR_RXFIS_POS (4ul) /*!< Position of RXFIS field. */
#define SSIC_ISR_RXFIS_MSK (0x1ul << SSIC_ISR_RXFIS_POS) /*!< Bit mask of RXFIS field. */

/*bit 5 :Multi-Master Contention Interrupt Status */
#define SSIC_ISR_MSTIS_POS (5ul) /*!< Position of MSTIS field. */
#define SSIC_ISR_MSTIS_MSK (0x1ul << SSIC_ISR_MSTIS_POS) /*!< Bit mask of MSTIS field. */

/*bit 6 :Multi-Master Contention Interrupt Status */
#define SSIC_IMR_XRXOIS_POS (6ul) /*!< Position of XRXOIS field. */
#define SSIC_IMR_XRXOIS_MSK (0x1ul << SSIC_IMR_XRXOIS_POS) /*!< Bit mask of XRXOIS field. */




/* Register: RISR */
/* Description: Raw Interrupt Status Register */

/*bit 0 :Transmit FIFO Empty Raw Interrupt Status */
#define SSIC_ISR_TXEIR_POS (0ul) /*!< Position of TXEIR field. */
#define SSIC_ISR_TXEIR_MSK (0x1ul << SSIC_ISR_TXEIR_POS) /*!< Bit mask of TXEIR field. */

/*bit 1 :Transmit FIFO Overflow Raw Interrupt Status */
#define SSIC_ISR_TXOIR_POS (1ul) /*!< Position of TXOIR field. */
#define SSIC_ISR_TXOIR_MSK (0x1ul << SSIC_ISR_TXOIR_POS) /*!< Bit mask of TXOIR field. */

/*bit 2 :Receive FIFO Underflow Raw Interrupt Status*/
#define SSIC_ISR_RXUIR_POS (2ul) /*!< Position of RXUIR field. */
#define SSIC_ISR_RXUIR_MSK (0x1ul << SSIC_ISR_RXUIR_POS) /*!< Bit mask of RXUIR field. */

/*bit 3 :Receive FIFO Overflow Raw Interrupt Status*/
#define SSIC_ISR_RXOIR_POS (3ul) /*!< Position of RXOIR field. */
#define SSIC_ISR_RXOIR_MSK (0x1ul << SSIC_ISR_RXOIR_POS) /*!< Bit mask of RXOIR field. */

/*bit 4 : Receive FIFO Full Raw Interrupt Status */
#define SSIC_ISR_RXFIR_POS (4ul) /*!< Position of RXFIR field. */
#define SSIC_ISR_RXFIR_MSK (0x1ul << SSIC_ISR_RXFIR_POS) /*!< Bit mask of RXFIR field. */

/*bit 5 :Multi-Master Contention Raw Interrupt Status */
#define SSIC_ISR_MSTIR_POS (5ul) /*!< Position of MSTIR field. */
#define SSIC_ISR_MSTIR_MSK (0x1ul << SSIC_ISR_MSTIR_POS) /*!< Bit mask of MSTIR field. */

/*bit 6 :Multi-Master Contention Raw  Interrupt Status */
#define SSIC_IMR_XRXOIR_POS (6ul) /*!< Position of XRXOIR field. */
#define SSIC_IMR_XRXOIR_MSK (0x1ul << SSIC_IMR_XRXOIR_POS) /*!< Bit mask of XRXOIR field. */


/* Register: DMACR */
/* Description: DMA Control Register*/

/*bit 0 :Receive DMA Enable */
#define SSIC_DMACR_RDMAE_POS (0ul) /*!< Position of RDMAE field. */
#define SSIC_DMACR_RDMAE_MSK (0x1ul << SSIC_DMACR_RDMAE_POS) /*!< Bit mask of RDMAE field. */

/*bit 1 :Transmit DMA Enable */
#define SSIC_DMACR_TDMAE_POS (1ul) /*!< Position of TDMAE field. */
#define SSIC_DMACR_TDMAE_MSK (0x1ul << SSIC_DMACR_TDMAE_POS) /*!< Bit mask of TDMAE field. */


/* Register: RX_SAMPLE_DELAY  */
/* Description:  RX Sample Delay Register */

/*bit 0-7 : Receive Data (rxd) Sample Delay. */
#define SSIC_RX_SAMPLE_DELAY_RSD_POS (0ul) /*!< Position of RSD field. */
#define SSIC_RX_SAMPLE_DELAY_RSD_MSK (0xFFul << SSIC_RX_SAMPLE_DELAY_RSD_POS) /*!< Bit mask of RSD field. */

/*bit 16 : Receive Data (rxd) Sampling Edge . */
#define SSIC_RX_SAMPLE_DELAY_SE_POS (16ul) /*!< Position of SE field. */
#define SSIC_RX_SAMPLE_DELAY_SE_MSK (0x1ul << SSIC_RX_SAMPLE_DELAY_SE_POS) /*!< Bit mask of SE field. */


/* Register: SPI_CTRLR0 */
/* Description: SPI Control Register*/

/*bit 0-1 : Address and instruction transfer format. */
#define SSIC_SPI_CTRLR0_TRANS_TYPE_POS (0ul) /*!< Position of TRANS_TYPE field. */
#define SSIC_SPI_CTRLR0_TRANS_TYPE_MSK (0x3ul << SSIC_SPI_CTRLR0_TRANS_TYPE_POS) /*!< Bit mask of TRANS_TYPE field. */

/*bit 2-5 : This bit defines length of address to be transmitted. */
#define SSIC_SPI_CTRLR0_ADDR_L_POS (2ul) /*!< Position of ADDR_L field. */
#define SSIC_SPI_CTRLR0_ADDR_L_MSK (0xFul << SSIC_SPI_CTRLR0_ADDR_L_POS) /*!< Bit mask of ADDR_L field. */

/*bit 7 : This bit defines length of address to be transmitted. */
#define SSIC_SPI_CTRLR0_XIP_MD_BIT_EN_POS (7ul) /*!< Position of XIP_MD_BIT_EN field. */
#define SSIC_SPI_CTRLR0_XIP_MD_BIT_EN_MSK (0x1ul << SSIC_SPI_CTRLR0_XIP_MD_BIT_EN_POS) /*!< Bit mask of XIP_MD_BIT_EN field. */

/*bit 8-9 : Dual/Quad mode instruction length in bits. */
#define SSIC_SPI_CTRLR0_INST_L_POS (8ul) /*!< Position of INST_L field. */
#define SSIC_SPI_CTRLR0_INST_L_MSK (0x3ul << SSIC_SPI_CTRLR0_INST_L_POS) /*!< Bit mask of INST_L field. */

/*bit 11-15 : This bit defines the wait cycles in dual/quad mode between control frames transmit and data reception. */
#define SSIC_SPI_CTRLR0_WAIT_CYCLES_POS (11ul) /*!< Position of WAIT_CYCLES field. */
#define SSIC_SPI_CTRLR0_WAIT_CYCLES_MSK (0x3Ful << SSIC_SPI_CTRLR0_WAIT_CYCLES_POS) /*!< Bit mask of WAIT_CYCLES field. */

/*bit 16 : SPI DDR Enable bit. */
#define SSIC_SPI_CTRLR0_SPI_DDR_EN_POS (16ul) /*!< Position of SPI_DDR_EN field. */
#define SSIC_SPI_CTRLR0_SPI_DDR_EN_MSK (0x1ul << SSIC_SPI_CTRLR0_SPI_DDR_EN_POS) /*!< Bit mask of SPI_DDR_EN field. */

/*bit 17 : Instruction DDR Enable bit. */
#define SSIC_SPI_CTRLR0_INST_DDR_EN_POS (17ul) /*!< Position of INST_DDR_EN field. */
#define SSIC_SPI_CTRLR0_INST_DDR_EN_MSK (0x1ul << SSIC_SPI_CTRLR0_INST_DDR_EN_POS) /*!< Bit mask of INST_DDR_EN field. */

/*bit 18 : Read data strobe enable bit. */
#define SSIC_SPI_CTRLR0_SPI_RXDS_EN_POS (18ul) /*!< Position of SPI_RXDS_EN field. */
#define SSIC_SPI_CTRLR0_SPI_RXDS_EN_MSK (0x1ul << SSIC_SPI_CTRLR0_SPI_RXDS_EN_POS) /*!< Bit mask of SPI_RXDS_EN field. */

/*bit 19 : Fix DFS for XIP transfers. */
#define SSIC_SPI_CTRLR0_XIP_DFS_HC_POS (19ul) /*!< Position of XIP_DFS_HC field. */
#define SSIC_SPI_CTRLR0_XIP_DFS_HC_MSK (0x1ul << SSIC_SPI_CTRLR0_XIP_DFS_HC_POS) /*!< Bit mask of XIP_DFS_HC field. */

/*bit 20 : XIP instruction enable bit. */
#define SSIC_SPI_CTRLR0_XIP_INST_EN_POS (20ul) /*!< Position of XIP_INST_EN field. */
#define SSIC_SPI_CTRLR0_XIP_INST_EN_MSK (0x1ul << SSIC_SPI_CTRLR0_XIP_INST_EN_POS) /*!< Bit mask of XIP_INST_EN field. */

/*bit 21 : Enable continuous transfer in XIP mode. */
#define SSIC_SPI_CTRLR0_SSIC_XIP_CONT_XFER_EN_POS (21ul) /*!< Position of DWCSSIC_XIP_CONT_XFER_EN field. */
#define SSIC_SPI_CTRLR0_SSIC_XIP_CONT_XFER_EN_MSK (0x1ul << SSIC_SPI_CTRLR0_SSIC_XIP_CONT_XFER_EN_POS) /*!< Bit mask of DWCSSIC_XIP_CONT_XFER_EN field. */

/*bit 24 : SPI data mask enable bit. */
#define SSIC_SPI_CTRLR0_SPI_DM_EN_POS (24ul) /*!< Position of SPI_DM_EN field. */
#define SSIC_SPI_CTRLR0_SPI_DM_EN_MSK (0x1ul << SSIC_SPI_CTRLR0_SPI_DM_EN_POS) /*!< Bit mask of SPI_DM_EN field. */

/*bit 25 : SPI DDR Enable bit. */
#define SSIC_SPI_CTRLR0_SPI_RXDS_SIG_EN_POS (25ul) /*!< Position of SPI_RXDS_SIG_EN field. */
#define SSIC_SPI_CTRLR0_SPI_RXDS_SIG_EN_MSK (0x1ul << SSIC_SPI_CTRLR0_SPI_RXDS_SIG_EN_POS) /*!< Bit mask of SPI_RXDS_SIG_EN field. */

/*bit 26 - 27 : XIP Mode bits length. */
#define SSIC_SPI_CTRLR0_XIP_MBL_POS (26ul) /*!< Position of XIP_MBL field. */
#define SSIC_SPI_CTRLR0_XIP_MBL_MSK (0x1ul << SSIC_SPI_CTRLR0_XIP_MBL_POS) /*!< Bit mask of XIP_MBL field. */

/*bit 28 : XIP Mode bits length. */
//#define SSIC_SPI_CTRLR0_SPI_DDR_EN_POS (28ul) /*!< Position of SPI_DDR_EN field. */
//#define SSIC_SPI_CTRLR0_SPI_DDR_EN_MSK (0x1ul << SSIC_SPI_CTRLR0_SPI_DDR_EN_POS) /*!< Bit mask of SPI_DDR_EN field. */

/*bit 29 : Enables XIP pre-fetch functionality in DWC_ssi. */
#define SSIC_SPI_CTRLR0_XIP_PREFETCH_EN_POS (29ul) /*!< Position of XIP_PREFETCH_EN field. */
#define SSIC_SPI_CTRLR0_XIP_PREFETCH_EN_MSK (0x1ul << SSIC_SPI_CTRLR0_XIP_PREFETCH_EN_POS) /*!< Bit mask of XIP_PREFETCH_EN field. */

/*bit 30 : Enables clock stretching capability in SPI transfers. */
#define SSIC_SPI_CTRLR0_CLK_STRETCH_EN_POS (30ul) /*!< Position of CLK_STRETCH_EN field. */
#define SSIC_SPI_CTRLR0_CLK_STRETCH_EN_MSK (0x1ul << SSIC_SPI_CTRLR0_CLK_STRETCH_EN_POS) /*!< Bit mask of CLK_STRETCH_EN field. */


/* Register: DDR_DRIVE_EDGE  */
/* Description:  DDR_DRIVE_EDGE - Transmit Drive Edge Register*/

/*bit 0-7 :TXD Drive edge register which decided the driving edge of transmit data.. */
#define SSIC_DDR_DRIVE_EDGE_TDE_POS (0ul) /*!< Position of TDE field. */
#define SSIC_DDR_DRIVE_EDGE_TDE_MSK (0xFFul << SSIC_DDR_DRIVE_EDGE_TDE_POS) /*!< Bit mask of TDE field. */


/* Register: XIP_MODE_BITS  */
/* Description:  eXecute in Place - Mode bits*/

/*bit 0-15 :XIP_MD_BITS. */
#define SSIC_XIP_MODE_BITS_XIP_MD_BITS_POS (0ul) /*!< Position of XIP_MD_BITS field. */
#define SSIC_XIP_MODE_BITS_XIP_MD_BITS_MSK (0xFFFFul << SSIC_XIP_MODE_BITS_XIP_MD_BITS_POS) /*!< Bit mask of XIP_MD_BITS field. */



/* Register: XIP_INCR_INST  */
/* Description:  XIP_INCR_INST - XIP INCR transfer opcode*/

/*bit 0-15 :XIP INCR transfer opcode. */
#define SSIC_XIP_INCR_INST_INCR_INST_POS (0ul) /*!< Position of INCR_INST field. */
#define SSIC_XIP_INCR_INST_INCR_INST_MSK (0xFFFFul << SSIC_XIP_INCR_INST_INCR_INST_POS) /*!< Bit mask of INCR_INST field. */

/* Register: XIP_WRAP_INST  */
/* Description:  XIP_INCR_INST - XIP INCR transfer opcode*/

/*bit 0-15 :XIP_WRAP_INST - XIP WRAP transfer opcode. */
#define SSIC_XIP_WRAP_INST_POS (0ul) /*!< Position of WRAP_INST field. */
#define SSIC_XIP_WRAP_INST_MSK (0xFFFFul << SSIC_XIP_WRAP_INST_POS) /*!< Bit mask of WRAP_INST field. */

/* Register: XIP_CTRL  */
/* Description:  XIP_CTRL - XIP Control Register*/

/*bit 0-1 :SPI Frame Format. */
#define SSIC_XIP_CTRL_FRF_POS (0ul) /*!< Position of FRF field. */
#define SSIC_XIP_CTRL_FRF_MSK (0x3ul << SSIC_XIP_CTRL_FRF_POS) /*!< Bit mask of FRF field. */

/*bit 2-3 :Address and instruction transfer format. */
#define SSIC_XIP_CTRL_TRANS_TYPE_POS (2ul) /*!< Position of TRANS_TYPE field. */
#define SSIC_XIP_CTRL_TRANS_TYPE_MSK (0x3ul << SSIC_XIP_CTRL_TRANS_TYPE_POS) /*!< Bit mask of TRANS_TYPE field. */

/*bit 4-7 :This bit defines Length of Address to be transmitted. */
#define SSIC_XIP_CTRL_ADDR_L_POS (4ul) /*!< Position of ADDR_L field. */
#define SSIC_XIP_CTRL_ADDR_L_MSK (0xful << SSIC_XIP_CTRL_ADDR_L_POS) /*!< Bit mask of ADDR_L field. */

/*bit 9-10 :Dual/Quad/Octal mode instruction length in bits.. */
#define SSIC_XIP_CTRL_INST_L_POS (9ul) /*!< Position of INST_L field. */
#define SSIC_XIP_CTRL_INST_L_MSK (0x3ul << SSIC_XIP_CTRL_INST_L_POS) /*!< Bit mask of INST_L field. */

/*bit 12 :Mode bits enable in XIP mode. */
#define SSIC_XIP_CTRL_MD_BITS_EN_POS (12ul) /*!< Position of MD_BITS_EN field. */
#define SSIC_XIP_CTRL_MD_BITS_EN_MSK (0x1ul << SSIC_XIP_CTRL_MD_BITS_EN_POS) /*!< Bit mask of MD_BITS_EN field. */

/*bit 13-17 :Dual/Quad/Octal mode instruction length in bits.. */
#define SSIC_XIP_CTRL_WAIT_CYCLES_POS (13ul) /*!< Position of WAIT_CYCLES field. */
#define SSIC_XIP_CTRL_WAIT_CYCLES_MSK (0x3Ful << SSIC_XIP_CTRL_WAIT_CYCLES_POS) /*!< Bit mask of WAIT_CYCLES field. */

/*bit 18 : Fix DFS for XIP transfers. */
#define SSIC_XIP_CTRL_DFS_HC_POS (18ul) /*!< Position of DFS_HCfield. */
#define SSIC_XIP_CTRL_DFS_HC_MSK (0x1ul << SSIC_XIP_CTRL_DFS_HC_POS) /*!< Bit mask of DFS_HC field. */

/*bit 19 : SPI DDR Enable bit. */
#define SSIC_XIP_CTRL_DDR_EN_POS (19ul) /*!< Position of DDR_EN field. */
#define SSIC_XIP_CTRL_DDR_EN_MSK (0x1ul << SSIC_XIP_CTRL_DDR_EN_POS) /*!< Bit mask of DDR_EN field. */

/*bit 20 : Instruction DDR Enable bit. */
#define SSIC_XIP_CTRL_INST_DDR_EN_POS (20ul) /*!< Position of INST_DDR_EN field. */
#define SSIC_XIP_CTRL_INST_DDR_EN_MSK (0x1ul << SSIC_XIP_CTRL_INST_DDR_EN_POS) /*!< Bit mask of INST_DDR_EN field. */

/*bit 21 : Read data strobe enable bit. */
#define SSIC_XIP_CTRL_RXDS_EN_POS (21ul) /*!< Position of RXDS_EN field. */
#define SSIC_XIP_CTRL_RXDS_EN_MSK (0x1ul << SSIC_XIP_CTRL_RXDS_EN_POS) /*!< Bit mask of RXDS_EN field. */

/*bit 22 : XIP instruction enable bit. If this bit is set to 1 then XIP transfers will also have instruction phase. */
#define SSIC_XIP_CTRL_INST_EN_POS (22ul) /*!< Position of  INST_EN field. */
#define SSIC_XIP_CTRL_INST_EN_MSK (0x1ul << SSIC_XIP_CTRL_INST_EN_POS) /*!< Bit mask of  INST_EN field. */

/*bit 23 :Enable continuous transfer in XIP mode. */
#define SSIC_XIP_CTRL_CONT_XFER_EN_POS (23ul) /*!< Position of CONT_XFER_EN field. */
#define SSIC_XIP_CTRL_CONT_XFER_EN_MSK (0x1ul << SSIC_XIP_CTRL_CONT_XFER_EN_POS) /*!< Bit mask of CONT_XFER_EN field. */

/*bit 24 :SPI Hyperbus Frame format enable for XIP transfers. */
#define SSIC_XIP_CTRL_XIP_HYPERBUS_EN_POS (24ul) /*!< Position of XIP_HYPERBUS_EN field. */
#define SSIC_XIP_CTRL_XIP_HYPERBUS_EN_MSK (0x1ul << SSIC_XIP_CTRL_XIP_HYPERBUS_EN_POS) /*!< Bit mask of XIP_HYPERBUS_EN field. */

/*bit 25 : Enable rxds signaling during address and command phase of Hypebus transfer */
#define SSIC_XIP_CTRL_RXDS_SIG_EN_POS (25ul) /*!< Position of RXDS_SIG_EN field. */
#define SSIC_XIP_CTRL_RXDS_SIG_EN_MSK (0x1ul << SSIC_XIP_CTRL_RXDS_SIG_EN_POS) /*!< Bit mask of RXDS_SIG_EN field. */

/*bit 26-27 :XIP Mode bits length  */
#define SSIC_XIP_CTRL_XIP_MB_POS (26ul) /*!< Position of XIP_MB field. */
#define SSIC_XIP_CTRL_XIP_MB_MSK (0x3ul << SSIC_XIP_CTRL_XIP_MB_POS) /*!< Bit mask of XIP_MB field. */

/*bit 28 : Fix DFS for XIP transfers. */
//#define SSIC_XIP_CTRL_DFS_HC_POS (28ul) /*!< Position of DFS_HCfield. */
//#define SSIC_XIP_CTRL_DFS_HC_MSK (0x1ul << SSIC_XIP_CTRL_DFS_HC_POS) /*!< Bit mask of DFS_HC field. */

/*bit 29 :Enables XIP pre-fetch functionality in DWC_ssi. . */
#define SSIC_XIP_CTRL_XIP_PREFETCH_EN_POS (29ul) /*!< Position of XIP_PREFETCH_EN field. */
#define SSIC_XIP_CTRL_XIP_PREFETCH_EN_MSK (0x1ul << SSIC_XIP_CTRL_XIP_PREFETCH_EN_POS) /*!< Bit mask of XIP_PREFETCH_EN field. */


/* Register: XIP_SER  */
/* Description:  Slave Enable Register*/

/*bit 0 :Slave Select Enable Flag.. */
#define SSIC_XIP_SER_POS (0ul) /*!< Position of XIP_SER field. */
#define SSIC_XIP_SER_MSK (0x1ul << SSIC_XIP_SER_POS) /*!< Bit mask of XIP_SER field. */

/* Register: XRXOICR  */
/* Description:  XIP Receive FIFO Overflow Interrupt Clear Register */

/*bit 0 : Clear XIP Receive FIFO Overflow Interrupt.. */
#define SSIC_XRXOICR_XRXOICR_POS (0ul) /*!< Position of XRXOICR field. */
#define SSIC_XRXOICR_XRXOICR_MSK (0x1ul << SSIC_XRXOICR_XRXOICR_POS) /*!< Bit mask of XRXOICR field. */

/* Register: XIP_CNT_TIME_OUT  */
/* Description:  XIP time out register for continuous transfers*/

/*bit 0 : XIP time out value in terms of hclk.  */
#define SSIC_XIP_CNT_TIME_OUT_XTOC_POS (0ul) /*!< Position of XTOC field. */
#define SSIC_XIP_CNT_TIME_OUT_XTOC_MSK (0x1ul << SSIC_XIP_CNT_TIME_OUT_XTOC_POS) /*!< Bit mask of XTOC field. */

#endif /* __BT1051Axx_SSIC_IF_H__*/

