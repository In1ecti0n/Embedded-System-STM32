#ifndef _DELAY_H_
#define _DELAY_H_

#include "sys.h"

void DELAY_Config(void);
void SysTick_Handler(void);
void DELAY_ms(uint32_t time);

#endif
