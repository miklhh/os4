/*
 * Part of OS4, thread.h
 * Author: Mikael Henriksson, miklhh
 */

#ifndef _THREAD_H
#define _THREAD_H

#include <kernel/register.h>
#include <stdint.h>

/* Thread status types. */
typedef enum thread_status {
    THREAD_ACTIVE,
    THREAD_SUSPENDED,
    THREAD_DEAD
} thread_status_t;

/* Structure for storing a thread. */
typedef struct thread {
    registers_t     regs;                   // Registers for thread.
    uintptr_t       page_dir;               // Page directory location for thread.
    thread_status_t thread_status;          // Thread status.
    uint32_t        thread_number;          // Thread number.
    char            thread_name[32];        // Thread name.
} thread_t;

#endif
