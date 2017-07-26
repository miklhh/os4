/*
 * Part of OS4, kernel.c
 * Author Mikael Henriksson, miklhh
 */

#include <memory/paging.h>
#include <memory/memory.h>
#include <kstdio.h>
#include <stdio.h>
#include <driver/tty.h>
#include <driver/keyboard.h>
#include <kernel/gdt.h>
#include <kernel/idt.h>
#include <kernel/pic.h>
#include <kernel/timer.h>
#include <kernel/syscall.h>
#include <kernel/exceptions.h>
#include <task/task.h>
#include <kernel/ksleep.h>
#include <system/cpuid.h>
#include <string.h>

extern uint32_t __kernel_start;
extern uint32_t __kernel_end;
extern uint32_t interrupt_stack_top;

void kernel_main(void)
{
    // Initialize terminal, for being able to write.
    terminal_init();

    // Initialize the GDT.
    gdt_init();
    
    // Initialize the IDT.
    idt_init();

    // Initialize exeptions.
    exceptions_init();
    
    // Initalize the heap data.
    mm_init(&__kernel_end);
    
    // Initialize the paging.
    paging_init();

    // Initialize the PIC
    pic_init();

    // Initialze timer.
    timer_init();

    // Initialize system calls.
    syscall_init();

    // Print kernel start and kernel end.
    kprintf("Kernel start: %x, and kernel end: %x\n", &__kernel_start, &__kernel_end);

    // Initialize keyboard driver.
    keyboard_init();

    // Test if the CPUID instructions works.
    if (test_cpuid())
    {
        kprintf("CPUID-instruction available.\n");
        uint32_t a, b, c, d;
        __cpuid(0, a, b, c, d);
        kprintf("EAX: %x\nEBX: %x\nECX: %x\nEDX: %x\n", a, b, c, d);
        print_vendor_label_kstdio();
        kprintf("\n");
    }
    else
    {
        kprintf("CPUID-instriction NOT availabe.\n");
    }


    /* ------------------------------------------------ */
    set_kernel_stack((uint32_t) &interrupt_stack_top);
    //switch_to_user_mode();
    interrupt_enable();

    // Test a systemcall
    asm volatile(
        "movl $0, %%eax     \n"
        "int $0x80          \n"
        :
        :
        : "eax");
    uint32_t returnvalue = 0;
    asm volatile(
        "movl %%eax, %0"
        : "=r"(returnvalue)
        :
        :);
    kprintf("Return value: %x\n", returnvalue);

    /* Test user-land printf. */
    printf("Userland printf printing!\n");

    task_enable();
    kprintf("Returned to kernel main.\n");
    /*
    while(1)
    {
        kprintf("Hello world!\n");
        ksleep(1000);
    }
    */


    // Keyboard.
    //task_fork();
    while (1)
    {
        char c = keyboard_get_key();
        if (c)
        {
            putchar(c);
        }
        kprintf("Task nr: %u\n", task_get_id());
    // Sleep 20ms.
    asm volatile(
        "movl $2, %%eax     \n"
        "movl $20, %%ebx  \n"
        "int $0x80          \n"
        : "=r"(returnvalue)
        :
        : "eax", "ebx");
    }
}
