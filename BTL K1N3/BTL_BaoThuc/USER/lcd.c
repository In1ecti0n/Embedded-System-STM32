#include "lcd.h"


void LCD_Write_Byte(char data)
{
    /* Send START condition */
    I2C_GenerateSTART(I2C_Chanel, ENABLE);
    /* Test on EV5 and clear it */
    while (!I2C_CheckEvent(I2C_Chanel, I2C_EVENT_MASTER_MODE_SELECT));
    /* Send PCF8574A address for write */
    I2C_Send7bitAddress(I2C_Chanel, PCF8574T_Address, I2C_Direction_Transmitter);
	/* Test on EV6 and clear it */
    while (!I2C_CheckEvent(I2C_Chanel, I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED));
    /* Send the byte to be written */
    I2C_SendData(I2C_Chanel, data);
    /* Test on EV8 and clear it */
    while (!I2C_CheckEvent(I2C_Chanel, I2C_EVENT_MASTER_BYTE_TRANSMITTED));
    /* Send STOP condition */
    I2C_GenerateSTOP(I2C_Chanel, ENABLE);		
}

void LCD_Write_Data(char data)
{
	char data_u, data_l;
	uint8_t data_t[4]={0},i=0;
	data_u = data&0xf0;
	data_l = (data<<4)&0xf0;
	data_t[0] = data_u|0x0d;  //en=1, rs=0
	data_t[1] = data_u|0x09;  //en=0, rs=0
	data_t[2] = data_l|0x0d;  //en=1, rs=0
	data_t[3] = data_l|0x09;  //en=0, rs=0
	for(i = 0;i<4;i++)
	{
	     LCD_Write_Byte(data_t[i]);
	}

}

void LCD_Write_Control(char cmd)
{
	char data_u, data_l;
	uint8_t data_t[4]={0},i=0;
	data_u = cmd&0xf0;
	data_l = (cmd<<4)&0xf0;
	data_t[0] = data_u|0x0C;  //en=1, rs=0
	data_t[1] = data_u|0x08;  //en=0, rs=0
	data_t[2] = data_l|0x0C;  //en=1, rs=0
	data_t[3] = data_l|0x08;  //en=0, rs=0
	for(i = 0;i<4;i++)
	{
	     LCD_Write_Byte(data_t[i]);
	}

}

void LCD_Config(void)
{
	/* Set 4-bits interface */
	LCD_Write_Control(0x33);		 
	DELAY_ms(DELAY_TIME);
	LCD_Write_Control(0x32);
	DELAY_ms(DELAY_TIME);
	/* Start to set LCD function */
	LCD_Write_Control(0x28);
	DELAY_ms(DELAY_TIME);	
	/* clear LCD */
	LCD_Write_Control(0x01);
	DELAY_ms(DELAY_TIME);
	/* wait 60ms */
	
	/* set entry mode */
	LCD_Write_Control(0x06);	
	DELAY_ms(DELAY_TIME);
	/* set display to on */	
	LCD_Write_Control(0x0C);	
	DELAY_ms(DELAY_TIME);
	/* move cursor to home and set data address to 0 */
	LCD_Write_Control(0x02);	
	DELAY_ms(DELAY_TIME);
	LCD_Write_Control(0x80);
}

void LCD_Write_String (char *str)
{
	while(*str) LCD_Write_Data(*str++);
}

void LCD_Goto_XY (uint8_t row, uint8_t col)
{
	uint8_t pos_Addr;
	if(row == 1) {
		pos_Addr = 0x80 + row - 1 + col;
	}
	else{
		pos_Addr = 0x80 | (0x40 + col);
	}
	LCD_Write_Control(pos_Addr);
}

