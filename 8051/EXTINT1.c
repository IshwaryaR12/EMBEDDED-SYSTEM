#include <reg51.h>
sbit led1=P2^0;
sbit led2=P2^1;
void delay();
void ISR_ex0();

// INT0 = 0
// INT1 = 2

void ISR_ex0() interrupt 2    //Take External interrupt 0.
	{
		led1 = ~led1;
		delay(); 
		led1 = ~led1;
		delay();

		led1 = ~led1;
		delay();
		led1 = ~led1;
		delay();
	}

int main ()
	{ 
		P2=0X00;
		// INT0 IE = 0X81;
		// INT1 IE = 0X84;
		IE=0x84;// 1000 0001 
		// level trigger IT0 = 0;
		// edge  trigger IT0 = 1;
	  IT1=1;

		while(1)
			{
				led2 = ~led2;
				delay();
			}
	}

void delay()
{
	unsigned int i,j;
	for (i=0; i<1000; i++)
	for (j=0; j<100; j++);	
}