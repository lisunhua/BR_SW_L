`include "chip_defines.sv"

class chip_clk extends chip_base_test;

	`uvm_component_utils(chip_clk)

      int i=16'h0;  // for print of data0;
      int j=16'h0;  // for print of data1;    
      int k=16'h0;  // for print of data2; 
      int l=16'h0;  // for print of data3;
      int m=32'h0;  // basic data0 with high_bit and low_bit;
      int n=32'd0;  // cycle times
      int o=32'h1;  // value of data3 and register for print    
      int p=32'd2;  // cycle times                    
      int q=32'd2;  // read_only register selected                    
      int s=32'h20; // for data2
      int t=32'h20; // for fw
      int u=0;      // for fw

      string register_name;

      uvm_status_e status0;         // status of data0 register
      uvm_status_e status1;         // status of data1 register
      uvm_status_e status2;         // status of data2 register
      uvm_status_e status3;         // status of data3 register
      uvm_status_e status_IP;       // status of IP register
      uvm_reg_data_t data0;         // value of data0 register
      uvm_reg_data_t data1;         // value of data1 register
      uvm_reg_data_t data2;         // value of data2 register
      uvm_reg_data_t data3;         // value of data3 register
      uvm_reg_data_t read_value_IP; // value of IP register

		function new(string name, uvm_component parent);
			super.new(name, parent);
		endfunction: new

		task main_phase(uvm_phase phase);
	    phase.raise_objection(phase);
//--------------------CPU write, TB read----------------------------------//										 
          fork
            begin
              while(1) begin
                if (data0!= i || data1 != j) begin
                  `uvm_info("DATA REGISTER",$psprintf("TB read value from CPU: data0=%0x,data1=%0x\n", data0, data1),UVM_LOW)
                   i = data0;
                   j = data1;
                     end
                else begin 
                   sa_env.chip_reg.MESSAGE_TB.read(.status(status0), .value(data0), .path(UVM_BACKDOOR));
                   sa_env.chip_reg.MESSAGE_CPU.read(.status(status1), .value(data1), .path(UVM_BACKDOOR));
                   #1us;                 
                   end                  
               end 
            end
            begin
              while(1) begin
                if (data2 != k || data3 != l) begin
                  `uvm_info("DATA REGISTER",$psprintf("TB write value to CPU: data2=%0x,data3=%0x\n", data2, data3),UVM_LOW)
                   k = data2;
                   l = data3;
                     end
                else begin
                   sa_env.chip_reg.DATA2.read(.status(status2), .value(data2), .path(UVM_BACKDOOR));
                   sa_env.chip_reg.DATA3.read(.status(status3), .value(data3), .path(UVM_BACKDOOR));
                   #1us;                  
                   end                  
               end
            end
            begin
              while(1) begin
                if (n != p) begin
                  `uvm_info("N",$psprintf("n=%0d\n", n),UVM_LOW)
                   p = n;
                     end
                   #1us;
                   end
                 end
            begin
              while(1) begin
                if (u != t) begin
                  `uvm_info("U",$psprintf("u=%0d\n", u),UVM_LOW)
                   t = u;
                     end
                   #1us;
                   end
                 end

         join_none;


//           while (data0 != 'h4 || data1 != 'h1 ) begin    // read data0=4,data1=1                                                                           
//             #1us;
//           end
//           sa_env.chip_reg.DATA3.write(.status(status3), .value('h155), .path(UVM_BACKDOOR));//write 1,155
//           sa_env.chip_reg.DATA2.write(.status(status2), .value('h1), .path(UVM_BACKDOOR));
//           while (data0 != 'h2 || data1 != 'h155 ) begin
//             #1us;
//           end
//             sa_env.chip_reg.DATA3.write(.status(status3), .value('h1), .path(UVM_BACKDOOR));//write 2,1
//             sa_env.chip_reg.DATA2.write(.status(status2), .value('h2), .path(UVM_BACKDOOR));
//             while (  data2 != 'h2  ||  data3 != 'h1) begin
//               #1us;
//               end
     
//-------------------------------------------- Traversal of writable registers----------------------------//

                for (n=0; n<10000;n++) begin            
                 while (data0 == m) begin
                     #1us;
                                     end
                if (data0 == 'h3) break;
                writable_register;
                end 

//           sa_env.chip_reg.DATA3.write(.status(status3), .value('h1), .path(UVM_BACKDOOR));//write 
//           sa_env.chip_reg.DATA2.write(.status(status2), .value('h5), .path(UVM_BACKDOOR));
//                     while (data2 != 'h5 || data3 != 'h1 ) begin
//                       #1us;
//                     end
//                     #1ms;
//
//           sa_env.chip_reg.DATA3.write(.status(status3), .value('h1), .path(UVM_BACKDOOR));//write 
//           sa_env.chip_reg.DATA2.write(.status(status2), .value('h6), .path(UVM_BACKDOOR));
//                     while (data2 != 'h6 || data3 != 'h1 ) begin
//                       #1us;
//                     end
//                       #1ms;
//
//--------------------------------------------final response----------------------------//
                     while (data0!= 'h3 || data1 != 'h1 ) begin
                       #1us;
                     end
                     sa_env.chip_reg.DATA3.write(.status(status3), .value('h1), .path(UVM_BACKDOOR));//write 3,1
                     sa_env.chip_reg.DATA2.write(.status(status2), .value('h3), .path(UVM_BACKDOOR));
                       #90ns;
                 `uvm_info("---SUCCEED---",$psprintf("Simulation completed succeessfully !"),UVM_LOW)
$finish;

								                    #18s;
		     phase.drop_objection(phase);
		endtask: main_phase

    task writable_register;
      while (( data0 == m )||(data0[7:4]==0 )) begin
            #1us;
      end
        m = data0;

          #1us;
          if ((data0 == 'h20)||(data0 == 'h21)) begin
            uvm_hdl_read("soc_tb.DUT.u_dig_top.u_aon_domain.u_scu.pclk", read_value_IP); register_name="SCU";
          end else if ((data0 == 'h22)||(data0 == 'h23)) begin
            uvm_hdl_read("soc_tb.DUT.u_dig_top.u_aon_domain.u_gpio.U_apb_gpio_apbif.pclk", read_value_IP); register_name="GPIO";
          end else if ((data0 == 'h24)||(data0 == 'h25)) begin
            uvm_hdl_read("soc_tb.DUT.u_dig_top.u_sys_domain.u_sys_main.i_wdt.U_DW_apb_wdt_biu.pclk", read_value_IP);register_name="WDT ";
          end else if ((data0 == 'h26)||(data0 == 'h27)) begin
            uvm_hdl_read("soc_tb.DUT.u_dig_top.u_aon_domain.u_rtc.uRtcApbif.PCLK", read_value_IP); register_name="RTC ";
          end else if ((data0 == 'h28)||(data0 == 'h29)) begin
            uvm_hdl_read("soc_tb.DUT.u_dig_top.u_peri_domain.u_peri_main.i_uart0.pclk", read_value_IP); register_name="UART0. ";
          end else if ((data0 == 'h2a)||(data0 == 'h2b)) begin
            uvm_hdl_read("soc_tb.DUT.u_dig_top.u_sys_domain.u_sys_main.i_uart1.pclk", read_value_IP); register_name="UART1. ";
          end else if ((data0 == 'h2c)||(data0 == 'h2d)) begin
            uvm_hdl_read("soc_tb.DUT.u_dig_top.u_sys_domain.u_sys_main.i_ssim1.U_biu.pclk", read_value_IP); register_name="ssim1";
          end else if ((data0 == 'h2e)||(data0 == 'h2f)) begin
            uvm_hdl_read("soc_tb.DUT.u_dig_top.u_peri_domain.u_peri_main.i_ssis1.U_biu.pclk", read_value_IP); register_name="ssis1";
          end else if ((data0 == 'h30)||(data0 == 'h31)) begin
            uvm_hdl_read("soc_tb.DUT.u_dig_top.u_sys_domain.u_sys_main.i_i2sm.U_I2S_regmap.pclk", read_value_IP);  register_name="i2sm.";
          end else if ((data0 == 'h32)||(data0 == 'h33)) begin
            uvm_hdl_read("soc_tb.DUT.u_dig_top.u_sys_domain.u_sys_main.i_i2ss.U_I2S_regmap.pclk", read_value_IP); register_name="i2ss";
          end else if ((data0 == 'h34)||(data0 == 'h35)) begin
            uvm_hdl_read("soc_tb.DUT.u_dig_top.u_sys_domain.u_sys_main.i_timers.U_apbif.pclk", read_value_IP); register_name="timers.";
          end else if ((data0 == 'h36)||(data0 == 'h37)) begin
            uvm_hdl_read("soc_tb.DUT.u_dig_top.u_sys_domain.u_sys_main.i_i2c.U_DW_apb_i2c_biu.pclk", read_value_IP); register_name="i2c.";
          end else if ((data0 == 'h38)||(data0 == 'h39)) begin
            uvm_hdl_read("soc_tb.DUT.u_dig_top.u_aon_domain.u_scu.u_clk_gen.pclk_flash_c", read_value_IP);  register_name="pclk_flash_c";
          end else if ((data0 == 'h3a)||(data0 == 'h3b)) begin
            uvm_hdl_read("soc_tb.DUT.u_dig_top.u_bb_domain.u_rw_btdm_top_wrap.u_apb_eg_slave_reg.pclk", read_value_IP); register_name="rf";
          end else if ((data0 == 'h3c)||(data0 == 'h3d)) begin
            uvm_hdl_read("soc_tb.DUT.u_dig_top.u_bb_domain.pclk", read_value_IP); register_name="pclkbb";          
          end else if ((data0 == 'h3e)||(data0 == 'h3f)) begin
            uvm_hdl_read("soc_tb.DUT.u_dig_top.u_bb_domain.hclk", read_value_IP); register_name="hclkbb";
          end else if ((data0 == 'h40)||(data0 == 'h41)) begin
            uvm_hdl_read("soc_tb.DUT.u_dig_top.u_sys_domain.u_sys_main.i_dmac.hclk", read_value_IP); register_name="dma";
          end else if ((data0 == 'h42)||(data0 == 'h43)) begin
            uvm_hdl_read("soc_tb.DUT.u_dig_top.u_sys_domain.u_sys_main.i_spim0.U_ahb_sbiu.hclk", read_value_IP); register_name="spim0";
          end else if ((data0 == 'h44)||(data0 == 'h45)) begin
            uvm_hdl_read("soc_tb.DUT.u_dig_top.u_sys_domain.u_sys_main.CortexM3.TRACECLKIN", read_value_IP); register_name="cpu_trace_clk";
          end else if ((data0 == 'h46)||(data0 == 'h47)) begin
            uvm_hdl_read("soc_tb.DUT.u_dig_top.u_usb_domain.u_usb_ctl.U_DWC_otg_core.U_DWC_otg_power_dn.U_DWC_otg_aiu.hclk", read_value_IP); register_name="usb_clk";

             end


            for( u=0;u<10;u++) begin 
                if (((data0[0]=='h0)&&(read_value_IP==0))||((data0[0]=='h1)&&(read_value_IP==1))||(data0 == 'h20)||(data0 == 'h21)||(data0 == 'h38)||(data0 == 'h39)||(data0 > 'h47)) begin
                sa_env.chip_reg.DATA3.write(.status(status3), .value('h1), .path(UVM_BACKDOOR));//wri
          `uvm_info("RIGHT",$psprintf("CPU write value to %0s is succeed ! read %0s=%0x\n",register_name,register_name,read_value_IP),UVM_LOW)
                break;end 
                 else 
          `uvm_error("ERROR",$psprintf("CPU write value to %0s is wrong! read %0s=%0x\n",register_name,register_name,read_value_IP))

                 #111us;     
          if ((data0 == 'h20)||(data0 == 'h21)) begin
            uvm_hdl_read("soc_tb.DUT.u_dig_top.u_aon_domain.u_scu.pclk", read_value_IP); register_name="SCU";
          end else if ((data0 == 'h22)||(data0 == 'h23)) begin
            uvm_hdl_read("soc_tb.DUT.u_dig_top.u_aon_domain.u_gpio.U_apb_gpio_apbif.pclk", read_value_IP); register_name="GPIO";
          end else if ((data0 == 'h24)||(data0 == 'h25)) begin
            uvm_hdl_read("soc_tb.DUT.u_dig_top.u_sys_domain.u_sys_main.i_wdt.U_DW_apb_wdt_biu.pclk", read_value_IP);register_name="WDT ";
          end else if ((data0 == 'h26)||(data0 == 'h27)) begin
            uvm_hdl_read("soc_tb.DUT.u_dig_top.u_aon_domain.u_rtc.uRtcApbif.PCLK", read_value_IP); register_name="RTC ";
          end else if ((data0 == 'h28)||(data0 == 'h29)) begin
            uvm_hdl_read("soc_tb.DUT.u_dig_top.u_peri_domain.u_peri_main.i_uart0.pclk", read_value_IP); register_name="UART0. ";
          end else if ((data0 == 'h2a)||(data0 == 'h2b)) begin
            uvm_hdl_read("soc_tb.DUT.u_dig_top.u_sys_domain.u_sys_main.i_uart1.pclk", read_value_IP); register_name="UART1. ";
          end else if ((data0 == 'h2c)||(data0 == 'h2d)) begin
            uvm_hdl_read("soc_tb.DUT.u_dig_top.u_sys_domain.u_sys_main.i_ssim1.U_biu.pclk", read_value_IP); register_name="ssim1";
          end else if ((data0 == 'h2e)||(data0 == 'h2f)) begin
            uvm_hdl_read("soc_tb.DUT.u_dig_top.u_peri_domain.u_peri_main.i_ssis1.U_biu.pclk", read_value_IP); register_name="ssis1";
          end else if ((data0 == 'h30)||(data0 == 'h31)) begin
            uvm_hdl_read("soc_tb.DUT.u_dig_top.u_sys_domain.u_sys_main.i_i2sm.U_I2S_regmap.pclk", read_value_IP);  register_name="i2sm.";
          end else if ((data0 == 'h32)||(data0 == 'h33)) begin
            uvm_hdl_read("soc_tb.DUT.u_dig_top.u_sys_domain.u_sys_main.i_i2ss.U_I2S_regmap.pclk", read_value_IP); register_name="i2ss";
          end else if ((data0 == 'h34)||(data0 == 'h35)) begin
            uvm_hdl_read("soc_tb.DUT.u_dig_top.u_sys_domain.u_sys_main.i_timers.U_apbif.pclk", read_value_IP); register_name="timers.";
          end else if ((data0 == 'h36)||(data0 == 'h37)) begin
            uvm_hdl_read("soc_tb.DUT.u_dig_top.u_sys_domain.u_sys_main.i_i2c.U_DW_apb_i2c_biu.pclk", read_value_IP); register_name="i2c.";
          end else if ((data0 == 'h38)||(data0 == 'h39)) begin
            uvm_hdl_read("soc_tb.DUT.u_dig_top.u_aon_domain.u_scu.u_clk_gen.pclk_flash_c", read_value_IP);  register_name="pclk_flash_c";
          end else if ((data0 == 'h3a)||(data0 == 'h3b)) begin
            uvm_hdl_read("soc_tb.DUT.u_dig_top.u_bb_domain.u_rw_btdm_top_wrap.u_apb_eg_slave_reg.pclk", read_value_IP); register_name="rf";
          end else if ((data0 == 'h3c)||(data0 == 'h3d)) begin
            uvm_hdl_read("soc_tb.DUT.u_dig_top.u_bb_domain.pclk", read_value_IP); register_name="pclkbb";          
          end else if ((data0 == 'h3e)||(data0 == 'h3f)) begin
            uvm_hdl_read("soc_tb.DUT.u_dig_top.u_bb_domain.hclk", read_value_IP); register_name="hclkbb";
          end else if ((data0 == 'h40)||(data0 == 'h41)) begin
            uvm_hdl_read("soc_tb.DUT.u_dig_top.u_sys_domain.u_sys_main.i_dmac.hclk", read_value_IP); register_name="dma";
          end else if ((data0 == 'h42)||(data0 == 'h43)) begin
            uvm_hdl_read("soc_tb.DUT.u_dig_top.u_sys_domain.u_sys_main.i_spim0.U_ahb_sbiu.hclk", read_value_IP); register_name="spim0";
          end else if ((data0 == 'h44)||(data0 == 'h45)) begin
            uvm_hdl_read("soc_tb.DUT.u_dig_top.u_sys_domain.u_sys_main.CortexM3.TRACECLKIN", read_value_IP); register_name="cpu_trace_clk";
          end else if ((data0 == 'h46)||(data0 == 'h47)) begin
            uvm_hdl_read("soc_tb.DUT.u_dig_top.u_usb_domain.u_usb_ctl.U_DWC_otg_core.U_DWC_otg_power_dn.U_DWC_otg_aiu.hclk", read_value_IP); register_name="usb_clk";

             end
              end
      //        if (((data0[0]=='h0)&&(read_value_IP==0))||((data0[0]=='h1)&&(read_value_IP==1))||(data0 == 'h20)||(data0 == 'h21)) begin 
        //        sa_env.chip_reg.DATA3.write(.status(status3), .value('h1), .path(UVM_BACKDOOR));//wri
          //      `uvm_info("RIGHT",$psprintf("CPU write value to %0s is succeed ! read %0s=%0x\n",register_name,register_name,read_value_IP),UVM_LOW)
           if (u == 10) begin 
                `uvm_info("ERROR",$psprintf("CPU write value to %0s is failed ! %0s =%0x\n", register_name,register_name,read_value_IP),UVM_LOW)
                sa_env.chip_reg.DATA3.write(.status(status3), .value('h0), .path(UVM_BACKDOOR));//wri
                end
              sa_env.chip_reg.DATA2.write(.status(status2), .value(data0), .path(UVM_BACKDOOR));
          
                  s[15:0] = m[15:0] + 'h1;
//                  while(data2 != m) #1us; 
//                  if(data2 == 'h3f) #100ms; else #1us;

    endtask: writable_register  


//    task read_only_register(int q, string ro_register_name);
//
//          if (q == 'hf) begin
//            sa_env.chip_reg.IC_INTR_STAT.write(.status(status_IP), .value(o), .path(UVM_BACKDOOR));s[31:16] = 'hf;
//          end else if(q == 'h11) begin  
//            uvm_hdl_force("soc_tb.DUT.u_dig_top.u_sys_domain.u_sys_main.i_i2c.ic_raw_intr_stat[14:0]", o);s[31:16] = 'h11; 
//          end else if(q == 'h14) begin  
//            sa_env.chip_reg.IC_CLR_INTR.write(.status(status_IP), .value(o), .path(UVM_BACKDOOR));s[31:16] = 'h14;
//          end else if(q == 'h15) begin  
//            sa_env.chip_reg.IC_RX_UNDER.write(.status(status_IP), .value(o), .path(UVM_BACKDOOR));s[31:16] = 'h15;
//          end else if(q == 'h16) begin  
//            sa_env.chip_reg.IC_RX_OVER.write(.status(status_IP), .value(o), .path(UVM_BACKDOOR));s[31:16] = 'h16;
//          end else if(q == 'h17) begin  
//            sa_env.chip_reg.IC_TX_OVER.write(.status(status_IP), .value(o), .path(UVM_BACKDOOR));s[31:16] = 'h17;
//          end else if(q == 'h18) begin  
//            sa_env.chip_reg.IC_RD_REQ.write(.status(status_IP), .value(o), .path(UVM_BACKDOOR));s[31:16] = 'h18;
//          end else if(q == 'h19) begin  
//            sa_env.chip_reg.IC_TX_ABRT.write(.status(status_IP), .value(o), .path(UVM_BACKDOOR));s[31:16] = 'h19;
//          end else if(q == 'h1a) begin  
//            sa_env.chip_reg.IC_RX_DONE.write(.status(status_IP), .value(o), .path(UVM_BACKDOOR));s[31:16] = 'h1a;
//          end else if(q == 'h1b) begin  
//            sa_env.chip_reg.IC_ACTIVITY.write(.status(status_IP), .value(o), .path(UVM_BACKDOOR));s[31:16] = 'h1b;
//          end else if(q == 'h1c) begin  
//            sa_env.chip_reg.IC_STOP_DET.write(.status(status_IP), .value(o), .path(UVM_BACKDOOR));s[31:16] = 'h1c;
//          end else if(q == 'h1d) begin  
//            sa_env.chip_reg.IC_START_DET.write(.status(status_IP), .value(o), .path(UVM_BACKDOOR));s[31:16] = 'h1d;
//          end else if(q == 'h1e) begin  
//            sa_env.chip_reg.IC_GEN_CALL.write(.status(status_IP), .value(o), .path(UVM_BACKDOOR));s[31:16] = 'h1e;
//          end else if(q == 'h20) begin  
//            uvm_hdl_force("soc_tb.DUT.u_dig_top.u_sys_domain.u_sys_main.i_i2c.U_DW_apb_i2c_regfile.ic_status[6:0]", o);s[31:16] = 'h20; 
//          end else if(q == 'h21) begin  
//            sa_env.chip_reg.IC_TXFLR.write(.status(status_IP), .value(o), .path(UVM_BACKDOOR));s[31:16] = 'h21;
//          end else if(q == 'h22) begin  
//            sa_env.chip_reg.IC_RXFLR.write(.status(status_IP), .value(o), .path(UVM_BACKDOOR));s[31:16] = 'h22;
//    
//         end
//            if ((s[31:16] == 'h15) || (s[31:16] == 'h16) || (s[31:16] == 'h17) || (s[31:16] == 'h18) || (s[31:16] == 'h19) || (s[31:16] == 'h1a) || (s[31:16] == 'h1b) || (s[31:16] == 'h1c) || (s[31:16] == 'h1d) || (s[31:16] == 'h1e) || (s[31:16] == 'h21) || (s[31:16] == 'h22)) begin 
//            sa_env.chip_reg.DATA3.write(.status(status3), .value('h0), .path(UVM_BACKDOOR));end
//            else begin
//          sa_env.chip_reg.DATA3.write(.status(status3), .value(o), .path(UVM_BACKDOOR));
//            end
//            sa_env.chip_reg.DATA2.write(.status(status2), .value(s), .path(UVM_BACKDOOR));
//            `uvm_info("IP REGISTER",$psprintf("TB write value to %0s=%0x\n",ro_register_name,o),UVM_LOW)
//
//          while (data0 != s || data1 != 'h1) begin
//            #1us;  
//            end
//
//               o = o*2;
//               s = s + 'h1;
//    endtask: read_only_register  
endclass: chip_clk
