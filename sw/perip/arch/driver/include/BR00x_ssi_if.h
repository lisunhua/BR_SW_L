/*
 *++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 * Copyright (c) 1999-2018 Barrot Technology Limited
 *
 * All rights reserved.
 *
 *------------------------------------------------------------------------------
 */
/**
 * @file    BR1051Axx_ssi_if.h
 * @brief     This file provides  the ssi register parameter.
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

#ifndef __BT1051Axx_SSI_IF_H__
#define __BT1051Axx_SSI_IF_H__


/* Peripheral: SSI */
/* Description:Synchronous Serial Interface */

/* Register: CTRLR0 */
/* Description: Control Register 0*/

/*bit 0-3 :Data Frame Size*/
#define SSI_CTRLR0_DFS_POS (0ul) /*!< Position of DFS field. */
#define SSI_CTRLR0_DFS_MSK (0x0Ful << SSI_CTRLR0_DFS_POS) /*!< Bit mask of DFS field. */

/*bit 4-5 :Frame Format*/
#define SSI_CTRLR0_FRF_POS (4ul) /*!< Position of FRF field. */
#define SSI_CTRLR0_FRF_MSK (0x3ul << SSI_CTRLR0_FRF_POS) /*!< Bit mask of FRF field. */

/*bit 6 :Serial Clock Phase*/
#define SSI_CTRLR0_SCPH_POS (6ul) /*!< Position of SCPH field. */
#define SSI_CTRLR0_SCPH_MSK (0x1ul << SSI_CTRLR0_SCPH_POS) /*!< Bit mask of SCPH field. */

/*bit 7 :Serial Clock Polarity*/
#define SSI_CTRLR0_SCPOL_POS (7ul) /*!< Position of SCPOL field. */
#define SSI_CTRLR0_SCPOL_MSK (0x1ul << SSI_CTRLR0_SCPOL_POS) /*!< Bit mask of SCPOL field. */

/*bit 8-9  :Transfer Mode*/
#define SSI_CTRLR0_TMOD_POS (8ul) /*!< Position of TMOD field. */
#define SSI_CTRLR0_TMOD_MSK (0x3ul << SSI_CTRLR0_TMOD_POS) /*!< Bit mask of TMOD field. */

/*bit 10  :Slave Output Enable*/
#define SSI_CTRLR0_SLV_OE_POS (10ul) /*!< Position of SLV_OE field. */
#define SSI_CTRLR0_SLV_OE_MSK (0x1ul << SSI_CTRLR0_SLV_OE_POS) /*!< Bit mask of SLV_OE field. */

/*bit 11  :Shift Register Loop*/
#define SSI_CTRLR0_SRL_POS (11ul) /*!< Position of SRL field. */
#define SSI_CTRLR0_SRL_MSK (0x1ul << SSI_CTRLR0_SRL_POS) /*!< Bit mask of SRL field. */

/*bit 12-15  :Control Frame Size*/
#define SSI_CTRLR0_CFS_POS (12ul) /*!< Position of CFS field. */
#define SSI_CTRLR0_CFS_MSK (0xFul << SSI_CTRLR0_CFS_POS) /*!< Bit mask of CFS field. */

/*bit 16-20  :Data Frame Size in 32-bit mode*/
#define SSI_CTRLR0_DFS_32_POS (16ul) /*!< Position of DFS_32 field. */
#define SSI_CTRLR0_DFS_32_MSK (0x1Ful << SSI_CTRLR0_DFS_32_POS) /*!< Bit mask of DFS_32 field. */

/*bit 21-22  :SPI Frame Format*/
#define SSI_CTRLR0_SPI_FRF_POS (21ul) /*!< Position of SPI_FRF field. */
#define SSI_CTRLR0_SPI_FRF_MSK (0x3ul << SSI_CTRLR0_SPI_FRF_POS) /*!< Bit mask of SPI_FRF field. */

/*bit 24  :Slave Select Toggle Enable*/
#define SSI_CTRLR0_SSTE_POS (24ul) /*!< Position of SSTE field. */
#define SSI_CTRLR0_SSTE_MSK (0x1ul << SSI_CTRLR0_SSTE_POS) /*!< Bit mask of SSTE field. */



/* Register: CTRLR1 */
/* Description: Control Register 1 */

