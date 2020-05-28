#include <stdio.h>
#include <stdint.h>

#include "delay.h"

#include "digital_io.h"

#define CommonCA 0	//0 - common catode, 1 - common anode

#define A_PORT	GPIOA
#define A_N		10

#define B_PORT	GPIOB
#define B_N		3

#define C_PORT	GPIOB
#define C_N		5

#define D_PORT	GPIOB
#define D_N		4

#define E_PORT	GPIOB
#define E_N		10

#define F_PORT	GPIOA
#define F_N		8

#define G_PORT	GPIOA
#define G_N		9

#define H_PORT	GPIOC
#define H_N		7

#define DIG_1_PORT	GPIOB
#define DIG_1_N		6

#define DIG_2_PORT	GPIOA
#define DIG_2_N		7

#define DIG_3_PORT
#define DIG_3_N



void seg7_init();
void OffDigits();
void PrintDigit(uint8_t val);
void PrintNum(uint8_t val, uint8_t dig);

