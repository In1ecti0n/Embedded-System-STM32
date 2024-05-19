#ifndef __I2C_LIB_
#define __I2C_LIB_

#ifdef __cplusplus
 extern "C" {
#endif

#include "sys.h"
#include "stdint.h"

#define PCF8574T_Address    0x4E				// Dia chi cua I2C la 0x4E
#define I2C_Chanel      	I2C1				// Su dung bo I2C1 cua STM32

#define LCD_DATA			GPIO_Pin_7			// Data:			SDA
#define LCD_SCK				GPIO_Pin_6			// Clock:			SCL
#define LCD_PORT			GPIOB				// Port:			B

void I2C_Config(void);							// Cau hinh bo I2C1


#ifdef __cplusplus
}
#endif

#endif

/********************************* END OF FILE ********************************/
/******************************************************************************/

