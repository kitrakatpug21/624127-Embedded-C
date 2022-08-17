/*
 * Sensor Interfacing using ADC.c
 *
 * Created: 16-08-2022 10:46:14 AM
 * Author : kartik.iot
 */ 

#include <avr/io.h>
#define F_CPU 8000000UL
#include <util/delay.h>

int main(void)
{
    DDRC = 0b11111111;
	DDRD = 0b00000011;
	ADMUX = 0b01000011;
	ADCSRA = 0b10000110;
	while (1) 
    {
		ADCSRA = ADCSRA | 0b01000000;// 0b11000110;
		while ((ADCSRA & 0b00010000)==0)
		{
			// wait till conversion is complete
		}
		PORTC = ADCL;
		PORTD = ADCH;
		_delay_ms(500);
    }
}

