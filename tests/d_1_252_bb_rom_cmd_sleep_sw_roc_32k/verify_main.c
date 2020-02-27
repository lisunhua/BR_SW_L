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

typedef struct {
    uint32_t dpll_sel  : 2;      //[1:0]
    uint32_t pclk_sel  : 1;      //[2]
    uint32_t hclk_sel  : 2;      //[4:3]
    uint32_t spim0_sel : 1;     //[5]
    uint32_t l32k_sel  : 2;      //[7:6]
    uint32_t usb_sel   : 1;      //[8]
    uint32_t uart0_sel : 1;     //[9]
    uint32_t h2p_sel   : 4;      //[13:10]
    uint32_t auto_en_32k   : 1;      //[14]

    uint32_t unused1   : 1;      //[15]
    uint32_t unused2   : 16;
} SCUClkSel_Type;


struct boot_driver_stru {
    void (*func)(void const *);
    void const *param;
};

extern struct boot_driver_stru s_boot_driver_list[];

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

    System32KClockUpdateType(LCT_OSC_24MDIV, 750/* 32000 */);
    SystemCoreClockUpdateType(CCT_PLL_24M);
#endif
}



void v_SystemClockLowPowerCtlFunc(bool enable)
{

#ifndef SLEEP_AUTO_32k
    //enable == true must the first operation.
    static CoreClk_Type preSystemCoreClockType;
    uint32_t clk_sel = SCU->CLK_SEL;
    SCUClkSel_Type  *p_clk_sel = (SCUClkSel_Type *)&clk_sel;

    if (enable) {
        //Record current HCLK type.
        preSystemCoreClockType = p_clk_sel->hclk_sel;
        //Wait for BB turn up the clk_status signal(Mean can use lowpower clock now).
        while (!(SCU->DEV_STATUS & (1 << 8)));
        SystemCoreClockUpdateType(CCT_RCO_32K); //CCT_OSC_24M
        //Disable DPLL to save power
        SCU->ANA_CTL[0] = SCU->ANA_CTL[0] & ~(1 << 23);
    }
    else {
        //Enable DPLL to get high performance.
        SCU->ANA_CTL[0] = SCU->ANA_CTL[0] | 1 << 23;
        delay_us(20); //Sleep 20us to wait for DPLL ready.
        SystemCoreClockUpdateType(preSystemCoreClockType);
    }
#else
    if (enable) 
        SystemDevClockCtl(CLK_EN_BBH, DISABLE); 
    // else
    //     SystemDevClockCtl(CLK_EN_BBH, ENABLE); 
#endif
    
}

//void (*g_SystemClockEnterLowPower)(bool enable);// = SystemClockLowPowerCtlFunc;
extern void (*g_SystemClockEnterLowPower)(bool enable);

void VerifyInit(void){
	s_boot_driver_list[0].func = v_sys_drv_init;

	g_SystemClockEnterLowPower = v_SystemClockLowPowerCtlFunc;
	//void (*g_SystemClockEnterLowPower)(bool enable) = 
}

void VerifyMain(uint32_t count){
    //VerifyDualGetRoleHandler();
}