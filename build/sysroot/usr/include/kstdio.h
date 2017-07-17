/*
 * Part of OS4, kstdio.h
 * Author: Mikael Henriksson, miklhh
 */

#ifndef _KSTDIO_H
#define _KSTDIO_H

#define EOF (-1)

int kprintf(const char* restrict format, ...);
int kputchar(int character);
int kputs(const char* string);

#endif
