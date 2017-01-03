section .init
global _init  ;:function (_init.initend - _init)
_init:
	push ebp
	mov ebp, esp
;.initend:

section .fini
global _fini   ;:function ;(_fini.finiend - _fini)
_fini:
	push ebp
	mov ebp, esp
;.finiend:
