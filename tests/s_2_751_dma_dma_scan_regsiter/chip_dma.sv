`include "chip_defines.sv"

class chip_dma extends chip_base_test;

		`uvm_component_utils(chip_dma)

      int i=16'h0; // for print of data0;
      int j=16'h0; // for print of data1;    
      int k=16'h0; // for print of data2; 
      int l=16'h0; // for print of data3;
      int m=32'h0; // basic data0 with high_bit and low_bit;
      int n=32'd0; // cycle times
      int o=32'h1; // value of data3 and register for print    
      int p=32'd2; // cycle times                    
      int q=32'd2; // read_only register selected                    
      int s=32'h6d0020; // for data2

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

         join_none;


//           while (data0 != 'h4 || data1 != 'h1 ) begin    // read data0=4,data1=1                                                                           
//             #1us;
//           end
//           sa_env.chip_reg.DATA3.write(.status(status3), .value('h1510), .path(UVM_BACKDOOR));//write 1,1510
//           sa_env.chip_reg.DATA2.write(.status(status2), .value('h1), .path(UVM_BACKDOOR));
//           while (data0 != 'h2 || data1 != 'h1510 ) begin
//             #1us;
//           end
//             sa_env.chip_reg.DATA3.write(.status(status3), .value('h1), .path(UVM_BACKDOOR));//write 2,1
//             sa_env.chip_reg.DATA2.write(.status(status2), .value('h2), .path(UVM_BACKDOOR));
//             while (  data2 != 'h2  ||  data3 != 'h1) begin
//               #1us;
//               end
     
