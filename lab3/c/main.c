#include <stdint.h>

#define RCC_AHB1ENR 			(uint32_t*)0x40023830
#define GPIOA_MODER		 		(uint32_t*)0x40020000
#define GPIOA_BSRR 				(uint32_t*)0x40020018
#define GPIOC_PUPDR				(uint32_t*)0x4002080C
#define GPIOC_IDR				(uint32_t*)0x40020810

#define FIRST_LED 				4
#define BUTTON 					13


void delay();

int main(void)
{
	*RCC_AHB1ENR = 0b101;	//enable clock on GPIOA and GPIOC
	
	//set PA[4-9] to output
	*GPIOA_MODER &= ~(1 << ((FIRST_LED+0)*2 + 1));
	*GPIOA_MODER |= (1 << (FIRST_LED+0)*2);
	*GPIOA_MODER &= ~(1 << ((FIRST_LED+1)*2 + 1));
	*GPIOA_MODER |= (1 << (FIRST_LED+1)*2);
	*GPIOA_MODER &= ~(1 << ((FIRST_LED+2)*2 + 1));
	*GPIOA_MODER |= (1 << (FIRST_LED+2)*2);
	*GPIOA_MODER &= ~(1 << ((FIRST_LED+3)*2 + 1));
	*GPIOA_MODER |= (1 << (FIRST_LED+3)*2);
	*GPIOA_MODER &= ~(1 << ((FIRST_LED+4)*2 + 1));
	*GPIOA_MODER |= (1 << (FIRST_LED+4)*2);
	*GPIOA_MODER &= ~(1 << ((FIRST_LED+5)*2 + 1));
	*GPIOA_MODER |= (1 << (FIRST_LED+5)*2);
	
	//set pull-up on PC13
	*GPIOC_PUPDR |= (1 << BUTTON*2);
	*GPIOC_PUPDR &= ~(1 << (BUTTON*2 + 1));
	
	
	while(1)
	{
		
		while((*GPIOC_IDR)&(1<<BUTTON));	//waiting for button press
		
		//action after button press
		for(uint8_t i = 0; i < 6; i++)
		{
			*(uint32_t*)GPIOA_BSRR = (1 << (i+FIRST_LED));
			delay();
		}
		
		//turn off all leds after finishing of action
		*(uint32_t*)GPIOA_BSRR = (0b111111 << 20);
		delay();
	}
	
}


void delay()
{
	for(uint32_t i = 0; i < 1500000; i++);
}