void LCD_Interger_Number(int32_t number)
{
//		char str[5];
//    sprintf(str, "%d", number);
//    LCD_Write_String(str);
	uint8_t count_element=0;// count_element: bien dem so luong phan tu cua chuoi so
	int32_t varNumber=number;
	uint8_t string_number[10];
	if(number<0)
	{
		varNumber=-varNumber;
	}
		
	while(varNumber)
	{
		string_number[count_element]=(uint8_t)(varNumber%10)+48;
		count_element++;
		varNumber/=10;
	}
	
	if(number<0)
	{
		string_number[count_element]='-';
		count_element++;
	}
	
	string_number[count_element]='\0';
	while(count_element--)
	{
		LCD_Write_Data(string_number[count_element]);
	}
}	

void LCD_Float_Number(float number)
{
//		char str[5];
//    sprintf(str, "%.3f", number);
//    LCD_Write_String(str);
	uint8_t count_element=0;// count_element: bien dem so luong phan tu cua chuoi so
	int32_t varNumber=number*10000;
	uint8_t string_number[10];
	if(number<0)
	{
		varNumber=-varNumber;
	}
	
	if(varNumber%10>=5)
	{
		varNumber=(varNumber/10)+1;
	}
	else
	{
		varNumber=varNumber/10;
	}
	
	while(varNumber)
	{
		string_number[count_element]=(uint8_t)(varNumber%10)+48;
		if(count_element==3)
		{
			string_number[count_element]='.';
			count_element++;
			string_number[count_element]=(uint8_t)(varNumber%10)+48;
		}
		count_element++;
		varNumber/=10;
	}
	
	if(number<0)
	{
		string_number[count_element]='-';
		count_element++;
	}
	
	string_number[count_element]='\0';
	while(count_element--)
	{
		LCD_Write_Data(string_number[count_element]);
	}
}

void LCD_Clear(void)
{
	LCD_Write_Control(0x01);
	DELAY_ms(5);
}

void LCD_Clear_Row(uint8_t row)
{
	uint8_t i=0;
	if(row==1){
		LCD_Write_Control(ROW1);
		for(i=0; i<16; i++){
			LCD_Write_Data(' ');
		}
	}
	
	if(row==2){
		LCD_Write_Control(ROW2);
		for(i=0; i<16; i++){
			LCD_Write_Data(' ');
		}
	}
}

void LCD_Print_On(void)
{
	LCD_Clear();
	LCD_Goto_XY(1,0);
	LCD_Write_String("Set Current Time");
	DELAY_ms(500);
	LCD_Goto_XY(0,4);
	LCD_Write_String("00:00:00");
	DELAY_ms(1000);
	LCD_Clear();
}

void LCD_SetAlarm(uint8_t config_hour, uint8_t config_minute, uint8_t config_seconds)
{
	LCD_Goto_XY(1,4);
	LCD_Write_String("Set Alarm");
	
	if(config_hour < 1)
	{
		LCD_Goto_XY(0,4);
		LCD_Write_String("00");
	}
	else if(config_hour >= 1 && config_hour <= 9)
	{
		LCD_Goto_XY(0,4);
		LCD_Write_String("0"); 
		LCD_Goto_XY(0,5);
		LCD_Interger_Number(config_hour);
	}
	else
	{
		LCD_Goto_XY(0,4);
		LCD_Interger_Number(config_hour);
	}
	
	LCD_Goto_XY(0,6);
	LCD_Write_String(":");
	
	if(config_minute < 1)
	{
		LCD_Goto_XY(0,7);
		LCD_Write_String("00");
	}
	else if(config_minute >= 1 && config_minute <= 9)
	{
		LCD_Goto_XY(0,7);
		LCD_Write_String("0"); 
		LCD_Goto_XY(0,8);
		LCD_Interger_Number(config_minute);
	}
	else
	{
		LCD_Goto_XY(0,7);
		LCD_Interger_Number(config_minute);
	}
	
	LCD_Goto_XY(0,9);
	LCD_Write_String(":");
	
	if(config_seconds < 1)
	{
		LCD_Goto_XY(0,10);
		LCD_Write_String("00");
	}
	else if(config_seconds >= 1 && config_seconds <= 9)
	{
		LCD_Goto_XY(0,10);
		LCD_Write_String("0"); 
		LCD_Goto_XY(0,11);
		LCD_Interger_Number(config_seconds);
	}
	else
	{
		LCD_Goto_XY(0,10);
		LCD_Interger_Number(config_seconds);
	}
}

