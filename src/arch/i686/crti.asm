section .init
global _init
_init:
	push ebp
	mov ebp, esp
;.initend:

section .fini
global _fini
_fini:
	push ebp
	mov ebp, esp

