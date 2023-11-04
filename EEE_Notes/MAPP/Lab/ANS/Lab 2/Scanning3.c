// BlinkLeds.c
// Program to use 1 switch to control 8 leds on General I/O Board


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
//------------------------------------------------------
void delay()
{
		Delay10KTCYx(250);
		Delay10KTCYx(250);
		
		if (PORTAbits.RA4==0) //Lab 2.20
		{//More delay:
			Delay10KTCYx(250);
			Delay10KTCYx(250);
		}
}
//------------------------------------------------------
void main(void) //Lab 2.18 
{
	char n;
	unsigned char patt[8]={0x01,0x02,0x04,0x08,
							0x10,0x20,0x40,0x80};

	ADCON1 = 0x0F;		//make Port A digital
	TRISA=0b11111111;	//RA5 to RA3 are connected to On/Off switches
	TRISD=0b00000000;	//RD7 to RD0 are connected to LEDs

	while(1)		//repeat 
	{
		for (n=0; n<8; n++) //patt 0 to 7 (Right to Left)
		{
			PORTD=patt[n];
			delay();
			while (PORTAbits.RA3==0);//2.12 Pause while RA3 is 0
		}

		for (n=7; n>=0; n--) //patt 7 to 0 (Left to Right)
		{
			PORTD=patt[n];
			delay();
			while (PORTAbits.RA3==0);//2.12 Pause while RA3 is 0
		}
	}
}


		

