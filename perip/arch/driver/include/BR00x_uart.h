/*
 *++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 * Copyright (c) 1999-2018 Barrot Technology Limited
 *
 * All rights reserved.
 *
 *------------------------------------------------------------------------------
 */
/**
 * @file    BR00x_uart.h
 * @brief    This file provides all the UART firmware functions.
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

#ifndef __BR00x_UART_H__
#define __BR00x_UART_H__

#include "BR00x_config.h"

/*
 * Define the bit mean for LSR
 */
#define UART_LSR_BIT_ADDR_REVD    (1 << 8)  /*!< Address Received bit
                                                If 9-bit data mode (LCR_EXT[0]=1) is enabled, this bit is used to indicate that the 9th bit of
                                                the receive data is set to 1. This bit can also be used to indicate whether the incoming
                                                character is an address or data.
                                                ¦ 1 - Indicates that the character is an address.
                                                ¦ 0 - Indicates that the character is data.
                                                In the FIFO mode, since the 9th bit is associated with the received character, it is revealed
                                                when the character with the 9th bit set to 1 is at the top of the FIFO list. Reading the LSR
                                                clears the 9th bit.
                                                NOTE: You must ensure that an interrupt gets cleared (reading LSR register) before the
                                                next address byte arrives. If there is a delay in clearing the interrupt, then software will not
                                                be able to distinguish between multiple address related interrupt. */
#define UART_LSR_BIT_RFE          (1 << 7)  /*!< Receiver FIFO Error bit. This bit is only relevant when FIFO_MODE != NONE AND FIFOs
                                                are enabled (FCR[0] set to 1). This is used to indicate if there is at least one parity error,
                                                framing error, or break indication in the FIFO.
                                                ¦ 0 – no error in RX FIFO
                                                ¦ 1 – error in RX FIFO
                                                This bit is cleared when the LSR is read and the character with the error is at the top of the
                                                receiver FIFO and there are no subsequent errors in the FIFO. */
#define UART_LSR_BIT_TEMT         (1 << 6)  /*!< Transmitter Empty bit. If in FIFO mode (FIFO_MODE != NONE) and FIFOs enabled
                                                (FCR[0] set to 1), this bit is set whenever the Transmitter Shift Register and the FIFO are
                                                both empty. If in non-FIFO mode or FIFOs are disabled, this bit is set whenever the
                                                Transmitter Holding Register and the Transmitter Shift Register are both empty. */
#define UART_LSR_BIT_THRE         (1 << 5)  /*!< Transmit Holding Register Empty bit. If THRE_MODE_USER = Disabled or THRE mode
                                                is disabled (IER[7] set to 0) and regardless of FIFO's being implemented/enabled or not,
                                                this bit indicates that the THR or TX FIFO is empty.
                                                This bit is set whenever data is transferred from the THR or TX FIFO to the transmitter
                                                shift register and no new data has been written to the THR or TX FIFO. This also causes
                                                a THRE Interrupt to occur, if the THRE Interrupt is enabled. If THRE_MODE_USER =
                                                Enabled AND FIFO_MODE != NONE and both modes are active (IER[7] set to 1 and
                                                FCR[0] set to 1 respectively), the functionality is switched to indicate the transmitter FIFO
                                                is full, and no longer controls THRE interrupts, which are then controlled by the FCR[5:4]
                                                threshold setting. */
#define UART_LSR_BIT_BI           (1 << 4)  /*!< Break Interrupt bit. This is used to indicate the detection of a break sequence on the serial
                                                input data.
                                                If in UART mode (SIR_MODE = Disabled), it is set whenever the serial input, sin, is held in
                                                a logic '0' state for longer than the sum of start time + data bits + parity + stop bits.
                                                If in infrared mode (SIR_MODE = Enabled), it is set whenever the serial input, sir_in, is
                                                continuously pulsed to logic '0' for longer than the sum of start time + data bits + parity +
                                                stop bits. A break condition on serial input causes one and only one character, consisting
                                                of all 0s, to be received by the UART.
                                                In FIFO mode, the character associated with the break condition is carried through the
                                                FIFO and is revealed when the character is at the top of the FIFO. Reading the LSR clears
                                                the BI bit. In non-FIFO mode, the BI indication occurs immediately and persists until the
                                                LSR is read.
                                                NOTE: If a FIFO is full when a break condition is received, a FIFO overrun occurs. The
                                                break condition and all the information associated with it—parity and framing errors—is
                                                discarded; any information that a break character was received is lost. */
