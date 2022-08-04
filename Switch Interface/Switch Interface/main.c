/*
 * Switch Interface.c
 *
 * Created: 03-08-2022 02:47:08 PM
 * Author : kartik.iot
 */ 

#include <avr/io.h>
#define F_CPU 8000000UL
#include <util/delay.h>

int main(void)
{
	DDRA = 0b00000000;// PA0-PA7 are Input
	DDRC = 0b00001111;// PC0-PC3 are OUTPUT
	while (1) 
    {
		if (PINA & (0b00000001))
		{
			PORTC = 0b00000011;
		}
		else if (PINA & (0b10000000))
		{
			PORTC = 0b00001100;
		}
		else
		{
			PORTC = 0b00000000;
		}
    }
}