/*bit 0-15 :Data Frame Size*/
#define SSI_CTRLR1_NDF_POS (0ul) /*!< Position of NDF field. */
#define SSI_CTRLR1_NDF_MSK (0xFFFFul << SSI_CTRLR1_NDF_POS) /*!< Bit mask of NDF field. */

/* Register: SSIENR */
/* Description: SSI Enable Register */

/*bit 0 :SSI Enable*/
#define SSI_SSIENR_SSI_EN_POS (0ul) /*!< Position of SSI_EN field. */
#define SSI_SSIENR_SSI_EN_MSK (0x1ul << SSI_SSIENR_SSI_EN_POS) /*!< Bit mask of SSI_EN field. */


/* Register: MWCR */
/* Description: Microwire Control Register*/

/*bit 0 : Microwire Transfer Mode */
#define SSI_MWCR_MWMOD_POS (0ul) /*!< Position of MWMOD field. */
#define SSI_MWCR_MWMOD_MSK (0x1ul << SSI_MWCR_MWMOD_POS) /*!< Bit mask of MWMOD field. */

/*bit 1 : Microwire Control*/
#define SSI_MWCR_MDD_POS (1ul) /*!< Position of MDD field. */
#define SSI_MWCR_MDD_MSK (0x1ul << SSI_MWCR_MDD_POS) /*!< Bit mask of MDD field. */

/*bit 2 : Microwire Handshaking*/
#define SSI_MWCR_MHS_POS (2ul) /*!< Position of MHS field. */
#define SSI_MWCR_MHS_MSK (0x1ul << SSI_MWCR_MHS_POS) /*!< Bit mask of MHS field. */


/* Register: SER */
/* Description: Slave Enable Register */

/*bit 0 :Slave Select Enable Flag */
#define SSI_SER_SSI_NUM_SLAVES_1_POS (0ul) /*!< Position of SSI_NUM_SLAVES_1 field. */
#define SSI_SER_SSI_NUM_SLAVES_1_MSK (0x1ul << SSI_SER_SSI_NUM_SLAVES_1_POS) /*!< Bit mask of SSI_NUM_SLAVES_1 field. */


/* Register: BAUDR */
/* Description: Baud Rate Select */

/*bit 0-15 :SSI Clock Divider*/
#define SSI_BAUDR_SCKDV_POS (0ul) /*!< Position of SCKDV field. */
#define SSI_BAUDR_SCKDV_MSK (0xfffful << SSI_BAUDR_SCKDV_POS) /*!< Bit mask of SCKDV field. */





/* Register: SR */
/* Description: Status Register */

/*bit 0 :Slave Select Enable Flag */
#define SSI_SR_BUSY_POS (0ul) /*!< Position of BUSY field. */
#define SSI_SR_BUSY_MSK (0x1ul << SSI_SR_BUSY_POS) /*!< Bit mask of BUSY field. */

/*bit 1 :Transmit FIFO Not Full */
#define SSI_SR_TFNF_POS (1ul) /*!< Position of TFNF field. */
#define SSI_SR_TFNF_MSK (0x1ul << SSI_SR_TFNF_POS) /*!< Bit mask of TFNF field. */

/*bit 2 :Transmit FIFO Empty */
#define SSI_SR_TFE_POS (2ul) /*!< Position of TFE field. */
#define SSI_SR_TFE_MSK (0x1ul << SSI_SR_TFE_POS) /*!< Bit mask of TFE field. */

/*bit 3 :Receive FIFO Not Empty*/
#define SSI_SR_RFNE_POS (3ul) /*!< Position of RFNE field. */
#define SSI_SR_RFNE_MSK (0x1ul << SSI_SR_RFNE_POS) /*!< Bit mask of RFNE field. */

/*bit 4 :Receive FIFO Full */
#define SSI_SR_RFF_POS (4ul) /*!< Position of RFF field. */
#define SSI_SR_RFF_MSK (0x1ul << SSI_SR_RFF_POS) /*!< Bit mask of RFF field. */

/*bit 5 :Transmission Error */
#define SSI_SR_TXE_POS (5ul) /*!< Position of TXE field. */
#define SSI_SR_TXE_MSK (0x1ul << SSI_SR_TXE_POS) /*!< Bit mask of TXE field. */

/*bit 6 :Data Collision Error*/
#define SSI_SR_DCOL_POS (6ul) /*!< Position of DCOL field. */
#define SSI_SR_DCOL_MSK (0x1ul << SSI_SR_DCOL_POS) /*!< Bit mask of DCOL field. */





