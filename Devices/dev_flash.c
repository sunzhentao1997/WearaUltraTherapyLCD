/*
 * dev_flash.c
 *
 *  Created on: Sep 9, 2024
 *      Author: szt
 */

#include "dev_flash.h"

const FLASH_BLOCK Flash_Block[8] =
{
	{.bank = FLASH_SECTOR_12,.flash_addr = 0x8100000,.size = 16384},
	{.bank = FLASH_SECTOR_13,.flash_addr = 0x8104000,.size = 16384},
	{.bank = FLASH_SECTOR_14,.flash_addr = 0x8108000,.size = 16384},
	{.bank = FLASH_SECTOR_15,.flash_addr = 0x810C000,.size = 16384},
	{.bank = FLASH_SECTOR_16,.flash_addr = 0x8110000,.size = 65536},
	{.bank = FLASH_SECTOR_17,.flash_addr = 0x8120000,.size = 131072},
	{.bank = FLASH_SECTOR_18,.flash_addr = 0x8140000,.size = 131072},
	{.bank = FLASH_SECTOR_19,.flash_addr = 0x8160000,.size = 0},

};

HAL_StatusTypeDef DevFlash_Write(uint32_t addr,uint16_t* buff,uint16_t len)
{
	uint8_t tag_i = 0;
	uint32_t sector = 0;
	uint32_t writeaddr = 0;
	uint32_t writedata = 0;
	uint32_t sectorerror;
	HAL_StatusTypeDef status = HAL_BUSY;
	FLASH_EraseInitTypeDef EraseInitStruct;

	if((addr < Flash_Block[0].flash_addr) && (addr > Flash_Block[6].flash_addr))
	{
		return HAL_ERROR;
	}

	for(tag_i = 0;tag_i < 7;tag_i++)
	{
		if((addr >= Flash_Block[tag_i].flash_addr) && (addr < Flash_Block[tag_i+1].flash_addr))
		{
			sector = Flash_Block[tag_i].bank;
			break;
		}
	}

	HAL_FLASH_Unlock();

	EraseInitStruct.TypeErase = FLASH_TYPEERASE_SECTORS;
	EraseInitStruct.NbSectors = 1;
	EraseInitStruct.Sector = sector;
	EraseInitStruct.VoltageRange = FLASH_VOLTAGE_RANGE_3;

	status = HAL_FLASHEx_Erase(&EraseInitStruct, &sectorerror);
	if(status != HAL_OK)
	{
		return status;
	}

	writeaddr = addr;

	for(tag_i = 0;tag_i < len;tag_i++)
	{
		writedata = buff[tag_i];
		status = HAL_FLASH_Program(FLASH_TYPEPROGRAM_HALFWORD, writeaddr, (uint64_t)writedata);
		if(status != HAL_OK)
		{
			return status;
		}else
		{
			writeaddr += 2;
		}
	}
	HAL_FLASH_Lock();

	return status;
}

void DevFlash_Read(uint32_t addr,uint16_t* buff,uint16_t len)
{
	uint8_t tag_i = 0;
	uint32_t readaddr = 0;

	// 解锁闪存
	HAL_FLASH_Unlock();
	readaddr = addr;
	for (tag_i = 0; tag_i < len; tag_i++)
	{
		*(buff + tag_i) = *(volatile uint32_t *)readaddr;
		readaddr += 2;
	}
	// 锁定闪存
	HAL_FLASH_Lock();
}


