#include "N76E003.h"

char putchar (char c)  
{
	while (!TI);
	TI = 0;
	return (SBUF = c);
}