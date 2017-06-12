/*
 * Part of OS4, string.h
 * Author Mikael Henriksson, miklhh
 */


#ifndef _STRING_H
#define _STRING_H

#include <stddef.h>
#include <sys/cdefs.h>

/*** Memory compare: 
 * Compare two strings. Returns zero if the bytes pointed to by ptr1 and ptr2 
 * are equal. Returns 1 if the first character that breakes the string 
 * comparison is bigger in ptr 1, and vice versa. Tries max 'bytes' characters.
 * ---------------------------------------------------------------------------*/
int memcmp(const void* ptr1, const void* ptr2, size_t bytes);


/*** Memory copy:
 * Copys the source to the destination. The destination is returned.
 * ---------------------------------------------------------------------------*/
void* memcpy(void* destination, const void* source, size_t bytes);


/*** Memory move:
 * Moves memory from source to destination. Much like memcpy, but safer.
 * ---------------------------------------------------------------------------*/
void* memmove(void* destination, const void* source, size_t bytes);


/*** Memory set
 * Sets n character in the string str to 'c'.
 * ---------------------------------------------------------------------------*/
void* memset (void* str, int c, size_t n);


/*** String lenght:
 * Returns the length of a string.
 * ---------------------------------------------------------------------------*/
size_t strlen(const char* string);


#endif
