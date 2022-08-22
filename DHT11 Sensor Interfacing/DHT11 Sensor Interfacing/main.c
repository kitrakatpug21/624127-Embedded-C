/*
 * DHT11 Sensor Interfacing.c
 *
 * Created: 18-08-2022 10:40:25 AM
 * Author : kartik.iot
 */ 

#include <avr/io.h>
#define F_CPU 8000000UL
#include <util/delay.h>

#include <stdlib.h>
#include <stdio.h>

void lcd_config(uint8_t cmd);
void lcd_character(char ch);
void lcd_setup();
void lcd_print(char *data);
void Request()
{
	//1. Micro-controller send start pulse/request
	DDRB = 0xFF;			// Set the PA1 Pin as output
	PORTB &= ~(0b00000010);		// set to low pin
	_delay_ms(20);				// wait for 20ms 
	PORTB |= (0b00000010);		// set to high pin	
	_delay_ms(20);				// wait for 20ms
	PORTB &= ~(0b00000010);		// set to low pin
	_delay_ms(20);
	lcd_config(0xC0);
	lcd_print("Request Done");
}

void Response()					
{
	//1. receive response from DHT11 Sensor
	//In order to receive a signal, the DHT Sensor returns a signal like 
	//	1 - 0 - 1
	//Once this frame is received, means data incoming is started
	DDRB &= ~(0b00000010);			// Set the PA1 Pin as input
	while(PINB & (0b00000010))
	{
		// wait until the PA1 pin becomes LOW (return 0 at PA1)
	}
	while((PINB & (0b00000010))==0)
	{
		// wait until the PA1 pin becomes HIGH (return 1 at PA1)
	}
	while(PINB & (0b00000010))
	{
		// wait until the PA1 pin becomes LOW again (return 0 at PA1)
	}
	lcd_config(0xC0);
	lcd_print("Response Done");
}
uint8_t c=0, I_RH,D_RH,I_Temp,D_Temp,CheckSum;
int Receive_data()
{
	// Data is Returned in 8 bit format, so
	for (int q=0; q<8; q++)
	{
		while((PINB & (0b00000010)) == 0);  /* check received bit 0 or 1 */
		_delay_us(30);
		if (PINB & (0b00000010))
		{
			// if high pulse is greater than 30ms then its logic HIGH 
			c = (c<<1)|(0x01);
		}
		else
		{			
			// otherwise its logic LOW
			c = (c<<1);
		}
		while(PINB & (0b00000010))
		{
			// wait until the signal is processed
		}
	}
	// once the 8 bits are received, return to the main function
	return c;
}

int main(void)
{
	DDRC = 0b11001111;// D7..D0
	lcd_setup();
	char humid[16],temp[16];
	while(1)
	{
		Request();				/* send start pulse */
		Response();				/* receive response */
		I_RH=Receive_data();	/* store first eight bit in I_RH */
		D_RH=Receive_data();	/* store next eight bit in D_RH */
		I_Temp=Receive_data();	/* store next eight bit in I_Temp */
		D_Temp=Receive_data();	/* store next eight bit in D_Temp */
		CheckSum=Receive_data();/* store next eight bit in CheckSum */
		
		if ((I_RH + D_RH + I_Temp + D_Temp) != CheckSum)
		{
			lcd_config(0x80);
			lcd_print("Error");
		}
		else
		{
			sprintf(humid,"Humid:%d.%d%%",I_RH,D_RH);
			lcd_config(0x80);
			lcd_print(humid);
			
			sprintf(temp,"Temp:%d.%d DegC",I_Temp,D_Temp);
			lcd_config(0xC0);
			lcd_print(temp);
		}
		_delay_ms(10);
	}
}

/*
 * LCD (4-Bit).c
 *
 * Created: 18-08-2022 10:41:31 AM
 * Author : kartik.iot
 */ 

void lcd_config(uint8_t cmd)
{
	// FIRST PART OF 8-bit Data
	//1. Upload the character on PORTC
	PORTC = (PORTC & 0x0F) | (cmd & 0xF0);// msb will load first
	//2. Set RS Pin to 0
	PORTC = PORTC & ~(0b00000001);	// Set RS Pin to 0
	//3. Generate a Latch signal 0-1-0
	PORTC = PORTC | 0b00000010;	// Set EN Pin to 1
	_delay_ms(1);
	PORTC = PORTC & ~(0b00000010);	// Set EN Pin to 0
	_delay_ms(1);
	// SECOND PART OF 8-bit Data
	//1. Upload the character on PORTC
	PORTC = (PORTC & 0x0F) | ((cmd<<4) & 0xF0);// lsb will load first
	//2. Set RS Pin to 0
	PORTC = PORTC & ~(0b00000001);	// Set RS Pin to 0
	//3. Generate a Latch signal 0-1-0
	PORTC = PORTC | 0b00000010;	// Set EN Pin to 1
	_delay_ms(1);
	PORTC = PORTC & ~(0b00000010);	// Set EN Pin to 0
	_delay_ms(1);
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
	_delay_ms(1);
	PORTC = PORTC & ~(0b00000010);	// Set EN Pin to 0
	_delay_ms(1);
	// SECOND PART OF 8-bit Data
	//1. Upload the character on PORTC
	PORTC = (PORTC & 0x0F) | ((ch<<4) & 0xF0);// lsb will load first
	//2. Set RS Pin to 1
	PORTC = PORTC | 0b00000001;	// Set RS Pin to 1
	//3. Generate a Latch signal 0-1-0
	PORTC = PORTC | 0b00000010;	// Set EN Pin to 1
	_delay_ms(1);
	PORTC = PORTC & ~(0b00000010);	// Set EN Pin to 0
	_delay_ms(1);
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

