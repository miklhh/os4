/*
 * Part of OS4, task.c
 * Author: Mikael Henriksson, miklhh
 */

#include <task/task.h>
#include <memory/memory.h>
#include <stdint.h>
#include <kstdio.h>
#include <string.h>


static task_t* current_task;
static task_t* last_task;
static task_t* kernel_task;
static uint32_t task_count = 0;
uint8_t tasking_initialized = 0;

extern void task_switch(uintptr_t* new_stack, uintptr_t* old_stack);
extern void busy_wait();


/* Add a task to the task list. */
void task_add(task_t* task)
{
    last_task->next_task = task;
    last_task = task;
    task_count++;
}


/* Function for enabling (multi)tasking. */
void task_enable()
{
    kprintf("Initializing tasking.\n");

    /* Allocate the kernel task. */
    kernel_task = kmalloc(sizeof(task_t));
    memset(kernel_task, 0, sizeof(task_t));
    kernel_task->task_stack = ((uintptr_t) &kernel_task->regs) + sizeof(registers_t);
    current_task = kernel_task;
    current_task->next_task = kernel_task;
    last_task = kernel_task;
    task_count = 1;
    
    tasking_initialized = 1;
    kprintf("Tasking initialized.\n");
}



/* Function called by the timer interrupt service routine. Function schedules
 * the running tasks with the 'Round Robin' algorithm. */
void task_preempt()
{
    /* Switch task. */
    task_switch(
        &current_task->next_task->task_stack, 
        &current_task->task_stack);

    /* Cycle (schedule) the current task. */
    last_task->next_task = current_task;
    last_task = current_task;
    current_task = current_task->next_task;
    //last_task->next_task = NULL;
}
