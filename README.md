# OS4
Minimal hobby operating system written for the x86 architecture.

### Prerequisites
**[GNU Compiler Collection](https://gcc.gnu.org/)** - The *GNU Compiler Collection C (cross) compiler* is used for building the software. The *GNU Binary Utilities (binutils)* from GCC is also requiered for linking the software and archiving libraries. The compiler ouput arcitecture used for developing the software is i686 but the i386 build architecture should work aswell. [This OSdev.org tutorial](http://wiki.osdev.org/GCC_Cross-Compiler) will help you install a cross-compiler on your system.

**[NASM](http://www.nasm.us/)** - The *Netwide Assembler* is used to to assemble parts of the software. NASM or equivalent assembler is requiered to build the software although nasm is recommended. You can install NASM through your local maching package manager or build from source via the NASM web page.

**[GRUB](https://www.gnu.org/software/grub/)** - The *GNU Grand Unified Bootloader* is used to bootstrap the software. You can install GRUB through your package manager or build it yourself via source code from the GRUB web page.

### Installing
1. Install the necessary prerequisites for building the software.
2. Download the files from the repository.
3. Change the *CROSSCOMPILERPATH* field in ***src/make.config*** to match the path of your installed cross-compiler. If you've installed another cross-compiler than the i686 cross compiler, you have to manually change the appropriate fields in this file.
4. Whils in the ***src*** directory, build the software by running GNU make in the following manner.
    1. > *make headers*
    2. > *make objfiles*
    3. > *make libs*
    4. > *make os*
5. To generate a bootable disk image, run the following command in the repository root directory:
    > grub-mkrescue build/sysroot -o os.iso
    
### FAQ
**Q: GRUB doesn't work. I can't create a bootable diskimage.** </br>
You might need to install *xorriso* to use GRUB, since GRUB is dependant on that piece of software. You can install *xorriso* through most package mangagers.

**Q: QEMU produces an error message: *'Could not read from CD-ROM (code 0009)'* when i try to emulate the software.** </br>
> If your development system is booted from EFI it may be that you don't have the PC-BIOS version of the grub binaries installed anywhere. If you install them then grub-mkrescue will by default produce a hybrid ISO that will work in QEMU. On Ubuntu this can be achieved with: apt-get install grub-pc-bin.
> -- <cite>[FAQ on 'Bare Bones' on OSDev.org (2017-06-17)][1]</cite>
    

## Authors
* **Mikael Henriksson** - *Code and testing* - [https://github.com/miklhh](https://github.com/miklhh)

## License
This project is licensed under MIT License - see the [LICENSE.txt](LICENSE.txt) for more details.

Version: 1.3.2 <br />
Version Date: 2017-07-17

[1]:http://wiki.osdev.org/Bare_bones#Frequently_Asked_Questions

