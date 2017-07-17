/*
 * Part of OS4, register.c
 * Author: Mikael Henriksson, miklhh
 */

#include <kernel/registers.h>

/* Function for copying registers. */
void registers_copy(registers_t* dst, registers_t* src)
{
    dst->cs = src->cs;
    dst->ds = src->ds;
    dst->es = src->es;
    dst->fs = src->fs;
    dst->gs = src->gs;
    dst->ss = src->ss;

    dst->edi = src->edi;
    dst->esi = src->esi;
    dst->ebp = src->ebp;
    dst->esp = src->esp;

    dst->eax = src->eax;
    dst->ebx = src->ebx;
    dst->ecx = src->ecx;
    dst->edx = src->edx;

    dst->eflags = src->eflags;
}
