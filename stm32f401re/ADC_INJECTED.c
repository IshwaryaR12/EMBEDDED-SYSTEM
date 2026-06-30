#include "stm32f401xe.h"

#include <stdint.h>
#include <stdio.h>

void ADC_INIT(void);
void START_CONVERSION(void);
uint32_t ADC_READ(void);

#define GPIOAEN (1U << 0)
#define GPIOBEN (1U << 1)
#define ADC1EN (1U << 8)

#define ADON (1U << 0)
#define SWSTART (1U << 30)
#define SR_EOC (1U << 1)

void LED_GPIO();

void DELAY(uint32_t ms);

unsigned int sensor;

int main()
{
    LED_GPIO();
    ADC_INIT();
    START_CONVERSION();
    while (1)
    {
        sensor = ADC_READ();
        if (sensor>2000)
        	{
        	  GPIOA->ODR |= 0X1<<5;
        	}
        else
        	{
        	GPIOA->ODR &= ~(0X1<<5);
        	}
    }
}

void ADC_INIT()
{
    RCC->AHB1ENR |= GPIOAEN;

    // PA1 => Analog mode
    GPIOA->MODER &= ~(3U << 2);
    GPIOA->MODER |= (3U << 2);

    RCC->APB2ENR |= ADC1EN;

    // Enable ADC
    ADC1->CR2 |= ADON;
    ADC1->JSQR=(0X3<<20);

}

void START_CONVERSION(void)
{
	ADC1->CR2 |= (0X1<<1);

    ADC1->CR2 |= SWSTART;
}

uint32_t ADC_READ(void)
{
    while (!(ADC1->SR & SR_EOC));

    uint32_t value = ADC1->JDR1;

    ADC1->SR &= ~SR_EOC;

    return value;
}

void LED_GPIO()
{

	RCC->AHB1ENR |= GPIOAEN;

	GPIOA->MODER |= 0X1<<10;
}

void LCD_PRINT(char *print)
{
	while(*print)
	{
		LCD_DATA(*print);
	}
}

void DELAY(uint32_t ms)
{
	uint32_t i,j;
	for(i=0; i<ms; i++)
		for(j=0; j<16000; j++);
}
