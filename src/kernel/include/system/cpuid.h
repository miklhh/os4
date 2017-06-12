/*
 * Part of OS4, cpuid.h
 * Author: Mikael Henriksson, miklhh
 */

#ifndef SYSTEM_CPUID_H
#define SYSTEM_CPUID_H

#include <stdint.h>
#include <stdio.h>

/* Macro for using the cpuid instruction. */
#define __cpuid(level, a, b, c, d)                                \
    asm volatile (  "cpuid\n"                                    \
                    : "=a" (a), "=b" (b), "=c" (c), "=d" (d)    \
                    : "0" (level))

/* Function returns a number bigger than zero if the cpuid instruction can be
 * called. Otherwise returns zero */
extern uint32_t test_cpuid();

static inline void print_vendor_label()
{
    uint32_t eax, ebx, ecx, edx;
    __cpuid(0, eax, ebx, ecx, edx);
    for (uint8_t i = 0; i < 4; i++)
    {
        printf("%c", (char) (ebx >> (i * 4) & 0x000000FF));
    }
    for (uint8_t i = 0; i < 4; i++)
    {
        printf("%c", (char) (edx >> (i * 4)));
    }
    for (uint8_t i = 0; i < 4; i++)
    {
        printf("%c", (char) (ecx >> (i * 4)));
    }
}



#endif
