/*
 * Part of OS4, registers_h.h
 * Author: Mikael Henriksson, miklhh
 */

#ifndef _I686_REGISTERS_H
#define _I686_REGISTERS_H

#include <stdint.h>


/* Structure for storing registers. Packed so that it can be used as a pointer
 * to a stack by the task switching routines. */
#ifdef COMMENT_OUT
typedef struct registers {
    uint16_t cs, ds, es, fs, gs, ss;        // Segment registers.
    uint32_t edi, esi, ebp, esp, eip;       // Index/pointer registers.
    uint32_t eax, ebx, ecx, edx;            // General purpose registers
    uint32_t eflags;                        // Processor state register.
} __attribute__((packed)) registers_t;
#endif

/* Structure layout made to fit task switch routine with pusha and pushf
 * instruction. Layout change here will require task_switch to be rewritten. */
typedef struct registers {
    uint32_t cs, ds, es, fs, gs, ss;
    uint32_t eflags;
    uint32_t edi, esi;
    uint32_t ebp, esp;
    uint32_t ebx, edx, ecx, eax;
} __attribute__((packed)) registers_t;


/* Function prototypes. */
void registers_copy(registers_t* dst, registers_t* src);

#endif
