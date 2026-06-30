#include <reg51.h>
#define led P2
void delay(unsigned int ms);
void main()
{
	int ca[10]={0X3F,0X06,0X5B,0X4F,0X66,0X6D,0X7D,0X07,0XFF,0X6F};
	int i;
	led=0x00;
	while(1)
	{
		for(i=0;i<10;i++)
		{
			led=ca[i];
			delay(1000);
		}
		
	}
}
void delay(unsigned int ms)
{
	int i,j;
	for(i=0;i<ms;i++)
	for(j=0;j<100;j++);
}