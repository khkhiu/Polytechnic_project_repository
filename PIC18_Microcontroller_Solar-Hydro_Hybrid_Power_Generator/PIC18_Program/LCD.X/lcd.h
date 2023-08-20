/*  file : lcd.h 
 *	LCD interface header file
 *	See lcd.c for more info
 */

 /* intialize the LCD - call before anything else */
extern void lcd_init(void);

/* write a byte to the LCD in 4 bit mode */
extern void lcd_write_cmd(unsigned char cmd);

//extern void lcd_write(unsigned char i);
extern void lcd_write_data(char data);



