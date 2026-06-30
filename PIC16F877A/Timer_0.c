
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
#define led PORTB
void delay(unsigned int time);
int main()
{
    TRISB=0x00;
    led=0x00;
    while(1)
    {
        led=0xFF;
        delay(3);
        led=0x00;
        delay(2);
    }
}
void delay(unsigned int time)
{
    unsigned int i;
    OPTION_REG=0x07;
    if(time==3)
    {
    for(i=0;i<time;i++)
    {
        TMR0=251;
        while(TMR0IF==0);
        TMR0IF=0;
    }
    }
    else if(time==2)
    {
    for(i=0;i<time;i++)
    {
        TMR0=252;
        while(TMR0IF==0);
        TMR0IF=0;
    }
    }
}
