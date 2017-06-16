# OS4
Minimal hobby operating system written for the x86 architecture.

### Prerequisites
**[GNU Compiler Collection](https://gcc.gnu.org/)** - C cross-compiler used to build the software. The binutils from GCC is also requiered for linking the software and archiving libraries. The crosscompiler arcitecture used to developing the software was i686, but the i386 build architecture should work aswell. [This OSdev.org tutorial](http://wiki.osdev.org/GCC_Cross-Compiler) will help you install a cross-compiler on your system.

**[NASM](http://www.nasm.us/)** - The *Netwide Assembler* is used to to assemble parts of the software. NASM or equivalent assembler is requiered to build the software, although nasm is the recommended one. You can install NASM throught your package manager or build from source via the NASM web page.

**[GRUB](https://www.gnu.org/software/grub/)** - The *GNU Grand Unified Bootloader* is used to bootstrap the software. You can install GRUB through your package manager or build it yourself via source code from the GRUB web page.

### Installing
1. Install the necessary prerequisites for building the software.
2. Download the files from the repository.
3. Change the *CROSSCOMPILERPATH* field in ***src/make.config*** to match the path of your installed cross-compiler. If you've installed any other cross-compiler than the one for the i686 arcitecture you have to manually change the appropriate fields in this file.
4. Whils in the ***src*** directory, build the software by running GNU make in the following manner.
    1. *make headers*
    2. *make objfiles*
    3. *make libs*
    4. *make os*
5. To generate a bootable disk image, run the following command in the repository root directory:
    > grub-mkrescue build/sysroot -o os.iso
  

## Authors
* **Mikael Henriksson** - *Code and testing* - [https://github.com/miklhh](https://github.com/miklhh)

Version: 1.3.1 <br />
Version Date: 2017-06-16

