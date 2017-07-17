/*
 * Part of OS4, io.h
 * Author: Mikael Henriksson, miklhh
 */

#ifndef _IO_H
#define _IO_H

/* ****************************************** *
 * Functions for using the processor BUS I/O. * 
 * ****************************************** */

/*
 * Note: This file is implemented in the arch directory.
 */

/* TODO:
 * Implement the in and out for double word!
 */
#include <stdint.h>

/* In functions */
uint8_t   inb (uint16_t port);
uint16_t  inw (uint16_t port);
uint32_t  ind (uint16_t port);

/* Out functions */
void  outb (uint8_t value, uint16_t port);
void  outw (uint16_t value, uint16_t port);
void  outd (uint32_t value, uint16_t port);

#endif
