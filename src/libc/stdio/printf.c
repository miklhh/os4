/* File copied from:
 * http://wiki.osdev.org/Meaty_Skeleton
 * ------------------------------------
 * Modofications has been made to printf.c to fit this OS.
 */
#include <limits.h>
#include <stdbool.h>
#include <stdarg.h>
#include <stdio.h>
#include <string.h>
#include <stdint.h>

/* An Ascii-Hexabet */
static char hexabet[16] = {'0', '1', '2', '3',
			   '4', '5', '6', '7',
			   '8', '9', 'A', 'B',
			   'C', 'D', 'E', 'F'};

/* Variable array for hexconverter */
static char hexstring[11] = "0x00000000\0";

/* Print function. */
static bool print(const char* data, size_t length) 
{
	const unsigned char* bytes = (const unsigned char*) data;
	for (size_t i = 0; i < length; i++)
		if (putchar(bytes[i]) == EOF)
			return false;
	return true;
}

char* hexconverter (uint32_t num)
{
	memcpy(hexstring, (char[11]){ '0', 'x', '0', '0', '0',
				      '0', '0', '0', '0', '0',
				      '\0'}, 11);
	
	for (uint8_t i = 9; i > 1; i--)
	{
		/* For each iteration, bitshift the number accordingly. */
		uint32_t temp = 0;
		temp = num >> (4 * (9 - i));

		/* Mask the the first four bits of the temp variable */
		temp &= 0xf;
		hexstring[i] = hexabet[temp];
	}

	/* Return the string. */
	return hexstring;
}

int printf(const char* restrict format, ...) 
{
	va_list parameters;
	va_start(parameters, format);

	int written = 0;

	while (*format != '\0') 
	{
		size_t maxrem = INT_MAX - written;

		if (format[0] != '%' || format[1] == '%') 
		{
			if (format[0] == '%')
				format++;
			size_t amount = 1;
			while (format[amount] && format[amount] != '%')
				amount++;
			if (maxrem < amount) 
			{
				// TODO: Set errno to EOVERFLOW.
				return -1;
			}
			if (!print(format, amount))
				return -1;
			format += amount;
			written += amount;
			continue;
		}

		const char* format_begun_at = format++;

		/* Handle '%c, a character being passed in the argument list. */
		if (*format == 'c') 
		{
			format++;
			char c = (char) va_arg(parameters, int /* char promotes to int */);
			if (!maxrem) 
			{
				// TODO: Set errno to EOVERFLOW.
				return -1;
			}
			if (!print(&c, sizeof(c)))
				return -1;
			written++;
		}
		 
		/* Handle '%s', a string being passed in the argument list */
		else if (*format == 's') 
		{
			format++;
			const char* str = va_arg(parameters, const char*);
			size_t len = strlen(str);
			if (maxrem < len) 
			{
				// TODO: Set errno to EOVERFLOW.
				return -1;
			}
			if (!print(str, len))
				return -1;
			written += len;
		}
		
		/* Handle '%h', an unsinged integer being passed in the
		 * argument list. Printing argument in hex. */
		else if (*format == 'h')
		{
			format++;
			uint32_t num = va_arg(parameters, uint32_t);

			char* string = hexconverter(num);
			if (!maxrem)
			{
				// TODO: Set errno to EOVERFLOW.
				return -1;
			}
			if (!printf(string))
				return -1;
			written++;
		}

		else if (*format == 'u')
		{
			format++;
			uint32_t num = va_arg(parameters, uint32_t);

			/* Test if the number is zero */
			if (num == 0)
			{
				putchar('0');
			}

			/* Otherwise, use simple algorithm to print the number */
			uint8_t index = 0;
			uint32_t stack[10];	// Uint32 cannot be bigger than 4 billion.
			while (num > 0)
			{
				/* Divide by ten, store the remainder onto a stack. */
				uint32_t remainder;
				remainder = num % 10;
				num = num / 10;
				stack[index] = remainder;
				index++;
			}
			
			for (size_t i = 0; i < index; i++)
			{
				putchar((char)(stack[index-(i+1)] + 48));
			}
		}
	
		else  {
			format = format_begun_at;
			size_t len = strlen(format);
			if (maxrem < len) 
			{
				// TODO: Set errno to EOVERFLOW.
				return -1;
			}
			if (!print(format, len))
				return -1;
			written += len;
			format += len;
		}
	}

	va_end(parameters);
	return written;
}
