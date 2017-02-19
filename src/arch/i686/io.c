/*
 * Part of OS4, io.c
 * Author: Mikael Henriksson, miklhh
 */

#include <kernel/io.h>


/* 8-bit (a byte) port in function. */
uint8_t inb (uint16_t port)
{
	uint8_t value;
	asm volatile ("inb %1, %0" : "=a"(value) : "Nd"(port));
	return value;
} 

/* 8-bit (a byte) port out function. */
void outb (uint8_t value, uint16_t port)
{
	asm volatile ("outb %0, %1" :: "a"(value), "Nd"(port));
}

/* 16-bit (a word) port in function. */
uint16_t inw (uint16_t port)
{
	uint16_t value;
	asm volatile ("inw %1, %0" : "=a"(value) : "Nd"(port));
	return value;
}

/* 16-bit (a word) port out function. */
void outw (uint16_t value, uint16_t port)
{
	asm volatile ("outw %0, %1" :: "a"(value), "Nd"(port));
}

/* 32-bit (a long) port in function. */
uint32_t inl(uint16_t port)
{
	uint32_t value;
	asm volatile ("inl %1, %0" : "=a"(value) : "Nd"(port));
	return value;
}

/* 32-bit (a long) port out function. */
void outl (uint32_t value, uint16_t port)
{
	asm volatile ("outl %0, %1" :: "a"(value), "Nd"(port));

}
