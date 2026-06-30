#include "stm32f401xe.h"
#define GPIOAEN  (1<<0)
#define BUTTON   (1<<9)

int main()
{
	RCC->AHB1ENR |= GPIOAEN;

	GPIOA->MODER |= 0X5555;// OUTPUT

	GPIOA->MODER &=~(0X1<<18);// INPUT
	GPIOA->MODER &=~(0X1<<19);

	GPIOA->PUPDR |= (0X1<<18);//PULL UP

	while(1)
	{
		if(!(GPIOA->IDR & BUTTON))//if((GPIOA->IDR & BUTTON)== 0)
		{
			GPIOA->ODR |= 0XFFUL<<0U;
		}
		else
		{
			GPIOA->ODR &= ~(0XFFUL<<0U);
		}
	}
}
