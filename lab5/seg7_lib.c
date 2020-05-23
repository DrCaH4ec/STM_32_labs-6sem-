#include "seg7_lib.h"

const uint8_t LED_MATRIX[32] ={
	0b00111111, //0
	0b00000110, //1
	0b01011011, //2
	0b01001111, //3
	0b01100110, //4
	0b01101101, //5
	0b01111101, //6
	0b00000111, //7
	0b01111111, //8
	0b01101111, //9
	0b01110111, //A(10)
	0b01111100, //b(11)
	0b00111001, //C(12)
	0b01011110, //d(13)
	0b01111001, //E(14)
	0b01110001, //F(15)
	0b01110110, //H(16)
	0b00110000, //I(17)
	0b00011110, //J(18)
	0b00111000, //L(19)
	0b01010100, //n(20)
	0b01110001, //P(21)
	0b01100111, //q(22)
	0b01010000, //r(23)
	0b01101101, //S(24)
	0b01111000, //t(25)
	0b00111110, //U(26)
	0b00011100, //v(27)
	0b01101110, //y(28)
	0b01000000, //"-"(29)
	0x00, // (30)
};

void OffDigits()
{
	DigitalWrite(A_PORT, A_N, CommonCA);
	DigitalWrite(B_PORT, B_N, CommonCA);
	DigitalWrite(C_PORT, C_N, CommonCA);
	DigitalWrite(D_PORT, D_N, CommonCA);
	DigitalWrite(E_PORT, E_N, CommonCA);
	DigitalWrite(F_PORT, F_N, CommonCA);
	DigitalWrite(G_PORT, G_N, CommonCA);
	DigitalWrite(H_PORT, H_N, CommonCA);
}

void PrintDigit(uint8_t val)
{
	if(val > 29)
		return;
	
	uint8_t tmp = CommonCA ? ~LED_MATRIX[val] : LED_MATRIX[val];
	
	DigitalWrite(A_PORT, A_N, tmp&(1<<0));
	DigitalWrite(B_PORT, B_N, tmp&(1<<1));
	DigitalWrite(C_PORT, C_N, tmp&(1<<2));
	DigitalWrite(D_PORT, D_N, tmp&(1<<3));
	DigitalWrite(E_PORT, E_N, tmp&(1<<4));
	DigitalWrite(F_PORT, F_N, tmp&(1<<5));
	DigitalWrite(G_PORT, G_N, tmp&(1<<6));		
}

void PrintNum(uint8_t val)
{
	PrintDigit(val/10);
	DigitalWrite(DIG_1_PORT, DIG_1_N, CommonCA);
	DigitalWrite(DIG_2_PORT, DIG_2_N, !CommonCA);
	_delay(50000);
	
	PrintDigit(val%10);
	DigitalWrite(DIG_1_PORT, DIG_1_N, !CommonCA);
	DigitalWrite(DIG_2_PORT, DIG_2_N, CommonCA);
	_delay(30000);	
	
	//OffDigits();
}
