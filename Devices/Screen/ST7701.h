#ifndef __ST7701_H
#define __ST7701_H

#include "main.h"


#define ST7701_CS(x)		do{ x ? \
														 HAL_GPIO_WritePin(LCD_SPI_CS_GPIO_Port, LCD_SPI_CS_Pin, GPIO_PIN_SET) : \
														 HAL_GPIO_WritePin(LCD_SPI_CS_GPIO_Port, LCD_SPI_CS_Pin, GPIO_PIN_RESET); \
													}while(0) 

#define ST7701_SDA(x)		do{ x ? \
														 HAL_GPIO_WritePin(LCD_SPI_SDA_GPIO_Port, LCD_SPI_SDA_Pin, GPIO_PIN_SET) : \
														 HAL_GPIO_WritePin(LCD_SPI_SDA_GPIO_Port, LCD_SPI_SDA_Pin, GPIO_PIN_RESET); \
											  }while(0) 

#define ST7701_SCL(x)		do{ x ? \
														 HAL_GPIO_WritePin(LCD_SPI_SCL_GPIO_Port, LCD_SPI_SCL_Pin, GPIO_PIN_SET) : \
														 HAL_GPIO_WritePin(LCD_SPI_SCL_GPIO_Port, LCD_SPI_SCL_Pin, GPIO_PIN_RESET); \
													}while(0) 

#define ST7701_READ		HAL_GPIO_ReadPin(LCD_SPI_SDA_GPIO_Port, LCD_SPI_SDA_Pin) /* 输入SDA */
													
void st7701_init(void);
												
#endif
