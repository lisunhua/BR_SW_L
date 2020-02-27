/*
 *++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 * Copyright (c) 1999-2018 Barrot Technology Limited
 *
 * All rights reserved.
 *
 *------------------------------------------------------------------------------
 */
/**
 * @file main.c
 * @brief Main program entry
 * @attention
 *
 * THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
 * WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE
 * TIME. AS A RESULT, STMICROELECTRONICS SHALL NOT BE HELD LIABLE FOR ANY
 * DIRECT, INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING
 * FROM THE CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE
 * CODING INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
 *
 * @date    14. Augest 2019
 * @version V1.0.0
 * @author  MEIGER
*/

#include <stdio.h>
#include "BR00x_uart.h"
#include "BR00x_clock.h"
#include "BR00x_config.h"
#include "verify_message.h"
#include "log_uart_config.h"


#define SetDIVReg(x,y,z)  y?(x |= 0x01ul<<z ):(x &= ~(0x01ul<<z)) 

int main (void)
{
    sysTimeUpdataClk(SystemCoreClock);
    Verrify_SendPinConnect(UART0_OUTPUT);
    LOGUartInit();
    c_printf("s_1_603_scu_scan_div_register case \r\n");

    {
        SCU->CLK_EN = 0xffffffff;
        uint32_t ctl = 0xFFFFFFFF;
			for(uint16_t idx=0;idx<32;idx++){
				if((ctl>>idx & 0x01)){
                    SetDIVReg(SCU->CLK_DIV,1,idx);
                    SetDIVReg(SCU->CLK_DIV,0,idx);
				}
            }
            for(uint16_t idx=0;idx<32;idx++){
				if((ctl>>idx & 0x01)){
                    SetDIVReg(SCU->CLK_DIV1,1,idx);
                    SetDIVReg(SCU->CLK_DIV1,0,idx);
				}
            }
            for(uint16_t idx=0;idx<32;idx++){
				if((ctl>>idx & 0x01)){
                    SetDIVReg(SCU->CLK_DIV2,1,idx);
                    SetDIVReg(SCU->CLK_DIV2,0,idx);
				}
            }
            
            for(uint16_t tm=0;tm<8;tm++){
                for(uint16_t idx=0;idx<16;idx++){
                    if((ctl>>idx & 0x01)){
                        SetDIVReg(SCU->TIMERS_DIV[tm],1,idx);
                        SetDIVReg(SCU->TIMERS_DIV[tm],0,idx);
                    }
                }
            }
            
            for(uint16_t tm=0;tm<33;tm++){
                for(uint16_t idx=0;idx<32;idx++){
                    if((ctl>>idx & 0x01)){
                        SetDIVReg(SCU->PAD_CFG[tm],1,idx);
                        SetDIVReg(SCU->PAD_CFG[tm],0,idx);
                    }
                }
            } 
            
            for(uint16_t idx=0;idx<32;idx++){
				if((ctl>>idx & 0x01)){
                    SetDIVReg(SCU->READ_DATA,1,idx);
                    SetDIVReg(SCU->READ_DATA,0,idx);
				}
            }

            for(uint16_t idx=0;idx<32;idx++){
				if((ctl>>idx & 0x01)){
                    SetDIVReg(SCU->READ_CMD,1,idx);
                    SetDIVReg(SCU->READ_CMD,0,idx);
				}
            }
            for(uint16_t idx=0;idx<32;idx++){
                if((0xffffffff>>idx & 0x01)){
                    SetDIVReg(SCU->SEND_DATA,1,idx);
                    SetDIVReg(SCU->SEND_DATA,0,idx);
				}
            }
            for(uint16_t idx=0;idx<32;idx++){
                if((0xffffffff>>idx & 0x01)){
                    SetDIVReg(SCU->SEND_CMD,1,idx);
                    SetDIVReg(SCU->SEND_CMD,0,idx);
				}
            }
    }

	MCU_Sleep(3);
    c_printf("s_1_603_scu_scan_div_register case completed \r\n");
    SimulationEnd();
    while(1){     
    };
}
















