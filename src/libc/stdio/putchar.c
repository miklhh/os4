#include <stdio.h>

#if defined (__is_libk)
#include <driver/tty.h>
#endif



int putchar(int character)
{
    char c = (char) character;
    asm volatile(
            "movb   %0, %%bl        \n"
            "movw   $1, %%ax        \n"
            "int    $0x80           \n"
            :
            : "r"(c)
            : "%bl");

    return character;
}
