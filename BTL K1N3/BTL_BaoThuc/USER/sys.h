#ifndef _SYS_H_
#define _SYS_H_

#include <stdio.h>
#include <stdlib.h>
#include "stdint.h"
#include "string.h"
#include "stm32f10x.h"
#include "stm32f10x_i2c.h"
#include "stm32f10x_rcc.h"
#include "stm32f10x_gpio.h"
#include "stm32f10x_usart.h"

#include "i2c.h"
#include "lcd.h"
#include "uart.h"
#include "delay.h"
#include "device.h"

void SYS_Config(void);
void SYS_Run(void);

#endif
