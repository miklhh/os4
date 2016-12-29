; --- 16 bit-instruction bootfunctions.
BITS 16

; Print string function. [Pointer to string in SI register]
printstring:
	printstring_start:
	pusha			; Push all general purpose registers to the stack.
	mov ah, 0x0e		; Bios routine for printing characters.	
	cmp byte[si], 0x0	; Test if the string is NULL-string
	je printstring_end	; In the case of NULL-string end jmp to the end.

	printstring_loop:
	mov al, [si]		; Mov the first character of the string the registrs.
	int 0x10		; Call bios
	inc si
	cmp byte[si], 0		; Test if this is the end of the string.
	je printstring_end	; Jump accordingly.
	jne printstring_loop


	printstring_end:
	popa			; Pop all the general purpose regisers back to their correspoing regisers.
	ret			; Return to caller.

clearscreen:
	pusha			; Push registers onto the stack.
	mov ah, 0x0e		; Prepare BIOS for writing.
	mov al, 0		; Print NULL character (print nothing at all).
	mov bx, 0		; Variable for printing NULL character.

	clearscreenloop:
	cmp bx, 2000		; Stop looping when the clearing has been done 2000 times.
	je clearscreenend	; Jump accordingly.

	int 0x10		; Make the interupt call.
	inc bx			; Increase BX.
	jmp clearscreenloop	; Redo.

	clearscreenend:
	mov ah, 0x02		; Prepare BIOS for moving cursor
	mov bh, 0x0		; Displaypage 0.
	mov dh, 0x0		; Row: 0
	mov dl, 0x0		; Column 0
	int 0x10		; Make the interupt call
	popa			; Pop values back to their registers
	ret			; Return
