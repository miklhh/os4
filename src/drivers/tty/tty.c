#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <string.h>

#include <driver/tty.h>
#include <kernel/io.h>

#include "vga.h"

static const size_t VGA_WIDTH = 80;
static const size_t VGA_HEIGHT = 25;
static uint16_t* const VGA_MEMORY = (uint16_t*) 0xB8000;

static ttyposition cursor;
static uint8_t terminal_color;
static uint16_t* terminal_buffer;


/* Set the current position of the curser */
static void set_cursor_at(size_t x, size_t y)
{
	/* TODO: Like everything else here, but even more importantly in this 
	 * functioni, since this functino uses io-ports, make sure this 
	 * function is only used in VGAs TEXT MODE! */
	const uint16_t ADDR_REG_PORT = 0x3d4;   // VGA Address register port
	const uint16_t DATA_REG_PORT = 0x3d5;   // VGA Data register port.
	const uint8_t CURSOR_LOC_H_REG = 0x0e;  // Cursor location high register.
	const uint8_t CURSOR_LOC_L_REG = 0x0f;  // Cursor location low register.

	uint16_t cursor_loc = VGA_WIDTH * y + x;
	uint8_t cursor_loc_h = (uint8_t) (cursor_loc >> 8);
	uint8_t cursor_loc_l = (uint8_t)  cursor_loc;

	outw(CURSOR_LOC_H_REG, 	ADDR_REG_PORT);
	outw(cursor_loc_h, 	DATA_REG_PORT);

	outw(CURSOR_LOC_L_REG, 	ADDR_REG_PORT);
	outw(cursor_loc_l,	DATA_REG_PORT);
}

/* Initialize the tty */
void terminal_init() 
{
	/* Set cursorposition on initialization */
	cursor.x = 0;
	cursor.y = 0;
	
	terminal_color = vga_entry_color(VGA_COLOR_LIGHT_GREY, VGA_COLOR_BLACK);
	terminal_buffer = VGA_MEMORY;
	for (size_t y = 0; y < VGA_HEIGHT; y++) 
	{
		for (size_t x = 0; x < VGA_WIDTH; x++) 
		{
			const size_t index = y * VGA_WIDTH + x;
			terminal_buffer[index] = vga_entry(' ', terminal_color);
		}
	}

	/* Set the cursor to the start position. */
	set_cursor_at(0,0);
}

void terminal_setcolor(uint8_t color) 
{
	terminal_color = color;
}

static void terminal_putentryat(unsigned char c, uint8_t color, size_t x, size_t y) 
{
	const size_t index = y * VGA_WIDTH + x;
	terminal_buffer[index] = vga_entry(c, color);
}

void terminal_putchar(char c) 
{
	unsigned char uc = c;

	/* Test for newline */
	if (c == '\n')
	{
		cursor.x = 0;
		if (++cursor.y >= VGA_HEIGHT)
			terminal_scroll(1);
	}
	
	else 
	{
		terminal_putentryat(uc, terminal_color, cursor.x, cursor.y);
		if (++cursor.x == VGA_WIDTH)
		{
			cursor.x = 0;
			if (++cursor.y == VGA_HEIGHT)
				terminal_scroll(1);	
		}
	}

	/* Set cursor position */
	set_cursor_at(cursor.x, cursor.y);
}

void terminal_write(const char* data, size_t size) 
{
	for (size_t i = 0; i < size; i++)
		terminal_putchar(data[i]);
}

void terminal_writestring(const char* data) 
{
	terminal_write(data, strlen(data));
}

/* Scroll the terminal. */
void terminal_scroll(size_t scrolltimes)
{
	/* When a buffer for storing longer tty session has been implomenter
	 * Make sure to edit this function so that the top line wont be
	 * removed. */
	
	// Relocate the entries in the terminal
	for (size_t row = scrolltimes; row < VGA_HEIGHT; row++)
	{
		for (size_t col = 0; col < VGA_WIDTH; col++)
		{
			unsigned char character = terminal_buffer[row * VGA_WIDTH + col];
			terminal_putentryat
				(
					character,          // Character.
					terminal_color,     // Color.
					col,                // Column.
					row - scrolltimes   // Row.
				);
		}
	}

	// Clear out the moved characters.
	for (size_t row = (VGA_HEIGHT - scrolltimes); row < VGA_WIDTH; row++)
	{
		for (size_t col = 0; col < VGA_WIDTH; col++)
		{
			terminal_putentryat
				(
					' ',            // Character.
					terminal_color, // Color.
					col,            // Column.	
					row             // Row.
				);
		}
	}
	
	// Set the cursor accordingly.
	if (scrolltimes > cursor.y)
	{
		cursor.x = 0;
		cursor.y = 0;
		set_cursor_at(cursor.x, cursor.y);
	}
	else
	{
		cursor.y = cursor.y - scrolltimes;
		set_cursor_at(cursor.x, cursor.y);
	}
}
