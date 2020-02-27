`include "chip_defines.sv"
`include "chip_def.inc"

class chip_scu extends chip_base_test;

		`uvm_component_utils(chip_scu)

      int i=16'h0; // for print of data0;
      int j=16'h0; // for print of data1;    
      int k=16'h0; // for print of data2; 
      int l=16'h0; // for print of data3;
      int m=32'h8; // basic data0 with high_bit and low_bit;
      int n=32'd0; // cycle times
      int o=32'h1; // value of data3 and register for print    
      int p=32'd2; // cycle times                    
      int q=32'd2; // read_only register selected                    
      int r=32'd0; // store value of data1                    
      int s=32'h20; // for data2

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
//           sa_env.chip_reg.DATA3.write(.status(status3), .value('h), .path(UVM_BACKDOOR));//write 1,
//           sa_env.chip_reg.DATA2.write(.status(status2), .value('h1), .path(UVM_BACKDOOR));
//           while (data0 != 'h2 || data1 != 'h ) begin
//             #1us;
//           end
//             sa_env.chip_reg.DATA3.write(.status(status3), .value('h1), .path(UVM_BACKDOOR));//write 2,1
//             sa_env.chip_reg.DATA2.write(.status(status2), .value('h2), .path(UVM_BACKDOOR));
//             while (  data2 != 'h2  ||  data3 != 'h1) begin
//               #1us;
//               end
     
                for (n=0; n<10000;n++) begin
                  while (data0 == m) begin
                     #1us;
                                     end
                  if (data0 == 'h5) break;
                  writable_register;
                end 

           sa_env.chip_reg.DATA3.write(.status(status3), .value('h1), .path(UVM_BACKDOOR));//write 
           sa_env.chip_reg.DATA2.write(.status(status2), .value('h5), .path(UVM_BACKDOOR));
                     while (data2 != 'h5 || data3 != 'h1 ) begin
                       #1us;
                     end
                     #1ms;

         o = 'h1; for (n = 0 ; n < 32; n++) begin read_only_register('h6,  "SCU_SYS_STATUS"); end
         o = 'h1; for (n = 0 ; n < 32; n++) begin read_only_register('h8,  "PWR_STATUS")    ; end
         o = 'h1; for (n = 0 ; n < 32; n++) begin read_only_register('ha,  "DEV_STATUS")    ; end
         o = 'h1; for (n = 0 ; n < 32; n++) begin read_only_register('h14, "ANA_STATUS0")   ; end
         o = 'h1; for (n = 0 ; n < 32; n++) begin read_only_register('h15, "ANA_STATUS1")   ; end
 //        o = 'h1; for (n = 0 ; n < 32; n++) begin read_only_register('h1b, "TIMER6CURRENT_COUNT"); end
 //        o = 'h1; for (n = 0 ; n < 32; n++) begin read_only_register('h20, "TIMER7CURRENT_COUNT"); end
 //        o = 'h1; for (n = 0 ; n < 32; n++) begin read_only_register('h25, "TIMER8CURRENT_COUNT"); end
 //        o = 'h1; for (n = 0 ; n < 1; n++) begin read_only_register('h5, "TIMER1INTSTATUS"); end
 //        o = 'h1; for (n = 0 ; n < 1; n++) begin read_only_register('ha, "TIMER2INTSTATUS"); end
 //        o = 'h1; for (n = 0 ; n < 1; n++) begin read_only_register('hf, "TIMER3INTSTATUS"); end
 //        o = 'h1; for (n = 0 ; n < 1; n++) begin read_only_register('h14, "TIMER4INTSTATUS"); end
 //        o = 'h1; for (n = 0 ; n < 1; n++) begin read_only_register('h19, "TIMER5INTSTATUS"); end
 //        o = 'h1; for (n = 0 ; n < 1; n++) begin read_only_register('h1e, "TIMER6INTSTATUS"); end
 //        o = 'h1; for (n = 0 ; n < 1; n++) begin read_only_register('h23, "TIMER7INTSTATUS"); end
 //        o = 'h1; for (n = 0 ; n < 1; n++) begin read_only_register('h28, "TIMER8INTSTATUS"); end
 //        o = 'h1; for (n = 0 ; n < 3; n++) begin read_only_register('h29, "INT_STATUS"); end
 //     //   o = 'h1; for (n = 0 ; n < 3; n++) begin read_only_register('h2a, "TIMEREOI"); end
 //        o = 'h1; for (n = 0 ; n < 3; n++) begin read_only_register('h2b, "RAW_INT_STATUS"); end

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
$finish;

								                    #18s;
		     phase.drop_objection(phase);
		endtask: main_phase

    task writable_register;
      while ( data0 == m || data0[31:16] == 'h0) begin
            #1us;
      end
        m = data0;

          #1us;
          if (data0[31:16] == 'h2) begin
              sa_env.chip_reg.SCU_SW_RST.read(.status(status_IP), .value(read_value_IP), .path(UVM_BACKDOOR)); register_name = "SCU_SW_RST";
          end else if (data0[31:16] == 'h3) begin                       
              sa_env.chip_reg.SCU_CLK_CTL.read(.status(status_IP), .value(read_value_IP), .path(UVM_BACKDOOR)); register_name = "SCU_CLK_CTL";
          end else if (data0[31:16] == 'h4) begin
              sa_env.chip_reg.SCU_CLK_DIV.read(.status(status_IP), .value(read_value_IP), .path(UVM_BACKDOOR)); register_name = "SCU_CLK_DIV";
          end else if (data0[31:16] == 'h5) begin
              sa_env.chip_reg.SCU_SYS_CONFIG.read(.status(status_IP), .value(read_value_IP), .path(UVM_BACKDOOR)); register_name = "SCU_SYS_CONFIG";
          end else if (data0[31:16] == 'h7) begin
              sa_env.chip_reg.SCU_SLEEP_EN.read(.status(status_IP), .value(read_value_IP), .path(UVM_BACKDOOR)); register_name = "SCU_SLEEP_EN";
          end else if (data0[31:16] == 'h9) begin
              sa_env.chip_reg.SCU_DEV_CONFIG.read(.status(status_IP), .value(read_value_IP), .path(UVM_BACKDOOR)); register_name = "SCU_DEV_CONFIG";
          end else if (data0[31:16] == 'hb) begin
              sa_env.chip_reg.SCU_IO_CONFIG.read(.status(status_IP), .value(read_value_IP), .path(UVM_BACKDOOR)); register_name = "SCU_IO_CONFIG";
          end else if (data0[31:16] == 'hd) begin
              sa_env.chip_reg.SCU_CLK_DIV1.read(.status(status_IP), .value(read_value_IP), .path(UVM_BACKDOOR)); register_name = "SCU_CLK_DIV1";
          end else if (data0[31:16] == 'he) begin
              sa_env.chip_reg.SCU_CLK_DIV2.read(.status(status_IP), .value(read_value_IP), .path(UVM_BACKDOOR)); register_name = "SCU_CLK_DIV2";
          end else if (data0[31:16] == 'hf) begin
              sa_env.chip_reg.SCU_ANA_CTL0.read(.status(status_IP), .value(read_value_IP), .path(UVM_BACKDOOR)); register_name = "SCU_ANA_CTL0";
          end else if (data0[31:16] == 'h10) begin
              sa_env.chip_reg.SCU_ANA_CTL1.read(.status(status_IP), .value(read_value_IP), .path(UVM_BACKDOOR)); register_name = "SCU_ANA_CTL1";
          end else if (data0[31:16] == 'h11) begin
              sa_env.chip_reg.SCU_ANA_CTL2.read(.status(status_IP), .value(read_value_IP), .path(UVM_BACKDOOR)); register_name = "SCU_ANA_CTL2";
          end else if (data0[31:16] == 'h12) begin
              sa_env.chip_reg.SCU_ANA_CTL3.read(.status(status_IP), .value(read_value_IP), .path(UVM_BACKDOOR)); register_name = "SCU_ANA_CTL3";
          end else if (data0[31:16] == 'h13) begin
              sa_env.chip_reg.SCU_ANA_CTL4.read(.status(status_IP), .value(read_value_IP), .path(UVM_BACKDOOR)); register_name = "SCU_ANA_CTL4";
          end else if (data0[31:16] == 'h16) begin
              sa_env.chip_reg.SCU_TIMERS_DIV1.read(.status(status_IP), .value(read_value_IP), .path(UVM_BACKDOOR)); register_name = "SCU_TIMERS_DIV1";
          end else if (data0[31:16] == 'h17) begin
              sa_env.chip_reg.SCU_TIMERS_DIV2.read(.status(status_IP), .value(read_value_IP), .path(UVM_BACKDOOR)); register_name = "SCU_TIMERS_DIV2";
          end else if (data0[31:16] == 'h18) begin
              sa_env.chip_reg.SCU_TIMERS_DIV3.read(.status(status_IP), .value(read_value_IP), .path(UVM_BACKDOOR)); register_name = "SCU_TIMERS_DIV3";
          end else if (data0[31:16] == 'h19) begin
              sa_env.chip_reg.SCU_TIMERS_DIV4.read(.status(status_IP), .value(read_value_IP), .path(UVM_BACKDOOR)); register_name = "SCU_TIMERS_DIV4";

          end
              if (data1=='h1) r=0;  // for timers
              if ((read_value_IP == data1)||(data0[31:16] == 'h2)||(data0[31:16] == 'h3)||(data0[31:16] == 'h4)||(data0[31:16] == 'h5)||(data0[31:16] == 'h7)||(data0[31:16] == 'h9)||(data0[31:16] == 'hb)||(data0[31:16] == 'hd)||(data0[31:16] == 'he)||(data0[31:16] == 'hf)||(data0[31:16] == 'h10)||(data0[31:16] == 'h11)||(data0[31:16] == 'h12)||(data0[31:16] == 'h13)||(data0[31:16] == 'h16)||(data0[31:16] == 'h17)||(data0[31:16] == 'h18)||(data0[31:16] > 'h18)) begin 
                sa_env.chip_reg.DATA3.write(.status(status3), .value('h1), .path(UVM_BACKDOOR));//wri
                `uvm_info("RIGHT",$psprintf("CPU write value to %0s is succeed ! read %0s=%0x\n",register_name,register_name,read_value_IP),UVM_LOW)
              end else begin 
                `uvm_info("ERROR",$psprintf("CPU write value to %0s is failed ! %0s =%0x\n", register_name,register_name,read_value_IP),UVM_LOW)
                sa_env.chip_reg.DATA3.write(.status(status3), .value('h0), .path(UVM_BACKDOOR));//wri
              end 
                r = data1;
              sa_env.chip_reg.DATA2.write(.status(status2), .value(data0), .path(UVM_BACKDOOR));
          
                  s[15:0] = m[15:0] + 'h1; 
//                  while(data2 != m) #1us; 
//                  if(data2[31:16] == 'h19) begin repeat(10) @(posedge soc_tb.DUT.u_dig_top.u_aon_domain.u_scu.u_clk_gen.osc_32k); end else #1us;// BR005 'h19 it is failed after one cycle 

    endtask: writable_register  


    task read_only_register(int q, string ro_register_name);

      if (q == 'h6) begin
        sa_env.chip_reg.SCU_SYS_STATUS.write(.status(status_IP), .value(o), .path(UVM_BACKDOOR));s[31:16] = 'h6;
      end else if(q == 'h8) begin
        uvm_hdl_force("soc_tb.DUT.u_dig_top.u_aon_domain.u_scu.u_apb_eg_slave_reg.pwr_status[31:0]", o);s[31:16] = 'h8;
      end else if(q == 'ha) begin
        uvm_hdl_force("soc_tb.DUT.u_dig_top.u_aon_domain.u_scu.u_apb_eg_slave_reg.dev_status[31:0]", o);s[31:16] = 'ha;
      end else if(q == 'h14) begin
        uvm_hdl_force("soc_tb.DUT.u_dig_top.u_aon_domain.u_scu.u_apb_eg_slave_reg.ana_status0[31:0]", o);s[31:16] = 'h14;
      end else if(q == 'h15) begin
        uvm_hdl_force("soc_tb.DUT.u_dig_top.u_aon_domain.u_scu.u_apb_eg_slave_reg.ana_status1[31:0]", o);s[31:16] = 'h15;
    
     end
///        if ((s[31:16] == 'h2a)||(s[31:16] == 'h2b)||(s[31:16] == 'h60)||(s[31:16] == 'h61)||(s[31:16] == 'h62)) begin 
///        sa_env.chip_reg.DATA3.write(.status(status3), .value('h0), .path(UVM_BACKDOOR));end
///        else begin
        sa_env.chip_reg.DATA3.write(.status(status3), .value(o), .path(UVM_BACKDOOR)); 
//        end
        sa_env.chip_reg.DATA2.write(.status(status2), .value(s), .path(UVM_BACKDOOR));
        `uvm_info("IP REGISTER",$psprintf("TB write value to %0s=%0x\n",ro_register_name,o),UVM_LOW)

      while (data0 != s || data1 != 'h1) begin
        #1us;  
        end

           o = o*2;
           s = s + 'h1;
    endtask: read_only_register  
endclass: chip_scu

