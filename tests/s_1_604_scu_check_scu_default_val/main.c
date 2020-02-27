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


SCU_TypeDef SCUDefaultValue = {
    .CLK_EN     =(0x0004000C|(0x01 << UART0_CKEn)),            /*!< Offset: 0x000  */  
    .SW_RST     =0x0,                   /*!< Offset: 0x004  */
    .CLK_CTL    =0x0,                   /*!< Offset: 0x008  */
    .CLK_DIV    =0x0,                   /*!< Offset: 0x00c  */
    .SYS_CONFIG =0x0,                   /*!< Offset: 0x010  */
    .SYS_STATUS =0x0,                   /*!< Offset: 0x014  */
    .SLEEP_EN   =0x0,                   /*!< Offset: 0x018  */
    .PWR_STATUS =0x1,                   /*!< Offset: 0x01c  */
    .DEV_CONFIG =0x20000,               /*!< Offset: 0x020  */
    .DEV_STATUS =0xA7,/*USB STATUS*/    /*!< Offset: 0x024  */
    .IO_CONFIG  =0x0,                   /*!< Offset: 0x028  */
    .IO_STATUS  =0x0,                   /*!< Offset: 0x02c  */
    .CLK_DIV1   =0x0,                   /*!< Offset: 0x030  */
    .CLK_DIV2   =0x0,                   /*!< Offset: 0x034  */
    
    .SEND_CMD   =0x0,                   /*!< Offset: 0x038  */
    .SEND_DATA  =0x0,                   /*!< Offset: 0x03C  */
    .READ_CMD   =0x0,                   /*!< Offset: 0x040  */
    .READ_DATA  =0x0,                   /*!< Offset: 0x044  */
    .ANA_CTL0   =0x0FFF90f0,            /*!< Offset: 0x048  */
    .ANA_CTL1   =0x89942452,            /*!< Offset: 0x04C  */
    .ANA_CTL2   =0x0F20AAA4,            /*!< Offset: 0x050  */
    .ANA_CTL3   =0x2C608238,            /*!< Offset: 0x054  */
    .ANA_CTL4   =0x92722800,            /*!< Offset: 0x058  */
    .ANA_STATUS0   =0x0,                /*!< Offset: 0x05C  */
    .ANA_STATUS1   =0x140000,           /*!< Offset: 0x060  */
    
    /*!< Offset: 0x064-0X70 */
    .TIMERS_DIV[0] =0x0,.TIMERS_DIV[1] =0x0,.TIMERS_DIV[2] =0x0,.TIMERS_DIV[3] =0x0,
    .TIMERS_DIV[4] =0x0,.TIMERS_DIV[5] =0x0,.TIMERS_DIV[6] =0x0,.TIMERS_DIV[7] =0x0,
    /*!< Offset: 0X74-0x114 */ 
    .PAD_CFG[0]=0x0,.PAD_CFG[8 ]=0xF,.PAD_CFG[16]=0xF,.PAD_CFG[24]=0xF,.PAD_CFG[32]=0xF,
    .PAD_CFG[1]=0x0,.PAD_CFG[9 ]=0xF,.PAD_CFG[17]=0xF,.PAD_CFG[25]=0xF,.PAD_CFG[33]=0xF,
    .PAD_CFG[2]=0x0,.PAD_CFG[10]=0xF,.PAD_CFG[18]=0xF,.PAD_CFG[26]=0xF,.PAD_CFG[34]=0xF,
    .PAD_CFG[3]=0x0,.PAD_CFG[11]=0xF,.PAD_CFG[19]=0xF,.PAD_CFG[27]=0xF,.PAD_CFG[35]=0x0,
    .PAD_CFG[4]=0x0,.PAD_CFG[12]=0xF,.PAD_CFG[20]=0xF,.PAD_CFG[28]=0xF,.PAD_CFG[36]=0x0,
    .PAD_CFG[5]=0x0,.PAD_CFG[13]=0xF,.PAD_CFG[21]=0xF,.PAD_CFG[29]=0xF,.PAD_CFG[37]=0x0,
    .PAD_CFG[6]=0xF,.PAD_CFG[14]=0xF,.PAD_CFG[22]=0xF,.PAD_CFG[30]=0xF,.PAD_CFG[38]=0x0,
    .PAD_CFG[7]=0xF,.PAD_CFG[15]=0xF,.PAD_CFG[23]=0xF,.PAD_CFG[31]=0xF,.PAD_CFG[39]=0x0,
    
    .BB_WAKEUP_MASK_L=0x0,             /*!< Offset: 0X118 */
    .BB_WAKEUP_MASK_H=0x0,             /*!< Offset: 0X11c */
    .BB_WAKEUP_MASK_SEL=0x0            /*!< Offset: 0X120 */

};



int main (void)
{
    bool sut = true;
    sysTimeUpdataClk(SystemCoreClock);
    Verrify_SendPinConnect(UART0_OUTPUT);
    LOGUartInit();
    c_printf("s_1_604_scu_check_scu_default_val case \r\n");
    c_printf("SCU App Check Scu Default value\n");
    {
        
        volatile uint32_t *addr1 = (uint32_t *)SCU;
        volatile uint32_t *addr2 = (uint32_t *)&SCUDefaultValue;

        Verrify_SendPinConnect(0);
        for(uint32_t i=0;i<sizeof(SCU_TypeDef)/sizeof(uint32_t);i++)
        {
            //if ((uint32_t)addr1 == 0x9000005c){
            //    addr1+=2;
            //    addr2+=2;
            //    i++;
            //    continue;
            //}

            if((*addr1) != (*addr2))
            {
                c_printf("SCU Default Error; addr:%X scu:[%8X],Rdata[%8X]\n",addr1,*addr1,*addr2);
                sut = false;
                break;
            }
            addr1++;
            addr2++;
        }
        
        SCU->SW_RST |=0x01;
        addr1 = (uint32_t *)SCU;
        addr2 = (uint32_t *)&SCUDefaultValue;
        SystemDevClockCtl(UART0_CKEn,true);  
        for(uint32_t i=0;i<sizeof(SCU_TypeDef)/sizeof(uint32_t);i++)
        {
            //if ((uint32_t)addr1 == 0x9000005c){
            //    addr1+=2;
            //    addr2+=2;
            //    i++;
            //    continue;
            //}

            if((*addr1) != (*addr2))
            {
                c_printf("ReSCU Default Error; addr:%X [%8X],[%8X]\n",addr1,*addr1,*addr2);
                sut = false;
                break;
            }
            addr1++;
            addr2++;
        }     
    }

	MCU_Sleep(1);
    c_printf("s_1_604_scu_check_scu_default_val case completed \r\n");
    SimulationEnd();
    while(1){     
    };
}
















