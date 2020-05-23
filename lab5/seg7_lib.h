#include <stdio.h>
#include <stdint.h>

#include "delay.h"

#include "digital_io.h"

#define CommonCA 0	//0 - common catode, 1 - common anode

#define A_PORT	GPIOA
#define A_N		4

#define B_PORT	GPIOA
#define B_N		5

#define C_PORT	GPIOA
#define C_N		6

#define D_PORT	GPIOA
#define D_N		7

#define E_PORT	GPIOA
#define E_N		8

#define F_PORT	GPIOA
#define F_N		9

#define G_PORT	GPIOA
#define G_N		10

#define H_PORT	GPIOB
#define H_N		3

#define DIG_1_PORT	GPIOC
#define DIG_1_N		0

#define DIG_2_PORT	GPIOC
#define DIG_2_N		1

#define DIG_3_PORT
#define DIG_3_N




void OffDigits();
void PrintDigit(uint8_t val);
void PrintNum(uint8_t val);

