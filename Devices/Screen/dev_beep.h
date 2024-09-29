#ifndef __DEV_BEEP_H
#define __DEV_BEEP_H

#include "main.h"

/******************************************************************************************/
/* 引脚 定义 */

#define IIC_SCL_GPIO_PORT               GPIOH
#define IIC_SCL_GPIO_PIN                GPIO_PIN_4
#define IIC_SCL_GPIO_CLK_ENABLE()       do{ __HAL_RCC_GPIOH_CLK_ENABLE(); }while(0)   /* PH口时钟使能 */

#define IIC_SDA_GPIO_PORT               GPIOH
#define IIC_SDA_GPIO_PIN                GPIO_PIN_5
#define IIC_SDA_GPIO_CLK_ENABLE()       do{ __HAL_RCC_GPIOH_CLK_ENABLE(); }while(0)   /* PH口时钟使能 */

/******************************************************************************************/
/* IO操作 */

#define IIC_SCL(x)        do{ x ? \
                              HAL_GPIO_WritePin(IIC_SCL_GPIO_PORT, IIC_SCL_GPIO_PIN, GPIO_PIN_SET) : \
                              HAL_GPIO_WritePin(IIC_SCL_GPIO_PORT, IIC_SCL_GPIO_PIN, GPIO_PIN_RESET); \
                          }while(0)       /* SCL */

#define IIC_SDA(x)        do{ x ? \
                              HAL_GPIO_WritePin(IIC_SDA_GPIO_PORT, IIC_SDA_GPIO_PIN, GPIO_PIN_SET) : \
                              HAL_GPIO_WritePin(IIC_SDA_GPIO_PORT, IIC_SDA_GPIO_PIN, GPIO_PIN_RESET); \
                          }while(0)       /* SDA */

#define IIC_READ_SDA     HAL_GPIO_ReadPin(IIC_SDA_GPIO_PORT, IIC_SDA_GPIO_PIN)        /* 读取SDA */

/******************************************************************************************/
													
													/******************************************************************************************/
/* 引脚 定义 */

#define PCF8574_GPIO_PORT                  GPIOB
#define PCF8574_GPIO_PIN                   GPIO_PIN_12
#define PCF8574_GPIO_CLK_ENABLE()          do{ __HAL_RCC_GPIOB_CLK_ENABLE(); }while(0)  /* PB口时钟使能 */

/******************************************************************************************/

#define PCF8574_INT  HAL_GPIO_ReadPin(PCF8574_GPIO_PORT, PCF8574_GPIO_PIN)              /* PCF8574 INT脚 */

#define PCF8574_ADDR  0X40      /* PCF8574地址(左移了一位) */

/* PCF8574各个IO的功能 */
#define BEEP_IO         0       /* 蜂鸣器控制引脚        P0 */
#define AP_INT_IO       1       /* AP3216C中断引脚       P1 */
#define DCMI_PWDN_IO    2       /* DCMI的电源控制引脚    P2 */
#define USB_PWR_IO      3       /* USB电源控制引脚       P3 */
#define EX_IO           4       /* 扩展IO,自定义使用     P4 */
#define MPU_INT_IO      5       /* SH3001中断引脚        P5 */
#define RS485_RE_IO     6       /* RS485_RE引脚          P6 */
#define ETH_RESET_IO    7       /* 以太网复位引脚        P7 */

/******************************************************************************************/
/* IIC所有操作函数 */

void iic_init(void);                        /* 初始化IIC的IO口 */
void iic_start(void);                       /* 发送IIC开始信号 */
void iic_stop(void);                        /* 发送IIC停止信号 */
void iic_ack(void);                         /* IIC发送ACK信号 */
void iic_nack(void);                        /* IIC不发送ACK信号 */
uint8_t iic_wait_ack(void);                 /* IIC等待ACK信号 */
void iic_send_byte(uint8_t data);           /* IIC发送一个字节 */
uint8_t iic_read_byte(unsigned char ack);   /* IIC读取一个字节 */
													


uint8_t pcf8574_init(void); 
uint8_t pcf8574_read_byte(void); 
void pcf8574_write_byte(uint8_t data);
void pcf8574_write_bit(uint8_t bit, uint8_t sta);
uint8_t pcf8574_read_bit(uint8_t bit);

void beep_func(void);

#endif
