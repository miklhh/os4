;
; Part of OS4, task.asm
; Author: Mikael Henriksson, miklhh
;


; ----------------------------------------------------------------
;
; ----- C prototype of registers_t:
;   typedef struct task {
;       sp_t        current_sp;
;       uintptr_t   page_dir;
;       uint32_t    task_nr;
;   }
;
; For the task switch the registers are pushed to the stack, the stack pointer
; for the next task is loaded and the registers for the new task are poped of
; its stack.
;
; Note: Registers are pushed to the stack according to the registers_t 
;       definition (registers_t.h), and the System V ABI specification for
;       32-bit architecture routines.


; Task switch routine.
; C prototype:
; -- void task_switch(uintptr_t* new_stack, uintptr_t* old_stack)
global task_switch
task_switch:
    pusha                       ; Push all general purpose registers.
    mov     eax, dword[esp+8]   
    mov     dword[eax], esp
    mov     eax, dword[esp+8]
    mov     esp, dword[eax]
    ;mov     dword[esp+8], esp   ; Store the old task stack.
    ;mov     esp, dword[esp+4]   ; Load the task stack.
    popad                       ; Retrive the new gprs.
    ret                         ; Return.


; Store a task to a registers_t structure.
global task_store_old
task_store_old:
    push    eax
    mov     eax, dword[esp+4]   ; (esp+4) == pointer to registers.
    mov     dword[eax+28], esp  ; Add the current tasks stackpointer.
    add     eax, 52             ; Size of the registers_t structure.
    mov     esp, eax            ; Use the pointer to the registers as stack.

    pushf                       ; Store eflag (not really needed, but hey...).
    push    edx                 ; Store edx.
    push    ecx                 ; Store ecx.
    push    ebx                 ; Store ebx.
    push    eax                 ; Store eax.

    push    0x00000000          ; We skip adding eip for now, not needed anyway.
    sub     esp, 4              ; Stackpointer already added.
    push    ebp                 ; Store ebp.
    push    esi                 ; Store esi.
    push    edi                 ; Store edi.

    push    ss                  ; Store segment register.
    push    gs                  ; Store segment register.
    push    fs                  ; Store segment register.
    push    es                  ; Store segment register.
    push    ds                  ; Store segment register.
    push    cs                  ; Store cs (not really needed, bu hey...).

    mov     esp, dword[esp-30]  ; Restore the stack a return.
    pop     eax
    ret

    
; Load a task from a registers_t structure.
global task_load_old
task_load_old:
    mov     eax, dword[esp+4]
    mov     esp, eax
    
    add     esp, 4              ; CS register will be loaded by iret instruction.
    pop     ds                  ; Load segment register.
    pop     es                  ; Load segment register.
    pop     fs                  ; Load segment register.
    pop     gs                  ; Load segment register.
    pop     ss                  ; Load segment register.
    
    pop     edi                 ; Load edi.
    pop     esi                 ; Load esi.
    pop     ebp                 ; Load ebp.
    add     esp, 8              ; Skip poping esp and eip.

    pop     eax                 ; Load eax.
    pop     ebx                 ; Load ebx.
    pop     ecx                 ; Load ecx.
    pop     edx                 ; Load edx.
    add     esp, 4              ; Skip poping eflags, loaded by iret instruction.
    mov     esp, dword[esp+28]  ; Load the new stackpointer.
    ret


; Function used to make a switch to user mode.
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


