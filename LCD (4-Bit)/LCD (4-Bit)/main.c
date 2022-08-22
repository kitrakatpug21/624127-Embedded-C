/*
 * LCD (4-Bit).c
 *
 * Created: 18-08-2022 10:41:31 AM
 * Author : kartik.iot
 */ 
#include <avr/io.h>
#define F_CPU 8000000UL
#include <util/delay.h>

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
	DDRC = 0b11001111;// D7..D0
	lcd_setup();
	while (1)
	{
		lcd_config(0x80);
		lcd_print("SAVITRI");
		_delay_ms(1000);
		lcd_config(0xC0);
		lcd_print("RAJIV");
		_delay_ms(1000);
		lcd_config(0x01);_delay_ms(10);
		lcd_config(0x80);
		lcd_print("SUMANTI");
		_delay_ms(1000);
		lcd_config(0xC0);
		lcd_print("PRITAM");
		_delay_ms(1000);
		lcd_config(0x01);_delay_ms(10);
	}
}

