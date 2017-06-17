;
; Part of OS4, load_gdtr.asm
; Author: Mikael Henriksson, miklhh
;

section .text
global load_gdtr:function (load_gdtr.end - load_gdtr)

; -- Routine for loading the GDT-register.
; After base pointer push:
; [ebp + 8] == uint32_t gdtd_location (4 bytes).
; [ebp + 4] == Return address (4 bytes).
; [ebp + 0] == Last base pointer (4 bytes).
load_gdtr:
    push  ebp
    mov   ebp, esp
    push  eax

    mov   eax, [ebp + 8]
    lgdt  [eax]

    pop   eax
    pop   ebp
    ret
.end:


global reload_segments:function (reload_segments.end - reload_segments)

; -- Routine for reloading the segments. Should be called once after
;    the gdtr register has been set.
reload_segments:
	push  ebp
	mov   ebp, esp

	push  eax
	mov   ax, 0x10 		; Load 0x10 into the ds-register. (and others).
	mov   ds, ax
	mov   es, ax
	mov   fs, ax
	mov   gs, ax
	mov   ss, ax
	pop   eax

	jmp   0x08:.rscontinue 	; Load 0x08 into the cs-register. 
.rscontinue:
	mov   esp, ebp
	pop   ebp
	ret
.end:
