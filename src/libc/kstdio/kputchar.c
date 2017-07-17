/*
 * Part of OS4, kputchar.c
 * Author: Mikael Henriksson, miklhh
 */

#include <kstdio.h>
#include <driver/tty.h>



int kputchar(int character)
{
    char c = (char) character;
    terminal_write(&c, sizeof(c));
    return character;
}
