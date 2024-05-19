#include "uart.h"


uint8_t flag_uart_get_end = 0;
char RRX[string_size];
uint8_t RXI = 0;
char temp_char;
char a[10];

struct __FILE{
	int dummy;
};
FILE __stdout;

int fputc(int ch, FILE *f)
{
	UART_SendChar(ch);
	return ch;
}

void UART_Config(void)
{
	USART_InitTypeDef Usart;
	GPIO_InitTypeDef Gpio;
	
	// enable clock
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);
	
	// config Tx-A9
	Gpio.GPIO_Mode = GPIO_Mode_AF_PP;
	Gpio.GPIO_Pin = GPIO_Pin_9;
	Gpio.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &Gpio);
	
	// config Rx-A10
	Gpio.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	Gpio.GPIO_Pin = GPIO_Pin_10;
	Gpio.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &Gpio);
	
	// config Usart
	Usart.USART_BaudRate = 9600;
	Usart.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	Usart.USART_Mode = USART_Mode_Tx | USART_Mode_Rx;
	Usart.USART_Parity = USART_Parity_No;
	Usart.USART_StopBits = USART_StopBits_1;
	Usart.USART_WordLength = USART_WordLength_8b;
	USART_Init(USART1, &Usart);
	
	// enable usart1 global interrupt
	USART_ITConfig(USART1, USART_IT_RXNE, ENABLE); // ham cho phep ngat USART hoac khong
	USART_Cmd(USART1, ENABLE);
	USART_ClearFlag(USART1, ENABLE);
	NVIC_EnableIRQ(USART1_IRQn);
}

void USART1_IRQHandler()
{
	if(USART_GetITStatus(USART1,USART_IT_RXNE) != RESET)
	{
		temp_char = USART_ReceiveData(USART1);
		
		if(temp_char != '\n')
		{	
			RRX[RXI] = temp_char;
			RXI++;
			//sprintf(a,"%d",RXI);
		}
		else
		{
			RRX[RXI] = 0x00;
			flag_uart_get_end = 1;
			RXI = 0;
		}
	}
	USART_ClearITPendingBit(USART1, USART_IT_RXNE);
}

/*ham gui du lieu*/
void UART_SendChar(char _ch){
	USART_SendData(USART1, _ch);
	while(USART_GetFlagStatus(USART1, USART_FLAG_TXE) == RESET);
}

/* ham nhan du lieu */
void UART_Putchar(char *String)
{
	while(*String)
	{
		UART_SendChar(*String);
		String++;
	}
}
