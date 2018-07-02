/*===========================================================================
     _____        _____        _____        _____
 ___|    _|__  __|_    |__  __|__   |__  __| __  |__  ______
|    \  /  | ||    \      ||     |     ||  |/ /     ||___   |
|     \/   | ||     \     ||     \     ||     \     ||___   |
|__/\__/|__|_||__|\__\  __||__|\__\  __||__|\__\  __||______|
    |_____|      |_____|      |_____|      |_____|

--[Mark3 Realtime Platform]--------------------------------------------------

Copyright (c) 2018 Funkenstein Software Consulting, all rights reserved.
See license.txt for more information
===========================================================================*/
/*!
    @file   startup.c
    @brief  ARM Cortex m3 startup code.

    @note derived from https://github.com/arunkuttiyara/cortex_m3_development
 */

#include <stdint.h>
#include <stddef.h>

void ResetISR(void);
static void NmiSR(void);
static void FaultISR(void);
static void IntDefaultHandler(void);

static uint32_t stack[2048];

extern int main(void);

extern void SVC_Handler(void);
extern void PendSV_Handler(void);
extern void SysTick_Handler(void);

//*****************************************************************************
//
// The vector table.  Note that the proper constructs must be placed on this to
// ensure that it ends up at physical address 0x0000.0000.
//
//*****************************************************************************
__attribute__ ((section(".isr_vector")))
void (* const g_pfnVectors[])(void) =
{
    (void (*)(void))((unsigned long)stack + sizeof(stack)),
                                            // The initial stack pointer
    ResetISR,                               // The reset handler
    NmiSR,                                  // The NMI handler
    FaultISR,                               // The hard fault handler
    IntDefaultHandler,                      // The MPU fault handler
    IntDefaultHandler,                      // The bus fault handler
    IntDefaultHandler,                      // The usage fault handler
    0,                                      // Reserved
    0,                                      // Reserved
    0,                                      // Reserved
    0,                                      // Reserved
    SVC_Handler,                            // SVCall handler
    IntDefaultHandler,                      // Debug monitor handler
    0,                                      // Reserved
    PendSV_Handler,                    	    // The PendSV handler
    SysTick_Handler                         // The SysTick handler
};

//*****************************************************************************
//
// The following are constructs created by the linker, indicating where the
// the "data" and "bss" segments reside in memory.  The initializers for the
// "data" segment resides immediately following the "text" segment.
//
//*****************************************************************************
extern unsigned long _etext;
extern unsigned long _data;
extern unsigned long _edata;
extern unsigned long _bss;
extern unsigned long _ebss;

#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>

extern void (*__preinit_array_start []) (void) __attribute__((weak));
extern void (*__preinit_array_end []) (void) __attribute__((weak));
extern void (*__init_array_start []) (void) __attribute__((weak));
extern void (*__init_array_end []) (void) __attribute__((weak));
extern void (*__fini_array_start []) (void) __attribute__((weak));
extern void (*__fini_array_end []) (void) __attribute__((weak));

void _init();
void _fini();
void _exit(int return_code) __attribute__((noreturn));

int __cxa_atexit(void (*func) (void *), void * arg, void * dso_handle){
    return 0;
}

void __cxa_pure_virtual(void) __attribute__((weak));
void __cxa_pure_virtual(void)
{
}

static void __libc_init_array() {
 int count, i;

 count = __preinit_array_end - __preinit_array_start;
 for (i = 0; i < count; i++)
     __preinit_array_start[i]();

 _init();

 count = __init_array_end - __init_array_start;
 for (i = 0; i < count; i++)
     __init_array_start[i]();
}

void libc_init() {
    __libc_init_array();
}

//*****************************************************************************
//
// This is the code that gets called when the processor first starts execution
// following a reset event.  Only the absolutely necessary set is performed,
// after which the application supplied entry() routine is called.
//
//*****************************************************************************
void ResetISR(void)
{
    unsigned long *pulSrc, *pulDest;

    //
    // Copy the data segment initializers from flash to SRAM.
    //
    pulSrc = &_etext;
    pulDest = &_data;

    while(pulDest < &_edata )
    {
        *pulDest++ = *pulSrc++;
    }

    //
    // Zero fill the bss segment.
    //
    __asm("    ldr     r0, =_bss\n"
          "    ldr     r1, =_ebss\n"
          "    mov     r2, #0\n"
          "    .thumb_func\n"
          "zero_loop:\n"
          "        cmp     r0, r1\n"
          "        it      lt\n"
          "        strlt   r2, [r0], #4\n"
          "        blt     zero_loop");


    __libc_init_array();

    //
    // Call the application's entry point.
    //
    main();
}

//*****************************************************************************
//
// This is the code that gets called when the processor receives a NMI.  This
// simply enters an infinite loop, preserving the system state for examination
// by a debugger.
//
//*****************************************************************************
static void NmiSR(void)
{
    //
    // Enter an infinite loop.
    //
    while(1) {
        ;
    }
}

//*****************************************************************************
//
// This is the code that gets called when the processor receives a fault
// interrupt.  This simply enters an infinite loop, preserving the system state
// for examination by a debugger.
//
//*****************************************************************************
static void FaultISR(void)
{
    //
    // Enter an infinite loop.
    //
    while(1) {
        ;
    }
}

//*****************************************************************************
//
// This is the code that gets called when the processor receives an unexpected
// interrupt.  This simply enters an infinite loop, preserving the system state
// for examination by a debugger.
//
//*****************************************************************************
static void IntDefaultHandler(void)
{
    //
    // Go into an infinite loop.
    //
    while(1) {
        ;
    }
}
