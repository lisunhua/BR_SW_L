`include "chip_defines.sv"
`include "chip_def.inc"
/*
class chip_gpio_701 extends chip_base_test;
		`uvm_component_utils(chip_gpio_701)
                 

		function new(string name, uvm_component parent);
			super.new(name, parent);
		endfunction: new

		task main_phase(uvm_phase phase);

                     
      uvm_status_e status0;         // status of data0 register
      uvm_status_e status1;         // status of data1 register
      uvm_status_e status2;         // status of data2 register
      uvm_status_e status3;         // status of data3 register
      uvm_status_e status_gpio_dra; // status of gpio_dra register
      uvm_status_e status_gpio_ddr0;// status of gpio_ddr0 register
      uvm_reg_data_t data0;         // value of data0 register
      uvm_reg_data_t data1;         // value of data1 register
      uvm_reg_data_t data2;         // value of data2 register
      uvm_reg_data_t data3;         // value of data3 register
      uvm_reg_data_t gpio_dra;      // value of gpio_dra register
      uvm_reg_data_t gpio_ddr0;     // value of gpio_ddr0 register

	          phase.raise_objection(phase);
//--------------------------CPU write, TB read----------------------------------//										 
            sa_env.chip_reg.MESSAGE_TB.read(.status(status0), .value(data0), .path(UVM_BACKDOOR));
            sa_env.chip_reg.MESSAGE_CPU.read(.status(status1), .value(data1), .path(UVM_BACKDOOR));
            while ( data0 != 'h4 || data1 != 'h1 ) begin
               sa_env.chip_reg.MESSAGE_TB.read(.status(status0), .value(data0), .path(UVM_BACKDOOR));
               sa_env.chip_reg.MESSAGE_CPU.read(.status(status1), .value(data1), .path(UVM_BACKDOOR));
            #1us;
            end
        `uvm_info("READ",$psprintf("data0=%0x,data1=%0x\n", data0, data1),UVM_LOW)
          
            sa_env.chip_reg.DATA3.write(.status(status3), .value('h701), .path(UVM_BACKDOOR));
            sa_env.chip_reg.DATA2.write(.status(status2), .value('h1), .path(UVM_BACKDOOR));


               sa_env.chip_reg.MESSAGE_TB.read(.status(status0), .value(data0), .path(UVM_BACKDOOR));
               sa_env.chip_reg.MESSAGE_CPU.read(.status(status1), .value(data1), .path(UVM_BACKDOOR));
            while (data0!= 'h2 || data1 != 'h701 ) begin
               sa_env.chip_reg.MESSAGE_TB.read(.status(status0), .value(data0), .path(UVM_BACKDOOR));
               sa_env.chip_reg.MESSAGE_CPU.read(.status(status1), .value(data1), .path(UVM_BACKDOOR));
            #1us;
            end
        `uvm_info("SUCCEED!",$psprintf("data0=%0x,data1=%0x\n", data0, data1),UVM_LOW)
            sa_env.chip_reg.DATA3.write(.status(status3), .value('h1), .path(UVM_BACKDOOR));
            sa_env.chip_reg.DATA2.write(.status(status2), .value('h2), .path(UVM_BACKDOOR));
   
               sa_env.chip_reg.GPIO_DRA.read(.status(status_gpio_dra), .value(gpio_dra), .path(UVM_BACKDOOR));
            while (gpio_dra!= 'h55 ) begin
               sa_env.chip_reg.GPIO_DRA.read(.status(status_gpio_dra), .value(gpio_dra), .path(UVM_BACKDOOR));
            #1us;
            end
        `uvm_info("SUCCEED!",$psprintf("DR0=%0x\n", gpio_dra),UVM_LOW)

            sa_env.chip_reg.DATA3.write(.status(status3), .value('h1), .path(UVM_BACKDOOR));
            sa_env.chip_reg.DATA2.write(.status(status2), .value('h20), .path(UVM_BACKDOOR));


//-----------------------------------------TB write, CPU read------------------//
             #1ms;
               sa_env.chip_reg.GPIO_DRA.write(.status(status_gpio_dra), .value('h456), .path(UVM_BACKDOOR));
            sa_env.chip_reg.DATA3.write(.status(status3), .value('h456), .path(UVM_BACKDOOR));
            sa_env.chip_reg.DATA2.write(.status(status2), .value('h21), .path(UVM_BACKDOOR));

               sa_env.chip_reg.MESSAGE_TB.read(.status(status0), .value(data0), .path(UVM_BACKDOOR));
               sa_env.chip_reg.MESSAGE_CPU.read(.status(status1), .value(data1), .path(UVM_BACKDOOR));
            while (data0!= 'h3 || data1 != 'h1 ) begin
               sa_env.chip_reg.MESSAGE_TB.read(.status(status0), .value(data0), .path(UVM_BACKDOOR));
               sa_env.chip_reg.MESSAGE_CPU.read(.status(status1), .value(data1), .path(UVM_BACKDOOR));
            #1us;
            end
            sa_env.chip_reg.DATA3.write(.status(status3), .value('h1), .path(UVM_BACKDOOR));
            sa_env.chip_reg.DATA2.write(.status(status2), .value('h3), .path(UVM_BACKDOOR));
        `uvm_info("---SUCCEED---",$psprintf("Simulation completed succeessfully !"),UVM_LOW)
$finish;

								                    #800_000us;
		     phase.drop_objection(phase);
		endtask: main_phase
endclass: chip_gpio_701


class chip_gpio_702 extends chip_base_test;

		`uvm_component_utils(chip_gpio_702)

      int i=16'h0;
      int j=16'h0;
      int k=16'h0;
      int l=16'h0;
      int m=16'h29; //basic data
      uvm_status_e status; 
      uvm_status_e status1;
      uvm_status_e status2;
      uvm_status_e status3;
      uvm_status_e status4;
      uvm_status_e status5;
      uvm_status_e status6;
      uvm_status_e status7;
      uvm_status_e status8;
      uvm_status_e status9;
      uvm_status_e status10;
      uvm_status_e status11;
      uvm_status_e status12;
      uvm_status_e status13;
      uvm_status_e status14;
      uvm_status_e status15;
      uvm_status_e status16;
      uvm_status_e status17;
      uvm_status_e status18;
      uvm_status_e status19;
      uvm_status_e status20;
      uvm_status_e status21;
      uvm_status_e status22;
      uvm_status_e status23;
      uvm_status_e status24;
      uvm_status_e status25;
      uvm_status_e status26;
      uvm_status_e status27;
      uvm_status_e status28;
      uvm_status_e status29;
      uvm_status_e status30;
      uvm_status_e status31;
      uvm_status_e status32;
      uvm_status_e status33;
      uvm_status_e status34;
      uvm_status_e status35;
      uvm_status_e status36;
      uvm_status_e status37;
      uvm_status_e status38;
      uvm_status_e status39;
      uvm_status_e status40;
      uvm_status_e status41;
      uvm_status_e status42;
      uvm_status_e status43;
      uvm_status_e status44;
      uvm_status_e status45;
      uvm_status_e status46;
      uvm_status_e status47;
      uvm_status_e status48;
      uvm_status_e status49;
      uvm_status_e status50;
      uvm_status_e status51;
      uvm_status_e status52;
      uvm_status_e status53;
      uvm_status_e status54;
      uvm_status_e status55;
      uvm_status_e status56;
      uvm_status_e status57;
      uvm_status_e status58;
      uvm_status_e status59;
      uvm_status_e status60;
      uvm_status_e status61;
      uvm_status_e status62;
      uvm_status_e status63;
      uvm_status_e status64;
      uvm_status_e status65;
      uvm_status_e status66;
      uvm_status_e status67;
      uvm_status_e status68;
      uvm_status_e status69;
      uvm_status_e status70;
      uvm_status_e status71;
      uvm_status_e status72;
      uvm_status_e status73;
      uvm_status_e status74;
      uvm_status_e status75;
      uvm_status_e status76;
      uvm_status_e status77;
      uvm_status_e status78;
      uvm_status_e status79;
      uvm_status_e status80;
      uvm_status_e status81;
      uvm_status_e status82;
      uvm_status_e status83;
      uvm_status_e status84;
      uvm_status_e status85;
      uvm_status_e status86;
      uvm_status_e status87;
      uvm_status_e status88;
      uvm_status_e status89;
      uvm_status_e status90;
      uvm_status_e status91;
      uvm_status_e status92;
      uvm_status_e status93;
      uvm_status_e status94;
      uvm_status_e status95;
      uvm_status_e status96;
      uvm_status_e status97;
      uvm_status_e status98;
      uvm_status_e status99;
      uvm_status_e status100;
      uvm_status_e status101;
      uvm_reg_data_t read_value;
      uvm_reg_data_t read_value1;
      uvm_reg_data_t read_value2;
      uvm_reg_data_t read_value3;
      uvm_reg_data_t read_value4;
      uvm_reg_data_t read_value5;
      uvm_reg_data_t read_value6;
      uvm_reg_data_t read_value7;
      uvm_reg_data_t read_value8;
      uvm_reg_data_t read_value9;
      uvm_reg_data_t read_value10;
      uvm_reg_data_t read_value11;
      uvm_reg_data_t read_value12;
      uvm_reg_data_t read_value13;
      uvm_reg_data_t read_value14;
      uvm_reg_data_t read_value15;
      uvm_reg_data_t read_value16;
      uvm_reg_data_t read_value17;
      uvm_reg_data_t read_value18;
      uvm_reg_data_t read_value19;
      uvm_reg_data_t read_value20;
      uvm_reg_data_t read_value21;
      uvm_reg_data_t read_value22;
      uvm_reg_data_t read_value23;
      uvm_reg_data_t read_value24;
      uvm_reg_data_t read_value25;
      uvm_reg_data_t read_value26;
      uvm_reg_data_t read_value27;
      uvm_reg_data_t read_value28;
      uvm_reg_data_t read_value29;
      uvm_reg_data_t read_value30;
      uvm_reg_data_t read_value31;
      uvm_reg_data_t read_value32;
      uvm_reg_data_t read_value33;
      uvm_reg_data_t read_value34;
      uvm_reg_data_t read_value35;
      uvm_reg_data_t read_value36;
      uvm_reg_data_t read_value37;
      uvm_reg_data_t read_value38;
      uvm_reg_data_t read_value39;
      uvm_reg_data_t read_value40;
      uvm_reg_data_t read_value41;
      uvm_reg_data_t read_value42;
      uvm_reg_data_t read_value43;
      uvm_reg_data_t read_value44;
      uvm_reg_data_t read_value45;
      uvm_reg_data_t read_value46;
      uvm_reg_data_t read_value47;
      uvm_reg_data_t read_value48;
      uvm_reg_data_t read_value49;
      uvm_reg_data_t read_value50;
      uvm_reg_data_t read_value51;
      uvm_reg_data_t read_value52;
      uvm_reg_data_t read_value53;
      uvm_reg_data_t read_value54;
      uvm_reg_data_t read_value55;
      uvm_reg_data_t read_value56;
      uvm_reg_data_t read_value57;
      uvm_reg_data_t read_value58;
      uvm_reg_data_t read_value59;
      uvm_reg_data_t read_value60;
      uvm_reg_data_t read_value61;
      uvm_reg_data_t read_value62;
      uvm_reg_data_t read_value63;
      uvm_reg_data_t read_value64;
      uvm_reg_data_t read_value65;
      uvm_reg_data_t read_value66;
      uvm_reg_data_t read_value67;
      uvm_reg_data_t read_value68;
      uvm_reg_data_t read_value69;
      uvm_reg_data_t read_value70;
      uvm_reg_data_t read_value71;
      uvm_reg_data_t read_value72;
      uvm_reg_data_t read_value73;
      uvm_reg_data_t read_value74;
      uvm_reg_data_t read_value75;
      uvm_reg_data_t read_value76;
      uvm_reg_data_t read_value77;
      uvm_reg_data_t read_value78;
      uvm_reg_data_t read_value79;
      uvm_reg_data_t read_value80;
      uvm_reg_data_t read_value81;
      uvm_reg_data_t read_value82;
      uvm_reg_data_t read_value83;
      uvm_reg_data_t read_value84;
      uvm_reg_data_t read_value85;
      uvm_reg_data_t read_value86;
      uvm_reg_data_t read_value87;
      uvm_reg_data_t read_value88;
      uvm_reg_data_t read_value89;
      uvm_reg_data_t read_value90;
      uvm_reg_data_t read_value91;
      uvm_reg_data_t read_value92;
      uvm_reg_data_t read_value93;
      uvm_reg_data_t read_value94;
      uvm_reg_data_t read_value95;
      uvm_reg_data_t read_value96;
      uvm_reg_data_t read_value97;
      uvm_reg_data_t read_value98;
      uvm_reg_data_t read_value99;

		function new(string name, uvm_component parent);
			super.new(name, parent);
		endfunction: new

		task main_phase(uvm_phase phase);
	  phase.raise_objection(phase);
//-----------------------------------CPU write, TB read----------------------------------//										 
                     sa_env.chip_reg.MESSAGE_TB.read(.status(status), .value(read_value), .path(UVM_BACKDOOR));
                     sa_env.chip_reg.MESSAGE_CPU.read(.status(status1), .value(read_value1), .path(UVM_BACKDOOR));
                  
                         fork
                     begin
                       while(1) begin
                         if (read_value23!= i || read_value24 != j) begin
                 `uvm_info("DATA REGISTER",$psprintf("TB read value from CPU: data0=%0x,data1=%0x\n", read_value23, read_value24),UVM_LOW)
                           i = read_value23;
                           j = read_value24;
                        end  else begin 
                        sa_env.chip_reg.MESSAGE_TB.read(.status(status23), .value(read_value23), .path(UVM_BACKDOOR));
                        sa_env.chip_reg.MESSAGE_CPU.read(.status(status23), .value(read_value24), .path(UVM_BACKDOOR));
                             #1us;                 
                             end                  
                             end 
                        end

                        begin
                       while(1) begin
                         if (read_value21 != k || read_value22 != l) begin
                 `uvm_info("DATA REGISTER",$psprintf("TB write value to CPU: data2=%0x,data3=%0x\n", read_value21, read_value22),UVM_LOW)
                           k = read_value21;
                           l = read_value22;
                         end  else begin
                        sa_env.chip_reg.DATA2.read(.status(status21), .value(read_value21), .path(UVM_BACKDOOR));
                        sa_env.chip_reg.DATA3.read(.status(status22), .value(read_value22), .path(UVM_BACKDOOR));
                             #1us;                  
                             end                  
                             end end
                   join_none;


                     while (read_value != 'h4 || read_value1 != 'h1 ) begin    // read data0=4,data1=1                                                                           
                        sa_env.chip_reg.MESSAGE_TB.read(.status(status), .value(read_value), .path(UVM_BACKDOOR));
                        sa_env.chip_reg.MESSAGE_CPU.read(.status(status1), .value(read_value1), .path(UVM_BACKDOOR));
                     #1us;
                     end
                     
                        sa_env.chip_reg.DATA3.write(.status(status), .value('h702), .path(UVM_BACKDOOR));//write 1,702
                     sa_env.chip_reg.DATA2.write(.status(status), .value('h1), .path(UVM_BACKDOOR));
    

                        sa_env.chip_reg.MESSAGE_TB.read(.status(status3), .value(read_value3), .path(UVM_BACKDOOR));//read 2,702
                        sa_env.chip_reg.MESSAGE_CPU.read(.status(status4), .value(read_value4), .path(UVM_BACKDOOR));
                     while (read_value3!= 'h2 || read_value4 != 'h702 ) begin
                        sa_env.chip_reg.MESSAGE_TB.read(.status(status3), .value(read_value3), .path(UVM_BACKDOOR));
                        sa_env.chip_reg.MESSAGE_CPU.read(.status(status4), .value(read_value4), .path(UVM_BACKDOOR));
                     #1us;
                     end
                     sa_env.chip_reg.DATA3.write(.status(status8), .value('h1), .path(UVM_BACKDOOR));//write 2,1
                     sa_env.chip_reg.DATA2.write(.status(status7), .value('h2), .path(UVM_BACKDOOR));
     
//---------------------------------------DR0--------------------------------------------------//                     
                        sa_env.chip_reg.MESSAGE_CPU.read(.status(status19), .value(read_value19), .path(UVM_BACKDOOR));
                        sa_env.chip_reg.MESSAGE_TB.read(.status(status20), .value(read_value20), .path(UVM_BACKDOOR));//read 20,55
                     while (read_value20!= 'h20 ) begin
                        sa_env.chip_reg.MESSAGE_CPU.read(.status(status19), .value(read_value19), .path(UVM_BACKDOOR));
                        sa_env.chip_reg.MESSAGE_TB.read(.status(status20), .value(read_value20), .path(UVM_BACKDOOR));
                     #1us;
                     end

                        sa_env.chip_reg.GPIO_DRA.read(.status(status9), .value(read_value9), .path(UVM_BACKDOOR));//read dr0,55
                     if (read_value9 == read_value19 ) begin
                       sa_env.chip_reg.DATA3.write(.status(status11), .value('h1), .path(UVM_BACKDOOR));//write 20,1
                       sa_env.chip_reg.DATA2.write(.status(status10), .value('h20), .path(UVM_BACKDOOR));
                         end else begin 
                       sa_env.chip_reg.DATA3.write(.status(status11), .value('h0), .path(UVM_BACKDOOR));//write 20,1
                       sa_env.chip_reg.DATA2.write(.status(status10), .value('h20), .path(UVM_BACKDOOR));
                       end
                  `uvm_info("IP REGISTER",$psprintf("TB read value from DR0: DR0=%0x\n", read_value9),UVM_LOW)

                        #1ms;
                     sa_env.chip_reg.GPIO_DRA.write(.status(status12), .value('h456), .path(UVM_BACKDOOR));//write dr0,456
                     sa_env.chip_reg.GPIO_DRA.read(.status(status12), .value(read_value12), .path(UVM_BACKDOOR));
                     sa_env.chip_reg.DATA3.write(.status(status13), .value('h456), .path(UVM_BACKDOOR));//write 21,456
                     sa_env.chip_reg.DATA2.write(.status(status14), .value('h21), .path(UVM_BACKDOOR));
                 `uvm_info("IP REGISTER",$psprintf("TB write value to DR0:DR0=%0x\n", read_value12),UVM_LOW)


//-----------------------------------------DDR0---------------------------------------//
                        sa_env.chip_reg.MESSAGE_CPU.read(.status(status29), .value(read_value29), .path(UVM_BACKDOOR));
                        sa_env.chip_reg.MESSAGE_TB.read(.status(status28), .value(read_value28), .path(UVM_BACKDOOR));//read 22,aa
                     while (read_value28!= 'h22 ) begin
                        sa_env.chip_reg.MESSAGE_CPU.read(.status(status29), .value(read_value29), .path(UVM_BACKDOOR));
                        sa_env.chip_reg.MESSAGE_TB.read(.status(status28), .value(read_value28), .path(UVM_BACKDOOR));
                     #1us;
                     end
                       sa_env.chip_reg.GPIO_DDR0.read(.status(status25), .value(read_value25), .path(UVM_BACKDOOR));//read ddr0,aa
                     if (read_value25 == read_value29 ) begin
                     sa_env.chip_reg.DATA3.write(.status(status26), .value('h1), .path(UVM_BACKDOOR));//write 22,1
                     sa_env.chip_reg.DATA2.write(.status(status26), .value('h22), .path(UVM_BACKDOOR));
                     end else begin 
                     sa_env.chip_reg.DATA3.write(.status(status26), .value('h0), .path(UVM_BACKDOOR));//write 22,1
                     sa_env.chip_reg.DATA2.write(.status(status26), .value('h22), .path(UVM_BACKDOOR));
                     end
                  `uvm_info("IP REGISTER",$psprintf("TB read value from DDR0=%0x\n", read_value25),UVM_LOW)

                      #1ms;
                     sa_env.chip_reg.GPIO_DDR0.write(.status(status), .value('h234), .path(UVM_BACKDOOR));//write ddr0,234 
                     sa_env.chip_reg.GPIO_DDR0.read(.status(status), .value(read_value27), .path(UVM_BACKDOOR));
                     sa_env.chip_reg.DATA3.write(.status(status13), .value('h234), .path(UVM_BACKDOOR));//write 23,234
                     sa_env.chip_reg.DATA2.write(.status(status14), .value('h23), .path(UVM_BACKDOOR));
                 `uvm_info("IP REGISTER",$psprintf("TB write value to DDR0=%0x\n", read_value27),UVM_LOW)

//-----------------------------------------IE---------------------------------------//
                        sa_env.chip_reg.MESSAGE_CPU.read(.status(status31), .value(read_value31), .path(UVM_BACKDOOR));
                        sa_env.chip_reg.MESSAGE_TB.read(.status(status30), .value(read_value30), .path(UVM_BACKDOOR));//
                     while (read_value30!= 'h24  ) begin
                        sa_env.chip_reg.MESSAGE_CPU.read(.status(status31), .value(read_value31), .path(UVM_BACKDOOR));
                        sa_env.chip_reg.MESSAGE_TB.read(.status(status30), .value(read_value30), .path(UVM_BACKDOOR));
                     #1us;
                     end
                       sa_env.chip_reg.GPIO_IE.read(.status(status32), .value(read_value32), .path(UVM_BACKDOOR));//read
                     if (read_value32 == read_value31 ) begin
                     sa_env.chip_reg.DATA3.write(.status(status), .value('h1), .path(UVM_BACKDOOR));//
                     sa_env.chip_reg.DATA2.write(.status(status), .value('h24), .path(UVM_BACKDOOR));
                     end else begin 
                     sa_env.chip_reg.DATA3.write(.status(status), .value('h0), .path(UVM_BACKDOOR));//
                     sa_env.chip_reg.DATA2.write(.status(status), .value('h24), .path(UVM_BACKDOOR));
                     end
                  `uvm_info("IP REGISTER",$psprintf("TB read value from IE=%0x\n", read_value32),UVM_LOW)


                      #1ms;
                     sa_env.chip_reg.GPIO_IE.write(.status(status), .value('h648), .path(UVM_BACKDOOR));//wri 
                     sa_env.chip_reg.GPIO_IE.read(.status(status), .value(read_value33), .path(UVM_BACKDOOR));
                     sa_env.chip_reg.DATA3.write(.status(status), .value('h648), .path(UVM_BACKDOOR));//wri
                     sa_env.chip_reg.DATA2.write(.status(status), .value('h25), .path(UVM_BACKDOOR));
                 `uvm_info("IP REGISTER",$psprintf("TB write value to IE=%0x\n", read_value33),UVM_LOW)


//-----------------------------------------IM---------------------------------------//
                        sa_env.chip_reg.MESSAGE_CPU.read(.status(status35), .value(read_value35), .path(UVM_BACKDOOR));
                        sa_env.chip_reg.MESSAGE_TB.read(.status(status34), .value(read_value34), .path(UVM_BACKDOOR));//
                     while (read_value34!= 'h26 ) begin
                        sa_env.chip_reg.MESSAGE_CPU.read(.status(status35), .value(read_value35), .path(UVM_BACKDOOR));
                        sa_env.chip_reg.MESSAGE_TB.read(.status(status34), .value(read_value34), .path(UVM_BACKDOOR));
                     #1us;
                     end
                       sa_env.chip_reg.GPIO_IM.read(.status(status36), .value(read_value36), .path(UVM_BACKDOOR));//read
                     if (read_value36 == read_value35 ) begin
                     sa_env.chip_reg.DATA3.write(.status(status), .value('h1), .path(UVM_BACKDOOR));//
                     sa_env.chip_reg.DATA2.write(.status(status), .value('h26), .path(UVM_BACKDOOR));
                     end else begin 
                     sa_env.chip_reg.DATA3.write(.status(status), .value('h0), .path(UVM_BACKDOOR));//
                     sa_env.chip_reg.DATA2.write(.status(status), .value('h26), .path(UVM_BACKDOOR));
                     end
                  `uvm_info("IP REGISTER",$psprintf("TB read value from IM=%0x\n", read_value36),UVM_LOW)


                      #1ms;
                     sa_env.chip_reg.GPIO_IM.write(.status(status), .value('h98), .path(UVM_BACKDOOR));//wri 
                     sa_env.chip_reg.GPIO_IM.read(.status(status), .value(read_value37), .path(UVM_BACKDOOR));
                     sa_env.chip_reg.DATA3.write(.status(status), .value('h98), .path(UVM_BACKDOOR));//wri
                     sa_env.chip_reg.DATA2.write(.status(status), .value('h27), .path(UVM_BACKDOOR));
                 `uvm_info("IP REGISTER",$psprintf("TB write value to IM=%0x\n", read_value37),UVM_LOW)


//-----------------------------------------ITL---------------------------------------//
                        sa_env.chip_reg.MESSAGE_CPU.read(.status(status39), .value(read_value39), .path(UVM_BACKDOOR));
                        sa_env.chip_reg.MESSAGE_TB.read(.status(status38), .value(read_value38), .path(UVM_BACKDOOR));//
                     while (read_value38!= 'h28 ) begin
                        sa_env.chip_reg.MESSAGE_CPU.read(.status(status39), .value(read_value39), .path(UVM_BACKDOOR));
                        sa_env.chip_reg.MESSAGE_TB.read(.status(status38), .value(read_value38), .path(UVM_BACKDOOR));
                     #1us;
                     end
                       sa_env.chip_reg.GPIO_ITL.read(.status(status40), .value(read_value40), .path(UVM_BACKDOOR));//read
                     if (read_value40 == read_value39 ) begin
                     sa_env.chip_reg.DATA3.write(.status(status), .value('h1), .path(UVM_BACKDOOR));//
                     sa_env.chip_reg.DATA2.write(.status(status), .value('h28), .path(UVM_BACKDOOR));
                     end else begin 
                     sa_env.chip_reg.DATA3.write(.status(status), .value('h0), .path(UVM_BACKDOOR));//
                     sa_env.chip_reg.DATA2.write(.status(status), .value('h28), .path(UVM_BACKDOOR));
                     end
                  `uvm_info("IP REGISTER",$psprintf("TB read value from ITL=%0x\n", read_value40),UVM_LOW)


                      #1ms;
                     sa_env.chip_reg.GPIO_ITL.write(.status(status), .value('h138), .path(UVM_BACKDOOR));//wri 
                     sa_env.chip_reg.GPIO_ITL.read(.status(status), .value(read_value41), .path(UVM_BACKDOOR));
                     sa_env.chip_reg.DATA3.write(.status(status), .value('h138), .path(UVM_BACKDOOR));//wri
                     sa_env.chip_reg.DATA2.write(.status(status), .value('h29), .path(UVM_BACKDOOR));
                 `uvm_info("IP REGISTER",$psprintf("TB write value to ITL=%0x\n", read_value41),UVM_LOW)

//-----------------------------------------IP---------------------------------------//
                        m = m + 'h1;
           read_write_IP_register( 
                             status46,
                             status47,
                             status48,
                             status49,
                             status50,
                             status51,
                             status52,
                             status53,
                             status54,
                             status55,
                             status56,
                             read_value46,
                             read_value47,
                             read_value48,
                             read_value49,
                             m,
                             'h698,
                             "GPIO_IP");
                        m = m + 'h1;
//----------------------------------------IS---------------------------------------//
           read_only_IP_IS_register( 
                             status57,
                             status58,
                             status59,
                             status60,
                             status61,
                             status62,
                             status63,
                             status64,
                             status65,
                             read_value50,
                             read_value51,
                             read_value52,
                             read_value53,
                             read_value54,
                             m,
                             'h300,
                             "GPIO_IS");
                        m = m + 'h1;

//---------------------------------------RIS---------------------------------------//
           read_only_IP_RIS_register( 
                             status57,
                             status58,
                             status59,
                             status60,
                             status61,
                             status62,
                             read_value52,
                             read_value53,
                             read_value54,
                             m,
                             'h340,
                             "GPIO_RIS");
                        m = m + 'h1;

//-----------------------------------------DB---------------------------------------//
                        m = m + 'h1;
           read_write_IP_DB_register( 
                             status46,
                             status47,
                             status48,
                             status49,
                             status50,
                             status51,
                             status52,
                             status53,
                             status54,
                             status55,
                             status56,
                             read_value46,
                             read_value47,
                             read_value48,
                             read_value49,
                             m,
                             'h648,
                             "GPIO_DB");
                        m = m + 'h1;
//----------------------------------------EXTDR0---------------------------------------//
           read_only_EXTDR0_register( 
                             status57,
                             status58,
                             status59,
                             status60,
                             status61,
                             status62,
                             status63,
                             status64,
                             status65,
                             read_value50,
                             read_value51,
                             read_value52,
                             read_value53,
                             read_value54,
                             m,
                             'h5a,
                             "GPIO_EXTDR0");
                        m = m + 'h1;
//-----------------------------------------EOI---------------------------------------------//
                        m = m + 'h1;
           write_only_EOI_register( 
                             m,
                             'h48,
                             "GPIO_EOI");
                        m = m + 'h1;








//--------------------------------------------final response----------------------------//
                        sa_env.chip_reg.MESSAGE_TB.read(.status(status15), .value(read_value15), .path(UVM_BACKDOOR));//read 3,1
                        sa_env.chip_reg.MESSAGE_CPU.read(.status(status16), .value(read_value16), .path(UVM_BACKDOOR));
                     while (read_value15!= 'h3 || read_value16 != 'h1 ) begin
                        sa_env.chip_reg.MESSAGE_TB.read(.status(status15), .value(read_value15), .path(UVM_BACKDOOR));
                        sa_env.chip_reg.MESSAGE_CPU.read(.status(status16), .value(read_value16), .path(UVM_BACKDOOR));
                     #1us;
                     end
                     sa_env.chip_reg.DATA3.write(.status(status17), .value('h1), .path(UVM_BACKDOOR));//write 3,1
                     sa_env.chip_reg.DATA2.write(.status(status18), .value('h3), .path(UVM_BACKDOOR));
                     sa_env.chip_reg.DATA3.read(.status(status), .value(read_value18), .path(UVM_BACKDOOR));
                     sa_env.chip_reg.DATA2.read(.status(status), .value(read_value17), .path(UVM_BACKDOOR));
                 `uvm_info("---SUCCEED---",$psprintf("Simulation completed succeessfully !"),UVM_LOW)
$finish;

								                    #2s;
		     phase.drop_objection(phase);
		endtask: main_phase
    task read_write_IP_register(uvm_status_e status42,
                                uvm_status_e status43,
                                uvm_status_e status44,
                                uvm_status_e status45,
                                uvm_status_e status46,
                                uvm_status_e status47,
                                uvm_status_e status48,
                                uvm_status_e status49,
                                uvm_status_e status50,
                                uvm_status_e status51,
                                uvm_status_e status52,
                                uvm_reg_data_t read_value42,
                                uvm_reg_data_t read_value43,
                                uvm_reg_data_t read_value44,
                                uvm_reg_data_t read_value45,
                                int basic, 
                                int data,
                                string GPIO_IP  );
                        sa_env.chip_reg.MESSAGE_CPU.read(.status(status43), .value(read_value43), .path(UVM_BACKDOOR));
                        sa_env.chip_reg.MESSAGE_TB.read(.status(status42), .value(read_value42), .path(UVM_BACKDOOR));//
                     while (read_value42!= basic  ) begin
                        sa_env.chip_reg.MESSAGE_CPU.read(.status(status43), .value(read_value43), .path(UVM_BACKDOOR));
                        sa_env.chip_reg.MESSAGE_TB.read(.status(status42), .value(read_value42), .path(UVM_BACKDOOR));//
                     #1us;
                     end
                      sa_env.chip_reg.GPIO_IP.read(.status(status44), .value(read_value44), .path(UVM_BACKDOOR));//read
                     if (read_value44 == read_value43) begin
                     sa_env.chip_reg.DATA3.write(.status(status47), .value('h1), .path(UVM_BACKDOOR));//
                     sa_env.chip_reg.DATA2.write(.status(status46), .value(basic), .path(UVM_BACKDOOR));
                     end else begin
                     sa_env.chip_reg.DATA3.write(.status(status51), .value('h0), .path(UVM_BACKDOOR));//
                     sa_env.chip_reg.DATA2.write(.status(status52), .value(basic), .path(UVM_BACKDOOR));
                     end
                  `uvm_info("IP REGISTER",$psprintf("TB read value from %0s=%0x\n",GPIO_IP, read_value44),UVM_LOW)


                      #1ms;
                     sa_env.chip_reg.GPIO_IP.write(.status(status48), .value(data), .path(UVM_BACKDOOR));//wri 
                     sa_env.chip_reg.GPIO_IP.read(.status(status45), .value(read_value45), .path(UVM_BACKDOOR));
                     sa_env.chip_reg.DATA3.write(.status(status50), .value(data), .path(UVM_BACKDOOR));//wri
                     sa_env.chip_reg.DATA2.write(.status(status49), .value(basic +'h01), .path(UVM_BACKDOOR));
                 `uvm_info("IP REGISTER",$psprintf("TB write value to %0s=%0x\n",GPIO_IP, read_value45),UVM_LOW)
    endtask: read_write_IP_register  

    task read_only_IP_RIS_register(uvm_status_e status42,
                                uvm_status_e status43,
                                uvm_status_e status45,
                                uvm_status_e status48,
                                uvm_status_e status49,
                                uvm_status_e status50,
                                uvm_reg_data_t read_value42,
                                uvm_reg_data_t read_value43,
                                uvm_reg_data_t read_value45,
                                int basic, 
                                int data,
                                string GPIO_IS  );
                        sa_env.chip_reg.MESSAGE_CPU.read(.status(status43), .value(read_value43), .path(UVM_BACKDOOR));
                        sa_env.chip_reg.MESSAGE_TB.read(.status(status42), .value(read_value42), .path(UVM_BACKDOOR));//
                     while (read_value42!= basic || read_value43 != 'h1) begin
                        sa_env.chip_reg.MESSAGE_CPU.read(.status(status43), .value(read_value43), .path(UVM_BACKDOOR));
                        sa_env.chip_reg.MESSAGE_TB.read(.status(status42), .value(read_value42), .path(UVM_BACKDOOR));//
                     #1us;
                     end                   
                      #1ms;
                     sa_env.chip_reg.GPIO_RIS.write(.status(status48), .value(data), .path(UVM_BACKDOOR));//wri 
                     sa_env.chip_reg.GPIO_RIS.read(.status(status45), .value(read_value45), .path(UVM_BACKDOOR));
                     if (read_value45 != data) begin
                 `uvm_info("ERROR",$psprintf("TB write value to %0s is failed ! read %0s=%0x\n",GPIO_IS,GPIO_IS, read_value45),UVM_LOW)
                       end else begin
                     sa_env.chip_reg.DATA3.write(.status(status50), .value(data), .path(UVM_BACKDOOR));//wri
                     sa_env.chip_reg.DATA2.write(.status(status49), .value(basic +'h01), .path(UVM_BACKDOOR));
                 `uvm_info("IP REGISTER",$psprintf("TB write value to %0s=%0x\n",GPIO_IS, read_value45),UVM_LOW)
                 end
    endtask: read_only_IP_RIS_register  
    
    task read_only_IP_IS_register(uvm_status_e status42,
                                uvm_status_e status43,
                                uvm_status_e status44,
                                uvm_status_e status45,
                                uvm_status_e status46,
                                uvm_status_e status47,
                                uvm_status_e status48,
                                uvm_status_e status49,
                                uvm_status_e status50,
                                uvm_reg_data_t read_value42,
                                uvm_reg_data_t read_value43,
                                uvm_reg_data_t read_value45,
                                uvm_reg_data_t read_value46,
                                uvm_reg_data_t read_value47,
                                int basic, 
                                int data,
                                string GPIO_IS  );
                        sa_env.chip_reg.MESSAGE_CPU.read(.status(status43), .value(read_value43), .path(UVM_BACKDOOR));
                        sa_env.chip_reg.MESSAGE_TB.read(.status(status42), .value(read_value42), .path(UVM_BACKDOOR));//
                     while (read_value42!= basic || read_value43 != 'h1) begin
                        sa_env.chip_reg.MESSAGE_CPU.read(.status(status43), .value(read_value43), .path(UVM_BACKDOOR));
                        sa_env.chip_reg.MESSAGE_TB.read(.status(status42), .value(read_value42), .path(UVM_BACKDOOR));//
                     #1us;
                     end                   
                      #1ms;
                     sa_env.chip_reg.GPIO_RIS.write(.status(status48), .value('h321), .path(UVM_BACKDOOR));//wri 
                     sa_env.chip_reg.GPIO_IM.write(.status(status44), .value('h77), .path(UVM_BACKDOOR));//wri 
                     sa_env.chip_reg.GPIO_RIS.read(.status(status46), .value(read_value46), .path(UVM_BACKDOOR));//wri 
                     sa_env.chip_reg.GPIO_IM.read(.status(status47), .value(read_value47), .path(UVM_BACKDOOR));//wri 
                     if ((read_value46 & (~read_value47)) != data) begin
                 `uvm_info("ERROR",$psprintf("TB write value to %0s is failed ! read %0s=%0x\n",GPIO_IS,GPIO_IS, data),UVM_LOW)
                       end else begin
                     sa_env.chip_reg.DATA3.write(.status(status50), .value(data), .path(UVM_BACKDOOR));//wri
                     sa_env.chip_reg.DATA2.write(.status(status49), .value(basic +'h01), .path(UVM_BACKDOOR));
                 `uvm_info("DATA",$psprintf("TB write value to %0s is SUCCEED! read %0s=%0x\n",GPIO_IS,GPIO_IS, data),UVM_LOW)
                 end
    endtask: read_only_IP_IS_register  
    
    task read_write_IP_DB_register(uvm_status_e status42,
                                uvm_status_e status43,
                                uvm_status_e status44,
                                uvm_status_e status45,
                                uvm_status_e status46,
                                uvm_status_e status47,
                                uvm_status_e status48,
                                uvm_status_e status49,
                                uvm_status_e status50,
                                uvm_status_e status51,
                                uvm_status_e status52,
                                uvm_reg_data_t read_value42,
                                uvm_reg_data_t read_value43,
                                uvm_reg_data_t read_value44,
                                uvm_reg_data_t read_value45,
                                int basic, 
                                int data,
                                string GPIO_IP  );
                        sa_env.chip_reg.MESSAGE_CPU.read(.status(status43), .value(read_value43), .path(UVM_BACKDOOR));
                        sa_env.chip_reg.MESSAGE_TB.read(.status(status42), .value(read_value42), .path(UVM_BACKDOOR));//
                     while (read_value42!= basic  ) begin
                        sa_env.chip_reg.MESSAGE_CPU.read(.status(status43), .value(read_value43), .path(UVM_BACKDOOR));
                        sa_env.chip_reg.MESSAGE_TB.read(.status(status42), .value(read_value42), .path(UVM_BACKDOOR));//
                     #1us;
                     end
                      sa_env.chip_reg.GPIO_DB.read(.status(status44), .value(read_value44), .path(UVM_BACKDOOR));//read
                     if (read_value44 == read_value43) begin
                     sa_env.chip_reg.DATA3.write(.status(status47), .value('h1), .path(UVM_BACKDOOR));//
                     sa_env.chip_reg.DATA2.write(.status(status46), .value(basic), .path(UVM_BACKDOOR));
                 `uvm_info("RIGHT",$psprintf("CPU write value to %0s is succeed ! read %0s=%0x\n",GPIO_IP,GPIO_IP, read_value44),UVM_LOW)
                     end else begin
                     sa_env.chip_reg.DATA3.write(.status(status51), .value('h0), .path(UVM_BACKDOOR));//
                     sa_env.chip_reg.DATA2.write(.status(status52), .value(basic), .path(UVM_BACKDOOR));
                 `uvm_info("ERROR",$psprintf("CPU write value to %0s is failed ! read %0s=%0x\n",  GPIO_IP,GPIO_IP, read_value44),UVM_LOW)
                     end


                      #1ms;
                     sa_env.chip_reg.GPIO_DB.write(.status(status48), .value(data), .path(UVM_BACKDOOR));//wri 
                     sa_env.chip_reg.GPIO_DB.read(.status(status45), .value(read_value45), .path(UVM_BACKDOOR));
                     sa_env.chip_reg.DATA3.write(.status(status50), .value(data), .path(UVM_BACKDOOR));//wri
                     sa_env.chip_reg.DATA2.write(.status(status49), .value(basic +'h01), .path(UVM_BACKDOOR));
                 `uvm_info("IP REGISTER",$psprintf("TB write value to %0s=%0x\n",GPIO_IP, read_value45),UVM_LOW)
    endtask: read_write_IP_DB_register  
    task read_only_EXTDR0_register(uvm_status_e status42,
                                uvm_status_e status43,
                                uvm_status_e status44,
                                uvm_status_e status45,
                                uvm_status_e status46,
                                uvm_status_e status47,
                                uvm_status_e status48,
                                uvm_status_e status49,
                                uvm_status_e status50,
                                uvm_reg_data_t read_value42,
                                uvm_reg_data_t read_value43,
                                uvm_reg_data_t read_value45,
                                uvm_reg_data_t read_value46,
                                uvm_reg_data_t read_value47,
                                int basic, 
                                int data, 
                                string GPIO_IS  );
                        sa_env.chip_reg.MESSAGE_CPU.read(.status(status43), .value(read_value43), .path(UVM_BACKDOOR));
                        sa_env.chip_reg.MESSAGE_TB.read(.status(status42), .value(read_value42), .path(UVM_BACKDOOR));//
                     while (read_value42!= basic || read_value43 != 'h1) begin
                        sa_env.chip_reg.MESSAGE_CPU.read(.status(status43), .value(read_value43), .path(UVM_BACKDOOR));
                        sa_env.chip_reg.MESSAGE_TB.read(.status(status42), .value(read_value42), .path(UVM_BACKDOOR));//
                     #1us;
                     end                   
                      #1ms;
                     uvm_hdl_force("soc_tb.DUT.u_dig_top.u_aon_domain.u_gpio.U_apb_gpio_apbif.gpio_ext_porta_rb",'h5a);
                     uvm_hdl_read("soc_tb.DUT.u_dig_top.u_aon_domain.u_gpio.U_apb_gpio_apbif.gpio_ext_porta_rb",read_value46);
                     if (read_value46 != data) begin
                 `uvm_info("ERROR",$psprintf("TB write value to %0s is failed ! read %0s=%0x\n",GPIO_IS,GPIO_IS,read_value46),UVM_LOW)
                       end else begin
                     sa_env.chip_reg.DATA3.write(.status(status50), .value('h5a), .path(UVM_BACKDOOR));//wri
                     sa_env.chip_reg.DATA2.write(.status(status49), .value(basic +'h01), .path(UVM_BACKDOOR));
                 `uvm_info("DATA",$psprintf("TB write value to %0s is SUCCEED! read %0s=%0x\n",GPIO_IS,GPIO_IS, data),UVM_LOW)
                 end    

   endtask: read_only_EXTDR0_register    
   task write_only_EOI_register(int basic, 
                                int data,
                                string GPIO_IP  );
                        sa_env.chip_reg.MESSAGE_CPU.read(.status(status43), .value(read_value43), .path(UVM_BACKDOOR));
                        sa_env.chip_reg.MESSAGE_TB.read(.status(status42), .value(read_value42), .path(UVM_BACKDOOR));//
                     while (read_value42!= basic  ) begin
                        sa_env.chip_reg.MESSAGE_CPU.read(.status(status43), .value(read_value43), .path(UVM_BACKDOOR));
                        sa_env.chip_reg.MESSAGE_TB.read(.status(status42), .value(read_value42), .path(UVM_BACKDOOR));//
                     #1us;
                     end
                      sa_env.chip_reg.GPIO_EOI.read(.status(status44), .value(read_value44), .path(UVM_BACKDOOR));//read
                     if (read_value44 == read_value43) begin
                     sa_env.chip_reg.DATA3.write(.status(status47), .value('h1), .path(UVM_BACKDOOR));//
                     sa_env.chip_reg.DATA2.write(.status(status46), .value(basic), .path(UVM_BACKDOOR));
                 `uvm_info("RIGHT",$psprintf("CPU write value to %0s is succeed ! read %0s=%0x\n",GPIO_IP,GPIO_IP, read_value44),UVM_LOW)
                     end else begin
                     sa_env.chip_reg.DATA3.write(.status(status51), .value('h1), .path(UVM_BACKDOOR));//
                     sa_env.chip_reg.DATA2.write(.status(status52), .value(basic), .path(UVM_BACKDOOR));
                 `uvm_info("ERROR",$psprintf("CPU write value to %0s is failed ! read %0s=%0x\n",  GPIO_IP,GPIO_IP, read_value44),UVM_LOW)
                     end

    endtask: write_only_EOI_register  

endclass: chip_gpio_702

class chip_gpio_710 extends chip_base_test;

		`uvm_component_utils(chip_gpio_710)

      int i=16'h0;                  // for print of data0;
      int j=16'h0;                  // for print of data1;    
      int k=16'h0;                  // for print of data2; 
      int l=16'h0;                  // for print of data3;
      int m=32'h0;                  // basic data0 with high_bit and low_bit;
      int s=32'h1;                  // variate of data1 
      int o=32'h0;                  // variate of data1 
      int n=32'h0;                  // cycle times
      int p=32'd1;                  // cycle times        
      uvm_status_e status0;         // status of data0 register
      uvm_status_e status1;         // status of data1 register
      uvm_status_e status2;         // status of data2 register
      uvm_status_e status3;         // status of data3 register
      uvm_status_e status_gpio_dra; // status of gpio_dra register
      uvm_status_e status_gpio_ddr0;// status of gpio_ddr0 register
      uvm_reg_data_t data0;         // value of data0 register
      uvm_reg_data_t data1;         // value of data1 register
      uvm_reg_data_t data2;         // value of data2 register
      uvm_reg_data_t data3;         // value of data3 register
      uvm_reg_data_t gpio_dra;      // value of gpio_dra register
      uvm_reg_data_t gpio_ddr0;     // value of gpio_ddr0 register

		function new(string name, uvm_component parent);
			super.new(name, parent);
		endfunction: new

		task main_phase(uvm_phase phase);

	    phase.raise_objection(phase);
//--------------------CPU write, TB read----------------------------------//										 
      
          fork
            begin
              while(1) begin
                if (data0!= i || data1!= j) begin
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


                     while (data0 != 'h4 || data1 != 'h1 ) begin    // read data0=4,data1=1                                                                           
                     #1us;
                     end
                     
                     sa_env.chip_reg.DATA3.write(.status(status3), .value('h710), .path(UVM_BACKDOOR));//write 1,710
                     sa_env.chip_reg.DATA2.write(.status(status2), .value('h1), .path(UVM_BACKDOOR));

                     while (data0!= 'h2 || data1 != 'h710 ) begin
                     #1us;
                     end
                     sa_env.chip_reg.DATA3.write(.status(status3), .value('h1), .path(UVM_BACKDOOR));//write 2,1
                     sa_env.chip_reg.DATA2.write(.status(status2), .value('h2), .path(UVM_BACKDOOR));
     
//--------------------------------------------check every bit of GPIO_DR0----------------------------//
      for(n = 0 ; n < 32; n++) begin 
        read_only_register(s,'h1);
          end

//--------------------------------------------final response----------------------------//
                     while (data0!= 'h3 || data1 != 'h1 ) begin
                     #1us;
                     end
                     sa_env.chip_reg.DATA3.write(.status(status3), .value('h1), .path(UVM_BACKDOOR));//write 3,1
                     sa_env.chip_reg.DATA2.write(.status(status2), .value('h3), .path(UVM_BACKDOOR));
                     #40ns;
                 `uvm_info("---SUCCEED---",$psprintf("Simulation completed succeessfully !"),UVM_LOW)
$finish;

								                    #3s;
		     phase.drop_objection(phase);
		endtask: main_phase
   //  task read_write_register(uvm_status_e status42,
   //                              uvm_status_e status43,
   //                              uvm_status_e status44,
   //                              uvm_status_e status_gpio_dra,
   //                              uvm_status_e status46,
   //                              uvm_status_e status47,
   //                              uvm_status_e status48,
   //                              uvm_status_e status49,
   //                              uvm_status_e status50,
   //                              uvm_status_e status51,
   //                              uvm_status_e status52,
   //                              uvm_reg_data_t data0,
   //                              uvm_reg_data_t read_value43,
   //                              uvm_reg_data_t read_value44,
   //                              uvm_reg_data_t gpio_dra,
   //                              int basic, 
   //                              int data,
   //                              string GPIO_IP);
   //                      sa_env.chip_reg.MESSAGE_CPU.read(.status(status43), .value(read_value43), .path(UVM_BACKDOOR));
   //                      sa_env.chip_reg.MESSAGE_TB.read(.status(status42), .value(data0), .path(UVM_BACKDOOR));//
   //                   while (data0!= basic  ) begin
   //                      sa_env.chip_reg.MESSAGE_CPU.read(.status(status43), .value(read_value43), .path(UVM_BACKDOOR));
   //                      sa_env.chip_reg.MESSAGE_TB.read(.status(status42), .value(data0), .path(UVM_BACKDOOR));//
   //                   #1us;
   //                   end
   //                    sa_env.chip_reg.GPIO_IP.read(.status(status44), .value(read_value44), .path(UVM_BACKDOOR));//read
   //                   if (read_value44 == read_value43) begin
   //                   sa_env.chip_reg.DATA3.write(.status(status47), .value('h1), .path(UVM_BACKDOOR));//
   //                   sa_env.chip_reg.DATA2.write(.status(status46), .value(basic), .path(UVM_BACKDOOR));
   //                   end else begin
   //                   sa_env.chip_reg.DATA3.write(.status(status51), .value('h0), .path(UVM_BACKDOOR));//
   //                   sa_env.chip_reg.DATA2.write(.status(status52), .value(basic), .path(UVM_BACKDOOR));
   //                   end
   //                `uvm_info("IP REGISTER",$psprintf("TB read value from %0s=%0x\n",GPIO_IP, read_value44),UVM_LOW)


   //                    #44ms;
   //                   sa_env.chip_reg.GPIO_IP.write(.status(status48), .value(data), .path(UVM_BACKDOOR));//wri 
   //                   sa_env.chip_reg.GPIO_IP.read(.status(status_gpio_dra), .value(gpio_dra), .path(UVM_BACKDOOR));
   //                   sa_env.chip_reg.DATA3.write(.status(status50), .value(data), .path(UVM_BACKDOOR));//wri
   //                   sa_env.chip_reg.DATA2.write(.status(status49), .value(basic +'h01), .path(UVM_BACKDOOR));
   //               `uvm_info("IP REGISTER",$psprintf("TB write value to %0s=%0x\n",GPIO_IP, gpio_dra),UVM_LOW)
   //  endtask: read_write_register  


    task read_only_register(int site, int data);

                     while ( data0 == m || data0[31:16] == 'h0) begin
                     #1us;
                       end
                        m = data0;

                     #44us;
                     if (data0[20:16] == 'h1) begin
                     sa_env.chip_reg.GPIO_DRA.read(.status(status_gpio_dra), .value(gpio_dra), .path(UVM_BACKDOOR));
                     if (gpio_dra != site) begin 
                 `uvm_info("ERROR",$psprintf("CPU write %0d bit to GPIO_DRA is failed ! read GPIO_DRA=%0x, s=%0x\n", n,  gpio_dra,site),UVM_LOW)
                     sa_env.chip_reg.DATA3.write(.status(status3), .value('h0), .path(UVM_BACKDOOR));//wri
                     sa_env.chip_reg.DATA2.write(.status(status2), .value(data0), .path(UVM_BACKDOOR));
                       end else begin 
                     sa_env.chip_reg.DATA3.write(.status(status3), .value(data), .path(UVM_BACKDOOR));//wri
                     sa_env.chip_reg.DATA2.write(.status(status2), .value(data0), .path(UVM_BACKDOOR));
                        s*=2;
                 `uvm_info("RIGHT",$psprintf("CPU write %0d bit to GPIO_DRA is succeed ! read GPIO_DRA=%0x\n", n, gpio_dra),UVM_LOW)
                     end 
                     end else if (data0[20:16] == 'h2) begin
                     sa_env.chip_reg.GPIO_DDR0.read(.status(status_gpio_ddr0), .value(gpio_ddr0), .path(UVM_BACKDOOR));
                     if (gpio_ddr0 != site) begin 
                 `uvm_info("ERROR",$psprintf("CPU write %0d bit to GPIO_DDR0 is failed ! read GPIO_DDR0=%0x\n", n,  gpio_dra),UVM_LOW)
                     sa_env.chip_reg.DATA3.write(.status(status3), .value('h0), .path(UVM_BACKDOOR));//wri
                     sa_env.chip_reg.DATA2.write(.status(status2), .value(data0), .path(UVM_BACKDOOR));
                       end else begin 
                     sa_env.chip_reg.DATA3.write(.status(status3), .value(data), .path(UVM_BACKDOOR));//wri
                     sa_env.chip_reg.DATA2.write(.status(status2), .value(data0), .path(UVM_BACKDOOR));
                 `uvm_info("RIGHT",$psprintf("CPU write %0d bit to GPIO_DDR0 is succeed ! read GPIO_DDR0=%0x\n", n, gpio_dra),UVM_LOW)
                     end 
                     end 

    endtask: read_only_register
endclass: chip_gpio_710
*/


