#include<stm32f401xe.h>
#include<stdint.h>
#define CEN (1<<0)
#define UIF (1U<<0)

void delay();

int main()
{
	RCC->AHB1ENR |= (1<<0);
	GPIOA->MODER |= 0x00005555;
	while(1)
	{
		GPIOA->ODR |= (0XFF<<0);
		delay();
		GPIOA->ODR &= ~(0XFF<<0);
		delay();
	}
}

void delay()
{
	RCC->APB2ENR |= (1<<17);
	TIM10->PSC = 32000-1;
	TIM10->ARR = 1;
    TIM10->CNT = 0;
    TIM10->CR1 |= CEN;
	while(!(TIM10->SR & UIF));
	TIM10->SR &= ~UIF;
}
