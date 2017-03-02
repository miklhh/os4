/* 
 * Part of OS4, panic.c
 * Author Mikael Henriksson, miklhh
 */

#include <stdio.h>

void panic(char* string)
{
	printf(string);
	while (1)
	{
		asm volatile("cli");
		asm volatile("hlt");
	}
}
