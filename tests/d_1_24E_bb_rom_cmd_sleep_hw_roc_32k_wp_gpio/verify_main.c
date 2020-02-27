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

#include "gpio.h"
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

static void SetwapInt(uint32_t It)
{
    if(It<32)
        SCU->BB_WPL_MASK |= 0x01<<It;
    else
        SCU->BB_WPH_MASK |= 0x01<<(It-32);
    SCU->BB_WP_SEL = 1;  
}

static void v_bm_drv_init(void const *param)
{
    BB->BB_CTL[0] = BB->BB_CTL[0] | 1 << 31/* Set TX Format: Binary Offset */ | 1 << 29/* Set RX Format: Binary Offset */ | 12 << 16/* Clock div for tick_1us */;
    SetwapInt((uint32_t)GPIO10_IRQn);   
    SetwapInt((uint32_t)UART0_IRQn); 
}

static void v_gpio_drv_init(void)
{
    GPIO_InitInfo_Type   GPIO_InitStru;
    PADConfig_Type       pad_InitStru;
    memset(&GPIO_InitStru,0,sizeof(GPIO_InitInfo_Type));
    memset(&pad_InitStru, 0,sizeof(PADConfig_Type));

    pad_InitStru.mode           = PAD_MD_0;
    SystemPADConfig(PADID10,&pad_InitStru);

    SystemDevClockCtl(CLK_EN_GPIO,true);
    SystemDevClockCtl(CLK_EN_GPIOL,true);


    GPIO_InitStru.pin           = GPIO_PIN_10;
    GPIO_InitStru.dir           = GPOP_DIR_IN;
    GPIO_InitStru.int_en        = ENABLE;
    GPIO_InitStru.int_unmask    = ENABLE;
    GPIO_InitStru.int_type      = GPIO_INTTYPE_EDGE;
    GPIO_InitStru.int_pol       = GPIO_INTPOL_ACTIVELOW;
    GPIO_InitStru.debounce_en   = ENABLE;


    GPIO_Init(&GPIO_InitStru);
    NVIC_ClearPendingIRQ(GPIO10_IRQn);
    NVIC_EnableIRQ(GPIO10_IRQn);
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
	s_boot_driver_list[0].func  = v_sys_drv_init;
    s_boot_driver_list[10].func = v_bm_drv_init;
    g_SystemClockEnterLowPower = v_SystemClockLowPowerCtlFunc;

    v_gpio_drv_init();


}

void VerifyMain(uint32_t count){
    //VerifyDualGetRoleHandler();
}




void GPIO10_IRQHandler(void)
{
     GPIO_ClrIntBit(GPIO_PIN_10);
}