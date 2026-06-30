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
	RCC->APB1ENR |= (1<<0);
	TIM2->PSC = 16000-1;
	TIM2->ARR = 1000;
    TIM2->CNT = 0;
    TIM2->CR1 |= CEN;
	while(!(TIM2->SR & UIF));
	TIM2->SR &= ~UIF;
}
