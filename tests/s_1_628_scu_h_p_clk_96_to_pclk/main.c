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
#include "BR00x_ssi.h"
#include "BR00x_ssi_common.h"
#include "BR00x_config.h"
#include "verify_message.h"
#include "log_uart_config.h"


//HCLK Pre Select
uint32_t P_scu_HClkSelect(SCU_HclkSelect_Type st, uint32_t clk)
{
	clk &= ~(0x03<<3);
	clk |=  (st&0x03)<<3;
    return clk;
}

//PCLK Pre Select
uint32_t P_scu_PClkPreSelect(SCU_Pclk_Pre_Select_Type st,uint32_t clk)
{
    clk &= ~(0x0f<<10);
    clk |=  (st&0x0f)<<10;
    return clk;  
}
//96M DIV Select
uint32_t P_scu_ClockSelectDivControl(SCU_96MDIVCtl_Type st,uint32_t clk)
{   
    clk &= ~0x03;
    clk |= st&0x03;
    return clk;
}



void  delay_ms(uint32_t clk,uint32_t timer)
{
    uint32_t cot= clk/10000;
    for(uint16_t k=0;k<timer;k++)
        for(uint32_t i = 0; i<cot;i++)
        {}
}



void verify_clk_reg(__IO uint32_t *reg,uint32_t val, bool *rut,uint32_t *val_fl,uint32_t *idx)
{
    uint32_t  buff = 0;
    (*reg)= val;
    for(uint16_t k=0;k<50;k++);
    buff = (*reg);
    if(buff != val)
    {
        (*rut) = false;
    }
    if(*rut)
        (*val_fl)|=0x01ul<<(*idx);
    else
        (*rut)=true;  
    (*idx)++;
}
void verify_clk_reg_dely(__IO uint32_t *reg,uint32_t val, bool *rut,uint32_t *val_fl,uint32_t *idx)
{
    uint32_t  buff = 0;
    (*reg)= val;
    for(uint16_t k=0;k<10;k++);
    buff = (*reg);
    for(uint16_t k=0;k<10;k++);
    if(buff != val)
    {
        *rut =false;
    }
    if(*rut)
        (*val_fl)|=0x01ul<<(*idx);
    else
        (*rut)=true;  
    (*idx)++;
}


