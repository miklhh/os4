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

/* The syscall entries */
extern uint32_t sys_0_default_syscall();


/* Function wrapper for the systemcall. */
extern void syscall_wrapper();

/* Vector with the syscall entries. */
static uint32_t (*syscall_entries[256])(void);

/* Function for setting up the syscall interface. */
void syscall_init()
{
    /* Setup the interrupt to be used for the syscalls. */
    set_int(
        0x80, 
        (uint32_t) &syscall_wrapper,
        SYSCALL_INTERRUPT_FLAGS);

    syscall_entries[0] = sys_0_default_syscall;

}


void syscall()
{
    /* Aquire the syscall. */
    uint32_t call = 0;
    asm volatile(
            "movl %%eax, %0"
            : "=r" (call)           // Output
            :                       // Input
            :               );      // Clobbered registers.
    
    /* Preform the syscall */
    uint32_t result = (*syscall_entries[call])();

    /* Return the value. */
    asm volatile(
            "movl %0, %%eax"
            :                       // Output
            : "r"(result)           // Input
            :               );      // Clobbered registers.

    /* Clarification:
     * In the last inline assembly section we do not tell the C compiler that
     * we have changed the value of eax, because the return value is passed
     * via that register. Thats why we say 'no clobbered registers' even though
     * EAX has been changes.
    */
}
