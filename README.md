# OS4
Minimal hobby operating system written for the x86 architecture.

### Prerequisites
**[GNU Compiler Collection](https://gcc.gnu.org/)** - C cross-compiler used to build the software. The binutils from GCC is also requiered for linking the software and archiving libraries. The crosscompiler arcitecture used to developing the software was i686, but the i386 build architecture should work aswell. [This OSdev.org tutorial](http://wiki.osdev.org/GCC_Cross-Compiler) will help you install a cross-compiler on your system.

**[NASM](http://www.nasm.us/)** - The *Netwide Assembler* is used to to assemble parts of the software. NASM or equivalent assembler is requiered to build the software, although nasm is the recommended one. You can install NASM throught your package manager or build from source via the NASM web page.

**[GRUB](https://www.gnu.org/software/grub/)** - The *GNU Grand Unified Bootloader* is used to bootstrap the software.

## Authors
* **Mikael Henriksson** - *Code and testing* - [https://github.com/miklhh](https://github.com/miklhh)

Version: 1.3.1 <br />
Version Date: 2017-06-16

