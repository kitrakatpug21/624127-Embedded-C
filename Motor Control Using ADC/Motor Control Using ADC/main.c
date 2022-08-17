/*
 * Motor Control Using ADC.c
 *
 * Created: 16-08-2022 11:41:53 AM
 * Author : kartik.iot
 */ 

#include <avr/io.h>
#define F_CPU 8000000UL
#include <util/delay.h>

int main(void)
{
    DDRC = 0b11000011;
	ADMUX = 0b01000011;
	ADCSRA = 0b10000110;
	while (1) 
    {
		ADCSRA = ADCSRA | 0b01000000;// 0b11000110;
		while ((ADCSRA & 0b00010000)==0)
		{
			// wait till conversion is complete
		}
		if (ADC > 700)
		{
			PORTC = 0b01000001;// both motor turn on
		}
		else if (ADC > 400 && ADC <= 700)
		{
			PORTC = 0b00000001;// motor1 is on, motor 2 is off
		}
		else if (ADC > 100 && ADC <= 400)
		{
			PORTC = 0b01000000;// motor1 is off, motor 2 is on
		}
		else
		{
			PORTC = 0b00000000;// both motor turn off
		}
		_delay_ms(500);
    }
}

