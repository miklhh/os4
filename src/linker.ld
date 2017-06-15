/* Entrypoint. */
ENTRY(_start)

/* OS-Sections. */
SECTIONS
{
	/* Load kernel at 1MiB into memory. */
	. = 0x00100000;
	
	/* Label to find the kernel start. */
	__kernel_start = .;

	/* The grubheader and the text-section. */
	.text :
	{
		*(.grubheader)
		*(.text)
	}

	/* Read only data. */
	.rodata :
	{
		*(.rodata)
	}

	/* Read and write data. */
	.data ALIGN(0x1000) :
	{
		*(.data)
	}

	/* Read and write data (uninitialized) plus stack */
	.bss :
	{
		*(COMMON)
		*(.bss)
	}

	/* Label to find the end of the kernel. */
	__kernel_end = .;

	/* If the compiler generates more sections, add them here */
}
