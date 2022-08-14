/*
 * LED Matrix with Keypad.c
 *
 * Created: 10-08-2022 11:03:54 AM
 * Author : kartik.iot
 */ 

#include <avr/io.h>
#define F_CPU 8000000UL
#include <util/delay.h>

int main(void)
{
	DDRA = 0b00000111;// KEYPAD
	DDRC = 0b01110111;// LEDs
	while (1)
	{
		PORTA = 0b00000001;// Set PA0 as +5V
		if (PINA & 0b00010000)
		{
			PORTC = 0b01100100;// D1
		}
		else if (PINA & 0b00100000)
		{
			PORTC = 0b01010100;// D4
		}
		else if (PINA & 0b01000000)
		{
			PORTC = 0b00110100;// D7
		}
		else if (PINA & 0b10000000)
		{
			PORTC = 0b00000111;// all on
		}
		_delay_ms(150);
		PORTA = 0b00000010;// Set PA2 as +5V
		if (PINA & 0b00010000)
		{
			PORTC = 0b01100010;// D2
		}
		else if (PINA & 0b00100000)
		{
			PORTC = 0b01010010;// D5
		}
		else if (PINA & 0b01000000)
		{
			PORTC = 0b00110010;// D8
		}
		_delay_ms(150);
		PORTA = 0b00000100;// Set PA3 as +5V
		if (PINA & 0b00010000)
		{
			PORTC = 0b01100001;// D3
		}
		else if (PINA & 0b00100000)
		{
			PORTC = 0b01010001;// D6
		}
		else if (PINA & 0b01000000)
		{
			PORTC = 0b00110001;// D9
		}
		else if (PINA & 0b10000000)
		{
			PORTC = 0b00000000;// all off
		}
		_delay_ms(150);		
	}
}

