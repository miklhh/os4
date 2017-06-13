;
; Part of OS4, load_page_directory
; Author: Mikael Henriksson, miklhh
;

global load_page_directory
load_page_directory:
	push    eax
	mov     eax, [esp+8]    ; Parameter address.
	mov     cr3, eax
	pop     eax
	ret
