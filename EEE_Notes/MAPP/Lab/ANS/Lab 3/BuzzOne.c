// BuzzOne.c
// Program to activate buzzer with one tone
// For project using USB interface with Bootloader

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

// additional codes ends here ===============================================================

// Your program declarations start here:====

//-----------------------------------------------------
void onetone(void)	//Function to generate one tone
{
	unsigned int  k;
	
	for(k= 0x0; k<1000; k++)//Determines duration of tone
	{
		Delay100TCYx(100);//Determines pitch of tone	
		PORTCbits.RC0 = !PORTCbits.RC0; //Invert logic level at RC0
	}
}
//-----------------------------------------------------
void tone(unsigned char c)	//Function to generate a tone
{
	unsigned int  k;
	
	for(k= 0x0; k<1000; k++)//Determines duration of tone
	{
		Delay100TCYx(c);//Determines pitch of tone	
		PORTCbits.RC0 = !PORTCbits.RC0; //Invert logic level at RC0
	}
}
//-----------------------------------------------------
void delay()
{
		Delay1KTCYx(240);//0.02 s
		Delay1KTCYx(240);//0.02 s
		Delay1KTCYx(240);//0.02 s
		Delay1KTCYx(240);//0.02 s
}
//-----------------------------------------------------
void main(void)
{
	ADCON1 = 0x0F;
	TRISCbits.TRISC0=0; 	//-- Set RC0 as output
	TRISD = 0x00;		//-- Set all pins on PortD as output

	while(1)
	{
		tone(100);		//sound ON then OFF
		PORTD=0b10101010;	//pattern on LEDs
		delay();
	
		tone(50);		//sound ON then OFF
		PORTD=0b01010101;	//another pattern on LEDs
		delay();
	}
}						



		

