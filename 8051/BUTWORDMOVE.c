#include<reg51.h>
#define lcd_data P0

sbit RS=P2^0;
sbit RW=P2^1;
sbit EN=P2^2;

sbit s1=P3^0;

void lcd_init();
void send_cmd(char a);
void send_data(char b);
void show_data(char *s);
void lcd_delay(int time);
		
void main()
	{
	lcd_data=0x00;
	 lcd_init();
	while(1)
		{
			send_cmd(0x80);
			if(s1==0)
			{
			  show_data("ADVANCE HAPPY BIRTHDAY HARISH");
				while(1)
				{
				if(s1==1)
			  {
           break;
			  }
				send_cmd(0x1C);
				lcd_delay(200);
				}
			}
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

void send_data(char b)
	{
		lcd_data=b;
		RS=1;
		RW=0;
		EN=1;
		lcd_delay(100);
		EN=0;
	}

void show_data(char *s)
	{
		while(*s)
			{
				send_data(*s++);
			}
	}	
	
void lcd_delay(int time)
	{
		int i,j;
		for(i=0;i<time;i++)
		for(j=0;j<100;j++);
	}