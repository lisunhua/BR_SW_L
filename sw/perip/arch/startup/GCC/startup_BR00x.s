/**************************************************************************//**
 * @file     startup_CM3DS_MPS2.s
 * @brief    CMSIS Cortex-M3 Core Device Startup File for
 *           Device CM3DS_MPS2_
 * @version  V3.01
 * @date     06. March 2012
 *
 * @note      Should use with GCC for ARM Embedded Processors
 * Copyright (C) 2012,2017 ARM Limited. All rights reserved.
 *
 * @par
 * ARM Limited (ARM) is supplying this software for use with Cortex-M
 * processor based microcontrollers.  This file can be freely distributed
 * within development tools that are supporting such ARM based processors.
 *
 * @par
 * THIS SOFTWARE IS PROVIDED "AS IS".  NO WARRANTIES, WHETHER EXPRESS, IMPLIED
 * OR STATUTORY, INCLUDING, BUT NOT LIMITED TO, IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE APPLY TO THIS SOFTWARE.
 * ARM SHALL NOT, IN ANY CIRCUMSTANCES, BE LIABLE FOR SPECIAL, INCIDENTAL, OR
 * CONSEQUENTIAL DAMAGES, FOR ANY REASON WHATSOEVER.
 *
 ******************************************************************************/
/*****************************************************************************/
/* startup_CM3DS_MPS2.s: Startup file for CM3DS_MPS2 device series               */
/*****************************************************************************/
/* Version: GNU Tools for ARM Embedded Processors                          */
/*****************************************************************************/


    .syntax unified
    .arch armv7-m

    .section .stack
    .align 3

/*
// <h> Stack Configuration
//   <o> Stack Size (in Bytes) <0x0-0xFFFFFFFF:8>
// </h>
*/

    .section .stack
    .align 3
#ifdef __STACK_SIZE
    .equ    Stack_Size, __STACK_SIZE
#else
    .equ    Stack_Size, 0x1000
#endif
    .globl    __StackTop
    .globl    __StackLimit
__StackLimit:
    .space    Stack_Size
    .size __StackLimit, . - __StackLimit
__StackTop:
    .size __StackTop, . - __StackTop


/*
// <h> Heap Configuration
//   <o>  Heap Size (in Bytes) <0x0-0xFFFFFFFF:8>
// </h>
*/

    .section .heap
    .align 3
#ifdef __HEAP_SIZE
    .equ    Heap_Size, __HEAP_SIZE
#else
    .equ    Heap_Size, 0x2000
#endif
    .globl    __HeapBase
    .globl    __HeapLimit
__HeapBase:
    .if    Heap_Size
    .space    Heap_Size
    .endif
    .size __HeapBase, . - __HeapBase
__HeapLimit:
    .size __HeapLimit, . - __HeapLimit


/* Vector Table */

    .section .isr_vector
    .align 2
    .globl __isr_vector
