//Automatically generate file.

`include "inputs/soc_top/sim/tb/inc/chip_def.inc"

task iomux_function;

  reg test_error = 0;
  force `DUT_XRM.TEST = 0;

  force `CLK_XRM.presetn_rf =$urandom;

//##################GPIO[0]-------------------------------------
//O
    release  `DUT_XRM.GPIO[0];    force    `UART0_XRM.sout = $urandom;
    force    `IOMUX_XRM.pad_cfg[ 0*8+:8] = 'h0;  
    #100;
    chech_in_function(`DUT_XRM.GPIO[0] , `UART0_XRM.sout , "GPIO[0]" ,'h0 ,test_error ,"OUT");

//I of IO
    release  `GPIO_XRM.gpio_ext_porta[0];    force    `DUT_XRM.GPIO[0] = $urandom;
    force    `IOMUX_XRM.pad_cfg[ 0*8+:8] = 'h10;  
    force    `GPIO_XRM.gpio_porta_ddr[0] = 'b0;    //OEN=1 
    #100;
    chech_in_function(`GPIO_XRM.gpio_ext_porta[0] , `DUT_XRM.GPIO[0] , "GPIO[0]" ,'h10 ,test_error ,"IN");

//O of IO
    release  `DUT_XRM.GPIO[0];    force    `GPIO_XRM.gpio_porta_dr[0] = $urandom;
    force    `IOMUX_XRM.pad_cfg[ 0*8+:8] = 'h10;  
    force    `GPIO_XRM.gpio_porta_ddr[0] = 'b1;    //OEN=0 
    #100;
    chech_in_function(`DUT_XRM.GPIO[0] , `GPIO_XRM.gpio_porta_dr[0] , "GPIO[0]" ,'h10 ,test_error ,"OUT");

//O
    release  `DUT_XRM.GPIO[0];    force    `BTDM_XRM.rf_tx_en = $urandom;
    force    `IOMUX_XRM.pad_cfg[ 0*8+:8] = 'h20;  
    #100;
    chech_in_function(`DUT_XRM.GPIO[0] , `BTDM_XRM.rf_tx_en , "GPIO[0]" ,'h20 ,test_error ,"OUT");

//O
    release  `DUT_XRM.GPIO[0];    force    `UART0_XRM.sout = $urandom;
    force    `IOMUX_XRM.pad_cfg[ 0*8+:8] = 'h30;  
    #100;
    chech_in_function(`DUT_XRM.GPIO[0] , `UART0_XRM.sout , "GPIO[0]" ,'h30 ,test_error ,"OUT");

//O
    release  `DUT_XRM.GPIO[0];    force    `UART0_XRM.sout = $urandom;
    force    `IOMUX_XRM.pad_cfg[ 0*8+:8] = 'h40;  
    #100;
    chech_in_function(`DUT_XRM.GPIO[0] , `UART0_XRM.sout , "GPIO[0]" ,'h40 ,test_error ,"OUT");

//O
    release  `DUT_XRM.GPIO[0];    force    `UART0_XRM.sout = $urandom;
    force    `IOMUX_XRM.pad_cfg[ 0*8+:8] = 'h50;  
    #100;
    chech_in_function(`DUT_XRM.GPIO[0] , `UART0_XRM.sout , "GPIO[0]" ,'h50 ,test_error ,"OUT");

//release
    release `IOMUX_XRM.pad_cfg[ 0*8+:8];
    #100;


//##################GPIO[1]-------------------------------------
//I
    release  `UART0_XRM.sin;    force    `DUT_XRM.GPIO[1] = $urandom;
    force    `IOMUX_XRM.pad_cfg[ 1*8+:8] = 'h0;  
    #100;
    chech_in_function(`UART0_XRM.sin , `DUT_XRM.GPIO[1] , "GPIO[1]" ,'h0 ,test_error ,"IN");

//I of IO
    release  `GPIO_XRM.gpio_ext_porta[1];    force    `DUT_XRM.GPIO[1] = $urandom;
    force    `IOMUX_XRM.pad_cfg[ 1*8+:8] = 'h10;  
    force    `GPIO_XRM.gpio_porta_ddr[1] = 'b0;    //OEN=1 
    #100;
    chech_in_function(`GPIO_XRM.gpio_ext_porta[1] , `DUT_XRM.GPIO[1] , "GPIO[1]" ,'h10 ,test_error ,"IN");

//O of IO
    release  `DUT_XRM.GPIO[1];    force    `GPIO_XRM.gpio_porta_dr[1] = $urandom;
    force    `IOMUX_XRM.pad_cfg[ 1*8+:8] = 'h10;  
    force    `GPIO_XRM.gpio_porta_ddr[1] = 'b1;    //OEN=0 
    #100;
    chech_in_function(`DUT_XRM.GPIO[1] , `GPIO_XRM.gpio_porta_dr[1] , "GPIO[1]" ,'h10 ,test_error ,"OUT");

//O
    release  `DUT_XRM.GPIO[1];    force    `BTDM_XRM.rf_rx_en = $urandom;
    force    `IOMUX_XRM.pad_cfg[ 1*8+:8] = 'h20;  
    #100;
    chech_in_function(`DUT_XRM.GPIO[1] , `BTDM_XRM.rf_rx_en , "GPIO[1]" ,'h20 ,test_error ,"OUT");

//I
    release  `UART0_XRM.sin;    force    `DUT_XRM.GPIO[1] = $urandom;
    force    `IOMUX_XRM.pad_cfg[ 1*8+:8] = 'h30;  
    #100;
    chech_in_function(`UART0_XRM.sin , `DUT_XRM.GPIO[1] , "GPIO[1]" ,'h30 ,test_error ,"IN");

//I
    release  `UART0_XRM.sin;    force    `DUT_XRM.GPIO[1] = $urandom;
    force    `IOMUX_XRM.pad_cfg[ 1*8+:8] = 'h40;  
    #100;
    chech_in_function(`UART0_XRM.sin , `DUT_XRM.GPIO[1] , "GPIO[1]" ,'h40 ,test_error ,"IN");

//I
    release  `UART0_XRM.sin;    force    `DUT_XRM.GPIO[1] = $urandom;
    force    `IOMUX_XRM.pad_cfg[ 1*8+:8] = 'h50;  
    #100;
    chech_in_function(`UART0_XRM.sin , `DUT_XRM.GPIO[1] , "GPIO[1]" ,'h50 ,test_error ,"IN");

//release
    release `IOMUX_XRM.pad_cfg[ 1*8+:8];
    #100;


//##################GPIO[2]-------------------------------------
//O
    release  `DUT_XRM.GPIO[2];    force    `UART0_XRM.rts_n = $urandom;
    force    `IOMUX_XRM.pad_cfg[ 2*8+:8] = 'h0;  
    #100;
    chech_in_function(`DUT_XRM.GPIO[2] , `UART0_XRM.rts_n , "GPIO[2]" ,'h0 ,test_error ,"OUT");

//I of IO
    release  `GPIO_XRM.gpio_ext_porta[2];    force    `DUT_XRM.GPIO[2] = $urandom;
    force    `IOMUX_XRM.pad_cfg[ 2*8+:8] = 'h10;  
    force    `GPIO_XRM.gpio_porta_ddr[2] = 'b0;    //OEN=1 
    #100;
    chech_in_function(`GPIO_XRM.gpio_ext_porta[2] , `DUT_XRM.GPIO[2] , "GPIO[2]" ,'h10 ,test_error ,"IN");

//O of IO
    release  `DUT_XRM.GPIO[2];    force    `GPIO_XRM.gpio_porta_dr[2] = $urandom;
    force    `IOMUX_XRM.pad_cfg[ 2*8+:8] = 'h10;  
    force    `GPIO_XRM.gpio_porta_ddr[2] = 'b1;    //OEN=0 
    #100;
    chech_in_function(`DUT_XRM.GPIO[2] , `GPIO_XRM.gpio_porta_dr[2] , "GPIO[2]" ,'h10 ,test_error ,"OUT");

//O
    release  `DUT_XRM.GPIO[2];    force    `TIMER_XRM.timer_1_toggle = $urandom;
    force    `IOMUX_XRM.pad_cfg[ 2*8+:8] = 'h20;  
    #100;
    chech_in_function(`DUT_XRM.GPIO[2] , `TIMER_XRM.timer_1_toggle , "GPIO[2]" ,'h20 ,test_error ,"OUT");

//O
    release  `DUT_XRM.GPIO[2];    force    `CLK_XRM.clk_12m_bb = $urandom;
    force    `IOMUX_XRM.pad_cfg[ 2*8+:8] = 'h30;  
    #100;
    chech_in_function(`DUT_XRM.GPIO[2] , `CLK_XRM.clk_12m_bb , "GPIO[2]" ,'h30 ,test_error ,"OUT");

//O
    release  `DUT_XRM.GPIO[2];    force    `ANATOP_XRM.RCO_32K_BB = $urandom;
    force    `IOMUX_XRM.pad_cfg[ 2*8+:8] = 'h40;  
    #100;
    chech_in_function(`DUT_XRM.GPIO[2] , `ANATOP_XRM.RCO_32K_BB , "GPIO[2]" ,'h40 ,test_error ,"OUT");

//O
    release  `DUT_XRM.GPIO[2];    force    `BTDM_XRM.bt_dbg_bus[0] = $urandom;
    force    `IOMUX_XRM.pad_cfg[ 2*8+:8] = 'h50;  
    #100;
    chech_in_function(`DUT_XRM.GPIO[2] , `BTDM_XRM.bt_dbg_bus[0] , "GPIO[2]" ,'h50 ,test_error ,"OUT");

//release
    release `IOMUX_XRM.pad_cfg[ 2*8+:8];
    #100;


//##################GPIO[3]-------------------------------------
//I
    release  `UART0_XRM.cts_n;    force    `DUT_XRM.GPIO[3] = $urandom;
    force    `IOMUX_XRM.pad_cfg[ 3*8+:8] = 'h0;  
    #100;
    chech_in_function(`UART0_XRM.cts_n , `DUT_XRM.GPIO[3] , "GPIO[3]" ,'h0 ,test_error ,"IN");

//I of IO
    release  `GPIO_XRM.gpio_ext_porta[3];    force    `DUT_XRM.GPIO[3] = $urandom;
    force    `IOMUX_XRM.pad_cfg[ 3*8+:8] = 'h10;  
    force    `GPIO_XRM.gpio_porta_ddr[3] = 'b0;    //OEN=1 
    #100;
    chech_in_function(`GPIO_XRM.gpio_ext_porta[3] , `DUT_XRM.GPIO[3] , "GPIO[3]" ,'h10 ,test_error ,"IN");

//O of IO
    release  `DUT_XRM.GPIO[3];    force    `GPIO_XRM.gpio_porta_dr[3] = $urandom;
    force    `IOMUX_XRM.pad_cfg[ 3*8+:8] = 'h10;  
    force    `GPIO_XRM.gpio_porta_ddr[3] = 'b1;    //OEN=0 
    #100;
    chech_in_function(`DUT_XRM.GPIO[3] , `GPIO_XRM.gpio_porta_dr[3] , "GPIO[3]" ,'h10 ,test_error ,"OUT");

//O
    release  `DUT_XRM.GPIO[3];    force    `TIMER_XRM.timer_2_toggle = $urandom;
    force    `IOMUX_XRM.pad_cfg[ 3*8+:8] = 'h20;  
    #100;
    chech_in_function(`DUT_XRM.GPIO[3] , `TIMER_XRM.timer_2_toggle , "GPIO[3]" ,'h20 ,test_error ,"OUT");

//O
    release  `DUT_XRM.GPIO[3];    force    `ANA_XRM.CLK_26M_OUT = $urandom;
    force    `IOMUX_XRM.pad_cfg[ 3*8+:8] = 'h30;  
    #100;
    chech_in_function(`DUT_XRM.GPIO[3] , `ANA_XRM.CLK_26M_OUT , "GPIO[3]" ,'h30 ,test_error ,"OUT");

//O
    release  `DUT_XRM.GPIO[3];    force    `QL_XRM.RESETN_RF = $urandom;
    force    `IOMUX_XRM.pad_cfg[ 3*8+:8] = 'h40;  
    #100;
    chech_in_function(`DUT_XRM.GPIO[3] , `QL_XRM.RESETN_RF , "GPIO[3]" ,'h40 ,test_error ,"OUT");

//O
    release  `DUT_XRM.GPIO[3];    force    `BTDM_XRM.bt_dbg_bus[1] = $urandom;
    force    `IOMUX_XRM.pad_cfg[ 3*8+:8] = 'h50;  
    #100;
    chech_in_function(`DUT_XRM.GPIO[3] , `BTDM_XRM.bt_dbg_bus[1] , "GPIO[3]" ,'h50 ,test_error ,"OUT");

//release
    release `IOMUX_XRM.pad_cfg[ 3*8+:8];
    #100;


//##################GPIO[4]-------------------------------------
//I
    release  `M3_XRM.SWCLKTCK;    force    `DUT_XRM.GPIO[4] = $urandom;
    force    `IOMUX_XRM.pad_cfg[ 4*8+:8] = 'h0;  
    #100;
    chech_in_function(`M3_XRM.SWCLKTCK , `DUT_XRM.GPIO[4] , "GPIO[4]" ,'h0 ,test_error ,"IN");

//I of IO
    release  `GPIO_XRM.gpio_ext_porta[4];    force    `DUT_XRM.GPIO[4] = $urandom;
    force    `IOMUX_XRM.pad_cfg[ 4*8+:8] = 'h10;  
    force    `GPIO_XRM.gpio_porta_ddr[4] = 'b0;    //OEN=1 
    #100;
    chech_in_function(`GPIO_XRM.gpio_ext_porta[4] , `DUT_XRM.GPIO[4] , "GPIO[4]" ,'h10 ,test_error ,"IN");

//O of IO
    release  `DUT_XRM.GPIO[4];    force    `GPIO_XRM.gpio_porta_dr[4] = $urandom;
    force    `IOMUX_XRM.pad_cfg[ 4*8+:8] = 'h10;  
    force    `GPIO_XRM.gpio_porta_ddr[4] = 'b1;    //OEN=0 
    #100;
    chech_in_function(`DUT_XRM.GPIO[4] , `GPIO_XRM.gpio_porta_dr[4] , "GPIO[4]" ,'h10 ,test_error ,"OUT");

//O
    release  `DUT_XRM.GPIO[4];    force    `TIMER_XRM.timer_3_toggle = $urandom;
    force    `IOMUX_XRM.pad_cfg[ 4*8+:8] = 'h20;  
    #100;
    chech_in_function(`DUT_XRM.GPIO[4] , `TIMER_XRM.timer_3_toggle , "GPIO[4]" ,'h20 ,test_error ,"OUT");

//I of IO1
    release  `I2C_XRM.ic_clk_in_a;    force    `IOMUX_XRM.pad_cfg[ 4*8+:8] = 'h30;  
    force    `I2C_XRM.ic_clk_oe = 'b0;    //OEN=1 
    #100;
    chech_in_function(`I2C_XRM.ic_clk_in_a , `DUT_XRM.GPIO[4] , "GPIO[4]" ,'h30 ,test_error ,"IN");

//O of IO1
    release  `DUT_XRM.GPIO[4];    force    `IOMUX_XRM.pad_cfg[ 4*8+:8] = 'h30;  
    force    `I2C_XRM.ic_clk_oe = 'b1;    //OEN=0 
    #100;
    chech_in_function(`DUT_XRM.GPIO[4] , `PAD_IPORT_TIE , "GPIO[4]" ,'h30 ,test_error ,"OUT");

//O
    release  `DUT_XRM.GPIO[4];    force    `BTDM_XRM.rf_tx_en = $urandom;
    force    `IOMUX_XRM.pad_cfg[ 4*8+:8] = 'h40;  
    #100;
    chech_in_function(`DUT_XRM.GPIO[4] , `BTDM_XRM.rf_tx_en , "GPIO[4]" ,'h40 ,test_error ,"OUT");

//I
    release  `M3_XRM.SWCLKTCK;    force    `DUT_XRM.GPIO[4] = $urandom;
    force    `IOMUX_XRM.pad_cfg[ 4*8+:8] = 'h50;  
    #100;
    chech_in_function(`M3_XRM.SWCLKTCK , `DUT_XRM.GPIO[4] , "GPIO[4]" ,'h50 ,test_error ,"IN");

//release
    release `IOMUX_XRM.pad_cfg[ 4*8+:8];
    #100;


//##################GPIO[5]-------------------------------------
//I of IO
    release  `M3_XRM.SWDITMS;    force    `DUT_XRM.GPIO[5] = $urandom;
    force    `IOMUX_XRM.pad_cfg[ 5*8+:8] = 'h0;  
    force    `M3_XRM.SWDOEN = 'b0;    //OEN=1 
    #100;
    chech_in_function(`M3_XRM.SWDITMS , `DUT_XRM.GPIO[5] , "GPIO[5]" ,'h0 ,test_error ,"IN");

//O of IO
    release  `DUT_XRM.GPIO[5];    force    `M3_XRM.SWDO = $urandom;
    force    `IOMUX_XRM.pad_cfg[ 5*8+:8] = 'h0;  
    force    `M3_XRM.SWDOEN = 'b1;    //OEN=0 
    #100;
    chech_in_function(`DUT_XRM.GPIO[5] , `M3_XRM.SWDO , "GPIO[5]" ,'h0 ,test_error ,"OUT");

//I of IO
    release  `GPIO_XRM.gpio_ext_porta[5];    force    `DUT_XRM.GPIO[5] = $urandom;
    force    `IOMUX_XRM.pad_cfg[ 5*8+:8] = 'h10;  
    force    `GPIO_XRM.gpio_porta_ddr[5] = 'b0;    //OEN=1 
    #100;
    chech_in_function(`GPIO_XRM.gpio_ext_porta[5] , `DUT_XRM.GPIO[5] , "GPIO[5]" ,'h10 ,test_error ,"IN");

//O of IO
    release  `DUT_XRM.GPIO[5];    force    `GPIO_XRM.gpio_porta_dr[5] = $urandom;
    force    `IOMUX_XRM.pad_cfg[ 5*8+:8] = 'h10;  
    force    `GPIO_XRM.gpio_porta_ddr[5] = 'b1;    //OEN=0 
    #100;
    chech_in_function(`DUT_XRM.GPIO[5] , `GPIO_XRM.gpio_porta_dr[5] , "GPIO[5]" ,'h10 ,test_error ,"OUT");

//O
    release  `DUT_XRM.GPIO[5];    force    `TIMER_XRM.timer_4_toggle = $urandom;
    force    `IOMUX_XRM.pad_cfg[ 5*8+:8] = 'h20;  
    #100;
    chech_in_function(`DUT_XRM.GPIO[5] , `TIMER_XRM.timer_4_toggle , "GPIO[5]" ,'h20 ,test_error ,"OUT");

//I of IO1
    release  `I2C_XRM.ic_data_in_a;    force    `IOMUX_XRM.pad_cfg[ 5*8+:8] = 'h30;  
    force    `I2C_XRM.ic_data_oe = 'b0;    //OEN=1 
    #100;
    chech_in_function(`I2C_XRM.ic_data_in_a , `DUT_XRM.GPIO[5] , "GPIO[5]" ,'h30 ,test_error ,"IN");

//O of IO1
    release  `DUT_XRM.GPIO[5];    force    `IOMUX_XRM.pad_cfg[ 5*8+:8] = 'h30;  
    force    `I2C_XRM.ic_data_oe = 'b1;    //OEN=0 
    #100;
    chech_in_function(`DUT_XRM.GPIO[5] , `PAD_IPORT_TIE , "GPIO[5]" ,'h30 ,test_error ,"OUT");

//O
    release  `DUT_XRM.GPIO[5];    force    `BTDM_XRM.rf_rx_en = $urandom;
    force    `IOMUX_XRM.pad_cfg[ 5*8+:8] = 'h40;  
    #100;
    chech_in_function(`DUT_XRM.GPIO[5] , `BTDM_XRM.rf_rx_en , "GPIO[5]" ,'h40 ,test_error ,"OUT");

//I of IO
    release  `M3_XRM.SWDITMS;    force    `DUT_XRM.GPIO[5] = $urandom;
    force    `IOMUX_XRM.pad_cfg[ 5*8+:8] = 'h50;  
    force    `M3_XRM.SWDOEN = 'b0;    //OEN=1 
    #100;
    chech_in_function(`M3_XRM.SWDITMS , `DUT_XRM.GPIO[5] , "GPIO[5]" ,'h50 ,test_error ,"IN");

//O of IO
    release  `DUT_XRM.GPIO[5];    force    `M3_XRM.SWDO = $urandom;
    force    `IOMUX_XRM.pad_cfg[ 5*8+:8] = 'h50;  
    force    `M3_XRM.SWDOEN = 'b1;    //OEN=0 
    #100;
    chech_in_function(`DUT_XRM.GPIO[5] , `M3_XRM.SWDO , "GPIO[5]" ,'h50 ,test_error ,"OUT");

//release
    release `IOMUX_XRM.pad_cfg[ 5*8+:8];
    #100;


//##################GPIO[6]-------------------------------------
//I of IO
    release  `GPIO_XRM.gpio_ext_porta[6];    force    `DUT_XRM.GPIO[6] = $urandom;
    force    `IOMUX_XRM.pad_cfg[ 6*8+:8] = 'h0;  
    force    `GPIO_XRM.gpio_porta_ddr[6] = 'b0;    //OEN=1 
    #100;
    chech_in_function(`GPIO_XRM.gpio_ext_porta[6] , `DUT_XRM.GPIO[6] , "GPIO[6]" ,'h0 ,test_error ,"IN");

//O of IO
    release  `DUT_XRM.GPIO[6];    force    `GPIO_XRM.gpio_porta_dr[6] = $urandom;
    force    `IOMUX_XRM.pad_cfg[ 6*8+:8] = 'h0;  
    force    `GPIO_XRM.gpio_porta_ddr[6] = 'b1;    //OEN=0 
    #100;
    chech_in_function(`DUT_XRM.GPIO[6] , `GPIO_XRM.gpio_porta_dr[6] , "GPIO[6]" ,'h0 ,test_error ,"OUT");

//O
    release  `DUT_XRM.GPIO[6];    force    `SCU_XRM.lfclk_main_test = $urandom;
    force    `IOMUX_XRM.pad_cfg[ 6*8+:8] = 'h30;  
    #100;
    chech_in_function(`DUT_XRM.GPIO[6] , `SCU_XRM.lfclk_main_test , "GPIO[6]" ,'h30 ,test_error ,"OUT");

//O
    release  `DUT_XRM.GPIO[6];    force    `ANATOP_XRM.DPLL_LOCK = $urandom;
    force    `IOMUX_XRM.pad_cfg[ 6*8+:8] = 'h40;  
    #100;
    chech_in_function(`DUT_XRM.GPIO[6] , `ANATOP_XRM.DPLL_LOCK , "GPIO[6]" ,'h40 ,test_error ,"OUT");

//O
    release  `DUT_XRM.GPIO[6];    force    `BTDM_XRM.bt_dbg_bus[2] = $urandom;
    force    `IOMUX_XRM.pad_cfg[ 6*8+:8] = 'h50;  
    #100;
    chech_in_function(`DUT_XRM.GPIO[6] , `BTDM_XRM.bt_dbg_bus[2] , "GPIO[6]" ,'h50 ,test_error ,"OUT");

//release
    release `IOMUX_XRM.pad_cfg[ 6*8+:8];
    #100;


//##################GPIO[7]-------------------------------------
//I of IO
    release  `GPIO_XRM.gpio_ext_porta[7];    force    `DUT_XRM.GPIO[7] = $urandom;
    force    `IOMUX_XRM.pad_cfg[ 7*8+:8] = 'h0;  
    force    `GPIO_XRM.gpio_porta_ddr[7] = 'b0;    //OEN=1 
    #100;
    chech_in_function(`GPIO_XRM.gpio_ext_porta[7] , `DUT_XRM.GPIO[7] , "GPIO[7]" ,'h0 ,test_error ,"IN");

//O of IO
    release  `DUT_XRM.GPIO[7];    force    `GPIO_XRM.gpio_porta_dr[7] = $urandom;
    force    `IOMUX_XRM.pad_cfg[ 7*8+:8] = 'h0;  
    force    `GPIO_XRM.gpio_porta_ddr[7] = 'b1;    //OEN=0 
    #100;
    chech_in_function(`DUT_XRM.GPIO[7] , `GPIO_XRM.gpio_porta_dr[7] , "GPIO[7]" ,'h0 ,test_error ,"OUT");

//I
    release  `SCU_XRM.osc_32k;    force    `DUT_XRM.GPIO[7] = $urandom;
    force    `IOMUX_XRM.pad_cfg[ 7*8+:8] = 'h10;  
    #100;
    chech_in_function(`SCU_XRM.osc_32k , `DUT_XRM.GPIO[7] , "GPIO[7]" ,'h10 ,test_error ,"IN");

//O
    release  `DUT_XRM.GPIO[7];    force    `TIMER_XRM.timer_1_toggle = $urandom;
    force    `IOMUX_XRM.pad_cfg[ 7*8+:8] = 'h20;  
    #100;
    chech_in_function(`DUT_XRM.GPIO[7] , `TIMER_XRM.timer_1_toggle , "GPIO[7]" ,'h20 ,test_error ,"OUT");

//O
    release  `DUT_XRM.GPIO[7];    force    `CLK_XRM.pclk_en = $urandom;
    force    `IOMUX_XRM.pad_cfg[ 7*8+:8] = 'h30;  
    #100;
    chech_in_function(`DUT_XRM.GPIO[7] , `CLK_XRM.pclk_en , "GPIO[7]" ,'h30 ,test_error ,"OUT");

//O
    release  `DUT_XRM.GPIO[7];    force    `ANATOP_XRM.DPLL_OUT_16M = $urandom;
    force    `IOMUX_XRM.pad_cfg[ 7*8+:8] = 'h40;  
    #100;
    chech_in_function(`DUT_XRM.GPIO[7] , `ANATOP_XRM.DPLL_OUT_16M , "GPIO[7]" ,'h40 ,test_error ,"OUT");

//O
    release  `DUT_XRM.GPIO[7];    force    `BTDM_XRM.bt_dbg_bus[3] = $urandom;
    force    `IOMUX_XRM.pad_cfg[ 7*8+:8] = 'h50;  
    #100;
    chech_in_function(`DUT_XRM.GPIO[7] , `BTDM_XRM.bt_dbg_bus[3] , "GPIO[7]" ,'h50 ,test_error ,"OUT");

//release
    release `IOMUX_XRM.pad_cfg[ 7*8+:8];
    #100;


//##################GPIO[8]-------------------------------------
//I of IO
    release  `GPIO_XRM.gpio_ext_porta[8];    force    `DUT_XRM.GPIO[8] = $urandom;
    force    `IOMUX_XRM.pad_cfg[ 8*8+:8] = 'h0;  
    force    `GPIO_XRM.gpio_porta_ddr[8] = 'b0;    //OEN=1 
    #100;
    chech_in_function(`GPIO_XRM.gpio_ext_porta[8] , `DUT_XRM.GPIO[8] , "GPIO[8]" ,'h0 ,test_error ,"IN");

//O of IO
    release  `DUT_XRM.GPIO[8];    force    `GPIO_XRM.gpio_porta_dr[8] = $urandom;
    force    `IOMUX_XRM.pad_cfg[ 8*8+:8] = 'h0;  
    force    `GPIO_XRM.gpio_porta_ddr[8] = 'b1;    //OEN=0 
    #100;
    chech_in_function(`DUT_XRM.GPIO[8] , `GPIO_XRM.gpio_porta_dr[8] , "GPIO[8]" ,'h0 ,test_error ,"OUT");

//O
    release  `DUT_XRM.GPIO[8];    force    `ANATOP_XRM.DCDC_START_TEST = $urandom;
    force    `IOMUX_XRM.pad_cfg[ 8*8+:8] = 'h10;  
    #100;
    chech_in_function(`DUT_XRM.GPIO[8] , `ANATOP_XRM.DCDC_START_TEST , "GPIO[8]" ,'h10 ,test_error ,"OUT");

//O
    release  `DUT_XRM.GPIO[8];    force    `TIMER_XRM.timer_2_toggle = $urandom;
    force    `IOMUX_XRM.pad_cfg[ 8*8+:8] = 'h20;  
    #100;
    chech_in_function(`DUT_XRM.GPIO[8] , `TIMER_XRM.timer_2_toggle , "GPIO[8]" ,'h20 ,test_error ,"OUT");

//O
    release  `DUT_XRM.GPIO[8];    force    `RST_XRM.hw_rst_n = $urandom;
    force    `IOMUX_XRM.pad_cfg[ 8*8+:8] = 'h30;  
    #100;
    chech_in_function(`DUT_XRM.GPIO[8] , `RST_XRM.hw_rst_n , "GPIO[8]" ,'h30 ,test_error ,"OUT");

//O
    release  `DUT_XRM.GPIO[8];    force    `ANATOP_XRM.RCO32_COARSE_DONE = $urandom;
    force    `IOMUX_XRM.pad_cfg[ 8*8+:8] = 'h40;  
    #100;
    chech_in_function(`DUT_XRM.GPIO[8] , `ANATOP_XRM.RCO32_COARSE_DONE , "GPIO[8]" ,'h40 ,test_error ,"OUT");

//O
    release  `DUT_XRM.GPIO[8];    force    `BTDM_XRM.bt_dbg_bus[4] = $urandom;
    force    `IOMUX_XRM.pad_cfg[ 8*8+:8] = 'h50;  
    #100;
    chech_in_function(`DUT_XRM.GPIO[8] , `BTDM_XRM.bt_dbg_bus[4] , "GPIO[8]" ,'h50 ,test_error ,"OUT");

//release
    release `IOMUX_XRM.pad_cfg[ 8*8+:8];
    #100;


//##################GPIO[9]-------------------------------------
//I of IO
    release  `GPIO_XRM.gpio_ext_porta[9];    force    `DUT_XRM.GPIO[9] = $urandom;
    force    `IOMUX_XRM.pad_cfg[ 9*8+:8] = 'h0;  
    force    `GPIO_XRM.gpio_porta_ddr[9] = 'b0;    //OEN=1 
    #100;
    chech_in_function(`GPIO_XRM.gpio_ext_porta[9] , `DUT_XRM.GPIO[9] , "GPIO[9]" ,'h0 ,test_error ,"IN");

//O of IO
    release  `DUT_XRM.GPIO[9];    force    `GPIO_XRM.gpio_porta_dr[9] = $urandom;
    force    `IOMUX_XRM.pad_cfg[ 9*8+:8] = 'h0;  
    force    `GPIO_XRM.gpio_porta_ddr[9] = 'b1;    //OEN=0 
    #100;
    chech_in_function(`DUT_XRM.GPIO[9] , `GPIO_XRM.gpio_porta_dr[9] , "GPIO[9]" ,'h0 ,test_error ,"OUT");

//O
    release  `DUT_XRM.GPIO[9];    force    `ANATOP_XRM.DCDC_OCP_DET = $urandom;
    force    `IOMUX_XRM.pad_cfg[ 9*8+:8] = 'h10;  
    #100;
    chech_in_function(`DUT_XRM.GPIO[9] , `ANATOP_XRM.DCDC_OCP_DET , "GPIO[9]" ,'h10 ,test_error ,"OUT");

//O
    release  `DUT_XRM.GPIO[9];    force    `TIMER_XRM.timer_3_toggle = $urandom;
    force    `IOMUX_XRM.pad_cfg[ 9*8+:8] = 'h20;  
    #100;
    chech_in_function(`DUT_XRM.GPIO[9] , `TIMER_XRM.timer_3_toggle , "GPIO[9]" ,'h20 ,test_error ,"OUT");

//O
    release  `DUT_XRM.GPIO[9];    force    `RST_XRM.freeclk_rst_n = $urandom;
    force    `IOMUX_XRM.pad_cfg[ 9*8+:8] = 'h30;  
    #100;
    chech_in_function(`DUT_XRM.GPIO[9] , `RST_XRM.freeclk_rst_n , "GPIO[9]" ,'h30 ,test_error ,"OUT");

//O
    release  `DUT_XRM.GPIO[9];    force    `ANATOP_XRM.DCDC_PWM_TEST = $urandom;
    force    `IOMUX_XRM.pad_cfg[ 9*8+:8] = 'h40;  
    #100;
    chech_in_function(`DUT_XRM.GPIO[9] , `ANATOP_XRM.DCDC_PWM_TEST , "GPIO[9]" ,'h40 ,test_error ,"OUT");

//O
    release  `DUT_XRM.GPIO[9];    force    `BTDM_XRM.bt_dbg_bus[5] = $urandom;
    force    `IOMUX_XRM.pad_cfg[ 9*8+:8] = 'h50;  
    #100;
    chech_in_function(`DUT_XRM.GPIO[9] , `BTDM_XRM.bt_dbg_bus[5] , "GPIO[9]" ,'h50 ,test_error ,"OUT");

//release
    release `IOMUX_XRM.pad_cfg[ 9*8+:8];
    #100;


//##################GPIO[10]-------------------------------------
//I of IO
    release  `GPIO_XRM.gpio_ext_porta[10];    force    `DUT_XRM.GPIO[10] = $urandom;
    force    `IOMUX_XRM.pad_cfg[ 10*8+:8] = 'h0;  
    force    `GPIO_XRM.gpio_porta_ddr[10] = 'b0;    //OEN=1 
    #100;
    chech_in_function(`GPIO_XRM.gpio_ext_porta[10] , `DUT_XRM.GPIO[10] , "GPIO[10]" ,'h0 ,test_error ,"IN");

//O of IO
    release  `DUT_XRM.GPIO[10];    force    `GPIO_XRM.gpio_porta_dr[10] = $urandom;
    force    `IOMUX_XRM.pad_cfg[ 10*8+:8] = 'h0;  
    force    `GPIO_XRM.gpio_porta_ddr[10] = 'b1;    //OEN=0 
    #100;
    chech_in_function(`DUT_XRM.GPIO[10] , `GPIO_XRM.gpio_porta_dr[10] , "GPIO[10]" ,'h0 ,test_error ,"OUT");

//O
    release  `DUT_XRM.GPIO[10];    force    `ANATOP_XRM.DCDC_ZCD_TEST = $urandom;
    force    `IOMUX_XRM.pad_cfg[ 10*8+:8] = 'h10;  
    #100;
    chech_in_function(`DUT_XRM.GPIO[10] , `ANATOP_XRM.DCDC_ZCD_TEST , "GPIO[10]" ,'h10 ,test_error ,"OUT");

//O
    release  `DUT_XRM.GPIO[10];    force    `TIMER_XRM.timer_4_toggle = $urandom;
    force    `IOMUX_XRM.pad_cfg[ 10*8+:8] = 'h20;  
    #100;
    chech_in_function(`DUT_XRM.GPIO[10] , `TIMER_XRM.timer_4_toggle , "GPIO[10]" ,'h20 ,test_error ,"OUT");

//O
    release  `DUT_XRM.GPIO[10];    force    `BTDM_XRM.clk_status = $urandom;
    force    `IOMUX_XRM.pad_cfg[ 10*8+:8] = 'h30;  
    #100;
    chech_in_function(`DUT_XRM.GPIO[10] , `BTDM_XRM.clk_status , "GPIO[10]" ,'h30 ,test_error ,"OUT");

//I
    release  `QL_XRM.RESETN_RF;    force    `DUT_XRM.GPIO[10] = $urandom;
    force    `IOMUX_XRM.pad_cfg[ 10*8+:8] = 'h40;  
    #100;
    chech_in_function(`QL_XRM.RESETN_RF , `DUT_XRM.GPIO[10] , "GPIO[10]" ,'h40 ,test_error ,"IN");

//O
    release  `DUT_XRM.GPIO[10];    force    `BTDM_XRM.bt_dbg_bus[6] = $urandom;
    force    `IOMUX_XRM.pad_cfg[ 10*8+:8] = 'h50;  
    #100;
    chech_in_function(`DUT_XRM.GPIO[10] , `BTDM_XRM.bt_dbg_bus[6] , "GPIO[10]" ,'h50 ,test_error ,"OUT");

//release
    release `IOMUX_XRM.pad_cfg[ 10*8+:8];
    #100;


//##################GPIO[11]-------------------------------------
//I of IO
    release  `GPIO_XRM.gpio_ext_porta[11];    force    `DUT_XRM.GPIO[11] = $urandom;
    force    `IOMUX_XRM.pad_cfg[ 11*8+:8] = 'h0;  
    force    `GPIO_XRM.gpio_porta_ddr[11] = 'b0;    //OEN=1 
    #100;
    chech_in_function(`GPIO_XRM.gpio_ext_porta[11] , `DUT_XRM.GPIO[11] , "GPIO[11]" ,'h0 ,test_error ,"IN");

//O of IO
    release  `DUT_XRM.GPIO[11];    force    `GPIO_XRM.gpio_porta_dr[11] = $urandom;
    force    `IOMUX_XRM.pad_cfg[ 11*8+:8] = 'h0;  
    force    `GPIO_XRM.gpio_porta_ddr[11] = 'b1;    //OEN=0 
    #100;
    chech_in_function(`DUT_XRM.GPIO[11] , `GPIO_XRM.gpio_porta_dr[11] , "GPIO[11]" ,'h0 ,test_error ,"OUT");

//I
    release  `SPS1_XRM.sclk_in;    force    `DUT_XRM.GPIO[11] = $urandom;
    force    `IOMUX_XRM.pad_cfg[ 11*8+:8] = 'h10;  
    #100;
    chech_in_function(`SPS1_XRM.sclk_in , `DUT_XRM.GPIO[11] , "GPIO[11]" ,'h10 ,test_error ,"IN");

//O
    release  `DUT_XRM.GPIO[11];    force    `TIMER_XRM.timer_1_toggle = $urandom;
    force    `IOMUX_XRM.pad_cfg[ 11*8+:8] = 'h20;  
    #100;
    chech_in_function(`DUT_XRM.GPIO[11] , `TIMER_XRM.timer_1_toggle , "GPIO[11]" ,'h20 ,test_error ,"OUT");

//O
    release  `DUT_XRM.GPIO[11];    force    `QL_XRM.RESETN_RF = $urandom;
    force    `IOMUX_XRM.pad_cfg[ 11*8+:8] = 'h30;  
    #100;
    chech_in_function(`DUT_XRM.GPIO[11] , `QL_XRM.RESETN_RF , "GPIO[11]" ,'h30 ,test_error ,"OUT");

//I
    release  `QL_XRM.SPI_CLK;    force    `DUT_XRM.GPIO[11] = $urandom;
    force    `IOMUX_XRM.pad_cfg[ 11*8+:8] = 'h40;  
    #100;
    chech_in_function(`QL_XRM.SPI_CLK , `DUT_XRM.GPIO[11] , "GPIO[11]" ,'h40 ,test_error ,"IN");

//O
    release  `DUT_XRM.GPIO[11];    force    `BTDM_XRM.bt_dbg_bus[7] = $urandom;
    force    `IOMUX_XRM.pad_cfg[ 11*8+:8] = 'h50;  
    #100;
    chech_in_function(`DUT_XRM.GPIO[11] , `BTDM_XRM.bt_dbg_bus[7] , "GPIO[11]" ,'h50 ,test_error ,"OUT");

//release
    release `IOMUX_XRM.pad_cfg[ 11*8+:8];
    #100;


//##################GPIO[12]-------------------------------------
//I of IO
    release  `GPIO_XRM.gpio_ext_porta[12];    force    `DUT_XRM.GPIO[12] = $urandom;
    force    `IOMUX_XRM.pad_cfg[ 12*8+:8] = 'h0;  
    force    `GPIO_XRM.gpio_porta_ddr[12] = 'b0;    //OEN=1 
    #100;
    chech_in_function(`GPIO_XRM.gpio_ext_porta[12] , `DUT_XRM.GPIO[12] , "GPIO[12]" ,'h0 ,test_error ,"IN");

//O of IO
    release  `DUT_XRM.GPIO[12];    force    `GPIO_XRM.gpio_porta_dr[12] = $urandom;
    force    `IOMUX_XRM.pad_cfg[ 12*8+:8] = 'h0;  
    force    `GPIO_XRM.gpio_porta_ddr[12] = 'b1;    //OEN=0 
    #100;
    chech_in_function(`DUT_XRM.GPIO[12] , `GPIO_XRM.gpio_porta_dr[12] , "GPIO[12]" ,'h0 ,test_error ,"OUT");

//I
    release  `SPS1_XRM.ss_in_n;    force    `DUT_XRM.GPIO[12] = $urandom;
    force    `IOMUX_XRM.pad_cfg[ 12*8+:8] = 'h10;  
    #100;
    chech_in_function(`SPS1_XRM.ss_in_n , `DUT_XRM.GPIO[12] , "GPIO[12]" ,'h10 ,test_error ,"IN");

//O
    release  `DUT_XRM.GPIO[12];    force    `TIMER_XRM.timer_2_toggle = $urandom;
    force    `IOMUX_XRM.pad_cfg[ 12*8+:8] = 'h20;  
    #100;
    chech_in_function(`DUT_XRM.GPIO[12] , `TIMER_XRM.timer_2_toggle , "GPIO[12]" ,'h20 ,test_error ,"OUT");

//O
    release  `DUT_XRM.GPIO[12];    force    `CLK_XRM.hclk_main_test = $urandom;
    force    `IOMUX_XRM.pad_cfg[ 12*8+:8] = 'h30;  
    #100;
    chech_in_function(`DUT_XRM.GPIO[12] , `CLK_XRM.hclk_main_test , "GPIO[12]" ,'h30 ,test_error ,"OUT");

//I
    release  `QL_XRM.SPI_CSN;    force    `DUT_XRM.GPIO[12] = $urandom;
    force    `IOMUX_XRM.pad_cfg[ 12*8+:8] = 'h40;  
    #100;
    chech_in_function(`QL_XRM.SPI_CSN , `DUT_XRM.GPIO[12] , "GPIO[12]" ,'h40 ,test_error ,"IN");

//O
    release  `DUT_XRM.GPIO[12];    force    `BTDM_XRM.bt_dbg_bus[8] = $urandom;
    force    `IOMUX_XRM.pad_cfg[ 12*8+:8] = 'h50;  
    #100;
    chech_in_function(`DUT_XRM.GPIO[12] , `BTDM_XRM.bt_dbg_bus[8] , "GPIO[12]" ,'h50 ,test_error ,"OUT");

//release
    release `IOMUX_XRM.pad_cfg[ 12*8+:8];
    #100;


//##################GPIO[13]-------------------------------------
//I of IO
    release  `GPIO_XRM.gpio_ext_porta[13];    force    `DUT_XRM.GPIO[13] = $urandom;
    force    `IOMUX_XRM.pad_cfg[ 13*8+:8] = 'h0;  
    force    `GPIO_XRM.gpio_porta_ddr[13] = 'b0;    //OEN=1 
    #100;
    chech_in_function(`GPIO_XRM.gpio_ext_porta[13] , `DUT_XRM.GPIO[13] , "GPIO[13]" ,'h0 ,test_error ,"IN");

//O of IO
    release  `DUT_XRM.GPIO[13];    force    `GPIO_XRM.gpio_porta_dr[13] = $urandom;
    force    `IOMUX_XRM.pad_cfg[ 13*8+:8] = 'h0;  
    force    `GPIO_XRM.gpio_porta_ddr[13] = 'b1;    //OEN=0 
    #100;
    chech_in_function(`DUT_XRM.GPIO[13] , `GPIO_XRM.gpio_porta_dr[13] , "GPIO[13]" ,'h0 ,test_error ,"OUT");

//O
    release  `DUT_XRM.GPIO[13];    force    `SPS1_XRM.txd = $urandom;
    force    `IOMUX_XRM.pad_cfg[ 13*8+:8] = 'h10;  
    #100;
    chech_in_function(`DUT_XRM.GPIO[13] , `SPS1_XRM.txd , "GPIO[13]" ,'h10 ,test_error ,"OUT");

//O
    release  `DUT_XRM.GPIO[13];    force    `TIMER_XRM.timer_3_toggle = $urandom;
    force    `IOMUX_XRM.pad_cfg[ 13*8+:8] = 'h20;  
    #100;
    chech_in_function(`DUT_XRM.GPIO[13] , `TIMER_XRM.timer_3_toggle , "GPIO[13]" ,'h20 ,test_error ,"OUT");

//O
    release  `DUT_XRM.GPIO[13];    force    `CLK_XRM.usb_clk_test = $urandom;
    force    `IOMUX_XRM.pad_cfg[ 13*8+:8] = 'h30;  
    #100;
    chech_in_function(`DUT_XRM.GPIO[13] , `CLK_XRM.usb_clk_test , "GPIO[13]" ,'h30 ,test_error ,"OUT");

//I
    release  `QL_XRM.SPI_DI;    force    `DUT_XRM.GPIO[13] = $urandom;
    force    `IOMUX_XRM.pad_cfg[ 13*8+:8] = 'h40;  
    #100;
    chech_in_function(`QL_XRM.SPI_DI , `DUT_XRM.GPIO[13] , "GPIO[13]" ,'h40 ,test_error ,"IN");

//O
    release  `DUT_XRM.GPIO[13];    force    `BTDM_XRM.bt_dbg_bus[9] = $urandom;
    force    `IOMUX_XRM.pad_cfg[ 13*8+:8] = 'h50;  
    #100;
    chech_in_function(`DUT_XRM.GPIO[13] , `BTDM_XRM.bt_dbg_bus[9] , "GPIO[13]" ,'h50 ,test_error ,"OUT");

//release
    release `IOMUX_XRM.pad_cfg[ 13*8+:8];
    #100;


//##################GPIO[14]-------------------------------------
//I of IO
    release  `GPIO_XRM.gpio_ext_porta[14];    force    `DUT_XRM.GPIO[14] = $urandom;
    force    `IOMUX_XRM.pad_cfg[ 14*8+:8] = 'h0;  
    force    `GPIO_XRM.gpio_porta_ddr[14] = 'b0;    //OEN=1 
    #100;
    chech_in_function(`GPIO_XRM.gpio_ext_porta[14] , `DUT_XRM.GPIO[14] , "GPIO[14]" ,'h0 ,test_error ,"IN");

//O of IO
    release  `DUT_XRM.GPIO[14];    force    `GPIO_XRM.gpio_porta_dr[14] = $urandom;
    force    `IOMUX_XRM.pad_cfg[ 14*8+:8] = 'h0;  
    force    `GPIO_XRM.gpio_porta_ddr[14] = 'b1;    //OEN=0 
    #100;
    chech_in_function(`DUT_XRM.GPIO[14] , `GPIO_XRM.gpio_porta_dr[14] , "GPIO[14]" ,'h0 ,test_error ,"OUT");

//I
    release  `SPS1_XRM.rxd;    force    `DUT_XRM.GPIO[14] = $urandom;
    force    `IOMUX_XRM.pad_cfg[ 14*8+:8] = 'h10;  
    #100;
    chech_in_function(`SPS1_XRM.rxd , `DUT_XRM.GPIO[14] , "GPIO[14]" ,'h10 ,test_error ,"IN");

//O
    release  `DUT_XRM.GPIO[14];    force    `TIMER_XRM.timer_4_toggle = $urandom;
    force    `IOMUX_XRM.pad_cfg[ 14*8+:8] = 'h20;  
    #100;
    chech_in_function(`DUT_XRM.GPIO[14] , `TIMER_XRM.timer_4_toggle , "GPIO[14]" ,'h20 ,test_error ,"OUT");

//O
    release  `DUT_XRM.GPIO[14];    force    `CLK_XRM.pclk_main_test = $urandom;
    force    `IOMUX_XRM.pad_cfg[ 14*8+:8] = 'h30;  
    #100;
    chech_in_function(`DUT_XRM.GPIO[14] , `CLK_XRM.pclk_main_test , "GPIO[14]" ,'h30 ,test_error ,"OUT");

//O
    release  `DUT_XRM.GPIO[14];    force    `QL_XRM.SPI_DO = $urandom;
    force    `IOMUX_XRM.pad_cfg[ 14*8+:8] = 'h40;  
    #100;
    chech_in_function(`DUT_XRM.GPIO[14] , `QL_XRM.SPI_DO , "GPIO[14]" ,'h40 ,test_error ,"OUT");

//O
    release  `DUT_XRM.GPIO[14];    force    `BTDM_XRM.bt_dbg_bus[10] = $urandom;
    force    `IOMUX_XRM.pad_cfg[ 14*8+:8] = 'h50;  
    #100;
    chech_in_function(`DUT_XRM.GPIO[14] , `BTDM_XRM.bt_dbg_bus[10] , "GPIO[14]" ,'h50 ,test_error ,"OUT");

//release
    release `IOMUX_XRM.pad_cfg[ 14*8+:8];
    #100;


//##################GPIO[15]-------------------------------------
//I of IO
    release  `GPIO_XRM.gpio_ext_porta[15];    force    `DUT_XRM.GPIO[15] = $urandom;
    force    `IOMUX_XRM.pad_cfg[ 15*8+:8] = 'h0;  
    force    `GPIO_XRM.gpio_porta_ddr[15] = 'b0;    //OEN=1 
    #100;
    chech_in_function(`GPIO_XRM.gpio_ext_porta[15] , `DUT_XRM.GPIO[15] , "GPIO[15]" ,'h0 ,test_error ,"IN");

//O of IO
    release  `DUT_XRM.GPIO[15];    force    `GPIO_XRM.gpio_porta_dr[15] = $urandom;
    force    `IOMUX_XRM.pad_cfg[ 15*8+:8] = 'h0;  
    force    `GPIO_XRM.gpio_porta_ddr[15] = 'b1;    //OEN=0 
    #100;
    chech_in_function(`DUT_XRM.GPIO[15] , `GPIO_XRM.gpio_porta_dr[15] , "GPIO[15]" ,'h0 ,test_error ,"OUT");

//O
    release  `DUT_XRM.GPIO[15];    force    `UART1_XRM.sout = $urandom;
    force    `IOMUX_XRM.pad_cfg[ 15*8+:8] = 'h10;  
    #100;
    chech_in_function(`DUT_XRM.GPIO[15] , `UART1_XRM.sout , "GPIO[15]" ,'h10 ,test_error ,"OUT");

//O
    release  `DUT_XRM.GPIO[15];    force    `SPM1_XRM.sclk_out = $urandom;
    force    `IOMUX_XRM.pad_cfg[ 15*8+:8] = 'h20;  
    #100;
    chech_in_function(`DUT_XRM.GPIO[15] , `SPM1_XRM.sclk_out , "GPIO[15]" ,'h20 ,test_error ,"OUT");

//I
    release  `SPS1_XRM.sclk_in;    force    `DUT_XRM.GPIO[15] = $urandom;
    force    `IOMUX_XRM.pad_cfg[ 15*8+:8] = 'h30;  
    #100;
    chech_in_function(`SPS1_XRM.sclk_in , `DUT_XRM.GPIO[15] , "GPIO[15]" ,'h30 ,test_error ,"IN");

//O
    release  `DUT_XRM.GPIO[15];    force    `QL_XRM.BB_RX_PKD_SAT = $urandom;
    force    `IOMUX_XRM.pad_cfg[ 15*8+:8] = 'h40;  
    #100;
    chech_in_function(`DUT_XRM.GPIO[15] , `QL_XRM.BB_RX_PKD_SAT , "GPIO[15]" ,'h40 ,test_error ,"OUT");

//O
    release  `DUT_XRM.GPIO[15];    force    `BTDM_XRM.bt_dbg_bus[11] = $urandom;
    force    `IOMUX_XRM.pad_cfg[ 15*8+:8] = 'h50;  
    #100;
    chech_in_function(`DUT_XRM.GPIO[15] , `BTDM_XRM.bt_dbg_bus[11] , "GPIO[15]" ,'h50 ,test_error ,"OUT");

//release
    release `IOMUX_XRM.pad_cfg[ 15*8+:8];
    #100;


//##################GPIO[16]-------------------------------------
//I of IO
    release  `GPIO_XRM.gpio_ext_porta[16];    force    `DUT_XRM.GPIO[16] = $urandom;
    force    `IOMUX_XRM.pad_cfg[ 16*8+:8] = 'h0;  
    force    `GPIO_XRM.gpio_porta_ddr[16] = 'b0;    //OEN=1 
    #100;
    chech_in_function(`GPIO_XRM.gpio_ext_porta[16] , `DUT_XRM.GPIO[16] , "GPIO[16]" ,'h0 ,test_error ,"IN");

//O of IO
    release  `DUT_XRM.GPIO[16];    force    `GPIO_XRM.gpio_porta_dr[16] = $urandom;
    force    `IOMUX_XRM.pad_cfg[ 16*8+:8] = 'h0;  
    force    `GPIO_XRM.gpio_porta_ddr[16] = 'b1;    //OEN=0 
    #100;
    chech_in_function(`DUT_XRM.GPIO[16] , `GPIO_XRM.gpio_porta_dr[16] , "GPIO[16]" ,'h0 ,test_error ,"OUT");

//I
    release  `UART1_XRM.sin;    force    `DUT_XRM.GPIO[16] = $urandom;
    force    `IOMUX_XRM.pad_cfg[ 16*8+:8] = 'h10;  
    #100;
    chech_in_function(`UART1_XRM.sin , `DUT_XRM.GPIO[16] , "GPIO[16]" ,'h10 ,test_error ,"IN");

//O
    release  `DUT_XRM.GPIO[16];    force    `SPM1_XRM.ss_0_n = $urandom;
    force    `IOMUX_XRM.pad_cfg[ 16*8+:8] = 'h20;  
    #100;
    chech_in_function(`DUT_XRM.GPIO[16] , `SPM1_XRM.ss_0_n , "GPIO[16]" ,'h20 ,test_error ,"OUT");

//I
    release  `SPS1_XRM.ss_in_n;    force    `DUT_XRM.GPIO[16] = $urandom;
    force    `IOMUX_XRM.pad_cfg[ 16*8+:8] = 'h30;  
    #100;
    chech_in_function(`SPS1_XRM.ss_in_n , `DUT_XRM.GPIO[16] , "GPIO[16]" ,'h30 ,test_error ,"IN");

//I
    release  `BT_XRM.CLK_EXT_IN;    force    `DUT_XRM.GPIO[16] = $urandom;
    force    `IOMUX_XRM.pad_cfg[ 16*8+:8] = 'h40;  
    #100;
    chech_in_function(`BT_XRM.CLK_EXT_IN , `DUT_XRM.GPIO[16] , "GPIO[16]" ,'h40 ,test_error ,"IN");

//O
    release  `DUT_XRM.GPIO[16];    force    `BTDM_XRM.bt_dbg_bus[12] = $urandom;
    force    `IOMUX_XRM.pad_cfg[ 16*8+:8] = 'h50;  
    #100;
    chech_in_function(`DUT_XRM.GPIO[16] , `BTDM_XRM.bt_dbg_bus[12] , "GPIO[16]" ,'h50 ,test_error ,"OUT");

//release
    release `IOMUX_XRM.pad_cfg[ 16*8+:8];
    #100;


//##################GPIO[17]-------------------------------------
//I of IO
    release  `GPIO_XRM.gpio_ext_porta[17];    force    `DUT_XRM.GPIO[17] = $urandom;
    force    `IOMUX_XRM.pad_cfg[ 17*8+:8] = 'h0;  
    force    `GPIO_XRM.gpio_porta_ddr[17] = 'b0;    //OEN=1 
    #100;
    chech_in_function(`GPIO_XRM.gpio_ext_porta[17] , `DUT_XRM.GPIO[17] , "GPIO[17]" ,'h0 ,test_error ,"IN");

//O of IO
    release  `DUT_XRM.GPIO[17];    force    `GPIO_XRM.gpio_porta_dr[17] = $urandom;
    force    `IOMUX_XRM.pad_cfg[ 17*8+:8] = 'h0;  
    force    `GPIO_XRM.gpio_porta_ddr[17] = 'b1;    //OEN=0 
    #100;
    chech_in_function(`DUT_XRM.GPIO[17] , `GPIO_XRM.gpio_porta_dr[17] , "GPIO[17]" ,'h0 ,test_error ,"OUT");

//I of IO1
    release  `I2C_XRM.ic_clk_in_a;    force    `IOMUX_XRM.pad_cfg[ 17*8+:8] = 'h10;  
    force    `I2C_XRM.ic_clk_oe = 'b0;    //OEN=1 
    #100;
    chech_in_function(`I2C_XRM.ic_clk_in_a , `DUT_XRM.GPIO[17] , "GPIO[17]" ,'h10 ,test_error ,"IN");

//O of IO1
    release  `DUT_XRM.GPIO[17];    force    `IOMUX_XRM.pad_cfg[ 17*8+:8] = 'h10;  
    force    `I2C_XRM.ic_clk_oe = 'b1;    //OEN=0 
    #100;
    chech_in_function(`DUT_XRM.GPIO[17] , `PAD_IPORT_TIE , "GPIO[17]" ,'h10 ,test_error ,"OUT");

//I
    release  `SPM1_XRM.rxd;    force    `DUT_XRM.GPIO[17] = $urandom;
    force    `IOMUX_XRM.pad_cfg[ 17*8+:8] = 'h20;  
    #100;
    chech_in_function(`SPM1_XRM.rxd , `DUT_XRM.GPIO[17] , "GPIO[17]" ,'h20 ,test_error ,"IN");

//O
    release  `DUT_XRM.GPIO[17];    force    `SPS1_XRM.txd = $urandom;
    force    `IOMUX_XRM.pad_cfg[ 17*8+:8] = 'h30;  
    #100;
    chech_in_function(`DUT_XRM.GPIO[17] , `SPS1_XRM.txd , "GPIO[17]" ,'h30 ,test_error ,"OUT");

//O
    release  `DUT_XRM.GPIO[17];    force    `USB_XRM.utmifs_tx_dp = $urandom;
    force    `IOMUX_XRM.pad_cfg[ 17*8+:8] = 'h40;  
    #100;
    chech_in_function(`DUT_XRM.GPIO[17] , `USB_XRM.utmifs_tx_dp , "GPIO[17]" ,'h40 ,test_error ,"OUT");

//O
    release  `DUT_XRM.GPIO[17];    force    `BTDM_XRM.bt_dbg_bus[13] = $urandom;
    force    `IOMUX_XRM.pad_cfg[ 17*8+:8] = 'h50;  
    #100;
    chech_in_function(`DUT_XRM.GPIO[17] , `BTDM_XRM.bt_dbg_bus[13] , "GPIO[17]" ,'h50 ,test_error ,"OUT");

//release
    release `IOMUX_XRM.pad_cfg[ 17*8+:8];
    #100;


//##################GPIO[18]-------------------------------------
//I of IO
    release  `GPIO_XRM.gpio_ext_porta[18];    force    `DUT_XRM.GPIO[18] = $urandom;
    force    `IOMUX_XRM.pad_cfg[ 18*8+:8] = 'h0;  
    force    `GPIO_XRM.gpio_porta_ddr[18] = 'b0;    //OEN=1 
    #100;
    chech_in_function(`GPIO_XRM.gpio_ext_porta[18] , `DUT_XRM.GPIO[18] , "GPIO[18]" ,'h0 ,test_error ,"IN");

//O of IO
    release  `DUT_XRM.GPIO[18];    force    `GPIO_XRM.gpio_porta_dr[18] = $urandom;
    force    `IOMUX_XRM.pad_cfg[ 18*8+:8] = 'h0;  
    force    `GPIO_XRM.gpio_porta_ddr[18] = 'b1;    //OEN=0 
    #100;
    chech_in_function(`DUT_XRM.GPIO[18] , `GPIO_XRM.gpio_porta_dr[18] , "GPIO[18]" ,'h0 ,test_error ,"OUT");

//I of IO1
    release  `I2C_XRM.ic_data_in_a;    force    `IOMUX_XRM.pad_cfg[ 18*8+:8] = 'h10;  
    force    `I2C_XRM.ic_data_oe = 'b0;    //OEN=1 
    #100;
    chech_in_function(`I2C_XRM.ic_data_in_a , `DUT_XRM.GPIO[18] , "GPIO[18]" ,'h10 ,test_error ,"IN");

//O of IO1
    release  `DUT_XRM.GPIO[18];    force    `IOMUX_XRM.pad_cfg[ 18*8+:8] = 'h10;  
    force    `I2C_XRM.ic_data_oe = 'b1;    //OEN=0 
    #100;
    chech_in_function(`DUT_XRM.GPIO[18] , `PAD_IPORT_TIE , "GPIO[18]" ,'h10 ,test_error ,"OUT");

//O
    release  `DUT_XRM.GPIO[18];    force    `SPM1_XRM.txd = $urandom;
    force    `IOMUX_XRM.pad_cfg[ 18*8+:8] = 'h20;  
    #100;
    chech_in_function(`DUT_XRM.GPIO[18] , `SPM1_XRM.txd , "GPIO[18]" ,'h20 ,test_error ,"OUT");

//I
    release  `SPS1_XRM.rxd;    force    `DUT_XRM.GPIO[18] = $urandom;
    force    `IOMUX_XRM.pad_cfg[ 18*8+:8] = 'h30;  
    #100;
    chech_in_function(`SPS1_XRM.rxd , `DUT_XRM.GPIO[18] , "GPIO[18]" ,'h30 ,test_error ,"IN");

//O
    release  `DUT_XRM.GPIO[18];    force    `USB_XRM.utmifs_tx_dm = $urandom;
    force    `IOMUX_XRM.pad_cfg[ 18*8+:8] = 'h40;  
    #100;
    chech_in_function(`DUT_XRM.GPIO[18] , `USB_XRM.utmifs_tx_dm , "GPIO[18]" ,'h40 ,test_error ,"OUT");

//O
    release  `DUT_XRM.GPIO[18];    force    `BTDM_XRM.bt_dbg_bus[14] = $urandom;
    force    `IOMUX_XRM.pad_cfg[ 18*8+:8] = 'h50;  
    #100;
    chech_in_function(`DUT_XRM.GPIO[18] , `BTDM_XRM.bt_dbg_bus[14] , "GPIO[18]" ,'h50 ,test_error ,"OUT");

//release
    release `IOMUX_XRM.pad_cfg[ 18*8+:8];
    #100;


//##################GPIO[19]-------------------------------------
//I of IO
    release  `GPIO_XRM.gpio_ext_porta[19];    force    `DUT_XRM.GPIO[19] = $urandom;
    force    `IOMUX_XRM.pad_cfg[ 19*8+:8] = 'h0;  
    force    `GPIO_XRM.gpio_porta_ddr[19] = 'b0;    //OEN=1 
    #100;
    chech_in_function(`GPIO_XRM.gpio_ext_porta[19] , `DUT_XRM.GPIO[19] , "GPIO[19]" ,'h0 ,test_error ,"IN");

//O of IO
    release  `DUT_XRM.GPIO[19];    force    `GPIO_XRM.gpio_porta_dr[19] = $urandom;
    force    `IOMUX_XRM.pad_cfg[ 19*8+:8] = 'h0;  
    force    `GPIO_XRM.gpio_porta_ddr[19] = 'b1;    //OEN=0 
    #100;
    chech_in_function(`DUT_XRM.GPIO[19] , `GPIO_XRM.gpio_porta_dr[19] , "GPIO[19]" ,'h0 ,test_error ,"OUT");

//I of IO
    release  `AUDIO_XRM.pcmclk_in;    force    `DUT_XRM.GPIO[19] = $urandom;
    force    `IOMUX_XRM.pad_cfg[ 19*8+:8] = 'h10;  
    force    `AUDIO_XRM.pcmclk_en = 'b0;    //OEN=1 
    #100;
    chech_in_function(`AUDIO_XRM.pcmclk_in , `DUT_XRM.GPIO[19] , "GPIO[19]" ,'h10 ,test_error ,"IN");

//O of IO
    release  `DUT_XRM.GPIO[19];    force    `AUDIO_XRM.pcmclk_out = $urandom;
    force    `IOMUX_XRM.pad_cfg[ 19*8+:8] = 'h10;  
    force    `AUDIO_XRM.pcmclk_en = 'b1;    //OEN=0 
    #100;
    chech_in_function(`DUT_XRM.GPIO[19] , `AUDIO_XRM.pcmclk_out , "GPIO[19]" ,'h10 ,test_error ,"OUT");

//I of IO
    release  `I2SS_XRM.sclk;    force    `DUT_XRM.GPIO[19] = $urandom;
    force    `IOMUX_XRM.pad_cfg[ 19*8+:8] = 'h20;  
    force    `SCUREG_XRM.io_config[4] = 'b0;    //OEN=1 
    #100;
    chech_in_function(`I2SS_XRM.sclk , `DUT_XRM.GPIO[19] , "GPIO[19]" ,'h20 ,test_error ,"IN");

//O of IO
    release  `DUT_XRM.GPIO[19];    force    `SYS_XRM.i2sm_sclk_out = $urandom;
    force    `IOMUX_XRM.pad_cfg[ 19*8+:8] = 'h20;  
    force    `SCUREG_XRM.io_config[4] = 'b1;    //OEN=0 
    #100;
    chech_in_function(`DUT_XRM.GPIO[19] , `SYS_XRM.i2sm_sclk_out , "GPIO[19]" ,'h20 ,test_error ,"OUT");

//O
    release  `DUT_XRM.GPIO[19];    force    `UART1_XRM.sout = $urandom;
    force    `IOMUX_XRM.pad_cfg[ 19*8+:8] = 'h30;  
    #100;
    chech_in_function(`DUT_XRM.GPIO[19] , `UART1_XRM.sout , "GPIO[19]" ,'h30 ,test_error ,"OUT");

//O
    release  `DUT_XRM.GPIO[19];    force    `USB_XRM.utmifs_tx_enable_n = $urandom;
    force    `IOMUX_XRM.pad_cfg[ 19*8+:8] = 'h40;  
    #100;
    chech_in_function(`DUT_XRM.GPIO[19] , `USB_XRM.utmifs_tx_enable_n , "GPIO[19]" ,'h40 ,test_error ,"OUT");

//O
    release  `DUT_XRM.GPIO[19];    force    `BTDM_XRM.bt_dbg_bus[15] = $urandom;
    force    `IOMUX_XRM.pad_cfg[ 19*8+:8] = 'h50;  
    #100;
    chech_in_function(`DUT_XRM.GPIO[19] , `BTDM_XRM.bt_dbg_bus[15] , "GPIO[19]" ,'h50 ,test_error ,"OUT");

//release
    release `IOMUX_XRM.pad_cfg[ 19*8+:8];
    #100;


//##################GPIO[20]-------------------------------------
//I of IO
    release  `GPIO_XRM.gpio_ext_porta[20];    force    `DUT_XRM.GPIO[20] = $urandom;
    force    `IOMUX_XRM.pad_cfg[ 20*8+:8] = 'h0;  
    force    `GPIO_XRM.gpio_porta_ddr[20] = 'b0;    //OEN=1 
    #100;
    chech_in_function(`GPIO_XRM.gpio_ext_porta[20] , `DUT_XRM.GPIO[20] , "GPIO[20]" ,'h0 ,test_error ,"IN");

//O of IO
    release  `DUT_XRM.GPIO[20];    force    `GPIO_XRM.gpio_porta_dr[20] = $urandom;
    force    `IOMUX_XRM.pad_cfg[ 20*8+:8] = 'h0;  
    force    `GPIO_XRM.gpio_porta_ddr[20] = 'b1;    //OEN=0 
    #100;
    chech_in_function(`DUT_XRM.GPIO[20] , `GPIO_XRM.gpio_porta_dr[20] , "GPIO[20]" ,'h0 ,test_error ,"OUT");

//I of IO
    release  `AUDIO_XRM.pcmfsync_in;    force    `DUT_XRM.GPIO[20] = $urandom;
    force    `IOMUX_XRM.pad_cfg[ 20*8+:8] = 'h10;  
    force    `AUDIO_XRM.pcmfsync_en = 'b0;    //OEN=1 
    #100;
    chech_in_function(`AUDIO_XRM.pcmfsync_in , `DUT_XRM.GPIO[20] , "GPIO[20]" ,'h10 ,test_error ,"IN");

//O of IO
    release  `DUT_XRM.GPIO[20];    force    `AUDIO_XRM.pcmfsync_out = $urandom;
    force    `IOMUX_XRM.pad_cfg[ 20*8+:8] = 'h10;  
    force    `AUDIO_XRM.pcmfsync_en = 'b1;    //OEN=0 
    #100;
    chech_in_function(`DUT_XRM.GPIO[20] , `AUDIO_XRM.pcmfsync_out , "GPIO[20]" ,'h10 ,test_error ,"OUT");

//I of IO
    release  `I2SS_XRM.ws_slv;    force    `DUT_XRM.GPIO[20] = $urandom;
    force    `IOMUX_XRM.pad_cfg[ 20*8+:8] = 'h20;  
    force    `SCUREG_XRM.io_config[4] = 'b0;    //OEN=1 
    #100;
    chech_in_function(`I2SS_XRM.ws_slv , `DUT_XRM.GPIO[20] , "GPIO[20]" ,'h20 ,test_error ,"IN");

//O of IO
    release  `DUT_XRM.GPIO[20];    force    `I2SM_XRM.ws_out = $urandom;
    force    `IOMUX_XRM.pad_cfg[ 20*8+:8] = 'h20;  
    force    `SCUREG_XRM.io_config[4] = 'b1;    //OEN=0 
    #100;
    chech_in_function(`DUT_XRM.GPIO[20] , `I2SM_XRM.ws_out , "GPIO[20]" ,'h20 ,test_error ,"OUT");

//I
    release  `UART1_XRM.sin;    force    `DUT_XRM.GPIO[20] = $urandom;
    force    `IOMUX_XRM.pad_cfg[ 20*8+:8] = 'h30;  
    #100;
    chech_in_function(`UART1_XRM.sin , `DUT_XRM.GPIO[20] , "GPIO[20]" ,'h30 ,test_error ,"IN");

//O
    release  `DUT_XRM.GPIO[20];    force    `USB_XRM.utmi_suspend_n = $urandom;
    force    `IOMUX_XRM.pad_cfg[ 20*8+:8] = 'h40;  
    #100;
    chech_in_function(`DUT_XRM.GPIO[20] , `USB_XRM.utmi_suspend_n , "GPIO[20]" ,'h40 ,test_error ,"OUT");

//O
    release  `DUT_XRM.GPIO[20];    force    `AON_XRM.bb_wakeup_req = $urandom;
    force    `IOMUX_XRM.pad_cfg[ 20*8+:8] = 'h50;  
    #100;
    chech_in_function(`DUT_XRM.GPIO[20] , `AON_XRM.bb_wakeup_req , "GPIO[20]" ,'h50 ,test_error ,"OUT");

//release
    release `IOMUX_XRM.pad_cfg[ 20*8+:8];
    #100;


//##################GPIO[21]-------------------------------------
//I of IO
    release  `GPIO_XRM.gpio_ext_porta[21];    force    `DUT_XRM.GPIO[21] = $urandom;
    force    `IOMUX_XRM.pad_cfg[ 21*8+:8] = 'h0;  
    force    `GPIO_XRM.gpio_porta_ddr[21] = 'b0;    //OEN=1 
    #100;
    chech_in_function(`GPIO_XRM.gpio_ext_porta[21] , `DUT_XRM.GPIO[21] , "GPIO[21]" ,'h0 ,test_error ,"IN");

//O of IO
    release  `DUT_XRM.GPIO[21];    force    `GPIO_XRM.gpio_porta_dr[21] = $urandom;
    force    `IOMUX_XRM.pad_cfg[ 21*8+:8] = 'h0;  
    force    `GPIO_XRM.gpio_porta_ddr[21] = 'b1;    //OEN=0 
    #100;
    chech_in_function(`DUT_XRM.GPIO[21] , `GPIO_XRM.gpio_porta_dr[21] , "GPIO[21]" ,'h0 ,test_error ,"OUT");

//I
    release  `AUDIO_XRM.pcmdin;    force    `DUT_XRM.GPIO[21] = $urandom;
    force    `IOMUX_XRM.pad_cfg[ 21*8+:8] = 'h10;  
    #100;
    chech_in_function(`AUDIO_XRM.pcmdin , `DUT_XRM.GPIO[21] , "GPIO[21]" ,'h10 ,test_error ,"IN");

//I of IO
    release  `I2SS_XRM.sdi0;    force    `DUT_XRM.GPIO[21] = $urandom;
    force    `IOMUX_XRM.pad_cfg[ 21*8+:8] = 'h20;  
    force    `SCUREG_XRM.io_config[4] = 'b0;    //OEN=1 
    #100;
    chech_in_function(`I2SS_XRM.sdi0 , `DUT_XRM.GPIO[21] , "GPIO[21]" ,'h20 ,test_error ,"IN");

//O of IO
    release  `DUT_XRM.GPIO[21];    force    `I2SM_XRM.sdo0 = $urandom;
    force    `IOMUX_XRM.pad_cfg[ 21*8+:8] = 'h20;  
    force    `SCUREG_XRM.io_config[4] = 'b1;    //OEN=0 
    #100;
    chech_in_function(`DUT_XRM.GPIO[21] , `I2SM_XRM.sdo0 , "GPIO[21]" ,'h20 ,test_error ,"OUT");

//O
    release  `DUT_XRM.GPIO[21];    force    `BTDM_XRM.rf_tx_en = $urandom;
    force    `IOMUX_XRM.pad_cfg[ 21*8+:8] = 'h30;  
    #100;
    chech_in_function(`DUT_XRM.GPIO[21] , `BTDM_XRM.rf_tx_en , "GPIO[21]" ,'h30 ,test_error ,"OUT");

//O
    release  `DUT_XRM.GPIO[21];    force    `USB_XRM.utmifs_fs_edge_sel = $urandom;
    force    `IOMUX_XRM.pad_cfg[ 21*8+:8] = 'h40;  
    #100;
    chech_in_function(`DUT_XRM.GPIO[21] , `USB_XRM.utmifs_fs_edge_sel , "GPIO[21]" ,'h40 ,test_error ,"OUT");

//O
    release  `DUT_XRM.GPIO[21];    force    `BB_XRM.osc_en = $urandom;
    force    `IOMUX_XRM.pad_cfg[ 21*8+:8] = 'h50;  
    #100;
    chech_in_function(`DUT_XRM.GPIO[21] , `BB_XRM.osc_en , "GPIO[21]" ,'h50 ,test_error ,"OUT");

//release
    release `IOMUX_XRM.pad_cfg[ 21*8+:8];
    #100;


//##################GPIO[22]-------------------------------------
//I of IO
    release  `GPIO_XRM.gpio_ext_porta[22];    force    `DUT_XRM.GPIO[22] = $urandom;
    force    `IOMUX_XRM.pad_cfg[ 22*8+:8] = 'h0;  
    force    `GPIO_XRM.gpio_porta_ddr[22] = 'b0;    //OEN=1 
    #100;
    chech_in_function(`GPIO_XRM.gpio_ext_porta[22] , `DUT_XRM.GPIO[22] , "GPIO[22]" ,'h0 ,test_error ,"IN");

//O of IO
    release  `DUT_XRM.GPIO[22];    force    `GPIO_XRM.gpio_porta_dr[22] = $urandom;
    force    `IOMUX_XRM.pad_cfg[ 22*8+:8] = 'h0;  
    force    `GPIO_XRM.gpio_porta_ddr[22] = 'b1;    //OEN=0 
    #100;
    chech_in_function(`DUT_XRM.GPIO[22] , `GPIO_XRM.gpio_porta_dr[22] , "GPIO[22]" ,'h0 ,test_error ,"OUT");

//O1
    release  `DUT_XRM.GPIO[22];    force    `AUDIO_XRM.pcmdout = $urandom;
    force    `IOMUX_XRM.pad_cfg[ 22*8+:8] = 'h10;  
    force    `AUDIO_XRM.pcmdout_en = 'b1;    //OEN=0 
    #100;
    chech_in_function(`DUT_XRM.GPIO[22] , `AUDIO_XRM.pcmdout , "GPIO[22]" ,'h10 ,test_error ,"OUT");

//I of IO
    release  `I2SM_XRM.sdi0;    force    `DUT_XRM.GPIO[22] = $urandom;
    force    `IOMUX_XRM.pad_cfg[ 22*8+:8] = 'h20;  
    force    `SCUREG_XRM.io_config[4] = 'b1;    //OEN=1 
    #100;
    chech_in_function(`I2SM_XRM.sdi0 , `DUT_XRM.GPIO[22] , "GPIO[22]" ,'h20 ,test_error ,"IN");

//O of IO
    release  `DUT_XRM.GPIO[22];    force    `I2SS_XRM.sdo0 = $urandom;
    force    `IOMUX_XRM.pad_cfg[ 22*8+:8] = 'h20;  
    force    `SCUREG_XRM.io_config[4] = 'b0;    //OEN=0 
    #100;
    chech_in_function(`DUT_XRM.GPIO[22] , `I2SS_XRM.sdo0 , "GPIO[22]" ,'h20 ,test_error ,"OUT");

//O
    release  `DUT_XRM.GPIO[22];    force    `BTDM_XRM.rf_rx_en = $urandom;
    force    `IOMUX_XRM.pad_cfg[ 22*8+:8] = 'h30;  
    #100;
    chech_in_function(`DUT_XRM.GPIO[22] , `BTDM_XRM.rf_rx_en , "GPIO[22]" ,'h30 ,test_error ,"OUT");

//O
    release  `DUT_XRM.GPIO[22];    force    `USB_XRM.usb_up_p_en = $urandom;
    force    `IOMUX_XRM.pad_cfg[ 22*8+:8] = 'h40;  
    #100;
    chech_in_function(`DUT_XRM.GPIO[22] , `USB_XRM.usb_up_p_en , "GPIO[22]" ,'h40 ,test_error ,"OUT");

//O
    release  `DUT_XRM.GPIO[22];    force    `BB_XRM.clk_status = $urandom;
    force    `IOMUX_XRM.pad_cfg[ 22*8+:8] = 'h50;  
    #100;
    chech_in_function(`DUT_XRM.GPIO[22] , `BB_XRM.clk_status , "GPIO[22]" ,'h50 ,test_error ,"OUT");

//release
    release `IOMUX_XRM.pad_cfg[ 22*8+:8];
    #100;


//##################GPIO[23]-------------------------------------
//I of IO
    release  `GPIO_XRM.gpio_ext_porta[23];    force    `DUT_XRM.GPIO[23] = $urandom;
    force    `IOMUX_XRM.pad_cfg[ 23*8+:8] = 'h0;  
    force    `GPIO_XRM.gpio_porta_ddr[23] = 'b0;    //OEN=1 
    #100;
    chech_in_function(`GPIO_XRM.gpio_ext_porta[23] , `DUT_XRM.GPIO[23] , "GPIO[23]" ,'h0 ,test_error ,"IN");

//O of IO
    release  `DUT_XRM.GPIO[23];    force    `GPIO_XRM.gpio_porta_dr[23] = $urandom;
    force    `IOMUX_XRM.pad_cfg[ 23*8+:8] = 'h0;  
    force    `GPIO_XRM.gpio_porta_ddr[23] = 'b1;    //OEN=0 
    #100;
    chech_in_function(`DUT_XRM.GPIO[23] , `GPIO_XRM.gpio_porta_dr[23] , "GPIO[23]" ,'h0 ,test_error ,"OUT");

//O
    release  `DUT_XRM.GPIO[23];    force    `SPM1_XRM.sclk_out = $urandom;
    force    `IOMUX_XRM.pad_cfg[ 23*8+:8] = 'h10;  
    #100;
    chech_in_function(`DUT_XRM.GPIO[23] , `SPM1_XRM.sclk_out , "GPIO[23]" ,'h10 ,test_error ,"OUT");

//I of IO
    release  `AUDIO_XRM.pcmclk_in;    force    `DUT_XRM.GPIO[23] = $urandom;
    force    `IOMUX_XRM.pad_cfg[ 23*8+:8] = 'h20;  
    force    `AUDIO_XRM.pcmclk_en = 'b0;    //OEN=1 
    #100;
    chech_in_function(`AUDIO_XRM.pcmclk_in , `DUT_XRM.GPIO[23] , "GPIO[23]" ,'h20 ,test_error ,"IN");

//O of IO
    release  `DUT_XRM.GPIO[23];    force    `AUDIO_XRM.pcmclk_out = $urandom;
    force    `IOMUX_XRM.pad_cfg[ 23*8+:8] = 'h20;  
    force    `AUDIO_XRM.pcmclk_en = 'b1;    //OEN=0 
    #100;
    chech_in_function(`DUT_XRM.GPIO[23] , `AUDIO_XRM.pcmclk_out , "GPIO[23]" ,'h20 ,test_error ,"OUT");

//I of IO
    release  `I2SS_XRM.sclk;    force    `DUT_XRM.GPIO[23] = $urandom;
    force    `IOMUX_XRM.pad_cfg[ 23*8+:8] = 'h30;  
    force    `SCUREG_XRM.io_config[5] = 'b0;    //OEN=1 
    #100;
    chech_in_function(`I2SS_XRM.sclk , `DUT_XRM.GPIO[23] , "GPIO[23]" ,'h30 ,test_error ,"IN");

//O of IO
    release  `DUT_XRM.GPIO[23];    force    `SYS_XRM.i2sm_sclk_out = $urandom;
    force    `IOMUX_XRM.pad_cfg[ 23*8+:8] = 'h30;  
    force    `SCUREG_XRM.io_config[5] = 'b1;    //OEN=0 
    #100;
    chech_in_function(`DUT_XRM.GPIO[23] , `SYS_XRM.i2sm_sclk_out , "GPIO[23]" ,'h30 ,test_error ,"OUT");

//O
    release  `DUT_XRM.GPIO[23];    force    `USB_XRM.usb_up_m_en = $urandom;
    force    `IOMUX_XRM.pad_cfg[ 23*8+:8] = 'h40;  
    #100;
    chech_in_function(`DUT_XRM.GPIO[23] , `USB_XRM.usb_up_m_en , "GPIO[23]" ,'h40 ,test_error ,"OUT");

//O
    release  `DUT_XRM.GPIO[23];    force    `BTDM_XRM.bt_dbg_bus[16] = $urandom;
    force    `IOMUX_XRM.pad_cfg[ 23*8+:8] = 'h50;  
    #100;
    chech_in_function(`DUT_XRM.GPIO[23] , `BTDM_XRM.bt_dbg_bus[16] , "GPIO[23]" ,'h50 ,test_error ,"OUT");

//release
    release `IOMUX_XRM.pad_cfg[ 23*8+:8];
    #100;


//##################GPIO[24]-------------------------------------
//I of IO
    release  `GPIO_XRM.gpio_ext_porta[24];    force    `DUT_XRM.GPIO[24] = $urandom;
    force    `IOMUX_XRM.pad_cfg[ 24*8+:8] = 'h0;  
    force    `GPIO_XRM.gpio_porta_ddr[24] = 'b0;    //OEN=1 
    #100;
    chech_in_function(`GPIO_XRM.gpio_ext_porta[24] , `DUT_XRM.GPIO[24] , "GPIO[24]" ,'h0 ,test_error ,"IN");

//O of IO
    release  `DUT_XRM.GPIO[24];    force    `GPIO_XRM.gpio_porta_dr[24] = $urandom;
    force    `IOMUX_XRM.pad_cfg[ 24*8+:8] = 'h0;  
    force    `GPIO_XRM.gpio_porta_ddr[24] = 'b1;    //OEN=0 
    #100;
    chech_in_function(`DUT_XRM.GPIO[24] , `GPIO_XRM.gpio_porta_dr[24] , "GPIO[24]" ,'h0 ,test_error ,"OUT");

//O
    release  `DUT_XRM.GPIO[24];    force    `SPM1_XRM.ss_0_n = $urandom;
    force    `IOMUX_XRM.pad_cfg[ 24*8+:8] = 'h10;  
    #100;
    chech_in_function(`DUT_XRM.GPIO[24] , `SPM1_XRM.ss_0_n , "GPIO[24]" ,'h10 ,test_error ,"OUT");

//I of IO
    release  `AUDIO_XRM.pcmfsync_in;    force    `DUT_XRM.GPIO[24] = $urandom;
    force    `IOMUX_XRM.pad_cfg[ 24*8+:8] = 'h20;  
    force    `AUDIO_XRM.pcmfsync_en = 'b0;    //OEN=1 
    #100;
    chech_in_function(`AUDIO_XRM.pcmfsync_in , `DUT_XRM.GPIO[24] , "GPIO[24]" ,'h20 ,test_error ,"IN");

//O of IO
    release  `DUT_XRM.GPIO[24];    force    `AUDIO_XRM.pcmfsync_out = $urandom;
    force    `IOMUX_XRM.pad_cfg[ 24*8+:8] = 'h20;  
    force    `AUDIO_XRM.pcmfsync_en = 'b1;    //OEN=0 
    #100;
    chech_in_function(`DUT_XRM.GPIO[24] , `AUDIO_XRM.pcmfsync_out , "GPIO[24]" ,'h20 ,test_error ,"OUT");

//I of IO
    release  `I2SS_XRM.ws_slv;    force    `DUT_XRM.GPIO[24] = $urandom;
    force    `IOMUX_XRM.pad_cfg[ 24*8+:8] = 'h30;  
    force    `SCUREG_XRM.io_config[5] = 'b0;    //OEN=1 
    #100;
    chech_in_function(`I2SS_XRM.ws_slv , `DUT_XRM.GPIO[24] , "GPIO[24]" ,'h30 ,test_error ,"IN");

//O of IO
    release  `DUT_XRM.GPIO[24];    force    `I2SM_XRM.ws_out = $urandom;
    force    `IOMUX_XRM.pad_cfg[ 24*8+:8] = 'h30;  
    force    `SCUREG_XRM.io_config[5] = 'b1;    //OEN=0 
    #100;
    chech_in_function(`DUT_XRM.GPIO[24] , `I2SM_XRM.ws_out , "GPIO[24]" ,'h30 ,test_error ,"OUT");

//O
    release  `DUT_XRM.GPIO[24];    force    `USBPHY_XRM.utmifs_rx_dp = $urandom;
    force    `IOMUX_XRM.pad_cfg[ 24*8+:8] = 'h40;  
    #100;
    chech_in_function(`DUT_XRM.GPIO[24] , `USBPHY_XRM.utmifs_rx_dp , "GPIO[24]" ,'h40 ,test_error ,"OUT");

//O
    release  `DUT_XRM.GPIO[24];    force    `BTDM_XRM.bt_dbg_bus[17] = $urandom;
    force    `IOMUX_XRM.pad_cfg[ 24*8+:8] = 'h50;  
    #100;
    chech_in_function(`DUT_XRM.GPIO[24] , `BTDM_XRM.bt_dbg_bus[17] , "GPIO[24]" ,'h50 ,test_error ,"OUT");

//release
    release `IOMUX_XRM.pad_cfg[ 24*8+:8];
    #100;


//##################GPIO[25]-------------------------------------
//I of IO
    release  `GPIO_XRM.gpio_ext_porta[25];    force    `DUT_XRM.GPIO[25] = $urandom;
    force    `IOMUX_XRM.pad_cfg[ 25*8+:8] = 'h0;  
    force    `GPIO_XRM.gpio_porta_ddr[25] = 'b0;    //OEN=1 
    #100;
    chech_in_function(`GPIO_XRM.gpio_ext_porta[25] , `DUT_XRM.GPIO[25] , "GPIO[25]" ,'h0 ,test_error ,"IN");

//O of IO
    release  `DUT_XRM.GPIO[25];    force    `GPIO_XRM.gpio_porta_dr[25] = $urandom;
    force    `IOMUX_XRM.pad_cfg[ 25*8+:8] = 'h0;  
    force    `GPIO_XRM.gpio_porta_ddr[25] = 'b1;    //OEN=0 
    #100;
    chech_in_function(`DUT_XRM.GPIO[25] , `GPIO_XRM.gpio_porta_dr[25] , "GPIO[25]" ,'h0 ,test_error ,"OUT");

//I
    release  `SPM1_XRM.rxd;    force    `DUT_XRM.GPIO[25] = $urandom;
    force    `IOMUX_XRM.pad_cfg[ 25*8+:8] = 'h10;  
    #100;
    chech_in_function(`SPM1_XRM.rxd , `DUT_XRM.GPIO[25] , "GPIO[25]" ,'h10 ,test_error ,"IN");

//I
    release  `AUDIO_XRM.pcmdin;    force    `DUT_XRM.GPIO[25] = $urandom;
    force    `IOMUX_XRM.pad_cfg[ 25*8+:8] = 'h20;  
    #100;
    chech_in_function(`AUDIO_XRM.pcmdin , `DUT_XRM.GPIO[25] , "GPIO[25]" ,'h20 ,test_error ,"IN");

//I of IO
    release  `I2SS_XRM.sdi0;    force    `DUT_XRM.GPIO[25] = $urandom;
    force    `IOMUX_XRM.pad_cfg[ 25*8+:8] = 'h30;  
    force    `SCUREG_XRM.io_config[5] = 'b0;    //OEN=1 
    #100;
    chech_in_function(`I2SS_XRM.sdi0 , `DUT_XRM.GPIO[25] , "GPIO[25]" ,'h30 ,test_error ,"IN");

//O of IO
    release  `DUT_XRM.GPIO[25];    force    `I2SM_XRM.sdo0 = $urandom;
    force    `IOMUX_XRM.pad_cfg[ 25*8+:8] = 'h30;  
    force    `SCUREG_XRM.io_config[5] = 'b1;    //OEN=0 
    #100;
    chech_in_function(`DUT_XRM.GPIO[25] , `I2SM_XRM.sdo0 , "GPIO[25]" ,'h30 ,test_error ,"OUT");

//O
    release  `DUT_XRM.GPIO[25];    force    `USBPHY_XRM.utmifs_rx_dm = $urandom;
    force    `IOMUX_XRM.pad_cfg[ 25*8+:8] = 'h40;  
    #100;
    chech_in_function(`DUT_XRM.GPIO[25] , `USBPHY_XRM.utmifs_rx_dm , "GPIO[25]" ,'h40 ,test_error ,"OUT");

//O
    release  `DUT_XRM.GPIO[25];    force    `BTDM_XRM.bt_dbg_bus[18] = $urandom;
    force    `IOMUX_XRM.pad_cfg[ 25*8+:8] = 'h50;  
    #100;
    chech_in_function(`DUT_XRM.GPIO[25] , `BTDM_XRM.bt_dbg_bus[18] , "GPIO[25]" ,'h50 ,test_error ,"OUT");

//release
    release `IOMUX_XRM.pad_cfg[ 25*8+:8];
    #100;


//##################GPIO[26]-------------------------------------
//I of IO
    release  `GPIO_XRM.gpio_ext_porta[26];    force    `DUT_XRM.GPIO[26] = $urandom;
    force    `IOMUX_XRM.pad_cfg[ 26*8+:8] = 'h0;  
    force    `GPIO_XRM.gpio_porta_ddr[26] = 'b0;    //OEN=1 
    #100;
    chech_in_function(`GPIO_XRM.gpio_ext_porta[26] , `DUT_XRM.GPIO[26] , "GPIO[26]" ,'h0 ,test_error ,"IN");

//O of IO
    release  `DUT_XRM.GPIO[26];    force    `GPIO_XRM.gpio_porta_dr[26] = $urandom;
    force    `IOMUX_XRM.pad_cfg[ 26*8+:8] = 'h0;  
    force    `GPIO_XRM.gpio_porta_ddr[26] = 'b1;    //OEN=0 
    #100;
    chech_in_function(`DUT_XRM.GPIO[26] , `GPIO_XRM.gpio_porta_dr[26] , "GPIO[26]" ,'h0 ,test_error ,"OUT");

//O
    release  `DUT_XRM.GPIO[26];    force    `SPM1_XRM.txd = $urandom;
    force    `IOMUX_XRM.pad_cfg[ 26*8+:8] = 'h10;  
    #100;
    chech_in_function(`DUT_XRM.GPIO[26] , `SPM1_XRM.txd , "GPIO[26]" ,'h10 ,test_error ,"OUT");

//O1
    release  `DUT_XRM.GPIO[26];    force    `AUDIO_XRM.pcmdout = $urandom;
    force    `IOMUX_XRM.pad_cfg[ 26*8+:8] = 'h20;  
    force    `AUDIO_XRM.pcmdout_en = 'b1;    //OEN=0 
    #100;
    chech_in_function(`DUT_XRM.GPIO[26] , `AUDIO_XRM.pcmdout , "GPIO[26]" ,'h20 ,test_error ,"OUT");

//I of IO
    release  `I2SM_XRM.sdi0;    force    `DUT_XRM.GPIO[26] = $urandom;
    force    `IOMUX_XRM.pad_cfg[ 26*8+:8] = 'h30;  
    force    `SCUREG_XRM.io_config[5] = 'b1;    //OEN=1 
    #100;
    chech_in_function(`I2SM_XRM.sdi0 , `DUT_XRM.GPIO[26] , "GPIO[26]" ,'h30 ,test_error ,"IN");

//O of IO
    release  `DUT_XRM.GPIO[26];    force    `I2SS_XRM.sdo0 = $urandom;
    force    `IOMUX_XRM.pad_cfg[ 26*8+:8] = 'h30;  
    force    `SCUREG_XRM.io_config[5] = 'b0;    //OEN=0 
    #100;
    chech_in_function(`DUT_XRM.GPIO[26] , `I2SS_XRM.sdo0 , "GPIO[26]" ,'h30 ,test_error ,"OUT");

//O
    release  `DUT_XRM.GPIO[26];    force    `USBPHY_XRM.utmifs_rx_rcv = $urandom;
    force    `IOMUX_XRM.pad_cfg[ 26*8+:8] = 'h40;  
    #100;
    chech_in_function(`DUT_XRM.GPIO[26] , `USBPHY_XRM.utmifs_rx_rcv , "GPIO[26]" ,'h40 ,test_error ,"OUT");

//O
    release  `DUT_XRM.GPIO[26];    force    `BTDM_XRM.bt_dbg_bus[19] = $urandom;
    force    `IOMUX_XRM.pad_cfg[ 26*8+:8] = 'h50;  
    #100;
    chech_in_function(`DUT_XRM.GPIO[26] , `BTDM_XRM.bt_dbg_bus[19] , "GPIO[26]" ,'h50 ,test_error ,"OUT");

//release
    release `IOMUX_XRM.pad_cfg[ 26*8+:8];
    #100;


//##################GPIO[27]-------------------------------------
//I of IO
    release  `GPIO_XRM.gpio_ext_porta[27];    force    `DUT_XRM.GPIO[27] = $urandom;
    force    `IOMUX_XRM.pad_cfg[ 27*8+:8] = 'h0;  
    force    `GPIO_XRM.gpio_porta_ddr[27] = 'b0;    //OEN=1 
    #100;
    chech_in_function(`GPIO_XRM.gpio_ext_porta[27] , `DUT_XRM.GPIO[27] , "GPIO[27]" ,'h0 ,test_error ,"IN");

//O of IO
    release  `DUT_XRM.GPIO[27];    force    `GPIO_XRM.gpio_porta_dr[27] = $urandom;
    force    `IOMUX_XRM.pad_cfg[ 27*8+:8] = 'h0;  
    force    `GPIO_XRM.gpio_porta_ddr[27] = 'b1;    //OEN=0 
    #100;
    chech_in_function(`DUT_XRM.GPIO[27] , `GPIO_XRM.gpio_porta_dr[27] , "GPIO[27]" ,'h0 ,test_error ,"OUT");

//O
    release  `DUT_XRM.GPIO[27];    force    `UART1_XRM.rts_n = $urandom;
    force    `IOMUX_XRM.pad_cfg[ 27*8+:8] = 'h10;  
    #100;
    chech_in_function(`DUT_XRM.GPIO[27] , `UART1_XRM.rts_n , "GPIO[27]" ,'h10 ,test_error ,"OUT");

//O
    release  `DUT_XRM.GPIO[27];    force    `BTDM_XRM.rf_tx_en = $urandom;
    force    `IOMUX_XRM.pad_cfg[ 27*8+:8] = 'h20;  
    #100;
    chech_in_function(`DUT_XRM.GPIO[27] , `BTDM_XRM.rf_tx_en , "GPIO[27]" ,'h20 ,test_error ,"OUT");

//I of IO1
    release  `I2C_XRM.ic_clk_in_a;    force    `IOMUX_XRM.pad_cfg[ 27*8+:8] = 'h30;  
    force    `I2C_XRM.ic_clk_oe = 'b0;    //OEN=1 
    #100;
    chech_in_function(`I2C_XRM.ic_clk_in_a , `DUT_XRM.GPIO[27] , "GPIO[27]" ,'h30 ,test_error ,"IN");

//O of IO1
    release  `DUT_XRM.GPIO[27];    force    `IOMUX_XRM.pad_cfg[ 27*8+:8] = 'h30;  
    force    `I2C_XRM.ic_clk_oe = 'b1;    //OEN=0 
    #100;
    chech_in_function(`DUT_XRM.GPIO[27] , `PAD_IPORT_TIE , "GPIO[27]" ,'h30 ,test_error ,"OUT");

//O
    release  `DUT_XRM.GPIO[27];    force    `BTDM_XRM.rf_test_out = $urandom;
    force    `IOMUX_XRM.pad_cfg[ 27*8+:8] = 'h40;  
    #100;
    chech_in_function(`DUT_XRM.GPIO[27] , `BTDM_XRM.rf_test_out , "GPIO[27]" ,'h40 ,test_error ,"OUT");

//O
    release  `DUT_XRM.GPIO[27];    force    `BTDM_XRM.bt_dbg_bus[20] = $urandom;
    force    `IOMUX_XRM.pad_cfg[ 27*8+:8] = 'h50;  
    #100;
    chech_in_function(`DUT_XRM.GPIO[27] , `BTDM_XRM.bt_dbg_bus[20] , "GPIO[27]" ,'h50 ,test_error ,"OUT");

//release
    release `IOMUX_XRM.pad_cfg[ 27*8+:8];
    #100;


//##################GPIO[28]-------------------------------------
//I of IO
    release  `GPIO_XRM.gpio_ext_porta[28];    force    `DUT_XRM.GPIO[28] = $urandom;
    force    `IOMUX_XRM.pad_cfg[ 28*8+:8] = 'h0;  
    force    `GPIO_XRM.gpio_porta_ddr[28] = 'b0;    //OEN=1 
    #100;
    chech_in_function(`GPIO_XRM.gpio_ext_porta[28] , `DUT_XRM.GPIO[28] , "GPIO[28]" ,'h0 ,test_error ,"IN");

//O of IO
    release  `DUT_XRM.GPIO[28];    force    `GPIO_XRM.gpio_porta_dr[28] = $urandom;
    force    `IOMUX_XRM.pad_cfg[ 28*8+:8] = 'h0;  
    force    `GPIO_XRM.gpio_porta_ddr[28] = 'b1;    //OEN=0 
    #100;
    chech_in_function(`DUT_XRM.GPIO[28] , `GPIO_XRM.gpio_porta_dr[28] , "GPIO[28]" ,'h0 ,test_error ,"OUT");

//I
    release  `UART1_XRM.cts_n;    force    `DUT_XRM.GPIO[28] = $urandom;
    force    `IOMUX_XRM.pad_cfg[ 28*8+:8] = 'h10;  
    #100;
    chech_in_function(`UART1_XRM.cts_n , `DUT_XRM.GPIO[28] , "GPIO[28]" ,'h10 ,test_error ,"IN");

//O
    release  `DUT_XRM.GPIO[28];    force    `BTDM_XRM.rf_rx_en = $urandom;
    force    `IOMUX_XRM.pad_cfg[ 28*8+:8] = 'h20;  
    #100;
    chech_in_function(`DUT_XRM.GPIO[28] , `BTDM_XRM.rf_rx_en , "GPIO[28]" ,'h20 ,test_error ,"OUT");

//I of IO1
    release  `I2C_XRM.ic_data_in_a;    force    `IOMUX_XRM.pad_cfg[ 28*8+:8] = 'h30;  
    force    `I2C_XRM.ic_data_oe = 'b0;    //OEN=1 
    #100;
    chech_in_function(`I2C_XRM.ic_data_in_a , `DUT_XRM.GPIO[28] , "GPIO[28]" ,'h30 ,test_error ,"IN");

//O of IO1
    release  `DUT_XRM.GPIO[28];    force    `IOMUX_XRM.pad_cfg[ 28*8+:8] = 'h30;  
    force    `I2C_XRM.ic_data_oe = 'b1;    //OEN=0 
    #100;
    chech_in_function(`DUT_XRM.GPIO[28] , `PAD_IPORT_TIE , "GPIO[28]" ,'h30 ,test_error ,"OUT");

//O
    release  `DUT_XRM.GPIO[28];    force    `ANATOP_XRM.RCO32_FINE_DONE = $urandom;
    force    `IOMUX_XRM.pad_cfg[ 28*8+:8] = 'h40;  
    #100;
    chech_in_function(`DUT_XRM.GPIO[28] , `ANATOP_XRM.RCO32_FINE_DONE , "GPIO[28]" ,'h40 ,test_error ,"OUT");

//O
    release  `DUT_XRM.GPIO[28];    force    `BTDM_XRM.bt_dbg_bus[21] = $urandom;
    force    `IOMUX_XRM.pad_cfg[ 28*8+:8] = 'h50;  
    #100;
    chech_in_function(`DUT_XRM.GPIO[28] , `BTDM_XRM.bt_dbg_bus[21] , "GPIO[28]" ,'h50 ,test_error ,"OUT");

//release
    release `IOMUX_XRM.pad_cfg[ 28*8+:8];
    #100;


//##################GPIO[29:34] function0 -------------------------------------
    force    `IOMUX_XRM.pad_cfg[ 29*8+:8] = 'h0;
    force    `IOMUX_XRM.pad_cfg[ 30*8+:8] = 'h0;
    force    `IOMUX_XRM.pad_cfg[ 31*8+:8] = 'h0;
    force    `IOMUX_XRM.pad_cfg[ 32*8+:8] = 'h0;
    force    `IOMUX_XRM.pad_cfg[ 33*8+:8] = 'h0;
    force    `IOMUX_XRM.pad_cfg[ 34*8+:8] = 'h0;
//O
    release  `DUT_XRM.GPIO[29];    force    `SPM0_XRM.ss_0_n = $urandom;
    #100;
    chech_in_function(`DUT_XRM.GPIO[29] , `SPM0_XRM.ss_0_n , "GPIO[29]" ,'h0 ,test_error ,"OUT");

//I of IO
    release  `SPM0_XRM.rxd[1];    force    `DUT_XRM.GPIO[30] = $urandom;
    force    `SPM0_XRM.ssi_oe_n[1] = 'b1;    //OEN=1 
    #100;
    chech_in_function(`SPM0_XRM.rxd[1] , `DUT_XRM.GPIO[30] , "GPIO[30]" ,'h0 ,test_error ,"IN");

//O of IO
    release  `DUT_XRM.GPIO[30];    force    `SPM0_XRM.txd[1] = $urandom;
    force    `SPM0_XRM.ssi_oe_n[1] = 'b0;    //OEN=0 
    #100;
    chech_in_function(`DUT_XRM.GPIO[30] , `SPM0_XRM.txd[1] , "GPIO[30]" ,'h0 ,test_error ,"OUT");

//I of IO
    release  `SPM0_XRM.rxd[2];    force    `DUT_XRM.GPIO[31] = $urandom;
    force    `SPM0_XRM.ssi_oe_n[2] = 'b1;    //OEN=1 
    #100;
    chech_in_function(`SPM0_XRM.rxd[2] , `DUT_XRM.GPIO[31] , "GPIO[31]" ,'h0 ,test_error ,"IN");

//O of IO
    release  `DUT_XRM.GPIO[31];    force    `SPM0_XRM.txd[2] = $urandom;
    force    `SPM0_XRM.ssi_oe_n[2] = 'b0;    //OEN=0 
    #100;
    chech_in_function(`DUT_XRM.GPIO[31] , `SPM0_XRM.txd[2] , "GPIO[31]" ,'h0 ,test_error ,"OUT");

//I of IO
    release  `SPM0_XRM.rxd[3];    force    `DUT_XRM.GPIO[32] = $urandom;
    force    `SPM0_XRM.ssi_oe_n[3] = 'b1;    //OEN=1 
    #100;
    chech_in_function(`SPM0_XRM.rxd[3] , `DUT_XRM.GPIO[32] , "GPIO[32]" ,'h0 ,test_error ,"IN");

//O of IO
    release  `DUT_XRM.GPIO[32];    force    `SPM0_XRM.txd[3] = $urandom;
    force    `SPM0_XRM.ssi_oe_n[3] = 'b0;    //OEN=0 
    #100;
    chech_in_function(`DUT_XRM.GPIO[32] , `SPM0_XRM.txd[3] , "GPIO[32]" ,'h0 ,test_error ,"OUT");

//O
    release  `DUT_XRM.GPIO[33];    force    `SPM0_XRM.sclk_out = $urandom;
    #100;
    chech_in_function(`DUT_XRM.GPIO[33] , `SPM0_XRM.sclk_out , "GPIO[33]" ,'h0 ,test_error ,"OUT");

//I of IO
    release  `SPM0_XRM.rxd[0];    force    `DUT_XRM.GPIO[34] = $urandom;
    force    `SPM0_XRM.ssi_oe_n[0] = 'b1;    //OEN=1 
    #100;
    chech_in_function(`SPM0_XRM.rxd[0] , `DUT_XRM.GPIO[34] , "GPIO[34]" ,'h0 ,test_error ,"IN");

//O of IO
    release  `DUT_XRM.GPIO[34];    force    `SPM0_XRM.txd[0] = $urandom;
    force    `SPM0_XRM.ssi_oe_n[0] = 'b0;    //OEN=0 
    #100;
    chech_in_function(`DUT_XRM.GPIO[34] , `SPM0_XRM.txd[0] , "GPIO[34]" ,'h0 ,test_error ,"OUT");

//##################GPIO[29:34] function1 -------------------------------------
    force    `IOMUX_XRM.pad_cfg[ 29*8+:8] = 'h10;
    force    `IOMUX_XRM.pad_cfg[ 30*8+:8] = 'h10;
    force    `IOMUX_XRM.pad_cfg[ 31*8+:8] = 'h10;
    force    `IOMUX_XRM.pad_cfg[ 32*8+:8] = 'h10;
    force    `IOMUX_XRM.pad_cfg[ 33*8+:8] = 'h10;
    force    `IOMUX_XRM.pad_cfg[ 34*8+:8] = 'h10;
//I of IO
    release  `SPM0_XRM.rxd[0];    force    `DUT_XRM.GPIO[29] = $urandom;
    force    `SPM0_XRM.ssi_oe_n[0] = 'b1;    //OEN=1 
    #100;
    chech_in_function(`SPM0_XRM.rxd[0] , `DUT_XRM.GPIO[29] , "GPIO[29]" ,'h10 ,test_error ,"IN");

//O of IO
    release  `DUT_XRM.GPIO[29];    force    `SPM0_XRM.txd[0] = $urandom;
    force    `SPM0_XRM.ssi_oe_n[0] = 'b0;    //OEN=0 
    #100;
    chech_in_function(`DUT_XRM.GPIO[29] , `SPM0_XRM.txd[0] , "GPIO[29]" ,'h10 ,test_error ,"OUT");

//O
    release  `DUT_XRM.GPIO[30];    force    `SPM0_XRM.ss_0_n = $urandom;
    #100;
    chech_in_function(`DUT_XRM.GPIO[30] , `SPM0_XRM.ss_0_n , "GPIO[30]" ,'h10 ,test_error ,"OUT");

//I of IO
    release  `SPM0_XRM.rxd[1];    force    `DUT_XRM.GPIO[31] = $urandom;
    force    `SPM0_XRM.ssi_oe_n[1] = 'b1;    //OEN=1 
    #100;
    chech_in_function(`SPM0_XRM.rxd[1] , `DUT_XRM.GPIO[31] , "GPIO[31]" ,'h10 ,test_error ,"IN");

//O of IO
    release  `DUT_XRM.GPIO[31];    force    `SPM0_XRM.txd[1] = $urandom;
    force    `SPM0_XRM.ssi_oe_n[1] = 'b0;    //OEN=0 
    #100;
    chech_in_function(`DUT_XRM.GPIO[31] , `SPM0_XRM.txd[1] , "GPIO[31]" ,'h10 ,test_error ,"OUT");

//I of IO
    release  `SPM0_XRM.rxd[2];    force    `DUT_XRM.GPIO[32] = $urandom;
    force    `SPM0_XRM.ssi_oe_n[2] = 'b1;    //OEN=1 
    #100;
    chech_in_function(`SPM0_XRM.rxd[2] , `DUT_XRM.GPIO[32] , "GPIO[32]" ,'h10 ,test_error ,"IN");

//O of IO
    release  `DUT_XRM.GPIO[32];    force    `SPM0_XRM.txd[2] = $urandom;
    force    `SPM0_XRM.ssi_oe_n[2] = 'b0;    //OEN=0 
    #100;
    chech_in_function(`DUT_XRM.GPIO[32] , `SPM0_XRM.txd[2] , "GPIO[32]" ,'h10 ,test_error ,"OUT");

//I of IO
    release  `SPM0_XRM.rxd[3];    force    `DUT_XRM.GPIO[33] = $urandom;
    force    `SPM0_XRM.ssi_oe_n[3] = 'b1;    //OEN=1 
    #100;
    chech_in_function(`SPM0_XRM.rxd[3] , `DUT_XRM.GPIO[33] , "GPIO[33]" ,'h10 ,test_error ,"IN");

//O of IO
    release  `DUT_XRM.GPIO[33];    force    `SPM0_XRM.txd[3] = $urandom;
    force    `SPM0_XRM.ssi_oe_n[3] = 'b0;    //OEN=0 
    #100;
    chech_in_function(`DUT_XRM.GPIO[33] , `SPM0_XRM.txd[3] , "GPIO[33]" ,'h10 ,test_error ,"OUT");

//O
    release  `DUT_XRM.GPIO[34];    force    `SPM0_XRM.sclk_out = $urandom;
    #100;
    chech_in_function(`DUT_XRM.GPIO[34] , `SPM0_XRM.sclk_out , "GPIO[34]" ,'h10 ,test_error ,"OUT");

//##################GPIO[29:34] function2 -------------------------------------
    force    `IOMUX_XRM.pad_cfg[ 29*8+:8] = 'h20;
    force    `IOMUX_XRM.pad_cfg[ 30*8+:8] = 'h20;
    force    `IOMUX_XRM.pad_cfg[ 31*8+:8] = 'h20;
    force    `IOMUX_XRM.pad_cfg[ 32*8+:8] = 'h20;
    force    `IOMUX_XRM.pad_cfg[ 33*8+:8] = 'h20;
    force    `IOMUX_XRM.pad_cfg[ 34*8+:8] = 'h20;
//O
    release  `DUT_XRM.GPIO[29];    force    `SPM0_XRM.sclk_out = $urandom;
    #100;
    chech_in_function(`DUT_XRM.GPIO[29] , `SPM0_XRM.sclk_out , "GPIO[29]" ,'h20 ,test_error ,"OUT");

//I of IO
    release  `SPM0_XRM.rxd[0];    force    `DUT_XRM.GPIO[30] = $urandom;
    force    `SPM0_XRM.ssi_oe_n[0] = 'b1;    //OEN=1 
    #100;
    chech_in_function(`SPM0_XRM.rxd[0] , `DUT_XRM.GPIO[30] , "GPIO[30]" ,'h20 ,test_error ,"IN");

//O of IO
    release  `DUT_XRM.GPIO[30];    force    `SPM0_XRM.txd[0] = $urandom;
    force    `SPM0_XRM.ssi_oe_n[0] = 'b0;    //OEN=0 
    #100;
    chech_in_function(`DUT_XRM.GPIO[30] , `SPM0_XRM.txd[0] , "GPIO[30]" ,'h20 ,test_error ,"OUT");

//O
    release  `DUT_XRM.GPIO[31];    force    `SPM0_XRM.ss_0_n = $urandom;
    #100;
    chech_in_function(`DUT_XRM.GPIO[31] , `SPM0_XRM.ss_0_n , "GPIO[31]" ,'h20 ,test_error ,"OUT");

//I of IO
    release  `SPM0_XRM.rxd[1];    force    `DUT_XRM.GPIO[32] = $urandom;
    force    `SPM0_XRM.ssi_oe_n[1] = 'b1;    //OEN=1 
    #100;
    chech_in_function(`SPM0_XRM.rxd[1] , `DUT_XRM.GPIO[32] , "GPIO[32]" ,'h20 ,test_error ,"IN");

//O of IO
    release  `DUT_XRM.GPIO[32];    force    `SPM0_XRM.txd[1] = $urandom;
    force    `SPM0_XRM.ssi_oe_n[1] = 'b0;    //OEN=0 
    #100;
    chech_in_function(`DUT_XRM.GPIO[32] , `SPM0_XRM.txd[1] , "GPIO[32]" ,'h20 ,test_error ,"OUT");

//I of IO
    release  `SPM0_XRM.rxd[2];    force    `DUT_XRM.GPIO[33] = $urandom;
    force    `SPM0_XRM.ssi_oe_n[2] = 'b1;    //OEN=1 
    #100;
    chech_in_function(`SPM0_XRM.rxd[2] , `DUT_XRM.GPIO[33] , "GPIO[33]" ,'h20 ,test_error ,"IN");

//O of IO
    release  `DUT_XRM.GPIO[33];    force    `SPM0_XRM.txd[2] = $urandom;
    force    `SPM0_XRM.ssi_oe_n[2] = 'b0;    //OEN=0 
    #100;
    chech_in_function(`DUT_XRM.GPIO[33] , `SPM0_XRM.txd[2] , "GPIO[33]" ,'h20 ,test_error ,"OUT");

//I of IO
    release  `SPM0_XRM.rxd[3];    force    `DUT_XRM.GPIO[34] = $urandom;
    force    `SPM0_XRM.ssi_oe_n[3] = 'b1;    //OEN=1 
    #100;
    chech_in_function(`SPM0_XRM.rxd[3] , `DUT_XRM.GPIO[34] , "GPIO[34]" ,'h20 ,test_error ,"IN");

//O of IO
    release  `DUT_XRM.GPIO[34];    force    `SPM0_XRM.txd[3] = $urandom;
    force    `SPM0_XRM.ssi_oe_n[3] = 'b0;    //OEN=0 
    #100;
    chech_in_function(`DUT_XRM.GPIO[34] , `SPM0_XRM.txd[3] , "GPIO[34]" ,'h20 ,test_error ,"OUT");

//##################GPIO[29:34] function3 -------------------------------------
    force    `IOMUX_XRM.pad_cfg[ 29*8+:8] = 'h30;
    force    `IOMUX_XRM.pad_cfg[ 30*8+:8] = 'h30;
    force    `IOMUX_XRM.pad_cfg[ 31*8+:8] = 'h30;
    force    `IOMUX_XRM.pad_cfg[ 32*8+:8] = 'h30;
    force    `IOMUX_XRM.pad_cfg[ 33*8+:8] = 'h30;
    force    `IOMUX_XRM.pad_cfg[ 34*8+:8] = 'h30;
//I of IO
    release  `SPM0_XRM.rxd[3];    force    `DUT_XRM.GPIO[29] = $urandom;
    force    `SPM0_XRM.ssi_oe_n[3] = 'b1;    //OEN=1 
    #100;
    chech_in_function(`SPM0_XRM.rxd[3] , `DUT_XRM.GPIO[29] , "GPIO[29]" ,'h30 ,test_error ,"IN");

//O of IO
    release  `DUT_XRM.GPIO[29];    force    `SPM0_XRM.txd[3] = $urandom;
    force    `SPM0_XRM.ssi_oe_n[3] = 'b0;    //OEN=0 
    #100;
    chech_in_function(`DUT_XRM.GPIO[29] , `SPM0_XRM.txd[3] , "GPIO[29]" ,'h30 ,test_error ,"OUT");

//O
    release  `DUT_XRM.GPIO[30];    force    `SPM0_XRM.sclk_out = $urandom;
    #100;
    chech_in_function(`DUT_XRM.GPIO[30] , `SPM0_XRM.sclk_out , "GPIO[30]" ,'h30 ,test_error ,"OUT");

//I of IO
    release  `SPM0_XRM.rxd[0];    force    `DUT_XRM.GPIO[31] = $urandom;
    force    `SPM0_XRM.ssi_oe_n[0] = 'b1;    //OEN=1 
    #100;
    chech_in_function(`SPM0_XRM.rxd[0] , `DUT_XRM.GPIO[31] , "GPIO[31]" ,'h30 ,test_error ,"IN");

//O of IO
    release  `DUT_XRM.GPIO[31];    force    `SPM0_XRM.txd[0] = $urandom;
    force    `SPM0_XRM.ssi_oe_n[0] = 'b0;    //OEN=0 
    #100;
    chech_in_function(`DUT_XRM.GPIO[31] , `SPM0_XRM.txd[0] , "GPIO[31]" ,'h30 ,test_error ,"OUT");

//O
    release  `DUT_XRM.GPIO[32];    force    `SPM0_XRM.ss_0_n = $urandom;
    #100;
    chech_in_function(`DUT_XRM.GPIO[32] , `SPM0_XRM.ss_0_n , "GPIO[32]" ,'h30 ,test_error ,"OUT");

//I of IO
    release  `SPM0_XRM.rxd[1];    force    `DUT_XRM.GPIO[33] = $urandom;
    force    `SPM0_XRM.ssi_oe_n[1] = 'b1;    //OEN=1 
    #100;
    chech_in_function(`SPM0_XRM.rxd[1] , `DUT_XRM.GPIO[33] , "GPIO[33]" ,'h30 ,test_error ,"IN");

//O of IO
    release  `DUT_XRM.GPIO[33];    force    `SPM0_XRM.txd[1] = $urandom;
    force    `SPM0_XRM.ssi_oe_n[1] = 'b0;    //OEN=0 
    #100;
    chech_in_function(`DUT_XRM.GPIO[33] , `SPM0_XRM.txd[1] , "GPIO[33]" ,'h30 ,test_error ,"OUT");

//I of IO
    release  `SPM0_XRM.rxd[2];    force    `DUT_XRM.GPIO[34] = $urandom;
    force    `SPM0_XRM.ssi_oe_n[2] = 'b1;    //OEN=1 
    #100;
    chech_in_function(`SPM0_XRM.rxd[2] , `DUT_XRM.GPIO[34] , "GPIO[34]" ,'h30 ,test_error ,"IN");

//O of IO
    release  `DUT_XRM.GPIO[34];    force    `SPM0_XRM.txd[2] = $urandom;
    force    `SPM0_XRM.ssi_oe_n[2] = 'b0;    //OEN=0 
    #100;
    chech_in_function(`DUT_XRM.GPIO[34] , `SPM0_XRM.txd[2] , "GPIO[34]" ,'h30 ,test_error ,"OUT");

//##################GPIO[29:34] function4 -------------------------------------
    force    `IOMUX_XRM.pad_cfg[ 29*8+:8] = 'h40;
    force    `IOMUX_XRM.pad_cfg[ 30*8+:8] = 'h40;
    force    `IOMUX_XRM.pad_cfg[ 31*8+:8] = 'h40;
    force    `IOMUX_XRM.pad_cfg[ 32*8+:8] = 'h40;
    force    `IOMUX_XRM.pad_cfg[ 33*8+:8] = 'h40;
    force    `IOMUX_XRM.pad_cfg[ 34*8+:8] = 'h40;
//I of IO
    release  `SPM0_XRM.rxd[2];    force    `DUT_XRM.GPIO[29] = $urandom;
    force    `SPM0_XRM.ssi_oe_n[2] = 'b1;    //OEN=1 
    #100;
    chech_in_function(`SPM0_XRM.rxd[2] , `DUT_XRM.GPIO[29] , "GPIO[29]" ,'h40 ,test_error ,"IN");

//O of IO
    release  `DUT_XRM.GPIO[29];    force    `SPM0_XRM.txd[2] = $urandom;
    force    `SPM0_XRM.ssi_oe_n[2] = 'b0;    //OEN=0 
    #100;
    chech_in_function(`DUT_XRM.GPIO[29] , `SPM0_XRM.txd[2] , "GPIO[29]" ,'h40 ,test_error ,"OUT");

//I of IO
    release  `SPM0_XRM.rxd[3];    force    `DUT_XRM.GPIO[30] = $urandom;
    force    `SPM0_XRM.ssi_oe_n[3] = 'b1;    //OEN=1 
    #100;
    chech_in_function(`SPM0_XRM.rxd[3] , `DUT_XRM.GPIO[30] , "GPIO[30]" ,'h40 ,test_error ,"IN");

//O of IO
    release  `DUT_XRM.GPIO[30];    force    `SPM0_XRM.txd[3] = $urandom;
    force    `SPM0_XRM.ssi_oe_n[3] = 'b0;    //OEN=0 
    #100;
    chech_in_function(`DUT_XRM.GPIO[30] , `SPM0_XRM.txd[3] , "GPIO[30]" ,'h40 ,test_error ,"OUT");

//O
    release  `DUT_XRM.GPIO[31];    force    `SPM0_XRM.sclk_out = $urandom;
    #100;
    chech_in_function(`DUT_XRM.GPIO[31] , `SPM0_XRM.sclk_out , "GPIO[31]" ,'h40 ,test_error ,"OUT");

//I of IO
    release  `SPM0_XRM.rxd[0];    force    `DUT_XRM.GPIO[32] = $urandom;
    force    `SPM0_XRM.ssi_oe_n[0] = 'b1;    //OEN=1 
    #100;
    chech_in_function(`SPM0_XRM.rxd[0] , `DUT_XRM.GPIO[32] , "GPIO[32]" ,'h40 ,test_error ,"IN");

//O of IO
    release  `DUT_XRM.GPIO[32];    force    `SPM0_XRM.txd[0] = $urandom;
    force    `SPM0_XRM.ssi_oe_n[0] = 'b0;    //OEN=0 
    #100;
    chech_in_function(`DUT_XRM.GPIO[32] , `SPM0_XRM.txd[0] , "GPIO[32]" ,'h40 ,test_error ,"OUT");

//O
    release  `DUT_XRM.GPIO[33];    force    `SPM0_XRM.ss_0_n = $urandom;
    #100;
    chech_in_function(`DUT_XRM.GPIO[33] , `SPM0_XRM.ss_0_n , "GPIO[33]" ,'h40 ,test_error ,"OUT");

//I of IO
    release  `SPM0_XRM.rxd[1];    force    `DUT_XRM.GPIO[34] = $urandom;
    force    `SPM0_XRM.ssi_oe_n[1] = 'b1;    //OEN=1 
    #100;
    chech_in_function(`SPM0_XRM.rxd[1] , `DUT_XRM.GPIO[34] , "GPIO[34]" ,'h40 ,test_error ,"IN");

//O of IO
    release  `DUT_XRM.GPIO[34];    force    `SPM0_XRM.txd[1] = $urandom;
    force    `SPM0_XRM.ssi_oe_n[1] = 'b0;    //OEN=0 
    #100;
    chech_in_function(`DUT_XRM.GPIO[34] , `SPM0_XRM.txd[1] , "GPIO[34]" ,'h40 ,test_error ,"OUT");

//##################GPIO[29:34] function5 -------------------------------------
    force    `IOMUX_XRM.pad_cfg[ 29*8+:8] = 'h50;
    force    `IOMUX_XRM.pad_cfg[ 30*8+:8] = 'h50;
    force    `IOMUX_XRM.pad_cfg[ 31*8+:8] = 'h50;
    force    `IOMUX_XRM.pad_cfg[ 32*8+:8] = 'h50;
    force    `IOMUX_XRM.pad_cfg[ 33*8+:8] = 'h50;
    force    `IOMUX_XRM.pad_cfg[ 34*8+:8] = 'h50;
//I of IO
    release  `SPM0_XRM.rxd[1];    force    `DUT_XRM.GPIO[29] = $urandom;
    force    `SPM0_XRM.ssi_oe_n[1] = 'b1;    //OEN=1 
    #100;
    chech_in_function(`SPM0_XRM.rxd[1] , `DUT_XRM.GPIO[29] , "GPIO[29]" ,'h50 ,test_error ,"IN");

//O of IO
    release  `DUT_XRM.GPIO[29];    force    `SPM0_XRM.txd[1] = $urandom;
    force    `SPM0_XRM.ssi_oe_n[1] = 'b0;    //OEN=0 
    #100;
    chech_in_function(`DUT_XRM.GPIO[29] , `SPM0_XRM.txd[1] , "GPIO[29]" ,'h50 ,test_error ,"OUT");

//I of IO
    release  `SPM0_XRM.rxd[2];    force    `DUT_XRM.GPIO[30] = $urandom;
    force    `SPM0_XRM.ssi_oe_n[2] = 'b1;    //OEN=1 
    #100;
    chech_in_function(`SPM0_XRM.rxd[2] , `DUT_XRM.GPIO[30] , "GPIO[30]" ,'h50 ,test_error ,"IN");

//O of IO
    release  `DUT_XRM.GPIO[30];    force    `SPM0_XRM.txd[2] = $urandom;
    force    `SPM0_XRM.ssi_oe_n[2] = 'b0;    //OEN=0 
    #100;
    chech_in_function(`DUT_XRM.GPIO[30] , `SPM0_XRM.txd[2] , "GPIO[30]" ,'h50 ,test_error ,"OUT");

//I of IO
    release  `SPM0_XRM.rxd[3];    force    `DUT_XRM.GPIO[31] = $urandom;
    force    `SPM0_XRM.ssi_oe_n[3] = 'b1;    //OEN=1 
    #100;
    chech_in_function(`SPM0_XRM.rxd[3] , `DUT_XRM.GPIO[31] , "GPIO[31]" ,'h50 ,test_error ,"IN");

//O of IO
    release  `DUT_XRM.GPIO[31];    force    `SPM0_XRM.txd[3] = $urandom;
    force    `SPM0_XRM.ssi_oe_n[3] = 'b0;    //OEN=0 
    #100;
    chech_in_function(`DUT_XRM.GPIO[31] , `SPM0_XRM.txd[3] , "GPIO[31]" ,'h50 ,test_error ,"OUT");

//O
    release  `DUT_XRM.GPIO[32];    force    `SPM0_XRM.sclk_out = $urandom;
    #100;
    chech_in_function(`DUT_XRM.GPIO[32] , `SPM0_XRM.sclk_out , "GPIO[32]" ,'h50 ,test_error ,"OUT");

//I of IO
    release  `SPM0_XRM.rxd[0];    force    `DUT_XRM.GPIO[33] = $urandom;
    force    `SPM0_XRM.ssi_oe_n[0] = 'b1;    //OEN=1 
    #100;
    chech_in_function(`SPM0_XRM.rxd[0] , `DUT_XRM.GPIO[33] , "GPIO[33]" ,'h50 ,test_error ,"IN");

//O of IO
    release  `DUT_XRM.GPIO[33];    force    `SPM0_XRM.txd[0] = $urandom;
    force    `SPM0_XRM.ssi_oe_n[0] = 'b0;    //OEN=0 
    #100;
    chech_in_function(`DUT_XRM.GPIO[33] , `SPM0_XRM.txd[0] , "GPIO[33]" ,'h50 ,test_error ,"OUT");

//O
    release  `DUT_XRM.GPIO[34];    force    `SPM0_XRM.ss_0_n = $urandom;
    #100;
    chech_in_function(`DUT_XRM.GPIO[34] , `SPM0_XRM.ss_0_n , "GPIO[34]" ,'h50 ,test_error ,"OUT");

//release
    force    `IOMUX_XRM.pad_cfg[ 29*8+:8] = 'h0;  
    force    `IOMUX_XRM.pad_cfg[ 30*8+:8] = 'h0;  
    force    `IOMUX_XRM.pad_cfg[ 31*8+:8] = 'h0;  
    force    `IOMUX_XRM.pad_cfg[ 32*8+:8] = 'h0;  
    force    `IOMUX_XRM.pad_cfg[ 33*8+:8] = 'h0;  
    force    `IOMUX_XRM.pad_cfg[ 34*8+:8] = 'h0;  
    #100;






$display("TEST_ERROR = %d",test_error);
  if (test_error != 0)
    $display("tests are wrong.............................................");
  else begin
    $display("All tests are right!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!");
  end
endtask: iomux_function

task chech_in_function (bit left_signal, bit right_signal, string name,int function_num, int error_count, string in_out);
  if (left_signal != right_signal) begin
      error_count = error_count + 1; 
      $display("%t L = %b, R = %b,GPIO_bit = %s test FAIL,function_num = %0x,test_error = %0d,direction = %s!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!",$realtime,left_signal,right_signal,name,function_num,error_count,in_out);
    end
    #1000;
endtask: chech_in_function
