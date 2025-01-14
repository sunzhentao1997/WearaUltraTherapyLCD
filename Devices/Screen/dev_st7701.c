#include "dev_st7701.h"

static void st7701_delay(uint16_t delay)
{
	uint16_t i = delay;

	while (i--)
		;
}

/*
 *函数名称：SPI_WriteComm
 *函数功能：SPI写命令
 *输入参数：data：命令数据
 *返回值：无
 */
static void SPI_WriteComm(uint8_t data)
{
	uint8_t n, m;

	ST7701_CS(0);
	ST7701_SCL(0);
	ST7701_SDA(0);
	ST7701_SCL(1);

	m = 0x80;
	for (n = 0; n < 8; n++)
	{
		if (data & m)
		{
			ST7701_SCL(0);
			ST7701_SDA(1);
			ST7701_SCL(1);
		}
		else
		{
			ST7701_SCL(0);
			ST7701_SDA(0);
			ST7701_SCL(1);
		}
		m = m >> 1;
	}

	ST7701_CS(1);
}

/*
 *函数名称：SPI_WriteData
 *函数功能：SPI写数据
 *输入参数：data：数据
 *返回值：无
 */
static void SPI_WriteData(uint8_t data)
{
	uint8_t n, m;

	ST7701_CS(0);
	ST7701_SCL(0);
	ST7701_SDA(1);
	ST7701_SCL(1);

	m = 0x80;
	for (n = 0; n < 8; n++)
	{
		if (data & m)
		{
			ST7701_SCL(0);
			ST7701_SDA(1);
			ST7701_SCL(1);
		}
		else
		{
			ST7701_SCL(0);
			ST7701_SDA(0);
			ST7701_SCL(1);
		}
		m = m >> 1;
	}

	ST7701_CS(1);
}

/*******************************************************************************************
 *
 *							ST7701S芯片初始化，有屏幕厂家提供
 *
 *******************************************************************************************/
/*
 *函数名称：st7701_init
 *函数功能：ST7701S芯片初始化，有屏幕厂家提供
 *输入参数：无
 *返回值：	无
 */
