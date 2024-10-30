/*
 * dev_flash.h
 *
 *  Created on: Sep 9, 2024
 *      Author: szt
 */

#ifndef DEV_FLASH_H_
#define DEV_FLASH_H_

#include "main.h"

typedef struct
{
	uint32_t bank;
	uint32_t start_addr;
	uint32_t stop_addr;
	uint32_t size;
}FLASH_BLOCK;

HAL_StatusTypeDef DevFlash_Write(uint32_t addr,uint16_t* buff,uint16_t len);
void DevFlash_Read(uint32_t addr,uint16_t* buff,uint16_t len);

#endif /* DEV_FLASH_H_ */
