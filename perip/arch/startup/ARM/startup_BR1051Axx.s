;/**************************************************************************//**
; * @file     startup_ARMCM3.s
; * @brief    CMSIS Core Device Startup File for
; *           ARMCM3 Device Series
; * @version  V1.08
; * @date     23. November 2012
; *
; * @note
; *
; ******************************************************************************/
;/* Copyright (c) 2011 - 2012 ARM LIMITED
;
;   All rights reserved.
;   Redistribution and use in source and binary forms, with or without
;   modification, are permitted provided that the following conditions are met:
;   - Redistributions of source code must retain the above copyright
;     notice, this list of conditions and the following disclaimer.
;   - Redistributions in binary form must reproduce the above copyright
;     notice, this list of conditions and the following disclaimer in the
;     documentation and/or other materials provided with the distribution.
;   - Neither the name of ARM nor the names of its contributors may be used
;     to endorse or promote products derived from this software without
;     specific prior written permission.
;   *
;   THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
;   AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
;   IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
;   ARE DISCLAIMED. IN NO EVENT SHALL COPYRIGHT HOLDERS AND CONTRIBUTORS BE
;   LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
;   CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
;   SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
;   INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
;   CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
;   ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
;   POSSIBILITY OF SUCH DAMAGE.
;   ---------------------------------------------------------------------------*/
;/*
;//-------- <<< Use Configuration Wizard in Context Menu >>> ------------------
;*/


; <h> Stack Configuration
;   <o> Stack Size (in Bytes) <0x0-0xFFFFFFFF:8>
; </h>

Stack_Size      EQU     0x00000400

                AREA    STACK, NOINIT, READWRITE, ALIGN=3
Stack_Mem       SPACE   Stack_Size
__initial_sp


; <h> Heap Configuration
;   <o>  Heap Size (in Bytes) <0x0-0xFFFFFFFF:8>
; </h>

Heap_Size       EQU     0x00000C00

                AREA    HEAP, NOINIT, READWRITE, ALIGN=3
__heap_base
Heap_Mem        SPACE   Heap_Size
__heap_limit


                PRESERVE8
                THUMB


; Vector Table Mapped to Address 0 at Reset

                AREA    RESET, DATA, READONLY
                EXPORT  __Vectors
                EXPORT  __Vectors_End
                EXPORT  __Vectors_Size

__Vectors       DCD     __initial_sp              ; Top of Stack
                DCD     Reset_Handler             ; Reset Handler
                DCD     NMI_Handler               ; NMI Handler
                DCD     HardFault_Handler         ; Hard Fault Handler
                DCD     MemManage_Handler         ; MPU Fault Handler
                DCD     BusFault_Handler          ; Bus Fault Handler
                DCD     UsageFault_Handler        ; Usage Fault Handler
                DCD     0                         ; Reserved
                DCD     0                         ; Reserved
                DCD     0                         ; Reserved
                DCD     0                         ; Reserved
                DCD     SVC_Handler               ; SVCall Handler
                DCD     DebugMon_Handler          ; Debug Monitor Handler
                DCD     0                         ; Reserved
                DCD     PendSV_Handler            ; PendSV Handler
                DCD     SysTick_Handler           ; SysTick Handler

                ; External Interrupts
                DCD     UART0_IRQHandler            ;  0:  UART0
                DCD     UART1_IRQHandler            ;  1:  UART1
                DCD     DMA_IRQHandler              ;  2:  DMA
                DCD     SPIM0_IRQHandler            ;  3:  SPIM0
                DCD     SPIM1_IRQHandler            ;  4:  SPIM1
                DCD     SPIS1_IRQHandler            ;  5:  SPIS1
                DCD     I2C0_IRQHandler             ;  6:  I2C0
                DCD     I2C1_IRQHandler             ;  7:  I2C1
                DCD     I2SM_IRQHandler             ;  8:  I2SM
                DCD     I2SS_IRQHandler             ;  9:  I2SS
                DCD     RTC_IRQHandler              ; 10: RTC
                DCD     QDEC_IRQHandler              ; 11: WDT
                DCD     TIMER0_IRQHandler           ; 12: TIMER0
                DCD     TIMER1_IRQHandler           ; 13: TIMER1
                DCD     TIMER2_IRQHandler           ; 14: TIMER2
                DCD     TIMER3_IRQHandler           ; 15: TIMER3
                DCD     TIMER4_IRQHandler           ; 16: TIMER4
                DCD     TIMER5_IRQHandler           ; 17: TIMER5
                DCD     TIMER6_IRQHandler           ; 18: TIMER6
                DCD     TIMER7_IRQHandler           ; 19: TIMER7
                DCD     GPIO0_IRQHandler            ; 20: GPIO0
                DCD     GPIO1_IRQHandler            ; 21: GPIO1
                DCD     GPIO2_IRQHandler            ; 22: GPIO2
                DCD     GPIO3_IRQHandler            ; 23: GPIO3
                DCD     GPIO4_IRQHandler            ; 24: GPIO4
                DCD     GPIO5_IRQHandler            ; 25: GPIO5
                DCD     GPIO6_IRQHandler            ; 26: GPIO6
                DCD     GPIO7_IRQHandler            ; 27: GPIO7
                DCD     GPIO8_IRQHandler            ; 28: GPIO8
                DCD     GPIO9_IRQHandler            ; 29: GPIO9 
                DCD     GPIO10_IRQHandler           ; 30: GPIO10    
                DCD     GPIO11_IRQHandler           ; 31: GPIO11 
                DCD     GPIO12_IRQHandler           ; 32: GPIO12
                DCD     GPIO13_IRQHandler           ; 33: GPIO13
                DCD     GPIO14_IRQHandler           ; 34: GPIO14
                DCD     GPIO15_IRQHandler           ; 35: GPIO15
                DCD     GPIO16_IRQHandler           ; 36: GPIO16
                DCD     GPIO17_IRQHandler           ; 37: GPIO17
                DCD     GPIO18_IRQHandler           ; 38: GPIO18
				DCD     GPIO19_IRQHandler           ; 39: GPIO19
                DCD     GPIO20_IRQHandler           ; 40: GPIO20
				DCD     GPIO21_IRQHandler           ; 41: GPIO21
				DCD     GPIO22_IRQHandler           ; 42: GPIO22
				DCD     GPIO23_IRQHandler           ; 43: GPIO23
				DCD     GPIO24_IRQHandler           ; 44: GPIO24
				DCD     GPIO25_IRQHandler           ; 45: GPIO25
				DCD     GPIO26_IRQHandler           ; 46: GPIO26
				DCD     GPIO27_IRQHandler           ; 47: GPIO27
				DCD     GPIO28_IRQHandler           ; 48: GPIO28
				DCD     GPIO29_IRQHandler           ; 49: GPIO29
				DCD     GPIO30_IRQHandler           ; 50: GPIO30
				DCD     GPIO31_IRQHandler           ; 51: GPIO31
