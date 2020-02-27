`include "chip_defines.sv"

class chip_i2c extends chip_base_test;

	`uvm_component_utils(chip_i2c)

      int i=16'h0; // for print of data0;
      int j=16'h0; // for print of data1;    
      int k=16'h0; // for print of data2; 
      int l=16'h0; // for print of data3;
      int m=32'h0; // basic data0 with high_bit and low_bit;
      int n=32'd0; // cycle times
      int o=32'h1; // value of data3 and register for print    
      int p=32'd2; // cycle times                    
      int q=32'd2; // read_only register selected                    
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


//`           while (data0 != 'h4 || data1 != 'h1 ) begin    // read data0=4,data1=1                                                                           
//`             #1us;
//`           end
//`           sa_env.chip_reg.DATA3.write(.status(status3), .value('hd10), .path(UVM_BACKDOOR));//write 1,d10
//`           sa_env.chip_reg.DATA2.write(.status(status2), .value('h1), .path(UVM_BACKDOOR));
//`           while (data0 != 'h2 || data1 != 'hd10 ) begin
//`             #1us;
//`           end
//`             sa_env.chip_reg.DATA3.write(.status(status3), .value('h1), .path(UVM_BACKDOOR));//write 2,1
//`             sa_env.chip_reg.DATA2.write(.status(status2), .value('h2), .path(UVM_BACKDOOR));
//`             while (  data2 != 'h2  ||  data3 != 'h1) begin
//`               #1us;
//`               end
//`     
//`//-------------------------------------------- Traversal of writable registers----------------------------//

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

         o = 'h1; for (n = 0 ; n < 15; n++) begin read_only_register('hf, "IC_INTR_STAT"); end
         o = 'h1; for (n = 0 ; n < 15; n++) begin read_only_register('h11, "IC_RAW_INTR_STAT"); end
         o = 'h1; for (n = 0 ; n < 1; n++) begin read_only_register('h14, "IC_CLR_INTR"); end
         o = 'h1; for (n = 0 ; n < 1; n++) begin read_only_register('h15, "IC_RX_UNDER"); end
         o = 'h1; for (n = 0 ; n < 1; n++) begin read_only_register('h16, "IC_RX_OVER"); end
         o = 'h1; for (n = 0 ; n < 1; n++) begin read_only_register('h17, "IC_TX_OVER"); end
         o = 'h1; for (n = 0 ; n < 1; n++) begin read_only_register('h18, "IC_RD_REQ"); end
         o = 'h1; for (n = 0 ; n < 1; n++) begin read_only_register('h19, "IC_TX_ABRT"); end
         o = 'h1; for (n = 0 ; n < 1; n++) begin read_only_register('h1a, "IC_RX_DONE"); end
         o = 'h1; for (n = 0 ; n < 1; n++) begin read_only_register('h1b, "IC_ACTIVITY"); end
         o = 'h1; for (n = 0 ; n < 1; n++) begin read_only_register('h1c, "IC_STOP_DET"); end
         o = 'h1; for (n = 0 ; n < 1; n++) begin read_only_register('h1d, "IC_START_DET"); end
         o = 'h1; for (n = 0 ; n < 1; n++) begin read_only_register('h1e, "IC_GEN_CALL"); end
         o = 'h1; for (n = 0 ; n < 7; n++) begin read_only_register('h20, "IC_STATUS"); end
         //modified n < 7  on the basis of spec.
         o = 'h1; for (n = 0 ; n < 3; n++) begin read_only_register('h21, "IC_TXFLR"); end
         o = 'h1; for (n = 0 ; n < 3; n++) begin read_only_register('h22, "IC_RXFLR"); end

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
          if (data0[31:16] == 'h1) begin
                sa_env.chip_reg.IC_CON.read(.status(status_IP), .value(read_value_IP), .path(UVM_BACKDOOR));register_name = "IC_CON";
          end else if (data0[31:16] == 'h2) begin
                       sa_env.chip_reg.IC_TAR.read(.status(status_IP), .value(read_value_IP), .path(UVM_BACKDOOR));register_name = "IC_TAR";
          end else if (data0[31:16] == 'h3) begin
                       sa_env.chip_reg.IC_SAR.read(.status(status_IP), .value(read_value_IP), .path(UVM_BACKDOOR));register_name = "IC_SAR";
          end else if (data0[31:16] == 'h4) begin
                       sa_env.chip_reg.IC_HS_MADDR.read(.status(status_IP), .value(read_value_IP), .path(UVM_BACKDOOR));register_name = "IC_HS_MADDR";
          end else if (data0[31:16] == 'h5) begin
                                                                                                                register_name = "SPIS1_BAUDR";
          end else if (data0[31:16] == 'h6) begin
              sa_env.chip_reg.IC_SS_SCL_HCNT.read(.status(status_IP), .value(read_value_IP), .path(UVM_BACKDOOR)); register_name = "IC_SS_SCL_HCNT";
          end else if (data0[31:16] == 'h8) begin
              sa_env.chip_reg.IC_SS_SCL_LCNT.read(.status(status_IP), .value(read_value_IP), .path(UVM_BACKDOOR)); register_name = "IC_SS_SCL_LCNT";
          end else if (data0[31:16] == 'ha) begin
              sa_env.chip_reg.IC_FS_SCL_HCNT.read(.status(status_IP), .value(read_value_IP), .path(UVM_BACKDOOR)); register_name = "IC_FS_SCL_HCNT";
          end else if (data0[31:16] == 'hc) begin
              sa_env.chip_reg.IC_FS_SCL_LCNT.read(.status(status_IP), .value(read_value_IP), .path(UVM_BACKDOOR)); register_name = "IC_FS_SCL_LCNT";
          end else if (data0[31:16] == 'hd) begin
              sa_env.chip_reg.IC_HS_SCL_HCNT.read(.status(status_IP), .value(read_value_IP), .path(UVM_BACKDOOR)); register_name = "IC_HS_SCL_HCNT";
          end else if (data0[31:16] == 'he) begin
              sa_env.chip_reg.IC_HS_SCL_LCNT.read(.status(status_IP), .value(read_value_IP), .path(UVM_BACKDOOR)); register_name = "IC_HS_SCL_LCNT";
          end else if (data0[31:16] == 'h10) begin
              sa_env.chip_reg.IC_INTR_MASK.read(.status(status_IP), .value(read_value_IP), .path(UVM_BACKDOOR)); register_name = "IC_INTR_MASK";
          end else if (data0[31:16] == 'h12) begin
              sa_env.chip_reg.IC_RX_TL.read(.status(status_IP), .value(read_value_IP), .path(UVM_BACKDOOR)); register_name = "IC_RX_TL";
          end else if (data0[31:16] == 'h13) begin
              sa_env.chip_reg.IC_TX_TL.read(.status(status_IP), .value(read_value_IP), .path(UVM_BACKDOOR)); register_name = "IC_TX_TL";
//          end else if (data0[31:16] == 'h1f) begin
//              sa_env.chip_reg.IC_ENABLE_REG.read(.status(status_IP), .value(read_value_IP), .path(UVM_BACKDOOR)); register_name = "IC_ENABLE_REG";

             end

              if ((read_value_IP == data1)||((data0[31:16] == 'h1)&&((n == 1 && read_value_IP == 'h2)||(n == 2 && read_value_IP == 'h4)||(read_value_IP == data1+'h6)))||(data0[31:16] == 'h5)||((data0[31:16] == 'h6||'ha||'hd)&&(data1<'h7)&&(read_value_IP == 'h6))) begin 
                sa_env.chip_reg.DATA3.write(.status(status3), .value('h1), .path(UVM_BACKDOOR));//wri
                `uvm_info("RIGHT",$psprintf("CPU write value to %0s is succeed ! read %0s=%0x\n",register_name,register_name,read_value_IP),UVM_LOW)
              end else begin 
                `uvm_info("ERROR",$psprintf("CPU write value to %0s is failed ! %0s =%0x\n", register_name,register_name,read_value_IP),UVM_LOW)
                sa_env.chip_reg.DATA3.write(.status(status3), .value('h0), .path(UVM_BACKDOOR));//wri
              end 
              sa_env.chip_reg.DATA2.write(.status(status2), .value(data0), .path(UVM_BACKDOOR));
          
                  s[15:0] = m[15:0] + 'h1;
//                  while(data2 != m) #1us; 
//                  if(data2[31:16] == 'h13) #100ms; else #1us;
               //   if(data2[31:16] == 'h1f) begin
               //     
               //     end

    endtask: writable_register  


    task read_only_register(int q, string ro_register_name);

          if (q == 'hf) begin
            sa_env.chip_reg.IC_INTR_STAT.write(.status(status_IP), .value(o), .path(UVM_BACKDOOR));s[31:16] = 'hf;
          end else if(q == 'h11) begin  
            uvm_hdl_force("soc_tb.DUT.u_dig_top.u_sys_domain.u_sys_main.i_i2c.ic_raw_intr_stat[14:0]", o);s[31:16] = 'h11; 
          end else if(q == 'h14) begin  
            sa_env.chip_reg.IC_CLR_INTR.write(.status(status_IP), .value(o), .path(UVM_BACKDOOR));s[31:16] = 'h14;
          end else if(q == 'h15) begin  
            sa_env.chip_reg.IC_RX_UNDER.write(.status(status_IP), .value(o), .path(UVM_BACKDOOR));s[31:16] = 'h15;
          end else if(q == 'h16) begin  
            sa_env.chip_reg.IC_RX_OVER.write(.status(status_IP), .value(o), .path(UVM_BACKDOOR));s[31:16] = 'h16;
          end else if(q == 'h17) begin  
            sa_env.chip_reg.IC_TX_OVER.write(.status(status_IP), .value(o), .path(UVM_BACKDOOR));s[31:16] = 'h17;
          end else if(q == 'h18) begin  
            sa_env.chip_reg.IC_RD_REQ.write(.status(status_IP), .value(o), .path(UVM_BACKDOOR));s[31:16] = 'h18;
          end else if(q == 'h19) begin  
            sa_env.chip_reg.IC_TX_ABRT.write(.status(status_IP), .value(o), .path(UVM_BACKDOOR));s[31:16] = 'h19;
          end else if(q == 'h1a) begin  
            sa_env.chip_reg.IC_RX_DONE.write(.status(status_IP), .value(o), .path(UVM_BACKDOOR));s[31:16] = 'h1a;
          end else if(q == 'h1b) begin  
            sa_env.chip_reg.IC_ACTIVITY.write(.status(status_IP), .value(o), .path(UVM_BACKDOOR));s[31:16] = 'h1b;
          end else if(q == 'h1c) begin  
            sa_env.chip_reg.IC_STOP_DET.write(.status(status_IP), .value(o), .path(UVM_BACKDOOR));s[31:16] = 'h1c;
          end else if(q == 'h1d) begin  
            sa_env.chip_reg.IC_START_DET.write(.status(status_IP), .value(o), .path(UVM_BACKDOOR));s[31:16] = 'h1d;
          end else if(q == 'h1e) begin  
            sa_env.chip_reg.IC_GEN_CALL.write(.status(status_IP), .value(o), .path(UVM_BACKDOOR));s[31:16] = 'h1e;
          end else if(q == 'h20) begin  
            uvm_hdl_force("soc_tb.DUT.u_dig_top.u_sys_domain.u_sys_main.i_i2c.U_DW_apb_i2c_regfile.ic_status[6:0]", o);s[31:16] = 'h20; 
          end else if(q == 'h21) begin  
            sa_env.chip_reg.IC_TXFLR.write(.status(status_IP), .value(o), .path(UVM_BACKDOOR));s[31:16] = 'h21;
          end else if(q == 'h22) begin  
            sa_env.chip_reg.IC_RXFLR.write(.status(status_IP), .value(o), .path(UVM_BACKDOOR));s[31:16] = 'h22;
    
         end
            if ((s[31:16] == 'h15) || (s[31:16] == 'h16) || (s[31:16] == 'h17) || (s[31:16] == 'h18) || (s[31:16] == 'h19) || (s[31:16] == 'h1a) || (s[31:16] == 'h1b) || (s[31:16] == 'h1c) || (s[31:16] == 'h1d) || (s[31:16] == 'h1e) || (s[31:16] == 'h21) || (s[31:16] == 'h22)) begin 
            sa_env.chip_reg.DATA3.write(.status(status3), .value('h0), .path(UVM_BACKDOOR));end
            else begin
          sa_env.chip_reg.DATA3.write(.status(status3), .value(o), .path(UVM_BACKDOOR));
            end
            sa_env.chip_reg.DATA2.write(.status(status2), .value(s), .path(UVM_BACKDOOR));
            `uvm_info("IP REGISTER",$psprintf("TB write value to %0s=%0x\n",ro_register_name,o),UVM_LOW)

          while (data0 != s || data1 != 'h1) begin
            #1us;  
            end

               o = o*2;
               s = s + 'h1;
    endtask: read_only_register  
endclass: chip_i2c
