#include "i2c.h"


void I2C_Config(void)
{
	// cau hinh GPIO
	GPIO_InitTypeDef Gpio;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
	Gpio.GPIO_Pin = LCD_DATA | LCD_SCK;			
	Gpio.GPIO_Mode = GPIO_Mode_AF_OD;
	Gpio.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(LCD_PORT, &Gpio);
	
	// cau hinh I2C
	I2C_InitTypeDef I2C_InitStructure;
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_I2C1, ENABLE);
	I2C_InitStructure.I2C_Mode = I2C_Mode_I2C;
	I2C_InitStructure.I2C_DutyCycle = I2C_DutyCycle_2;
	I2C_InitStructure.I2C_OwnAddress1 = 0;
	I2C_InitStructure.I2C_Ack = I2C_Ack_Disable;
	I2C_InitStructure.I2C_AcknowledgedAddress = I2C_AcknowledgedAddress_7bit;
	I2C_InitStructure.I2C_ClockSpeed = 100000;
	I2C_Init(I2C1, &I2C_InitStructure);
	I2C_Cmd(I2C1, ENABLE);
}
