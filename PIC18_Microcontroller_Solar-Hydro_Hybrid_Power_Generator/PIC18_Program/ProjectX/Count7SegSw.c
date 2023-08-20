// Count7SegSw.c
// Counting on 4 7-segment display by a switch on 7-seg Board

#include <xc.h>
#include "delays.h"
#include "seg7.h"

unsigned char point, outchar, press;

void main(void) {
    char i;
    TRISB = 0b11110000; //RB3 to RB0 are connected DIG3 to DIG0 active high
                        //RB5 is connected to a switch

    TRISD = 0b00000000; //RD7 to RD0 are connected to segment LEDs active high

    val[3] = 9; //contents of DIG3
    val[2] = 8; //contents of DIG2
    val[1] = 7; //contents of DIG1
    val[0] = 6; //contents of DIG0
    press = 0;

    while (1) //repeat 
    {

        point = 0b00000001; //enable DIG0

        for (i = 0; i < 4; i++) 
        {
            PORTB = point; //enable one DIG
            outchar = val[i]; //get one value for the DIG
            PORTD = convert(outchar); //convert to LED code

            point = point << 1; //point to the next DIG
            delay_ms(1);

        }
        if (press == 0) //switch press first time
        {
            if (PORTBbits.RB5 == 0) //if RB5sw is ON
            {
                press = 1; //switch being pressed
                val[0] = val[0] + 1; //increase DIG0 value 
                update(); //adjust the rest of values

            }
        }

        if (PORTBbits.RB5 == 1) press = 0; //switch released
    }
}




