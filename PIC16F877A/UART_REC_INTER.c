//
//// PIC16F877A Configuration Bit Settings
//
//// 'C' source line config statements
//
//// CONFIG
#pragma config FOSC = HS        // Oscillator Selection bits (HS oscillator)
#pragma config WDTE = OFF       // Watchdog Timer Enable bit (WDT disabled)
#pragma config PWRTE = OFF      // Power-up Timer Enable bit (PWRT disabled)
#pragma config BOREN = OFF      // Brown-out Reset Enable bit (BOR disabled)
#pragma config LVP = OFF        // Low-Voltage (Single-Supply) In-Circuit Serial Programming Enable bit (RB3 is digital I/O, HV on MCLR must be used for programming)
#pragma config CPD = OFF        // Data EEPROM Memory Code Protection bit (Data EEPROM code protection off)
#pragma config WRT = OFF        // Flash Program Memory Write Enable bits (Write protection off; all program memory may be written to by EECON control)
#pragma config CP = OFF         // Flash Program Memory Code Protection bit (Code protection off)
//
//// #pragma config statements should precede project file includes.
//// Use project enums instead of #define for ON and OFF.
//
#include <xc.h>
#include <xc.h>
#include <stdio.h>
#define _XTAL_FREQ 20000000
#define lcd PORTB
#define RS RC0
#define RW RC1
#define E RC2
char RX();
//void TX();
void show_data(char *s);
void send_data(char a);
void send_cmd(char b);
void lcd_init();
void lcd_data(char a);
void __interrupt() ISR();
int main()
{
    TRISB=0x00;
    TRISC0=0;
    TRISC1=0;
    TRISC2=0;
    TRISC6=0;
    TRISC7=1;
    INTCON=0xc0;
    PIE1=0x30;
    PIR1=0x30;
    lcd_init(); 
    RCSTA = 0X90; 
    SPBRG = 129;
    show_data("ishu");
    while(1);
    
//        TX();
//        received = RX();
//        send_cmd(0x80);
//        show_data(received);
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
    RW=0;
    E=1;
    __delay_ms(200);
    E=0;
}
void show_data(char *s)
{
    while(*s)
    {
      lcd_data(*s++);
    }
}
void send_data(char a)
{
        TXREG = a;
    	while(TXIF==0);
        TXIF=0;
        __delay_ms(1000);
    
}
void lcd_data(char a)
{
    lcd = a;
    RS = 1;
    RW = 0;
    E = 1;
    __delay_ms(5);
    E = 0;
}
void __interrupt() ISR()
{
    char received = RX();
    send_cmd(0x80);
    lcd_data(received);
    send_data(received);
}
char RX()
{
    while(RCIF==0);
    RCIF=0;
    return RCREG;
}