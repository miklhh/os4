/* Paging header file */

#ifndef _PAGING_H
#define _PAGING_H

#include <stdint.h>

void paging_map_memory_to_phys(uint32_t virt, uint32_t phys);
void paging_enable();
void paging_init();

#endif
