#include "stm32f401xe.h"


void GPIO_Init(void);

int main() {
    GPIO_Init();
    while (1) {

    }
}

void EXTI1_IRQHandler() {
	// Check if interrupt is from pin PB1
    if (EXTI->PR & EXTI_PR_PR1) {
        GPIOB->ODR ^=(0X1<<0);
    }
}


void GPIO_Init() {

    RCC->AHB1ENR |= RCC_AHB1ENR_GPIOBEN;

    //  PB0 = output (LED)
    GPIOB->MODER  |= (0x1<<0);


    GPIOB -> MODER &= ~(0X3<<2); // GPIOB->MODER &= ~(0X1<<2) , GPIOB->MODER &= ~(0X1<<3)
    GPIOB->PUPDR |= (0x1<<2);

    // Configure EXTI line for PB1
    RCC->APB2ENR |= RCC_APB2ENR_SYSCFGEN;
    SYSCFG->EXTICR[0] |= (0x1<<4);

    EXTI->IMR |= EXTI_IMR_IM1;  // Unmask EXTI1 (0X1<<1)

    EXTI->FTSR |= EXTI_FTSR_TR1; // Falling edge trigger

    NVIC_EnableIRQ(EXTI1_IRQn );
    // NVIC_EnableIRQ(7);  //Another Method.
}
