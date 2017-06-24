/*
 * Part of OS4, registers_h.h
 * Author: Mikael Henriksson, miklhh
 */

#ifndef _I686_REGISTERS_H
#define _I686_REGISTERS_H

#include <stdint.h>

typedef struct registers {
    uint16_t cs, ds, es, fs, ss;        // Segment registers.
    uint32_t edi, esi, ebp, esp, eip;   // Index/pointer registers.
    uint32_t eax, ebx, ecx, edx;        // General purpose registers
    uint32_t eflags;                    // Processor state register.
} registers_t;

/* Function prototypes. */
void registers_copy(registers_t* dst, registers_t* src);

#endif
