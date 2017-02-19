;
; Part of OS4, _set_idtr.asm
; Author Mikael Henriksson, mikl
;

section .text
global _set_idtr:function (_set_idtr.end - _set_idtr)
_set_idtr:
	push ebp
	mov ebp, esp
	lidt [0x10F0]
	pop ebp
	ret
.end:
