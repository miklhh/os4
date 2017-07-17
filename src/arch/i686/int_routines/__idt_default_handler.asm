; 
; Part of OS4, __idt_default_handler.asm
; Author Mikael Henriksson, miklhh
;

global __idt_default_handler:function (__idt_default_handler.end - __idt_default_handler)
__idt_default_handler:
	pusha

	mov         al,  0x20    ; ???
	mov         dx,  0x20    ; ???
	out         dx,  al      ; ???

	popa
	iret
.end:
