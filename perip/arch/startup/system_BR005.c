/**************************************************************************//**
 * @file     system_ARMCM3.c
 * @brief    CMSIS Device System Source File for
 *           ARMCM3 Device Series
 * @version  V2.00
 * @date     18. August 2015
 ******************************************************************************/
/* Copyright (c) 2011 - 2015 ARM LIMITED

   All rights reserved.
   Redistribution and use in source and binary forms, with or without
   modification, are permitted provided that the following conditions are met:
   - Redistributions of source code must retain the above copyright
     notice, this list of conditions and the following disclaimer.
   - Redistributions in binary form must reproduce the above copyright
     notice, this list of conditions and the following disclaimer in the
     documentation and/or other materials provided with the distribution.
   - Neither the name of ARM nor the names of its contributors may be used
     to endorse or promote products derived from this software without
     specific prior written permission.
   *
   THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
   AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
   IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
   ARE DISCLAIMED. IN NO EVENT SHALL COPYRIGHT HOLDERS AND CONTRIBUTORS BE
   LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
   CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
   SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
   INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
   CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
   ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
   POSSIBILITY OF SUCH DAMAGE.
   ---------------------------------------------------------------------------*/

#include "BR00x_config.h"
#include "BR00x_clock.h"
/*----------------------------------------------------------------------------
  Define clocks
 *----------------------------------------------------------------------------*/
#define  XTAL            (24000000UL)      /* Oscillator frequency             */

#define  SYSTEM_CLOCK    (1* XTAL)

/*----------------------------------------------------------------------------
  System Core Clock Variable
 *----------------------------------------------------------------------------*/
unsigned long int SystemCoreClock = SYSTEM_CLOCK;  /* System Core Clock Frequency      */

void SystemCoreClockUpdate(unsigned long int clock)
{
    SystemCoreClock = clock;
}

void SystemInit (void)
{
    SystemCoreClock = SYSTEM_CLOCK;
}

void SystemDevClockCtl(CKEnId_Type id, uint8_t enable)
{
   if (enable) {
       SCU->CLK_EN |= 0x01ul << id;
   }
   else {
       SCU->CLK_EN &= ~(0x01ul << id);
   }
}

void SystemDevRstCtl(SwRstId_Type id)
{
    SCU->SW_RST = 1 << id;
    /* The SoC need us set it to zero when reset request is triggered! */
    SCU->SW_RST = 0 << id;
}

void SystemPADConfig(PADId_Type pad_id, PADConfig_Type *config)
{
    SCU->PAD_CFG[pad_id] = ((config->set    &0x01) << 0 | 
                            (config->ie     &0x01) << 1 | 
                            (config->oen    &0x01) << 2 | 
                            (config->ren    &0x01) << 3 | 
                            (config->pad_ctl&0x07) << 4 );
}


void SystemIOConfigQspi(IOConfig_Type *config)
{
    uint32_t cfg = SCU->IO_CONFIG ;
    cfg  &=~(0x07ul<<8|0x07ul<<11|0x07ul<<14|0x07ul<<17);
    cfg  |= (	(config->d0&0x07) << 8  | 
                (config->d1&0x07) << 11 | 
                (config->d2&0x07) << 14 | 
                (config->d3&0x07) << 17 );	
    SCU->IO_CONFIG = cfg ;
}


void SystemIOConfigQspiOne(uint32_t config,PadIoConfig_Type io)
{
    uint32_t cfg = SCU->IO_CONFIG ;
    if(io>3 || config >5)
        return ;
        
    cfg &=~(0x7ul<<(8 + 3*io));
    cfg  |= ((config&0x07) << (8 + 3*io));	
    SCU->IO_CONFIG = cfg ;
}