/* Register: IMR */
/* Description:  Interrupt Mask Register */

/*bit 0 :Transmit FIFO Empty Interrupt Mask */
#define SSI_IMR_TXEIM_POS (0ul) /*!< Position of TXEIM field. */
#define SSI_IMR_TXEIM_MSK (0x1ul << SSI_IMR_TXEIM_POS) /*!< Bit mask of TXEIM field. */

/*bit 1 :Transmit FIFO Overflow Interrupt Mask */
#define SSI_IMR_TXOIM_POS (1ul) /*!< Position of TXOIM field. */
#define SSI_IMR_TXOIM_MSK (0x1ul << SSI_IMR_TXOIM_POS) /*!< Bit mask of TXOIM field. */

/*bit 2 :Receive FIFO Underflow Interrupt Mask*/
#define SSI_IMR_RXUIM_POS (2ul) /*!< Position of RXUIM field. */
#define SSI_IMR_RXUIM_MSK (0x1ul << SSI_IMR_RXUIM_POS) /*!< Bit mask of RXUIM field. */

/*bit 3 :Receive FIFO Overflow Interrupt Mask*/
#define SSI_IMR_RXOIM_POS (3ul) /*!< Position of RXOIM field. */
#define SSI_IMR_RXOIM_MSK (0x1ul << SSI_IMR_RXOIM_POS) /*!< Bit mask of RXOIM field. */

/*bit 4 : Receive FIFO Full Interrupt Mask */
#define SSI_IMR_RXFIM_POS (4ul) /*!< Position of RXFIM field. */
#define SSI_IMR_RXFIM_MSK (0x1ul << SSI_IMR_RXFIM_POS) /*!< Bit mask of RXFIM field. */

/*bit 5 :Multi-Master Contention Interrupt Mask */
#define SSI_IMR_MSTIM_POS (5ul) /*!< Position of MSTIM field. */
#define SSI_IMR_MSTIM_MSK (0x1ul << SSI_IMR_MSTIM_POS) /*!< Bit mask of MSTIM field. */



/* Register: ISR */
/* Description:  Interrupt Status Register */

/*bit 0 :Transmit FIFO Empty Interrupt Status */
#define SSI_ISR_TXEIS_POS (0ul) /*!< Position of TXEIS field. */
#define SSI_ISR_TXEIS_MSK (0x1ul << SSI_ISR_TXEIS_POS) /*!< Bit mask of TXEIS field. */

/*bit 1 :Transmit FIFO Overflow Interrupt Status */
#define SSI_ISR_TXOIS_POS (1ul) /*!< Position of TXOIS field. */
#define SSI_ISR_TXOIS_MSK (0x1ul << SSI_ISR_TXOIS_POS) /*!< Bit mask of TXOIS field. */

/*bit 2 :Receive FIFO Underflow Interrupt Status*/
#define SSI_ISR_RXUIS_POS (2ul) /*!< Position of RXUIS field. */
#define SSI_ISR_RXUIS_MSK (0x1ul << SSI_ISR_RXUIS_POS) /*!< Bit mask of RXUIS field. */

/*bit 3 :Receive FIFO Overflow Interrupt Status*/
#define SSI_ISR_RXOIS_POS (3ul) /*!< Position of RXOIS field. */
#define SSI_ISR_RXOIS_MSK (0x1ul << SSI_ISR_RXOIS_POS) /*!< Bit mask of RXOIS field. */

/*bit 4 : Receive FIFO Full Interrupt Status */
#define SSI_ISR_RXFIS_POS (4ul) /*!< Position of RXFIS field. */
#define SSI_ISR_RXFIS_MSK (0x1ul << SSI_ISR_RXFIS_POS) /*!< Bit mask of RXFIS field. */

/*bit 5 :Multi-Master Contention Interrupt Status */
#define SSI_ISR_MSTIS_POS (5ul) /*!< Position of MSTIS field. */
#define SSI_ISR_MSTIS_MSK (0x1ul << SSI_ISR_MSTIS_POS) /*!< Bit mask of MSTIS field. */


/* Register: RISR */
/* Description: Raw Interrupt Status Register */

/*bit 0 :Transmit FIFO Empty Raw Interrupt Status */
#define SSI_ISR_TXEIR_POS (0ul) /*!< Position of TXEIR field. */
#define SSI_ISR_TXEIR_MSK (0x1ul << SSI_ISR_TXEIR_POS) /*!< Bit mask of TXEIR field. */

/*bit 1 :Transmit FIFO Overflow Raw Interrupt Status */
#define SSI_ISR_TXOIR_POS (1ul) /*!< Position of TXOIR field. */
#define SSI_ISR_TXOIR_MSK (0x1ul << SSI_ISR_TXOIR_POS) /*!< Bit mask of TXOIR field. */

/*bit 2 :Receive FIFO Underflow Raw Interrupt Status*/
#define SSI_ISR_RXUIR_POS (2ul) /*!< Position of RXUIR field. */
#define SSI_ISR_RXUIR_MSK (0x1ul << SSI_ISR_RXUIR_POS) /*!< Bit mask of RXUIR field. */

/*bit 3 :Receive FIFO Overflow Raw Interrupt Status*/
#define SSI_ISR_RXOIR_POS (3ul) /*!< Position of RXOIR field. */
#define SSI_ISR_RXOIR_MSK (0x1ul << SSI_ISR_RXOIR_POS) /*!< Bit mask of RXOIR field. */

/*bit 4 : Receive FIFO Full Raw Interrupt Status */
#define SSI_ISR_RXFIR_POS (4ul) /*!< Position of RXFIR field. */
#define SSI_ISR_RXFIR_MSK (0x1ul << SSI_ISR_RXFIR_POS) /*!< Bit mask of RXFIR field. */

/*bit 5 :Multi-Master Contention Raw Interrupt Status */
#define SSI_ISR_MSTIR_POS (5ul) /*!< Position of MSTIR field. */
#define SSI_ISR_MSTIR_MSK (0x1ul << SSI_ISR_MSTIR_POS) /*!< Bit mask of MSTIR field. */


/* Register: DMACR */
/* Description: DMA Control Register*/

/*bit 0 :Receive DMA Enable */
#define SSI_DMACR_RDMAE_POS (0ul) /*!< Position of RDMAE field. */
#define SSI_DMACR_RDMAE_MSK (0x1ul << SSI_DMACR_RDMAE_POS) /*!< Bit mask of RDMAE field. */

/*bit 1 :Transmit DMA Enable */
#define SSI_DMACR_TDMAE_POS (1ul) /*!< Position of TDMAE field. */
#define SSI_DMACR_TDMAE_MSK (0x1ul << SSI_DMACR_TDMAE_POS) /*!< Bit mask of TDMAE field. */



/* Register: SPI_CTRLR0 */
/* Description: SPI Control Register*/

/*bit 0-1 : Address and instruction transfer format. */
#define SSI_SPI_CTRLR0_TRANS_TYPE_POS (0ul) /*!< Position of TRANS_TYPE field. */
#define SSI_SPI_CTRLR0_TRANS_TYPE_MSK (0x3ul << SSI_SPI_CTRLR0_TRANS_TYPE_POS) /*!< Bit mask of TRANS_TYPE field. */

/*bit 2-5 : This bit defines length of address to be transmitted. */
#define SSI_SPI_CTRLR0_ADDR_L_POS (2ul) /*!< Position of ADDR_L field. */
#define SSI_SPI_CTRLR0_ADDR_L_MSK (0xFul << SSI_SPI_CTRLR0_ADDR_L_POS) /*!< Bit mask of ADDR_L field. */

/*bit 8-9 : Dual/Quad mode instruction length in bits. */
#define SSI_SPI_CTRLR0_INST_L_POS (8ul) /*!< Position of INST_L field. */
#define SSI_SPI_CTRLR0_INST_L_MSK (0x3ul << SSI_SPI_CTRLR0_INST_L_POS) /*!< Bit mask of INST_L field. */

/*bit 11-14 : This bit defines the wait cycles in dual/quad mode between control frames transmit and data reception. */
#define SSI_SPI_CTRLR0_WAIT_CYCLES_POS (11ul) /*!< Position of WAIT_CYCLES field. */
#define SSI_SPI_CTRLR0_WAIT_CYCLES_MSK (0xFul << SSI_SPI_CTRLR0_WAIT_CYCLES_POS) /*!< Bit mask of WAIT_CYCLES field. */







#endif /* __BT1051Axx_SSI_IF_H__*/


