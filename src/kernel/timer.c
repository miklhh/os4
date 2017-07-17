/*
 * Part of OS4, timer.c
 * Author: Mikael Henriksson, miklhh
 */

#include <stdint.h>
#include <kernel/timer.h>
#include <kernel/pit.h>
#include <task/task.h>
#include <stdint.h>

/* Global tick variable. */
volatile uint64_t __sys_tick = 0;
extern uint8_t tasking_initialized;

/* 
 * Timer interrupt service routine.
 * 2017-06-25: Called each millisecond.
 * Gate type: Interruptgate.
 * DPL: Ring 0.
 */
void timer_irq()
{
    __sys_tick++;

    /* Call the task preempt function if tasking has been initialized. */
    if (tasking_initialized)
    {
        task_preempt();
    }
}

/* Timer init function. */
void timer_init()
{
   pit_init(); 
}
