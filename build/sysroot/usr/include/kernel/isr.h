/*
 * Part of OS4: isr.h
 * Author: Mikael Henriksson, miklhh
 */

typedef struct registers
{
	uint32_t ds;						// Data segment register.
	uint32_t edi, esi, ebp, esp, ebx, edx, ecx, eax		// GP registers.
	uint32_t int_no;					// Intterrupt number
	uint32_t err_code;					// Error code.
	uint32_t eip, cs, eflags, useresp, ss			// Pushed by processor.

} registers_t