bool  verify_clk_rw_IP(uint32_t *step,bool *sut,uint32_t cot)
{    
    bool  rut =true;
    uint32_t val_fl = 0;
    uint32_t bit_t  = 0;
    SCU->SEND_DATA = cot;

/*0*/verify_clk_reg(&GPIO->DR0,0x005500aa,&rut,&val_fl,&bit_t);
/*1*/verify_clk_reg(&GPIO->DR0,0x01,&rut,&val_fl,&bit_t);
/*2*/verify_clk_reg(&SCU->PAD_CFG[0],0xb,&rut,&val_fl,&bit_t);
/*3*/verify_clk_reg(&SCU->PAD_CFG[0],0x01,&rut,&val_fl,&bit_t);
/*4*/verify_clk_reg(&WDT->TORR,0x06,&rut,&val_fl,&bit_t);
/*5*/verify_clk_reg(&WDT->TORR,0x01,&rut,&val_fl,&bit_t);
/*6*/verify_clk_reg(&RTC->CLR ,0x518,&rut,&val_fl,&bit_t);
/*7*/verify_clk_reg(&RTC->CLR ,0x01,&rut,&val_fl,&bit_t);
/*8*/verify_clk_reg(&UART1->DLF ,0xe,&rut,&val_fl,&bit_t);
/*9*/verify_clk_reg(&UART1->DLF ,0x01,&rut,&val_fl,&bit_t);
    SPIM1->SSIENR   = DISABLE;
    SPIM1->IMR      = DISABLE;
/*10*/verify_clk_reg(&SPIM1->BAUDR ,0x80,&rut,&val_fl,&bit_t);
/*11*/verify_clk_reg(&SPIM1->BAUDR ,2,&rut,&val_fl,&bit_t);
     SPIS1->SSIENR   = DISABLE;
     SPIS1->IMR      = DISABLE;
 /*12*/verify_clk_reg(&SPIS1->TXFTLR ,0x5,&rut,&val_fl,&bit_t);
 /*13*/verify_clk_reg(&SPIS1->TXFTLR ,0x01,&rut,&val_fl,&bit_t);
 /*14*/verify_clk_reg(&I2SM->CCR ,0xF,&rut,&val_fl,&bit_t);
 /*15*/verify_clk_reg(&I2SM->CCR ,0x01,&rut,&val_fl,&bit_t);
 /*16*/verify_clk_reg(&I2SS->I2S_Ch.RCR ,2,&rut,&val_fl,&bit_t);
 /*17*/verify_clk_reg(&I2SS->I2S_Ch.RCR ,0x01,&rut,&val_fl,&bit_t);
 /*18*/verify_clk_reg(&I2C0->IC_TAR ,2,&rut,&val_fl,&bit_t);
 /*19*/verify_clk_reg(&I2C0->IC_TAR ,0x01,&rut,&val_fl,&bit_t);
 /*20*/verify_clk_reg(&DMA->CHR[0].SAR ,0x123,&rut,&val_fl,&bit_t);
 /*21*/verify_clk_reg(&DMA->CHR[0].SAR ,0x01,&rut,&val_fl,&bit_t);
     SPIM0->SSIENR = DISABLE;
     SSI_ClearInterrupt(SPIM0);
     SPIM0->IMR = DISABLE;
 /*22*/verify_clk_reg_dely(&SPIM0->TXFTLR ,6,&rut,&val_fl,&bit_t);
 /*23*/verify_clk_reg_dely(&SPIM0->TXFTLR ,0x01,&rut,&val_fl,&bit_t);

 /*24*/verify_clk_reg(&TIMERS->TIMER[0].LOAD_COUNT ,0x005500aa,&rut,&val_fl,&bit_t);
 /*25*/verify_clk_reg(&TIMERS->TIMER[0].LOAD_COUNT ,0x01,&rut,&val_fl,&bit_t);
 /*26*/verify_clk_reg(&TIMERS->TIMER[1].LOAD_COUNT ,0x005500aa,&rut,&val_fl,&bit_t);
 /*27*/verify_clk_reg(&TIMERS->TIMER[1].LOAD_COUNT ,0x01,&rut,&val_fl,&bit_t);
 /*28*/verify_clk_reg(&TIMERS->TIMER[2].LOAD_COUNT ,0x005500aa,&rut,&val_fl,&bit_t);
 /*29*/verify_clk_reg(&TIMERS->TIMER[2].LOAD_COUNT ,0x01,&rut,&val_fl,&bit_t);
 /*30*/verify_clk_reg(&TIMERS->TIMER[3].LOAD_COUNT ,0x005500aa,&rut,&val_fl,&bit_t);
 /*31*/verify_clk_reg(&TIMERS->TIMER[3].LOAD_COUNT ,0x01,&rut,&val_fl,&bit_t);

/*0*/verify_clk_reg(&TIMERS->TIMER[4].LOAD_COUNT ,0x005500aa,&rut,&val_fl,&bit_t);
/*0*/verify_clk_reg(&TIMERS->TIMER[4].LOAD_COUNT ,0x01,&rut,&val_fl,&bit_t);
/*0*/verify_clk_reg(&TIMERS->TIMER[5].LOAD_COUNT ,0x005500aa,&rut,&val_fl,&bit_t);
/*0*/verify_clk_reg(&TIMERS->TIMER[5].LOAD_COUNT ,0x01,&rut,&val_fl,&bit_t);
/*0*/verify_clk_reg(&TIMERS->TIMER[6].LOAD_COUNT ,0x005500aa,&rut,&val_fl,&bit_t);
/*0*/verify_clk_reg(&TIMERS->TIMER[6].LOAD_COUNT ,0x01,&rut,&val_fl,&bit_t);
/*0*/verify_clk_reg(&TIMERS->TIMER[7].LOAD_COUNT ,0x005500aa,&rut,&val_fl,&bit_t);
/*0*/verify_clk_reg(&TIMERS->TIMER[7].LOAD_COUNT ,0x01,&rut,&val_fl,&bit_t);
 
    // *sut = Verify_SendAppStep(*step,val_fl);
    
    (*step)+=1;
    return (*sut);
}


int main (void)
{
    bool sut = true;
    uint32_t idx=0;
	uint32_t step=0x30;
    uint32_t clk;
    sysTimeUpdataClk(SystemCoreClock);
    Verrify_SendPinConnect(UART0_OUTPUT);
    LOGUartInit();
    c_printf("s_1_628_scu_h_p_clk_96_to_pclk case \r\n");
    c_printf("Simu HCLK96M,PCLK 96M,PClkSelect DIV PCLK \n"); 
    {
        SCU_PClkSelect(HCLK_DIV_2_PCLK);
        MCU_Sleep(1); 
        
        clk = SCU->CLK_CTL;
        clk = P_scu_HClkSelect(CLK_HCLK_MUX,clk);
        clk = P_scu_ClockSelectDivControl(CLK_96M,clk);
        clk = P_scu_PClkPreSelect(HCLK_2_PLCK_PRE,clk);
        SCU->CLK_CTL = clk;
        
        MCU_Sleep(1); 
        verify_clk_rw_IP(&step,&sut,0x11110000+idx++);step++;
        MCU_Sleep(1);
      
    }

	MCU_Sleep(3);
    c_printf("s_1_628_scu_h_p_clk_96_to_pclk case completed \r\n");
    SimulationEnd();
    while(1){     
    };
}















