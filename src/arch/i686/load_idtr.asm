;
; Part of OS4, set_idtr.asm
; Author: Mikael Henriksson, mikl
;

section .text
global load_idtr:function (load_idtr.end - load_idtr)
load_idtr:
	push ebp
	mov ebp, esp
	lidt [0x10F0]
	pop ebp
	ret
.end:
