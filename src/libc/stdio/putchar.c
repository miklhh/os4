/*
 * Part of OS4, putchar.c
 * Author: Mikael Henriksson. miklhh
 */

#include <stdio.h>


int putchar(int character)
{
    char c = (char) character;
    asm volatile(
            "movb   %0, %%bl        \n"
            "movw   $1, %%ax        \n"
            "int    $0x80           \n"
            :
            : "q"(c)
            : "%bl");

    return character;
}
