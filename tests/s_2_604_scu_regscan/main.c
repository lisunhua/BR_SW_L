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
#include "verify_register_handle.h"
#include "log_uart_config.h"


#if  defined(BR002)||defined(BR003)
#include "BR00x_rom.h"
#endif

#ifdef SCU_DEBUG_LOG
#define scuprf(format, ...) cm_printf(format, ##__VA_ARGS__)
#else
#define scuprf(format, ...)
#endif

  
#if  defined(BR002) || defined(BR003) || defined(BR005)

const RegisterCell SCU_RegList[]=
{
  
//  {read,  write,  Register ID ,register_attr, Register},
  //{true,  true,   1,   0xFFFFFFFF,     &SCU->CLK_EN},//Reserved
    {true,  true,   2,   0xFFFFFFEE,     &SCU->SW_RST}, //bit[0] Reset SCU Cannot Set  
    {true,  true,   3,   0x1FE1FFFF,     &SCU->CLK_CTL},
    {true,  true,   4,   0xFFFFFFFF,     &SCU->CLK_DIV},
//    {true,  true,   5,   0xFFFFFFFF,     &SCU->SYS_CONFIG},
    {true,  false,  6,   0xFFFFFFFF,     (volatile uint32_t*)&SCU->SYS_STATUS},
//  {true,  true,   7,   0xFFFFFFFF,     &SCU->SLEEP_EN},
    {true,  false,  8,   0xFFFFFFFF,     (volatile uint32_t*)&SCU->PWR_STATUS},
    {true,  true,   9,   0xFFFFFFFF,     &SCU->DEV_CONFIG},
    {true,  false,  10,  0xFFFFFFFF,     (volatile uint32_t*)&SCU->DEV_STATUS},
    {true,  true,   11,  0xFFFFFFFF,     &SCU->IO_CONFIG},
    {true,  false,  12,  0xFFFFFFFF,     (volatile uint32_t*)&SCU->IO_STATUS},
    {true,  true,   13,  0xFFFFFFFF,     &SCU->CLK_DIV1},
    {true,  true,   14,  0xFFFFFFFF,     &SCU->CLK_DIV2},
    
//    {true,  true,   15,  0xFFFFFFEF,     &SCU->ANA_CTL0},  //GW change FF to EF 24M clk //sunhua said this is ignore
//    {true,  true,   16,  0xFFFFFFFF,     &SCU->ANA_CTL1},  //GW  
//    {true,  true,   17,  0xFFFFFFFF,     &SCU->ANA_CTL2},  //GW 
//    {true,  true,   18,  0xFFFFFFFF,     &SCU->ANA_CTL3},  //GW 
//    {true,  true,   19,  0xFFFFFFFF,     &SCU->ANA_CTL4},  //GW 
    {true,  false,  20,  0xFFFFFFFF,     (volatile uint32_t*)&SCU->ANA_STATUS0},
    {true,  false,  21,  0xFFFFFFFF,     (volatile uint32_t*)&SCU->ANA_STATUS1},
  
    {true,  true,  22,  0x0000FFFF,     (volatile uint32_t*)&SCU->TIMERS_DIV[0]},
    {true,  true,  23,  0x0000FFFF,     (volatile uint32_t*)&SCU->TIMERS_DIV[1]},
    {true,  true,  24,  0x0000FFFF,     (volatile uint32_t*)&SCU->TIMERS_DIV[2]},
    {true,  true,  25,  0x0000FFFF,     (volatile uint32_t*)&SCU->TIMERS_DIV[3]},
    {true,  true,  26,  0x0000FFFF,     (volatile uint32_t*)&SCU->TIMERS_DIV[4]},
    {true,  true,  27,  0x0000FFFF,     (volatile uint32_t*)&SCU->TIMERS_DIV[5]},
    {true,  true,  28,  0x0000FFFF,     (volatile uint32_t*)&SCU->TIMERS_DIV[6]},
    {true,  true,  29,  0x0000FFFF,     (volatile uint32_t*)&SCU->TIMERS_DIV[7]},

  /*{true,  true,  26,  0x0000003F,     &SCU->PAD_CFG[0]},
    {true,  true,  27,  0x0000003F,     &SCU->PAD_CFG[1]},
    {true,  true,  28,  0x0000003F,     &SCU->PAD_CFG[2]},
    {true,  true,  29,  0x0000003F,     &SCU->PAD_CFG[3]},
    {true,  true,  30,  0x0000003F,     &SCU->PAD_CFG[4]},
    {true,  true,  31,  0x0000003F,     &SCU->PAD_CFG[5]},
    {true,  true,  32,  0x0000003F,     &SCU->PAD_CFG[6]},
    {true,  true,  33,  0x0000003F,     &SCU->PAD_CFG[7]},
    {true,  true,  34,  0x0000003F,     &SCU->PAD_CFG[8]},
    {true,  true,  35,  0x0000003F,     &SCU->PAD_CFG[9]},
    {true,  true,  36,  0x0000003F,     &SCU->PAD_CFG[10]},
    {true,  true,  37,  0x0000003F,     &SCU->PAD_CFG[11]},
    {true,  true,  38,  0x0000003F,     &SCU->PAD_CFG[12]},
    {true,  true,  39,  0x0000003F,     &SCU->PAD_CFG[13]},
    {true,  true,  40,  0x0000003F,     &SCU->PAD_CFG[14]},
    {true,  true,  41,  0x0000003F,     &SCU->PAD_CFG[15]},
    {true,  true,  42,  0x0000003F,     &SCU->PAD_CFG[16]},
    {true,  true,  43,  0x0000003F,     &SCU->PAD_CFG[17]},
    {true,  true,  44,  0x0000003F,     &SCU->PAD_CFG[18]},
    {true,  true,  45,  0x0000003F,     &SCU->PAD_CFG[19]},
    {true,  true,  46,  0x0000003F,     &SCU->PAD_CFG[20]},
    {true,  true,  47,  0x0000003F,     &SCU->PAD_CFG[21]},
    {true,  true,  48,  0x0000003F,     &SCU->PAD_CFG[22]},
    {true,  true,  49,  0x0000003F,     &SCU->PAD_CFG[23]},
    {true,  true,  50,  0x0000003F,     &SCU->PAD_CFG[24]},
    {true,  true,  51,  0x0000003F,     &SCU->PAD_CFG[25]},
    {true,  true,  52,  0x0000003F,     &SCU->PAD_CFG[26]},
    {true,  true,  53,  0x0000003F,     &SCU->PAD_CFG[27]},
    {true,  true,  54,  0x0000003F,     &SCU->PAD_CFG[28]},
    {true,  true,  55,  0x0000003F,     &SCU->PAD_CFG[29]},
    {true,  true,  56,  0x0000003F,     &SCU->PAD_CFG[30]},
    {true,  true,  57,  0x0000003F,     &SCU->PAD_CFG[31]},
    {true,  true,  58,  0x0000003F,     &SCU->PAD_CFG[32]},
    {true,  true,  59,  0x0000003F,     &SCU->PAD_CFG[33]},
    {true,  true,  60,  0x0000003F,     &SCU->PAD_CFG[34]},
    {true,  true,  61,  0x0000003F,     &SCU->PAD_CFG[35]},
    {true,  true,  62,  0x0000003F,     &SCU->PAD_CFG[36]},
    {true,  true,  63,  0x0000003F,     &SCU->PAD_CFG[37]},
    {true,  true,  64,  0x0000003F,     &SCU->PAD_CFG[38]},
    {true,  true,  65,  0x0000003F,     &SCU->PAD_CFG[39]},
    
*/

};

#endif

int main (void)
{
    sysTimeUpdataClk(SystemCoreClock);
    Verrify_SendPinConnect(UART0_OUTPUT);
    LOGUartInit();
    c_printf("s_2_604_scu_regscan case \r\n");
    {
        bool sut = true;
        uint32_t idx=0;
    
        sut = Verify_RegisterHandle(SCU_RegList,sizeof(SCU_RegList),idx);
        Verify_SendCResult(BRCASE_RESULT,sut);
    }
    SimulationEnd();
    while(1){     
    };
}














