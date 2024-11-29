/*
 * dev_mpc5043.h
 *
 *  Created on: Sep 8, 2024
 *      Author: sunzhentao
 */

#ifndef DEV_MPC5043_H_
#define DEV_MPC5043_H_

#include "main.h"

#define BOOST						1
#define CHARGE 					2
#define CHARGE_FINISH		3

typedef enum
{
	Battery_Level1 = 1,
	Battery_Level2,
	Battery_Level3,
	Battery_Level4,
	Battery_Level5,
}Battery_Level;

void DevMPC5043_MainFunc(void);
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin);

#endif /* DEV_MPC5043_H_ */
