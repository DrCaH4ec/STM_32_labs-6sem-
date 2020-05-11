#include "my_header.h"

#define FIRST_LED 				4
#define BUTTON 					13
#define DELAY					2000000
#define NUM_OF_LED				6

int main(void)
{
	init();
	
	while(1)
	{
		//waiting for button press
		while((GPIOC->IDR)&(1<<BUTTON));
		
		//action after button press
		for(uint8_t i = 0; i < NUM_OF_LED; ++i)
		{
			SET_BIT(GPIOA->BSRR, (1<<(i+FIRST_LED)));
			__delay(DELAY);
		}
		
		//turn off all leds after finishing of action
		GPIOA->BSRR = (0b111111 << 20);
		__delay(DELAY);
	}
}

