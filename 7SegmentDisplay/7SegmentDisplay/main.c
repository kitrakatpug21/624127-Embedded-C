/*
 * 7SegmentDisplay.c
 *
 * Created: 01-08-2022 02:53:29 PM
 * Author : kartik.iot
 */ 

#include <avr/io.h>
#define F_CPU 8000000UL
#include <util/delay.h>

int main(void)
{
// sevenSeg  .gfedcba
    DDRC = 0b01111111;
    while (1) 
    {
		PORTC = 0b00111111;// digit 0
		_delay_ms(1000);
		PORTC = 0b00000110;// digit 1
		_delay_ms(1000);
		PORTC = 0b01011011;// digit 2
		_delay_ms(1000);
		PORTC = 0b01001111;// digit 3
		_delay_ms(1000);
		PORTC = 0b01100110;// digit 4
		_delay_ms(1000);
		PORTC = 0b01101101;// digit 5
		_delay_ms(1000);
		PORTC = 0b01111101;// digit 6
		_delay_ms(1000);
		PORTC = 0b00000111;// digit 7
		_delay_ms(1000);
		PORTC = 0b01111111;// digit 8
		_delay_ms(1000);
		PORTC = 0b01101111;// digit 9
		_delay_ms(1000);
    }
}