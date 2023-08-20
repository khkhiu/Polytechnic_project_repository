// BlinkLeds.c
// Program to use 1 switch to control 8 leds on General I/O Board

#include <xc.h>
#include "delays.h"

void main(void) {
    ADCON1 = 0x0F; //make Port A digital

    TRISA = 0b11111111; //RA5 to RA3 are connected to On/Off switches

    TRISD = 0b00000000; //RD7 to RD0 are connected to LEDs

    while (1) //repeat 
    {
        PORTD = 0b10101010;
        delay_ms(1000);

        PORTD = 0b01010101;
        delay_ms(1000);

    }
}




