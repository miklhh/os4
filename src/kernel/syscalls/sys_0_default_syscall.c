/*
 * Part of OS4, sys_0_test_syscall.c
 * Author: Mikael Henriksson
 */

#include <kstdio.h>
#include <stdint.h>

uint32_t sys_0_default_syscall()
{
    kprintf("Default syscall called. Did you do something wrong?\n");
    return 0x1337;
}
