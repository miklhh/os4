/*
 * Part of OS4, cpuid.h
 * Author: Mikael Henriksson, miklhh
 */

#ifndef SYSTEM_CPUID_H
#define SYSTEM_CPUID_H

#include <stdint.h>
#include <kstdio.h>

/* Macro for using the cpuid instruction. */
#define __cpuid(level, a, b, c, d)                              \
    asm volatile (  "cpuid \n"                                  \
                    : "=a" (a), "=b" (b), "=c" (c), "=d" (d)    \
                    : "0" (level))

/* Function returns a number bigger than zero if the cpuid instruction can be
 * called. Otherwise returns zero */
extern uint32_t test_cpuid();


/* Function for printing cpu vendor label. */
static inline void print_vendor_label_kstdio()
{
    uint32_t eax, ebx, ecx, edx;
    __cpuid(0, eax, ebx, ecx, edx);
    for (uint8_t i = 0; i < 4; i++)
    {
        kprintf("%c", (char) (ebx >> (i * 8) & 0x000000FF));
    }
    for (uint8_t i = 0; i < 4; i++)
    {
        kprintf("%c", (char) (edx >> (i * 8)));
    }
    for (uint8_t i = 0; i < 4; i++)
    {
        kprintf("%c", (char) (ecx >> (i * 8)));
    }
}



#endif
