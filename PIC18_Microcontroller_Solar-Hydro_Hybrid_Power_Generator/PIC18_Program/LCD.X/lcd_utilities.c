/*
 * File:   lcd utilities.c
 *
 * Created on 13 January, 2016, 10:28 AM
 */

//#include "LCD.H"	// Include file is located in the project directory

#include <xc.h>
#define _XTAL_FREQ 48000000
#define LCD_RS PORTDbits.RD6    //  Register Select on LCD
#define LCD_EN PORTDbits.RD4    //  Enable on LCD controller
#define LCD_WR PORTDbits.RD5    //  Write on LCD controller
void lcd_strobe(void);

//--- Function for writing a command byte to the LCD in 4 bit mode -------------

void lcd_write_cmd(unsigned char cmd)
{
    unsigned char temp2;
    LCD_RS = 0;					// Select LCD for command mode
    __delay_ms(4);				// 40us delay for LCD to settle down
    temp2 = cmd;
    temp2 = temp2 >> 4;			// Output upper 4 bits, by shifting out lower 4 bits
    PORTD = temp2 & 0x0F;		// Output to PORTD which is connected to LCD

    __delay_ms(8);			// 10ms - Delay at least 1 ms before strobing
    lcd_strobe();
    
	__delay_ms(8);			// 10ms - Delay at least 1 ms after strobing

    temp2 = cmd;				// Re-initialise temp2 
    PORTD = temp2 & 0x0F;		// Mask out upper 4 bits

    __delay_ms(8);			// 10ms - Delay at least 1 ms before strobing
    lcd_strobe();
    __delay_ms(8);			// 10ms - Delay at least 1 ms before strobing

}

//---- Function to write a character data to the LCD ---------------------------

void lcd_write_data(char data)
{
  	char temp1;

    LCD_RS = 1;					// Select LCD for data mode
    __delay_ms(4);				// 40us delay for LCD to settle down

    temp1 = data;
    temp1 = temp1 >> 4;
    PORTD = temp1 & 0x0F;
	__delay_ms(8); 
   	LCD_RS = 1;
    __delay_ms(8);			//_-_ strobe data in

    lcd_strobe();
    __delay_ms(8);

    temp1 = data;
    PORTD = temp1 & 0x0F;
    __delay_ms(8);
	LCD_RS = 1;
    __delay_ms(10); 			//_-_ strobe data in

    lcd_strobe();	
    __delay_ms(10);
}


//-- Function to generate the strobe signal for command and character----------

void lcd_strobe(void)			// Generate the E pulse
{
    LCD_EN = 1;					// E = 0
    __delay_ms(8);			// 10ms delay for LCD_EN to settle
    LCD_EN = 0;					// E = 1
    __delay_ms(8);			// 10ms delay for LCD_EN to settle
}


//---- Function to initialise LCD module ----------------------------------------
void lcd_init(void)
{
    int i;
    TRISD = 0x00;
    PORTD = 0x00;				// PORTD is connected to LCD data pin
    LCD_EN = 0;
    LCD_RS = 0;					// Select LCD for command mode
    LCD_WR = 0;					// Select LCD for write mode
   
    for(i=0;i<100;i++)
    __delay_ms(10);			// Delay a total of 1 s for LCD module to
			// finish its own internal initialisation

    /* The data sheets warn that the LCD module may fail to initialise properly when
       power is first applied. This is particularly likely if the Vdd
       supply does not rise to its correct operating voltage quickly enough.

       It is recommended that after power is applied, a command sequence of
       3 bytes of 30h be sent to the module. This will ensure that the module is in
       8-bit mode and is properly initialised. Following this, the LCD module can be
       switched to 4-bit mode.
    */

    lcd_write_cmd(0x33);
    lcd_write_cmd(0x32);
      
    lcd_write_cmd(0x28);		// 001010xx – Function Set instruction
    							// DL=0 :4-bit interface,N=1 :2 lines,F=0 :5x7 dots
   
    lcd_write_cmd(0x0E);		// 00001110 – Display On/Off Control instruction
    							// D=1 :Display on,C=1 :Cursor on,B=0 :Cursor Blink on
   
    lcd_write_cmd(0x06);		// 00000110 – Entry Mode Set instruction
    							// I/D=1 :Increment Cursor position
   								// S=0 : No display shift
   
    lcd_write_cmd(0x01);		// 00000001 Clear Display instruction
 
    __delay_ms(10);			// 20 ms delay

}