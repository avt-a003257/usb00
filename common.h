/** common.h: shared definitions, inclusions for usb00 board
 */

#ifndef _COMMON_H_
#define _COMMON_H_

#include <stdio.h>
#include <string.h>
#include "stc89c5xrc.h"

#define FCLK 22118400UL /* Hz */

#ifdef DBG
//#define dbg(s, b...) printf("[%010ld] " s, g_clk, ##b)
#define dbg(s, b...) printf("[%s] " s, __func__, ##b)
#else
#define dbg(s, b...)
#endif

//#define err(s, b...) printf("[%010ld] ERR " s, g_clk, ##b)

/* sdcc provided basic data types
 * char: 1 byte
 * short, int: 2 bytes
 * long: 4 bytes
 * float: 4 bytes
 */
typedef unsigned char bool;
typedef unsigned char u8;
typedef char s8;
//typedef unsigned short u16;
typedef unsigned int u16;
typedef int s16;
typedef unsigned long u32;
typedef long s32;

enum {
	FALSE,
	TRUE
};

struct _isr_status {
	u8 usbd12_intreg[2];
};

extern struct _isr_status g_isr;

void delayms(u16);

#endif

