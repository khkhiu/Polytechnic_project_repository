// ADC.c
// Program to use ADC to read variable resistor input and display on LEDs
// For project using USB interface with Bootloader


/*
 *	Perform 10-bit a2d on RA0/AN0 through Trimmer R16
 *	Output result on PORTD 
 *	
 *	Makes use of repetitive for-loop to convert the 
 *	analog value at RA0/AN0 to a 10-bit result.
 *
 *      Makes use of the ADRESH result to detect a user setting
 *      eg a temperature setting for a thermostat (TempTrip)
 *      
 *      Note that the time between each conversion will be
 *	longer as more user code are inserted.
 */
#include <xc.h>

void main(void)
{
	#define HIGH 0xD0   // HIGH water level indicator

	TRISD = 0x00;		// Set PORTD to be output
	PORTD = 0x00;		// Initialise PORTD LEDs to zeros

	TRISCbits.TRISC1 = 0; 	// RC1 as output pin
 	PORTCbits.RC1    = 0;   // RC1 is connected to Relay

	TRISCbits.TRISC2 = 0; 	// RC2 as output pin
 	PORTCbits.RC2    = 0;   // RC2 is connected to Motor

	/* Initialise analog to digital conversion setting */

	ADCON0 = 0b00000001;    // bit5-2 0000 select channel 0 conversion 
							// bit1	  A/D conversion status bit
							//	      1- GO to starts the conversion
							//	      0 - DONE when A/D is completed
							// bit0   Set to 1 to power up A/D

	ADCON1 = 0b00001100;	// bit5   reference is VSS
							// bit4   reference is VDD
							// bit3-0 AN2 to AN0 Analog, the rest Digital

	ADCON2 = 0b00010110;	// bit7   : A/D Result Format. 0 Left, 1 Right justified
							// bit5-3 : 010 acquisition time = 4 TAD
							// bit2-0 : 110 conversion clock = Tosc / 16

	while(1)
	{
		ADCON0bits.GO = 1;		// This is bit2 of ADCON0, START CONVERSION NOW
	        
		while(ADCON0bits.GO == 1); 	// Waiting for DONE 
			
		PORTD = ADRESH;			// Displaying only the upper 8-bits
						   		// of the A/D result
		
		if(ADRESH > HIGH)
		{		
			PORTCbits.RC2 = 1;   	// Turn on Motor
		
		}
		else
		{
			PORTCbits.RC2 = 0;   // Turn off Motor

		}
		    		 	
	  
	}
}



		

