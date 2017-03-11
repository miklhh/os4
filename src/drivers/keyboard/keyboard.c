/*
 * Part of OS4, keyboard.c
 * Author: Mikael Henriksson, miklhh
 */

#include <stdint.h>
#include <memory/memory.h>
#include <kernel/idt.h>
#include <kernel/io.h>
#include <kernel/pic.h>
#include <driver/keyboard.h>
#include <stdio.h>
#include <string.h>
#include <driver/keycode.h>

uint8_t	 last_key 	= 0;
char*	 keybuffer 	= 0;
uint16_t key_loc	= 0;
uint8_t	 kbd_enabled	= 0;

extern void keyboard_irq_wrapper();

void keyboard_init()
{
	printf("Initializing PS/2-Keyboard routines.\n");
	keybuffer = (char*) kmalloc(256);
	memset(keybuffer, 0, 256);
	set_int(
		0x21, 						// 0x21, IRQ-1.
		(uint32_t) &keyboard_irq_wrapper,		// Wrapper function.
		IDT_32BIT_INTERRUPT_GATE | IDT_PRESENT);	// Type attributes.
	kbd_enabled = 1;
	printf("Keyboard initialization done.\n");
}

uint8_t keyboard_enabled()
{
	return kbd_enabled;
}

void keyboard_read_key()
{
	last_key = 0;

	/* Test if we are allowed to read from the PS/2 controller, ie test the PS/2 output 
	 * buffer status. Bit zero (0x01) is the output buffer status bit in the status
	 * register (located at I/O port 0x64.*/
	if (inb(0x64) & 0x01)
	{
		last_key = inb(0x60);
	}
}

char keyboard_get_key()
{
	char c = 0;
	if (key_loc == 0) 
		return c;

	/* Set 'c' to the next key in the buffer, and roll the buffer (array) down. */
	c = *keybuffer;
	key_loc--;
	for (uint8_t i = 0; i < 255; i++)
	{
		keybuffer[i] = keybuffer[i+1];
	}
	
	return c;
}

static char* _qwertyuiop 	= "qwertyuiop";
static char* _asdfghjkl		= "asdfghjkl";
static char* _zxcvbnm		= "zxcvbnm";
static char* _num		= "1234567890";

char keyboard_to_ascii(uint8_t key)
{
	if (key == 0x1C) 		return '\n';
	if (key == 0x39) 		return ' ';
	if (key == 0x0E) 		return '\r';
	if (key == POINT_RELEASED) 	return '.';
	if (key == SLASH_RELEASED) 	return '/';
	if (key == ZERO_PRESSED) 	return '0';
	if (key >= ONE_PRESSED && key <= NINE_PRESSED)
		return _num[key - ONE_PRESSED];

	if (key >= 0x10 && key <= 0x1C)
		return _qwertyuiop[key - 0x10];
	
	if (key >= 0x1E && key <= 0x26)
		return _asdfghjkl[key - 0x1E];

	if (key >= 0x2C && key <= 0x32)
		return _zxcvbnm[key - 0x2C];
	
	return (char) 0;
}

void keyboard_irq()
{
	/* Load the keycode and convert it into ascii-code. Also send end of
	 * interrupt (IRQ1) to the PIC */
	keybuffer[key_loc++] = keyboard_to_ascii(inb(0x60));
	pic_send_eoi(1);
}
