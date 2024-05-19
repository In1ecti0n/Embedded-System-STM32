#ifndef _UART_H_
#define _UART_H_

#include "sys.h"


#define TX GPIO_Pin_9
#define RX GPIO_Pin_10

#define string_size 80

extern uint8_t flag_uart_get_end;
extern char RRX[string_size];

void UART_Config(void);
void UART_SendChar(char _ch);
void UART_SendString(char *_str);
void UART_SendNumber(int _number);
void UART_Putchar(char *String);

#endif
