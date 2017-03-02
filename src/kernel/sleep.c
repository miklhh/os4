/*
 * Part of OS4, sleep.c
 * Author Mikael Henriksson, miklhh
 */

#include <stdint.h>
#include <kernel/pit.h>
#include <system/sleep.h>

extern volatile uint32_t __sys_tick;

void sleep(uint32_t time_ms)
{
	/* The tick rate is 1000Hz. */
	uint32_t tick = __sys_tick;

	while (tick + time_ms >= __sys_tick)
	{
		asm volatile ("hlt");
	}
	return;
}
