#include<reg51.h>
#define lcd_data P0
#define lcd_data1 P3
sbit RS=P2^0;
sbit RW=P2^1;
sbit E=P2^2;
sbit R_S=P2^4;
sbit RW1=P2^5;
sbit E1=P2^6;

void lcd_int();
void send_cmd(char a);
void sendcmdoo(char a);
void delay02(int time);
void delay14(int time);
void show_data(char *s);
void show(char *s);
void send_data(char b);
void send(char b);
int main()
{
	lcd_data=0x00;
	lcd_data1=0x00;
	lcd_int();
	while(1)
	{
		send_cmd(0x80);
		show_data("EMBEDDED SYSTEM");
		delay14(200);
		send_cmd(0x01);
    delay02(500);
		show("ISHWARYA R");
    delay14(100);
		sendcmdoo(0x01);
	}
}
void lcd_int()
{
	send_cmd(0x38);
	send_cmd(0x0e);
	send_cmd(0x01);
	send_cmd(0x06);
	send_cmd(0x80);
	send_cmd(0x0c);
	sendcmdoo(0x38);
	sendcmdoo(0x0e);
	sendcmdoo(0x01);
	sendcmdoo(0x06);
	sendcmdoo(0x80);
	sendcmdoo(0x0c);
}
void send_data(char b)
{
	lcd_data=b;
	RS=1;
	RW=0;
	E=1;
	delay02(100);
	E=0;
}
void send(char b)
{
	lcd_data1=b;
	R_S=1;
	RW1=0;
	E1=1;
	delay14(50);
	E1=0;
}
void show_data(char *s)
{
	while(*s)
	{
		send_data(*s++);
	}
}
void show(char *s)
{
	while(*s)
	{
		send(*s++);
	}
	sendcmdoo(0x0c);
}
void send_cmd(char a)
{
	lcd_data=a;
	RS=0;
	RW=0;
	E=1;
	delay02(10);
	E=0;
}
void sendcmdoo(char a)
{
	lcd_data1 =a;
	R_S=0;
	RW1=0;
	E1=1;
	delay14(10);
	E1=0;
}
void delay02(int time)
{
	int i;
	TMOD=0x01;
	TR0=1;
	for(i=0;i<time;i++)
	{
		TH0=0xF8;
		TL0=0xCD;
		while(TF0==0);
		TF0=0;
		
	}
	TR0=1;
}
void delay14(int time)
{
	int i;
	TMOD=0x10;
	TR1=1;
	for(i=0;i<time;i++)
	{
		TH1=0xEE;
		TL1=0xBF;
		while(TF1==0);
		TF1=0;
	}
	TR1=1;
}