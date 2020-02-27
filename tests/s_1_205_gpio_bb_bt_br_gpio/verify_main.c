#include "boot_bluetooth.h"

#include "rwip_config.h" // RW SW configuration

#include "arch.h"      // architectural platform definitions
#include <stdlib.h>    // standard lib functions
#include <stddef.h>    // standard definitions
#include <stdint.h>    // standard integer definition
#include <stdbool.h>   // boolean definition
#include "rwip.h"      // RW SW initialization
#include "dbg.h"
#include "em_map.h"
#include "nvds.h"
#include "BR8051Axx.h"
#include "uart.h"
#include "dma.h"
#include "gpio.h"
#include "verdef.h"
#include "boot_driver.h"
#include "lld.h"

#include "co_hci.h"
#include "hci.h"

#include "rf.h"
#include "ld_test.h"

#include "reg_btcore.h"         // BT core registers
#include "vsimv.h"


void VerifyInit(void){

}


void VerifyMain(uint32_t count)
{
    VerifyDualGetRoleHandler();
    
    if (count == 25) {
        
        GPIO_InitInfo_Type   GPIO_InitStru;
        PADConfig_Type       pad_InitStru;
 

        memset(&GPIO_InitStru,0,sizeof(GPIO_InitInfo_Type));
        memset(&pad_InitStru, 0,sizeof(PADConfig_Type));

        pad_InitStru.mode           = PAD_MD_1;
        SystemPADConfig(PADID10,&pad_InitStru);


        GPIO_InitStru.pin           = GPIO_PIN_10;
        GPIO_InitStru.dir           = GPOP_DIR_OUT;
        GPIO_InitStru.mode          = GPIO_MODE_SOFTWARE;//Cannot Set//
        GPIO_InitStru.int_en        = DISABLE;
        GPIO_InitStru.int_unmask    = DISABLE;
        GPIO_InitStru.int_type      = GPIO_INTTYPE_LEVEL;
        GPIO_InitStru.int_pol       = GPIO_INTPOL_ACTIVELOW;
        GPIO_InitStru.debounce_en   = DISABLE;

        SystemDevClockCtl(CLK_EN_GPIO,true);
        GPIO_Init(&GPIO_InitStru);    
    }
   
}


void GPIO10_IRQHandler(void)
{


    
}