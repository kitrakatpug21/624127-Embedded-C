/*
 * 7Segment using Switch.c
 *
 * Created: 03-08-2022 03:18:21 PM
 * Author : kartik.iot
 */ 

#include <avr/io.h>
#define F_CPU 8000000UL
#include <util/delay.h>

uint8_t segment[10] = { 0b00111111,// digit 0
						0b00000110,// digit 1
						0b01011011,// digit 2
						0b01001111,// digit 3
						0b01100110,// digit 4
						0b01101101,// digit 5
						0b01111101,// digit 6
						0b00000111,// digit 7
						0b01111111,// digit 8
						0b01101111 };// digit 9

int main(void)
{
	DDRA = 0b00000000;// PA0-PA7 are Input
	DDRC = 0b01111111;// PC0-PC6 are OUTPUT for 7 segment
	int count = 0;
	while (1) 
    {
		if (PINA & (0b00000001))
		{
			if (count == 9)
				count = 0;
			else
				count = count + 1;
			_delay_ms(300);
		}
		else if (PINA & (0b10000000))
		{
			if (count == 0)
				count = 9;
			else
				count = count - 1;
			_delay_ms(300);
		}
		PORTC = segment[count];
    }
}

