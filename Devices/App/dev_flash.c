/*
 * dev_flash.c
 *
 *  Created on: Sep 9, 2024
 *      Author: szt
 */

#include "dev_flash.h"

#define FLASH_BANK_NUM	3
#define FLASH_WAITETIME         50000  

const FLASH_BLOCK Flash_Block[FLASH_BANK_NUM] =
{
	{.bank = FLASH_SECTOR_21,.start_addr = 0x81A0000,.stop_addr = 0x81BFFFF,.size = 131072},   
	{.bank = FLASH_SECTOR_22,.start_addr = 0x81C0000,.stop_addr = 0x81DFFFF,.size = 131072},
	{.bank = FLASH_SECTOR_23,.start_addr = 0x81E0000,.stop_addr = 0x81FFFFF,.size = 131072},
};

uint16_t ReadFlashBuff[128];

HAL_StatusTypeDef EraseFlash(uint32_t addr,uint8_t len)
{
	uint8_t tag_i = 0;
	uint32_t sector = 0;
	uint32_t sectorerror = 0;
	HAL_StatusTypeDef status = HAL_BUSY;
	FLASH_EraseInitTypeDef EraseInitStruct;

	if((addr < Flash_Block[0].start_addr) && (addr > Flash_Block[FLASH_BANK_NUM-1].stop_addr))
	{
		return HAL_ERROR;
	}

	HAL_FLASH_Unlock();
	
	for(tag_i = 0;tag_i < FLASH_BANK_NUM;tag_i++)
	{
		if((addr >= Flash_Block[tag_i].start_addr) && (addr <= Flash_Block[tag_i].stop_addr))
		{
				sector = Flash_Block[tag_i].bank;
				break;
		}
	}

	DevFlash_Read(addr,ReadFlashBuff,len);
	
	HAL_FLASH_Unlock();
	FLASH_WaitForLastOperation(FLASH_WAITETIME);
	__HAL_FLASH_DATA_CACHE_DISABLE();
	for(tag_i = 0;tag_i < len;tag_i++)
	{
			if(ReadFlashBuff[tag_i] != 0xFFFF)
			{	
					EraseInitStruct.TypeErase = FLASH_TYPEERASE_SECTORS;
					EraseInitStruct.NbSectors = 1;
					EraseInitStruct.Sector = sector;
					EraseInitStruct.VoltageRange = FLASH_VOLTAGE_RANGE_3;

					status = HAL_FLASHEx_Erase(&EraseInitStruct, &sectorerror);
					if(status != HAL_OK)
					{
						HAL_FLASH_Lock();
						return status;
					}
					break;
			}
	}
	HAL_FLASH_Lock();
	
	return status;
}

HAL_StatusTypeDef DevFlash_Write(uint32_t addr,uint16_t* buff,uint16_t len)
{
	uint8_t tag_i = 0;
	uint32_t sector = 0;
	uint32_t writeaddr = 0;
	uint32_t writedata = 0;
	uint32_t sectorerror = 0;
	
	HAL_StatusTypeDef status = HAL_BUSY;
	FLASH_EraseInitTypeDef EraseInitStruct;

	if((addr < Flash_Block[0].start_addr) && (addr > Flash_Block[FLASH_BANK_NUM-1].stop_addr))
	{
		return HAL_ERROR;
	}
	
	for(tag_i = 0;tag_i < FLASH_BANK_NUM;tag_i++)
	{
		if((addr >= Flash_Block[tag_i].start_addr) && (addr <= Flash_Block[tag_i].stop_addr))
		{
				sector = Flash_Block[tag_i].bank;
				break;
		}
	}

	DevFlash_Read(addr,ReadFlashBuff,len);
	
	HAL_FLASH_Unlock();
	FLASH_WaitForLastOperation(FLASH_WAITETIME);
	__HAL_FLASH_DATA_CACHE_DISABLE();
	for(tag_i = 0;tag_i < len;tag_i++)
	{
			if(ReadFlashBuff[tag_i] != 0xFFFF)
			{	
					EraseInitStruct.TypeErase = FLASH_TYPEERASE_SECTORS;
					EraseInitStruct.NbSectors = 1;
					EraseInitStruct.Sector = sector;
					EraseInitStruct.VoltageRange = FLASH_VOLTAGE_RANGE_3;

					status = HAL_FLASHEx_Erase(&EraseInitStruct, &sectorerror);
					if(status != HAL_OK)
					{
						HAL_FLASH_Lock();
						return status;
					}
					break;
			}
	}

	writeaddr = addr;

	for(tag_i = 0;tag_i < len;tag_i++)
	{
		writedata = buff[tag_i];
		status = HAL_FLASH_Program(FLASH_TYPEPROGRAM_HALFWORD, writeaddr, (uint64_t)writedata);
		if(status != HAL_OK)
		{
			__HAL_FLASH_DATA_CACHE_ENABLE();
			HAL_FLASH_Lock();
			return status;
		}else
		{
			writeaddr += 2;
		}
	}
	__HAL_FLASH_DATA_CACHE_ENABLE();
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
