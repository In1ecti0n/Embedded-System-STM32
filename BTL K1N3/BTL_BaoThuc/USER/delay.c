#include "delay.h"


static uint32_t i = 0;

void DELAY_Config(void)
{
	SystemCoreClockUpdate();
	SysTick_Config(SystemCoreClock/1000);
}

void SysTick_Handler(void)
{
	i--;
}

void DELAY_ms(uint32_t time)
{
	i = time;
	while(i != 0){}
}
