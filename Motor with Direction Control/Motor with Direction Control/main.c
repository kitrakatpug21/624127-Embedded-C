/*
 * Motor with Direction Control.c
 *
 * Created: 04-08-2022 02:44:38 PM
 * Author : kartik.iot
 */ 

#include <avr/io.h>
#define F_CPU 8000000UL
#include <util/delay.h>

int main(void)
{
    DDRA = 0b11000011;
	while (1) 
    {
		PORTA = 0b00000001; //MOTOR M1 is Anti-Clock, M2 is OFF
		_delay_ms(2000);
		PORTA = 0b00000010; //MOTOR M2 is Anti-Clock, M1 is OFF
		_delay_ms(2000);
		PORTA = 0b00000011; //MOTOR M1 is Anti-Clock, M2 is Anti-Clock
		_delay_ms(2000);
		PORTA = 0b00000000; //MOTOR M1 is OFF, M2 is OFF
		_delay_ms(2000);
		
		PORTA = 0b01000000; //MOTOR M1 is Clock, M2 is OFF
		_delay_ms(2000);
		PORTA = 0b10000000; //MOTOR M2 is Clock, M1 is OFF
		_delay_ms(2000);
		PORTA = 0b11000000; //MOTOR M1 is Clock, M2 is Clock
		_delay_ms(2000);
		PORTA = 0b00000000; //MOTOR M1 is OFF, M2 is OFF
		_delay_ms(2000);
    }
}


