#include "extint.h"
#include "usbd12.h"

void extint0_isr(void) __interrupt (0)
{
	usbd12_write_byte(CMD, READ_INT_REG);
	g_isr.usbd12_intreg[0] = usbd12_read_byte();
	g_isr.usbd12_intreg[1] = usbd12_read_byte();
//	usbd12_write_byte(CMD, READ_LAST_TRANSACT_STATUS_REG);
//	usbd12_read_byte();
}

#if 0
void extint1_isr(void) __interrupt (2)
{
}
#endif

void extint_init(u8 pin, u8 trigger_type)
{
	if (INT0 == pin) {
		IT0 = trigger_type;
		EX0 = 1;
	}

	if (INT1 == pin) {
		IT1 = trigger_type;
		EX1 = 1;
	}
}

