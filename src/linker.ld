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
	.text BLOCK(4K) : ALIGN(4K)
	{
		*(.grubheader)
		*(.text)
	}

	/* Read only data. */
	.rodata BLOCK(4K) : ALIGN(4K)

	{
		*(.rodata)
	}

	/* Read and write data. */
	.data BLOCK(4K) : ALIGN(4K)

	{
		*(.data)
	}

	/* Read and write data (uninitialized) plus stack */
	.bss BLOCK(4K) : ALIGN(4K)

	{
		*(COMMON)
		*(.bss)
	}

	/* Label to find the end of the kernel. */
	__kernel_end = .;

	/* If the compiler generates more sections, add them here */
}