class chip_gpio extends chip_base_test;
		`uvm_component_utils(chip_gpio)

      int i=16'h0; // for print of data0;
      int j=16'h0; // for print of data1;    
      int k=16'h0; // for print of data2; 
      int l=16'h0; // for print of data3;
      int m=32'h0; // basic data0 with high_bit and low_bit;
      int n=32'd0; // cycle times
      int o=32'h1; // value of data3 and register for print    
      int p=32'd2; // cycle times                    
      int q=32'd2; // read_only register selected                    
      int r=32'd0; //                    
      int s=32'h20; // for data2
      int t=32'h0; // 
      int u=32'h0; // 
      uvm_status_e status; 
      uvm_status_e status1;
      uvm_status_e status2;
      uvm_status_e status3;
      uvm_status_e status4;
      uvm_status_e status5;
      uvm_status_e status6;
      uvm_status_e status7;
      uvm_status_e status8;
      uvm_status_e status9;
      uvm_status_e status10;
      uvm_status_e status11;
      uvm_status_e status12;
      uvm_status_e status13;
      uvm_status_e status14;
      uvm_status_e status15;
      uvm_status_e status16;
      uvm_status_e status17;
      uvm_status_e status18;
      uvm_status_e status19;
      uvm_status_e status20;
      uvm_status_e status21;
      uvm_status_e status22;
      uvm_status_e status23;
      uvm_status_e status24;
      uvm_status_e status25;
      uvm_status_e status26;
      uvm_status_e status27;
      uvm_status_e status28;
      uvm_status_e status29;
      uvm_status_e status30;
      uvm_status_e status31;
      uvm_status_e status32;
      uvm_status_e status33;
      uvm_status_e status34;
      uvm_status_e status35;
      uvm_status_e status36;
      uvm_status_e status37;
      uvm_status_e status38;
      uvm_status_e status39;
      uvm_status_e status40;
      uvm_status_e status41;
      uvm_status_e status42;
      uvm_status_e status43;
      uvm_status_e status44;
      uvm_status_e status45;
      uvm_status_e status46;
      uvm_status_e status47;
      uvm_status_e status48;
      uvm_status_e status49;
      uvm_status_e status50;
      uvm_status_e status51;
      uvm_status_e status52;
      uvm_status_e status53;
      uvm_status_e status54;
      uvm_status_e status55;
      uvm_status_e status56;
      uvm_status_e status57;
      uvm_status_e status58;
      uvm_status_e status59;
      uvm_status_e status60;
      uvm_status_e status61;
      uvm_status_e status62;
      uvm_status_e status63;
      uvm_status_e status70;
      uvm_reg_data_t read_value;
      uvm_reg_data_t read_value1;
      uvm_reg_data_t read_value2;
      uvm_reg_data_t read_value3;
      uvm_reg_data_t read_value4;
      uvm_reg_data_t read_value5;
      uvm_reg_data_t read_value6;
      uvm_reg_data_t read_value7;
      uvm_reg_data_t read_value8;
      uvm_reg_data_t read_value9;
      uvm_reg_data_t read_value10;
      uvm_reg_data_t read_value11;
      uvm_reg_data_t read_value12;
      uvm_reg_data_t read_value13;
      uvm_reg_data_t read_value14;
      uvm_reg_data_t read_value15;
      uvm_reg_data_t read_value16;
      uvm_reg_data_t read_value17;
      uvm_reg_data_t read_value18;
      uvm_reg_data_t read_value19;
      uvm_reg_data_t read_value20;
      uvm_reg_data_t read_value21;
      uvm_reg_data_t read_value22;
      uvm_reg_data_t read_value23;
      uvm_reg_data_t read_value24;
      uvm_reg_data_t read_value25;
      uvm_reg_data_t read_value26;
      uvm_reg_data_t read_value27;
      uvm_reg_data_t read_value28;
      uvm_reg_data_t read_value29;
      uvm_reg_data_t read_value30;
      uvm_reg_data_t read_value31;
      uvm_reg_data_t read_value32;
      uvm_reg_data_t read_value33;
      uvm_reg_data_t read_value34;
      uvm_reg_data_t read_value35;
      uvm_reg_data_t read_value36;
      uvm_reg_data_t read_value37;
      uvm_reg_data_t read_value38;
      uvm_reg_data_t read_value39;
      uvm_reg_data_t read_value40;
      uvm_reg_data_t read_value41;
      uvm_reg_data_t read_value42;
      uvm_reg_data_t read_value43;
      uvm_reg_data_t read_value44;
      uvm_reg_data_t read_value45;
      uvm_reg_data_t read_value46;
      uvm_reg_data_t read_value47;
      uvm_reg_data_t read_value48;
      uvm_reg_data_t read_value49;
      uvm_reg_data_t read_value50;
      uvm_reg_data_t read_value51;
      uvm_reg_data_t read_value52;
      uvm_reg_data_t read_value53;
      uvm_reg_data_t read_value54;
      uvm_reg_data_t read_value55;
      uvm_reg_data_t read_value56;
      uvm_reg_data_t read_value57;
      uvm_reg_data_t read_value58;
      uvm_reg_data_t read_value59;
      uvm_reg_data_t read_value60;
      uvm_reg_data_t read_value61;
      uvm_reg_data_t read_value62;
      uvm_reg_data_t read_value63;
		function new(string name, uvm_component parent);
			super.new(name, parent);
		endfunction: new

		task main_phase(uvm_phase phase);


	                   phase.raise_objection(phase);
//-----------------------------------CPU write, TB read----------------------------------//										 
                     sa_env.chip_reg.MESSAGE_TB.read(.status(status), .value(read_value), .path(UVM_BACKDOOR));
                     sa_env.chip_reg.MESSAGE_CPU.read(.status(status1), .value(read_value1), .path(UVM_BACKDOOR));
                  
                         fork
                     begin
                       while(1) begin
                         if (read_value23!= i || read_value24 != j) begin
                 `uvm_info("DATA REGISTER",$psprintf("TB read value from CPU: data0=%0x,data1=%0x\n", read_value23, read_value24),UVM_LOW)
                           i = read_value23;
                           j = read_value24;
                        end  else begin 
                        sa_env.chip_reg.MESSAGE_TB.read(.status(status23), .value(read_value23), .path(UVM_BACKDOOR));
                        sa_env.chip_reg.MESSAGE_CPU.read(.status(status23), .value(read_value24), .path(UVM_BACKDOOR));
                             #1us;                 
                             end                  
                             end 
                        end

                        begin
                       while(1) begin
                         if (read_value21 != k || read_value22 != l) begin
                 `uvm_info("DATA REGISTER",$psprintf("TB write value to CPU: data2=%0x,data3=%0x\n", read_value21, read_value22),UVM_LOW)
                           k = read_value21;
                           l = read_value22;
                         end  else begin
                        sa_env.chip_reg.DATA2.read(.status(status21), .value(read_value21), .path(UVM_BACKDOOR));
                        sa_env.chip_reg.DATA3.read(.status(status22), .value(read_value22), .path(UVM_BACKDOOR));
                             #1us;                  
                             end                  
                             end end

                       begin
                           while(1) begin
                         if (n != p) begin
                 `uvm_info("N",$psprintf("n=%0d\n", n),UVM_LOW)
                 p = n;
                             end
                             #1us;
                             end
                                      end
