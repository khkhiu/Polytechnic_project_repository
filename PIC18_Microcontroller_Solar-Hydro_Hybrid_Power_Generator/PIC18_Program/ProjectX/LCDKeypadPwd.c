// LCDKeypad.c
// Program to test LCD and keypad.
// For project using USB interface with Bootloader

#include <xc.h>
#include "lcd.h"
#include "delays.h"
#include "keypad.h"

unsigned char key, outchar;
unsigned char p1, p2, p3, p4;
char Message1 [ ] = "Enter PIN number :  "; // Defining a 20 char string

void main(void) {
    int i;
    lcd_init(); // Initialise LCD module

    while (1) {

        lcd_write_cmd(0x80); // Move cursor to line 1 position 1
        for (i = 0; i < 20; i++) //for 20 char LCD module
        {
            outchar = Message1[i];
            lcd_write_data(outchar); // write character data to LCD
        }

        lcd_write_cmd(0xC0); // Move cursor to line 2 position 1

        key = getkey(); // waits and get an ascii key number when pressed
        p1 = key;
        lcd_write_data(key); //display on LCD

        key = getkey(); // waits and get an ascii key number when pressed
        p2 = key;
        lcd_write_data(key); //display on LCD

        key = getkey(); // waits and get an ascii key number when pressed
        p3 = key;
        lcd_write_data(key); //display on LCD

        key = getkey(); // waits and get an ascii key number when pressed
        p4 = key;
        lcd_write_data(key); //display on LCD

        if (p1 == '4' && p2 == '5' && p3 == '5' && p4 == '0') {
            lcd_write_data(0x20);
            lcd_write_data('O');
            lcd_write_data('P');
            lcd_write_data('E');
            lcd_write_data('N');
            lcd_write_data(0x20);
        } else {
            lcd_write_data(0x20);
            lcd_write_data('W');
            lcd_write_data('R');
            lcd_write_data('O');
            lcd_write_data('N');
            lcd_write_data('G');
        }

    }
}




