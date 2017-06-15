/* 
 * Part of OS4, kputs.c
 * Author: Mikael Henriksson, miklh
 */

#include <kstdio.h>

int kputs(const char* string)
{
	return kprintf("%s\n", string);
}
