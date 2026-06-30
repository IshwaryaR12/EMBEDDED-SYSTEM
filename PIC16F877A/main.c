
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
#include <xc.h>
#include <stdio.h>
#define _XTAL_FREQ 20000000
#define lcd PORTB
#define RS RC0
#define E RC1

void send_data(char a);
void show_data(char *st);
void send_cmd(char b);
void display(unsigned int h,unsigned int m,unsigned int s);
void lcd_init();
int main()
{
    TRISB = 0x00;
    TRISC=0x00;
    __delay_ms(20);
    lcd_init();
    while(1)
    {
        unsigned int h=0;
        unsigned int m=0;
        unsigned int s=0;
        for(h=0;h<12;h++)
        {
            for(m=0;m<=59;m++)
            {
                for(s=0;s<=59;s++)
                {
                    display(h,m,s);         
                }
            }
        }
    }
}
void lcd_init()
{
    send_cmd(0x38);
	send_cmd(0x0e);
	send_cmd(0x01);
	send_cmd(0x06);
	send_cmd(0x80);
	send_cmd(0x0c);
}
void send_cmd(char b)
{
    lcd = b;
    RS=0;
    E=1;
    __delay_ms(1);
    E=0;
}
void send_data(char a)
{
    lcd=a;
    RS=1;
    E=1;
    __delay_ms(1);
    E=0;
}
void display(unsigned int h,unsigned int m,unsigned int s)
{
    char b[16];
    sprintf(b,"%02d:%02d:%02d",h,m,s);
    show_data(b);
    
}
void show_data(char *st)
{
    send_cmd(0x80);
    while(*st)
    {
        send_data(*st++);
    }
}