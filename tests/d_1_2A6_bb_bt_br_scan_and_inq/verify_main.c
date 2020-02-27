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
    
    if(GetSocRole())
    {
        if (count == 25) {
            co_printf("Before BR Inquiry Scan Enable\r\n");
            lm_inq_scan_acc_param_set();
            lm_cod_param_set();
            lm_eir_param_set();
            lm_local_name();
            lm_scan_en_param_set();
        }
    }
    else
    {
        if (count == 25) {
            co_printf("Before BR Inquiry Enable\r\n");
            lm_inq_en_param_set();
        }
    }
}