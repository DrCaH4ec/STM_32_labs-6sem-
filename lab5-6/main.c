#include "libs.h"


volatile uint8_t counter = 0;

volatile uint32_t DelayCount = 0;

volatile uint8_t dig = 0;

volatile uint8_t DigCount = 0;

void EXTI15_10_IRQHandler(void)
{
	EXTI->PR |= EXTI_PR_PR13;			//reset EXTI[13] interrupt
	NVIC_DisableIRQ(EXTI15_10_IRQn);	//disable EXTI[13] (for safety)
 

	counter = (counter >= 99) ? 0 : counter+1;							//action

	
	NVIC_EnableIRQ(EXTI15_10_IRQn);		//enable EXTI[13]
}


void SysTick_Handler(void)
{
	if(DelayCount > 0)
		DelayCount--;
	
	if(DigCount == 10){
		PrintNum(counter, dig);
		dig = !dig;
		
		DigCount = 0;
	}
	
	DigCount++;
}


void _delay_ms(uint32_t delay)
{
	DelayCount = delay;
	
	while(DelayCount);
}


int main(void)
{
	
	SysTick_Config(SystemCoreClock/1000);
	
	
	//enable clock of GPIO
	GPIO_EN(GPIOA_en);
	GPIO_EN(GPIOB_en);
	GPIO_EN(GPIOC_en);

	seg7_init();
	
	PinMode(GPIOC, 13, INPUT_MODE);	//I know that it's default value but it saver
	PinPull(GPIOC, 13, PU);	//set pull-up
	
	PinMode(GPIOC, 0, GPIO_MODE);
	
	
	RCC->APB2ENR |= RCC_APB2ENR_SYSCFGEN;			//enable clock on necessary bus
	SYSCFG->EXTICR[3] |= SYSCFG_EXTICR4_EXTI13_PC;	//set EXTI[13] on GPIOC	
	EXTI->IMR |= (1<<13);							//enable EXTI[13]
	EXTI->FTSR |= (1<<13);							//interrupt of FALLING edge
	NVIC_EnableIRQ(EXTI15_10_IRQn);					//enable line of interrupt
	EXTI->PR |= EXTI_PR_PR13;						//reset EXTI[13] interrupt

	
	NVIC_EnableIRQ(SysTick_Handler);				//enable SysTick interrupt


	__enable_irq();									//enable global interrupts
	
	while(1)
	{	
		DigitalWrite(GPIOC, 0, HIGH);
		_delay_ms(500);
		DigitalWrite(GPIOC, 0, LOW);
		_delay_ms(500);		
	}
}
