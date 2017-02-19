;
; Part of OS4, interrupt_test_handler.asm
; Author Mikael Henriksson, miklhh
;

global interrupt_test_handler:function (interrupt_test_handler.end - interrupt_test_handler)
interrupt_test_handler:
	pusha
	extern interrupt_test_handler_function
	call interrupt_test_handler_function
	popa
	iret
.end:
