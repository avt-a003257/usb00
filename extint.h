#ifndef _EXTINT_H_
#define _EXTINT_H_

#include "common.h"

/* pin */
#define INT0 0
#define INT1 1

/* trigger_type */
#define TRIGGER_FALLING_EDGE 1
#define TRIGGER_LOW_LEVEL 0

void extint_init(u8 pin, u8 trigger_type);
void extint0_isr(void) __interrupt (0);
#if 0
void extint1_isr(void) __interrupt (2);
#endif

#endif /* _EXTINT_H_ */