#define UART_LSR_BIT_FE           (1 << 3)  /*!< Framing Error bit. This is used to indicate the occurrence of a framing error in the receiver.
                                                A framing error occurs when the receiver does not detect a valid STOP bit in the received
                                                data.
                                                In the FIFO mode, since the framing error is associated with a character received, it is
                                                revealed when the character with the framing error is at the top of the FIFO. When a
                                                framing error occurs, the UART tries to resynchronize. It does this by assuming
                                                that the error was due to the start bit of the next character and then continues receiving
                                                the other bit; that is, data, and/or parity and stop.
                                                It should be noted that the Framing Error (FE) bit (LSR[3]) is set if a break interrupt has
                                                occurred, as indicated by Break Interrupt (BI) bit (LSR[4]). This happens because the
                                                break character implicitly generates a framing error by holding the sin input to logic 0 for
                                                longer than the duration of a character.
                                                ¦ 0 – no framing error
                                                ¦ 1 – framing error
                                                Reading the LSR clears the FE bit. */
#define UART_LSR_BIT_PE           (1 << 2)  /*!< Parity Error bit. This is used to indicate the occurrence of a parity error in the receiver if
                                                the Parity Enable (PEN) bit (LCR[3]) is set.
                                                In the FIFO mode, since the parity error is associated with a character received, it is
                                                revealed when the character with the parity error arrives at the top of the FIFO.
                                                It should be noted that the Parity Error (PE) bit (LSR[2]) can be set if a break interrupt has
                                                occurred, as indicated by Break Interrupt (BI) bit (LSR[4]). In this situation, the Parity Error
                                                bit is set if parity generation and detection is enabled (LCR[3]=1) and the parity is set to
                                                odd (LCR[4]=0).
                                                ¦ 0 – no parity error
                                                ¦ 1 – parity error
                                                Reading the LSR clears the PE bit. */
#define UART_LSR_BIT_OE           (1 << 1)  /*!< Overrun error bit. This is used to indicate the occurrence of an overrun error. This occurs
                                                if a new data character was received before the previous data was read.
                                                In the non-FIFO mode, the OE bit is set when a new character arrives in the receiver
                                                before the previous character was read from the RBR. When this happens, the data in the
                                                RBR is overwritten. In the FIFO mode, an overrun error occurs when the FIFO is full and a
                                                new character arrives at the receiver. The data in the FIFO is retained and the data in the
                                                receive shift register is lost.
                                                ¦ 0 – no overrun error
                                                ¦ 1 – overrun error
                                                Reading the LSR clears the OE bit. */
#define UART_LSR_BIT_DR           (1 << 0)  /*!< Data Ready bit. This is used to indicate that the receiver contains at least one character in
                                                the RBR or the receiver FIFO.
                                                ¦ 0 – no data ready
                                                ¦ 1 – data ready
                                                This bit is cleared when the RBR is read in non-FIFO mode, or when the receiver FIFO is
                                                empty, in FIFO mode. */

/*
 * Define the bit mean for MSR
 */
#define UART_MSR_BIT_DCD          (1 << 7)  /*!< Data Carrier Detect. This is used to indicate the current state of the modem control line
                                                dcd_n. This bit is the complement of dcd_n. When the Data Carrier Detect input (dcd_n) is
                                                asserted it is an indication that the carrier has been detected by the modem or data set.
                                                ¦ 0 – dcd_n input is de-asserted (logic 1)
                                                ¦ 1 – dcd_n input is asserted (logic 0)
                                                In Loopback Mode (MCR[4] set to 1), DCD is the same as MCR[3] (Out2) */
