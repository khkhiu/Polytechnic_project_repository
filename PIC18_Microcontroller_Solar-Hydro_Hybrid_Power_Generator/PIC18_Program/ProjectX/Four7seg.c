/*
 * File:   Four7seg.c
 *
 * Created on 13 January, 2016, 1:52 PM
 */


#include <xc.h>
#include "delays.h"
void main(void)
{

	TRISB=0b11110000;	//RB3 to RB0 are connected DIG3 to DIG0 active high
						//RB5 is connected to a switch

	TRISD=0b00000000;	//RD7 to RD0 are connected to segment LEDs active high

		
	while(1)			//repeat 
	{

		PORTB = 0b00000001;	//enable DIG0
		PORTD = 0b00111111;  	//display 0
		delay_ms(1000);	//LEDs on for a while

		PORTB = 0b00000010;	//enable DIG1
		PORTD = 0b00000110;  	//display 1
		delay_ms(1000);	//LEDs on for a while

		PORTB = 0b00000100;	//enable DIG2
		PORTD = 0b01011011;  	//display 2
		delay_ms(1000);	//LEDs on for a while

		PORTB = 0b00001000;	//enable DIG3
		PORTD = 0b01001111;  	//display 3
		delay_ms(1000);	//LEDs on for a while

	}
}
