#include <reg51.h>
sbit s1=P1^0;
sbit s2=P1^1;
sbit s3=P1^2;
sbit s4=P1^3;
sbit s5=P1^4;
void delay(unsigned int ms);
void main()
{
	P0=0x00;
	while(1)
	{
		if(s1==0)
		{
		P0=0x18;
		delay(1000);
		P0=0x24;
		delay(1000);
		P0=0x42;
		delay(1000);
		P0=0x81;
		delay(1000);
		}
		else if(s2==0)
		{
		P0=0x0F;
		delay(1000);
		P0=0xF0;
		delay(1000);
		}
		else if(s3==0)
		{
			P0=0x80;
		delay(1000);
		P0=0x40;
		delay(1000);
		P0=0x20;
		delay(1000);
		P0=0x10;
		delay(1000);
		P0=0x08;
		delay(1000);
		P0=0x04;
		delay(1000);
		P0=0x02;
		delay(1000);
		P0=0x01;
		delay(1000);
		}
		else if(s4==0)
		{
		P0=0x10;
		delay(1000);
		P0=0x08;
		delay(1000);
		P0=0x20;
		delay(1000);
		P0=0x04;
		delay(1000);
		P0=0x40;
		delay(1000);
		P0=0x02;
		delay(1000);
		P0=0x80;
		delay(1000);
		P0=0x01;
		delay(1000);
		}
		else if(s5==0)
		{
		P0=0x81;
		delay(1000);
		P0=0x42;
		delay(1000);
		P0=0x24;
		delay(1000);
		P0=0x18;
		delay(1000);
		}
		else
		{
			P0=0x00;
		}
	}
}
void delay(unsigned int ms)
{
	int i,j;
	for(i=0;i<ms;i++)
	for(j=0;j<100;j++);
}