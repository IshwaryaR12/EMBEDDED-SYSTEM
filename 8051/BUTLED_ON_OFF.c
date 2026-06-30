#include <reg51.h>
sbit led=P2^0;
sbit s=P1^0;
void main()
{
	led=0x00;
	while(1)
	{
		if(s==0)
		{
			led=1;
		}
		else
		{
			led=0;
		}
	}
}