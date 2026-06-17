#include "stm32f10x.h"
void SPI2_Init(void) {
	//禁用SPI2
	SPI2->CR1 &= ~SPI2_CR1_SPE;
	//配置CR1
	SPI2->CR1=0//先清零
	SPI2->CR1 &= ~SPI_CR1_CRCEN;//硬件CRC计时器不使能
	SPI2->CR1 &= ~SPI_CR1_DFF;//8位
	SPI2->CR1 |= SPI_CR1_MSTR;//主模式
	SPI2->CR1 |= SPI_CR1_SSM;//软件从设备使能,NSS由软件控制
	SPI2->CR1 |= SPI_CR1_BR_1;//波特率/8
	SPI2->CR1 &= ~SPI_CR1_CPOL;//极性
	SPI2->CR1 &= ~SPI_CR1_CPOH;//相位
	SPI2->CR1 |= SPI_CR1_LSBFIRST;
	//配置CR2
	SPI2->CR2 &= ~SPI_CR2_TXEIE;
	SPI2->CR2 |= SPI_CR2_RXNEIE;//接受缓冲区非空中断使能
	SPI2->CR2 &= ~SPI_CR2_ERRIE;
	SPI2->CR2 &= ~SPI_CR2_SSOE;

	//使能外设
	SPI2->CR1 |= SPI2_CR1_SPE;
}

/* SPI2引脚：PB12(CS输出)、PB13(SCK复用输出)、PB14(MISO输入)、PB15(MOSI复用输出)*/
void SPI2_MspInit(void) {
	//使能时钟
	RCC->APB1ENR |= RCC_APB1ENR_SPI2EN;
	RCC->APB2ENR |= RCC_APB2ENR_AFIOEN;
	RCC->APB2ENR |= RCC_APB2ENR_IOPBEN;

	//先清零
	GPIOB->CRH &= ~((0x0F << 4 * 4) | (0x0F << 4 * 5) | (0x0F << 4 * 6) | (0x0F << 4 * 7));
	//PB12 普通推挽输出 00 01
	GPIOB->CRH |= (0x01 << 4 * 4);
	//PB13 复用推挽输出10MHz 10 01
	GPIOB->CRH |= (0x09 << 4 * 5);
	//PB14 浮空输入 01 00
	GPIOB->CRH |= (0x04 << 4 * 6);
	//PB15 复用推挽输出 10 01
	GPIOB->CRH |= (0x09 << 4 * 7);
}

void SPI2_CS_Control(unit8_t state) {
	if (state == 0) {
		//
	}
}