__isr_vector:
    .long   __StackTop                  /* Top of Stack                  */
    .long   Reset_Handler               /* Reset Handler                 */
    .long   NMI_Handler                 /* NMI Handler                   */
    .long   HardFault_Handler           /* Hard Fault Handler            */
    .long   MemManage_Handler           /* MPU Fault Handler             */
    .long   BusFault_Handler            /* Bus Fault Handler             */
    .long   UsageFault_Handler          /* Usage Fault Handler           */
    .long   0                           /* Reserved                      */
    .long   0                           /* Reserved                      */
    .long   0                           /* Reserved                      */
    .long   0                           /* Reserved                      */
    .long   SVC_Handler                 /* SVCall Handler                */
    .long   DebugMon_Handler            /* Debug Monitor Handler         */
    .long   0                           /* Reserved                      */
    .long   PendSV_Handler              /* PendSV Handler                */
    .long   SysTick_Handler             /* SysTick Handler               */

    /* External Interrupts */
    .long     UART0_IRQHandler            //  0:  UART0
    .long     UART1_IRQHandler            //  1:  UART1
    .long     DMA_IRQHandler              //  2:  DMA
    .long     SPIM0_IRQHandler            //  3:  SPIM0
    .long     SPIM1_IRQHandler            //  4:  SPIM1
    .long     SPIS1_IRQHandler            //  5:  SPIS1
    .long     I2C0_IRQHandler             //  6:  I2C0
    .long     I2C1_IRQHandler             //  7:  I2C1
    .long     I2SM_IRQHandler             //  8:  I2SM
    .long     I2SS_IRQHandler             //  9:  I2SS
    .long     RTC_IRQHandler              // 10: RTC
    .long     QDEC_IRQHandler             // 11: QDEC
    .long     TIMER0_IRQHandler           // 12: TIMER0
    .long     TIMER1_IRQHandler           // 13: TIMER1
    .long     TIMER2_IRQHandler           // 14: TIMER2
    .long     TIMER3_IRQHandler           // 15: TIMER3
    .long     TIMER4_IRQHandler           // 16: TIMER4
    .long     TIMER5_IRQHandler           // 17: TIMER5
    .long     TIMER6_IRQHandler           // 18: TIMER6
    .long     TIMER7_IRQHandler           // 19: TIMER7
    .long     GPIO0_IRQHandler            // 20: GPIO0
    .long     GPIO1_IRQHandler            // 21: GPIO1
    .long     GPIO2_IRQHandler            // 22: GPIO2
    .long     GPIO3_IRQHandler            // 23: GPIO3
    .long     GPIO4_IRQHandler            // 24: GPIO4
    .long     GPIO5_IRQHandler            // 25: GPIO5
    .long     GPIO6_IRQHandler            // 26: GPIO6
    .long     GPIO7_IRQHandler            // 27: GPIO7
    .long     GPIO8_IRQHandler            // 28: GPIO8
    .long     GPIO9_IRQHandler            // 29: GPIO9 
    .long     GPIO10_IRQHandler           // 30: GPIO10    
    .long     GPIO11_IRQHandler           // 31: GPIO11 
    .long     GPIO12_IRQHandler           // 32: GPIO12
    .long     GPIO13_IRQHandler           // 33: GPIO13
    .long     GPIO14_IRQHandler           // 34: GPIO14
    .long     GPIO15_IRQHandler           // 35: GPIO15
    .long     GPIO16_IRQHandler           // 36: GPIO16
    .long     GPIO17_IRQHandler           // 37: GPIO17
    .long     GPIO18_IRQHandler           // 38: GPIO18
    .long     GPIO19_IRQHandler           // 39: GPIO19
    .long     GPIO20_IRQHandler           // 40: GPIO20
    .long     GPIO21_IRQHandler           // 41: GPIO21
    .long     GPIO22_IRQHandler           // 42: GPIO22
    .long     GPIO23_IRQHandler           // 43: GPIO23
    .long     GPIO24_IRQHandler           // 44: GPIO24
    .long     GPIO25_IRQHandler           // 45: GPIO25
    .long     GPIO26_IRQHandler           // 46: GPIO26
    .long     GPIO27_IRQHandler           // 47: GPIO27
    .long     GPIO28_IRQHandler           // 48: GPIO28
    .long     GPIO29_IRQHandler           // 49: GPIO29
    .long     GPIO30_IRQHandler           // 50: GPIO30
    .long     GPIO31_IRQHandler           // 51: GPIO31
    .long     rwbt_isr      	          // 52: BT
    .long     rwble_isr      	          // 53: BLE
    .long     rwip_isr  	          // 54: DM
    .long     pcm_isr			  // 55: PCM
    .long     apb2dpv_isr		  // 56: APB2DPV For BT
    .long     bboscen_isr		  // 57: bb osc en
    .long     RF_IRQHandler  		  // 58: RF
    .long     USBSRT_IRQHandler		  // 59: USB SOF Sent Received Toggle
    .long     USBSTO_IRQHandler       	  // 60: USB SOF Toggle Out
    .long     USB_IRQHandler        	  // 61: USB Core
    .long     info_init_get               // Get Flash Info(XIP Mode)


//    .globl   FLASH_FLAG               
//    .long     0x0052554E          // XIP_MODE CFG
    .globl    boot_flag  
boot_flag:             
    .long     0x52554E58          //
    .globl    program_size      
program_size:        
    .long     0x00000000          //
    .globl    ram_addr     
ram_addr:             
    .long     0x00000000          //
    .globl    copy_unit_size      
copy_unit_size:      
    .long     0x00000000          //
    .globl    cpu_clk_type       
cpu_clk_type:       
    .long     64000000                   //
    .globl    qspi_clk_type       
qspi_clk_type:      
    .long     64000000                   //
    .globl    cache_cfg		
cache_cfg:		  
    .long     0x61

//Configuration for QSPI driver                      //
    .globl    clock_divider    
clock_divider:         
    .long     2                   // Fsclk_out = Fssi_clk/SCKDV
    .globl    frame_format_size     
frame_format_size:    
    .long     31                  //
    .globl    ssi_frame_format      
ssi_frame_format:   
    .long     0                   //
    .globl    clock_phase
clock_phase:               
    .long     0                   //
    .globl    clock_polarity    
clock_polarity:        
    .long     0                   //
    .globl    transfer_mode     
transfer_mode:        
    .long     3                   //
    .globl    slave_output_enable		
slave_output_enable:  
    .long     0                   //
    .globl    operation_mode      
