//#include "stc89c5xrc.h"
#include "N76E003.h"
#include "Common.h"
#include "Delay.h"
#include "SFR_Macro.h"
#include "Function_Define.h"

void main(void)
{
	Set_All_GPIO_Quasi_Mode;
	while (1)
	{
		P12 = !P12;
		Timer1_Delay10ms(5);
	}
}
	
