`include "chip_defines.sv"

class chip_uart0 extends chip_base_test;

		`uvm_component_utils(chip_uart0)

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
//           sa_env.chip_reg.DATA3.write(.status(status3), .value('h510), .path(UVM_BACKDOOR));//write 1,510
//           sa_env.chip_reg.DATA2.write(.status(status2), .value('h1), .path(UVM_BACKDOOR));
//           while (data0 != 'h2 || data1 != 'h510 ) begin
//             #1us;
//           end
//             sa_env.chip_reg.DATA3.write(.status(status3), .value('h1), .path(UVM_BACKDOOR));//write 2,1
//             sa_env.chip_reg.DATA2.write(.status(status2), .value('h2), .path(UVM_BACKDOOR));
//             while (  data2 != 'h2  ||  data3 != 'h1) begin
//               #1us;
//               end
//     
//-------------------------------------------- Traversal of writable registers----------------------------//
       for  (n = 0 ; n < 5500; n++) begin 
                  while (data0 == m) begin
                     #1us;
                                     end
                  if (data0 == 'h5) break;
      writable_register;
                  end 
                  
                     while (data0 != 'h5  ) begin
                       #1us;
                     end

           sa_env.chip_reg.DATA3.write(.status(status3), .value('h1), .path(UVM_BACKDOOR));//write 
           sa_env.chip_reg.DATA2.write(.status(status2), .value('h5), .path(UVM_BACKDOOR));
                     while (data2 != 'h5 || data3 != 'h1 ) begin
                       #1us;
                     end
                       #1us;

         o = 'h1;       for  (n = 0 ; n < 8; n++) begin      read_only_register('h1);                 end
         o = 'h1;       for  (n = 0 ; n < 8; n++) begin      read_only_register('h7);                 end
         o = 'h1;       for  (n = 0 ; n < 8; n++) begin      read_only_register('ha);                 end
         o = 'h1;       for  (n = 0 ; n < 5; n++) begin      read_only_register('hb);                 end
         o = 'h1;       for  (n = 0 ; n < 4; n++) begin      read_only_register('hc);                 end
         o = 'h1;       for  (n = 0 ; n < 4; n++) begin      read_only_register('hd);                 end

           sa_env.chip_reg.DATA3.write(.status(status3), .value('h1), .path(UVM_BACKDOOR));//write 
           sa_env.chip_reg.DATA2.write(.status(status2), .value('h6), .path(UVM_BACKDOOR));
                     while (data2 != 'h6 || data3 != 'h1 ) begin
                       #1us;
                     end
                       #1us;

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
                     if (data0[20:16] == 'h2) begin
                     sa_env.chip_reg.UART0_THR.read(.status(status_IP), .value(read_value_IP), .path(UVM_BACKDOOR));
                     if (read_value_IP != data1) begin 
                 `uvm_info("ERROR",$psprintf("CPU write value to UART0_THR is failed ! read UART0_THR=%0x\n",   read_value_IP),UVM_LOW)
                     sa_env.chip_reg.DATA3.write(.status(status3), .value('h0), .path(UVM_BACKDOOR));//wri
                       end else begin 
                     sa_env.chip_reg.DATA3.write(.status(status3), .value('h1), .path(UVM_BACKDOOR));//wri
                 `uvm_info("RIGHT",$psprintf("CPU write value to UART0_THR is succeed ! read UART0_THR=%0x\n",   read_value_IP),UVM_LOW)
                     end 
                     sa_env.chip_reg.DATA2.write(.status(status2), .value(data0), .path(UVM_BACKDOOR));
                     end else if (data0[20:16] == 'h3) begin
                     sa_env.chip_reg.UART0_IER.read(.status(status_IP), .value(read_value_IP), .path(UVM_BACKDOOR));
                     if (read_value_IP != data1) begin 
                 `uvm_info("ERROR",$psprintf("CPU write value to UART0_IER is failed ! read UART0_IER=%0x\n",   read_value_IP),UVM_LOW)
                     sa_env.chip_reg.DATA3.write(.status(status3), .value('h0), .path(UVM_BACKDOOR));//wri
                       end else begin 
                     sa_env.chip_reg.DATA3.write(.status(status3), .value('h1), .path(UVM_BACKDOOR));//wri
                 `uvm_info("RIGHT",$psprintf("CPU write value to UART0_IER is succeed ! read UART0_IER=%0x\n",   read_value_IP),UVM_LOW)
                     end                     
                     sa_env.chip_reg.DATA2.write(.status(status2), .value(data0), .path(UVM_BACKDOOR));
                     end else if (data0[20:16] == 'h4) begin
                     sa_env.chip_reg.UART0_DLL.read(.status(status_IP), .value(read_value_IP), .path(UVM_BACKDOOR));
                     if (read_value_IP != data1) begin 
                 `uvm_info("ERROR",$psprintf("CPU write value to UART0_DLL is failed ! read UART0_DLL=%0x\n",   read_value_IP),UVM_LOW)
                     sa_env.chip_reg.DATA3.write(.status(status3), .value('h0), .path(UVM_BACKDOOR));//wri
                       end else begin 
                     sa_env.chip_reg.DATA3.write(.status(status3), .value('h1), .path(UVM_BACKDOOR));//wri
                 `uvm_info("RIGHT",$psprintf("CPU write value to UART0_DLL is succeed ! read UART0_DLL=%0x\n",   read_value_IP),UVM_LOW)
                     end 
                     sa_env.chip_reg.DATA2.write(.status(status2), .value(data0), .path(UVM_BACKDOOR));
                     end else if (data0[20:16] == 'h5) begin
                     sa_env.chip_reg.UART0_DLH.read(.status(status_IP), .value(read_value_IP), .path(UVM_BACKDOOR));
                     if (read_value_IP != data1) begin 
                 `uvm_info("ERROR",$psprintf("CPU write value to UART0_DLH is failed ! read UART0_DLH=%0x\n",   read_value_IP),UVM_LOW)
                     sa_env.chip_reg.DATA3.write(.status(status3), .value('h0), .path(UVM_BACKDOOR));//wri
                       end else begin 
                     sa_env.chip_reg.DATA3.write(.status(status3), .value('h1), .path(UVM_BACKDOOR));//wri
                 `uvm_info("RIGHT",$psprintf("CPU write value to UART0_DLH is succeed ! read UART0_DLH=%0x\n",   read_value_IP),UVM_LOW)
                     end 
                     sa_env.chip_reg.DATA2.write(.status(status2), .value(data0), .path(UVM_BACKDOOR));

                     end else if (data0[20:16] == 'h6) begin
                     sa_env.chip_reg.UART0_FCR.read(.status(status_IP), .value(read_value_IP), .path(UVM_BACKDOOR));
                     if (read_value_IP != data1) begin 
                 `uvm_info("ERROR",$psprintf("CPU write value to UART0_FCR is failed ! read UART0_FCR=%0x\n",   read_value_IP),UVM_LOW)
                     sa_env.chip_reg.DATA3.write(.status(status3), .value('h1), .path(UVM_BACKDOOR));//wri
                       end else begin 
                     sa_env.chip_reg.DATA3.write(.status(status3), .value('h1), .path(UVM_BACKDOOR));//wri
                 `uvm_info("RIGHT",$psprintf("CPU write value to UART0_FCR is succeed ! read UART0_FCR=%0x\n",   read_value_IP),UVM_LOW)
                     end 
                     sa_env.chip_reg.DATA2.write(.status(status2), .value(data0), .path(UVM_BACKDOOR));
                     end else if (data0[20:16] == 'h8) begin
                     sa_env.chip_reg.UART0_LCR.read(.status(status_IP), .value(read_value_IP), .path(UVM_BACKDOOR));
                     if (read_value_IP != data1) begin 
                 `uvm_info("ERROR",$psprintf("CPU write value to UART0_LCR is failed ! read UART0_LCR=%0x\n",   read_value_IP),UVM_LOW)
                     sa_env.chip_reg.DATA3.write(.status(status3), .value('h0), .path(UVM_BACKDOOR));//wri
                       end else begin 
                     sa_env.chip_reg.DATA3.write(.status(status3), .value('h1), .path(UVM_BACKDOOR));//wri
                 `uvm_info("RIGHT",$psprintf("CPU write value to UART0_LCR is succeed ! read UART0_LCR=%0x\n",   read_value_IP),UVM_LOW)
                     end 
                     sa_env.chip_reg.DATA2.write(.status(status2), .value(data0), .path(UVM_BACKDOOR));
                     end else if (data0[20:16] == 'h9) begin
                     sa_env.chip_reg.UART0_MCR.read(.status(status_IP), .value(read_value_IP), .path(UVM_BACKDOOR));
                     if (read_value_IP != data1) begin 
                 `uvm_info("ERROR",$psprintf("CPU write value to UART0_MCR is failed ! read UART0_MCR=%0x\n",   read_value_IP),UVM_LOW)
                     sa_env.chip_reg.DATA3.write(.status(status3), .value('h0), .path(UVM_BACKDOOR));//wri
                       end else begin 
                     sa_env.chip_reg.DATA3.write(.status(status3), .value('h1), .path(UVM_BACKDOOR));//wri
                 `uvm_info("RIGHT",$psprintf("CPU write value to UART0_MCR is succeed ! read UART0_MCR=%0x\n",   read_value_IP),UVM_LOW)
                     end 
                     sa_env.chip_reg.DATA2.write(.status(status2), .value(data0), .path(UVM_BACKDOOR));
                     end else if (data0[20:16] == 'he) begin
                     sa_env.chip_reg.UART0_DLF.read(.status(status_IP), .value(read_value_IP), .path(UVM_BACKDOOR));
                     if (read_value_IP != data1) begin 
                 `uvm_info("ERROR",$psprintf("CPU write value to UART0_DLF is failed ! read UART0_DLF=%0x\n",   read_value_IP),UVM_LOW)
                     sa_env.chip_reg.DATA3.write(.status(status3), .value('h0), .path(UVM_BACKDOOR));//wri
                       end else begin 
                     sa_env.chip_reg.DATA3.write(.status(status3), .value('h1), .path(UVM_BACKDOOR));//wri
                 `uvm_info("RIGHT",$psprintf("CPU write value to UART0_DLF is succeed ! read UART0_DLF=%0x\n",   read_value_IP),UVM_LOW)
                     end 
                     sa_env.chip_reg.DATA2.write(.status(status2), .value(data0), .path(UVM_BACKDOOR));
                     end 
                     s[15:0] = m[15:0] + 'h1;
    endtask: writable_register  
    task read_only_register(int q);

                     if (q == 'h1) begin
                       sa_env.chip_reg.UART0_RBR.write(.status(status_IP), .value(o), .path(UVM_BACKDOOR));
                         s[31:16] = 'h1;
                       sa_env.chip_reg.DATA3.write(.status(status3), .value(o), .path(UVM_BACKDOOR));//wri
                       sa_env.chip_reg.DATA2.write(.status(status2), .value(s), .path(UVM_BACKDOOR));
                       `uvm_info("IP REGISTER",$psprintf("TB write value to UART0_RBR =%0x\n", o),UVM_LOW)
                     end else if(q == 'h7) begin  
                       sa_env.chip_reg.UART0_IIR.write(.status(status_IP), .value(o), .path(UVM_BACKDOOR));//
                         s[31:16] = 'h7;
                       sa_env.chip_reg.DATA3.write(.status(status3), .value(o), .path(UVM_BACKDOOR));//wri
                       sa_env.chip_reg.DATA2.write(.status(status2), .value(s), .path(UVM_BACKDOOR));
                       `uvm_info("IP REGISTER",$psprintf("TB write value to UART0_IIR=%0x\n",o),UVM_LOW)
                     end else if(q == 'ha) begin
                       uvm_hdl_force("soc_tb.DUT.u_dig_top.u_peri_domain.u_peri_main.i_uart0.U_DW_apb_uart_regfile.lsr", o);
                         s[31:16] = 'ha;
                       sa_env.chip_reg.DATA3.write(.status(status3), .value(o), .path(UVM_BACKDOOR));//wri
                       sa_env.chip_reg.DATA2.write(.status(status2), .value(s), .path(UVM_BACKDOOR));
                       `uvm_info("IP REGISTER",$psprintf("TB write value to UART0_LSR=%0x\n",o),UVM_LOW)
                     end else if(q == 'hb) begin
                       uvm_hdl_force("soc_tb.DUT.u_dig_top.u_peri_domain.u_peri_main.i_uart0.U_DW_apb_uart_regfile.usr", o);
                         s[31:16] = 'hb;
                       sa_env.chip_reg.DATA3.write(.status(status3), .value(o), .path(UVM_BACKDOOR));//wri
                       sa_env.chip_reg.DATA2.write(.status(status2), .value(s), .path(UVM_BACKDOOR));
                       `uvm_info("IP REGISTER",$psprintf("TB write value to UART0_USR=%0x\n",o),UVM_LOW)
                     end else if(q == 'hc) begin
                       sa_env.chip_reg.UART0_TFL.write(.status(status_IP), .value(o), .path(UVM_BACKDOOR));
                         s[31:16] = 'hc;
                       sa_env.chip_reg.DATA3.write(.status(status3), .value(o), .path(UVM_BACKDOOR));//wri
                       sa_env.chip_reg.DATA2.write(.status(status2), .value(s), .path(UVM_BACKDOOR));
                       `uvm_info("IP REGISTER",$psprintf("TB write value to UART0_TFL=%0x\n",o),UVM_LOW)
                     end else if(q == 'hd) begin
                       sa_env.chip_reg.UART0_RFL.write(.status(status_IP), .value(o), .path(UVM_BACKDOOR));
                         s[31:16] = 'hd;
                       sa_env.chip_reg.DATA3.write(.status(status3), .value(o), .path(UVM_BACKDOOR));//wri
                       sa_env.chip_reg.DATA2.write(.status(status2), .value(s), .path(UVM_BACKDOOR));
                       `uvm_info("IP REGISTER",$psprintf("TB write value to UART0_RFL=%0x\n",o),UVM_LOW)
                     end

                     #1us;
                     while (data0 != s || data1 != 'h1) begin
                     #1us;  
                       end

                          o = o*2;
                          s = s + 'h1;
    endtask: read_only_register  
endclass: chip_uart0