void st7701_init(void)
{
	HAL_GPIO_WritePin(LCD_RESET_GPIO_Port, LCD_RESET_Pin, GPIO_PIN_SET);
	HAL_Delay(100);
	ST7701_CS(0);
	HAL_Delay(1);

	SPI_WriteComm(0xFF); // 命令BK选择
	SPI_WriteData(0x77);
	SPI_WriteData(0x01);
	SPI_WriteData(0x00);
	SPI_WriteData(0x00);
	SPI_WriteData(0x13);

	SPI_WriteComm(0xEF);
	SPI_WriteData(0x08);

	SPI_WriteComm(0xFF);
	SPI_WriteData(0x77);
	SPI_WriteData(0x01);
	SPI_WriteData(0x00);
	SPI_WriteData(0x00);
	SPI_WriteData(0x10);

	SPI_WriteComm(0xC0); // 显示线设置
	SPI_WriteData(0x63); //[0x63,0x00]  EX = (0x63+1)*8 = 800
	SPI_WriteData(0x00);

	SPI_WriteComm(0xC1); // 门廊控制
	SPI_WriteData(0x0A); // VBP:10
	SPI_WriteData(0x0C); // VFP:12

	SPI_WriteComm(0xC2); // 反转选择和频率控制
	SPI_WriteData(0x01); //
	SPI_WriteData(0x08); // PCLK = 512 + ((0x08 & 0xF) * 16)

	SPI_WriteComm(0xCC); //
	SPI_WriteData(0x18);

	SPI_WriteComm(0xB0); // 正电压控制
	SPI_WriteData(0x00);
	SPI_WriteData(0x08);
	SPI_WriteData(0x10);
	SPI_WriteData(0x0E);
	SPI_WriteData(0x11);
	SPI_WriteData(0x07);
	SPI_WriteData(0x08);
	SPI_WriteData(0x08);
	SPI_WriteData(0x08);
	SPI_WriteData(0x25);
	SPI_WriteData(0x04);
	SPI_WriteData(0x12);
	SPI_WriteData(0x0F);
	SPI_WriteData(0x2C);
	SPI_WriteData(0x30);
	SPI_WriteData(0x1F);

	SPI_WriteComm(0xB1); // 负电压控制
	SPI_WriteData(0x00);
	SPI_WriteData(0x11);
	SPI_WriteData(0x18);
	SPI_WriteData(0x0C);
	SPI_WriteData(0x10);
	SPI_WriteData(0x05);
	SPI_WriteData(0x07);
	SPI_WriteData(0x09);
	SPI_WriteData(0x08);
	SPI_WriteData(0x24);
	SPI_WriteData(0x04);
	SPI_WriteData(0x11);
	SPI_WriteData(0x10);
	SPI_WriteData(0x2B);
	SPI_WriteData(0x30);
	SPI_WriteData(0x1F);

	SPI_WriteComm(0xFF);
	SPI_WriteData(0x77);
	SPI_WriteData(0x01);
	SPI_WriteData(0x00);
	SPI_WriteData(0x00);
	SPI_WriteData(0x11);

	SPI_WriteComm(0xB0);
	SPI_WriteData(0x4D);

	SPI_WriteComm(0xB1); // 亮度电压控制
	SPI_WriteData(0x31);

	SPI_WriteComm(0xB2);
	SPI_WriteData(0x87);

	SPI_WriteComm(0xB3);
	SPI_WriteData(0x80);

	SPI_WriteComm(0xB5);
	SPI_WriteData(0x47);

	SPI_WriteComm(0xB7);
	SPI_WriteData(0x8A);

	SPI_WriteComm(0xB8);
	SPI_WriteData(0x20);

	SPI_WriteComm(0xB9);
	SPI_WriteData(0x10);
	SPI_WriteData(0x13);

	SPI_WriteComm(0xC0);
	SPI_WriteData(0x09);

	SPI_WriteComm(0xC1);
	SPI_WriteData(0x78);

	SPI_WriteComm(0xC2);
	SPI_WriteData(0x78);

	SPI_WriteComm(0xD0);
	SPI_WriteData(0x88);

	st7701_delay(100);

	SPI_WriteComm(0xE0);
	SPI_WriteData(0x00);
	SPI_WriteData(0x00);
	SPI_WriteData(0x02);

	SPI_WriteComm(0xE1);
	SPI_WriteData(0x04);
	SPI_WriteData(0x00);
	SPI_WriteData(0x00);
	SPI_WriteData(0x00);
	SPI_WriteData(0x05);
	SPI_WriteData(0x00);
	SPI_WriteData(0x00);
	SPI_WriteData(0x00);
	SPI_WriteData(0x00);
	SPI_WriteData(0x20);
	SPI_WriteData(0x20);

	SPI_WriteComm(0xE2);
	SPI_WriteData(0x00);
	SPI_WriteData(0x00);
	SPI_WriteData(0x00);
	SPI_WriteData(0x00);
	SPI_WriteData(0x00);
	SPI_WriteData(0x00);
	SPI_WriteData(0x00);
	SPI_WriteData(0x00);
	SPI_WriteData(0x00);
	SPI_WriteData(0x00);
	SPI_WriteData(0x00);
	SPI_WriteData(0x00);
	SPI_WriteData(0x00);

	SPI_WriteComm(0xE3);
	SPI_WriteData(0x00);
	SPI_WriteData(0x00);
	SPI_WriteData(0x33);
	SPI_WriteData(0x00);

	SPI_WriteComm(0xE4);
	SPI_WriteData(0x22);
	SPI_WriteData(0x00);

	SPI_WriteComm(0xE5);
	SPI_WriteData(0x04);
	SPI_WriteData(0x34);
	SPI_WriteData(0xAA);
	SPI_WriteData(0xAA);
	SPI_WriteData(0x06);
	SPI_WriteData(0x34);
	SPI_WriteData(0xAA);
	SPI_WriteData(0xAA);
	SPI_WriteData(0x00);
	SPI_WriteData(0x00);
	SPI_WriteData(0x00);
	SPI_WriteData(0x00);
	SPI_WriteData(0x00);
	SPI_WriteData(0x00);
	SPI_WriteData(0x00);
	SPI_WriteData(0x00);

	SPI_WriteComm(0xE6);
	SPI_WriteData(0x00);
	SPI_WriteData(0x00);
	SPI_WriteData(0x33);
	SPI_WriteData(0x00);

	SPI_WriteComm(0xE7);
	SPI_WriteData(0x22);
	SPI_WriteData(0x00);

	SPI_WriteComm(0xE8);
	SPI_WriteData(0x05);
	SPI_WriteData(0x34);
	SPI_WriteData(0xAA);
	SPI_WriteData(0xAA);
	SPI_WriteData(0x07);
	SPI_WriteData(0x34);
	SPI_WriteData(0xAA);
	SPI_WriteData(0xAA);
	SPI_WriteData(0x00);
	SPI_WriteData(0x00);
	SPI_WriteData(0x00);
	SPI_WriteData(0x00);
	SPI_WriteData(0x00);
	SPI_WriteData(0x00);
	SPI_WriteData(0x00);
	SPI_WriteData(0x00);

	SPI_WriteComm(0xEB);
	SPI_WriteData(0x02);
	SPI_WriteData(0x00);
	SPI_WriteData(0x40);
	SPI_WriteData(0x40);
	SPI_WriteData(0x00);
	SPI_WriteData(0x00);
	SPI_WriteData(0x00);

	SPI_WriteComm(0xEC);
	SPI_WriteData(0x00);
	SPI_WriteData(0x00);

	SPI_WriteComm(0xED);
	SPI_WriteData(0xFA);
	SPI_WriteData(0x45);
	SPI_WriteData(0x0B);
	SPI_WriteData(0xFF);
	SPI_WriteData(0xFF);
	SPI_WriteData(0xFF);
	SPI_WriteData(0xFF);
	SPI_WriteData(0xFF);
	SPI_WriteData(0xFF);
	SPI_WriteData(0xFF);
	SPI_WriteData(0xFF);
	SPI_WriteData(0xFF);
	SPI_WriteData(0xFF);
	SPI_WriteData(0xB0);
	SPI_WriteData(0x54);
	SPI_WriteData(0xAF);

	SPI_WriteComm(0xEF);
	SPI_WriteData(0x10);
	SPI_WriteData(0x0D);
	SPI_WriteData(0x04);
	SPI_WriteData(0x08);
	SPI_WriteData(0x3F);
	SPI_WriteData(0x1F);

	SPI_WriteComm(0xFF);
	SPI_WriteData(0x77);
	SPI_WriteData(0x01);
	SPI_WriteData(0x00);
	SPI_WriteData(0x00);
	SPI_WriteData(0x13);

	SPI_WriteComm(0xE8);
	SPI_WriteData(0x00);
	SPI_WriteData(0x0E);

	SPI_WriteComm(0xFF);
	SPI_WriteData(0x77);
	SPI_WriteData(0x01);
	SPI_WriteData(0x00);
	SPI_WriteData(0x00);
	SPI_WriteData(0x00);

	SPI_WriteComm(0xFF);
	SPI_WriteData(0x77);
	SPI_WriteData(0x01);
	SPI_WriteData(0x00);
	SPI_WriteData(0x00);
	SPI_WriteData(0x13);

	SPI_WriteComm(0xE8);
	SPI_WriteData(0x00);
	SPI_WriteData(0x0C);

	st7701_delay(10);

	SPI_WriteComm(0xE8);
	SPI_WriteData(0x00);
	SPI_WriteData(0x00);

	SPI_WriteComm(0xFF);
	SPI_WriteData(0x77);
	SPI_WriteData(0x01);
	SPI_WriteData(0x00);
	SPI_WriteData(0x00);
	SPI_WriteData(0x12);

	SPI_WriteComm(0xD1); // MIPI设置
	SPI_WriteData(0x00);

	SPI_WriteComm(0x36); // 颜色格式
	SPI_WriteData(0x00); // 0x80:BGR格式	0x00:RGB格式

	SPI_WriteComm(0x11); // 关闭休眠模式
	st7701_delay(120);

	SPI_WriteComm(0x29); // 显示开
	st7701_delay(20);
}