//			begin
//			  force `SCUREG_XRM.pad_cfg[67] = 'h0 ;
//				@(posedge `SCUREG_XRM.presetn) ;
//                          release `SCUREG_XRM.pad_cfg;
//			end	
//			begin
//				while(1) begin
//                                sa_env.chip_reg.PAD_CFG1.write(.status(status21), .value({8{8'b0111}}), .path(UVM_BACKDOOR));
//					@(posedge `CLK_XRM.pclk_main);
//			        	if(`SCUREG_XRM.presetn == 'h1) begin break; end
//			        end
//			end
                   join_none;


//                     while (read_value != 'h4 || read_value1 != 'h1 ) begin    // read data0=4,data1=1                                                                           
//                        sa_env.chip_reg.MESSAGE_TB.read(.status(status), .value(read_value), .path(UVM_BACKDOOR));
//                        sa_env.chip_reg.MESSAGE_CPU.read(.status(status1), .value(read_value1), .path(UVM_BACKDOOR));
//                     #1us;
//                     end
//                     
//                        sa_env.chip_reg.DATA3.write(.status(status), .value('h711), .path(UVM_BACKDOOR));//write 1,711
//                     sa_env.chip_reg.DATA2.write(.status(status), .value('h1), .path(UVM_BACKDOOR));
//    
//
//                        sa_env.chip_reg.MESSAGE_TB.read(.status(status3), .value(read_value3), .path(UVM_BACKDOOR));//read 2,711
//                        sa_env.chip_reg.MESSAGE_CPU.read(.status(status4), .value(read_value4), .path(UVM_BACKDOOR));
//                     while (read_value3!= 'h2 || read_value4 != 'h711 ) begin
//                        sa_env.chip_reg.MESSAGE_TB.read(.status(status3), .value(read_value3), .path(UVM_BACKDOOR));
//                        sa_env.chip_reg.MESSAGE_CPU.read(.status(status4), .value(read_value4), .path(UVM_BACKDOOR));
//                     #1us;
//                     end
//                     sa_env.chip_reg.DATA3.write(.status(status8), .value('h1), .path(UVM_BACKDOOR));//write 2,1
//                     sa_env.chip_reg.DATA2.write(.status(status7), .value('h2), .path(UVM_BACKDOOR));
//                     sa_env.chip_reg.DATA3.read(.status(status62), .value(read_value62), .path(UVM_BACKDOOR));//write 2,1
//                     sa_env.chip_reg.DATA2.read(.status(status63), .value(read_value63), .path(UVM_BACKDOOR));
//                     while (  read_value63 != 'h2  ||  read_value62 != 'h1) begin
//                     sa_env.chip_reg.DATA3.read(.status(status62), .value(read_value62), .path(UVM_BACKDOOR));//write 2,1
//                     sa_env.chip_reg.DATA2.read(.status(status63), .value(read_value63), .path(UVM_BACKDOOR));
//                     #1us;
//                       end
     
