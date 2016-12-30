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
resb 16384
kernel_stack_top:


; -- Textsection for the acctual OS source code
section .text
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
