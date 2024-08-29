/*
 * Project_Name    :   LCD_Display_4
 * File_Name       :   main.c
 * Author          :   Mohamed Akram JABALLAH
 * Target          :   Atmega324p
*/


#include <avr/io.h>
#include <avr/delay.h>



#define LCD_Data    PORTA
#define RS          PINB4
#define RW          PINB5
#define EN          PINB6


void LCD_Init (void);
void Write_LCD_Command (unsigned char cmd);
void Write_LCD_Data (unsigned char data);
void LCD_Gotoxy (unsigned char x, unsigned char y);




int main (void) {

	DDRA = 0xFF;
	DDRB = 0xFF;

	LCD_Init();
	_delay_ms (100);
	Write_LCD_Command (0x0C);
	_delay_ms (100);
	Write_LCD_Command (0x01);

	Write_LCD_Data ('T');
	_delay_ms (1);
	Write_LCD_Data ('E');
	_delay_ms (1);
	Write_LCD_Data ('M');
	_delay_ms (1);
	Write_LCD_Data ('P');
	_delay_ms (1);
	Write_LCD_Data ('=');
	_delay_ms (1);


	Write_LCD_Command (0xC0);
	_delay_ms (100);
	Write_LCD_Command (0x0C);
	_delay_ms (100);



	Write_LCD_Data ('S');
	_delay_ms (1);
	Write_LCD_Data ('P');
	_delay_ms (1);
	Write_LCD_Data ('D');
	_delay_ms (1);
	Write_LCD_Data ('=');
	_delay_ms (1);

	float r0 = 950.3, r1 = 33.4567;
	unsigned char ch[10] = {' '};

	while (1) {

		for (uint8_t i = 0; i < 10; i++) {
			ch[i] = ' ';
		}

		LCD_Gotoxy (0,5);
		dtostrf (r0, 4,2, ch);

		for (uint8_t i = 0; i < 10; i++) {

			if ((ch[i] != '.') && (ch[i] < '0' || ch[i] > '9'))
				Write_LCD_Data (' ');
			else
				Write_LCD_Data (ch[i]);
		}

		r0 += 1;
		if (r0 > 999) {
			r0 = 0.3;
		}

		for (uint8_t i = 0; i < 10; i++) {
			ch[i] = ' ';
		}

		LCD_Gotoxy (1,4);
		dtostrf (r1, 4,4, ch);

		for (uint8_t i = 0; i < 10; i++) {
			if ((ch[i] != '.') && (ch[i] < '0' || ch[i] > '9'))
				Write_LCD_Data (' ');
			else
				Write_LCD_Data (ch[i]);
		}

		r1 += 1;
		if (r1 > 999) {
			r1 = 0.147;
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




























