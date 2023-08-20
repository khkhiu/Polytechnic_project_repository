// LCDKeypad.c
// Program to test LCD and keypad.
// For project using USB interface with Bootloader


#include <xc.h>
#include "keypad.h"
#include "delays.h"
#include "lcd.h"	
unsigned char key,outchar;
char Message1 [ ] = "Enter PIN number :  ";	  // Defining a 20 char string

// ---- Main Program ---------------------------------------------------------------
void main(void)
{
	int i;
	lcd_init();						// Initialise LCD module

	while(1)
	{
		lcd_write_cmd(0x80);			// Move cursor to line 1 position 1
		for (i = 0; i < 20; i++)		//for 20 char LCD module
		{
			outchar = Message1[i];
			lcd_write_data(outchar); 	// write character data to LCD
		}
		

		lcd_write_cmd(0xC0);			// Move cursor to line 2 position 1
		for (i = 0; i < 20; i++)		//for 20 number
		{ 
			key=getkey(); 				// waits and get an ascii key number when pressed
			lcd_write_data(key);		//display on LCD
			
		}
		
		delay_ms(1000);                 // wait 1 second
		lcd_write_cmd(0x01);			// 00000001 Clear Display instruction
	}
}




