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


void VerifyInit(void){

}


void VerifyMain(uint32_t count)
{
    VerifyDualGetRoleHandler();
    if (count == 25)
    {
        struct lld_test_params test_params;

        memset(&test_params,0,sizeof(struct lld_test_params));

        if(GetSocRole())
            test_params.type        = 1;
        else
            test_params.type        = 0;

        test_params.channel         = 0;
        test_params.data_len        = 100;
        test_params.payload         = 2;//0xAA
        test_params.phy             = PHY_1MBPS_BIT;

        if(GetSocRole())
            co_printf("BLE Enable 1Mbps TX, Please Wait!!\r\n");
        else
        {
            co_printf("BLE Enable 1Mbps RX, Please Wait!!\r\n");
        }
        
        lld_test_start(&test_params);
    }
}