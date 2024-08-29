/*
 * Project_Name    :   LCD_keyPad_1
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
unsigned char keypad (void);


int main (void) {

	DDRA  = 0xFF;
	DDRB  = 0xFF;

	DDRD  = 0x0F;
	PORTA = 0xF0;

	LCD_Init();
	_delay_ms (100);
	Write_LCD_Command (0x0C);
	_delay_ms (100);
	Write_LCD_Command (0x01);
	_delay_ms (100);


	Write_LCD_Data ('K');
	_delay_ms (1);
	Write_LCD_Data ('e');
	_delay_ms (1);
	Write_LCD_Data ('y');
	_delay_ms (1);
	Write_LCD_Data ('P');
	_delay_ms (1);
	Write_LCD_Data ('a');
	_delay_ms (1);
	Write_LCD_Data ('d');
	_delay_ms (1);
	Write_LCD_Data (' ');
	_delay_ms (1);
	Write_LCD_Data ('=');
	_delay_ms (1);

	while (1) {

		LCD_Gotoxy (0,9);
		if (keypad () != 'N') {
			Write_LCD_Data (keypad ());
		}
		_delay_ms (250);
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


unsigned char keypad (void) {

	PORTD = 0xFE;
	_delay_ms (1);

	if      ((PIND & (1 << PIND4)) == 0) return '1';
	else if ((PIND & (1 << PIND5)) == 0) return '2';
	else if ((PIND & (1 << PIND6)) == 0) return '3';
	else if ((PIND & (1 << PIND7)) == 0) return 'A';

	PORTD = 0XFD;
	_delay_ms (1);

	if      ((PIND & (1 << PIND4)) == 0) return '4';
	else if ((PIND & (1 << PIND5)) == 0) return '5';
	else if ((PIND & (1 << PIND6)) == 0) return '6';
	else if ((PIND & (1 << PIND7)) == 0) return 'B';

	PORTD = 0XFB;
	_delay_ms (1);

	if      ((PIND & (1 << PIND4)) == 0) return '7';
	else if ((PIND & (1 << PIND5)) == 0) return '8';
	else if ((PIND & (1 << PIND6)) == 0) return '9';
	else if ((PIND & (1 << PIND7)) == 0) return 'C';

	PORTD = 0XF7;
	_delay_ms (1);

	if      ((PIND & (1 << PIND4)) == 0) return '*';
	else if ((PIND & (1 << PIND5)) == 0) return '0';
	else if ((PIND & (1 << PIND6)) == 0) return '#';
	else if ((PIND & (1 << PIND7)) == 0) return 'D';

	return 'N';
}














































