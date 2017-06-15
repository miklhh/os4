;
; Part of OS4, boot.asm
; Author Mikael Henriksson, miklhh
;

; --- Multiboot header ---
; For documentation about the multibootheader:
; https://www.gnu.org/software/grub/manual/multiboot/multiboot.html
; --- Multiboot header ---
MBALIGN equ 1<<0                ; Align the master boot record with pages.
MEMINFO equ 1<<1                ; Tell GRUB that we want memory information.
MAGIC   equ 0x1BADB002          ; The magic GRUB boot number.
FLAGS   equ MBALIGN | MEMINFO   ; Flags for the multoboot header.


; Kernel virtual base address.
KERNEL_VIRTUAL_BASE equ 0xC0000000
KERNEL_PAGE_NUMBER  equ (KERNEL_VIRTUAL_BASE >> 22)

section .data
align 0x1000
boot_page_directory:
    ; 0x00000083 = (1 << 7) | (1 << 1) | (1 << 0)
    ; Bit 7: PS-bit.    The kernel page is 4MB.
    ; Bit 1: RW-bit.    The kernel is read/write.
    ; Bit 0: P-bit.     Present bit.
    dd 0x00000083
    times (KERNEL_PAGE_NUMBER - 1) dd 0         ; Pages before kernel space.
    dd 0x00000083
    times (1024 - KERNEL_PAGE_NUMBER - 1) dd 0  ; Pages after the kernel image.

; -- Start of multiboot header.
section .grubheader
align 4
	dd MAGIC
	dd FLAGS
	dd -(MAGIC + FLAGS)


; -- Stack after booting.
section .bss
align 16
global interrupt_stack_top
global kernel_stack_top

interrupt_stack_bottom:
    resb	32768
interrupt_stack_top:
    resb	16
kernel_stack_bottom:
    resb 	32768
kernel_stack_top:


; -- Textsection for the acctual OS source code
section .text


;global loader
;loader equ(_loader - 0xC0000000)
;_loader:
;    ; Till paging has been set up, the code must be position-independent.
;    mov ecx, (boot_page_directory - KERNEL_VIRTUAL_BASE)
;    mov cr3, ecx
;    
;    mov ecx, cr4
;    or  ecx, 0x00000010
;    mov cr0, ecx
;
;    lea ecx, [start_in_higher_half]
;    jmp ecx
;
;start_in_higher_half:
;    jmp $
;    mov dword [boot_page_directory], 0
;    invlpg [0]                              ; Flush the first page.
;    jmp _start                              ; Jump to the start.


; -- Function for loading the GDT-register.
global _set_gdtr:function (_set_gdtr.end - _set_gdtr)
_set_gdtr:
	push  ebp	
	mov   ebp, esp
	lgdt  [0x800]
	mov   esp, ebp
	pop   ebp
	ret
.end:

; -- Function for reloading the segments.
global _reload_segments:function (_reload_segments.end - _reload_segments)
_reload_segments:
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


global _start:function (_start.end - _start)
_start:

	; Setup the stack, call the global constructor and call the kernel
	mov 	esp, kernel_stack_top

	extern 	_init
	call	_init

	extern 	kernel_main
	call 	kernel_main

	; Halt the kernel if the OS by some reason returns.
	cli
.hang:	hlt
	jmp .hang

.end:	; End label for the _startfunction sizing.
