/*
 * Part of OS4, keyboard.h
 * Author: Mikael Henriksson, miklhh
 */

#ifndef _KEYBOARD_H
#define _KEYBOARD_H

void 	keyboard_init();
uint8_t keyboard_enabled();
void 	keyboard_read_key();
char 	keyboard_get_key();
char 	keyboard_to_ascii(uint8_t key);


#endif
