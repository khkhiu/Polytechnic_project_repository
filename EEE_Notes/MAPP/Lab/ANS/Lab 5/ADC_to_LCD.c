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

#include <p18F4550.h>
#include <delays.h>

// Include this when using Bootloader Program ================================
#pragma udata

extern void _startup (void);        // See c018i.c in your C18 compiler dir
#pragma code _RESET_INTERRUPT_VECTOR = 0x000800
void _reset (void)
{
    _asm goto _startup _endasm
}
#pragma code

#pragma code _HIGH_INTERRUPT_VECTOR = 0x000808
void _high_ISR (void)
{
    ;
}

#pragma code _LOW_INTERRUPT_VECTOR = 0x000818
void _low_ISR (void)
{
    ;
}
#pragma code

#pragma code

// additional codes ends here ===============================================================

// Your program declarations start here:====

//----------------------------------------------------------


#define LCD_RS PORTDbits.RD6    //  Register Select on LCD
#define LCD_EN PORTDbits.RD4    //  Enable on LCD controller
#define LCD_WR PORTDbits.RD5    //  Write on LCD controller



//-- Function to generate the strobe signal for command and character----------

void lcd_strobe(void)			// Generate the E pulse
{
    LCD_EN = 1;					// E = 0
    Delay1KTCYx(100);			// 10ms delay for LCD_EN to settle
    LCD_EN = 0;					// E = 1
    Delay1KTCYx(100);			// 10ms delay for LCD_EN to settle
}

//--- Function for writing a command byte to the LCD in 4 bit mode -------------

void lcd_write_cmd(signed char cmd)
{
    unsigned char temp2;
    LCD_RS = 0;					// Select LCD for command mode
    Delay10TCYx(4);				// 40us delay for LCD to settle down
    temp2 = cmd;
    temp2 = temp2 >> 4;			// Output upper 4 bits, by shifting out lower 4 bits
    PORTD = temp2 & 0x0F;		// Output to PORTD which is connected to LCD

    Delay1KTCYx(10);			// 10ms - Delay at least 1 ms before strobing
    lcd_strobe();
    
	Delay1KTCYx(10);			// 10ms - Delay at least 1 ms after strobing

    temp2 = cmd;				// Re-initialise temp2 
    PORTD = temp2 & 0x0F;		// Mask out upper 4 bits

    Delay1KTCYx(10);			// 10ms - Delay at least 1 ms before strobing
    lcd_strobe();
    Delay1KTCYx(10);			// 10ms - Delay at least 1 ms before strobing

}

//---- Function to write a character data to the LCD ---------------------------

void lcd_write_data(char data)
{
  	char temp1;

    LCD_RS = 1;					// Select LCD for data mode
    Delay10TCYx(4);				// 40us delay for LCD to settle down

    temp1 = data;
    temp1 = temp1 >> 4;
    PORTD = temp1 & 0x0F;
	Delay1KTCYx(10); 
   	LCD_RS = 1;
    Delay1KTCYx(10);			//_-_ strobe data in

    lcd_strobe();
    Delay1KTCYx(10);

    temp1 = data;
    PORTD = temp1 & 0x0F;
    Delay1KTCYx(10);
	LCD_RS = 1;
    Delay1KTCYx(10); 			//_-_ strobe data in

    lcd_strobe();	
    Delay1KTCYx(10);
}


//---- Function to initialise LCD module ----------------------------------------
void lcd_init(void)
{
    TRISD = 0x00;
    PORTD = 0x00;				// PORTD is connected to LCD data pin
    LCD_EN = 0;
    LCD_RS = 0;					// Select LCD for command mode
    LCD_WR = 0;					// Select LCD for write mode
   
    Delay10KTCYx(250);			// Delay a total of 1 s for LCD module to
    Delay10KTCYx(250);			//
    Delay10KTCYx(250);			//
    Delay10KTCYx(250);			// finish its own internal initialisation

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
 
    Delay1KTCYx(20);			// 20 ms delay

}

//----------------------------------------------------------
main(void)
{
	#define HIGH 0xD0   // HIGH water level indicator
	#define N 4
	unsigned char buffer[N];
	int i;

	unsigned int result_10bit;

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

	ADCON2 = 0b10010110;	// bit7   : A/D Result Format. 0 Left, 1 Right justified
							// bit5-3 : 010 acquisition time = 4 TAD
							// bit2-0 : 110 conversion clock = Tosc / 16
	lcd_init();					// Initialise LCD module
    lcd_write_cmd(0x01);		// Clear Display instruction

	while(1)
	{
		ADCON0bits.GO = 1;		// This is bit2 of ADCON0, START CONVERSION NOW
	        
		while(ADCON0bits.GO == 1); 	// Waiting for DONE 
			
		result_10bit = ADRESH;
		result_10bit = (result_10bit << 8) + ADRESL;

		for (i=0; i<N; ++i)
			buffer[i]=' ';	//Clear the buffer contents

		itoa(result_10bit, buffer); //Convert result to text
		
   		lcd_write_cmd(0x80);		// Move cursor to line 1 position 1
  
		for (i=0; i<N; ++i)
			lcd_write_data(buffer[i]);
	  
	}
}



		