#define UART_MSR_BIT_RI           (1 << 6)  /*!< Ring Indicator. This is used to indicate the current state of the modem control line ri_n.
                                                This bit is the complement of ri_n. When the Ring Indicator input (ri_n) is asserted it is an
                                                indication that a telephone ringing signal has been received by the modem or data set.
                                                ¦ 0 – ri_n input is de-asserted (logic 1)
                                                ¦ 1 – ri_n input is asserted (logic 0)
                                                In Loopback Mode (MCR[4] set to 1), RI is the same as MCR[2] (Out1). */
#define UART_MSR_BIT_DSR          (1 << 5)  /*!< Data Set Ready. This is used to indicate the current state of the modem control line dsr_n.
                                                This bit is the complement of dsr_n. When the Data Set Ready input (dsr_n) is asserted it
                                                is an indication that the modem or data set is ready to establish communications with the
                                                UART.
                                                ¦ 0 – dsr_n input is de-asserted (logic 1)
                                                ¦ 1 – dsr_n input is asserted (logic 0)
                                                In Loopback Mode (MCR[4] set to 1), DSR is the same as MCR[0] (DTR). */
#define UART_MSR_BIT_CTS          (1 << 4)  /*!< Clear to Send. This is used to indicate the current state of the modem control line cts_n.
                                                This bit is the complement of cts_n. When the Clear to Send input (cts_n) is asserted it is
                                                an indication that the modem or data set is ready to exchange data with the UART.
                                                ¦ 0 – cts_n input is de-asserted (logic 1)
                                                ¦ 1 – cts_n input is asserted (logic 0)
                                                In Loopback Mode (MCR[4] = 1), CTS is the same as MCR[1] (RTS). */
#define UART_MSR_BIT_DDCD         (1 << 3)  /*!< Delta Data Carrier Detect. This is used to indicate that the modem control line dcd_n has
                                                changed since the last time the MSR was read.
                                                ¦ 0 – no change on dcd_n since last read of MSR
                                                ¦ 1 – change on dcd_n since last read of MSR
                                                Reading the MSR clears the DDCD bit. In Loopback Mode (MCR[4] = 1), DDCD reflects
                                                changes on MCR[3] (Out2).
                                                Note, if the DDCD bit is not set and the dcd_n signal is asserted (low) and a reset occurs
                                                (software or otherwise), then the DDCD bit is set when the reset is removed if the dcd_n
                                                signal remains asserted. */
#define UART_MSR_BIT_TERI         (1 << 2)  /*!< Trailing Edge of Ring Indicator. This is used to indicate that a change on the input ri_n
                                                (from an active-low to an inactive-high state) has occurred since the last time the MSR
                                                was read.
                                                ¦ 0 – no change on ri_n since last read of MSR
                                                ¦ 1 – change on ri_n since last read of MSR
                                                Reading the MSR clears the TERI bit. In Loopback Mode (MCR[4] = 1), TERI reflects
                                                when MCR[2] (Out1) has changed state from a high to a low. */
#define UART_MSR_BIT_DDSR         (1 << 1)  /*!< Delta Data Set Ready. This is used to indicate that the modem control line dsr_n has
                                                changed since the last time the MSR was read.
                                                ¦ 0 – no change on dsr_n since last read of MSR
                                                ¦ 1 – change on dsr_n since last read of MSR
                                                Reading the MSR clears the DDSR bit. In Loopback Mode (MCR[4] = 1), DDSR reflects
                                                changes on MCR[0] (DTR).
                                                Note, if the DDSR bit is not set and the dsr_n signal is asserted (low) and a reset occurs
                                                (software or otherwise), then the DDSR bit is set when the reset is removed if the dsr_n
                                                signal remains asserted. */
#define UART_MSR_BIT_DCTS         (1 << 0)  /*!< Delta Clear to Send. This is used to indicate that the modem control line cts_n has
                                                changed since the last time the MSR was read.
                                                ¦ 0 – no change on cts_n since last read of MSR
                                                ¦ 1 – change on cts_n since last read of MSR
                                                Reading the MSR clears the DCTS bit. In Loopback Mode (MCR[4] = 1), DCTS reflects
                                                changes on MCR[1] (RTS).
                                                Note, if the DCTS bit is not set and the cts_n signal is asserted (low) and a reset occurs
                                                (software or otherwise), then the DCTS bit is set when the reset is removed if the cts_n
                                                signal remains asserted. */

