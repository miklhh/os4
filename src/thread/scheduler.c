/*
 * Part of OS4, scheduler.c
 * Author: Mikael Henriksson, miklhh
 */

#include <thread/thread.h>
#include <thread/scheduler.h>
#include <kernel/idt.c>
#include <stdint.h>

#define MAX_THREADS     1024

/* Thread list. */
static thread_t threads[MAX_THREADS];
static thread_t* active_thread;
static unsigned int active_threads;


void scheduler_init()
{
    /* Clear out the active thread list. */
    for (int i = 0; i < sizeof(thread_t) * MAX_THREADS; i++)
    {
         *((uint8_t) ((uintptr_t) thread + i)) = 0;
    }

    /* Active startup threads is zero. */
    active_threads = 0;
}

/* Function to be called by a timer to schedual threads. */
void sheduler_shedule()
{

}

void schedule_add_thread(thread_t* thread)
{
    interrupt_dissable();

    interrupt_enable();
}
