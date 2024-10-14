/*
 * dev_flash.h
 *
 *  Created on: Sep 9, 2024
 *      Author: szt
 */

#ifndef DEV_FLASH_H_
#define DEV_FLASH_H_

#include "main.h"
#include <stdint.h>

typedef struct
{
	uint32_t bank;
	uint32_t start_addr;
	uint32_t stop_addr;
	uint32_t size;
}FLASH_BLOCK;



#endif /* DEV_FLASH_H_ */
