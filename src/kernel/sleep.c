/*
 * Part of OS4, sleep.c
 * Author Mikael Henriksson, miklhh
 */

#include <stdint.h>
#include <kernel/pit.h>
#include <system/sleep.h>

extern volatile uint32_t pic_tick;

void sleep(uint32_t time_ms)
{
	/* The tick rate is 200Hz. */
	uint32_t tick_on_start = pic_tick;

	while (tick_on_start + time_ms >= pic_tick)
	{
		/* Do nothing... */
	}
	return;
}
