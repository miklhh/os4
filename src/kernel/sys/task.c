/*
 * Part of OS4, task.c
 * Author: Mikael Henriksson, miklhh
 */

#include <task/task.h>
#include <memory/memory.h>
#include <memory/paging.h>
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
    extern uint32_t kernel_page_directory[1024];
    kprintf("Initializing tasking.\n");

    /* Allocate the kernel task. */
    kernel_task = kmalloc(sizeof(task_t));
    memset(kernel_task, 0, sizeof(task_t));
    current_task = kernel_task;
    current_task->next_task = kernel_task;
    current_task->page_dir = (uintptr_t) kernel_page_directory;
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
    load_page_directory((uintptr_t) current_task->page_dir);

    /* Cycle (schedule) the current task. */
    last_task->next_task = current_task;
    last_task = current_task;
    current_task = current_task->next_task;
}

tid_t task_get_id()
{
    return current_task->task_nr;
}