void LCD_SetTime(uint8_t current_hour, uint8_t current_minute, uint8_t current_seconds)
{
	LCD_Goto_XY(1,4);
	LCD_Write_String("Set Time");
	
	if(current_hour < 1)
	{
		LCD_Goto_XY(0,4);
		LCD_Write_String("00");
	}
	else if(current_hour >= 1 && current_hour <= 9)
	{
		LCD_Goto_XY(0,4);
		LCD_Write_String("0"); 
		LCD_Goto_XY(0,5);
		LCD_Interger_Number(current_hour);
	}
	else
	{
		LCD_Goto_XY(0,4);
		LCD_Interger_Number(current_hour);
	}
	
	LCD_Goto_XY(0,6);
	LCD_Write_String(":");
	
	if(current_minute < 1)
	{
		LCD_Goto_XY(0,7);
		LCD_Write_String("00");
	}
	else if(current_minute >= 1 && current_minute <= 9)
	{
		LCD_Goto_XY(0,7);
		LCD_Write_String("0"); 
		LCD_Goto_XY(0,8);
		LCD_Interger_Number(current_minute);
	}
	else
	{
		LCD_Goto_XY(0,7);
		LCD_Interger_Number(current_minute);
	}
	
	LCD_Goto_XY(0,9);
	LCD_Write_String(":");
	
	if(current_seconds < 1)
	{
		LCD_Goto_XY(0,10);
		LCD_Write_String("00");
	}
	else if(current_seconds >= 1 && current_seconds <= 9)
	{
		LCD_Goto_XY(0,10);
		LCD_Write_String("0"); 
		LCD_Goto_XY(0,11);
		LCD_Interger_Number(current_seconds);
	}
	else
	{
		LCD_Goto_XY(0,10);
		LCD_Interger_Number(current_seconds);
	}
}

void LCD_CurrentTime(uint8_t current_hour, uint8_t current_minute, uint8_t current_seconds)
{
	LCD_Goto_XY(1,2);
	LCD_Write_String("Current Time");
	
	if(current_hour < 1)
	{
		LCD_Goto_XY(0,4);
		LCD_Write_String("00");
	}
	else if(current_hour >= 1 && current_hour <= 9)
	{
		LCD_Goto_XY(0,4);
		LCD_Write_String("0"); 
		LCD_Goto_XY(0,5);
		LCD_Interger_Number(current_hour);
	}
	else
	{
		LCD_Goto_XY(0,4);
		LCD_Interger_Number(current_hour);
	}
	
	LCD_Goto_XY(0,6);
	LCD_Write_String(":");
	
	if(current_minute < 1)
	{
		LCD_Goto_XY(0,7);
		LCD_Write_String("00");
	}
	else if(current_minute >= 1 && current_minute <= 9)
	{
		LCD_Goto_XY(0,7);
		LCD_Write_String("0"); 
		LCD_Goto_XY(0,8);
		LCD_Interger_Number(current_minute);
	}
	else
	{
		LCD_Goto_XY(0,7);
		LCD_Interger_Number(current_minute);
	}
	
	LCD_Goto_XY(0,9);
	LCD_Write_String(":");
	
	if(current_seconds < 1)
	{
		LCD_Goto_XY(0,10);
		LCD_Write_String("00");
	}
	else if(current_seconds >= 1 && current_seconds <= 9)
	{
		LCD_Goto_XY(0,10);
		LCD_Write_String("0"); 
		LCD_Goto_XY(0,11);
		LCD_Interger_Number(current_seconds);
	}
	else
	{
		LCD_Goto_XY(0,10);
		LCD_Interger_Number(current_seconds);
	}
}
