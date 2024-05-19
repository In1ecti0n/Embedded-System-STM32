#include "device.h"

void Device_Config(void)
{
	GPIO_InitTypeDef Gpio;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
	
	Gpio.GPIO_Mode = GPIO_Mode_Out_PP;
	Gpio.GPIO_Pin = GPIO_SIRENS;
	Gpio.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(PORT_SIRENS, &Gpio);
}

void Device_SirensOn(void)
{
	GPIO_SetBits(PORT_SIRENS, GPIO_SIRENS);
}

void Device_SirensOff(void)
{
	GPIO_ResetBits(PORT_SIRENS, GPIO_SIRENS);
}
