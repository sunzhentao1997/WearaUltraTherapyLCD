/*
 * dev_mpc5043.h
 *
 *  Created on: Sep 8, 2024
 *      Author: sunzhentao
 */

#ifndef DEV_MPC5043_H_
#define DEV_MPC5043_H_

#include "main.h"

typedef enum
{
	Charge_Level1 = 1,
	Charge_Level2,
	Charge_Level3,
	Charge_Level4,
	Charge_Level5,
	Boost_Level1,
	Boost_Level2,
	Boost_Level3,
	Boost_Level4,
	Boost_Level5,
}Battery_Level;

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin);

#endif /* DEV_MPC5043_H_ */
