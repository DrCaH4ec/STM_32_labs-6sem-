#include "libs.h"


volatile uint8_t counter = 0;

void EXTI15_10_IRQHandler(void)
{
	EXTI->PR |= EXTI_PR_PR13;			//reset EXTI[13] interrupt
	NVIC_DisableIRQ(EXTI15_10_IRQn);	//disable EXTI[13] (for safety)
 
	counter = (counter >= 100) ? 0 : counter+1;							//action
	
	NVIC_EnableIRQ(EXTI15_10_IRQn);		//enable EXTI[13]
}


int main(void)
{
	//enable clock of GPIO
	GPIO_EN(GPIOA_en);
	GPIO_EN(GPIOB_en);
	GPIO_EN(GPIOC_en);
	
	//set pin mode
	PinMode(GPIOA, 4, GPIO_MODE);
	PinMode(GPIOA, 5, GPIO_MODE);
	PinMode(GPIOA, 6, GPIO_MODE);
	PinMode(GPIOA, 7, GPIO_MODE);
	PinMode(GPIOA, 8, GPIO_MODE);
	PinMode(GPIOA, 9, GPIO_MODE);
	PinMode(GPIOA, 10, GPIO_MODE);
	PinMode(GPIOB, 3, GPIO_MODE);
	PinMode(GPIOC, 0, GPIO_MODE);
	PinMode(GPIOC, 1, GPIO_MODE);
	PinMode(GPIOC, 13, INPUT_MODE);
	
	
	PinPull(GPIOC, 13, PU);	//I know that it's default value but it saver
	
	
	RCC->APB2ENR |= RCC_APB2ENR_SYSCFGEN;			//enable clock on necessary bus
	SYSCFG->EXTICR[3] |= SYSCFG_EXTICR4_EXTI13_PC;	//set EXTI[13] on GPIOC	
	EXTI->IMR |= (1<<13);							//enable EXTI[13]
	EXTI->FTSR |= (1<<13);							//interrupt of FALLING edge
	NVIC_EnableIRQ(EXTI15_10_IRQn);					//enable line of interrupt
	EXTI->PR |= EXTI_PR_PR13;						//reset EXTI[13] interrupt

	__enable_irq();									//enable global interrupts
	
	while(1)
	{	
		PrintNum(counter);	//main action
	}
}
