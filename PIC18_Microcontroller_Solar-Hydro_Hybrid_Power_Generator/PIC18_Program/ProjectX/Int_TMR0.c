/* Int_TMR0.c Timer Interrupt based program
 * ISR activated by Timer0 interrupt when it over-flow
 * Set up a Timer0 interrupt-driven program to count up the LEDs at PORTD at
 * 1 sec interval
 *
 * Timer0 is configured for 16 bit Timer Mode operation. 
 * The TMR0 interrupt is generated when the TMRO register
 * overflows from FFFFh to 0000h. 
 * This overflow sets the TMR0IF bit.
 * The TMR0IF bit must be cleared in software by the Timer0 module
 * ISR before re-enabling this interrupt.
 *
 * Timer0 starting value is set by writing to TMR0H and TMR0L. 
 * For 1 sec, the starting value is 0x48E5   
 * Main Process - configure external interrupt and use RA3 switch to control motor at RC2
*/

#include <xc.h>

unsigned char j;

void interrupt ISR_Timer0_Int()			// Timer0 Interrupt Service Routine (ISR)
{
  if (INTCONbits.TMR0IF)		// TMR0IF:- Timer0 Overflow Interrupt Flag Bit
  								// 1 = TMR0 reg has overflowed
								// 0 = TMR0 reg has not overflowed
    {
        TMR0H = 0x48; // Timer0 start value = 0x48E5 for 1 second
        TMR0L = 0xE5;

        j++; // Increase count by 1
        PORTD = j; // Show count value at Port D Leds 

        INTCONbits.TMR0IF = 0; // Reset TMR0IF to "0" since the end of
								// the interrupt function has been reached
    }
}

			
void main(void)			// Main Function
{

	ADCON1 = 0x0F;
	CMCON = 0x07;

	TRISAbits.TRISA3 = 1;	// RA3 is the On/Off switch
	TRISCbits.TRISC2 = 0;	// RC2 connects to a DC motor
	TRISD = 0x00;			// PortD connects to a bar LEDs
	
	PORTD = 0x00;			// LEDs all off	
	j = 0;					// Start count from 0

	RCONbits.IPEN =1;	 	// Bit7 Interrupt Priority Enable Bit
				 		 	// 1 Enable priority levels on interrupts
						  	// 0 Disable priority levels on interrupts		

	INTCONbits.GIEH =1;	  	// Bit7 Global Interrupt Enable bit
				  			// When IPEN = 1
				  			// 1 Enable all high priority interrupts
				  			// 0 Disable all high priority interrupts 

	T0CON = 0b00000111;    // bit7:0 Stop Timer0
							// bit6:0 Timer0 as 16 bit timer
							// bit5:0 Clock source is internal 
							// bit4:0 Increment on lo to hi transition on TOCKI pin
							// bit3:0 Prescaler output is assigned to Timer0  
							// bit2-bit0:111 1:256 prescaler


	INTCON2 = 0b10000100;	// bit7 :PORTB Pull-Up Enable bit
							//	 1 All PORTB pull-ups are disabled
							// bit2 :TMR0 Overflow Int Priority Bit
							//   1 High Priority
 
	TMR0H = 0x48;			// Initialising TMR0H
	TMR0L = 0xE5;           // Initialising TMR0L for 1 second interrupt
							 
	T0CONbits.TMR0ON = 1;	// Turn on timer
	INTCONbits.TMR0IE = 1;	// bit5 TMR0 Overflow Int Enable bit
							// 0 Disable the TMR0 overflow int

	INTCONbits.TMR0IF = 0;  // bit2 TMR0 Overflow Int Flag bit
							// 0 TMR0 register did not overflow

    while (1) // Main Process
    {
        if (PORTAbits.RA3 == 0) // If RA3 switch is ON

            PORTCbits.RC2 = 1; // Turn On Motor

        else

            PORTCbits.RC2 = 0; // Else turn Off Motor 	 

    }

}
