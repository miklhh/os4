;
; Part of OS4, set_idtr.asm
; Author: Mikael Henriksson, mikl
;

section .text
global load_idtr:function (load_idtr.end - load_idtr)

; -- Routine for loading the IDT-register.
; After base pointer push:
; [ebp + 8] == uint32_t idtd_location (4 bytes).
; [ebp + 4] == Return address (4 bytes).
; [ebp + 0] == Last base pointer (4 bytes).
load_idtr:
	push  ebp
	mov   ebp, esp
    push  eax

    mov   eax, [ebp + 8]
	lidt  [eax]

    pop   eax
	pop   ebp
	ret
.end:
