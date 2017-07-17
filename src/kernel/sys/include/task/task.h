/*
 * Part of OS4, task.h
 * Autor: Mikael Henriksson, miklhh
 */

#ifndef _KERNEL_TASK_H
#define _KERNEL_TASK_H

#include <stdint.h>
#include <kernel/registers.h>
#include <types.h>


/* Process identification. */
typedef uint32_t pid_t;
typedef uint32_t tid_t;


/* Task for the x86 arcitecture (with support for linked lists). */
typedef struct task {
    registers_t     regs;           /* Task registers. */
    uintptr_t       task_stack;     /* Task stack. Pointer to bottom of regs. */
    uintptr_t       page_dir;       /* Page directory. */
    uint32_t        task_nr;        /* Task number. */
    struct task*    next_task;      /* Next task for linked list. */
} task_t;


/* Process image. */
typedef struct image {
    size_t      size;           /* Image size. */
    uintptr_t   entry;          /* Binart entry point. */
    uintptr_t   heap;           /* Heap pointer. */
    uintptr_t   heap_actual;    /* Heap physical location. */
    uintptr_t   stack;          /* Process kernel stack. */
    uintptr_t   user_stack;     /* User stack. */
} image_t;


/* Function declarations. */
extern void switch_task(task_t* task);
extern void switch_to_usermode();
void task_enable();
void task_preempt();

#endif
