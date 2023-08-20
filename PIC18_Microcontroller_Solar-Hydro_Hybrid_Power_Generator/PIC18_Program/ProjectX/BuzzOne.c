// BuzzOne.c
// Program to activate buzzer with one tone
// For project using USB interface with Bootloader

#include <xc.h>
#include "delays.h"

void onetone(void) //Function to generate one tone
{
    unsigned int k;

    for (k = 0; k < 100; k++) //Determines duration of tone
    {
        delay_us(3000);  // useable values from 100  to 5000
        PORTCbits.RC0 = !PORTCbits.RC0; //Invert logic level at RC0
    }
}

void main(void) {

    TRISCbits.TRISC0 = 0; //-- Set RC0 as output

    TRISD = 0x00; //-- Set all pins on PortD as output

    {
        onetone(); //sound ON then OFF
        PORTD = 0b10101010; //pattern on LEDs
        delay_ms(500);

        onetone(); //sound ON then OFF
        PORTD = 0b01010101; //another pattern on LEDs
        delay_ms(500);
		
        while (1); // loop forever to stop music!
    }
}





