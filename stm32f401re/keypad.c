#include <stm32f401xe.h>
#define GPIOAEN (1<<0)
#define GPIOBEN (1<<1)
#define GPIOCEN (1<<2)

#define R1 (1<<0)
#define R2 (1<<1)
#define R3 (1<<2)
#define R4 (1<<3)

#define C1 (1<<4)
#define C2 (1<<5)
#define C3 (1<<6)
#define C4 (1<<7)

#define RS (1<<0)
#define RW (1<<1)
#define EN (1<<2)

void lcd_init ();
void send_cmd(char a);
void send_data(char b);
void show_data (char *s);
void delay (unsigned int t);

char keypad (void);

int main()
{
	RCC ->AHB1ENR |= GPIOAEN;
	RCC ->AHB1ENR |= GPIOBEN;
	RCC ->AHB1ENR |= GPIOCEN;

	GPIOA ->MODER |= 0X00005555;
	GPIOB ->MODER |= 0X00005555;

	GPIOC-> MODER |= (0X1<<0);
	GPIOC-> MODER |= (0X1<<2);
	GPIOC-> MODER |= (0X1<<4);
	GPIOC-> MODER |= (0X1<<6);

	GPIOC-> MODER &= ~ (0X1<<8);
	GPIOC-> MODER &= ~ (0X1<<9);
	GPIOC-> MODER &= ~ (0X1<<10);
	GPIOC-> MODER &= ~ (0X1<<11);
	GPIOC-> MODER &= ~ (0X1<<12);
	GPIOC-> MODER &= ~ (0X1<<13);
	GPIOC-> MODER &= ~ (0X1<<14);
	GPIOC-> MODER &= ~ (0X1<<15);

	GPIOC->PUPDR |= (0X1<<8);
	GPIOC->PUPDR |= (0X1<<10);
	GPIOC->PUPDR |= (0X1<<12);
	GPIOC->PUPDR |= (0X1<<14);



	delay(50);

	lcd_init ();

	while(1)
	{
		send_cmd(0x80);
		show_data ("Enter:");
		send_cmd(0xc0);

		char key = keypad ();

		 if(key != 0)
		        {
		            send_data(key);
		            delay(200);
		        }
		delay(10);
	}

}

char keypad (void)
{

    GPIOC->ODR = (GPIOC->ODR & ~0x0F) | 0x0E;

    if(!(GPIOC->IDR & C1))
    {
        while(!(GPIOC->IDR & C1));
        return '7';
    }

    if(!(GPIOC->IDR & C2))
    {
        while(!(GPIOC->IDR & C2));
        return '8';
    }

    if(!(GPIOC->IDR & C3))
    {
        while(!(GPIOC->IDR & C3));
        return '9';
    }

    if(!(GPIOC->IDR & C4))
    {
        while(!(GPIOC->IDR & C4));
        return '/';
    }

    GPIOC->ODR = (GPIOC->ODR & ~0x0F) | 0x0D;

    if(!(GPIOC->IDR & C1))
    {
        while(!(GPIOC->IDR & C1));
        return '4';
    }

    if(!(GPIOC->IDR & C2))
    {
        while(!(GPIOC->IDR & C2));
        return '5';
    }

    if(!(GPIOC->IDR & C3))
    {
        while(!(GPIOC->IDR & C3));
        return '6';
    }

    if(!(GPIOC->IDR & C4))
    {
        while(!(GPIOC->IDR & C4));
        return '*';
    }



    GPIOC->ODR = (GPIOC->ODR & ~0x0F) | 0x0B;

    if(!(GPIOC->IDR & C1))
    {
        while(!(GPIOC->IDR & C1));
        return '1';
    }

    if(!(GPIOC->IDR & C2))
    {
        while(!(GPIOC->IDR & C2));
        return '2';
    }

    if(!(GPIOC->IDR & C3))
    {
        while(!(GPIOC->IDR & C3));
        return '3';
    }

    if(!(GPIOC->IDR & C4))
    {
        while(!(GPIOC->IDR & C4));
        return '-';
    }


    GPIOC->ODR = (GPIOC->ODR & ~0x0F) | 0x07;

    if(!(GPIOC->IDR & C1))
    {
        while(!(GPIOC->IDR & C1));
        return 'C';
    }

    if(!(GPIOC->IDR & C2))
    {
        while(!(GPIOC->IDR & C2));
        return '0';
    }

    if(!(GPIOC->IDR & C3))
    {
        while(!(GPIOC->IDR & C3));
        return '=';
    }

    if(!(GPIOC->IDR & C4))
    {
        while(!(GPIOC->IDR & C4));
        return '+';
    }

    return 0;
}

void send_cmd (char a)
	{
		GPIOA -> ODR = a;
		GPIOB -> ODR &= ~RS;
		GPIOB -> ODR &= ~RW;
		GPIOB -> ODR |= EN;
		delay(5);
		GPIOB -> ODR &= ~EN;

	}
void send_data (char b)
{
		GPIOA -> ODR = b;
		GPIOB -> ODR |= RS;
		GPIOB -> ODR &= ~RW;
		GPIOB -> ODR |= EN;
		delay(5);
		GPIOB -> ODR &= ~EN;


}

void show_data(char*s)
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


