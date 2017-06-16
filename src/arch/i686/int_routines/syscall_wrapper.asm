;
; Part of OS4, syscall_wrapper
; Author: Mikael Henriksson, miklhh
;

section .text
global syscall_wrapper
syscall_wrapper:
    extern  syscall
    call    syscall
    iret