/*
 * Define the bit mean for IER
 */
#define UART_IER_BIT_PTIME        (1 << 7)  /*!< Programmable THRE Interrupt Mode Enable that can be written to only when
                                                THRE_MODE_USER = Enabled, always readable. This is used to enable/disable the
                                                generation of THRE Interrupt.
                                                ¦ 0 – disabled
                                                ¦ 1 – enabled */
#define UART_IER_BIT_EDSI         (1 << 3)  /*!< Enable Modem Status Interrupt. This is used to enable/disable the generation of
                                                Modem Status Interrupt. This is the fourth highest priority interrupt.
                                                ¦ 0 – disabled
                                                ¦ 1 – enabled */
#define UART_IER_BIT_ELSI         (1 << 2)  /*!< Enable Receiver Line Status Interrupt. This is used to enable/disable the generation
                                                of Receiver Line Status Interrupt. This is the highest priority interrupt.
                                                ¦ 0 – disabled
                                                ¦ 1 – enabled */
#define UART_IER_BIT_ETBEI        (1 << 1)  /*!< Enable Transmit Holding Register Empty Interrupt. This is used to enable/disable the
                                                generation of Transmitter Holding Register Empty Interrupt. This is the third highest
                                                priority interrupt.
                                                ¦ 0 – disabled
                                                ¦ 1 – enabled */
#define UART_IER_BIT_ERBFI        (1 << 0)  /*!< Enable Received Data Available Interrupt. This is used to enable/disable the
                                                generation of Received Data Available Interrupt and the Character Timeout Interrupt
                                                (if in FIFO mode and FIFOs enabled). These are the second highest priority
                                                interrupts.
                                                ¦ 0 – disabled
                                                ¦ 1 – enabled */

/*
 * Define the interrupt ID
 */
#define UART_IID_BIT_MS           (0x0) /*!< Modem status.
                                           Interrupt Source: Clear to send or data set ready or ring indicator or data
                                                            carrier detect. Note that if auto flow control mode is enabled, 
                                                            a change in CTS (that is, DCTS set) does not cause an interrupt.
                                           Interrupt Reset Control: Reading the Modem status register. */
                                           
#define UART_IID_BIT_NIP          (0x1) /*!< No interrupt pending.
                                            Interrupt Source: None.
                                            Interrupt Reset Control: None. */

#define UART_IID_BIT_TE           (0x2) /*!< THR empty. 
                                            Interrupt Source: Transmitter holding register empty (Prog. THRE Mode disabled) 
                                                            or XMIT FIFO at or below threshold (Prog. THRE Mode enabled).
                                            Interrupt Reset Control: Reading the IIR register (if source of interrupt); 
                                                            or, writing into THR (FIFOs or THRE Mode not selected or 
                                                            disabled) or XMIT FIFO above threshold (FIFOs and THRE Mode 
                                                            selected and enabled). */

#define UART_IID_BIT_RDA          (0x4) /*!< Received data available. 
                                            Interrupt Source: Receiver data available (nonFIFO mode or FIFOs disabled) or 
                                                            RCVR FIFO trigger level reached (FIFO mode and FIFOs enabled).
                                            Interrupt Reset Control: Reading the receiver buffer register (non-FIFO mode 
                                                            or FIFOs disabled) or the FIFO drops below the trigger level 
                                                            (FIFO mode and FIFOs enabled). */

#define UART_IID_BIT_RLS          (0x6) /*!< Receiver line status. 
                                            Interrupt Source: Overrun/parity/ framing errors, break interrupt, or address 
                                                            received interrupt.
                                            Interrupt Reset Control: Reading the line status register. In addition to LSR 
                                                            read, the Receiver line status is also cleared when RX_FIFO is 
                                                            read. */

#define UART_IID_BIT_BD           (0x7) /*!< Busy detect. 
                                            Interrupt Source: Master has tried to write to the Line Control Register while 
                                                            the UART is busy (USR[0] is set to 1).
                                            Interrupt Reset Control: Reading the UART status register. */

