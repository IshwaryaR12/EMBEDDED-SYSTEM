
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
void show_data(char *s);
void send_data(char a);
void __interrupt() ISR(void);
int main()
{
    TRISC6=0;
    TXSTA = 0X26; 
    RCSTA = 0X80;
//    show_data("ishu");
    INTCON=0xc0;
    PIE1=0x30;
    PIR1=0x30;
    SPBRG = 129;
//    show_data("ishu");
//    while(TXIF==0);
}
void show_data(char *s)
{
	while(*s)
	{
		send_data(*s++);
	}
}
void send_data(char a)
{
	 TXREG = a;
     while(TXIF==0);
     TXIF=0;
     __delay_ms(1000);
}
void __interrupt() ISR(void)
{
     show_data("ishu");
//     while(TXIF==0);
     TXIE=0;
}