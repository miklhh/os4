/* 
 * Part of OS4, panic.c
 * Author Mikael Henriksson, miklhh
 */

#include <kstdio.h>

void panic(char* string)
{
	kprintf(string);
	while (1)
	{
		asm volatile("cli");
		asm volatile("hlt");
	}
}