operation_mode:      
    .long     0                   //
    .globl    slave_select_toggle_en   
slave_select_toggle_en: 
    .long     0                   //
    .globl    control_farme_size     
control_farme_size:   
    .long     0                   //
    .globl    spi_frame_format   
spi_frame_format:       
    .long     1                   //
    .globl    spi_hyperbus_en       
spi_hyperbus_en:    
    .long     0                   //
    .globl    data_frames_number     
data_frames_number:   
    .long     0                   //
    .globl    slaves_select      
slaves_select:       
    .long     1                   //
    .globl    tx_fifo_threshold_level  
tx_fifo_threshold_level: 
    .long     0                   //
    .globl    tx_fifo_start_fifo_level   
tx_fifo_start_fifo_level:
    .long     0                   //
    .globl    rx_fifo_threshold_level 
rx_fifo_threshold_level:  
    .long     0                   //
    .globl    dma_rx_data_level  
dma_rx_data_level:       
    .long     0                   //
    .globl    dma_tx_data_level      
dma_tx_data_level:   
    .long     0                   //
    .globl    unmask_interrupt     
unmask_interrupt:     
    .long     0                   //

//Configuration for XIP mpde                         //
    .globl    xip_spi_frame_format      
xip_spi_frame_format:
    .long     1                   //
    .globl    transfer_type    
transfer_type:         
    .long     0                   //
    .globl    address_length   
address_length:         
    .long     6                   //
    .globl    instruction_length      
instruction_length:  
    .long     2                   //
    .globl    xip_mode_bit_en       
xip_mode_bit_en:    
    .long     0                   //
    .globl    wait_cycles     
wait_cycles:          
    .long     8                   //
    .globl    xip_dfs_hsize_hburst_en 
xip_dfs_hsize_hburst_en:  
    .long     0                   //
    .globl    xip_spi_ddr_en      
xip_spi_ddr_en:      
    .long     0                   //
    .globl    instruction_ddr_enable    
instruction_ddr_enable:
    .long     0                   //
    .globl    read_data_strobe_enable   
read_data_strobe_enable:
    .long     0                   //
    .globl    xip_instruction_enable    
xip_instruction_enable:
    .long     1                   //
    .globl    xip_continuous_transfer_enable
xip_continuous_transfer_enable:   
    .long     0                //
    .globl    xip_spi_hyerbus_format_enable    
xip_spi_hyerbus_format_enable:
    .long     0                //
    .globl    xip_rxds_signaling_enable   
xip_rxds_signaling_enable:
    .long     0                   //
    .globl    xip_mode_bit_length   
xip_mode_bit_length:    
    .long     0                   //
    .globl    xip_pre_fetch_enable  
xip_pre_fetch_enable:    
    .long     0                   //
    .globl    xip_inst_transfer_opcode   
xip_inst_transfer_opcode:
    .long     0x3b                //
    .globl    xip_wrap_transfer_opcode   
xip_wrap_transfer_opcode:
    .long     0                   //
    .globl    slaves_enbale_mask    
slaves_enbale_mask:    
    .long     1                   //
    .globl    spi_clk_stretch_en       
spi_clk_stretch_en: 
    .long     0                   //
    .globl    spi_data_mask_en      
spi_data_mask_en:    
    .long     0                   //
    .globl    xip_time_out             
xip_time_out: 
    .long     50                  //

    .size    __isr_vector, . - __isr_vector

/* Reset Handler */
    .text
    .thumb
    .thumb_func
    .align 2
    .globl    Reset_Handler
    .type    Reset_Handler, %function
Reset_Handler:
/*     Loop to copy data from read only memory to RAM. The ranges
 *      of copy from/to are specified by following symbols evaluated in
 *      linker script.
 *      __etext: End of code section, i.e., begin of data sections to copy from.
 *      __data_start__/__data_end__: RAM address range that data should be
 *      copied to. Both must be aligned to 4 bytes boundary.  */

    ldr    r1, =__etext
    ldr    r2, =__data_start__
    ldr    r3, =__data_end__

    subs    r3, r2
    ble    .LC1
.LC0:
    subs    r3, #4
    ldr    r0, [r1, r3]
    str    r0, [r2, r3]
    bgt    .LC0
.LC1:

#ifdef __STARTUP_CLEAR_BSS
/*     This part of work usually is done in C library startup code. Otherwise,
 *     define this macro to enable it in this startup.
 *
 *     Loop to zero out BSS section, which uses following symbols
 *     in linker script:
 *      __bss_start__: start of BSS section. Must align to 4
 *      __bss_end__: end of BSS section. Must align to 4
 */
    ldr r1, =__bss_start__
    ldr r2, =__bss_end__

    movs    r0, 0
.LC2:
    cmp     r1, r2
    itt    lt
    strlt   r0, [r1], #4
    blt    .LC2
#endif /* __STARTUP_CLEAR_BSS */

#ifndef __NO_SYSTEM_INIT
    /* bl    SystemInit */
    ldr     r0,=SystemInit
    blx     r0
#endif

    bl    main
    bl    exit


    .pool
    .size Reset_Handler, . - Reset_Handler

/*    Macro to define default handlers. Default handler
 *    will be weak symbol and just dead loops. They can be
 *    overwritten by other handlers */
    .macro    def_default_handler    handler_name
    .align 1
    .thumb_func
    .weak    \handler_name
    .type    \handler_name, %function
\handler_name :
    b    .
    .size    \handler_name, . - \handler_name
    .endm

/* System Exception Handlers */

    def_default_handler    NMI_Handler
    def_default_handler    HardFault_Handler
    def_default_handler    MemManage_Handler
    def_default_handler    BusFault_Handler
    def_default_handler    UsageFault_Handler
    def_default_handler    SVC_Handler
    def_default_handler    DebugMon_Handler
    def_default_handler    PendSV_Handler
    def_default_handler    SysTick_Handler

/* IRQ Handlers */

    def_default_handler     UART0_IRQHandler 
    def_default_handler     UART1_IRQHandler        
    def_default_handler     DMA_IRQHandler          
    def_default_handler     SPIM0_IRQHandler        
    def_default_handler     SPIM1_IRQHandler        
    def_default_handler     SPIS1_IRQHandler        
    def_default_handler     I2C0_IRQHandler         
    def_default_handler     I2C1_IRQHandler         
    def_default_handler     I2SM_IRQHandler         
    def_default_handler     I2SS_IRQHandler         
    def_default_handler     RTC_IRQHandler          
    def_default_handler     QDEC_IRQHandler         
    def_default_handler     TIMER0_IRQHandler       
    def_default_handler     TIMER1_IRQHandler       
    def_default_handler     TIMER2_IRQHandler       
    def_default_handler     TIMER3_IRQHandler       
    def_default_handler     TIMER4_IRQHandler       
    def_default_handler     TIMER5_IRQHandler       
    def_default_handler     TIMER6_IRQHandler       
    def_default_handler     TIMER7_IRQHandler       
    def_default_handler     GPIO0_IRQHandler        
    def_default_handler     GPIO1_IRQHandler        
    def_default_handler     GPIO2_IRQHandler        
    def_default_handler     GPIO3_IRQHandler        
    def_default_handler     GPIO4_IRQHandler        
    def_default_handler     GPIO5_IRQHandler        
    def_default_handler     GPIO6_IRQHandler        
    def_default_handler     GPIO7_IRQHandler        
    def_default_handler     GPIO8_IRQHandler        
    def_default_handler     GPIO9_IRQHandler        
    def_default_handler     GPIO10_IRQHandler        
    def_default_handler     GPIO11_IRQHandler       
    def_default_handler     GPIO12_IRQHandler       
    def_default_handler     GPIO13_IRQHandler       
    def_default_handler     GPIO14_IRQHandler       
    def_default_handler     GPIO15_IRQHandler       
    def_default_handler     GPIO16_IRQHandler       
    def_default_handler     GPIO17_IRQHandler       
    def_default_handler     GPIO18_IRQHandler       
    def_default_handler     GPIO19_IRQHandler       
    def_default_handler     GPIO20_IRQHandler       
    def_default_handler     GPIO21_IRQHandler       
    def_default_handler     GPIO22_IRQHandler       
    def_default_handler     GPIO23_IRQHandler       
    def_default_handler     GPIO24_IRQHandler       
    def_default_handler     GPIO25_IRQHandler       
    def_default_handler     GPIO26_IRQHandler       
    def_default_handler     GPIO27_IRQHandler       
    def_default_handler     GPIO28_IRQHandler       
    def_default_handler     GPIO29_IRQHandler       
    def_default_handler     GPIO30_IRQHandler       
    def_default_handler     GPIO31_IRQHandler       
    def_default_handler     rwbt_isr   			   
    def_default_handler     rwble_isr   			   
    def_default_handler     rwip_isr				   
    def_default_handler     pcm_isr				   
    def_default_handler     apb2dpv_isr			   
    def_default_handler     bboscen_isr			   
    def_default_handler     RF_IRQHandler           
    def_default_handler     USBSRT_IRQHandler       
    def_default_handler     USBSTO_IRQHandler	   
    def_default_handler     USB_IRQHandler          
    def_default_handler     info_init_get           
    /*
    def_default_handler    Default_Handler
    .weak    DEF_IRQHandler
    .set    DEF_IRQHandler, Default_Handler
    */
    .end

