/*
 * LED Matrix.c
 *
 * Created: 10-08-2022 10:40:59 AM
 * Author : kartik.iot
 */ 

#include <avr/io.h>
#define F_CPU 8000000UL
#include <util/delay.h>

int main(void)
{
    DDRC = 0b01110111;
	while (1) 
    {
		PORTC = 0b01100100;// D1
		_delay_ms(1000);
		PORTC = 0b01100010;// D2
		_delay_ms(1000);
		PORTC = 0b01100001;// D3
		_delay_ms(1000);
		PORTC = 0b01010100;// D4
		_delay_ms(1000);
		PORTC = 0b01010010;// D5
		_delay_ms(1000);
		PORTC = 0b01010001;// D6
		_delay_ms(1000);
		PORTC = 0b00110100;// D7
		_delay_ms(1000);
		PORTC = 0b00110010;// D8
		_delay_ms(1000);
		PORTC = 0b00110001;// D9
		_delay_ms(1000);
    }
}