#define UART_IID_BIT_CT           (0xC) /*!< Character timeout. 
                                            Interrupt Source: No characters in or out of the RCVR FIFO during the last 4 
                                                            character times and there is at least 1 character in it during 
                                                            this time.
                                            Interrupt Reset Control: Reading the receiver buffer register */

/*
 * Define the UART status for USR register
 */
#define UART_USR_RFF              (1 << 4)  /*!< Receive FIFO Full. This bit is only valid when FIFO_STAT = YES. This is used to indicate
                                            that the receive FIFO is completely full.
                                            ¦ 0 – Receive FIFO not full
                                            ¦ 1 – Receive FIFO Full
                                            This bit is cleared when the RX FIFO is no longer full. */

#define UART_USR_RFNE             (1 << 3)  /*!< Receive FIFO Not Empty. This bit is only valid when FIFO_STAT = YES. This is used to
                                            indicate that the receive FIFO contains one or more entries.
                                            ¦ 0 – Receive FIFO is empty
                                            ¦ 1 – Receive FIFO is not empty
                                            This bit is cleared when the RX FIFO is empty. */

#define UART_USR_TFE              (1 << 2)  /*!< Transmit FIFO Empty. This bit is only valid when FIFO_STAT = YES. This is used to
                                            indicate that the transmit FIFO is completely empty.
                                            ¦ 0 – Transmit FIFO is not empty
                                            ¦ 1 – Transmit FIFO is empty
                                            This bit is cleared when the TX FIFO is no longer empty. */

#define UART_USR_TFNF             (1 << 1)  /*!< Transmit FIFO Not Full. This bit is only valid when FIFO_STAT = YES. This is used to
                                            indicate that the transmit FIFO in not full.
                                            ¦ 0 – Transmit FIFO is full
                                            ¦ 1 – Transmit FIFO is not full
                                            This bit is cleared when the TX FIFO is full. */

#define UART_USR_BUSY             (1 << 0)  /*!< UART Busy. This bit is valid only when UART_16550_COMPATIBLE = NO and indicates
                                            that a serial transfer is in progress; when cleared, indicates that the UART is idle
                                            or inactive.
                                            ¦ 0 – UART is idle or inactive
                                            ¦ 1 – UART is busy (actively transferring data)
                                            This bit will be set to 1 (busy) under any of the following conditions:
                                            1. Transmission in progress on serial interface
                                            2. Transmit data present in THR, when FIFO access mode is not being used (FAR = 0)
                                            and the baud divisor is non-zero ({DLH,DLL} does not equal 0) when the divisor latch
                                            access bit is 0 (LCR.DLAB = 0)
                                            3. Reception in progress on the interface
                                            4. Receive data present in RBR, when FIFO access mode is not being used (FAR = 0)
                                            NOTE: It is possible for the UART Busy bit to be cleared even though a new character may
                                            have been sent from another device. That is, if the UART has no data in THR and
                                            RBR and there is no transmission in progress and a start bit of a new character has just
                                            reached the UART. This is due to the fact that a valid start is not seen until the
                                            middle of the bit period and this duration is dependent on the baud divisor that has been
                                            programmed. If a second system clock has been implemented (CLOCK_MODE =
                                            Enabled), the assertion of this bit is also delayed by several cycles of the slower clock. */


typedef enum UART_WordLength {
    UART_WL_5BITS,
    UART_WL_6BITS,
    UART_WL_7BITS,
    UART_WL_8BITS,
    UART_WL_9BITS,
} UART_WordLength_Type;

typedef enum UART_StopBits {
    UART_SB_1BIT,                       /*!< 1 stop bit */
    UART_SB_1_5_2BITS,                  /*!< 1.5 stop bits when WordLength is 5bits, else 2 stop bit */
} UART_StopBits_Type;

typedef enum UART_ParityMode {
    UART_PM_NONE,
    UART_PM_ODD,
    UART_PM_EVEN,
    UART_PM_STICK_LOG0,
    UART_PM_STICK_LOG1
} UART_ParityMode_Type;

