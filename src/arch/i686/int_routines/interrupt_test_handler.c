/*
 * Part of OS4, idt_test_handler_function.c
 * Author: Mikael Henriksson, miklhh
 */

#include <stdio.h>
#include <stdint.h>
void interrupt_test_handler_function()
{
	static uint32_t i = 0;
	printf("Interrupt test handler printing: %u.\n", i);
	i++;
	return;
}
