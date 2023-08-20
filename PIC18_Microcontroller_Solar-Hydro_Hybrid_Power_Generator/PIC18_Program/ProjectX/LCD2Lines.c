// LCD2Lines.c
// Program to test LCD.
// The LCD display with two lines, 24 characters each.
// There are three control lines (RD4:RD6) and four data lines (RD3:RD0).
// RD6 - RS=0 Data represents Command, RS=1 Data represents Character
// RD5 - RW=0 Writing into the LCD module
// RD4 - E =1 Data is latched into LCD module during low to hight transition  

#include <xc.h>
#include "lcd.h"	// Include file is located in the project directory

void main(void)
{
	lcd_init();					// Initialise LCD module

	while(1)
	{
  	lcd_write_cmd(0x80);		// Move cursor to line 1 position 1
	lcd_write_data(0x41); 		// write "A" to LCD
  	lcd_write_data(0x42);		// write "B" to LCD
	lcd_write_data(0x43); 		// write "C" to LCD
  	
 	lcd_write_cmd(0xC0);		// Move cursor to line 2 position 1
	lcd_write_data(0x31); 		// write "1" to LCD
 	lcd_write_data(0x32);		// write "2" to LCD
	lcd_write_data(0x33); 		// write "3" to LCD
  	
	while(1);					//stop here for now

	}
}						


		

