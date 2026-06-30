#include<reg51.h>
#define lcd_data P3

sbit RS=P2^0;
sbit RW=P2^1;
sbit EN=P2^2;

sbit s1=P2^4;

void lcd_init();
void send_cmd(char a);
void send_dat(char b);
void show_dat(char *s);
void lcd_delay(int time);
		
int main()
	{
	lcd_data=0x00;
	 lcd_init();
	while(1)
		{
			send_cmd(0x80);
			if(s1==0)
			{
			show_dat("BUTTON PRESSED");
			}
			send_cmd(0xc0);
			if(s1==1)
			{
			show_dat("BUTTON NOT PRESSED");
			}
			lcd_delay(1000);
			send_cmd(0x01);
			lcd_delay(1000);
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
	
void lcd_delay(int time)
	{
		int i,j;
		for(i=0;i<time;i++)
		for(j=0;j<100;j++);
	}