/*
 * Motor Car Using Switch.c
 *
 * Created: 04-08-2022 03:10:08 PM
 * Author : kartik.iot
 */ 

#include <avr/io.h>
#define F_CPU 8000000UL
#include <util/delay.h>

int main(void)
{
    DDRA = 0b11000011;// Motor 
	DDRC = 0b00000000;// Switch is Connected Here at PC0
	int count = 0;
	while (1) 
    {
		if (PINC & (0b00000001))
		{
			while(PINC & (0b00000001))
			{
				// wait here for debouncer
			}
			
			if (count == 4)
				count = 0;
			else
				count = count + 1;
		}
		if (count == 1)
		{
			PORTA = 0b11000000; //MOTOR M1 and M2 Forward
		}
		else if (count == 2)
		{
			PORTA = 0b00000011; //MOTOR M1 and M2 Backward
		}
		else if (count == 3)
		{
			PORTA = 0b01000000; //MOTOR M1 is Forward and M2 OFF
		}
		else if (count == 4)
		{
			PORTA = 0b10000000; //MOTOR M2 is Forward and M1 OFF
		}
		else
		{
			PORTA = 0b00000000; //MOTOR M2 and M1 OFF
		}
	}
}


