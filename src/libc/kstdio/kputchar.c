#include <kstdio.h>

#if defined (__is_libk)
#include <driver/tty.h>
#endif



int kputchar(int character)
{
    char c = (char) character;
    terminal_write(&c, sizeof(c));
    return character;
}
