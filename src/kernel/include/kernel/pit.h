/*
 * Part of OS4, pit.h
 * Author: Mikael Henriksson, miklhh
 */

#ifndef _PIT_H
#define _PIT_H

void pit_init();

/* PIT tick-rate constant */
#define PIT_TICK_RATE 1000

/* PIT Macros */
#define PIT_REG_COUNTER0 0x40
#define PIT_REG_COUNTER1 0x41
#define PIT_REG_COUNTER2 0x42
#define PIT_REG_COMMAND  0x43

#define PIT_OCW_MASK_BINCOUNT 	1
#define PIT_OCW_MASK_MODE 	0xE
#define PIT_OCW_MASK_RL 	0x30
#define PIT_OCW_MASK_COUNTER	0xC0

#define PIT_OCW_BINCOUNT_BINARY 0
#define PIT_OCW_BINCOUNT_BCD 	1

#define PIT_OCW_MODE_TERMINALCOUNT 	0
#define PIT_OCW_MODE_ONESHOT 		0x2
#define PIT_OCW_MODE_RATEGEN 		0x4
#define PIT_OCW_MODE_SQUAREWAVEGEN 	0x6
#define PIT_OCW_MODE_SOFTWARETRIG 	0x8
#define PIT_OCW_MODE_HARDWARETRIG 	0xA

#define PIT_OCW_RL_LATCH 	0
#define PIT_OCW_RL_LSBONLY 	0x10
#define PIT_OCW_RL_MSBONLY 	0x20
#define PIT_OCW_RL_DATA 	0x30

#define PIT_OCW_COUNTER_0 0
#define PIT_OCW_COUNTER_1 0x40
#define PIT_OCW_COUNTER_2 0x80

#endif
