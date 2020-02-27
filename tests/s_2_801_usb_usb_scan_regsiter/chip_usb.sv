`include "chip_defines.sv"

class chip_usb extends chip_base_test;

		`uvm_component_utils(chip_usb)

      int i=16'h0; // for print of data0;
      int j=16'h0; // for print of data1;    
      int k=16'h0; // for print of data2; 
      int l=16'h0; // for print of data3;
      int m=32'h0; // basic data0 with high_bit and low_bit;
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
//           sa_env.chip_reg.DATA3.write(.status(status3), .value('h1d10), .path(UVM_BACKDOOR));//write 1,1d10
//           sa_env.chip_reg.DATA2.write(.status(status2), .value('h1), .path(UVM_BACKDOOR));
//           while (data0 != 'h2 || data1 != 'h1d10 ) begin
//             #1us;
//           end
//             sa_env.chip_reg.DATA3.write(.status(status3), .value('h1), .path(UVM_BACKDOOR));//write 2,1
//             sa_env.chip_reg.DATA2.write(.status(status2), .value('h2), .path(UVM_BACKDOOR));
//             while (  data2 != 'h2  ||  data3 != 'h1) begin
//               #1us;
//               end
//     
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

 //        o = 'h1; for (n = 0 ; n < 32; n++) begin read_only_register('h2, "TIMER1CURRENT_COUNT"); end
 //        o = 'h1; for (n = 0 ; n < 32; n++) begin read_only_register('h7, "TIMER2CURRENT_COUNT"); end
 //        o = 'h1; for (n = 0 ; n < 32; n++) begin read_only_register('hc, "TIMER3CURRENT_COUNT"); end
 //        o = 'h1; for (n = 0 ; n < 32; n++) begin read_only_register('h11, "TIMER4CURRENT_COUNT"); end
 //        o = 'h1; for (n = 0 ; n < 32; n++) begin read_only_register('h16, "TIMER5CURRENT_COUNT"); end
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
          if (data0[31:16] == 'h1) begin
              sa_env.chip_reg.TIMER1LOAD_COUNT.read(.status(status_IP), .value(read_value_IP), .path(UVM_BACKDOOR)); register_name = "USB_GOTGCTL";
          end else if (data0[31:16] == 'h2) begin
              sa_env.chip_reg.TIMER1CONTROL_REG.read(.status(status_IP), .value(read_value_IP), .path(UVM_BACKDOOR)); register_name = "USB_GAHBCFG";
          end else if (data0[31:16] == 'h3) begin
              sa_env.chip_reg.TIMER2LOAD_COUNT.read(.status(status_IP), .value(read_value_IP), .path(UVM_BACKDOOR)); register_name = "USB->GUSBCFG";
          end else if (data0[31:16] == 'h4) begin
              sa_env.chip_reg.TIMER2CONTROL_REG.read(.status(status_IP), .value(read_value_IP), .path(UVM_BACKDOOR)); register_name = "USB->GRSTCTL";
          end else if (data0[31:16] == 'h5) begin
              sa_env.chip_reg.TIMER3LOAD_COUNT.read(.status(status_IP), .value(read_value_IP), .path(UVM_BACKDOOR)); register_name = "USB->GINTMSK";
          end else if (data0[31:16] == 'h6) begin
              sa_env.chip_reg.TIMER3CONTROL_REG.read(.status(status_IP), .value(read_value_IP), .path(UVM_BACKDOOR)); register_name = "USB->GPVNDCTL";

          end
              if (data1=='h1) r=0;
              if ((read_value_IP == data1)||(data0[31:16] == 'h1||'h2||'h3||'h4||'h5||'h6)) begin 
                sa_env.chip_reg.DATA3.write(.status(status3), .value('h1), .path(UVM_BACKDOOR));//wri
                `uvm_info("RIGHT",$psprintf("CPU write value to %0s is succeed ! read %0s=%0x\n",register_name,register_name,read_value_IP),UVM_LOW)
              end else begin 
                `uvm_info("ERROR",$psprintf("CPU write value to %0s is failed ! %0s =%0x\n", register_name,register_name,read_value_IP),UVM_LOW)
                sa_env.chip_reg.DATA3.write(.status(status3), .value('h0), .path(UVM_BACKDOOR));//wri
              end 
                r = data1;
              sa_env.chip_reg.DATA2.write(.status(status2), .value(data0), .path(UVM_BACKDOOR));
          
                  s[15:0] = m[15:0] + 'h1; 
              //    while(data2 != m) #1us; 
              //    if(data2[31:16] == 'h6) #100ms; else #1us;

    endtask: writable_register  


    task read_only_register(int q, string ro_register_name);

      if (q == 'h2) begin
        uvm_hdl_force("soc_tb.DUT.u_dig_top.u_sys_domain.u_sys_main.i_usb.U_apbif.int_timer1currentvalue[31:0]", o);s[31:16] = 'h2;
      end else if(q == 'h7) begin
        uvm_hdl_force("soc_tb.DUT.u_dig_top.u_sys_domain.u_sys_main.i_usb.U_apbif.int_timer2currentvalue[31:0]", o);s[31:16] = 'h7;
      end else if(q == 'hc) begin
        uvm_hdl_force("soc_tb.DUT.u_dig_top.u_sys_domain.u_sys_main.i_usb.U_apbif.int_timer3currentvalue[31:0]", o);s[31:16] = 'hc;
      end else if(q == 'h11) begin
        uvm_hdl_force("soc_tb.DUT.u_dig_top.u_sys_domain.u_sys_main.i_usb.U_apbif.int_timer4currentvalue[31:0]", o);s[31:16] = 'h11;
      end else if(q == 'h16) begin
        uvm_hdl_force("soc_tb.DUT.u_dig_top.u_sys_domain.u_sys_main.i_usb.U_apbif.int_timer5currentvalue[31:0]", o);s[31:16] = 'h16;
      end else if(q == 'h1b) begin
        uvm_hdl_force("soc_tb.DUT.u_dig_top.u_sys_domain.u_sys_main.i_usb.U_apbif.int_timer6currentvalue[31:0]", o);s[31:16] = 'h1b;
      end else if(q == 'h20) begin
        uvm_hdl_force("soc_tb.DUT.u_dig_top.u_sys_domain.u_sys_main.i_usb.U_apbif.int_timer7currentvalue[31:0]", o);s[31:16] = 'h20;
      end else if(q == 'h25) begin
        uvm_hdl_force("soc_tb.DUT.u_dig_top.u_sys_domain.u_sys_main.i_usb.U_apbif.int_timer8currentvalue[31:0]", o);s[31:16] = 'h25;
      end else if(q == 'h5) begin
        sa_env.chip_reg.TIMER1INTSTATUS.write(.status(status_IP), .value(o), .path(UVM_BACKDOOR));s[31:16] = 'h5;
      end else if(q == 'ha) begin
        sa_env.chip_reg.TIMER2INTSTATUS.write(.status(status_IP), .value(o), .path(UVM_BACKDOOR));s[31:16] = 'ha;
      end else if(q == 'hf) begin
        sa_env.chip_reg.TIMER3INTSTATUS.write(.status(status_IP), .value(o), .path(UVM_BACKDOOR));s[31:16] = 'hf;
      end else if(q == 'h14) begin
        sa_env.chip_reg.TIMER4INTSTATUS.write(.status(status_IP), .value(o), .path(UVM_BACKDOOR));s[31:16] = 'h14;
      end else if(q == 'h19) begin
        sa_env.chip_reg.TIMER5INTSTATUS.write(.status(status_IP), .value(o), .path(UVM_BACKDOOR));s[31:16] = 'h19;
      end else if(q == 'h1e) begin
        sa_env.chip_reg.TIMER6INTSTATUS.write(.status(status_IP), .value(o), .path(UVM_BACKDOOR));s[31:16] = 'h1e;
      end else if(q == 'h23) begin
        sa_env.chip_reg.TIMER7INTSTATUS.write(.status(status_IP), .value(o), .path(UVM_BACKDOOR));s[31:16] = 'h23;
      end else if(q == 'h28) begin
        sa_env.chip_reg.TIMER8INTSTATUS.write(.status(status_IP), .value(o), .path(UVM_BACKDOOR));s[31:16] = 'h28;
      end else if(q == 'h29) begin
        sa_env.chip_reg.INT_STATUS.write(.status(status_IP), .value(o), .path(UVM_BACKDOOR));s[31:16] = 'h29;
      //end else if(q == 'h2a) begin
      //  uvm_hdl_force("soc_tb.DUT.u_dig_top.u_sys_domain.u_sys_main.i_usb.U_apbif.usbeoi", o);s[31:16] = 'h2a;
      //  sa_env.chip_reg.TIMEREOI.write(.status(status_IP), .value(o), .path(UVM_BACKDOOR));s[31:16] = 'h2a;
      end else if(q == 'h2b) begin
        sa_env.chip_reg.RAW_INT_STATUS.write(.status(status_IP), .value(o), .path(UVM_BACKDOOR));s[31:16] = 'h2b;
    
     end
        if ((s[31:16] == 'h2a)||(s[31:16] == 'h2b)||(s[31:16] == 'h60)||(s[31:16] == 'h61)||(s[31:16] == 'h62)) begin 
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
endclass: chip_usb

