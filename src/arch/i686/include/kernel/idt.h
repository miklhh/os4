/*
 * Part of OS4, idt.h
 * Author: Mikael Henriksson, miklhh.
 */

#ifndef _IDT_H
#define _IDT_H

#include <stdint.h>
#include <kstdio.h>

/* Interrupt-setting macros. */
#define IDT_ENTRIES                 256

#define IDT_32BIT_INTERRUPT_GATE    0xE
#define IDT_32BIT_TRAP_GATE         0xF
#define IDT_32BIT_TASK_GATE         0x5
#define IDT_STORAGE_SEGMENT         0x20
#define IDT_DPL_3                   0x60
#define IDT_PRESENT                 0x80


/* Functions. */
void idt_init();
void set_int(uint8_t i, uint32_t callback, uint8_t type_attr);


/* Inline functions for setting and clearing interruptflag. */
static inline void interrupt_dissable() { asm volatile ("cli"); }
static inline void interrupt_enable() { asm volatile ("sti"); }


/* Structure for IDTD. */
typedef struct __attribute__((packed)) interrupt_descriptor_table_descriptor {
    uint16_t size;
    uint32_t location;
} idtd_t;


/* The IDT array datatype. */
typedef uint64_t idt_t[IDT_ENTRIES];

#endif

