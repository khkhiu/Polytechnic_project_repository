// Single7Seg.c
// Program to test 1 7-segment display

#include <p18F4550.h>
#include <delays.h>

// Include this when using Bootloader Program ================================
#pragma udata

extern void _startup (void);        // See c018i.c in your C18 compiler dir
#pragma code _RESET_INTERRUPT_VECTOR = 0x000800
void _reset (void)
{
    _asm goto _startup _endasm
}
#pragma code

#pragma code _HIGH_INTERRUPT_VECTOR = 0x000808
void _high_ISR (void)
{
    ;
}

#pragma code _LOW_INTERRUPT_VECTOR = 0x000818
void _low_ISR (void)
{
    ;
}
#pragma code

#pragma code

//  Ends here ===============================================================

// Program starts here:



void main(void)
{
	ADCON1 = 0x0F;
	TRISB=0b11110000;	//RB3 to RB0 are connected DIG3 to DIG0 active high
						//RB5 is connected to a switch
	TRISD=0b00000000;	//RD7 to RD0 are connected to segment LEDs active high
		
	while(1)			//repeat 
	{
//3.2
//		PORTB = 0b00000001;	//enable DIG0
//		PORTD = 0b00111111;  	//display '0'
//		Delay1KTCYx(10);// 0.833 ms

//3.5
		PORTB = 0b00000010;	//enable DIG1
		PORTD = 0b00000110;  	//display '1'
		Delay1KTCYx(10);// 0.833 ms
	}

	
}


		

