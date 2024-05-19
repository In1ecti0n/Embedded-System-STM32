#ifndef _DEVICE_H_
#define _DEVICE_H_

#include "sys.h"

#define GPIO_SIRENS GPIO_Pin_0
#define PORT_SIRENS GPIOB

void Device_Config(void);
void Device_SirensOn(void);
void Device_SirensOff(void);

#endif
