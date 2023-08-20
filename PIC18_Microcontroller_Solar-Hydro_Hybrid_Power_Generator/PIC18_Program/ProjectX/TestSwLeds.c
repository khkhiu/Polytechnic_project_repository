// Template for modification into user program.
// For project using USB interface with Bootloader

#include <xc.h>
#include "delay.h"
unsigned char data;

main(void)
{
// Do not remove these as well=============
	ADCON1 = 0x0F;
	CMCON = 0x07;
// ========================================
// Your MAIN program Starts here: =========

	TRISB = 0b11111111;	// RB2 to RB0 are connected to switches
	TRISD = 0b00000000;	// RD2 to RD0 are connected to LEDs

	while(1)			//repeat 
	{
		PORTD = 0b00000001; // turn on LED at _____
        delay_ms(250);

		PORTD = 0b00000010; // turn on LED at _____
        delay_ms(250);
        
		PORTD = 0b00000100; // turn on LED at _____
        delay_ms(250);	}
}


		
