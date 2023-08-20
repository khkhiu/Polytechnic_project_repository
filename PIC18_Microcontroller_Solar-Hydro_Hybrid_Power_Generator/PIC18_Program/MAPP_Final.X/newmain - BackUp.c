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
        delay_ms(2.1);
        PORTCbits.RC1=0;
        delay_ms(17.9);
        PORTCbits.RC0=1;
        delay_ms(2.1);
        PORTCbits.RC0=0;
        delay_ms(17.9);
    }   
        
        lcd_write_cmd(0x80); // Move cursor to line 1 position 1
        for (i = 0; i < 4; i++) //for 20 char LCD module
        {
            delay_ms(1000);
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
        delay_ms(1000);
        lcd_write_data('N'); // write character data to LCD
        lcd_write_data('O'); // write character data to LCD
        lcd_write_data('O'); // write character data to LCD
        lcd_write_data('N'); // write character data to LCD
        break;
    }
    
    delay_ms(1000);
    for (count = 0; count<10; count++)
    {
        PORTCbits.RC1=1;
        delay_ms(0.9);
        PORTCbits.RC1=0;
        delay_ms(19.1);
        PORTCbits.RC0=1;
        delay_ms(0.9);
        PORTCbits.RC0=0;
        delay_ms(19.1);
    }  

    lcd_write_cmd(0x80); // Move cursor to line 1 position 1
    for (i = 0; i < 4; i++) //for 20 char LCD module
    {
        delay_ms(1000);
        lcd_write_data('W'); // write character data to LCD
        lcd_write_data('E'); // write character data to LCD
        lcd_write_data('S'); // write character data to LCD
        lcd_write_data('T'); // write character data to LCD
        break;
    }
}

void interrupt KeyPad(void)
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
            delay_ms(1000);
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
    //TRISBbits.TRISB1 = 1;	// RB1 is the push button switch for INT1
    //TRISBbits.TRISB2 = 1;	// RB2 is the push button switch for INT2

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

    while(1)
    {
        Tracking();
    }
}
