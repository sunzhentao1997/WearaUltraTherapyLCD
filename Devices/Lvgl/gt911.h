#ifndef __GT911_H
#define __GT911_H

#include "main.h"

#define GT911_IIC_SCL(x)		do{ x ? \
																HAL_GPIO_WritePin(T_SCK_GPIO_Port,T_SCK_Pin,GPIO_PIN_SET) : \
																HAL_GPIO_WritePin(T_SCK_GPIO_Port,T_SCK_Pin,GPIO_PIN_RESET); \
															}while(0)
#define GT911_IIC_SDA(x)		do{ x ? \
																HAL_GPIO_WritePin(T_MOSI_GPIO_Port,T_MOSI_Pin,GPIO_PIN_SET) : \
																HAL_GPIO_WritePin(T_MOSI_GPIO_Port,T_MOSI_Pin,GPIO_PIN_RESET); \
															}while(0)
#define GT911_READ_SDA			HAL_GPIO_ReadPin(T_MOSI_GPIO_Port,T_MOSI_Pin)
															
#define GT911_RST(x) 				do{ x ? \
																HAL_GPIO_WritePin(GPIOI,GPIO_PIN_8,GPIO_PIN_SET) : \
																HAL_GPIO_WritePin(GPIOI,GPIO_PIN_8,GPIO_PIN_RESET); \
															}while(0)
#define GT911_INT						HAL_GPIO_ReadPin(GPIOH,GPIO_PIN_7);
															
															
/* IIC读写命令 */
#define GT911_CMD_WR       0X28        /* 写命令 */
#define GT911_CMD_RD       0X29        /* 读命令 */

/* GT911 部分寄存器定义  */
#define GT911_CTRL_REG     0X8040      /* GT911控制寄存器 */
#define GT911_CFGS_REG     0X8047      /* GT911配置起始地址寄存器 */
#define GT911HECK_REG    	 0X80FF      /* GT911校验和寄存器 */
#define GT911_PID_REG      0X8140      /* GT911产品ID寄存器 */

#define GT911_GSTID_REG    0X814E      /* GT911当前检测到的触摸情况 */
#define GT911_TP1_REG      0X8150      /* 第一个触摸点数据地址 */
#define GT911_TP2_REG      0X8158      /* 第二个触摸点数据地址 */
#define GT911_TP3_REG      0X8160      /* 第三个触摸点数据地址 */
#define GT911_TP4_REG      0X8168      /* 第四个触摸点数据地址 */
#define GT911_TP5_REG      0X8170      /* 第五个触摸点数据地址 */
#define GT911_TP6_REG      0X8178      /* 第六个触摸点数据地址 */
#define GT911_TP7_REG      0X8180      /* 第七个触摸点数据地址 */
#define GT911_TP8_REG      0X8188      /* 第八个触摸点数据地址 */
#define GT911_TP9_REG      0X8190      /* 第九个触摸点数据地址 */
#define GT911_TP10_REG     0X8198      /* 第十个触摸点数据地址 */

uint8_t gt911_init(void);
uint8_t gt911_scan(uint8_t mode);


#endif
