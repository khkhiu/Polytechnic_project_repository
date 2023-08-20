/* TimerDelay.c Program containing a 1 sec delay function
*  Use Timer0
*  Frequency of OSC = 48 MHz, Prescaler = 256
*  TMR0H:TMR0L contain the starting count value
*  Monitor TMR0IF flag. When TMR0IF = 1, one sec is over
*/
#include <xc.h>


void Delay1sec(void);		//Function to provide 1 sec delay using Timer0
void Delay1sec(void)
{
	TMR0H=0X48;			//Starting count value
	TMR0L=0XE5;		
		
	INTCONbits.TMR0IF=0;		//Clear flag first
	T0CONbits.TMR0ON=1;		//Turn on Timer 0
	
	while(INTCONbits.TMR0IF==0);	//Wait for time is up when TMR0IF=1 
	T0CONbits.TMR0ON=0;		//Turn off Timer 0 to stop counting
}

void main(void)
{
	TRISD=0x00;			//PortD connected to 8 LEDs
	T0CON=0b00000111;		//Off Timer0, 16-bits mode, prescaler to 256

	while(1)			//Repeatedly
	{	
		PORTD=0x00;		//Off all LEDs
		Delay1sec();	
			
		PORTD=0xFF;		//On all LEDs
		Delay1sec();
	
	}
}
