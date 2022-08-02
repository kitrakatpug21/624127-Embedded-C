/*
 * 7SegmentMatrix.c
 *
 * Created: 02-08-2022 02:37:35 PM
 * Author : kartik.iot
 */ 

#include <avr/io.h>
#define F_CPU 8000000UL
#include <util/delay.h>

int main(void)
{
	// sevenSeg  .gfedcba
	DDRC = 0b01111111;
	DDRD = 0b00001111;
	
	uint8_t segment[10];
	segment[0] = 0b00111111;// digit 0
	segment[1] = 0b00000110;// digit 1
	segment[2] = 0b01011011;// digit 2
	segment[3] = 0b01001111;// digit 3
	segment[4] = 0b01100110;// digit 4
	segment[5] = 0b01101101;// digit 5
	segment[6] = 0b01111101;// digit 6
	segment[7] = 0b00000111;// digit 7
	segment[8] = 0b01111111;// digit 8
	segment[9] = 0b01101111;// digit 9
	
	while (1)
	{
		PORTD = 0b00001110;//PD0 -> ON PD1,2,3 -> OFF
		PORTC = segment[3];
		_delay_ms(10);
		PORTD = 0b00001101;//PD1 -> ON PD0,2,3 -> OFF
		PORTC = segment[5];
		_delay_ms(10);
		PORTD = 0b00001011;//PD2 -> ON PD0,1,3 -> OFF
		PORTC = segment[7];
		_delay_ms(10);
		PORTD = 0b00000111;//PD3 -> ON PD0,1,2 -> OFF
		PORTC = segment[9];
		_delay_ms(10);
		
		
		/*for (int tens = 0; tens <= 9; tens = tens + 1)
		//{
			for (int ones = 0; ones <= 9; ones = ones + 1)
			{
				PORTC = segment[ones];
				//PORTD = segment[tens];
				_delay_ms(1000);
			}
		//}*/
	}
}