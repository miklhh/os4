;
; Part of OS4, boot.asm
; Author Mikael Henriksson, miklhh
;

; --- Multiboot header ---
; For documentation about the multibootheader:
; https://www.gnu.org/software/grub/manual/multiboot/multiboot.html
; --- Multiboot header ---
MBALIGN	equ 1<<0		; Align the master boot record with pages.
MEMINFO	equ 1<<1		; Tell GRUB that we want memory information.
MAGIC	equ 0x1BADB002		; The magic GRUB boot number.
FLAGS	equ MBALIGN | MEMINFO	; Flags for the multoboot header.

; -- Start of multiboot header
section .grubheader
align 4
	dd MAGIC
	dd FLAGS
	dd -(MAGIC + FLAGS)


; -- Stack after booting.
section .bss
align 16			; Align 4 tested, did not work.
kernel_stack_bottom:
resb 32768
kernel_stack_top:


; -- Textsection for the acctual OS source code
section .text

; -- Function for loading the GDT-register.
global _set_gdtr:function (_set_gdtr.end - _set_gdtr)
_set_gdtr:
	push ebp	
	mov ebp, esp

	lgdt [0x800]

	mov esp, ebp
	pop ebp
	ret
.end:

; -- Function for reloading the segments.
global _reload_segments:function (_reload_segments.end - _reload_segments)
_reload_segments:
	push ebp
	mov ebp, esp

	push eax
	mov ax, 0x10 		; Load 0x10 into the ds-register. (and others).
	mov ds, ax
	mov es, ax
	mov fs, ax
	mov gs, ax
	mov ss, ax
	pop eax

	jmp 0x08:.rscontinue 	; Load 0x08 into the cs-register. 
.rscontinue:
	mov esp, ebp
	pop ebp
	ret
.end:


global _start:function (_start.end - _start)
_start:

	; Setup the stack, call the global constructor and call the kernel
	mov esp, kernel_stack_top

	extern _init
	call _init

	extern kernel_main
	call kernel_main

	; Halt the kernel if the OS by some reason returns.
	cli
.hang:	hlt
	jmp .hang

.end:	; End label for the _startfunction sizing.
