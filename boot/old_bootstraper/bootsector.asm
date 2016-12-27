; Assemble with 16 bit instructions.
BITS 16
[org 0x7c00]

; Clear the screen.
call clearscreen

; Try to write something
mov si, string3
call printstring


; End of the bootsector, halt the OS. The OS should not really ever come here.
end:
	cli
	hlt
	jmp end

; --- Includes ---
%include "bootfunctions.asm"

; --- Data-section ---:
helloworld:
	db 'Hello World! ',0

string2:
	db 'This is a test string',0

string3:
	db 'This is the third string',0


; Pad out and add the boot signature
times 510-($-$$) db 0x00	; Pad out with zeros.
dw 0xaa55			; Boot signature.
