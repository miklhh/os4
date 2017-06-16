/*
 * Part of OS4, sys_2_sleep.c
 * Author: Mikael Henriksson
 */

#include <kernel/ksleep.h>

// ---- Syscall 2 - sleep.
// Takes the amount of milliseconds to sleep in the EBX register.
uint32_t sys_2_sleep()
{
    uint32_t time_ms = 0;
    asm volatile(
        "movl %%ebx, %0"
        : "=r"(time_ms)     // Output.
        :                   // Input.
        :);                 // Clobbered registers.

    ksleep(time_ms);
    return 0;
}
