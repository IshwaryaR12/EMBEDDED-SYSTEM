
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
#include<stdio.h>
#define _XTAL_FREQ 20000000
#define lcd PORTB
#define RS RD7
#define RW RD6 
#define EN RD5
void lcd_init();
void send_cmd(char a);
void send_data(char b);
void show_data(char *s);
void capture();
void timer1();

int main()
{
    char result[50];
    unsigned int cap;
    TRISB=0X00;
    TRISD=0X00;
    TRISC2=1;
    lcd_init();
    timer1();
    capture();
    send_cmd(0x80);
    show_data("Captured Value"); 
    while(1)
    {
        cap=((CCPR1H<<8)|CCPR1L);
        send_cmd(0xc0);
        sprintf(result,"%05u",cap);
        show_data(result);
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
void send_cmd(char a)
{
	lcd=a;
	RS=0;
	RW=0;
	EN=1;
	__delay_ms(1);
	EN=0;
}
void send_data(char b)
{
	lcd=b;
	RS=1;
	RW=0;
	EN=1;
	__delay_ms(100);
	EN=0;
}
void show_data(char *s)
{
	while(*s)
	{
		send_data(*s++);
	}
}
void timer1()
{
    T1CON=0X31;
    TMR1H=0;
    TMR1L=0;
}
void capture()
{
    CCP1CON=0X05;
    CCPR1H=0;
    CCPR1L=0;
}

