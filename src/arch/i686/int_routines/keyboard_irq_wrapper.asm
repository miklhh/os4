global keyboard_irq_wrapper:function (keyboard_irq_wrapper.end - keyboard_irq_wrapper)
keyboard_irq_wrapper:
	pusha
	extern keyboard_irq
	call keyboard_irq
	popa
	iret
.end:
