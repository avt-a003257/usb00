#ifndef _TMR_H_
#define _TMR_H_

#include "common.h"

#define TMR0 0
#define TMR1 1
#define MOD_13B 0
#define MOD_16B 1
#define MOD_8B_RELOAD 2
#define MOD_8B_x2 3

void tmr0_isr(void) __interrupt (1);
void tmr0_init(void);
u32 get_clk(void);

#endif /* _TMR_H_ */

