/*
 * Part of OS4, scheduler.h
 * Author: Mikael Henriksson, miklhh
 */

#ifndef _SCHEDULER_H
#define _SCHEDULER_H

void scheduler_schedule();
void scheduler_init();
void scheduler_add_thread(thread_t* thread);

#endif
