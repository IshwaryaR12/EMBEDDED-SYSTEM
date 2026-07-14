#include "stm32f401xe.h"
#include "stdint.h"

#define GPIOAEN    (1U << 0)
#define GPIOBEN    (1U << 1)
#define SPI1EN     (1U << 12)

#define CR1_MSTR   (1U << 2)
#define CR1_SPE    (1U << 6)
#define CR1_BR     (5U << 3)
#define CR2_TXEIE  (1U << 7)
#define SR_TXE     (1U << 1)

volatile char tx_data = 0x41;

void delay(volatile uint32_t count)
{
    while(count--);
}

void interrupt(void)
{
    RCC->APB2ENR |= SPI1EN;
    RCC->AHB1ENR |= GPIOAEN;
    RCC->AHB1ENR |= GPIOBEN;

    GPIOA->MODER &= ~(3U << 10);
    GPIOA->MODER |= (1U << 10);

    GPIOB->MODER &= ~((3U << 6) | (3U << 8) | (3U << 10));
    GPIOB->MODER |= ((2U << 6) | (2U << 8) | (2U << 10));

    GPIOB->AFR[0] &= ~((0xFU << 12) | (0xFU << 16) | (0xFU << 20));
    GPIOB->AFR[0] |= ((5U << 12) | (5U << 16) | (5U << 20));

    GPIOB->MODER &= ~(3U << 0);
    GPIOB->MODER |= (1U << 0);
    GPIOB->ODR |= (1U << 0);

    SPI1->CR1 = CR1_MSTR | CR1_BR | CR1_SPE;
    SPI1->CR2 = CR2_TXEIE;

    NVIC_EnableIRQ(SPI1_IRQn);
}

void SPI1_IRQHandler(void)
{
    if (SPI1->SR & SR_TXE)
    {
        SPI1->DR = tx_data;
        GPIOA->ODR ^= (1U << 5);
        SPI1->CR2 &= ~CR2_TXEIE;
    }
}

int main(void)
{
    interrupt();

    while (1)
    {
        delay(400000);

        GPIOB->ODR &= ~(1U << 0);
        SPI1->CR2 |= CR2_TXEIE;
        delay(100);
        GPIOB->ODR |= (1U << 0);
    }
}
