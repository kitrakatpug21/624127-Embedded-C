/*
 * Relay Interfacing With ADC.c
 *
 * Created: 17-08-2022 11:51:18 AM
 * Author : kartik.iot
 */ 

#include <avr/io.h>
#define F_CPU 8000000UL
#include <util/delay.h>

int main(void)
{
	DDRC = 0b10001111;
	/*
	Relay at PC7, 
	Fans at PC0 and PC2
	*/
	ADMUX = 0b01000011;
	ADCSRA = 0b10000110;
	while (1)
	{
		ADCSRA = ADCSRA | 0b01000000;// 0b11000110;
		while ((ADCSRA & 0b00010000)==0)
		{
			// wait till conversion is complete
		}
		//Switch The Compressor and Fan(s) of the AC using ADC values
		if (ADC > 62 && ADC < 103)
		{
			// if temperature is beyond 30 Deg and within 50 Deg
			// turn both Compressor and FAN-1 and FAN-2 as ON
			PORTC = 0b10000101;
		}
		else if (ADC > 40 && ADC <= 62)
		{
			// if temperature is within 30 Deg and 20 Deg
			// turn both Compressor and FAN-1 as ON
			PORTC = 0b10000001;
		}
		else if (ADC > 24 && ADC <= 40)
		{
			// if temperature is within 20 Deg and 12 Deg
			// turn only FAN-1 as ON
			PORTC = 0b00000001;
		}
		else
		{
			// otherwise for remaining cases, everything will be turned off
			PORTC = 0b00000000;
		}
		_delay_ms(500);
	}
}

// 50Deg -> 103
// 30Deg -> 62
// 10Deg -> 21