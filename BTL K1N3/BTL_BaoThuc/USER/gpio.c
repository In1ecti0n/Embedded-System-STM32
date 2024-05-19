#include "gpio.h"


void GPIO_INIT(void)
{
	GPIO_InitTypeDef Button;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);
	Button.GPIO_Mode = GPIO_Mode_Out_PP;
	Button.GPIO_Pin = PIN_BUTTON_1;
	Button.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(PORT_BUTTON_1, &Button);
	
	GPIO_SetBits(PORT_BUTTON_1, PIN_BUTTON_1);
}