//-------------------------------------------- Traversal of writable registers----------------------------//

        //        `uvm_info("PAUSE",$psprintf("cycle for data0",),UVM_LOW)
                for (n=0; n<10000;n++) begin
                  while (data0 == m) begin
                     #1us;
                                     end
        //        `uvm_info("PAUSE",$psprintf("before register",),UVM_LOW)
                if (data0 == 'h5) break;
                writable_register;
        //        `uvm_info("PAUSE",$psprintf("after register",),UVM_LOW)
                end 

      //   join_any; 
      //   disable fork;

           sa_env.chip_reg.DATA3.write(.status(status3), .value('h1), .path(UVM_BACKDOOR));//write 
           sa_env.chip_reg.DATA2.write(.status(status2), .value('h5), .path(UVM_BACKDOOR));
                     while (data2 != 'h5 || data3 != 'h1 ) begin
                       #1us;
                     end
                       #1ms;

         o = 'h1; for (n = 0 ; n < 8; n++) begin read_only_register('h59, "DMA_IR_RST"); end
         o = 'h1; for (n = 0 ; n < 8; n++) begin read_only_register('h5a, "DMA_IR_RSB"); end
         o = 'h1; for (n = 0 ; n < 8; n++) begin read_only_register('h5b, "DMA_IR_RSST"); end
         o = 'h1; for (n = 0 ; n < 8; n++) begin read_only_register('h5c, "DMA_IR_RSDT"); end
         o = 'h1; for (n = 0 ; n < 8; n++) begin read_only_register('h5d, "DMA_IR_RSER"); end
         o = 'h1; for (n = 0 ; n < 8; n++) begin read_only_register('h5e, "DMA_IR_ST"); end
         o = 'h1; for (n = 0 ; n < 8; n++) begin read_only_register('h5f, "DMA_IR_SB"); end
         o = 'h1; for (n = 0 ; n < 8; n++) begin read_only_register('h60, "DMA_IR_SST"); end
         o = 'h1; for (n = 0 ; n < 8; n++) begin read_only_register('h61, "DMA_IR_SDT"); end
         o = 'h1; for (n = 0 ; n < 8; n++) begin read_only_register('h62, "DMA_IR_SER"); end
         o = 'h1; for (n = 0 ; n < 5; n++) begin read_only_register('h6d, "DMA_IR_SI"); end

           sa_env.chip_reg.DATA3.write(.status(status3), .value('h1), .path(UVM_BACKDOOR));//write 
           sa_env.chip_reg.DATA2.write(.status(status2), .value('h6), .path(UVM_BACKDOOR));
                     while (data2 != 'h6 || data3 != 'h1 ) begin
                       #1us;
                     end
                       #1ms;

//--------------------------------------------final response----------------------------//
                     while (data0!= 'h3 || data1 != 'h1 ) begin
                       #1us;
                     end
                     sa_env.chip_reg.DATA3.write(.status(status3), .value('h1), .path(UVM_BACKDOOR));//write 3,1
                     sa_env.chip_reg.DATA2.write(.status(status2), .value('h3), .path(UVM_BACKDOOR));
                       #90ns;
                 `uvm_info("---SUCCEED---",$psprintf("Simulation completed succeessfully !"),UVM_LOW)
$finish ;
								                    #18s;
		     phase.drop_objection(phase);
		endtask: main_phase

    task writable_register;
      while ( data0 == m || data0[31:16] == 'h0) begin
            #1us;
      end
        m = data0;

          #1us;
          if (data0[31:16] == 'h1) begin
              uvm_hdl_read("soc_tb.DUT.u_dig_top.u_sys_domain.u_sys_main.i_dmac.U_ch_top_0.sar", read_value_IP); register_name = "CHR[0].SAR";
          end else if (data0[31:16] == 'h2) begin
              uvm_hdl_read("soc_tb.DUT.u_dig_top.u_sys_domain.u_sys_main.i_dmac.U_ch_top_0.dar", read_value_IP); register_name = "CHR[0].DAR";
          end else if (data0[31:16] == 'h3) begin
              uvm_hdl_read("soc_tb.DUT.u_dig_top.u_sys_domain.u_sys_main.i_dmac.U_ch_top_0.llp", read_value_IP); register_name = "CHR[0].LLP";
          end else if (data0[31:16] == 'h4) begin
              uvm_hdl_read("soc_tb.DUT.u_dig_top.u_sys_domain.u_sys_main.i_dmac.U_ch_top_0.ctl[31:0]", read_value_IP); register_name = "CHR[0].CTL0";
          end else if (data0[31:16] == 'h5) begin
              uvm_hdl_read("soc_tb.DUT.u_dig_top.u_sys_domain.u_sys_main.i_dmac.U_ch_top_0.ctl[44:32]", read_value_IP); register_name = "CHR[0].CTL1";
          end else if (data0[31:16] == 'ha) begin
              uvm_hdl_read("soc_tb.DUT.u_dig_top.u_sys_domain.u_sys_main.i_dmac.U_ch_top_0.cfg[31:0]", read_value_IP); register_name = "CHR[0].CFG0";
          end else if (data0[31:16] == 'hb) begin
              uvm_hdl_read("soc_tb.DUT.u_dig_top.u_sys_domain.u_sys_main.i_dmac.U_ch_top_0.cfg[46:32]", read_value_IP); register_name = "CHR[0].CFG1";
          end else if (data0[31:16] == 'hc) begin
              uvm_hdl_read("soc_tb.DUT.u_dig_top.u_sys_domain.u_sys_main.i_dmac.U_ch_top_1.sar", read_value_IP); register_name = "CHR[1].SAR";
          end else if (data0[31:16] == 'hd) begin
              uvm_hdl_read("soc_tb.DUT.u_dig_top.u_sys_domain.u_sys_main.i_dmac.U_ch_top_1.dar", read_value_IP); register_name = "CHR[1].DAR";
          end else if (data0[31:16] == 'he) begin
              uvm_hdl_read("soc_tb.DUT.u_dig_top.u_sys_domain.u_sys_main.i_dmac.U_ch_top_1.llp", read_value_IP); register_name = "CHR[1].LLP";
          end else if (data0[31:16] == 'hf) begin
              uvm_hdl_read("soc_tb.DUT.u_dig_top.u_sys_domain.u_sys_main.i_dmac.U_ch_top_1.ctl[31:0]", read_value_IP); register_name = "CHR[1].CTL0";
          end else if (data0[31:16] == 'h10) begin
              uvm_hdl_read("soc_tb.DUT.u_dig_top.u_sys_domain.u_sys_main.i_dmac.U_ch_top_1.ctl[44:32]", read_value_IP); register_name = "CHR[1].CTL1";
          end else if (data0[31:16] == 'h15) begin
              uvm_hdl_read("soc_tb.DUT.u_dig_top.u_sys_domain.u_sys_main.i_dmac.U_ch_top_1.cfg[31:0]", read_value_IP); register_name = "CHR[1].CFG0";
          end else if (data0[31:16] == 'h16) begin
              uvm_hdl_read("soc_tb.DUT.u_dig_top.u_sys_domain.u_sys_main.i_dmac.U_ch_top_1.cfg[46:32]", read_value_IP); register_name = "CHR[1].CFG1";
          end else if (data0[31:16] == 'h17) begin
              uvm_hdl_read("soc_tb.DUT.u_dig_top.u_sys_domain.u_sys_main.i_dmac.U_ch_top_2.sar", read_value_IP); register_name = "CHR[2].SAR";
          end else if (data0[31:16] == 'h18) begin
              uvm_hdl_read("soc_tb.DUT.u_dig_top.u_sys_domain.u_sys_main.i_dmac.U_ch_top_2.dar", read_value_IP); register_name = "CHR[2].DAR";
          end else if (data0[31:16] == 'h19) begin
              uvm_hdl_read("soc_tb.DUT.u_dig_top.u_sys_domain.u_sys_main.i_dmac.U_ch_top_2.llp", read_value_IP); register_name = "CHR[2].LLP";
          end else if (data0[31:16] == 'h1a) begin
              uvm_hdl_read("soc_tb.DUT.u_dig_top.u_sys_domain.u_sys_main.i_dmac.U_ch_top_2.ctl[31:0]", read_value_IP); register_name = "CHR[2].CTL0";
          end else if (data0[31:16] == 'h1b) begin
              uvm_hdl_read("soc_tb.DUT.u_dig_top.u_sys_domain.u_sys_main.i_dmac.U_ch_top_2.ctl[44:32]", read_value_IP); register_name = "CHR[2].CTL1";
          end else if (data0[31:16] == 'h20) begin
              uvm_hdl_read("soc_tb.DUT.u_dig_top.u_sys_domain.u_sys_main.i_dmac.U_ch_top_2.cfg[31:0]", read_value_IP); register_name = "CHR[2].CFG0";
          end else if (data0[31:16] == 'h21) begin
              uvm_hdl_read("soc_tb.DUT.u_dig_top.u_sys_domain.u_sys_main.i_dmac.U_ch_top_2.cfg[46:32]", read_value_IP); register_name = "CHR[2].CFG1";
          end else if (data0[31:16] == 'h22) begin
              uvm_hdl_read("soc_tb.DUT.u_dig_top.u_sys_domain.u_sys_main.i_dmac.U_ch_top_3.sar", read_value_IP); register_name = "CHR[3].SAR";
          end else if (data0[31:16] == 'h23) begin
              uvm_hdl_read("soc_tb.DUT.u_dig_top.u_sys_domain.u_sys_main.i_dmac.U_ch_top_3.dar", read_value_IP); register_name = "CHR[3].DAR";
          end else if (data0[31:16] == 'h24) begin
              uvm_hdl_read("soc_tb.DUT.u_dig_top.u_sys_domain.u_sys_main.i_dmac.U_ch_top_3.llp", read_value_IP); register_name = "CHR[3].LLP";
          end else if (data0[31:16] == 'h25) begin
              uvm_hdl_read("soc_tb.DUT.u_dig_top.u_sys_domain.u_sys_main.i_dmac.U_ch_top_3.ctl[31:0]", read_value_IP); register_name = "CHR[3].CTL0";
          end else if (data0[31:16] == 'h26) begin
              uvm_hdl_read("soc_tb.DUT.u_dig_top.u_sys_domain.u_sys_main.i_dmac.U_ch_top_3.ctl[44:32]", read_value_IP); register_name = "CHR[3].CTL1";
          end else if (data0[31:16] == 'h2b) begin
              uvm_hdl_read("soc_tb.DUT.u_dig_top.u_sys_domain.u_sys_main.i_dmac.U_ch_top_3.cfg[31:0]", read_value_IP); register_name = "CHR[3].CFG0";
          end else if (data0[31:16] == 'h2c) begin
              uvm_hdl_read("soc_tb.DUT.u_dig_top.u_sys_domain.u_sys_main.i_dmac.U_ch_top_3.cfg[46:32]", read_value_IP); register_name = "CHR[3].CFG1";
          end else if (data0[31:16] == 'h2d) begin
              uvm_hdl_read("soc_tb.DUT.u_dig_top.u_sys_domain.u_sys_main.i_dmac.U_ch_top_4.sar", read_value_IP); register_name = "CHR[4].SAR";
          end else if (data0[31:16] == 'h2e) begin
              uvm_hdl_read("soc_tb.DUT.u_dig_top.u_sys_domain.u_sys_main.i_dmac.U_ch_top_4.dar", read_value_IP); register_name = "CHR[4].DAR";
          end else if (data0[31:16] == 'h2f) begin
              uvm_hdl_read("soc_tb.DUT.u_dig_top.u_sys_domain.u_sys_main.i_dmac.U_ch_top_4.llp", read_value_IP); register_name = "CHR[4].LLP";
          end else if (data0[31:16] == 'h30) begin
              uvm_hdl_read("soc_tb.DUT.u_dig_top.u_sys_domain.u_sys_main.i_dmac.U_ch_top_4.ctl[31:0]", read_value_IP); register_name = "CHR[4].CTL0";
          end else if (data0[31:16] == 'h31) begin
              uvm_hdl_read("soc_tb.DUT.u_dig_top.u_sys_domain.u_sys_main.i_dmac.U_ch_top_4.ctl[44:32]", read_value_IP); register_name = "CHR[4].CTL1";
          end else if (data0[31:16] == 'h36) begin
              uvm_hdl_read("soc_tb.DUT.u_dig_top.u_sys_domain.u_sys_main.i_dmac.U_ch_top_4.cfg[31:0]", read_value_IP); register_name = "CHR[4].CFG0";
          end else if (data0[31:16] == 'h37) begin
              uvm_hdl_read("soc_tb.DUT.u_dig_top.u_sys_domain.u_sys_main.i_dmac.U_ch_top_4.cfg[46:32]", read_value_IP); register_name = "CHR[4].CFG1";
          end else if (data0[31:16] == 'h38) begin
              uvm_hdl_read("soc_tb.DUT.u_dig_top.u_sys_domain.u_sys_main.i_dmac.U_ch_top_5.sar", read_value_IP); register_name = "CHR[5].SAR";
          end else if (data0[31:16] == 'h39) begin
              uvm_hdl_read("soc_tb.DUT.u_dig_top.u_sys_domain.u_sys_main.i_dmac.U_ch_top_5.dar", read_value_IP); register_name = "CHR[5].DAR";
          end else if (data0[31:16] == 'h3a) begin
              uvm_hdl_read("soc_tb.DUT.u_dig_top.u_sys_domain.u_sys_main.i_dmac.U_ch_top_5.llp", read_value_IP); register_name = "CHR[5].LLP";
          end else if (data0[31:16] == 'h3b) begin
              uvm_hdl_read("soc_tb.DUT.u_dig_top.u_sys_domain.u_sys_main.i_dmac.U_ch_top_5.ctl[31:0]", read_value_IP); register_name = "CHR[5].CTL0";
          end else if (data0[31:16] == 'h3c) begin
              uvm_hdl_read("soc_tb.DUT.u_dig_top.u_sys_domain.u_sys_main.i_dmac.U_ch_top_5.ctl[44:32]", read_value_IP); register_name = "CHR[5].CTL1";
          end else if (data0[31:16] == 'h41) begin
              uvm_hdl_read("soc_tb.DUT.u_dig_top.u_sys_domain.u_sys_main.i_dmac.U_ch_top_5.cfg[31:0]", read_value_IP); register_name = "CHR[5].CFG0";
          end else if (data0[31:16] == 'h42) begin
              uvm_hdl_read("soc_tb.DUT.u_dig_top.u_sys_domain.u_sys_main.i_dmac.U_ch_top_5.cfg[46:32]", read_value_IP); register_name = "CHR[5].CFG1";
          end else if (data0[31:16] == 'h43) begin
              uvm_hdl_read("soc_tb.DUT.u_dig_top.u_sys_domain.u_sys_main.i_dmac.U_ch_top_6.sar", read_value_IP); register_name = "CHR[6].SAR";
          end else if (data0[31:16] == 'h44) begin
              uvm_hdl_read("soc_tb.DUT.u_dig_top.u_sys_domain.u_sys_main.i_dmac.U_ch_top_6.dar", read_value_IP); register_name = "CHR[6].DAR";
          end else if (data0[31:16] == 'h45) begin
              uvm_hdl_read("soc_tb.DUT.u_dig_top.u_sys_domain.u_sys_main.i_dmac.U_ch_top_6.llp", read_value_IP); register_name = "CHR[6].LLP";
          end else if (data0[31:16] == 'h46) begin
              uvm_hdl_read("soc_tb.DUT.u_dig_top.u_sys_domain.u_sys_main.i_dmac.U_ch_top_6.ctl[31:0]", read_value_IP); register_name = "CHR[6].CTL0";
          end else if (data0[31:16] == 'h47) begin
              uvm_hdl_read("soc_tb.DUT.u_dig_top.u_sys_domain.u_sys_main.i_dmac.U_ch_top_6.ctl[44:32]", read_value_IP); register_name = "CHR[6].CTL1";
          end else if (data0[31:16] == 'h4c) begin
              uvm_hdl_read("soc_tb.DUT.u_dig_top.u_sys_domain.u_sys_main.i_dmac.U_ch_top_6.cfg[31:0]", read_value_IP); register_name = "CHR[6].CFG0";
          end else if (data0[31:16] == 'h4d) begin
              uvm_hdl_read("soc_tb.DUT.u_dig_top.u_sys_domain.u_sys_main.i_dmac.U_ch_top_6.cfg[46:32]", read_value_IP); register_name = "CHR[6].CFG1";
          end else if (data0[31:16] == 'h4e) begin
              uvm_hdl_read("soc_tb.DUT.u_dig_top.u_sys_domain.u_sys_main.i_dmac.U_ch_top_7.sar", read_value_IP); register_name = "CHR[7].SAR";
          end else if (data0[31:16] == 'h4f) begin
              uvm_hdl_read("soc_tb.DUT.u_dig_top.u_sys_domain.u_sys_main.i_dmac.U_ch_top_7.dar", read_value_IP); register_name = "CHR[7].DAR";
          end else if (data0[31:16] == 'h50) begin
              uvm_hdl_read("soc_tb.DUT.u_dig_top.u_sys_domain.u_sys_main.i_dmac.U_ch_top_7.llp", read_value_IP); register_name = "CHR[7].LLP";
          end else if (data0[31:16] == 'h51) begin
              uvm_hdl_read("soc_tb.DUT.u_dig_top.u_sys_domain.u_sys_main.i_dmac.U_ch_top_7.ctl[31:0]", read_value_IP); register_name = "CHR[7].CTL0";
          end else if (data0[31:16] == 'h52) begin
              uvm_hdl_read("soc_tb.DUT.u_dig_top.u_sys_domain.u_sys_main.i_dmac.U_ch_top_7.ctl[44:32]", read_value_IP); register_name = "CHR[7].CTL1";
          end else if (data0[31:16] == 'h57) begin
              uvm_hdl_read("soc_tb.DUT.u_dig_top.u_sys_domain.u_sys_main.i_dmac.U_ch_top_7.cfg[31:0]", read_value_IP); register_name = "CHR[7].CFG0";
          end else if (data0[31:16] == 'h58) begin
              uvm_hdl_read("soc_tb.DUT.u_dig_top.u_sys_domain.u_sys_main.i_dmac.U_ch_top_7.cfg[46:32]", read_value_IP); register_name = "CHR[7].CFG1";
          end else if (data0[31:16] == 'h63) begin
              sa_env.chip_reg.DMA_IR_MT.read(.status(status3), .value(read_value_IP), .path(UVM_BACKDOOR)); register_name = "DMA_IR_MT";
          end else if (data0[31:16] == 'h64) begin
              sa_env.chip_reg.DMA_IR_MB.read(.status(status3), .value(read_value_IP), .path(UVM_BACKDOOR)); register_name = "DMA_IR_MB";
          end else if (data0[31:16] == 'h65) begin
              sa_env.chip_reg.DMA_IR_MST.read(.status(status3), .value(read_value_IP), .path(UVM_BACKDOOR)); register_name = "DMA_IR_MST";
          end else if (data0[31:16] == 'h66) begin
              sa_env.chip_reg.DMA_IR_MDT.read(.status(status3), .value(read_value_IP), .path(UVM_BACKDOOR)); register_name = "DMA_IR_MDT";
          end else if (data0[31:16] == 'h67) begin
              sa_env.chip_reg.DMA_IR_MR.read(.status(status3), .value(read_value_IP), .path(UVM_BACKDOOR)); register_name = "DMA_IR_MR";
          end else if (data0[31:16] == 'h68) begin
              sa_env.chip_reg.DMA_IR_CT.read(.status(status3), .value(read_value_IP), .path(UVM_BACKDOOR)); register_name = "DMA_IR_CT";
          end else if (data0[31:16] == 'h69) begin
              sa_env.chip_reg.DMA_IR_CB.read(.status(status3), .value(read_value_IP), .path(UVM_BACKDOOR)); register_name = "DMA_IR_CB";
          end else if (data0[31:16] == 'h6a) begin
              sa_env.chip_reg.DMA_IR_CST.read(.status(status3), .value(read_value_IP), .path(UVM_BACKDOOR)); register_name = "DMA_IR_CST";
          end else if (data0[31:16] == 'h6b) begin
              sa_env.chip_reg.DMA_IR_CDT.read(.status(status3), .value(read_value_IP), .path(UVM_BACKDOOR)); register_name = "DMA_IR_CDT";
          end else if (data0[31:16] == 'h6c) begin
              sa_env.chip_reg.DMA_IR_CER.read(.status(status3), .value(read_value_IP), .path(UVM_BACKDOOR)); register_name = "DMA_IR_CER";
          end else if (data0[31:16] == 'h6e) begin
              sa_env.chip_reg.DMA_SR_RSR.read(.status(status3), .value(read_value_IP), .path(UVM_BACKDOOR)); register_name = "DMA_SR_RSR";
          end else if (data0[31:16] == 'h6f) begin
              sa_env.chip_reg.DMA_SR_RDR.read(.status(status3), .value(read_value_IP), .path(UVM_BACKDOOR)); register_name = "DMA_SR_RDR";
          end else if (data0[31:16] == 'h70) begin
              sa_env.chip_reg.DMA_SR_SRSR.read(.status(status3), .value(read_value_IP), .path(UVM_BACKDOOR)); register_name = "DMA_SR_SRSR";
          end else if (data0[31:16] == 'h71) begin
              sa_env.chip_reg.DMA_SR_SRDR.read(.status(status3), .value(read_value_IP), .path(UVM_BACKDOOR)); register_name = "DMA_SR_SRDR";
          end else if (data0[31:16] == 'h72) begin
              sa_env.chip_reg.DMA_SR_LSR.read(.status(status3), .value(read_value_IP), .path(UVM_BACKDOOR)); register_name = "DMA_SR_LSR";
          end else if (data0[31:16] == 'h73) begin
              sa_env.chip_reg.DMA_SR_LDR.read(.status(status3), .value(read_value_IP), .path(UVM_BACKDOOR)); register_name = "DMA_SR_LDR";
          end else if (data0[31:16] == 'h74) begin
              sa_env.chip_reg.DMA_MR_CFG.read(.status(status3), .value(read_value_IP), .path(UVM_BACKDOOR)); register_name = "DMA_MR_CFG";
//          end else if (data0[31:16] == 'h75) begin
//              sa_env.chip_reg.DMA_MR_EN.read(.status(status3), .value(read_value_IP), .path(UVM_BACKDOOR)); register_name = "DMA_MR_EN";

          end

              if ((read_value_IP == data1) || (((data0[31:16]=='ha) || (data0[31:16]=='h15) || (data0[31:16]=='h20) || (data0[31:16]=='h2b) || (data0[31:16]=='h36) || (data0[31:16]=='h41) || (data0[31:16]=='h4c) || (data0[31:16]=='h57))&& (read_value_IP==data1+'h200)) || (data0[31:16]=='h68)|| (data0[31:16]=='h69)|| (data0[31:16]=='h6a)|| (data0[31:16]=='h6b)|| (data0[31:16]=='h6c)) begin 
                sa_env.chip_reg.DATA3.write(.status(status3), .value('h1), .path(UVM_BACKDOOR));//wri
                `uvm_info("RIGHT",$psprintf("CPU write value to %0s is succeed ! read %0s=%0x\n",register_name,register_name,read_value_IP),UVM_LOW)
              end else begin 
                `uvm_info("ERROR",$psprintf("CPU write value to %0s is failed ! %0s =%0x\n", register_name,register_name,read_value_IP),UVM_LOW)
                sa_env.chip_reg.DATA3.write(.status(status3), .value('h0), .path(UVM_BACKDOOR));//wri
              end 
              sa_env.chip_reg.DATA2.write(.status(status2), .value(data0), .path(UVM_BACKDOOR));
          
                  s[15:0] = m[15:0] + 'h1; 
//                  while(data2 != m) #1us; 
//                  if(data2[31:16] == 'h74) #100ms; else #1us;

    endtask: writable_register  


    task read_only_register(int q, string ro_register_name);

      if (q == 'h59) begin
        sa_env.chip_reg.DMA_IR_RST.write(.status(status_IP), .value(o), .path(UVM_BACKDOOR));s[31:16] = 'h59;
      end else if(q == 'h5a) begin  
        sa_env.chip_reg.DMA_IR_RSB.write(.status(status_IP), .value(o), .path(UVM_BACKDOOR));s[31:16] = 'h5a;
      end else if(q == 'h5b) begin
        sa_env.chip_reg.DMA_IR_RSST.write(.status(status_IP), .value(o), .path(UVM_BACKDOOR));s[31:16] = 'h5b;
      end else if(q == 'h5c) begin
        sa_env.chip_reg.DMA_IR_RSDT.write(.status(status_IP), .value(o), .path(UVM_BACKDOOR));s[31:16] = 'h5c;
      end else if(q == 'h5d) begin
        sa_env.chip_reg.DMA_IR_RSER.write(.status(status_IP), .value(o), .path(UVM_BACKDOOR));s[31:16] = 'h5d;
      end else if(q == 'h5e) begin
        sa_env.chip_reg.DMA_IR_ST.write(.status(status_IP), .value(o), .path(UVM_BACKDOOR));s[31:16] = 'h5e;
      end else if(q == 'h5f) begin
        sa_env.chip_reg.DMA_IR_SB.write(.status(status_IP), .value(o), .path(UVM_BACKDOOR));s[31:16] = 'h5f;
      end else if(q == 'h60) begin
        sa_env.chip_reg.DMA_IR_SST.write(.status(status_IP), .value(o), .path(UVM_BACKDOOR));s[31:16] = 'h60;
      end else if(q == 'h61) begin
        sa_env.chip_reg.DMA_IR_SDT.write(.status(status_IP), .value(o), .path(UVM_BACKDOOR));s[31:16] = 'h61;
      end else if(q == 'h62) begin
        sa_env.chip_reg.DMA_IR_SER.write(.status(status_IP), .value(o), .path(UVM_BACKDOOR));s[31:16] = 'h62;
      end else if(q == 'h6d) begin
        uvm_hdl_force("soc_tb.DUT.u_dig_top.u_sys_domain.u_sys_main.i_dmac.U_intrif.istatusint", o);s[31:16] = 'h6d;
    
     end
        if ((s[31:16] == 'h5e)||(s[31:16] == 'h5f)||(s[31:16] == 'h60)||(s[31:16] == 'h61)||(s[31:16] == 'h62)) begin 
        sa_env.chip_reg.DATA3.write(.status(status3), .value('h0), .path(UVM_BACKDOOR));end
        else begin
        sa_env.chip_reg.DATA3.write(.status(status3), .value(o), .path(UVM_BACKDOOR)); end
        sa_env.chip_reg.DATA2.write(.status(status2), .value(s), .path(UVM_BACKDOOR));
        `uvm_info("IP REGISTER",$psprintf("TB write value to %0s=%0x\n",ro_register_name,o),UVM_LOW)

      while (data0 != s || data1 != 'h1) begin
        #1us;  
        end

           o = o*2;
           s = s + 'h1;
    endtask: read_only_register  
endclass: chip_dma