//--------------------------------------------check every bit of GPIO_DR0----------------------------//

      for  (n = 0 ; n < 20*8; n++) begin 
        writable_register;
                 end
                        sa_env.chip_reg.MESSAGE_CPU.read(.status(status43), .value(read_value43), .path(UVM_BACKDOOR));
                        sa_env.chip_reg.MESSAGE_TB.read(.status(status42), .value(read_value42), .path(UVM_BACKDOOR));//
                     while (read_value42!= 'h5  ) begin
                        sa_env.chip_reg.MESSAGE_CPU.read(.status(status43), .value(read_value43), .path(UVM_BACKDOOR));
                        sa_env.chip_reg.MESSAGE_TB.read(.status(status42), .value(read_value42), .path(UVM_BACKDOOR));//
                     #1us;
                     end
                     sa_env.chip_reg.DATA3.write(.status(status22), .value('h1), .path(UVM_BACKDOOR));//write 5,1
                     sa_env.chip_reg.DATA2.write(.status(status21), .value('h5), .path(UVM_BACKDOOR));
                     while (  read_value21 != 'h5  ||  read_value22 != 'h1) begin
                     sa_env.chip_reg.DATA3.read(.status(status22), .value(read_value22), .path(UVM_BACKDOOR));//write 2,1
                     sa_env.chip_reg.DATA2.read(.status(status21), .value(read_value21), .path(UVM_BACKDOOR));
                     #1us;
                       end
                     #1us;
        n=0; o=1;      for (n=0; n<20; n++)begin         read_only_register('h7);        end 
        n=0; o=1;      for (n=0; n<20; n++)begin         read_only_register('h8);        end
        n=0; o=1;      for (n=0; n<20; n++)begin         read_only_register('ha);        end    
           sa_env.chip_reg.DATA3.write(.status(status3), .value('h1), .path(UVM_BACKDOOR));//write 
           sa_env.chip_reg.DATA2.write(.status(status2), .value('h6), .path(UVM_BACKDOOR));
                     while (read_value21 != 'h6 || read_value22 != 'h1 ) begin
                       #1us;
                     end
                       #1us;

//--------------------------------------------final response----------------------------//
                        sa_env.chip_reg.MESSAGE_TB.read(.status(status15), .value(read_value15), .path(UVM_BACKDOOR));//read 3,1
                        sa_env.chip_reg.MESSAGE_CPU.read(.status(status16), .value(read_value16), .path(UVM_BACKDOOR));
                     while (read_value15!= 'h3 || read_value16 != 'h1 ) begin
                        sa_env.chip_reg.MESSAGE_TB.read(.status(status15), .value(read_value15), .path(UVM_BACKDOOR));
                        sa_env.chip_reg.MESSAGE_CPU.read(.status(status16), .value(read_value16), .path(UVM_BACKDOOR));
                     #1us;
                     end
                     sa_env.chip_reg.DATA3.write(.status(status17), .value('h1), .path(UVM_BACKDOOR));//write 3,1
                     sa_env.chip_reg.DATA2.write(.status(status18), .value('h3), .path(UVM_BACKDOOR));
                     sa_env.chip_reg.DATA3.read(.status(status), .value(read_value18), .path(UVM_BACKDOOR));
                     sa_env.chip_reg.DATA2.read(.status(status), .value(read_value17), .path(UVM_BACKDOOR));
                     #90ns;
                 `uvm_info("---SUCCEED---",$psprintf("Simulation completed succeessfully !"),UVM_LOW)
$finish;

								                    #18s;
		     phase.drop_objection(phase);
		endtask: main_phase
    task read_only_register(int q);

                     if (q == 'h7) begin
                       uvm_hdl_force("soc_tb.DUT.u_dig_top.u_aon_domain.u_gpio.U_apb_gpio_apbif.gpio_intstatus", o);
                         s[31:16] = 'h7;
                       sa_env.chip_reg.DATA3.write(.status(status50), .value(o), .path(UVM_BACKDOOR));//wri
                       sa_env.chip_reg.DATA2.write(.status(status49), .value(s), .path(UVM_BACKDOOR));
                 `uvm_info("IP REGISTER",$psprintf("TB write value to GPIO_IS=%0x\n", o),UVM_LOW)
                         end else if(q == 'h8) begin  
                     sa_env.chip_reg.GPIO_RIS.write(.status(status70), .value(o), .path(UVM_BACKDOOR));//
                         s[31:16] = 'h8;
                       sa_env.chip_reg.DATA3.write(.status(status50), .value(o), .path(UVM_BACKDOOR));//wri
                       sa_env.chip_reg.DATA2.write(.status(status49), .value(s), .path(UVM_BACKDOOR));
                 `uvm_info("IP REGISTER",$psprintf("TB write value to GPIO_RIS=%0x\n",o),UVM_LOW)
                         end else if(q == 'ha) begin
                     uvm_hdl_force("soc_tb.DUT.u_dig_top.u_aon_domain.u_gpio.U_apb_gpio_apbif.gpio_ext_porta_rb", o);
                         s[31:16] = 'ha;
                       sa_env.chip_reg.DATA3.write(.status(status50), .value(o), .path(UVM_BACKDOOR));//wri
                       sa_env.chip_reg.DATA2.write(.status(status49), .value(s), .path(UVM_BACKDOOR));
                 `uvm_info("IP REGISTER",$psprintf("TB write value to GPIO_EXTDR0=%0x\n",o),UVM_LOW)
                         end
                     #1us;
                     while (read_value23 != s || read_value24 != 'h1) begin
                     #1us;  
                       end

                          o = o*2;
                          s = s + 'h1;
    endtask: read_only_register  


    task writable_register;
                        sa_env.chip_reg.MESSAGE_CPU.read(.status(status43), .value(read_value43), .path(UVM_BACKDOOR));
                        sa_env.chip_reg.MESSAGE_TB.read(.status(status42), .value(read_value42), .path(UVM_BACKDOOR));//
                     while ( read_value42 == m || read_value42[31:16] == 'h0) begin
                        sa_env.chip_reg.MESSAGE_CPU.read(.status(status43), .value(read_value43), .path(UVM_BACKDOOR));
                        sa_env.chip_reg.MESSAGE_TB.read(.status(status42), .value(read_value42), .path(UVM_BACKDOOR));//
                     #1us;
                       end

                     #4us;
                     if (read_value42[20:16] == 'h1) begin
                     sa_env.chip_reg.GPIO_DRA.read(.status(status45), .value(read_value45), .path(UVM_BACKDOOR));
                     if (read_value45 != read_value43) begin 
                 `uvm_info("ERROR",$psprintf("CPU write value to GPIO_DRA is failed ! read GPIO_DRA=%0x\n",   read_value45),UVM_LOW)
                     sa_env.chip_reg.DATA3.write(.status(status50), .value('h0), .path(UVM_BACKDOOR));//wri
                     sa_env.chip_reg.DATA2.write(.status(status49), .value(read_value42), .path(UVM_BACKDOOR));
                       end else begin 
                     sa_env.chip_reg.DATA3.write(.status(status50), .value('h1), .path(UVM_BACKDOOR));//wri
                     sa_env.chip_reg.DATA2.write(.status(status49), .value(read_value42), .path(UVM_BACKDOOR));
                        m = read_value42;
                 `uvm_info("RIGHT",$psprintf("CPU write value to GPIO_DRA is succeed ! read GPIO_DRA=%0x\n",   read_value45),UVM_LOW)
                     end 
                     end else if (read_value42[20:16] == 'h2) begin
                     sa_env.chip_reg.GPIO_DDR0.read(.status(status45), .value(read_value45), .path(UVM_BACKDOOR));
                     if (read_value45 != read_value43) begin 
                 `uvm_info("ERROR",$psprintf("CPU write value to GPIO_DDR0 is failed ! read GPIO_DDR0=%0x\n",   read_value45),UVM_LOW)
                     sa_env.chip_reg.DATA3.write(.status(status50), .value('h0), .path(UVM_BACKDOOR));//wri
                     sa_env.chip_reg.DATA2.write(.status(status49), .value(read_value42), .path(UVM_BACKDOOR));
                       end else begin 
                     sa_env.chip_reg.DATA3.write(.status(status50), .value('h1), .path(UVM_BACKDOOR));//wri
                     sa_env.chip_reg.DATA2.write(.status(status49), .value(read_value42), .path(UVM_BACKDOOR));
                        m = read_value42;
                 `uvm_info("RIGHT",$psprintf("CPU write value to GPIO_DDR0 is succeed ! read GPIO_DDR0=%0x\n",   read_value45),UVM_LOW)
                     end                     
                     end else if (read_value42[20:16] == 'h3) begin
                     sa_env.chip_reg.GPIO_IE.read(.status(status45), .value(read_value45), .path(UVM_BACKDOOR));
                     if (read_value45 != read_value43) begin 
                 `uvm_info("ERROR",$psprintf("CPU write value to GPIO_IE is failed ! read GPIO_IE=%0x\n",   read_value45),UVM_LOW)
                     sa_env.chip_reg.DATA3.write(.status(status50), .value('h0), .path(UVM_BACKDOOR));//wri
                     sa_env.chip_reg.DATA2.write(.status(status49), .value(read_value42), .path(UVM_BACKDOOR));
                       end else begin 
                     sa_env.chip_reg.DATA3.write(.status(status50), .value('h1), .path(UVM_BACKDOOR));//wri
                     sa_env.chip_reg.DATA2.write(.status(status49), .value(read_value42), .path(UVM_BACKDOOR));
                        m = read_value42;
                 `uvm_info("RIGHT",$psprintf("CPU write value to GPIO_IE is succeed ! read GPIO_IE=%0x\n",   read_value45),UVM_LOW)
                     end 
                     end else if (read_value42[20:16] == 'h4) begin
                     sa_env.chip_reg.GPIO_IM.read(.status(status45), .value(read_value45), .path(UVM_BACKDOOR));
                     if (read_value45 != read_value43) begin 
                 `uvm_info("ERROR",$psprintf("CPU write value to GPIO_IM is failed ! read GPIO_IM=%0x\n",   read_value45),UVM_LOW)
                     sa_env.chip_reg.DATA3.write(.status(status50), .value('h0), .path(UVM_BACKDOOR));//wri
                     sa_env.chip_reg.DATA2.write(.status(status49), .value(read_value42), .path(UVM_BACKDOOR));
                       end else begin 
                     sa_env.chip_reg.DATA3.write(.status(status50), .value('h1), .path(UVM_BACKDOOR));//wri
                     sa_env.chip_reg.DATA2.write(.status(status49), .value(read_value42), .path(UVM_BACKDOOR));
                        m = read_value42;
                 `uvm_info("RIGHT",$psprintf("CPU write value to GPIO_IM is succeed ! read GPIO_IM=%0x\n",   read_value45),UVM_LOW)
                     end 
                     end else if (read_value42[20:16] == 'h5) begin
                     sa_env.chip_reg.GPIO_ITL.read(.status(status45), .value(read_value45), .path(UVM_BACKDOOR));
                     if (read_value45 != read_value43) begin 
                 `uvm_info("ERROR",$psprintf("CPU write value to GPIO_ITL is failed ! read GPIO_ITL=%0x\n",   read_value45),UVM_LOW)
                     sa_env.chip_reg.DATA3.write(.status(status50), .value('h0), .path(UVM_BACKDOOR));//wri
                     sa_env.chip_reg.DATA2.write(.status(status49), .value(read_value42), .path(UVM_BACKDOOR));
                       end else begin 
                     sa_env.chip_reg.DATA3.write(.status(status50), .value('h1), .path(UVM_BACKDOOR));//wri
                     sa_env.chip_reg.DATA2.write(.status(status49), .value(read_value42), .path(UVM_BACKDOOR));
                        m = read_value42;
                 `uvm_info("RIGHT",$psprintf("CPU write value to GPIO_ITL is succeed ! read GPIO_ITL=%0x\n",   read_value45),UVM_LOW)
                     end 
                     end else if (read_value42[20:16] == 'h6) begin
                     sa_env.chip_reg.GPIO_IP.read(.status(status45), .value(read_value45), .path(UVM_BACKDOOR));
                     if (read_value45 != read_value43) begin 
                 `uvm_info("ERROR",$psprintf("CPU write value to GPIO_IP is failed ! read GPIO_IP=%0x\n",   read_value45),UVM_LOW)
                     sa_env.chip_reg.DATA3.write(.status(status50), .value('h0), .path(UVM_BACKDOOR));//wri
                     sa_env.chip_reg.DATA2.write(.status(status49), .value(read_value42), .path(UVM_BACKDOOR));
                       end else begin 
                     sa_env.chip_reg.DATA3.write(.status(status50), .value('h1), .path(UVM_BACKDOOR));//wri
                     sa_env.chip_reg.DATA2.write(.status(status49), .value(read_value42), .path(UVM_BACKDOOR));
                        m = read_value42;
                 `uvm_info("RIGHT",$psprintf("CPU write value to GPIO_IP is succeed ! read GPIO_IP=%0x\n",   read_value45),UVM_LOW)
                     end 
                     end else if (read_value42[20:16] == 'h9) begin
                     sa_env.chip_reg.GPIO_DB.read(.status(status45), .value(read_value45), .path(UVM_BACKDOOR));
                     if (read_value45 != read_value43) begin 
                 `uvm_info("ERROR",$psprintf("CPU write value to GPIO_DB is failed ! read GPIO_DB=%0x\n",   read_value45),UVM_LOW)
                     sa_env.chip_reg.DATA3.write(.status(status50), .value('h0), .path(UVM_BACKDOOR));//wri
                     sa_env.chip_reg.DATA2.write(.status(status49), .value(read_value42), .path(UVM_BACKDOOR));
                       end else begin 
                     sa_env.chip_reg.DATA3.write(.status(status50), .value('h1), .path(UVM_BACKDOOR));//wri
                     sa_env.chip_reg.DATA2.write(.status(status49), .value(read_value42), .path(UVM_BACKDOOR));
                        m = read_value42;
                 `uvm_info("RIGHT",$psprintf("CPU write value to GPIO_DB is succeed ! read GPIO_DB=%0x\n",   read_value45),UVM_LOW)
                     end 
                     end else if (read_value42[20:16] == 'hb) begin
                     sa_env.chip_reg.GPIO_EOI.read(.status(status45), .value(read_value45), .path(UVM_BACKDOOR));
                     if (read_value45 != read_value43) begin 
                 `uvm_info("ERROR",$psprintf("CPU write value to GPIO_EOI is failed ! read GPIO_EOI=%0x\n",   read_value45),UVM_LOW)
                     sa_env.chip_reg.DATA3.write(.status(status50), .value('h1), .path(UVM_BACKDOOR));//wri
                     sa_env.chip_reg.DATA2.write(.status(status49), .value(read_value42), .path(UVM_BACKDOOR));
                        m = read_value42;
                       end else begin 
                     sa_env.chip_reg.DATA3.write(.status(status50), .value('h1), .path(UVM_BACKDOOR));//wr i  
                     sa_env.chip_reg.DATA2.write(.status(status49), .value(read_value42), .path(UVM_BACKDOOR));
                        m = read_value42;
                 `uvm_info("RIGHT",$psprintf("CPU write value to GPIO_EOI is succeed ! read GPIO_EOI=%0x\n",   read_value45),UVM_LOW)
                     end 
                     end 
                     s[15:0] = m[15:0] + 'h1; 
    endtask: writable_register
endclass: chip_gpio

