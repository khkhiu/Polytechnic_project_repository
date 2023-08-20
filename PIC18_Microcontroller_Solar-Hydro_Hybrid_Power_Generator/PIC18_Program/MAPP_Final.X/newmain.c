/*
 * File:   servo.c
 * Author: khiu_
 *
 * Created on 28 July, 2021, 9:42 AM
 */


#include <xc.h>
#include "keypad.h"
#include "delays.h"
#include "lcd.h"	

unsigned char press;
int i;
unsigned char count;

void Tracking(void)
{
    TRISC = 0b00000000;// use PORTC as output for servos
    
     // Initialize LCD module

    lcd_init();
        
    delay_ms(1000);
    for (count = 0; count<10; count++)
    {
        PORTCbits.RC1=1;
        delay_ms(2);
        PORTCbits.RC1=0;
        delay_ms(18);
        PORTCbits.RC0=1;
        delay_ms(0.9);
        PORTCbits.RC0=0;
        delay_ms(19.1);
    }   
        
        lcd_write_cmd(0x80); // Move cursor to line 1 position 1
        for (i = 0; i < 4; i++) //for 20 char LCD module
        {
            lcd_write_data('E'); // write character data to LCD
            lcd_write_data('A'); // write character data to LCD
            lcd_write_data('S'); // write character data to LCD
            lcd_write_data('T'); // write character data to LCD
            break;
        }
        
    delay_ms(1000);
    for (count = 0; count<10; count++)
    {
        PORTCbits.RC1=1;
        delay_ms(1.6);
        PORTCbits.RC1=0;
        delay_ms(18.4);
        PORTCbits.RC0=1;
        delay_ms(1.6);
        PORTCbits.RC0=0;
        delay_ms(18.4);
    }  

    lcd_write_cmd(0x80); // Move cursor to line 1 position 1
    for (i = 0; i < 4; i++) //for 20 char LCD module
    {
        lcd_write_data('M'); // write character data to LCD
        lcd_write_data('I'); // write character data to LCD
        lcd_write_data('D'); // write character data to LCD
        lcd_write_data('D'); // write character data to LCD
        break;
    }
    
    delay_ms(1000);
    for (count = 0; count<6; count++)
    {
        PORTCbits.RC1=1;
        delay_ms(0.9);
        PORTCbits.RC1=0;
        delay_ms(19.1);
        PORTCbits.RC0=1;
        delay_ms(2);
        PORTCbits.RC0=0;
        delay_ms(18);
    }  

    lcd_write_cmd(0x80); // Move cursor to line 1 position 1
    for (i = 0; i < 4; i++) //for 20 char LCD module
    {
        lcd_write_data('W'); // write character data to LCD
        lcd_write_data('E'); // write character data to LCD
        lcd_write_data('S'); // write character data to LCD
        lcd_write_data('T'); // write character data to LCD
        break;
    }
    
        delay_ms(1000);
    for (count = 0; count<10; count++)
    {
        PORTCbits.RC1=1;
        delay_ms(1.6);
        PORTCbits.RC1=0;
        delay_ms(18.4);
        PORTCbits.RC0=1;
        delay_ms(1.6);
        PORTCbits.RC0=0;
        delay_ms(18.4);
    }  

    lcd_write_cmd(0x80); // Move cursor to line 1 position 1
    for (i = 0; i < 4; i++) //for 20 char LCD module
    {
        lcd_write_data('M'); // write character data to LCD
        lcd_write_data('I'); // write character data to LCD
        lcd_write_data('D'); // write character data to LCD
        lcd_write_data('D'); // write character data to LCD
        break;
    }
}

void interrupt Stop (void)
{
 if (INTCONbits.INT0IF)	// External Interrupt Flag Bit = 1 when interrupt occurred
  {
	press++;		// To track first or second time pressing RB0 switch
	
	if (press == 1)		// First press
	{
        for (count = 0; count<10; count++)
        {
            PORTCbits.RC1=1;
            delay_ms(1.5);
            PORTCbits.RC1=0;
            delay_ms(18.5);
            PORTCbits.RC0=1;
            delay_ms(1.5);
            PORTCbits.RC0=0;
            delay_ms(18.5);
        }   

        lcd_write_cmd(0x80); // Move cursor to line 1 position 1
        for (i = 0; i < 4; i++) //for 20 char LCD module
        {
            lcd_write_data('S'); // write character data to LCD
            lcd_write_data('T'); // write character data to LCD
            lcd_write_data('O'); // write character data to LCD
            lcd_write_data('P'); // write character data to LCD
            lcd_write_data('!'); // write character data to LCD
            break;
        }	 
        while(1);
   	}
	else
	if (press == 2)		// Second press
	{
        Tracking();
        press=0;
	}
        INTCONbits.INT0IF = 0;  //Clearing the flag at the end of the ISR
  }
}

void main(void) {
    unsigned char press;
    press = 0;		// Not pressing yet
    
	ADCON1 = 0x0F;
	CMCON = 0x07;

    //For interrupt
	TRISBbits.TRISB0 = 1;	// RB0 is the push button switch for INT0

	TRISB=0x07;                                 //Configuring interrupt pins as input
    INTCONbits.GIEH=1;                          //Enabling High priority interrupts
    INTCONbits.GIEL=1;                          //Enabling Low priority interrupts
    RCONbits.IPEN=1;                            //Enabling Interrupt priority
    
    //For int0
    INTCONbits.INT0IE=1;                        //Enabling INT0 interrupt
    INTCONbits.INT0IF=0;                        //clearing INT0 interrupt flag
    
    while(1)
    {
        Tracking();
    }
}
