#include "tmr.h"

#define PERIOD 100 /* 1s/interrupt */
#define REGVAL (65535 - FCLK / 1000 / 12 * PERIOD) 

static volatile u32 g_clk;

void tmr0_isr(void) __interrupt (1)
{
	++g_clk;
	TH0 = (u8)((u32) REGVAL >> 8); 
	TL0 = REGVAL & 0xFF;
}

/** default use for global clock
 */
void tmr0_init(void)
{
	TMOD &= 0xF0; /* set tmr0 as mode 1 */
	TMOD |= MOD_16B;
	TH0 = (u8)((u32) REGVAL >> 8); 
	TL0 = REGVAL & 0xFF;
	ET0 = 1; /* enable tmr0 interrupt */
	TR0 = 1; /* start tmr0 */
}

u32 get_clk(void)
{
	u32 val = 0;

	EA = 0;
	val = g_clk;
	EA = 1;

	return val;
}

