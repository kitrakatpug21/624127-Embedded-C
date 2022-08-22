/*
 * Ultrasonic Sensor.c
 *
 * Created: 22-08-2022 10:51:29 AM
 * Author : kartik.iot
 */ 

#include <avr/io.h>
#define F_CPU 8000000UL
#include <util/delay.h>
//#########################//
#include <avr/interrupt.h>
#include <string.h>
#include <stdlib.h>
//#########################//

#define  Trigger_pin    PA0 /* Trigger pin */

int TimerOverflow = 0;

ISR(TIMER1_OVF_vect)
{
	TimerOverflow++;    /* Increment Timer Overflow count */
}

void lcd_config(uint8_t cmd)
{
	// FIRST PART OF 8-bit Data
	//1. Upload the character on PORTC
	PORTC = (PORTC & 0x0F) | (cmd & 0xF0);// msb will load first
	//2. Set RS Pin to 0
	PORTC = PORTC & ~(0b00000001);	// Set RS Pin to 0
	//3. Generate a Latch signal 0-1-0
	PORTC = PORTC | 0b00000010;	// Set EN Pin to 1
	_delay_ms(10);
	PORTC = PORTC & ~(0b00000010);	// Set EN Pin to 0
	_delay_ms(10);
	// SECOND PART OF 8-bit Data
	//1. Upload the character on PORTC
	PORTC = (PORTC & 0x0F) | ((cmd<<4) & 0xF0);// lsb will load first
	//2. Set RS Pin to 0
	PORTC = PORTC & ~(0b00000001);	// Set RS Pin to 0
	//3. Generate a Latch signal 0-1-0
	PORTC = PORTC | 0b00000010;	// Set EN Pin to 1
	_delay_ms(10);
	PORTC = PORTC & ~(0b00000010);	// Set EN Pin to 0
	_delay_ms(10);
}
void lcd_character(char ch)
{
	// FIRST PART OF 8-bit Data
	//1. Upload the character on PORTC
	PORTC = (PORTC & 0x0F) | (ch & 0xF0);// msb will load first
	//2. Set RS Pin to 1
	PORTC = PORTC | 0b00000001;	// Set RS Pin to 1
	//3. Generate a Latch signal 0-1-0
	PORTC = PORTC | 0b00000010;	// Set EN Pin to 1
	_delay_ms(10);
	PORTC = PORTC & ~(0b00000010);	// Set EN Pin to 0
	_delay_ms(10);
	// SECOND PART OF 8-bit Data
	//1. Upload the character on PORTC
	PORTC = (PORTC & 0x0F) | ((ch<<4) & 0xF0);// lsb will load first
	//2. Set RS Pin to 1
	PORTC = PORTC | 0b00000001;	// Set RS Pin to 1
	//3. Generate a Latch signal 0-1-0
	PORTC = PORTC | 0b00000010;	// Set EN Pin to 1
	_delay_ms(10);
	PORTC = PORTC & ~(0b00000010);	// Set EN Pin to 0
	_delay_ms(10);
}

void lcd_setup()
{
	//1. Wait for 300ms to let LCD turn ON
	_delay_ms(300);
	//2. Set the LCD mode to 4-bit 16 character and 2 rows
	lcd_config(0x33);
	lcd_config(0x32);
	lcd_config(0x28);
	//16x1 -> 0x30
	//3. Set the Writing Style (Left -> Right)
	lcd_config(0x06);
	// Right-> Left  0x04
	//4. Set the Cursor Style (a. Solid, b. Blinking, c. OFF)
	lcd_config(0x0E);
	// 0x0E -> Solid
	// 0x0F -> Blinking
	// 0x0C -> OFF
	//5. Clear the garbage values on LCD Screen
	lcd_config(0x01);
	//6. Set the Home Location
	lcd_config(0x80);
}

void lcd_print(char *data)
{
	while (*data != '\0')
	{
		lcd_character(*data);
		data++;
	}
}

int main(void)
{
	char string[10];
	long count;
	double distance;
	
	DDRA = 0b00000001; // Ultra sonic sensor connected at PA0
	DDRC = 0b11111111; // LCD
	lcd_setup();
	lcd_config(0x80);
	lcd_print("Sensor Reading");
	sei();					// Enable global interrupt */
	TIMSK = (1 << TOIE1);   // Enable Timer1 overflow interrupts */
	TCCR1A = 0;				// Set all bit to zero Normal operation */

	while(1)
	{
		// Give 10us trigger pulse on trig. pin to HC-SR04 
		PORTA = 0b00000001;
		_delay_us(10);
		PORTA = 0b00000000;
		
		TCNT1 = 0;		/* Clear Timer counter */
		TCCR1B = 0x41;  /* Capture on rising edge, No prescaler*/
		TIFR = 1<<ICF1; /* Clear ICP flag (Input Capture flag) */
		TIFR = 1<<TOV1; /* Clear Timer Overflow flag */

		/*Calculate width of Echo by Input Capture (ICP) */
		
		while ((TIFR & (1 << ICF1)) == 0);/* Wait for rising edge */
		TCNT1 = 0;  /* Clear Timer counter */
		TCCR1B = 0x01;  /* Capture on falling edge, No prescaler */
		TIFR = 1<<ICF1; /* Clear ICP flag (Input Capture flag) */
		TIFR = 1<<TOV1; /* Clear Timer Overflow flag */
		TimerOverflow = 0;/* Clear Timer overflow count */

		while ((TIFR & (1 << ICF1)) == 0);/* Wait for falling edge */
		count = ICR1 + (65535 * TimerOverflow); /* Take count */
		/* 8MHz Timer freq, sound speed =343 m/s */
		distance = (double)count / 466.47;

		dtostrf(distance, 2, 2, string);/* distance to string */
		strcat(string, " cm   ");   /* Concat unit i.e.cm */
		lcd_config(0xC0);
		lcd_print("Dist = ");
		lcd_config(0xC7);
		lcd_print(string);    /* Print distance */
		_delay_ms(200);
	}
}