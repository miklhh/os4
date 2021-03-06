/*
 * Part of OS4, stdio.h
 * Author: Mikael Henriksson, miklhh
 */

#ifndef _STDIO_H
#define _STDIO_H

// Includes:
#include <sys/cdefs.h>

// Macros:
#define EOF (-1)


/*** Print formated string:
 * Function that prints a formated string to the stdout. Returns the amount of
 * characters written.
 * ---------------------------------------------------------------------------*/
int printf(const char* restrict format, ...);


/*** Put character:
 * Function for writing a character (as an integer) to the stdout. Returns the
 * integer written on succes, or EOF (-1) if it fails.
 * ---------------------------------------------------------------------------*/
int putchar(int character);


/*** Put character:
 * Function for writing a string (without NULL character) to the stdout. 
 * Returns a positive integer on succes, or EOF (-1) if it fails.
 * ---------------------------------------------------------------------------*/
int puts(const char* string);


#endif
