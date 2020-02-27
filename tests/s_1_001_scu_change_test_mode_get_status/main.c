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


int main (void)
{
    sysTimeUpdataClk(SystemCoreClock);
    Verrify_SendPinConnect(UART0_OUTPUT);
    LOGUartInit();
    c_printf("s_1_001_scu_change_test_mode_get_status case \r\n");

    {
        uint32_t status=0;
        c_printf("IO S[%X]\n",status);
        
        for(MessagaConnectEn_Type md = TMODE_0; md<=TMODE_5;md++)
        {
            Verrify_SendPinConnect(md);
            Verrify_SendPinConnect(TMODE_DIS);
            Verrify_SendPinConnect(TMODE_EN);
            c_printf("TMode[%d]\n",md-TMODE_0); 
            c_printf("TMode En\n");
            status= SCU->IO_STATUS;
            c_printf("IO S[%X],FUNC[%s],MB[%s],SC[%s],BS[%s]\n",
            status,
            (status>>7 & 0x01)?"true":"false",
            (status>>4 & 0x01)?"true":"false",
            (status>>5 & 0x01)?"true":"false",
            (status>>6 & 0x01)?"true":"false");
        }
    }

	MCU_Sleep(3);
    c_printf("s_1_001_scu_change_test_mode_get_status case completed \r\n");
    SimulationEnd();
    while(1){     
    };
}
















