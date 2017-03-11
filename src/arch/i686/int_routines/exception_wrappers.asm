;
; Part of OS4, exception_wrappers.asm
; Author: Mikael Henriksson, miklhh
;

global general_protection_fault_wrapper
general_protection_fault_wrapper:
	push 	ebp
	mov 	ebp, esp

	extern 	general_protection_fault
	call 	general_protection_fault
	
	pop 	ebp
	iret


global divide_by_zero_error_wrapper
divide_by_zero_error_wrapper:
	push 	ebp
	mov	ebp, esp

	extern 	divide_by_zero_error
	call 	divide_by_zero_error
	
	pop 	ebp
	iret


global page_fault_wrapper
page_fault_wrapper:
	push 	ebp
	mov	ebp, esp

	extern 	page_fault
	call 	page_fault

	pop	ebp
	iret
