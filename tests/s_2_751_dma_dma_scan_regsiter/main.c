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



const RegisterCell dma_RegList[]=
{
#if  defined(BR002)||defined(BR003)
#if 1
//  {read,  write,  Register ID ,register_attr, Register},
    //DMA_Ch0
    {true,  true,   1,   0xFFFFFFFF,      &DMA->CHR[0].SAR},
    {true,  true,   2,   0xFFFFFFFF,      &DMA->CHR[0].DAR},
    {true,  true,   3,   0xFFFFFFFC,      &DMA->CHR[0].LLP},
    {true,  true,   4,   0x1871FFFF,      &DMA->CHR[0].CTL0},
    {true,  true,   5,   0x00001FFF,      &DMA->CHR[0].CTL1},
//    {true,  true,   6,   0xFFFFFFFF,      &DMA->CHR[0].SSTAT},
//    {true,  true,   7,   0xFFFFFFFF,      &DMA->CHR[0].DSTAT},
//    {true,  true,   8,   0xFFFFFFFF,      &DMA->CHR[0].SSTATAR},
//    {true,  true,   9,   0xFFFFFFFF,      &DMA->CHR[0].DSTATAR},
    {true,  true,   10,  0XC00C0FE0,      &DMA->CHR[0].CFG0},
    {true,  true,   11,  0x00007F9F,      &DMA->CHR[0].CFG1},
    
    //DMA_Ch1
    {true,  true,   12,  0xFFFFFFFF,      &DMA->CHR[1].SAR},
    {true,  true,   13,  0xFFFFFFFF,      &DMA->CHR[1].DAR},
    {true,  true,   14,  0xFFFFFFFC,      &DMA->CHR[1].LLP},
    {true,  true,   15,  0x1871FFFF,      &DMA->CHR[1].CTL0},
    {true,  true,   16,  0x00001FFF,      &DMA->CHR[1].CTL1},
//    {true,  true,   17,  0xFFFFFFFF,      &DMA->CHR[1].SSTAT},
//    {true,  true,   18,  0xFFFFFFFF,      &DMA->CHR[1].DSTAT},
//    {true,  true,   19,  0xFFFFFFFF,      &DMA->CHR[1].SSTATAR},
//    {true,  true,   20,  0xFFFFFFFF,      &DMA->CHR[1].DSTATAR},
    {true,  true,   21,  0XC00C0FE0,      &DMA->CHR[1].CFG0},
    {true,  true,   22,  0x00007F9F,      &DMA->CHR[1].CFG1},
    //DMA_Ch2
    {true,  true,   23,  0xFFFFFFFF,      &DMA->CHR[2].SAR},
    {true,  true,   24,  0xFFFFFFFF,      &DMA->CHR[2].DAR},
    {true,  true,   25,  0xFFFFFFFC,      &DMA->CHR[2].LLP},
    {true,  true,   26,  0x1871FFFF,      &DMA->CHR[2].CTL0},
    {true,  true,   27,  0x00001FFF,      &DMA->CHR[2].CTL1},
//    {true,  true,   28,  0xFFFFFFFF,      &DMA->CHR[2].SSTAT},
//    {true,  true,   29,  0xFFFFFFFF,      &DMA->CHR[2].DSTAT},
//    {true,  true,   30,  0xFFFFFFFF,      &DMA->CHR[2].SSTATAR},
//    {true,  true,   31,  0xFFFFFFFF,      &DMA->CHR[2].DSTATAR},
    {true,  true,   32,  0XC00C0FE0,      &DMA->CHR[2].CFG0},
    {true,  true,   33,  0x00007F9F,      &DMA->CHR[2].CFG1},
    //DMA_Ch3
    {true,  true,   34,  0xFFFFFFFF,      &DMA->CHR[3].SAR},
    {true,  true,   35,  0xFFFFFFFF,      &DMA->CHR[3].DAR},
    {true,  true,   36,  0xFFFFFFFC,      &DMA->CHR[3].LLP},
    {true,  true,   37,  0x1871FFFF,      &DMA->CHR[3].CTL0},
    {true,  true,   38,  0x00001FFF,      &DMA->CHR[3].CTL1},
//    {true,  true,   39,  0xFFFFFFFF,      &DMA->CHR[3].SSTAT},
//    {true,  true,   40,  0xFFFFFFFF,      &DMA->CHR[3].DSTAT},
//    {true,  true,   41,  0xFFFFFFFF,      &DMA->CHR[3].SSTATAR},
//    {true,  true,   42,  0xFFFFFFFF,      &DMA->CHR[3].DSTATAR},
    {true,  true,   43,  0XC00C0FE0,      &DMA->CHR[3].CFG0},
    {true,  true,   44,  0x00007F9F,      &DMA->CHR[3].CFG1},
    //DMA_Ch4
    {true,  true,   45,  0xFFFFFFFF,      &DMA->CHR[4].SAR},
    {true,  true,   46,  0xFFFFFFFF,      &DMA->CHR[4].DAR},
    {true,  true,   47,  0xFFFFFFFC,      &DMA->CHR[4].LLP},
    {true,  true,   48,  0x1871FFFF,      &DMA->CHR[4].CTL0},
    {true,  true,   49,  0x00001FFF,      &DMA->CHR[4].CTL1},
//    {true,  true,   50,  0xFFFFFFFF,      &DMA->CHR[4].SSTAT},
//    {true,  true,   51,  0xFFFFFFFF,      &DMA->CHR[4].DSTAT},
//    {true,  true,   52,  0xFFFFFFFF,      &DMA->CHR[4].SSTATAR},
//    {true,  true,   53,  0xFFFFFFFF,      &DMA->CHR[4].DSTATAR},
    {true,  true,   54,  0XC00C0FE0,      &DMA->CHR[4].CFG0},
    {true,  true,   55,  0x00007F9F,      &DMA->CHR[4].CFG1},
    //DMA_Ch5
    {true,  true,   56,  0xFFFFFFFF,      &DMA->CHR[5].SAR},
    {true,  true,   57,  0xFFFFFFFF,      &DMA->CHR[5].DAR},
    {true,  true,   58,  0xFFFFFFFC,      &DMA->CHR[5].LLP},
    {true,  true,   59,  0x1871FFFF,      &DMA->CHR[5].CTL0},
    {true,  true,   60,  0x00001FFF,      &DMA->CHR[5].CTL1},
//    {true,  true,   61,  0xFFFFFFFF,      &DMA->CHR[5].SSTAT},
//    {true,  true,   62,  0xFFFFFFFF,      &DMA->CHR[5].DSTAT},
//    {true,  true,   63,  0xFFFFFFFF,      &DMA->CHR[5].SSTATAR},
//    {true,  true,   64,  0xFFFFFFFF,      &DMA->CHR[5].DSTATAR},
    {true,  true,   65,  0XC00C0FE0,      &DMA->CHR[5].CFG0},
    {true,  true,   66,  0x00007F9F,      &DMA->CHR[5].CFG1},
    //DMA_Ch6
    {true,  true,   67,  0xFFFFFFFF,      &DMA->CHR[6].SAR},
    {true,  true,   68,  0xFFFFFFFF,      &DMA->CHR[6].DAR},
    {true,  true,   69,  0xFFFFFFFC,      &DMA->CHR[6].LLP},
    {true,  true,   70,  0x1871FFFF,      &DMA->CHR[6].CTL0},
    {true,  true,   71,  0x00001FFF,      &DMA->CHR[6].CTL1},
//    {true,  true,   72,  0xFFFFFFFF,      &DMA->CHR[6].SSTAT},
//    {true,  true,   73,  0xFFFFFFFF,      &DMA->CHR[6].DSTAT},
//    {true,  true,   74,  0xFFFFFFFF,      &DMA->CHR[6].SSTATAR},
//    {true,  true,   75,  0xFFFFFFFF,      &DMA->CHR[6].DSTATAR},
    {true,  true,   76,  0XC00C0FE0,      &DMA->CHR[6].CFG0},
    {true,  true,   77,  0x00007F9F,      &DMA->CHR[6].CFG1},
    //DMA_Ch7
    {true,  true,   78,  0xFFFFFFFF,      &DMA->CHR[7].SAR},
    {true,  true,   79,  0xFFFFFFFF,      &DMA->CHR[7].DAR},
    {true,  true,   80,  0xFFFFFFFC,      &DMA->CHR[7].LLP},
    {true,  true,   81,  0x1871FFFF,      &DMA->CHR[7].CTL0},
    {true,  true,   82,  0x00001FFF,      &DMA->CHR[7].CTL1},
//    {true,  true,   83,  0xFFFFFFFF,      &DMA->CHR[7].SSTAT},
//    {true,  true,   84,  0xFFFFFFFF,      &DMA->CHR[7].DSTAT},
//    {true,  true,   85,  0xFFFFFFFF,      &DMA->CHR[7].SSTATAR},
//    {true,  true,   86,  0xFFFFFFFF,      &DMA->CHR[7].DSTATAR},
    {true,  true,   87,  0XC00C0FE0,      &DMA->CHR[7].CFG0},
    {true,  true,   88,  0x00007F9F,      &DMA->CHR[7].CFG1},
 #endif   
    {true,  false,  89,  0x000000FF,      (volatile uint32_t *)&DMA->IR.RST},
    {true,  false,  90,  0x000000FF,      (volatile uint32_t *)&DMA->IR.RSB},
    {true,  false,  91,  0x000000FF,      (volatile uint32_t *)&DMA->IR.RSST},
    {true,  false,  92,  0x000000FF,      (volatile uint32_t *)&DMA->IR.RSDT},
    {true,  false,  93,  0x000000FF,      (volatile uint32_t *)&DMA->IR.RSER},
    
    {true,  false,  94,  0x000000FF,      (volatile uint32_t *)&DMA->IR.ST},
    {true,  false,  95,  0x000000FF,      (volatile uint32_t *)&DMA->IR.SB},
    {true,  false,  96,  0x000000FF,      (volatile uint32_t *)&DMA->IR.SST},
    {true,  false,  97,  0x000000FF,      (volatile uint32_t *)&DMA->IR.SDT},
    {true,  false,  98,  0x000000FF,      (volatile uint32_t *)&DMA->IR.SER},
  
    {true,  true,   99 ,  0x000000FF,      &DMA->IR.MT},
    {true,  true,   100,  0x000000FF,      &DMA->IR.MB},
    {true,  true,   101,  0x000000FF,      &DMA->IR.MST},
    {true,  true,   102,  0x000000FF,      &DMA->IR.MDT},
    {true,  true,   103,  0x000000FF,      &DMA->IR.MR},
    
    {true,  true,   104,  0x000000FF,      &DMA->IR.CT},
    {true,  true,   105,  0x000000FF,      &DMA->IR.CB},
    {true,  true,   106,  0x000000FF,      &DMA->IR.CST},
    {true,  true,   107,  0x000000FF,      &DMA->IR.CDT},
    {true,  true,   108,  0x000000FF,      &DMA->IR.CER},
    {true,  false,  109,  0x0000001F,      (volatile uint32_t *)&DMA->IR.SI},

//    {true,  true,   110,  0x000000FF,      &DMA->SR.RSR},
//    {true,  true,   111,  0x000000FF,      &DMA->SR.RDR},
//    {true,  true,   112,  0x000000FF,      &DMA->SR.SRSR},
//    {true,  true,   113,  0x000000FF,      &DMA->SR.SRDR},
//    {true,  true,   114,  0x000000FF,      &DMA->SR.LSR},
//    {true,  true,   115,  0x000000FF,      &DMA->SR.LDR},
    
    {true,  true,   116,  0x00000001,      &DMA->MR.CFG}, 
    //{true,  true,   117,  0x0000FFFF,      &DMA->MR.EN},//Enable Bit Cannot
#else    
    {true,  true,   117,  0x0000FFFF,      NULL },
#endif
};

int main (void)
{
    sysTimeUpdataClk(SystemCoreClock);
    Verrify_SendPinConnect(UART0_OUTPUT);
    LOGUartInit();
    c_printf("s_2_751_dma_dma_scan_regsiter case \r\n");
    {
        bool sut = true;
        uint32_t idx=0;
       
        SystemDevClockCtl(DMA_CKEn,true);
        sut =Verify_RegisterDAMHandle(dma_RegList,sizeof(dma_RegList),idx);
        Verify_SendCResult(BRCASE_RESULT,sut);
    }
    SimulationEnd();
    while(1){     
    };
}
















