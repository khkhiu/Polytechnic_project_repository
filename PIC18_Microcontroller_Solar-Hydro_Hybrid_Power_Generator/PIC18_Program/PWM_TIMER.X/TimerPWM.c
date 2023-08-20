/* TimerPWM.c Program to generate PWM at RC2
 *  Use Timer2
 *  Frequency of OSC = 48 MHz, Prescaler = 16
 *  PR2 register set the frequency of waveform
 *  CCPR1L with CP1CONbits.DC1B0, CCP1CONbits.DC1B1 set the On-Time 
 *  Use Timer0 for the one second delay function
 */
#include <xc.h>

void Delay1sec(void); //Function to provide 1 sec delay using Timer0

void Delay1sec(void) {
    TMR0H = 0X48; //Starting count value
    TMR0L = 0XE5;

    INTCONbits.TMR0IF = 0; //Clear flag first
    T0CONbits.TMR0ON = 1; //Turn on Timer 0

    while (INTCONbits.TMR0IF == 0); //Wait for time is up when TMR0IF=1 
    T0CONbits.TMR0ON = 0; //Turn off Timer 0 to stop counting
}

void main(void) {
    // Do not remove these as well=============
    ADCON1 = 0x0F;
    CMCON = 0x07;
    // ========================================
    // Your MAIN program Starts here: =========
    TRISC = 0x00; //PortC RC2 connects to motor
    TRISD = 0x00; //PortD connected to 8 LEDs
    T0CON = 0b00000111; //Off Timer0, 16-bits mode, prescaler to 256

    T2CON = 0b00000111; //Timer2 is On, Prescaler is 16

    CCP1CON = 0b00001100; //Turn on PWM on CCP1, output at RC2
    PR2 = 1575; //Load period of PWM 0.2msec for 5KHz

    while (1) //Repeatedly
    {
        CCPR1L = 1124; // Duty cycle 25%, 149 x 25% = 37


        Delay1sec();
        Delay1sec();


    }
}


