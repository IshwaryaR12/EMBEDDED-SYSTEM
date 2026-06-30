#include <stm32f401xe.h>
#define GPIOAEN (1<<0)
#define GPIOCEN (1<<2)

#define SW1 (1<<0)
#define SW2 (1<<1)
#define SW3 (1<<2)
#define SW4 (1<<3)

void delay();

int main()
{
	RCC ->AHB1ENR |= GPIOAEN;
	RCC ->AHB1ENR |= GPIOCEN;

	GPIOA ->MODER |= 0X00005555;

	GPIOC-> MODER &= ~ (0X1<<0);
	GPIOC-> MODER &= ~ (0X1<<1);
	GPIOC-> MODER &= ~ (0X1<<2);
	GPIOC-> MODER &= ~ (0X1<<3);
	GPIOC-> MODER &= ~ (0X1<<4);
	GPIOC-> MODER &= ~ (0X1<<5);
	GPIOC-> MODER &= ~ (0X1<<6);
	GPIOC-> MODER &= ~ (0X1<<7);

	GPIOC-> PUPDR |= (0X1<<0);
	GPIOC-> PUPDR |= (0X1<<2);
	GPIOC-> PUPDR |= (0X1<<5);
	GPIOC-> PUPDR |= (0X1<<7);

	while(1)
	{

		 if(!(GPIOC->IDR & SW1))
		        {
			 	 	 GPIOA->ODR |= 0XFFUL<<0U;
		            delay();

		            GPIOA->ODR &= ~(0XFFUL<<0U);
		            delay();
		        }



		        else if(!(GPIOC->IDR & SW2))
		        {
		            GPIOA->ODR= 0x01;
		            delay();

		            GPIOA->ODR= 0x02;
		            delay();

		            GPIOA->ODR= 0x04;
		            delay();

		            GPIOA->ODR= 0x08;
		            delay();

		            GPIOA->ODR= 0x10;
		            delay();

		            GPIOA->ODR= 0x20;
		            delay();

		            GPIOA->ODR= 0x40;
		            delay();

		            GPIOA->ODR= 0x80;
		            delay();
		        }


		        else if(GPIOC->IDR & SW3)
		        {
		            GPIOA->ODR= 0x80;
		            delay();

		            GPIOA->ODR= 0x40;
		            delay();

		            GPIOA->ODR= 0x20;
		            delay();

		            GPIOA->ODR= 0x10;
		            delay();

		            GPIOA->ODR= 0x08;
		            delay();

		            GPIOA->ODR = 0x04;
		            delay();

		            GPIOA->ODR= 0x02;
		            delay();

		            GPIOA->ODR= 0x01;
		            delay();
		        }


		        else if(GPIOC->IDR & SW4)
		        {
		            GPIOA->ODR = 0x03;
		            delay();

		            GPIOA->ODR = 0x0C;
		            delay();

		            GPIOA->ODR = 0x30;
		            delay();

		            GPIOA->ODR = 0xC0;
		            delay();
		        }

		        else
		        {
		            GPIOC->ODR = 0x00;
		        }
		    }
	}

void delay()
{
	int i,j;

    for(i=0;i<500;i++)
    {
        for(j=0;j<4000;j++);
    }
}

