`include "chip_defines.sv"

class chip_spim0 extends chip_base_test;

		`uvm_component_utils(chip_spim0)

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


//           while (data0 != 'h4 || data1 != 'h1 ) begin    // read data0=4,data1=1                                                                           
//             #1us;
//           end
//           sa_env.chip_reg.DATA3.write(.status(status3), .value('hf10), .path(UVM_BACKDOOR));//write 1,f10
//           sa_env.chip_reg.DATA2.write(.status(status2), .value('h1), .path(UVM_BACKDOOR));
//           while (data0 != 'h2 || data1 != 'hf10 ) begin
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

         o = 'h1; for (n = 0 ; n < 5; n++) begin read_only_register('h9, "SPIM0_TXFLR"); end
         o = 'h1; for (n = 0 ; n < 5; n++) begin read_only_register('ha, "SPIM0_RXFLR"); end
       //  o = 'h15; for (n = 0 ; n < 1; n++) begin read_only_register('ha, "SPIM0_RXFLR"); end
         o = 'h1; for (n = 0 ; n < 7; n++) begin read_only_register('hb, "SPIM0_SR"); end
         o = 'h1; for (n = 0 ; n < 7; n++) begin read_only_register('hd, "SPIM0_ISR"); end
         o = 'h1; for (n = 0 ; n < 7; n++) begin read_only_register('he, "SPIM0_RISR"); end
         o = 'h1; for (n = 0 ; n < 1; n++) begin read_only_register('hf, "SPIM0_TXOICR"); end
         o = 'h1; for (n = 0 ; n < 1; n++) begin read_only_register('h10, "SPIM0_RXOICR"); end
         o = 'h1; for (n = 0 ; n < 1; n++) begin read_only_register('h11, "SPIM0_RXUICR"); end
         o = 'h1; for (n = 0 ; n < 1; n++) begin read_only_register('h12, "SPIM0_MSTICR"); end
         o = 'h1; for (n = 0 ; n < 1; n++) begin read_only_register('h1e, "SPIM0_XRXOICR"); end

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
              sa_env.chip_reg.SPIM0_CTRLR0.read(.status(status_IP), .value(read_value_IP), .path(UVM_BACKDOOR)); register_name = "SPIM0_CTRLR0";
          end else if (data0[31:16] == 'h2) begin
              sa_env.chip_reg.SPIM0_CTRLR1.read(.status(status_IP), .value(read_value_IP), .path(UVM_BACKDOOR)); register_name = "SPIM0_CTRLR1";
          end else if (data0[31:16] == 'h4) begin
              sa_env.chip_reg.SPIM0_MWCR.read(.status(status_IP), .value(read_value_IP), .path(UVM_BACKDOOR)); register_name = "SPIM0_MWCR";
          end else if (data0[31:16] == 'h5) begin
              sa_env.chip_reg.SPIM0_SER.read(.status(status_IP), .value(read_value_IP), .path(UVM_BACKDOOR)); register_name = "SPIM0_SER";
          end else if (data0[31:16] == 'h6) begin
              sa_env.chip_reg.SPIM0_BAUDR.read(.status(status_IP), .value(read_value_IP), .path(UVM_BACKDOOR)); register_name = "SPIM0_BAUDR";
          end else if (data0[31:16] == 'h7) begin
              sa_env.chip_reg.SPIM0_TXFTLR.read(.status(status_IP), .value(read_value_IP), .path(UVM_BACKDOOR)); register_name = "SPIM0_TXFTLR";
          end else if (data0[31:16] == 'h8) begin
              sa_env.chip_reg.SPIM0_RXFTLR.read(.status(status_IP), .value(read_value_IP), .path(UVM_BACKDOOR)); register_name = "SPIM0_RXFTLR";
          end else if (data0[31:16] == 'hc) begin
              sa_env.chip_reg.SPIM0_IMR.read(.status(status_IP), .value(read_value_IP), .path(UVM_BACKDOOR)); register_name = "SPIM0_IMR";
          end else if (data0[31:16] == 'h14) begin
              sa_env.chip_reg.SPIM0_DMACR.read(.status(status_IP), .value(read_value_IP), .path(UVM_BACKDOOR));register_name = "SPIM0_DMACR";
          end else if (data0[31:16] == 'h15) begin
              sa_env.chip_reg.SPIM0_DMATDLR.read(.status(status_IP), .value(read_value_IP), .path(UVM_BACKDOOR)); register_name = "SPIM0_DMATDLR";
          end else if (data0[31:16] == 'h16) begin
              sa_env.chip_reg.SPIM0_DMARDLR.read(.status(status_IP), .value(read_value_IP), .path(UVM_BACKDOOR)); register_name = "SPIM0_DMARDLR";
          end else if (data0[31:16] == 'h17) begin
              uvm_hdl_read("soc_tb.DUT.u_dig_top.u_sys_domain.u_sys_main.i_spim0.dmardlr", read_value_IP); register_name = "**17**";
          end else if (data0[31:16] == 'h18) begin
              sa_env.chip_reg.SPIM0_RX_SAMPLE_DLY.read(.status(status_IP), .value(read_value_IP), .path(UVM_BACKDOOR)); register_name = "SPIM0_RX_SAMPLE_DLY";
          end else if (data0[31:16] == 'h19) begin
              sa_env.chip_reg.SPIM0_SPI_CTRLR0.read(.status(status_IP), .value(read_value_IP), .path(UVM_BACKDOOR)); register_name = "SPIM0_SPI_CTRLR0";
          end else if (data0[31:16] == 'h1a) begin
              sa_env.chip_reg.SPIM0_XIP_INCR_INST.read(.status(status_IP), .value(read_value_IP), .path(UVM_BACKDOOR)); register_name = "SPIM0_XIP_INCR_INST";
          end else if (data0[31:16] == 'h1b) begin
              sa_env.chip_reg.SPIM0_XIP_WRAP_INST.read(.status(status_IP), .value(read_value_IP), .path(UVM_BACKDOOR)); register_name = "SPIM0_XIP_WRAP_INST";
          end else if (data0[31:16] == 'h1c) begin
              sa_env.chip_reg.SPIM0_XIP_CTRL.read(.status(status_IP), .value(read_value_IP), .path(UVM_BACKDOOR)); register_name = "SPIM0_XIP_CTRL";
          end else if (data0[31:16] == 'h1d) begin
              sa_env.chip_reg.SPIM0_XIP_SER.read(.status(status_IP), .value(read_value_IP), .path(UVM_BACKDOOR)); register_name = "SPIM0_XIP_SER";
          end else if (data0[31:16] == 'h1f) begin
              sa_env.chip_reg.SPIM0_XIP_CNT_TIME_OUT.read(.status(status_IP), .value(read_value_IP), .path(UVM_BACKDOOR)); register_name = "SPIM0_XIP_CNT_TIME_OUT";

             end

              if ((read_value_IP == data1) || ((data0[31:16] == 'h1) && (((n>1)&&(read_value_IP == data1/2+'h10)) || ((n>9)&&(read_value_IP == data1/4+'h10)) || ((n>13)&&(read_value_IP == data1/16+'h10)))) || ((data0[31:16] == 'h19)&&(((n>5)&&(read_value_IP*2 == data1))|| ((n>8)&&(read_value_IP*4 == data1)))) || (data0[31:16] == 'h17) || ((data0[31:16] == 'h1c) && (((n>1)&&(read_value_IP == data1+'h2)) || ((n>7)&&(read_value_IP == data1/2+'h2)) || ((n>9)&&(read_value_IP == data1/4+'h2)) || ((n>16)&&(read_value_IP == data1/32+'h2))))) begin 
                sa_env.chip_reg.DATA3.write(.status(status3), .value('h1), .path(UVM_BACKDOOR));//wri
                `uvm_info("RIGHT",$psprintf("CPU write value to %0s is succeed ! read %0s=%0x\n",register_name,register_name,read_value_IP),UVM_LOW)
              end else begin 
                `uvm_info("ERROR",$psprintf("CPU write value to %0s is failed ! %0s =%0x\n", register_name,register_name,read_value_IP),UVM_LOW)
                sa_env.chip_reg.DATA3.write(.status(status3), .value('h0), .path(UVM_BACKDOOR));//wri
              end 
              sa_env.chip_reg.DATA2.write(.status(status2), .value(data0), .path(UVM_BACKDOOR));
          
                  s[15:0] = m[15:0] + 'h1; 
//                  while(data2 != m) #1us; 
//                  if(data2[31:16] == 'h1f) #100ms; else #1us;

    endtask: writable_register  


    task read_only_register(int q, string ro_register_name);

          if (q == 'h9) begin
            sa_env.chip_reg.SPIM0_TXFLR.write(.status(status_IP), .value(o), .path(UVM_BACKDOOR));s[31:16] = 'h9;
          end else if(q == 'ha) begin  
            sa_env.chip_reg.SPIM0_RXFLR.write(.status(status_IP), .value(o), .path(UVM_BACKDOOR));s[31:16] = 'ha;
          end else if(q == 'hb) begin
            uvm_hdl_force("soc_tb.DUT.u_dig_top.u_sys_domain.u_sys_main.i_spim0.U_regfile.sr[6:0]", o);s[31:16] = 'hb;
          end else if(q == 'hd) begin
            sa_env.chip_reg.SPIM0_ISR.write(.status(status_IP), .value(o), .path(UVM_BACKDOOR));s[31:16] = 'hd;
          end else if(q == 'he) begin
            uvm_hdl_force("soc_tb.DUT.u_dig_top.u_sys_domain.u_sys_main.i_spim0.U_intctl.irisr[6:0]", o);s[31:16] = 'he;
          end else if(q == 'hf) begin
            sa_env.chip_reg.SPIM0_TXOICR.write(.status(status_IP), .value(o), .path(UVM_BACKDOOR));s[31:16] = 'hf;
          end else if(q == 'h10) begin
            sa_env.chip_reg.SPIM0_RXOICR.write(.status(status_IP), .value(o), .path(UVM_BACKDOOR));s[31:16] = 'h10;
          end else if(q == 'h11) begin
            sa_env.chip_reg.SPIM0_RXUICR.write(.status(status_IP), .value(o), .path(UVM_BACKDOOR));s[31:16] = 'h11;
          end else if(q == 'h12) begin
            sa_env.chip_reg.SPIM0_MSTICR.write(.status(status_IP), .value(o), .path(UVM_BACKDOOR));s[31:16] = 'h12;
          end else if(q == 'h1e) begin
            sa_env.chip_reg.SPIM0_XRXOICR.write(.status(status_IP), .value(o), .path(UVM_BACKDOOR));s[31:16] = 'h1e;


      //    end else if(q == 'h5f) begin
      //      sa_env.chip_reg..write(.status(status_IP), .value(o), .path(UVM_BACKDOOR));s[31:16] = 'h5f;
      //    end else if(q == 'h60) begin
      //      sa_env.chip_reg..write(.status(status_IP), .value(o), .path(UVM_BACKDOOR));s[31:16] = 'h60;
      //    end else if(q == 'h61) begin
      //      sa_env.chip_reg..write(.status(status_IP), .value(o), .path(UVM_BACKDOOR));s[31:16] = 'h61;
      //    end else if(q == 'h62) begin
      //      sa_env.chip_reg..write(.status(status_IP), .value(o), .path(UVM_BACKDOOR));s[31:16] = 'h62;
      //    end else if(q == 'h6d) begin
      //      uvm_hdl_force("soc_tb.DUT.u_dig_top.u_sys_domain.u_sys_main.i_dmac.U_intrif.istatusint", o);s[31:16] = 'h6d;
    
         end
           if ((s[31:16] == 'h9) || (s[31:16] == 'ha) || (s[31:16] == 'hf) || (s[31:16] == 'h10) || (s[31:16] == 'h11) || (s[31:16] == 'h12) || (s[31:16] == 'h1e)) begin 
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
endclass: chip_spim0

