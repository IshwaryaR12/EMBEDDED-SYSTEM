
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
#include <stdio.h>
#define _XTAL_FREQ 20000000
#define lcd PORTB
#define RS RD5
#define RW RD6
#define E RD7
#define SS RC2
void send_data(char a);
void show_data(char *s);
void send_cmd(char b);
unsigned char spi_master_data(unsigned char a);
void spi_master_ini();
void tc72_ini();
void lcd_init();
int main()
{
    char b[16];
    char tem_w;
    TRISB = 0x00;
    TRISD=0x00;
    TRISC=0X10;
    SS=0;
    lcd_init();
    spi_master_ini();
    lcd_init();
    tc72_ini();
    send_cmd(0x80);
    show_data("TC72 Temp:");
    while(1)
    {
    SS=1;
    spi_master_data(0x02);
    tem_w=spi_master_data(0x00);
//    spi_master_data(0x00);
    SS=0;
    sprintf(b,"%d%cC",(signed)tem_w,223);
    send_cmd(0xc0);
    show_data(b);
    __delay_ms(1000);
    }
    
}
void spi_master_ini()
{
    SSPCON=0x20;
    SSPSTAT=0x00;
}
unsigned char spi_master_data(unsigned char a)
{
    SSPBUF = a;
    while(SSPIF == 0);
    SSPIF = 0;
    return SSPBUF;
}

void tc72_ini()
{
    SS=1;
    spi_master_data(0x80);
    spi_master_data(0x00);
    SS=0;
    __delay_ms(100);
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
    __delay_ms(5);
    E=0;
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
    lcd=a;
    RS=1;
    RW=0;
    E=1;
    __delay_ms(5);
    E=0;
}