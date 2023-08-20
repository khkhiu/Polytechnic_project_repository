// OnOffLeds.c
// Program to use switches to control 8 leds on General I/O Board

#include <xc.h>

void main(void) {
    ADCON1 = 0x0F; //make Port A digital

    TRISA = 0b11111111; //RA5 to RA3 are connected to On/Off switches

    TRISD = 0b00000000; //RD7 to RD0 are connected to LEDs

    while (1) //repeat 
    {
        if (PORTAbits.RA3 == 0) //_____________________
        {
            PORTD = 0xF0;     // PORTD = 0b______________________
        }
        else 
        {
            PORTD = 0x0F;     // PORTD = 0b______________________
        }
    }
}




