/*
 * Part of OS4, sleep.c
 * Author Mikael Henriksson, miklhh
 */

#include <stdint.h>
#include <kernel/pit.h>
#include <kernel/ksleep.h>
#include <kstdio.h>

extern volatile uint64_t __sys_tick;

/* This function requieres ring 0 priviliges. Otherwise it will throw a general
 * protection fault. */
void ksleep(uint32_t time_ms)
{
	/* The tick rate is 1000Hz. */
	uint32_t tick = __sys_tick;

	while (tick + time_ms >= __sys_tick)
	{
		asm volatile ("hlt");
	}
}
