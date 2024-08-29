/*
 * Project_Name    :   LCD_keyPad_2
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
uint8_t keypad (void);
uint16_t keypad_Num (void);


int main (void) {

	DDRA  = 0xFF;
	DDRB  = 0xFF;
	DDRD  = 0x0F;
	PORTD = 0xF0;


	LCD_Init();
	_delay_ms (100);
	Write_LCD_Command (0x0C);
	_delay_ms (100);
	Write_LCD_Command (0x01);

	LCD_Gotoxy (0,0);
	LCD_Write_String ("Keypad = ");
	_delay_ms (1);
	LCD_Gotoxy (1,0);
	LCD_Write_String ("Final = ");
	_delay_ms (1);

	uint16_t Final_data = 0;
	unsigned char ch[4] = {' '};

	while (1) {

		Final_data = keypad_Num();

		if (keypad() == 50) {
			for (int i = 0; i < 4; i++) {
				ch[i] = ' ';
			}

			LCD_Gotoxy (1,8);
			itoa (Final_data, ch, 10);

			if (keypad() != 100) {
				for (int i = 0; i < 4; i++) {
					if (ch[i] < '0' || ch[i] > '9')
						Write_LCD_Data (' ');
					else
						Write_LCD_Data (ch[i]);
				}
			}
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


void LCD_Write_String (char *str) {

	unsigned char i = 0;
	while (str[i] != 0) {
		Write_LCD_Data (str[i]);
		i++;
	}
}



uint8_t keypad (void) {

	PORTD = 0xFE;
	_delay_ms (1);

	if      ((PIND & (1 << PIND4)) == 0) return 1;
	else if ((PIND & (1 << PIND5)) == 0) return 2;
	else if ((PIND & (1 << PIND6)) == 0) return 3;
	else if ((PIND & (1 << PIND7)) == 0) return 'A';

	PORTD = 0xFD;
	_delay_ms (1);

	if      ((PIND & (1 << PIND4)) == 0) return 4;
	else if ((PIND & (1 << PIND5)) == 0) return 5;
	else if ((PIND & (1 << PIND6)) == 0) return 6;
	else if ((PIND & (1 << PIND7)) == 0) return 'B';

	PORTD = 0xFB;
	_delay_ms (1);

	if      ((PIND & (1 << PIND4)) == 0) return 7;
	else if ((PIND & (1 << PIND5)) == 0) return 8;
	else if ((PIND & (1 << PIND6)) == 0) return 9;
	else if ((PIND & (1 << PIND7)) == 0) return 'C';


	PORTD = 0xF7;
	_delay_ms (1);

	if      ((PIND & (1 << PIND4)) == 0) return '*';
	else if ((PIND & (1 << PIND5)) == 0) return 0;
	else if ((PIND & (1 << PIND6)) == 0) return '#';
	else if ((PIND & (1 << PIND7)) == 0) return 50;

	return 100;
}


uint16_t keypad_Num (void) {

	static uint16_t Num = 0;
	unsigned char ch[4] = {' '};

	if (keypad() < 10) {
		Num *= 10;
		Num += keypad();

		if (Num > 255) Num = 0;
		for (int i = 0; i < 4; i++ ) {
			ch[i] = ' ';
		}

		LCD_Gotoxy (0,9);
		itoa (Num, ch, 10);

		if (keypad() != 100) {
			for (int i = 0; i < 4; i++) {
				if (ch[i] < '0' || ch[i] > '9')
					Write_LCD_Data (' ');
				else
					Write_LCD_Data (ch[i]);
			}
		}
	}
	return Num;
}
































































