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
    .equ    Stack_Size, 0x200
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
    .equ    Heap_Size, 0
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
    .long   UART0_Handler               /* 16+ 0: UART 0 RX and TX Handler   */
    .long   UART1_Handler               /* 16+ 1: Not Used                   */
    .long   DMA_Handler                 /* 16+ 2: */
    .long   SPIM0_Handler               /* 16+ 3: */
    .long   SPIM1_Handler               /* 16+ 4: */
    .long   SPIS1_Handler               /* 16+ 5: */
    .long   I2C0_Handler                /* 16+ 6: */
    .long   I2C1_Handler                /* 16+ 7: */
    .long   I2SM_Handler                /* 16+ 8:  */
    .long   I2SS_Handler                /* 16+ 9: */
    .long   RTC_Handler                 /* 16+10: */
    .long   QDEC_Handler                /* 16+11: */
    .long   TIMER0_Handler              /* 16+12: */
    .long   TIMER1_Handler              /* 16+13: */
    .long   TIMER2_Handler              /* 16+14: */
    .long   TIMER3_Handler              /* 16+15: */
    .long   TIMER4_Handler              /* 16+16: */
    .long   TIMER5_Handler              /* 16+17: */
    .long   TIMER6_Handler              /* 16+18: */
    .long   TIMER7_Handler              /* 16+19: */
    .long   GPIO0_Handler               /* 16+20: */
    .long   GPIO1_Handler               /* 16+21: */
    .long   GPIO2_Handler               /* 16+22: */
    .long   GPIO3_Handler               /* 16+23: */
    .long   GPIO4_Handler               /* 16+24: */
    .long   GPIO5_Handler               /* 16+25: */
    .long   GPIO6_Handler               /* 16+26: */
    .long   GPIO7_Handler               /* 16+27: */
    .long   GPIO8_Handler               /* 16+28: */
    .long   GPIO9_Handler               /* 16+29: */
    .long   GPIO10_Handler              /* 16+30: */
    .long   GPIO11_Handler              /* 16+31: */
    .long   GPIO12_Handler              /* 16+32: */
    .long   GPIO13_Handler              /* 16+33: */
    .long   GPIO14_Handler              /* 16+34: */
    .long   GPIO15_Handler              /* 16+35: */
    .long   GPIO16_Handler              /* 16+36: */ 
    .long   GPIO17_Handler              /* 16+37: */ 
    .long   GPIO18_Handler              /* 16+38: */ 
    .long   GPIO19_Handler              /* 16+39: */ 
    .long   GPIO20_Handler              /* 16+40: */ 
    .long   GPIO21_Handler              /* 16+41: */ 
    .long   GPIO22_Handler              /* 16+42: */ 
    .long   GPIO23_Handler              /* 16+43: */ 
    .long   GPIO24_Handler              /* 16+44: */ 
    .long   GPIO25_Handler              /* 16+45: */ 
    .long   GPIO26_Handler              /* 16+46: */ 
    .long   GPIO27_Handler              /* 16+47: */ 
    .long   GPIO28_Handler              /* 16+48: */ 
    .long   GPIO29_Handler              /* 16+49: */ 
    .long   GPIO30_Handler              /* 16+50: */ 
    .long   GPIO31_Handler              /* 16+51: */ 
    .long   BLE_HSLOT_Handler           /* 16+51: */ 
    .long   BLE_RX_Handler              /* 16+51: */ 
    .long   BLE_TX_Handler              /* 16+51: */ 
    .long   BLE_SLP_Handler             /* 16+51: */ 
    .long   BLE_SKIP_Handler            /* 16+51: */ 
    .long   BLE_END_Handler             /* 16+51: */ 
    .long   BLE_START_Handler           /* 16+51: */ 
    .long   BLE_CRYPT_Handler           /* 16+51: */ 
    .long   BLE_ERROR_Handler           /* 16+51: */ 
    .long   BLE_TIMESTAMP_TGT_Handler   /* 16+51: */ 
    .long   BLE_GROSSTGTIM_Handler      /* 16+51: */ 
    .long   BLE_FINETGTIM_Handler       /* 16+51: */ 
    .long   BLE_SW_Handler              /* 16+51: */ 
    .long   SYSERROR_Handler            /* System Error Handler */
    .long   EFLASH_Handler              /* Embedded Flash Handler */
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

    def_default_handler    UART0_Handler
    def_default_handler    UART1_Handler
    def_default_handler    DMA_Handler
    def_default_handler    SPIM0_Handler
    def_default_handler    SPIM1_Handler
    def_default_handler    SPIS1_Handler
    def_default_handler    I2C0_Handler
    def_default_handler    I2C1_Handler
    def_default_handler    I2SM_Handler
    def_default_handler    I2SS_Handler
    def_default_handler    RTC_Handler
    def_default_handler    QDEC_Handler
    def_default_handler    TIMER0_Handler
    def_default_handler    TIMER1_Handler
    def_default_handler    TIMER2_Handler
    def_default_handler    TIMER3_Handler
    def_default_handler    TIMER4_Handler
    def_default_handler    TIMER5_Handler
    def_default_handler    TIMER6_Handler
    def_default_handler    TIMER7_Handler
    def_default_handler    GPIO0_Handler
    def_default_handler    GPIO1_Handler
    def_default_handler    GPIO2_Handler
    def_default_handler    GPIO3_Handler
    def_default_handler    GPIO4_Handler
    def_default_handler    GPIO5_Handler
    def_default_handler    GPIO6_Handler
    def_default_handler    GPIO7_Handler
    def_default_handler    GPIO8_Handler
    def_default_handler    GPIO9_Handler
    def_default_handler    GPIO10_Handler
    def_default_handler    GPIO11_Handler
    def_default_handler    GPIO12_Handler
    def_default_handler    GPIO13_Handler
    def_default_handler    GPIO14_Handler
    def_default_handler    GPIO15_Handler
    def_default_handler    GPIO16_Handler
    def_default_handler    GPIO17_Handler
    def_default_handler    GPIO18_Handler
    def_default_handler    GPIO19_Handler
    def_default_handler    GPIO20_Handler
    def_default_handler    GPIO21_Handler
    def_default_handler    GPIO22_Handler
    def_default_handler    GPIO23_Handler
    def_default_handler    GPIO24_Handler
    def_default_handler    GPIO25_Handler
    def_default_handler    GPIO26_Handler
    def_default_handler    GPIO27_Handler
    def_default_handler    GPIO28_Handler
    def_default_handler    GPIO29_Handler
    def_default_handler    GPIO30_Handler
    def_default_handler    GPIO31_Handler
    def_default_handler    BLE_HSLOT_Handler
    def_default_handler    BLE_RX_Handler  
    def_default_handler    BLE_TX_Handler 
    def_default_handler    BLE_SLP_Handler
    def_default_handler    BLE_SKIP_Handler
    def_default_handler    BLE_END_Handler 
    def_default_handler    BLE_START_Handler
    def_default_handler    BLE_CRYPT_Handler
    def_default_handler    BLE_ERROR_Handler
    def_default_handler    BLE_TIMESTAMP_TGT_Handler
    def_default_handler    BLE_GROSSTGTIM_Handler  
    def_default_handler    BLE_FINETGTIM_Handler  
    def_default_handler    BLE_SW_Handler        
    def_default_handler    PORT0_COMB_Handler
    def_default_handler    PORT1_COMB_Handler
    def_default_handler    Spare11_Handler
    def_default_handler    UARTOVF_Handler
    def_default_handler    Spare13_Handler
    def_default_handler    Spare14_Handler
    def_default_handler    Spare15_Handler
    def_default_handler    TSC_Handler
    def_default_handler    SYSERROR_Handler          /* System Error Handler */
    def_default_handler    EFLASH_Handler            /* Embedded Flash Handler */

    /*
    def_default_handler    Default_Handler
    .weak    DEF_IRQHandler
    .set    DEF_IRQHandler, Default_Handler
    */
    .end

