#include "delay.h"

void _delay(uint32_t i)
{
	while(i)
		--i;
}