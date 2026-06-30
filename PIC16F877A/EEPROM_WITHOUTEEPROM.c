
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
unsigned int my_data;
#define c RC0
//#define cl RC3
//#define cl RC3
//#define cl RC3
//#define cl RC3
void EEPROM_Write(unsigned char address, unsigned char data);
unsigned char EEPROM_Read(unsigned char address);

void main()
{
    TRISC0=0;
    TRISC1=0;
    TRISC2=0;
    TRISC3=0;
    TRISC5=0;
    TRISC6=0;
    TRISC7=0;
    TRISC4=1;
    EEPROM_Write(0x00, 'Z');
    
    __delay_ms(100);
    unsigned char my_data = EEPROM_Read(0x00);
    while(1);
}

void EEPROM_Write(unsigned char address, unsigned char data)
{
    c=0;
    EEADR = address;    
    EEDATA = data;      
    EEPGD = 0; 
    WREN = 1;
    EECON2 = 0x55;
    EECON2 = 0xAA;
    WR = 1;
    
    while(WR);
    WREN = 0;
    c=1;
}

unsigned char EEPROM_Read(unsigned char address)
{
    EEADR = address;
    EEPGD = 0;
     RD = 1;  
    return EEDATA;
}
