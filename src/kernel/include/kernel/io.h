/* ********************************************** *
 * Functions for using the processor input output 
 * ********************************************** */

/* 8-bit (a byte) port in function. */
static inline uint8_t inb (uint16_t port)
{
	uint8_t value;
	asm volatile ("inb %1, %0" : "=a"(value) : "Nd"(port));
	return value;
} 

/* 8-bit (a byte) port out function. */
static inline void outb (uint8_t value, uint16_t port)
{
	asm volatile ("outb %0, %1" :: "a"(value), "Nd"(port));
}

/* 16-bit (a word) port in function. */
static inline uint8_t inw (uint16_t port)
{
	uint16_t value;
	asm volatile ("inw %1, %0" : "=a"(value) : "Nd"(port));
	return value;
}

/* 16-bit (a word) port out function. */
static inline void outw (uint16_t value, uint16_t port)
{
	asm volatile ("outw %0, %1" :: "a"(value), "Nd"(port));
}
