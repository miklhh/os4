/*
 * Part of OS4, thread.c
 * Author: Mikael Henriksson, miklhh
 */

#include <thread/thread.h>
#include <kernel/registers.h>


/* Make a copy of a thread. */
void thread_copy(thread_t* dst, thread_t* src)
{
    registers_copy(dst->regs, src->regs);
    dst->page_dir      = src->page_dir;
    dst->thread_status = src->thread_status;
}

/* Initialise the threading. */
void threading_init()
{
    /* Clear the thread list. */
    for (uint8_t i = 0; i < sizeof(thread_t) * MAX_THREADS; i++)
    {
        *((uint8_t*) ((uintptr_t) thread + i)) = 0;
    }
}
