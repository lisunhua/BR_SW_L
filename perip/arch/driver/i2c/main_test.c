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
#include "BR00x_config.h"

#include "BR00x_uart.h"
#include "log_uart_config.h"

#include "BR00x_clock.h"
#include "i2c_api.h"
#include "e2prom_api.h"


//##########################################################
static unsigned long g_u32TimerMsCnt = 0;

unsigned long MCU_GetTickCount(void)
{
    return g_u32TimerMsCnt;
}

void SysTick_Handler(void)
{
  g_u32TimerMsCnt++;
}

void MCU_Sleep(unsigned int ms)
{
    unsigned long dest_time = ms + MCU_GetTickCount();
    while (MCU_GetTickCount() <= dest_time);
}
void sysTimeUpdataClk(uint32_t clk)
{
    SysTick_Config(clk/1000);
}

//##########################################################
void  printf_debug(const char *ch,uint8_t *da,uint16_t len)
{
    c_printf("%s",ch);
    for(uint16_t i =0 ;i<len; i++)
        c_printf("%d,",da[i]);
    c_printf("\r\n");
}
//##########################################################
#define data_len  1000

int main (void)
{
    uint8_t data_tx[data_len];
    uint8_t data_rx[data_len];
    PADConfig_Type      PAD_InitStru;
    
    SCU->CLK_EN = 0xffffffff;
    memset(&PAD_InitStru,0,sizeof(PADConfig_Type));
    memset(data_rx,0,sizeof(data_rx));
    
    sysTimeUpdataClk(SystemCoreClock);
    LOGUartInit();
    
    for(uint16_t i =0 ;i<data_len; i++)
        data_tx[i] = 0xff-i;
    
   
    PAD_InitStru.pad_ctl    = PAD_MODE1;
    SystemPADConfig(PADID17,&PAD_InitStru);
    SystemPADConfig(PADID18,&PAD_InitStru);
    c_printf("i2c verify \r\n");
         
    i2cm_init(&i2cm_default_cfg);
    if(eeprom_init())
        c_printf("i2c verify Init Success\r\n");
    else
        c_printf("i2c verify Init fail\r\n");
                    
    printf_debug("write:\r\n",data_tx,sizeof(data_tx));
    eeprom_block_write(0,data_tx,data_len);
    MCU_Sleep(100);//wiat E2prom Write
    eeprom_random_addr_read(0,data_rx,data_len);
    printf_debug("EEPROM read:\r\n",data_rx,sizeof(data_rx));
    
    while(1){     
    };
}
//##########################################################













