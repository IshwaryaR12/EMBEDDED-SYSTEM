#include <stm32f401xe.h>
#define GPIOAEN (1<<0)
#define GPIOCEN (1<<2)

#define RS (1<<0)
#define RW (1<<1)
#define EN (1<<2)

void lcd_init ();
void send_cmd(char a);
void send_data(char b);
void show_data (char *s);
void delay (unsigned int t);

int main()
{
	RCC ->AHB1ENR |= GPIOAEN;
	RCC ->AHB1ENR |= GPIOCEN;

	GPIOA ->MODER |= 0X00005555;
	GPIOC ->MODER |= 0X00005555;

	delay(50);

	lcd_init ();

	while(1)
	{
		send_cmd(0x80);
		show_data ("Embedded");
		send_cmd(0xc0);
		show_data ("System");
		delay(1000);
	}

}

void send_cmd (char a)
	{
		GPIOA -> ODR = a;
		GPIOC -> ODR &= ~RS;
		GPIOC -> ODR &= ~RW;
		GPIOC -> ODR |= EN;
		delay(5);
		GPIOC -> ODR &= ~EN;

	}
void send_data (char b)
{
		GPIOA -> ODR = b;
		GPIOC -> ODR |= RS;
		GPIOC -> ODR &= ~RW;
		GPIOC -> ODR |= EN;
		delay(5);
		GPIOC -> ODR &= ~EN;


}

void show_data(char *s)
{
	while(*s)
			{
				send_data(*s++);
			}
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

void delay(unsigned int t)
{
	int i,j;

    for(i=0;i<t;i++)
    {
        for(j=0;j<4000;j++);
    }
}


