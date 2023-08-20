// Single7Seg.c
// Program to test 1 7-segment display

#include <xc.h>

void main(void)
{
	ADCON1 = 0x0F;

	TRISB=0b11110000;	//RB3 to RB0 are connected DIG3 to DIG0 active high
						//RB5 is connected to a switch

	TRISD=0b00000000;	//RD7 to RD0 are connected to segment LEDs active high

		
	while(1)			//repeat 
	{

		PORTB = 0b00000001;	//enable DIG0
		
		PORTD = 0b00111111;  	//display 0
	
	}
}
