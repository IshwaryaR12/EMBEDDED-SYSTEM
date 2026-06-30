#include<reg51.h>
#define lcd_data P0

sbit RS=P2^0;
sbit RW=P2^1;
sbit EN=P2^2;

sbit s1=P3^4;
sbit s2=P3^5;

void lcd_init();
void send_cmd(char a);
void send_dat(char b);
void show_dat(char *s);

void count02();
void count13();
void lcd_delay(int time);

int main()
	{
	 lcd_data=0x00;
	 lcd_init();
	 while(1)
		{
			lcd_delay(1000);
			send_cmd(0x80);
			count02();
			send_cmd(0x80);
			show_dat("Counter 2");
			send_cmd(0xc0);
			show_dat("is working");
			count13();
			lcd_delay(1000);
			send_cmd(0x01);
			send_cmd(0x80);
			show_dat("Counte 3");
			send_cmd(0xc0);
			show_dat("is working");
		}
	}
	
void send_cmd(char a)
	{
		lcd_data=a;
		RS=0;
		RW=0;
		EN=1;
		lcd_delay(1);
		EN=0;
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

void send_dat(char b)
	{
		lcd_data=b;
		RS=1;
		RW=0;
		EN=1;
		lcd_delay(100);
		EN=0;
	}

void show_dat(char *s)
	{
		while(*s)
			{
				send_dat(*s++);
			}
	}	
	
void count02()
	{
	  TMOD=0x05;
	  TR0=1;
		TH0=0xFF;
		TL0=0xFE;
		while(TF0==0);
		TF0=0;
	  TR0=0;
	}
void count13()
	{
	  TMOD=0x50;
	  TR1=1;
		TH1=0xFF;
		TL1=0xFD;
		while(TF1==0)
		{
			;
		}
		TF1=0;
		
		TR1=0;
	}
	void lcd_delay(int time)
	{
		int i,j;
		for(i=0;i<time;i++);
		for(j=0;j<100;j++);
	}