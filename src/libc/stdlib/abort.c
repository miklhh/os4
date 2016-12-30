#include <stdio.h>
#include <stdlib.h>

__attribute__((noreturn))
void abort()
{
#if defined(__is_libk)
	// TODO: Add proper kernel panic.
	printf("Kernel panic: abort()\n");
#else
	// TODO: Abnormally terminante the process as if by SIGABRT
	printf("abort");
#endif
	while(1) { }
	__builtin_unreachable();
}
