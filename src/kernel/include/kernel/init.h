/*
 * Part of OS4, init.h
 * Author: Mikael Henriksson, miklhh
 */

#ifndef _KERNEL_INIT_H
#define _KERNEL_INIT_H

/* Multiboot information structure. */
typedef struct multiboot __attribute__((packed)) {
    uintptr_t flags;
    uintptr_t mem_lower;
    uintptr_t mem_upper;
    uintptr_t boot_device;
    uintptr_t cmdline;
    uintptr_t mods_count;
    uintptr_t mods_addr;
    uintptr_t num;
    uintptr_t size;
    uintptr_t addr;
    uintptr_t shndx;
    uintptr_t mmap_length;
    uintptr_t mmap_addr;
    uintptr_t drives_length;
    uintptr_t drives_addr;
    uintptr_t config_table;
    uintptr_t boot_loader_name;
    uintptr_t apm_table;
    uintptr_t vbe_control_info;
    uintptr_t vbe_mode_info;
    uintptr_t vbe_mode;
    uintptr_t vbe_interface_seg;
    uintptr_t vbe_interface_off;
    uintptr_t vbe_interface_len;
} multiboot_t;

#endif
