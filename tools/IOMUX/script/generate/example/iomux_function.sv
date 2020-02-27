//printf begin ---------------------------------
task iomux_function;

  reg test_error = 0;
  force `DUT_XRM.test_en = 0;

//printf end ---------------------------------

//generated begin ----------------------------
//O
  initial begin
  	#0;
  	release `DUT_XRM.GPIO[00]; 
  	force `UART0_XRM.sout  = $urandom;
  	force `IOMUX_XRM.pad_cfg[ 0*8+:8] = 'h00;    
  end
  chech_in_function(`DUT_XRM.GPIO[00]		,`UART0_XRM.sout                ,"GPIO[00]"  	,'h00	,test_error	,"OUT");
//I of IO
  initial begin
  	#1000;		//add 1000 once a time
  	release `GPIO_XRM.gpio_ext_porta[0]; 
  	force `DUT_XRM.GPIO[00] = $urandom;
  	force `IOMUX_XRM.pad_cfg[ 0*8+:8] = 'h10;  
  	force `GPIO_XRM.gpio_porta_ddr[0] = 'b0; //OEN=1 
  end
  chech_in_function(`GPIO_XRM.gpio_ext_porta[0]	,`DUT_XRM.GPIO[00]		,"GPIO[00]"	,'h10	,test_error	,"IN");
//O of IO
  initial begin
  	#2000;
  	release  `DUT_XRM.GPIO[00]; 
  	force ``GPIO_XRM.gpio_porta_dr[0] = $urandom;
  	force `IOMUX_XRM.pad_cfg[ 0*8+:8] = 'h10;  
  	force `GPIO_XRM.gpio_porta_ddr[0] = 'b1; 	//OEN=0 
  end
  chech_in_function(`DUT_XRM.GPIO[00]  		,`GPIO_XRM.gpio_porta_dr[0]	,"GPIO[00]"  	,'h10	,test_error	,"OUT");
//O
  initial begin
  	#3000;
  	release `DUT_XRM.GPIO[00]; 
  	force `UART0_XRM.sout  = $urandom;
  	force `IOMUX_XRM.pad_cfg[ 0*8+:8] = 'h30;    
  end
  chech_in_function(`DUT_XRM.GPIO[00]  		,`UART0_XRM.sout                ,"GPIO[00]"  	,'h30	,test_error	,"OUT");
//O
  initial begin
  	#4000;
  	release `DUT_XRM.GPIO[00]; 
  	force `UART0_XRM.sout  = $urandom;
  	force `IOMUX_XRM.pad_cfg[ 0*8+:8] = 'h40;    
  end
  chech_in_function(`DUT_XRM.GPIO[00]  		,`UART0_XRM.sout                ,"GPIO[00]"  	,'h40	,test_error	,"OUT");
//O
  initial begin
  	#5000;
  	release `DUT_XRM.GPIO[00]; 
  	force `UART0_XRM.sout  = $urandom;
  	force `IOMUX_XRM.pad_cfg[ 0*8+:8] = 'h50;    
  end
  chech_in_function(`DUT_XRM.GPIO[00]  		,`UART0_XRM.sout                ,"GPIO[00]"  	,'h50	,test_error	,"OUT");
//release
  initial begin
  	#6000;
  	force `IOMUX_XRM.pad_cfg[ 0*8+:8] = 'hz;    
  end

  ...

//generated end ----------------------------



//printf begin ---------------------------------------------------------------------
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
endtask: chech_in_function
//printf end-------------------------------------------------------------------------
