#include <reg51.h>

void delay(unsigned int ms);
void main()
{
    while(1)
    {
       P2=0x11;
			 P3=0x04;
			delay(1000);
			P2=0C;
			P3=0x02;
			delay(1000);
			P2=0x22;
			P3=0x01;
			delay(1000);
    }
}
void delay(unsigned int ms)
{
    unsigned int i,j;
    for(i=0;i<ms;i++)
        for(j=0;j<100;j++);
}

