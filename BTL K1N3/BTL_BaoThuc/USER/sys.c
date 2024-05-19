#include "sys.h"


static uint8_t flag_display = 0;
static uint8_t config_hour = 0, config_minute = 0, config_seconds = 0;
static uint8_t current_hour = 0, current_minute = 0, current_seconds = 0;
static char arr_recive[10];

void SYS_Config(void)
{
	DELAY_Config();
	UART_Config();
	I2C_Config();
	LCD_Config();
	Device_Config();
}

void SYS_Run(void)
{
	if(flag_uart_get_end == 1)
	{
		for(int i = 0; i < 10; i++)
		{
			if(RRX[i] != ' ')
			{
				arr_recive[i] = RRX[i];
			}
			else
			{
				arr_recive[i] = '\0';
			}
		}
		
		if(strcmp(arr_recive, "set_time") == 0)
		{
			flag_display = 1;
			current_hour = (RRX[9] - 48)*10 + (RRX[10] - 48);
			current_minute = (RRX[12] - 48)*10 + (RRX[13] - 48);
			current_seconds = (RRX[15] - 48)*10 + (RRX[16] - 48);
			printf("\n%d %d %d\n", current_hour, current_minute, current_seconds);
		}
		if(strcmp(arr_recive, "set_alarm") == 0)
		{
			flag_display = 2;
			config_hour = (RRX[10] - 48)*10 + (RRX[11] - 48);
			config_minute = (RRX[13] - 48)*10 + (RRX[14] - 48);
			config_seconds = (RRX[16] - 48)*10 + (RRX[17] - 48);
			printf("\n%d %d %d\n", config_hour, config_minute, config_seconds);
		}
		
		flag_uart_get_end = 0;
	}
	
	if(flag_display == 0)
	{
		LCD_Print_On();
	}
	else if(flag_display == 1)
	{
		LCD_SetTime(current_hour, current_minute, current_seconds);
	}
	else if(flag_display == 2)
	{
		LCD_SetAlarm(config_hour, config_minute, config_seconds);
		DELAY_ms(1000);
		flag_display = 3;
	}
	else if(flag_display == 3)
	{
		LCD_CurrentTime(current_hour, current_minute, current_seconds);
		
		if(current_hour == config_hour && current_minute == config_minute)
		{
			if(current_seconds <= 10)
			{
				Device_SirensOn();
			}
			else
			{
				Device_SirensOff();
			}
		}
		else
		{
			Device_SirensOff();
		}
		
		current_seconds++;
		if (current_seconds == 60) 
		{
			current_seconds = 0;
			current_minute++;
			
			if (current_minute == 60) 
			{
				current_minute = 0;
				current_hour++;

				if (current_hour == 24) 
				{
					current_hour = 0;
				}
			}
		}
		
		DELAY_ms(800);
	}
}


