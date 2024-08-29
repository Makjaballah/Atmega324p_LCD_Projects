/*
 * Project_Name    :   LCD_Display_2
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
void LCD_Gotoxy (unsigned char x, unsigned char y);
void LCD_Write_String (char *str);


int main (void) {

	DDRA = 0xFF;
	DDRB = 0xFF;

	LCD_Init();
	_delay_ms (100);
	Write_LCD_Command (0x0C);
	_delay_ms (100);

	while (1) {

		LCD_Gotoxy (0,0);
		LCD_Write_String ("Dr.Mohamed Akram");
		_delay_ms (100);
		LCD_Gotoxy (1,4);
		LCD_Write_String ("JABALLAH");
		_delay_ms (100);
		Write_LCD_Command (0x0E);
	    _delay_ms (1000);
	    Write_LCD_Command (0x01);
	}

	return 0;
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


void LCD_Gotoxy (unsigned char x_pos, unsigned char y_pos) {

	uint8_t The_Address = 0;
	if (x_pos == 0)
		The_Address = 0x80;
	else if (x_pos == 1)
		The_Address = 0xC0;
	if (y_pos < 16)
		The_Address += y_pos;
	Write_LCD_Command (The_Address);
}


void LCD_Write_String (char *str) {

	unsigned char i = 0;
	while (str[i] != 0) {
		Write_LCD_Data (str[i]);
		i++;
	}
}

