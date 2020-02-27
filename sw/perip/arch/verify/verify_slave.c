/*
 *++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 * Copyright (c) 1999-2018 Barrot Technology Limited
 *
 * All rights reserved.
 *
 *------------------------------------------------------------------------------
 */
/**
 * @file verify_slave.c
 * @brief
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

#include <string.h>

#include "cm_printf.h"

#include "verify_message.h"
#include "verify_slave_base.h"
#include "verify_slave_gpio.h"
#include "verify_slave_rtc.h"
#include "verify_slave_wdt.h"
#include "verify_slave_uart.h"
#include "verify_slave_timers.h"
#include "verify_slave_spi.h"
#include "verify_slave_i2c.h"
#include "verify_slave_i2s.h"
#include "verify_slave_dma.h"
#include "verify_slave_scu.h"
#include "verify_slave_usb.h"

typedef bool (*verify_handle)(uint32_t cmd, uint8_t *param_line, uint16_t len);
bool cmd_VerifyTestCase(uint32_t cmd, uint8_t *param_line,uint16_t len);

void Verify_Rust(bool ret);

typedef struct 
{
    uint32_t         cmd;
    verify_handle   handle;
}Verify_CmdInfo;


const Verify_CmdInfo verify_List[]=
{
//----------------------------------------------------------------------------
    {0,cmd_VerifyTestCase},
#ifndef BR_CASE_SPLIT
    //Base
#ifndef BR_DUAL 
    {1,cmd_VerifyBaseHelloCid0x0001},
#endif
		
    {2,cmd_VerifyBaseRamCid0x0002},
    {3,cmd_VerifyBaseRamCid0x0003},
    {4,cmd_VerifyBaseRamCid0x0004},
    {5,cmd_VerifyBaseRamCid0x0005},
    {6,cmd_VerifyBaseRomCid0x0006},
    {7,cmd_VerifyBaseRomCid0x0007},
//----------------------------------------------------------------------------    
    //Register
    {CASE_GPIO_REG      + 1      ,cmd_VerifyRegisterGPIOCasebase},
    {CASE_GPIO_REG      + 2      ,cmd_VerifyRegisterGPIOCase1},    
    {CASE_GPIO_REG      + 3      ,cmd_VerifyRegisterGPIOCasebase1},
    {CASE_GPIO_REG      + 4      ,cmd_VerifyRegisterGPIOCase2},
    //RTC
    {CASE_RTC_REG       + 1      ,cmd_VerifyRegisterRTCCase1},
    {CASE_RTC_REG       + 2      ,cmd_VerifyRegisterRTCCase2},
    //WDT
    {CASE_WDT_REG       + 1      ,cmd_VerifyRegisterWdtCase1},
    {CASE_WDT_REG       + 2      ,cmd_VerifyRegisterWdtCase2},
    //UART
    {CASE_UART0_REG     + 1      ,cmd_VerifyRegisterUart0Case1},//log 
    {CASE_UART0_REG     + 2      ,cmd_VerifyRegisterUart0Case2},//log 
    //UART1
    {CASE_UART1_REG     + 1      ,cmd_VerifyRegisterUart1Case1},
    {CASE_UART1_REG     + 2      ,cmd_VerifyRegisterUart1Case2},
    //I2C
    {CASE_I2C_REG       + 2      ,cmd_VerifyRegisterI2CCase2},
    //I2SM
    {CASE_I2SM_REG      + 2      ,cmd_VerifyRegisterI2smCase2},
    //I2SS
    {CASE_I2SS_REG      + 2      ,cmd_VerifyRegisterI2ssCase2},
    //TIMERS
    {CASE_TIMER_REG     + 1      ,cmd_VerifyRegisterTimersCase1},
    {CASE_TIMER_REG     + 2      ,cmd_VerifyRegisterTimersCase2},
    //SPIM1
    {CASE_SPIM1_REG     + 2      ,cmd_VerifyRegisterSPIM1Case2},
    //SPIM0
    {CASE_SPIM0_REG     + 2      ,cmd_VerifyRegisterSPIM0Case2},
    //SPIS1
    {CASE_SPIS1_REG     + 2      ,cmd_VerifyRegisterSPIS1Case2},
    //DMA
    {CASE_DMA_REG       + 2      ,cmd_VerifyRegisterDMACase2},
    //USB
    {CASE_USB_REG       + 2      ,cmd_VerifyRegisterUSBCase2},
    //SCU
    {CASE_SCU_REG       + 2      ,cmd_VerifyRegisterSCUCase2},

//----------------------------------------------------------------------------    
    //Dual CPU
#ifdef BR_DUAL 
    {1                  + 0	        ,cmd_VerifyBaseHelloCid0x0001},
#endif
    {CASE_UART0_DUL     + 1         ,cmd_VerifyDualAppUART0Case1},
    
    {CASE_UART1_DUL     + 1         ,cmd_VerifyDualAppUART1Case1},
    
    {CASE_I2C_DUL       + 1         ,cmd_VerifyDualAppI2CCase1},
    {CASE_I2C_DUL       + 2         ,cmd_VerifyDualAppI2CCase2},
    
    {CASE_SPIM1_DUL     + 1         ,cmd_VerifyDualAppSPI1Case1},
    {CASE_SPIM1_DUL     + 2         ,cmd_VerifyDualAppSPI1Case2},
    {CASE_SPIM1_DUL     + 3         ,cmd_VerifyDualAppSPI1Case3},
    {CASE_SPIM1_DUL     + 4         ,cmd_VerifyDualAppSPI1Case4},
    {CASE_SPIM1_DUL     + 5         ,cmd_VerifyDualAppSPI1Case5},
    {CASE_SPIM1_DUL     + 6         ,cmd_VerifyDualAppSPI1Case6},
    {CASE_SPIM1_DUL     + 7         ,cmd_VerifyDualAppSPI1Case7},
    {CASE_SPIM1_DUL     + 8         ,cmd_VerifyDualAppSPI1Case8},
    
    {CASE_I2SM_DUL      + 1         ,cmd_VerifyDualAppI2SCase1},
    {CASE_I2SM_DUL      + 2         ,cmd_VerifyDualAppI2SCase2},
    {CASE_I2SM_DUL      + 3         ,cmd_VerifyDualAppI2SCase3},
    {CASE_I2SM_DUL      + 4         ,cmd_VerifyDualAppI2SCase4},
    {CASE_I2SM_DUL      + 5         ,cmd_VerifyDualAppI2SCase5},
    {CASE_I2SM_DUL      + 6         ,cmd_VerifyDualAppI2SCase6},
    {CASE_I2SM_DUL      + 7         ,cmd_VerifyDualAppI2SCase7},
    {CASE_I2SM_DUL      + 8         ,cmd_VerifyDualAppI2SCase8},
    {CASE_I2SM_DUL      + 9         ,cmd_VerifyDualAppI2SCase9},
    {CASE_I2SM_DUL      + 10        ,cmd_VerifyDualAppI2SCase10},
    
    
    
    {CASE_DMA_DUL       + 1         ,cmd_VerifyDualAppDMACase1},//dual cpu
    {CASE_DMA_DUL       + 2         ,cmd_VerifyDualAppDMACase2},//dual cpu
    {CASE_DMA_DUL       + 3         ,cmd_VerifyDualAppDMACase3},

    
//---------------------------------------------------------------------------- 
    // Single CPU
    {CASE_GPIO_SIG      + 1         ,cmd_VerifyAppGPIOCase1},
    {CASE_GPIO_SIG      + 2         ,cmd_VerifyAppGPIOCase2},
    {CASE_GPIO_SIG      + 3         ,cmd_VerifyAppGPIOCase3},
    {CASE_GPIO_SIG      + 4         ,cmd_VerifyAppGPIOCase4},
    {CASE_GPIO_SIG      + 5         ,cmd_VerifyAppGPIOCase5},
    {CASE_GPIO_SIG      + 6         ,cmd_VerifyAppGPIOCase6},
    {CASE_GPIO_SIG      + 7         ,cmd_VerifyAppGPIOCase7},
    
    {CASE_RTC_SIG       + 1         ,cmd_VerifyAppRTCCase1},
    {CASE_RTC_SIG       + 2         ,cmd_VerifyAppRTCCase2},
    {CASE_RTC_SIG       + 3         ,cmd_VerifyAppRTCCase3},
    
    {CASE_WDT_SIG       + 1         ,cmd_VerifyAppWdtCase1},
    {CASE_WDT_SIG       + 2         ,cmd_VerifyAppWdtCase2},
    {CASE_WDT_SIG       + 3         ,cmd_VerifyAppWdtCase3},
    
    {CASE_UART0_SIG     + 1         ,cmd_VerifyAppUART0Case1},
    {CASE_UART0_SIG     + 2         ,cmd_VerifyAppUART0Case2},
    {CASE_UART0_SIG     + 3         ,cmd_VerifyAppUART0Case3},
    {CASE_UART0_SIG     + 4         ,cmd_VerifyAppUART0Case4},
    {CASE_UART0_SIG     + 5         ,cmd_VerifyAppUART0Case5},
    
    {CASE_UART1_SIG     + 1         ,cmd_VerifyAppUART1Case1},
    {CASE_UART1_SIG     + 2         ,cmd_VerifyAppUART1Case2},
    {CASE_UART1_SIG     + 3         ,cmd_VerifyAppUART1Case3},
    {CASE_UART1_SIG     + 4         ,cmd_VerifyAppUART1Case4},
    {CASE_UART1_SIG     + 5         ,cmd_VerifyAppUART1Case5},

    {CASE_I2C_SIG       + 1         ,cmd_VerifyAppI2CCase1},
    {CASE_I2SM_SIG      + 1         ,cmd_VerifyAppI2SMCase1},
    {CASE_SPIM1_SIG     + 1         ,cmd_VerifyAppSPIM1Case1},
     
    {CASE_TIMER_SIG     + 1         ,cmd_VerifyAppTimersCase1},
    {CASE_TIMER_SIG     + 2         ,cmd_VerifyAppTimersCase2},
    {CASE_TIMER_SIG     + 3         ,cmd_VerifyAppTimersCase3},

    
    {CASE_SPIM0_SIG     + 1         ,cmd_VerifyAppSPIM0Case1},
    {CASE_SPIM0_SIG     + 2         ,cmd_VerifyAppSPIM0Case2},
    {CASE_SPIM0_SIG     + 3         ,cmd_VerifyAppSPIM0Case3},
     
    
      
    {CASE_DMA_SIG       + 1         ,cmd_VerifyAppDMACase1},
    {CASE_DMA_SIG       + 2         ,cmd_VerifyAppDMACase2},
    {CASE_DMA_SIG       + 3         ,cmd_VerifyAppDMACase3},
    {CASE_DMA_SIG       + 4         ,cmd_VerifyAppDMACase4},
    {CASE_DMA_SIG       + 5         ,cmd_VerifyAppDMACase5},

       
#if  defined(BR002)||defined(BR003)    
    
    {CASE_SCU_SIG       + 1         ,cmd_VerifyAppSCUCase1},
    {CASE_SCU_SIG       + 2         ,cmd_VerifyAppSCUCase2},
    {CASE_SCU_SIG       + 3         ,cmd_VerifyAppSCUCase3},
    {CASE_SCU_SIG       + 4         ,cmd_VerifyAppSCUCase4},
    {CASE_SCU_SIG       + 5         ,cmd_VerifyAppSCUCase5},
    {CASE_SCU_SIG       + 6         ,cmd_VerifyAppSCUCase6},
    {CASE_SCU_SIG       + 7         ,cmd_VerifyAppSCUCase7},
    {CASE_SCU_SIG       + 8         ,cmd_VerifyAppSCUCase8},
    {CASE_SCU_SIG       + 9         ,cmd_VerifyAppSCUCase9},
    
    {CASE_SCU_SIG       + 10        ,cmd_VerifyAppSCUCase10},//a
    {CASE_SCU_SIG       + 11        ,cmd_VerifyAppSCUCase11},//b
    {CASE_SCU_SIG       + 12        ,cmd_VerifyAppSCUCase12},//c
    {CASE_SCU_SIG       + 13        ,cmd_VerifyAppSCUCase13},//d
    {CASE_SCU_SIG       + 14        ,cmd_VerifyAppSCUCase14},//e
    
    {CASE_SCU_SIG       + 15       ,cmd_VerifyAppSCUCase15},    
    {CASE_SCU_SIG       + 16       ,cmd_VerifyAppSCUCase16},
    {CASE_SCU_SIG       + 17       ,cmd_VerifyAppSCUCase17},   
    {CASE_SCU_SIG       + 18       ,cmd_VerifyAppSCUCase18},  
    {CASE_SCU_SIG       + 19       ,cmd_VerifyAppSCUCase19},
    {CASE_SCU_SIG       + 20       ,cmd_VerifyAppSCUCase20},
    {CASE_SCU_SIG       + 21       ,cmd_VerifyAppSCUCase21},
    {CASE_SCU_SIG       + 22       ,cmd_VerifyAppSCUCase22},   
    {CASE_SCU_SIG       + 23       ,cmd_VerifyAppSCUCase23},      
    {CASE_SCU_SIG       + 24       ,cmd_VerifyAppSCUCase24},
    {CASE_SCU_SIG       + 25       ,cmd_VerifyAppSCUCase25},
    {CASE_SCU_SIG       + 26       ,cmd_VerifyAppSCUCase26},
    {CASE_SCU_SIG       + 27       ,cmd_VerifyAppSCUCase27},
    {CASE_SCU_SIG       + 28       ,cmd_VerifyAppSCUCase28},
    {CASE_SCU_SIG       + 29       ,cmd_VerifyAppSCUCase29},
    {CASE_SCU_SIG       + 30       ,cmd_VerifyAppSCUCase30},
    {CASE_SCU_SIG       + 31       ,cmd_VerifyAppSCUCase31},
    {CASE_SCU_SIG       + 32       ,cmd_VerifyAppSCUCase32},
    {CASE_SCU_SIG       + 33       ,cmd_VerifyAppSCUCase33},
    {CASE_SCU_SIG       + 34       ,cmd_VerifyAppSCUCase34},
    {CASE_SCU_SIG       + 35       ,cmd_VerifyAppSCUCase35},
    {CASE_SCU_SIG       + 36       ,cmd_VerifyAppSCUCase36},
	
    
    
#endif
#endif
};                              


void  Verify_NextCasePream(uint32_t cid)
{
    switch(cid)
    {
        case 0x00: verify_SendRunCaseId(0x02);  break;
        case 0x01: verify_SendRunCaseId(0x02);  break;
        case 0x02: verify_SendRunCaseId(0x03);  break;
        
        default:
            break;
    }
}


void slave_messageSend(uint32_t cmd, uint32_t val)
{
    
#if (defined(BR_MASTER) || defined(BR_SLAVE))
    SCU->SEND_DATA  = val;
    SCU->SEND_CMD   = cmd;
#else
    SCU->READ_DATA  = val;
    SCU->READ_CMD   = cmd;
#endif    
    at_eventInd("Send[%X],[%X]\r\n",cmd,val);
}

#ifdef BR_DUAL 
void VerifyDualGetRoleHandler(void)
{
    SCU->SEND_CMD   = 0;
    SCU->SEND_DATA  = 0xDD01;
    while(SCU->SEND_CMD==0){};    
       
    if(SCU->SEND_CMD==0xDD03)
        SetSocRole(SOC_SLAVE);
    else if(SCU->SEND_CMD==0xDD04)
        SetSocRole(SOC_MASTER);
    else
        cm_printf("Get Rolt Error !\n");    
    SCU->SEND_DATA  =0xDD02;

}

static  void  VerifyDualGetCidToTb(void)
{
    BB->BB_CTL[9] = 0;
    BB->BB_CTL[8] = 1;    
    while(BB->BB_CTL[9]==0){};
        
    if(BB->BB_CTL[9])
        slave_messageSend(0x01,BB->BB_CTL[9]); 
}
#endif


#ifdef BR_NO_UVM
static  void  VerifyNoUvmGetCidToTb(void)
{
    BB->BB_CTL[9] = 0;
    BB->BB_CTL[8] = 1;    
    while(BB->BB_CTL[9]==0){};
        
    if(BB->BB_CTL[9])
        slave_messageSend(0x01,BB->BB_CTL[9]); 
}
#endif 

void VerifySlaveHandle(void)
{
    bool ret = false;
    
    sysTimeUpdataClk(SystemCoreClock);
    
#ifndef BR_DUAL    
#ifdef BR_MASTER 
    Verify_messageSend(BRCASE_DUAL_MST_RDY,true);  
#endif
#ifdef BR_SLAVE
    Verify_messageSend(BRCASE_DUAL_SLV_RDY,true);  
#endif
#else
    VerifyDualGetRoleHandler();
#endif
 
#ifdef SINGLE
    Verify_messageSend(BRCASE_RDY,true);
#endif
 
#if defined(BR_SLAVE)||defined(BR_MASTER)
#ifndef BR_DUAL
    slave_messageSend(0x01,0X160a);   
#else
    VerifyDualGetCidToTb();
#endif
#endif

#ifdef ONLY_NO_UVM   
    slave_messageSend(0x01,0X20a);
#endif    

#ifdef BR_NO_UVM 
    VerifyNoUvmGetCidToTb();
#endif

    while(1)
    {
        if(VerifyIsGo())
        {
            uint32_t index ;
            for(index = 0;index < (sizeof(verify_List) / sizeof(Verify_CmdInfo)); index++) 
            {
                if (verify_List[index].cmd == verify_messageGetRunCid()) {
                    ret = verify_List[index].handle(verify_List[index].cmd,0,0);
                    break;
                }
            }
            Verify_Rust(ret);
        }
        //Verify_NextCasePream(verify_messageGetRunCid());
        //run next case ;  TB control Case,
        //check TB Send Cmd,The function has to go on the lasr row
        Verify_messageCheckRececive();
    }
}



bool cmd_VerifyTestCase(uint32_t cmd, uint8_t *param_line,uint16_t len)
{
    at_eventInd("Verify Test Case... \r\n");
    return true;
}


void Verify_Rust(bool ret)
{
#ifdef  CMD_UART_RUST
    if (ret)
        at_eventInd("OK\r\n");
    else
        at_eventInd("ERROR\r\n");
#endif
}








