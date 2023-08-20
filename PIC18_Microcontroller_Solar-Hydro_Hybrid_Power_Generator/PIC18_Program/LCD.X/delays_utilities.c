/*
* File:   delays_utilities.c
*
* Created on 13 January, 2016, 1:31 PM
*/

#include <xc.h>
#define _XTAL_FREQ 48000000

void delay_ms(unsigned int i)
{ unsigned int j;
	if(i!=0)  // check for i=0
	for(j=0;j<i;j++)__delay_ms(1); // call __delay_ms(1) x i times
}

// this delay is too short to be accurate - good luck.
void delay_us(unsigned int i)
{
	unsigned int j,lower;
	// for micro sec, the looping takes too long
	// so split into two parts, 20 seems to work fine
	lower = i;
	lower = lower/20;

	if (i< 5)
	{
		return; // too short no delay
	}
	else
	if(i<10)
	{
		__delay_us(7); // delay is 5 to 9 so just pick 7
	}
	else if(i< 20)
	{
		__delay_us(15); // delay is 10-19
	}
	else
	for(j=0;j<lower;j++)__delay_us(20);

}

