#include<reg51.h>

void Counter2(unsigned int ms);
void main()
{
	while(1)
	{
		P0=0xFF;
		counter2(200);
		P0=0x00;
		counter2(200);
	}
}
void Counter2(unsigned int ms)
{
	unsigned int i;
	TMOD=0x05;
	TR0=1;
	for(i=0;i<ms;i++)
	{
		TH1=0xF;
		TL1=0xFE;
		while(TF0==0);
		TF0=0;
	}
	TR0=0;
}