#include "digital_io.h"



void DigitalWrite(GPIO_TypeDef *port, uint8_t pin, uint8_t value)
{
	if(pin > 15)
		return;
	
	port->BSRR |= value ? (1<<pin) : (1<<(pin+16));	
}



void GPIO_EN(uint8_t port)
{
	RCC->AHB1ENR |= (1<<port);
}



void PinMode(GPIO_TypeDef *port, uint8_t pin, uint8_t mode)
{
	if(pin > 15)
		return;
	
	port->MODER = (0x1&mode) ? (port->MODER|(1<<pin*2)) : (port->MODER&(~(1<<pin*2)));
	port->MODER = (mode>>1) ? (port->MODER|(1<<(pin*2+1))) : (port->MODER&(~(1<<(pin*2+1))));
}



void PinPull(GPIO_TypeDef *port, uint8_t pin, uint8_t mode)
{
	if(mode == 0b11 || pin > 15)
		return;
	
	port->PUPDR = (0x1&mode) ? (port->PUPDR|(1<<pin*2)) : (port->PUPDR&(~(1<<pin*2)));
	port->MODER = (mode>>1) ? (port->PUPDR|(1<<(pin*2+1))) : (port->PUPDR&(~(1<<(pin*2+1))));
}



uint8_t DigitalRead(GPIO_TypeDef *port, uint8_t pin)
{
	if(pin > 15)
		return;
	
	return port->IDR&(1<<pin);
}



void PinType(GPIO_TypeDef *port, uint8_t pin, uint8_t mode)
{
	port->OTYPER = mode ? (port->OTYPER|(1<<pin)) : (port->OTYPER&(~(1<<pin)));
}
