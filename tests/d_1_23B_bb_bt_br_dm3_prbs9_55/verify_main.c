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


typedef struct packet_name_stru {
    const char  *str;
    uint16_t    type
} packet_name_t;

packet_name_t PACKET_NAME[] = {
    /* ACL 1M */
    {"DM1",         TST_DM1_TYPE},
    {"DH1",         TST_DH1_TYPE},
    {"AUX1",        TST_AUX1_TYPE},
    {"DM3",         TST_DM3_TYPE},
    {"DH3",         TST_DH3_TYPE},
    {"DM5",         TST_DM5_TYPE},
    {"DH5",         TST_DH5_TYPE},

    /* ACL 2-3M */
    {"2-DH1",       TST_DH1_2_TYPE},
    {"2-DH3",       TST_DH3_2_TYPE},
    {"2-DH5",       TST_DH5_2_TYPE},
    {"3-DH1",       TST_DH1_3_TYPE},
    {"3-DH3",       TST_DH3_3_TYPE},
    {"3-DH5",       TST_DH5_3_TYPE},

    /* SCO */
    {"HV1",         TST_HV1_TYPE},
    {"HV2",         TST_HV2_TYPE},
    {"HV3",         TST_HV3_TYPE},

    /* eSCO 1M */
    {"EV3",         TST_EV3_TYPE},
    {"EV4",         TST_EV4_TYPE},
    {"EV5",         TST_EV5_TYPE},

    /* eSCO 2-3M */
    {"2-EV3",       TST_EV3_2_TYPE},
    {"2-EV5",       TST_EV5_2_TYPE},
    {"3-EV3",       TST_EV3_3_TYPE},
    {"3-EV5",       TST_EV5_3_TYPE},
};

const char *packet_name(uint16_t packet_type)
{
    uint8_t n = 0;

    while ((n < (sizeof(PACKET_NAME) / sizeof(packet_name_t)))
           && (PACKET_NAME[n].type != packet_type)) {
        n++;
    }
    if (n >= (sizeof(PACKET_NAME) / sizeof(packet_name_t))) {
        return NULL;
    }

    return PACKET_NAME[n].str;
}

void VerifyInit(void){

}



void VerifyMain(uint32_t count)
{
    VerifyDualGetRoleHandler();
    if (count == 25) 
    {
        uint8_t status;
        struct ld_test_params par =
        {
            .cnt      = 3,
            .bd       = {0x45, 0x23, 0x01, 0x83, 0x15, 0x00},
            .pkt_tcod = TST_DM3_TYPE,
            .pl_len   = 0,
            .channel  = 0,
            .lt_addr  = 1,
            .pwr_lvl  = RF_POWER_MAX,
            .random   = LD_RAND_MOD_PRBS9,
            .pattern  = 0x55,
        };

        if(GetSocRole())
        {
            status = ld_test_start(LD_TST_MOD_TX, &par);
            co_printf("BR TX ");
        }else 
        {
            status = ld_test_start(LD_TST_MOD_RX, &par);
            co_printf("BR RX ");
        }
        co_printf("Enable, %s(%04X) -- ", packet_name(par.pkt_tcod), par.pkt_tcod);
        switch (par.random)
        {
            case LD_RAND_MOD_PATTEN:
                co_printf("%02X\r\n", par.pattern);
                break;
            case LD_RAND_MOD_PRBS9:
                co_printf("PRBS9\r\n");
                break;
            case LD_RAND_MOD_PRBS15:
                co_printf("PRBS15\r\n");
                break;
            case LD_RAND_MOD_PCM:
                co_printf("PCM\r\n");
                break;
            default:
                break;
        }
    }
}