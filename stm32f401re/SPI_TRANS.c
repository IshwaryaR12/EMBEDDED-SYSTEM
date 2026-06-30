
//spi_tx
//#include"stm32f401xe.h"
//void GPIO_init()
//{
//	// Enable Clock Access for GPIOA
//	RCC->AHB1ENR |= (1<<0);
//
//	// Set P7 as alternate function mode
//	GPIOA->MODER |= (1U<<15);
//	GPIOA->MODER &= ~(1U<<14);
//
//	// Set P6 as alternate function mode
//	GPIOA->MODER |= (1U<<13);
//	GPIOA->MODER &= ~(1U<<12);
//
//	// Set P5 as alternate function mode
//	GPIOA->MODER |= (1U<<11);
//	GPIOA->MODER &= ~(1U<<10);
//
//	// Set P4 as OUTPUT mode
//	GPIOA->MODER &= ~(1U<<9);
//	GPIOA->MODER |= (1U<<8);
//
//	//Set Alternate Function AF5	in PA7
//	GPIOA->AFR[0] |= 0x5UL<<28U; // 0 IS LOW REGISTER. 1 IS HIGH REGISTER.
//
//	//Set Alternate Function AF5	in PA6
//	GPIOA->AFR[0] |= 0x5UL<<24;
//
//	//Set Alternate Function AF5	in PA5
//	GPIOA->AFR[0] |= 0x5UL<<20;
//}
//void SPI1_init()
//{
//	GPIO_init();
//	// Enable Clock access for SPI1
//	RCC->APB2ENR |= (1<<12);
//
//	// 4 MHz is fast enough for good balance between speed and reliability.
//	SPI1->CR1 |= 0X08UL; // 0000 1000 (001) whatever select (But varry  the data speed)
//
//
//	// The MSTR and SPE bits must be set (they remain set only if the NSS pin is connected to a high-level signal).
//	SPI1->CR1 |= (1<<2); // Master configuration
//	SPI1->CR1 |= (1<<6); //SPI-Peripheral enabled
//}
//
//int main()
//{
//	uint32_t i;
//	SPI1_init();
//	GPIOA->ODR |= (1<<4);
//	for(i=0;i<100000;i++);
//	GPIOA->ODR &= ~(1<<4);
//	while(!(SPI1->SR & SPI_SR_TXE));//TXE this bit ensures that the buffer is ready to accept new data before writing (buffer is empty=1)
//	SPI1->DR='Z';
//	while((SPI1->SR & SPI_SR_BSY));//wait for completing transmission and overwriting and avoid corruption
//	GPIOA->ODR |= (1<<4);
//    while(1);
//}


//spi_eeprom
//#include "stm32f401xe.h"
//
//#define EEPROM_WREN  0x06
//#define EEPROM_WRDI  0x04
//#define EEPROM_WRITE 0x02
//#define EEPROM_READ  0x03
//#define EEPROM_RDSR  0x05
//
//void GPIO_init(void)
//{
//    RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN;
//
//    GPIOA->MODER &= ~((3U << 8) | (3U << 10) | (3U << 12) | (3U << 14));
//
//    GPIOA->MODER |= (1U << 8);
//    GPIOA->MODER |= (2U << 10);
//    GPIOA->MODER |= (2U << 12);
//    GPIOA->MODER |= (2U << 14);
//
//    GPIOA->OSPEEDR &= ~((3U << 8) | (3U << 10) | (3U << 12) | (3U << 14));
//    GPIOA->OSPEEDR |= (3U << 8)  | (3U << 10) | (3U << 12) | (3U << 14);
//
//    GPIOA->AFR[0] &= ~((0xFUL << 20) | (0xFUL << 24) | (0xFUL << 28));
//    GPIOA->AFR[0] |= (5UL << 20);
//    GPIOA->AFR[0] |= (5UL << 24);
//    GPIOA->AFR[0] |= (5UL << 28);
//
//    GPIOA->ODR |= (1U << 4);
//}
//
//void SPI1_init(void)
//{
//    GPIO_init();
//
//    RCC->APB2ENR |= RCC_APB2ENR_SPI1EN;
//
//    SPI1->CR1 = 0;
//
//    SPI1->CR1 |= (3U << 3);
//    SPI1->CR1 |= SPI_CR1_CPOL;
//    SPI1->CR1 |= SPI_CR1_CPHA;
//    SPI1->CR1 |= SPI_CR1_MSTR;
//    SPI1->CR1 |= SPI_CR1_SSM;
//    SPI1->CR1 |= SPI_CR1_SSI;
//
//    SPI1->CR1 |= SPI_CR1_SPE;
//}
//
//int SPI1_Transfer(int data)
//{
//    while (!(SPI1->SR & SPI_SR_TXE));
//    SPI1->DR = data;
//    while (!(SPI1->SR & SPI_SR_RXNE));
//    return (int)(SPI1->DR);
//}
//
//void EEPROM_CS_Low(void)
//{
//	GPIOA->ODR &= ~(1U << 4);
//}
//void EEPROM_CS_High(void) {
//	GPIOA->ODR |=  (1U << 4);
//}
//
//void EEPROM_WaitReady(void)
//{
//    int status = 0;
//    do {
//        EEPROM_CS_Low();
//        SPI1_Transfer(EEPROM_RDSR);
//        status = SPI1_Transfer(0xFF);
//        EEPROM_CS_High();
//    } while (status & 0x01);
//}
//
//void EEPROM_WriteByte(int address, int data)
//{
//    EEPROM_CS_Low();
//    SPI1_Transfer(EEPROM_WREN);
//    EEPROM_CS_High();
//
//    EEPROM_CS_Low();
//    SPI1_Transfer(EEPROM_WRITE);
//    SPI1_Transfer((address >> 8) & 0xFF);
//    SPI1_Transfer(address & 0xFF);
//    SPI1_Transfer(data);
//    EEPROM_CS_High();
//
//    EEPROM_WaitReady();
//}
//
//int EEPROM_ReadByte(int address)
//{
//    int data = 0;
//
//    EEPROM_CS_Low();
//    SPI1_Transfer(EEPROM_READ);
//    SPI1_Transfer((address >> 8) & 0xFF);
//    SPI1_Transfer(address & 0xFF);
//    data = SPI1_Transfer(0xFF);
//    EEPROM_CS_High();
//
//    return data;
//}
//
//int main(void)
//{
//    SPI1_init();
//    EEPROM_WriteByte(0x0010, 'Z');
//    EEPROM_ReadByte(0x0010);
//    while(1)
//    {
//       SPI1->DR='Z';
//    }
//}

