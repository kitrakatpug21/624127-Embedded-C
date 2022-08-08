/*
 * LCD.c
 *
 * Created: 08-08-2022 10:41:27 AM
 * Author : kartik.iot
 */ 

#include <avr/io.h>
#define F_CPU 8000000UL
#include <util/delay.h>

void lcd_config(uint8_t cmd)
{
	//1. Set RS Pin to 0
	PORTC = 0b00000000;
	//2. Upload the command on PORTD
	PORTD = cmd;
	//3. Generate a Latch signal 0-1-0
	PORTC = 0b00000010;
	_delay_ms(10);
	PORTC = 0b00000000;
	_delay_ms(10);
}
void lcd_character(char ch)
{
	//1. Set RS Pin to 1
	PORTC = 0b00000001;
	//2. Upload the character on PORTD
	PORTD = ch;
	//3. Generate a Latch signal 0-1-0
	PORTC = 0b00000011;
	_delay_ms(10);
	PORTC = 0b00000001;
	_delay_ms(10);
}

void lcd_setup()
{
	//1. Wait for 300ms to let LCD turn ON
	_delay_ms(300);
	//2. Set the LCD mode to 8-bit 16 character and 2 rows
	lcd_config(0x38);
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
	DDRC = 0b00000011;// EN RS
	DDRD = 0b11111111;// D7..D0
	lcd_setup();
    while (1) 
    {
	    lcd_config(0x80);
		lcd_print("Hello SUDHESH");
		_delay_ms(1000);
		lcd_config(0xC0);
		lcd_print("Hi!! Renu");
		_delay_ms(1000);
    }
}

