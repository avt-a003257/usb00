#include "uart.h"
//#include "tmr.h"

static unsigned char is_tx_busy = 0;

void uart_isr(void) __interrupt (4) // __using (1)
{
	char c = SBUF;

	if (RI) {
		RI = 0;
		printf("%c", c);
		if ('\r' == c)
			printf("\n");
	}

	if (TI) {
		TI = 0;
		is_tx_busy = 0;
	}
}

void uart_init(u32 baudrate)
{
#if ((PARITY_BIT == PARITY_ODD) || \
     (PARITY_BIT == PARITY_EVEN) || \
     (PARITY_BIT == PARITY_MARK))
	SCON = 0xDA;
#elif (PARITY_BIT == PARITY_SPACE)
	SCON = 0xD2;
#else /* PARITY_NONE */
	SCON = 0x50;
#endif

	TMOD &= 0x0F; /* set timer 1 as mode 2, autoload */
	TMOD |= 0x20;
//	TH1 = TL1 = 256 - (FCLK / (12 * 16 * baudrate));
	TH1 = TL1 = 256 - (FCLK / 12 / 16 / baudrate);
//	tmr1_init(MOD_8B_RELOAD, 
//		  256 - (FCLK / 12 / 16 / baudrate), 0);
	PCON |= 0x80;
	ES = 1; /* enable uart interrupt */
	TR1 = 1; /* start timer 1 */
	REN = 1; /* enable input */
}

int putchar(int c)
{
	while (is_tx_busy);

	ACC = c; /* calculate parity */

	if (P) {
#if (PARITY_BIT == PARITY_ODD)
		TB8 = 0;
#elif (PARITY_BIT == PARITY_EVEN)
		TB8 = 1;
#endif
	} else {
#if (PARITY_BIT == PARITY_ODD)
		TB8 = 1;
#elif (PARITY_BIT == PARITY_EVEN)
		TB8 = 0;
#endif

	}

	is_tx_busy = 1;
	return (SBUF = ACC);
}



