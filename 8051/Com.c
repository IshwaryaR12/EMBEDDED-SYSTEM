#include <reg51.h>
void show_data(char *s);
void send_data(char b);
void main()
{
	SCON=0x50;
	TMOD=0x20;
	TH1=0xFD;
	TR1=1;
	show_data("ISHWARYA");
  while(TI==0);
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
	SBUF=a;
	while(TI==0);
	TI=0;
}