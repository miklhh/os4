/*
 * Part of OS4, syscall.c
 * Author: Mikael Henriksson, miklh
 */

#include <kernel/idt.h>
#include <stdio.h>
#include <stdint.h>


/* Syscall interrupt flags macro. */
#define SYSCALL_INTERRUPT_FLAGS     (IDT_32BIT_INTERRUPT_GATE |  \
                                     IDT_PRESENT              |  \
                                     IDT_DPL_3)


/* Function wrapper for the systemcall. */
extern void syscall_wrapper();


/* Function for setting up the syscall interface. */
void syscall_init()
{
    /* Setup the interrupt to be used for the syscalls. */
    set_int(
        0x80, 
        (uint32_t) &syscall_wrapper,
        SYSCALL_INTERRUPT_FLAGS);
}


void syscall()
{
    uint32_t call = 0;
    asm volatile(
            "movl %%eax, %0"
            : "=r" (call));

    printf("SYSCALL PREFORMED: %u\n", call);
    asm("cli");
}
