;
; Part of OS4, interrupt_test_handler.asm
; Author Mikael Henriksson, miklhh
;

global interrupt_test_handler
interrupt_test_handler:
	pusha
    
    extern      idt_initialized
    mov         byte[idt_initialized], 0xAB

	popa
	iret
