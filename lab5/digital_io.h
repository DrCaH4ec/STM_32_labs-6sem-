#include <stdio.h>
#include <stdint.h>
#include <stm32f4xx.h>


#define HIGH	1
#define LOW		0



#define GPIOA_en 0
#define GPIOB_en 1
#define GPIOC_en 2
#define GPIOD_en 3

void GPIO_EN(uint8_t port);

void DigitalWrite(GPIO_TypeDef *port, uint8_t pin, uint8_t value);


#define INPUT_MODE 			0b00
#define GPIO_MODE			0b01
#define ALT_FUNK_MODE		0b10
#define ANALOG_MODE			0b11

void PinMode(GPIO_TypeDef *port, uint8_t pin, uint8_t mode);


#define NPUPD 	0b00 //no pull-up, pull-down
#define PU		0b01 //pull-up
#define PD		0b10 //pull-down

void PinPull(GPIO_TypeDef *port, uint8_t pin, uint8_t mode);

uint8_t DigitalRead(GPIO_TypeDef *port, uint8_t pin);

#define PUSH_PULL	0
#define OPEN_DRAIN	1

void PinType(GPIO_TypeDef *port, uint8_t pin, uint8_t mode);
