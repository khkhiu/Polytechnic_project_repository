// Int_INT0_b.c Interrupt based program
// ISR activated by INT0 from an active low switch from RB0

#include <xc.h>
#include"delays.h"

unsigned char i, j;
unsigned char press, a, b;

void interrupt ISR_PortB0_low(void)		// Interrupt Service Routine for INT0
{
  if (INTCONbits.INT0IF)	// External Interrupt Flag Bit = 1 when interrupt occurred
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

        INTCONbits.INT0IF = 0;  //Clearing the flag at the end of the ISR
  }
}


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
	j = 0;

	RCONbits.IPEN =1;	// Bit7 Interrupt Priority Enable Bit
				// 1 Enable priority levels on interrupts
				// 0 Disable priority levels on interrupts		

	INTCONbits.GIEH =1;	// Bit7 Global Interrupt Enable bit
				// When IPEN = 1
				// 1 Enable all high priority interrupts
				// 0 Disable all high priority interrupts 

    	INTCON2bits.INTEDG0 = 0;// Bit4 External Interrupt2 Edge Select Bit
				// 1 Interrupt on rising edge
				// 0 Interrupt on falling edge

	INTCONbits.INT0IE = 1;  // Bit4 INT0 External Interrupt Enable bit
				// 1 Enable the INT0 external interrupt
				// 0 Disable the INT0 external interrupt

 	INTCONbits.INT0IF = 0;  // Clearing the flag


    	while(1)		// Main Process
	{
           LED_RD7_RD0();	// Move Port D LEDs from bit7 to bit0
	}

}





		

