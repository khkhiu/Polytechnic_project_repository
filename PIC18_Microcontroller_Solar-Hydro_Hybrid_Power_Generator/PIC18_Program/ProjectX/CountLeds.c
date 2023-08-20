// CountLeds.c
// Program to use 1 switch to control counting on 8 leds on General I/O Board

#include <xc.h>
#include "delays.h"

unsigned char j;	/* 8 bit data type, range 0 to 255     */

void main(void)
{
	ADCON1 = 0x0F;		//make Port A digital

	TRISA=0b11111111;	//RA5 to RA3 are connected to On/Off switches

	TRISD=0b00000000;	//RD7 to RD0 are connected to LEDs

	j=0;				//beginning

	while(1)			//repeat 
	{
	
		PORTD = j;		// Output value of j to PORTD 

        delay_ms(500);

		j++;			// Increment j	
	}
}


		

