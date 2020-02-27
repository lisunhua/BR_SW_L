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
#include "verdef.h"
#include "boot_driver.h"
#include "lld.h"

#include "co_hci.h"
#include "hci.h"

#include "rf.h"
#include "ld_test.h"

#include "reg_btcore.h"         // BT core registers
#include "vsimv.h"

struct boot_driver_stru {
    void (*func)(void const *);
    void const *param;
};

struct boot_driver_stru s_boot_driver_list[];

static void v_sys_drv_init(void const *param)
{
#if !(__FPGA_VER__)
    NVIC_SetPriorityGrouping(6);
    SystemDevClockCtl(CLK_EN_RF, ENABLE);  //Enable BB pclk to access BB RFT/Modem REG
    SystemDevClockCtl(CLK_EN_BBP, ENABLE); //Enable BB pclk to access BB RFT/Modem REG
    SystemDevClockCtl(CLK_EN_BBH, ENABLE); //Enable BB hclk to access BB RFT/Modem REG
    SystemDevClockCtl(CLK_EN_BBL, ENABLE); //Enable BB lclk to enable low power support
    delay_us(20); //Delay to make sure clock is stable
    {
         PADConfig_Type pad_config;
         memset(&pad_config,0,sizeof(PADConfig_Type));
         pad_config.mode = PAD_MD_1;
         SystemPADConfig(PADID7, &pad_config);  //external low power clock input; //for tb
         SCU->DATA[1] = 0xE020;                 // TODO  SH //TB Need
    }
    
#ifdef SLEEP_AUTO_32k
    System32KAutoCLKEnCtl(true);
#endif 

    System32KClockUpdateType(LCT_RCO_32K,0);
    SystemCoreClockUpdateType(CCT_PLL_24M);
#endif
}


void v_SystemClockLowPowerCtlFunc(bool enable)
{
    if (enable) {
        while (!(SCU->DEV_STATUS & (1 << 8))); 
    }   
    if (enable) 
        SystemDevClockCtl(CLK_EN_BBH, DISABLE); 
    // else
    //     SystemDevClockCtl(CLK_EN_BBH, ENABLE); 
}

extern void (*g_SystemClockEnterLowPower)(bool enable);

void VerifyInit(void){
	s_boot_driver_list[0].func = v_sys_drv_init;
    g_SystemClockEnterLowPower = v_SystemClockLowPowerCtlFunc;
}

void VerifyMain(uint32_t count){
    //VerifyDualGetRoleHandler();
}