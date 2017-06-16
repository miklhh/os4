;
; Part of OS4, task.asm
; Author: Mikael Henriksson, miklhh
;

global switch_to_user_mode:function (switch_continue.end - switch_to_user_mode)
switch_to_user_mode:
    push  ebp
    mov   ebp, esp          ; Setup function stack-frame.
	
    cli
    mov   ax, 0x23          ; 0x23 = 0x20 | 0x03. Descriptor 3, and ring level 3.
    mov   ds, ax            ; Load data segment register.
    mov   es, ax            ; Load extra segment register 1.
    mov   fs, ax            ; Load extra segment register 2.
    mov   gs, ax            ; Load extra segment register 3.

    mov   eax, esp          ; Prepare to push the stack pointer.
    push  0x23              ; Stack segment selector to be used (ring level 3)
    push  eax               ; Push the stackpointer.
    pushf                   ; Push the current EFLAGS state.

    pop   eax               ; Get the EFLAGS into the eax register.
    or    eax, 0x200        ; Set the 'Interrupt enable flag'.
    push  eax               ; Push the EFLAGS with interrupt flag back to stack.

    push  0x1B              ; Code segment (0x1b = 0x18 | 0x03. Ring level 3.)
    push  switch_continue   ; Push the instruction to continue execution at.
    iret                    ; Preform the interrupt-return. 
	
switch_continue:
    pop   	ebp
    ret
.end:
