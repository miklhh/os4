;
; Part of OS4, pit_irq_wrapper
; Author Mikael Henriksson, miklhh
;

global pit_irq_wrapper:function (pit_irq_wrapper.end - pit_irq_wrapper)
pit_irq_wrapper:
	pusha
	extern pit_irq
	call pit_irq
	popa
	iret
.end:
