
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
#define lcd_data PORTB
#define _XTAL_FREQ 20000000
#define R1 RD0
#define R2 RD1
#define R3 RD2
#define R4 RD3
#define C1 RD4
#define C2 RD5
#define C3 RD6
#define C4 RD7
#define RS RC0
#define RW RC1
#define EN RC2

void lcd_init();
void send_cmd(unsigned char a);
void send_data(unsigned char b);
void show_dat(unsigned char *s);
unsigned char keypad();

void main()
{
	unsigned char key,op;
	int result,n1,n2;
    TRISB=0x00;
    TRISC0 =0;
    TRISC1=0;
    TRISC2=0;
    TRISD =0xF0;
	lcd_init();		
	while(1)
	{
		  key=keypad();
		  if(key=='C')
			{
				continue;
			}
			n1=key-'0';
			send_data(key);
			op=keypad();
			send_data(op);
			key=keypad();
			n2=key-'0';
			send_data(key);
			key=keypad();
			if(key=='=')
			{
				send_data('=');
				switch(op)
				{
					case '+':
						result=n1+n2;
					break;
					case '-':
						result=n1-n2;
					break;
					case '*':
						result=n1*n2;
					break;
					case '/':
						if(n2!=0)
						{
						result=n1/n2;
						}
					break;
				}
				if(result>9)
			  {
				send_data((result/10)+'0');
				send_data((result%10)+'0');
			  }
			  else
			  {
				 send_data(result+'0');
			  }
			}
      while(keypad()!='C');
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

void send_cmd(unsigned char a)
	{
		lcd_data=a;
		RS=0;
		RW=0;
		EN=1;
		__delay_ms(1);
		EN=0;
	}

void send_data(unsigned char b)
	{
		lcd_data=b;
		RS=1;
		RW=0;
		EN=1;
		__delay_ms(1);
		EN=0;
	}

void show_data(unsigned char *s)
	{
		while(*s)
			{
				send_data(*s++);
			}
	}

void lcd_delay(unsigned int time)
	{
		int i,j;
		for(i=0;i<time;i++)
		for(j=0;j<100;j++);
	}

unsigned char keypad()
{
	while(1)
	{
		R2=R3=R4=1;
		R1=0;
		if(C1==0)
		{
			while(C1==0);
			return '7';
		}
		if(C2==0)
		{
			while(C2==0);
			return '8';
		}
		if(C3==0)
		{
			while(C3==0);
			return '9';
		}
		if(C4==0)
		{
			while(C4==0);
			return '/';
		}
		
		R1=R3=R4=1;
		R2=0;
		if(C1==0)
		{
			while(C1==0);
			return '4';
		}
		if(C2==0)
		{
			while(C2==0);
			return '5';
		}
		if(C3==0)
		{
			while(C3==0);
			return '6';
		}
		if(C4==0)
		{
			while(C4==0);
			return '*';
		}
		
		R1=R2=R4=1;
		R3=0;
		if(C1==0)
		{
			while(C1==0);
			return '1';
		}
		if(C2==0)
		{
			while(C2==0);
			return '2';
		}
		if(C3==0)
		{
			while(C3==0);
			return '3';
		}
		if(C4==0)
		{
			while(C4==0);
			return '-';
		}
		
		R1=R2=R3=1;
		R4=0;
		if(C1==0)
		{
			send_cmd(0x01);
			return 'C';
		}
		if(C2==0)
		{
			while(C2==0);
			return '0';
		}
		if(C3==0)
		{
			while(C3==0);
			return '=';
		}
		if(C4==0)
		{
			while(C4==0);
			return '+';
		}
	}
}
