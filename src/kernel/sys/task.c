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

#define KERNEL_STACK_SIZE           8192        // 8K kernel stack per task.
#define USER_STACK_SIZE             8192        // 2M user stack per task.

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

    /* Set kernel task parameters. */
    extern uintptr_t kernel_stack_bottom;
    extern uintptr_t kernel_stack_top;
    extern uintptr_t interrupt_stack_bottom;
    extern uint32_t kernel_page_directory[1024];
    kernel_task->page_dir   = (uintptr_t) kernel_page_directory;
    kernel_task->task_nr    = 0;
    kernel_task->next_task  = kernel_task;

    kernel_task->task_stack_begin   = kernel_stack_bottom;
    kernel_task->task_stack         = 0; // Set by task_preempt routine.
    kernel_task->task_stack_end     = kernel_stack_top;
    kernel_task->kernel_stack       = interrupt_stack_bottom;

    /* Give the kernel task to the tasking system. */
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
    /* Cycle (schedule) the tasks. */
    last_task->next_task = current_task;
    last_task = current_task;
    current_task = current_task->next_task;
    
    /* Switch task. */
    extern void set_kernel_stack(uintptr_t kernel_stack);
    load_page_directory((uintptr_t) current_task->page_dir);
    set_kernel_stack(current_task->kernel_stack);
    task_switch(
        &current_task->next_task->task_stack,    // Next task stack.
        &current_task->task_stack);              // Current task stack.
}


/* Function for getting the id of the currently running task. */
tid_t task_get_id()
{
    return current_task->task_nr;
}

/* Fork a task. */
tid_t task_fork()
{
    kprintf("Forking!\n");

    /* Allocate a new task and clean it. */
    task_t* new_task = kmalloc(sizeof(task_t));
    memset((void*) new_task, 0, sizeof(task_t));


    /* Setup a new kernel and user stack for the task. */
    new_task->task_stack_end = (uintptr_t) kmalloc(USER_STACK_SIZE);
    new_task->task_stack_begin = new_task->task_stack_end + USER_STACK_SIZE;
    new_task->kernel_stack = 
        (uintptr_t) kmalloc(KERNEL_STACK_SIZE) + KERNEL_STACK_SIZE;
    //memset((void*) new_task->task_stack_end, 0, sizeof(USER_STACK_SIZE));

    /* Copy the user stack from the running task. */
    // REDO!!
    memcpy(
        (void*) new_task->task_stack_end, 
        (void*) current_task->task_stack_end,
        USER_STACK_SIZE);

    new_task->task_stack = 
        new_task->task_stack_end + 
        //(current_task->task_stack_end - current_task->task_stack);
        (current_task->task_stack - current_task->task_stack_end);

    /* Set new task parameters. */
    new_task->task_nr = 1337;

    /* Add the task to the tasking system and return. */

    /* DEBUG */
    kprintf("Current task: %x, %x, %x, %x, %x, %x, %x, %x\n",
        *((uint32_t*) (current_task->task_stack + 0)),
        *((uint32_t*) (current_task->task_stack + 4)),
        *((uint32_t*) (current_task->task_stack + 8)),
        *((uint32_t*) (current_task->task_stack + 12)),
        *((uint32_t*) (current_task->task_stack + 16)),
        *((uint32_t*) (current_task->task_stack + 20)),
        *((uint32_t*) (current_task->task_stack + 24)),
        *((uint32_t*) (current_task->task_stack + 28)));
    kprintf("Next task task: %x, %x, %x, %x, %x, %x, %x, %x\n",
        *((uint32_t*) (new_task->task_stack + 0)),
        *((uint32_t*) (new_task->task_stack + 4)),
        *((uint32_t*) (new_task->task_stack + 8)),
        *((uint32_t*) (new_task->task_stack + 12)),
        *((uint32_t*) (new_task->task_stack + 16)),
        *((uint32_t*) (new_task->task_stack + 20)),
        *((uint32_t*) (new_task->task_stack + 24)),
        *((uint32_t*) (new_task->task_stack + 28)));

    task_add(new_task);
    kprintf("Fork completed.\n");
    return new_task->task_nr;
}
