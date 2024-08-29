/*
 * Project_Name    :   LCD_Display_1
 * File_Name       :   main.c
 * Author          :   Mohamed Akram JABALLAH
 * Target          :   Atmega324p
*/


#include <avr/io.h>
#include <util/delay.h>

#define LCD_Data    PORTA
#define RS          PINB4
#define RW          PINB5
#define EN          PINB6


void LCD_Init (void);
void Write_LCD_Command (unsigned char cmd);
void Write_LCD_Data (unsigned char data);


int main (void) {

	DDRA = 0xFF;
	DDRB = 0xFF;

	LCD_Init();
	_delay_ms (100);
	Write_LCD_Command (0x0C);
	_delay_ms (100);

	while (1) {

		Write_LCD_Data ('D');
		_delay_ms (100);
		Write_LCD_Data ('r');
		_delay_ms (100);
		Write_LCD_Data ('.');
		_delay_ms (100);
		Write_LCD_Data ('M');
		_delay_ms (100);
		Write_LCD_Data ('o');
		_delay_ms (100);
		Write_LCD_Data ('h');
		_delay_ms (100);
		Write_LCD_Data ('a');
		_delay_ms (100);
		Write_LCD_Data ('m');
		_delay_ms (100);
		Write_LCD_Data ('e');
		_delay_ms (100);
		Write_LCD_Data ('d');
		Write_LCD_Data (' ');
		_delay_ms (100);

		Write_LCD_Data ('A');
		_delay_ms (100);
		Write_LCD_Data ('k');
		_delay_ms (100);
		Write_LCD_Data ('r');
		_delay_ms (100);
		Write_LCD_Data ('a');
		_delay_ms (100);
		Write_LCD_Data ('m');
		_delay_ms (100);

		Write_LCD_Command (0xC0);
		_delay_ms (100);
		Write_LCD_Command (0x0C);
		_delay_ms (100);

		for (uint8_t i = 0; i < 4; i++) {

			Write_LCD_Data (' ');
			_delay_ms (2);
		}

		Write_LCD_Data ('J');
		_delay_ms (100);
		Write_LCD_Data ('A');
		_delay_ms (100);
		Write_LCD_Data ('B');
		_delay_ms (100);
		Write_LCD_Data ('A');
		_delay_ms (100);
		Write_LCD_Data ('L');
		_delay_ms (100);
		Write_LCD_Data ('L');
		_delay_ms (100);
		Write_LCD_Data ('A');
		_delay_ms (100);
		Write_LCD_Data ('H');
		_delay_ms (100);

		Write_LCD_Command (0x0E);
		_delay_ms (1000);
		Write_LCD_Command (0x01);
	}
}


void LCD_Init (void) {

	Write_LCD_Command (0x38);
	_delay_ms (1);
	Write_LCD_Command (0x01);
	_delay_ms (1);
	Write_LCD_Command (0x02);
	_delay_ms (1);
	Write_LCD_Command (0x06);
	_delay_ms (1);
	Write_LCD_Command (0x80);
	_delay_ms (1);
}

void Write_LCD_Command (unsigned char cmd) {

	LCD_Data = cmd;
	PORTB   &= ~(1 << RS);
	PORTB   &= ~(1 << RW);
	PORTB   |=  (1 << EN);
	_delay_ms (2);
	PORTB   &= ~(1 << EN);
}

void Write_LCD_Data (unsigned char data) {

	LCD_Data = data;
	PORTB   |=  (1 << RS);
	PORTB   &= ~(1 << RW);
	PORTB   |=  (1 << EN);
	_delay_ms (2);
	PORTB   &= ~(1 << EN);
}

