
//channel 2 timer 2
///#include "stm32f401xe.h"
//#include "stdint.h"
//
//void TIM2_COUNTER();
//void TIM2_COUNT_INIT();
//
//int main()
//{
//	RCC->AHB1ENR |= 0X1UL<<0U ;
//
//	GPIOA->MODER |= 0X1UL<<10U;
//
//	GPIOA->MODER |= 0X1UL<<12U;
//
//	TIM2_COUNT_INIT();
//	while(1)
//	{
//		GPIOA->ODR = 0X3UL<<5U;
//		TIM2_COUNTER();
//
//		GPIOA->ODR = 0X0UL<<5U;
//		TIM2_COUNTER();
//	}
//}
//
//void TIM2_COUNT_INIT()
//{
//	RCC->APB1ENR |= RCC_APB1ENR_TIM2EN;
//
//	GPIOA->MODER |= 0X1UL<<3U;
//
//	GPIOA->AFR[0] |= 0X1UL<<4U;
//
//	TIM2->ARR = 5;
//
//	TIM2->CNT = 1;
//
//	TIM2->CCMR1 |= 0X1<<8;
//
//	TIM2->CCER |= (0X1<<5);
//
//	TIM2->SMCR |= 0X3<<5;
//
//	TIM2->SMCR |= 0X7<<0;
//
//	TIM2->CR1 |=  TIM_CR1_CEN;
//}
//
//void TIM2_COUNTER()
//{
//	while(!(TIM2->SR & TIM_SR_UIF));
//	TIM2->SR &= ~TIM_SR_UIF;
//}



//channel 2 timer 4
#include "stm32f401xe.h"
#include "stdint.h"

void TIM2_COUNTER();
void TIM2_COUNT_INIT();

int main()
{
	RCC->AHB1ENR |= 0X1UL<<0U ;
	RCC->AHB1ENR |= 0X1UL<<1U ;
	GPIOA->MODER |= 0X1UL<<10U;

	GPIOA->MODER |= 0X1UL<<12U;

	TIM2_COUNT_INIT();
	while(1)
	{
		GPIOA->ODR = 0X3UL<<5U;
		TIM2_COUNTER();

		GPIOA->ODR = 0X0UL<<5U;
		TIM2_COUNTER();
	}
}

void TIM2_COUNT_INIT()
{
	RCC->APB1ENR |= RCC_APB1ENR_TIM4EN;

	GPIOB->MODER |= 0X2UL<<14U;

	GPIOB->AFR[0] |= 0X2UL<<28;

	TIM4->ARR = 5;

	TIM4->CNT = 1;

	TIM4->CCMR1 |= 0X1<<8;

	TIM4->CCER |= (0X1<<5);

	TIM4->SMCR |= 0X3<<5;

	TIM4->SMCR |= 0X7<<0;

	TIM4->CR1 |=  TIM_CR1_CEN;
}

void TIM2_COUNTER()
{
	while(!(TIM4->SR & TIM_SR_UIF));
	TIM4->SR &= ~TIM_SR_UIF;
}
