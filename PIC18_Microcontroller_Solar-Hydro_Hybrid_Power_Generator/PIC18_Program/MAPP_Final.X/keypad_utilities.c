/*
 * File:   keypad utilities.c
 *
 * Created on 13 January, 2016, 10:46 AM
 */


#include <xc.h>


#define KEY_DA PORTBbits.RB5   	//  74922 DA output
#define KEY_PORT PORTB			//	RB3 to RB0 has keypad data


//----- Function to obtained wait for key press and returns its ASCII value

char getkey(void)
{	char keycode;
    const unsigned char lookup[] = "123F456E789DA0BC ";

    while (KEY_DA==0);			//wait for key to be pressed
    keycode=KEY_PORT & 0x0F;		//read from encoder at portB,mask upper 4 bits

    while (KEY_DA==1);			//wait for key to be released
    return(lookup[keycode]);	//convert keycode to its ascii value for LCD
}

