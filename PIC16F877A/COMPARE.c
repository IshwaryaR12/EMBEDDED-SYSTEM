
// PIC16F877A Configuration Bit Settings

// 'C' source line config statements

// CONFIG
#pragma config FOSC = HS        // Oscillator Selection bits (HS oscillator)
#pragma config WDTE = OFF       // Watchdog Timer Enable bit (WDT disabled)
#pragma config PWRTE = OFF      // Power-up Timer Enable bit (PWRT disabled)
#pragma config BOREN = OFF      // Brown-out Reset Enable bit (BOR disabled)
#pragma config LVP = OFF        // Low-Voltage (Single-Supply) In-Circuit Serial Programming Enable bit (RB3 is digital I/O, HV on MCLR must be used for programming)
#pragma config CPD = OFF        // Data EEPROM Memory Code Protection bit (Data EEPROM code protection off)
#pragma config WRT = OFF        // Flash Program Memory Write Enable bits (Write protection off; all program memory may be written to by EECON control)
#pragma config CP = OFF         // Flash Program Memory Code Protection bit (Code protection off)

// #pragma config statements should precede project file includes.
// Use project enums instead of #define for ON and OFF.

#include <xc.h>
#define _XTAL_FREQ 20000000

void compare();
void compare_set();
void compare_reset();

int main()
{
    TRISC = 0x00;
    PORTC = 0x00;
    while(1)
    {
        compare_set();
        __delay_ms(1000);

        compare_reset();
        __delay_ms(1000);
    }
}


void compare_set()
{
    CCP1CON = 0x08;// 0000 1000
    CCPR1 = 1000;
    compare();
}

void compare_reset()
{
    CCP1CON = 0x09;// 0000 1001
    CCPR1 = 6000;
    compare();
}

void compare()
{
    TMR1  = 0;
    T1CON = 0X31;
    while(CCP1IF == 0);
    CCP1IF = 0;
    while(TMR1IF == 0);
    TMR1IF=0;
    TMR1ON=0;
}