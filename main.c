//#include "stc89c5xrc.h"
#include "N76E003.h"
#include "Common.h"
#include "Delay.h"
#include "SFR_Macro.h"
#include "Function_Define.h"
#include "usbd12.h"

void main(void)
{
	__xdata unsigned char buf[128];
	Set_All_GPIO_Quasi_Mode;
	InitialUART0_Timer3(115200);
	printf("usb00: %s %s\r\n", __TIME__, __DATE__);

	while (1)
	{
		P12 = !P12;
		Timer1_Delay10ms(50);
		printf("ID: %04x\r\n", usbd12_read_id());
	}
}
	
