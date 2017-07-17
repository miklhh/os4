;
; Part of OS4, busy_wait.asm
; Author: Mikael Henriksson, miklhh
;

; Function for busy waiting. Used by certaion architecture specific routines
; written in C so that GCC wont optimize certaion parts away.
global busy_wait
busy_wait:
    jmp $