__Vectors_End

__Vectors_Size  EQU     __Vectors_End - __Vectors

				AREA    |.text|, CODE, READONLY


; Reset Handler

Reset_Handler   PROC
                EXPORT  Reset_Handler             [WEAK]
                IMPORT  SystemInit
                IMPORT  __main
                LDR     R0, =SystemInit
                BLX     R0
                LDR     R0, =__main
                BX      R0
                ENDP


; Dummy Exception Handlers (infinite loops which can be modified)

NMI_Handler     PROC
                EXPORT  NMI_Handler               [WEAK]
                B       .
                ENDP
HardFault_Handler\
                PROC
                EXPORT  HardFault_Handler         [WEAK]
                B       .
                ENDP
MemManage_Handler\
                PROC
                EXPORT  MemManage_Handler         [WEAK]
                B       .
                ENDP
BusFault_Handler\
                PROC
                EXPORT  BusFault_Handler          [WEAK]
                B       .
                ENDP
UsageFault_Handler\
                PROC
                EXPORT  UsageFault_Handler        [WEAK]
                B       .
                ENDP
SVC_Handler     PROC
                EXPORT  SVC_Handler               [WEAK]
                B       .
                ENDP
DebugMon_Handler\
                PROC
                EXPORT  DebugMon_Handler          [WEAK]
                B       .
                ENDP
PendSV_Handler\
                PROC
                EXPORT  PendSV_Handler            [WEAK]
                B       .
                ENDP
SysTick_Handler\
                PROC
                EXPORT  SysTick_Handler           [WEAK]
                B       .
                ENDP

Default_Handler PROC
					
                EXPORT     UART0_IRQHandler       [WEAK]
                EXPORT     UART1_IRQHandler       [WEAK]
                EXPORT     DMA_IRQHandler         [WEAK]
                EXPORT     SPIM0_IRQHandler       [WEAK]
                EXPORT     SPIM1_IRQHandler       [WEAK]
                EXPORT     SPIS1_IRQHandler       [WEAK]
                EXPORT     I2C0_IRQHandler        [WEAK]
                EXPORT     I2C1_IRQHandler        [WEAK]
                EXPORT     I2SM_IRQHandler        [WEAK]
                EXPORT     I2SS_IRQHandler        [WEAK]
                EXPORT     RTC_IRQHandler         [WEAK]
                EXPORT     QDEC_IRQHandler        [WEAK]
                EXPORT     TIMER0_IRQHandler      [WEAK]
                EXPORT     TIMER1_IRQHandler      [WEAK]
                EXPORT     TIMER2_IRQHandler      [WEAK]
                EXPORT     TIMER3_IRQHandler      [WEAK]
                EXPORT     TIMER4_IRQHandler      [WEAK]
                EXPORT     TIMER5_IRQHandler      [WEAK]
                EXPORT     TIMER6_IRQHandler      [WEAK]
                EXPORT     TIMER7_IRQHandler      [WEAK]
                EXPORT     GPIO0_IRQHandler       [WEAK]
                EXPORT     GPIO1_IRQHandler       [WEAK]
                EXPORT     GPIO2_IRQHandler       [WEAK]
                EXPORT     GPIO3_IRQHandler       [WEAK]
                EXPORT     GPIO4_IRQHandler       [WEAK]
                EXPORT     GPIO5_IRQHandler       [WEAK]
                EXPORT     GPIO6_IRQHandler       [WEAK]
                EXPORT     GPIO7_IRQHandler       [WEAK]
                EXPORT     GPIO8_IRQHandler       [WEAK]
                EXPORT     GPIO9_IRQHandler       [WEAK]
                EXPORT     GPIO10_IRQHandler      [WEAK] 
                EXPORT     GPIO11_IRQHandler      [WEAK]
                EXPORT     GPIO12_IRQHandler      [WEAK]
                EXPORT     GPIO13_IRQHandler      [WEAK]
                EXPORT     GPIO14_IRQHandler      [WEAK]
                EXPORT     GPIO15_IRQHandler      [WEAK]
                EXPORT     GPIO16_IRQHandler      [WEAK]
                EXPORT     GPIO17_IRQHandler      [WEAK]
                EXPORT     GPIO18_IRQHandler      [WEAK]
				EXPORT     GPIO19_IRQHandler      [WEAK]
                EXPORT     GPIO20_IRQHandler      [WEAK]
				EXPORT     GPIO21_IRQHandler      [WEAK]
				EXPORT     GPIO22_IRQHandler      [WEAK]
				EXPORT     GPIO23_IRQHandler      [WEAK]
				EXPORT     GPIO24_IRQHandler      [WEAK]
				EXPORT     GPIO25_IRQHandler      [WEAK]
				EXPORT     GPIO26_IRQHandler      [WEAK]
				EXPORT     GPIO27_IRQHandler      [WEAK]
				EXPORT     GPIO28_IRQHandler      [WEAK]
				EXPORT     GPIO29_IRQHandler      [WEAK]
				EXPORT     GPIO30_IRQHandler      [WEAK]
				EXPORT     GPIO31_IRQHandler      [WEAK]
					
UART0_IRQHandler  
UART1_IRQHandler  
DMA_IRQHandler    
SPIM0_IRQHandler  
SPIM1_IRQHandler  
SPIS1_IRQHandler  
I2C0_IRQHandler   
I2C1_IRQHandler   
I2SM_IRQHandler   
I2SS_IRQHandler   
RTC_IRQHandler    
QDEC_IRQHandler    
TIMER0_IRQHandler 
TIMER1_IRQHandler 
TIMER2_IRQHandler 
TIMER3_IRQHandler 
TIMER4_IRQHandler 
TIMER5_IRQHandler 
TIMER6_IRQHandler 
TIMER7_IRQHandler 
GPIO0_IRQHandler  
GPIO1_IRQHandler  
GPIO2_IRQHandler  
GPIO3_IRQHandler  
GPIO4_IRQHandler  
GPIO5_IRQHandler  
GPIO6_IRQHandler  
GPIO7_IRQHandler  
GPIO8_IRQHandler  
GPIO9_IRQHandler  
GPIO10_IRQHandler  
GPIO11_IRQHandler 
GPIO12_IRQHandler 
GPIO13_IRQHandler 
GPIO14_IRQHandler 
GPIO15_IRQHandler 
GPIO16_IRQHandler 
GPIO17_IRQHandler 
GPIO18_IRQHandler 
GPIO19_IRQHandler 
GPIO20_IRQHandler 
GPIO21_IRQHandler
GPIO22_IRQHandler
GPIO23_IRQHandler
GPIO24_IRQHandler
GPIO25_IRQHandler
GPIO26_IRQHandler
GPIO27_IRQHandler
GPIO28_IRQHandler
GPIO29_IRQHandler
GPIO30_IRQHandler
GPIO31_IRQHandler

                B       .

                ENDP


                ALIGN


; User Initial Stack & Heap

                IF      :DEF:__MICROLIB

                EXPORT  __initial_sp
                EXPORT  __heap_base
                EXPORT  __heap_limit

                ELSE

                IMPORT  __use_two_region_memory
                EXPORT  __user_initial_stackheap

__user_initial_stackheap PROC
                LDR     R0, =  Heap_Mem
                LDR     R1, =(Stack_Mem + Stack_Size)
                LDR     R2, = (Heap_Mem +  Heap_Size)
                LDR     R3, = Stack_Mem
                BX      LR
                ENDP

                ALIGN

                ENDIF


                END
