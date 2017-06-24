/*
 * Part of OS4, fat.h
 * Author: Mikael Henriksson miklhh
 */

#ifndef
#define _FAT_H

#include <stdint.h>

struct __attribute__((packed)) fat32_bootblock {


    uint32_t sectors_per_fat;       // Sectors per FAT.
    uint16_t flags;                 // Flags.
    uint8_t fatver;                 // Fat version.
    uint32_t root_cluster;          // Cluster number of root dir.
    uint16_t fs_info_sector;        // 
    uint16_t backup_boot_sector;    // Backup boot sector.
    uint8_t reserved[12];           // Reserver, should be zero.
    uint8_t logical_drive;          // Drive number.
    uint8_t unused;                 // Unused (used by windows NT).
    uint8_t ext_sig;                // Signature (must be 0x28 or 0x29).
    uint32_t volume_serial;         // Volume serial number.
    uint8_t volume_label[11];       // Volume label string.
    uint8_t file_system[8];         // System identifier string. Always "FAT32   ".
    uint8_t boot_code[420];         // Bootcode.
    uint16_t signature;             // Bootsignature (0xAA55).
} fat32_bootblock_t;


#endif