#define STM32F401xE
#include "stm32f4xx.h"

void sys_delay_ms(int ms);
void SPI1_Master_init(void);
void SPI_Master_data(int data);
void SPI_write_byte(int msb, int lsb, int data);
void SPI_write_page(int msb, int lsb);

void sys_delay_ms(int ms)
{
    for(volatile int i = 0; i < ms; i++)
    {
        for(volatile int j = 0; j < 3180; j++);
    }
}

void GPIO_init(void)
{
    RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN;

    GPIOA->MODER &= ~((3U << 8) | (3U << 10) | (3U << 12) | (3U << 14));

    GPIOA->MODER |= (1U << 8);
    GPIOA->MODER |= (2U << 10);
    GPIOA->MODER |= (2U << 12);
    GPIOA->MODER |= (2U << 14);

    GPIOA->OSPEEDR &= ~((3U << 8) | (3U << 10) | (3U << 12) | (3U << 14));
    GPIOA->OSPEEDR |= (3U << 8)  | (3U << 10) | (3U << 12) | (3U << 14);

    GPIOA->AFR[0] &= ~((0xFUL << 20) | (0xFUL << 24) | (0xFUL << 28));
    GPIOA->AFR[0] |= (5UL << 20);
    GPIOA->AFR[0] |= (5UL << 24);
    GPIOA->AFR[0] |= (5UL << 28);

    GPIOA->ODR |= (1U << 4);
}

void SPI1_Master_init(void)
{
    GPIO_init();

    RCC->APB2ENR |= RCC_APB2ENR_SPI1EN;

    SPI1->CR1 = 0;

    SPI1->CR1 |= (3U << 3);
    SPI1->CR1 |= SPI_CR1_MSTR;
    SPI1->CR1 |= SPI_CR1_SSM;
    SPI1->CR1 |= SPI_CR1_SSI;
    SPI1->CR1 |= SPI_CR1_SPE;
}

void SPI_Master_data(int data)
{
    while (!(SPI1->SR & SPI_SR_TXE));
    SPI1->DR = data;

    while (SPI1->SR & SPI_SR_BSY);

    int temp = SPI1->DR;
    (void)temp;
}

void SPI_write_byte(int msb, int lsb, int data)
{
    GPIOA->ODR |= (1U << 4);
    sys_delay_ms(1);
    GPIOA->ODR &= ~(1U << 4);

    SPI_Master_data(0x06);

    GPIOA->ODR |= (1U << 4);
    sys_delay_ms(1);
    GPIOA->ODR &= ~(1U << 4);

    SPI_Master_data(0x02);
    SPI_Master_data(msb);
    SPI_Master_data(lsb);
    SPI_Master_data(data);

    GPIOA->ODR |= (1U << 4);
    sys_delay_ms(1);
    GPIOA->ODR &= ~(1U << 4);

    SPI_Master_data(0x04);
    GPIOA->ODR |= (1U << 4);
}

void SPI_write_page(int msb, int lsb)
{
    int i;

    GPIOA->ODR |= (1U << 4);
    sys_delay_ms(10);
    GPIOA->ODR &= ~(1U << 4);

    SPI_Master_data(0x06);

    GPIOA->ODR |= (1U << 4);
    sys_delay_ms(10);
    GPIOA->ODR &= ~(1U << 4);

    SPI_Master_data(0x02);
    SPI_Master_data(msb);
    SPI_Master_data(lsb);

    for(i = 'A'; i <= 'Z'; i++)
    {
        SPI_Master_data(i);
    }

    GPIOA->ODR |= (1U << 4);
    sys_delay_ms(10);
    GPIOA->ODR &= ~(1U << 4);

    SPI_Master_data(0x04);
    GPIOA->ODR |= (1U << 4);
}

int main(void)
{
    SPI1_Master_init();

    SPI_write_byte(0x00, 0xFF, 'Z');
    sys_delay_ms(1000);

    SPI_write_page(0x00, 0x00);
    sys_delay_ms(1000);

    while(1)
    {
    }
}
