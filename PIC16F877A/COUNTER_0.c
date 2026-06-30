#pragma config FOSC = HS
#pragma config WDTE = OFF
#pragma config PWRTE = OFF
#pragma config BOREN = OFF
#pragma config LVP = OFF
#pragma config CPD = OFF
#pragma config WRT = OFF
#pragma config CP = OFF

#include <xc.h>

#define led PORTB

void delay();

int main()
{
    TRISA=0X10;
    TRISB=0x00;
    led=0x00;

    while(1)
    {
        led=0xff;
        delay();
        led=0x00;
        delay();
    }
}

void delay()
{
    OPTION_REG=0X28;// 0 0 1 0 1 0 0 0
    TMR0= 254;
    while (TMR0IF==0);
    TMR0IF=0;
}