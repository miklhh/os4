global enable_paging
enable_paging:
	push 	ebp
	mov	ebp, esp
	mov	eax, cr0
	or	eax, 0x80000000
	mov	cr0, eax
	pop	ebp
	ret