typedef enum UART_HWFlowControlMode {
    UART_FC_NONE,
    UART_FC_DTRDSR,
    UART_FC_RTSCTS,
    UART_FC_AUTO_RTSCTS,
    UART_FC_RTSCTS_DTRDSR,
    UART_FC_AUTO_RTSCTS_DTRDSR,
    
} UART_HWFlowControlMode_type;

typedef enum UART_DMAMode {
    UART_DM_MODE_0,
    UART_DM_MODE_1
} UART_DMAMode_Type;

typedef enum UART_FIFOMode {
    UART_FM_DISABLE,
    UART_FM_ENABLE
} UART_FIFOMode_Type;

typedef enum UART_TXFIFOTriggerMode {
    UART_TT_EMPTY,
    UART_TT_2_CHARACTERS,
    UART_TT_QUARTER,
    UART_TT_HALF
} UART_TXFIFOTriggerMode_Type;

typedef enum UART_RXFIFOTriggerMode {
    UART_RT_1_CHARACTER,
    UART_RT_QUARTER,
    UART_RT_HALF,
    UART_RT_2_LESS
} UART_RXFIFOTriggerMode_Type;

typedef enum 
{
    UART_ERBFI,/*Enable Received Data Available Interrupt. */
    UART_ETBEI,/*Enable Transmit Holding Register Empty Interrupt. */
    UART_ElSI,/*Enable Receiver Line Status Interrupt. */
    UART_EDSSI,/*Enable Modem Status Interrupt.*/
    UART_ELCOLR,/*ALC:his is applicable only for Overrun Error, Parity Error, Framing Error, and Break Interrupt status bits*/
    UART_RES1, /* Reserved bits read as zero (0).*/
    UART_RES2, /* Reserved bits read as zero (0).*/
    UART_PTIME,/*Programmable THRE Interrupt Mode Enable*/
}UART_Interrupt_Tpye;


typedef enum
{
    MODEM_STATUS=0,           //): modem status
    NO_INTERRUPT_PENDING=1,   //): no interrupt pending
    THR_EMPTY=2,              //): THR empty
    RECEIVED_DATA_AVAILABLE=4,//): received dataavailable
    RECEIVER_LINE_STATUS=6,   //): receiver line status
    BUSY_DETECT=7,            //): busy detect
    CHARACTER_TIMEOUT=12,      //): character ti
}UART_InterID_Tpye;

typedef struct UART_InitInfo {
    uint32_t UART_BaudRate;             /*!< This member configures the USART communication baud rate.
                                           The baud rate is computed using the following formula:
                                            - IntegerDivider = ((PCLKx) / (16 * (USART_InitStruct->USART_BaudRate)))
                                            - FractionalDivider = ((IntegerDivider - ((u32) IntegerDivider)) * 16) + 0.5 */

    uint16_t UART_WordLength;           /*!< Specifies the number of data bits transmitted or received in a frame.
                                           This parameter can be a value of @ref UART_WordLength_Type */

    uint16_t UART_StopBits;             /*!< Specifies the number of stop bits transmitted.
                                           This parameter can be a value of @ref UART_StopBits_Type */

    uint16_t UART_ParityMode;           /*!< Specifies the parity mode.
                                           This parameter can be a value of @ref UART_ParityMode_Type
                                           @note When parity is enabled, the computed parity is inserted
                                                 at the MSB position of the transmitted data */

    uint16_t UART_HardwareFlowControl;  /*!< Specifies wether the hardware flow control mode is enabled
                                           or disabled.
                                           This parameter can be a value of @ref UART_HWFlowControlMode_type */

    uint16_t UART_DMAMode;              /*!< Specifies wether the fifo mode is MODE_0 or MODE_1.
                                          This parameter can be a value of @ref UART_DMAMode_Type */

    uint16_t UART_FIFOMode;             /*!< Specifies wether the DMA mode is enabled or disabled.
                                           This parameter can be a value of @ref UART_FIFOMode_Type */
                                           
    uint16_t UART_TX_FIFOTriggerMode;   /*!< Specifies wether the fifo mode is enabled
                                           or disabled.
                                           This parameter can be a value of @ref UART_TXFIFOTriggerMode_Type */
                                           
    uint16_t UART_RX_FIFOTriggerMode;   /*!< Specifies wether the fifo mode is enabled
                                           or disabled.
                                           This parameter can be a value of @ref UART_RXFIFOTriggerMode_Type */
} UART_InitInfo_Type;



typedef void (*UART_write_handle)(void);


/**
  * @brief  Deinitializes the UART peripheral registers to their default reset values.
  * @param  None
  * @retval None
  */
void UART_DeInit(UART_TypeDef *UARTx);

/**
  * @brief  Initializes the UART peripheral according to the specified
  *         parameters in the UART_InitInfo_Type.
  * @param  UARTx: pointer to a UART.
  * @param  UART_InitStruct: pointer to a UART_InitInfo_Type structure that
  *         contains the configuration information for the specified UART peripheral.
  * @retval None
  */
void UART_Init(UART_TypeDef *UARTx, UART_InitInfo_Type *UART_InitStruct);

/**
  * @brief  Set the UART peripheral interrupt enable.
  *
  * @param  UARTx: pointer to a UART.
  * @param  UART_IntMask: Which interrput will be enabled for the specified UART peripheral interrupt mask.
  * @retval None
  */
void UART_InterruptSet(UART_TypeDef *UARTx, uint16_t UART_IntMask);

/**
  * @brief  Write to UART peripheral with byte.
  *
  * @param  UARTx: pointer to a UART.
  * @param  byte: This data will be write to the UART fifo or data register.
  * @retval None
  */
void UART_WriteByte(UART_TypeDef *UARTx, uint8_t byte);

/**
  * @brief  Write to UART peripheral with byte.
  *
  * @param  UARTx: pointer to a UART.
  * @param  data: The data pointer will be write to the UART fifo or data register.
  * @param  length: The data length.
  * @retval None
  */
void UART_WriteData(UART_TypeDef *UARTx, uint8_t *data, uint16_t length);

/**
  * @brief  Read from UART peripheral.
  *
  * @param  UARTx: pointer to a UART.
  * @retval The data will be read from the UART fifo or data register.
  */
uint8_t UART_ReadByte(UART_TypeDef *UARTx);

/**
  * @brief  Conterl Auto Flaow to UART0 peripheral.
  * @param  UARTx: pointer to a UART.
  * @param  En: true-> Enable ; false->Disable.
  * @retval None
  */
void  UART_AutoFlow(UART_TypeDef *UARTx,bool En);

/**
  * @brief  Conterl RTS to UART0 peripheral.
  * @param  UARTx: pointer to a UART.
  * @param  En: true-> Enable ; false->Disable.
  * @retval None
  */
void  UART_SetRts(UART_TypeDef *UARTx,bool En);


void UART_SetUWriteHandle(UART_write_handle handle);

/**
  * @brief  Check line status with parameter bits specified.
  *
  * @param  UARTx: pointer to a UART.
  * @param  bits:  Which status need check.
  * @retval The status (SET/RESET).
  */
FlagStatus UART_LSRCheckBits(UART_TypeDef *UARTx, uint32_t bits);

/**
  * @brief  Check modem status with parameter bits specified.
  *
  * @param  UARTx: pointer to a UART.
  * @param  bits:  Which status need check.
  * @retval The status (SET/RESET).
  */
FlagStatus UART_MSRCheckBits(UART_TypeDef *UARTx, uint32_t bits);

/**
  * @brief  Check interrupt IDs with parameter bits specified.
  *
  * @param  UARTx: pointer to a UART.
  * @param  bits:  Which IDs need check.
  * @retval The status (SET/RESET).
  */
ITStatus UART_GetInterruptStatus(UART_TypeDef *UARTx, uint16_t UART_IntIds);

UART_InterID_Tpye UART_GetInterruptID(UART_TypeDef *UARTx);

uint32_t UART_GetStatus(UART_TypeDef *UARTx);
#endif /* __BR00x_UART_H__ */
