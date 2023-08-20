// Int_INT0_a.c Polling based program

#include <xc.h>
#include "delays.h"

unsigned char j;
unsigned char press;

void LED_RD7_RD0(void);		// Declaring function protypes 


void LED_RD7_RD0(void)		// The function to shift a set-bit from the MSB to LSB position
{				
	j = 0x80;		// Initialise j with B1000 0000
				// ie the leftmost bit (or MSB)

	while(j!=0x00)		// Check that the bit has not been shifted
				// to the right-most bit (LSB) ie B00000001
	{
	  PORTD = j;		// Display j at PORTD
	  delay_ms(250);    // Calling a delay function from delays.h
	  j = j>>1;  		// Making use of LOGICAL-RIGHT-SHIFT bit-wise
	}		   	// operator to shift data to the right

	PORTD = j;		// Display j at PORTD
}				// Stop at B00000001 

			
void main(void)			// Main Function
{
	ADCON1 = 0x0F;
	CMCON = 0x07;

	TRISBbits.TRISB0 = 1;	// RB0 is the push button switch for INT0
	TRISCbits.TRISC2 = 0;	// RC2 connects to a DC motor
	TRISD = 0x00;		// PortD connects to a bar LEDs
	
	PORTD = 0x00;		// LEDs all off	
	press = 0;		// Not pressing yet

    	while(1)		// Main Process
	{
           LED_RD7_RD0();	// Move Port D LEDs from bit7 to bit0

           // polling the switch at RB0
           if (PORTBbits.RB0 == 0)
           {
	      press++;		// To track first or second time pressing RB0 switch
	
	      if (press == 1)		// First press
	      {
	         PORTCbits.RC2 = 1;	// Turn On Motor	 
   	      }
	      else
	      if (press == 2)		// Second press
	      {
	         PORTCbits.RC2 = 0;	// Else turn Off Motor 
	         press = 0;		// Reset the pressing counter
	      }
           }
	}
}





		

