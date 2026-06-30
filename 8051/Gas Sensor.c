#include<reg51.h>
#define lcd P1
sbit RS=P2^0;
sbit RW=P2^1;
sbit E=P2^2;
sbit led = P2^3;
sbit GAS=P2^6;
void lcd_ini();
void delay(int time);
void send_cmd(char a);
void send_data(char b);
void show_data(char *s);
void main()
{
	lcd_ini();
	lcd=0x00;
	led=0;
	if(GAS==1)
	{
		send_cmd(0x80);
		show_data("GAS LEAKAGE");
		send_cmd(0xC0);
		show_data("DETECTED");
		led=1;
    delay(1000);
	else
	{
		send_cmd(0x80);
		show_data("GAS LEAKAGE");
		send_cmd(0xC0);
		show_data("NOT DETECTED");
		led=0;
		delay(1000);
	}
}
void lcd_ini()
{
	send_cmd(0x38);
	send_cmd(0x0e);
	send_cmd(0x01);
	send_cmd(0x06);
	send_cmd(0x80);
	send_cmd(0x0c);	
}
void delay(int time)
{
	int i,j;
	for(i=0;i<time;i++)
	for(j=0;j<100;j++);
}
void send_cmd(char a)
{
	lcd=a;
	RS=0;
	RW=0;
	E=1;
	delay(1);
  E=0;
}
void send_data(char b)
{
	lcd=b;
	RS=1;
	RW=0;
	E=1;
	delay(1);
	E=0;
}
void show_data(char *s)
{
	while(*s)
	{
		send_data(*s++);
	}
}
