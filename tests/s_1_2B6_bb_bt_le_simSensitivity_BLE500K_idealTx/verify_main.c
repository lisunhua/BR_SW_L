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
    if (count == 25)
    {
        struct lld_test_params test_params;
        memset(&test_params,0,sizeof(struct lld_test_params));  
		test_params.type        = 0;
		test_params.channel     = 0;
		test_params.data_len    = 1;
		test_params.payload     = 2;//0xAA
		test_params.phy         = 4; 
        co_printf("BLE Enable LRS2 RX, Please Wait!!\r\n");
        lld_test_start(&test_params); 
    }
}