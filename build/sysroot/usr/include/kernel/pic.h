/*
 * Part of OS4, pic.h
 * Author: Mikael Henriksson, miklhh
 */

#ifndef _PIC_H
#define _PIC_H

void pic_init();
void pic_send_eoi(uint8_t irq);

#endif
