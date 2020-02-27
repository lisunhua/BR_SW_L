/*
 *++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 * Copyright (c) 1999-2018 Barrot Technology Limited
 *
 * All rights reserved.
 *
 *------------------------------------------------------------------------------
 */
/**
 * @file verify_slave_base.c
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

#include "BR00x_config.h"
#include "BR00x_uart.h"
#include "cm_printf.h"


#include "verify_slave_base.h"
#include "verify_slave_gpio.h"
#include "verify_message.h"


#ifdef BASE_DEBUG_LOG
#define baseprf(format, ...) cm_printf(format, ##__VA_ARGS__)
#else
#define baseprf(format, ...)
#endif

//void  UART0_EndSimEnd(void)
//{
//    uint8_t dat[1] = {0x04};
//    UART_WriteData(UART0, dat, 1);
//}


bool cmd_VerifyBaseHelloCid0x0001(uint32_t cmd, uint8_t *param_line,uint16_t len)
{

#if  defined(BR_MASTER) || defined(BR_SLAVE)
#ifndef BR_DUAL
#ifdef BR_MASTER 
    baseprf("MASTER Hello Word!\n"); 
    return true;
#endif
	
#ifdef BR_SLAVE
    baseprf("SLAVR Hello Word!\n"); 
    return true;
#endif
#else
    if(GetSocRole())
        baseprf("MASTER Hello Word!\n"); 
    else
        baseprf("SLAVR Hello Word!\n"); 
    
    Verify_messageSend(BRCASE_RESULT,true);
    return true;
#endif
#else
	baseprf("Hello Word! \r\n"); 
	MCU_Sleep(3);
	Verify_messageSend(BRCASE_RESULT,true);
	return true;
#endif

}

bool cmd_VerifyBaseRamCid0x0002(uint32_t cmd, uint8_t *param_line,uint16_t len)
{
    uint32_t adr =  0x20008000;
    volatile uint32_t *addr = (uint32_t *)adr;
    uint8_t  ram_ksize = 32;
    uint32_t val = 0;
    baseprf("Check RAM:[0x%X],u:[%p]\n",adr,&adr); 
    baseprf("Set RAM\n");
    for(uint32_t i=0;i<0x100*ram_ksize;i++)
    {
        *addr = i;
         addr++;
    }
    baseprf("Get RAM\n");
    addr = (uint32_t *)adr;
    for(uint32_t i=0;i<0x100*ram_ksize;i++)
    {
        val = *addr;
        addr++;
        if(val !=i)
        {
            baseprf("RAM:Error!\n");
            Verify_messageSend(BRCASE_RESULT,false);
            return false;
        }
    }
    baseprf("RAM:Completed!\n");
    Verify_messageSend(BRCASE_RESULT,true);
    return true;
}

bool cmd_VerifyBaseRamCid0x0003(uint32_t cmd, uint8_t *param_line,uint16_t len)
{
    uint32_t adr =  0x08008000;
    volatile uint32_t *addr = (uint32_t *)adr;
    uint8_t  ram_ksize = 32;
    uint32_t val = 0;
    baseprf("Check RAM:[0x%X],u:[%p]\n",adr,&adr);  
    baseprf("Set RAM\n");
    for(uint32_t i=0;i<0x100*ram_ksize;i++)
    {
        *addr = i;
         addr++;
    }
    baseprf("Get RAM\n");
    addr = (uint32_t *)adr;
    for(uint32_t i=0;i<0x100*ram_ksize;i++)
    {
        val = *addr;
        addr++;
        if(val !=i)
        {
            baseprf("RAM:Error!\n");
            Verify_messageSend(BRCASE_RESULT,false);
            return false;
        }
    }
    baseprf("RAM:Completed!\n");
    Verify_messageSend(BRCASE_RESULT,true);
    return true;
}

bool cmd_VerifyBaseRamCid0x0004(uint32_t cmd, uint8_t *param_line,uint16_t len)
{
    uint32_t adr =  0x08000000;
    volatile uint32_t *addr = (uint32_t *)adr;
    uint8_t  ram_ksize = 32;
    uint32_t val = 0;
    baseprf("Check RAM:[0x%X],u:[%p]\n",adr,&adr); 
    baseprf("Set RAM\n");
    for(uint32_t i=0;i<0x100*ram_ksize;i++)
    {
        *addr = i;
         addr++;
    }
    baseprf("Get RAM\n");
    addr = (uint32_t *)adr;
    for(uint32_t i=0;i<0x100*ram_ksize;i++)
    {
        val = *addr;
        addr++;
        if(val !=i)
        {
            baseprf("RAM:Error!\n");
            Verify_messageSend(BRCASE_RESULT,false);
            return false;
        }
    }
    baseprf("RAM:Completed!\n");
    Verify_messageSend(BRCASE_RESULT,true);
    return true;
}

bool cmd_VerifyBaseRamCid0x0005(uint32_t cmd, uint8_t *param_line,uint16_t len)
{
    uint32_t adr =  0x20000000;
    volatile uint32_t *addr = (uint32_t *)adr;
    uint8_t  ram_ksize = 32;
    uint32_t val = 0;
    baseprf("Check RAM:[0x%X],u:[%p]\n",adr,&adr); 
    baseprf("Set RAM\n");
    for(uint32_t i=0;i<0x100*ram_ksize;i++)
    {
        *addr = i;
         addr++;
    }
    baseprf("Get RAM\n");
    addr = (uint32_t *)adr;
    for(uint32_t i=0;i<0x100*ram_ksize;i++)
    {
        val = *addr;
        addr++;
        if(val !=i)
        {
            baseprf("RAM:Error!\n");
            Verify_messageSend(BRCASE_RESULT,false);
            return false;
        }
    }
    baseprf("RAM:Completed!\n");
    Verify_messageSend(BRCASE_RESULT,true);
    return true;
}

bool cmd_VerifyBaseRomCid0x0006(uint32_t cmd, uint8_t *param_line,uint16_t len)
{
    uint32_t adr =  0x14000;
    volatile uint32_t *addr = (uint32_t *)adr;
    uint16_t  ram_ksize = 384;
    uint32_t val = 0;
    
    baseprf("Check ROM:0x[%X]-128K*3\n",adr); 
    baseprf("Set ROM\n");
    for(uint32_t i=0;i<((ram_ksize<<8)-(adr/4));i++)
    {
        *addr = i;
         addr++;
    }
    baseprf("Get ROM\n");
    addr = (uint32_t *)adr;
    for(uint32_t i=0;i<((ram_ksize<<8)-(adr/4));i++)
    {
        val = *addr;
        addr++;
        if(val !=i)
        {
            baseprf("ROM:Error![%X],[%p],[%X]\n",i,addr,*addr);
            Verify_messageSend(BRCASE_RESULT,false);
            return false;
        }
    }
    baseprf("ROM:Completed!\n");
    Verify_messageSend(BRCASE_RESULT,true);
    return true;
}



bool cmd_VerifyBaseRomCid0x0007(uint32_t cmd, uint8_t *param_line,uint16_t len)
{
    uint32_t adr =  0x0;
    volatile uint32_t *addr = (uint32_t *)adr;
    uint16_t  ram_ksize = 384;
    uint32_t val = 0;

    baseprf("Get ROM\n");
    addr = (uint32_t *)adr;
    for(uint32_t i=0;i<((ram_ksize<<8)-(adr/4));i++)
    {
        val = *addr;
        addr++;
    }
    baseprf("ROM G Completed ! [%X]\n",val);
    Verify_messageSend(BRCASE_RESULT,true);
    return true;
}






