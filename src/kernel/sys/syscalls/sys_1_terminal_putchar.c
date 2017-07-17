/*
 * Part of OS4, sys_1_terminal_putchar.c
 * Author: Mikael Henriksson, miklhh
 */

/* 
 * Systemcall:      terminal_putchar.
 * Syscallnumber:   1.
 * Parameters:      Reg: bl = ascii-character.
 */

#include <stdint.h>
#include <driver/tty.h>

uint32_t sys_1_terminal_putchar()
{
    /* Aquire the character and print it. */
    char c;
    asm volatile("movb %%bl, %0" : "=r"(c) : : );
    terminal_putchar(c);
    return 0;
}
