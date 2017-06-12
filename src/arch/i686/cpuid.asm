;
; Part of OS4, cpuid.asm
; Author: Mikael Henriksson, miklhh
;

section .text

; Function returns a value larger than zero in eax if CPUID instruction is 
; avilable for use.
global test_cpuid
test_cpuid:
    pushfd                          ; Push EFLAGS for reference.
    pushfd                          ; Push EFLAGS to grab them.
    xor     dword[esp], 0x00200000  ; Switch the state of the ID bit.
    popfd                           ; Put EFLAGS back into its register.
    pushfd                          ; Take the EFLAGS back from the register.
    pop     eax                     ; Pop them back to eax (id bit may reverse).
    xor     eax, dword[esp]         ; Test if we managed to switch the cpuid bit.
    popfd                           ; Pop reference EFLAGS back.
    and     eax, 0x00200000         ; Mask away all the other bits.
    ret                             ; Return from routine.

    
section .data
CPU_vendor_string:
times 12 db 0
