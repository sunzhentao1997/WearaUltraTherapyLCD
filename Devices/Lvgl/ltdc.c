#include "ltdc.h"
#include "main.h"

//LCD的画笔颜色和背景色
uint32_t POINT_COLOR = 0xFF000000;		//画笔颜色
uint32_t BACK_COLOR = 0xFFFFFFFF;  	//背景色
uint16_t ltdc_lcd_framebuf[1280][800] __attribute__((at(LCD_FRAME_BUF_ADDR)));	//定义最大屏分辨率时,LCD所需的帧缓存数组大小
uint32_t *ltdc_framebuf[2];					//LTDC LCD帧缓存数组指针,必须指向对应大小的内存区域
_ltdc_dev lcdltdc;						//管理LCD LTDC的重要参数
//默认为竖屏
_lcd_dev lcddev;
extern LTDC_HandleTypeDef hltdc;

//设置LCD显示方向
//dir:0,竖屏；1,横屏
static void LTDC_Display_Dir(uint8_t dir)
{
	lcdltdc.dir=dir; 	//显示方向
	if(dir==0)			//竖屏
	{
		lcdltdc.width=lcdltdc.pheight;
		lcdltdc.height=lcdltdc.pwidth;	
	}else if(dir==1)	//横屏
	{
		lcdltdc.width=lcdltdc.pwidth;
		lcdltdc.height=lcdltdc.pheight;
	}
}

//选择层
//layerx:层号;0,第一层;1,第二层;
static void LTDC_Select_Layer(uint8_t layerx)
{
	lcdltdc.activelayer=layerx;
}
//LTDC填充矩形,DMA2D填充
//(sx,sy),(ex,ey):填充矩形对角坐标,区域大小为:(ex-sx+1)*(ey-sy+1)   
//color:要填充的颜色
//有时候需要频繁的调用填充函数，所以为了速度，填充函数采用寄存器版本，
//不过下面有对应的库函数版本的代码。
static void LTDC_Fill(uint16_t sx,uint16_t sy,uint16_t ex,uint16_t ey,uint32_t color)
{ 
	uint32_t psx,psy,pex,pey;	//以LCD面板为基准的坐标系,不随横竖屏变化而变化
	uint32_t timeout = 0; 
	uint16_t offline;
	uint32_t addr; 
	//坐标系转换
	if(lcdltdc.dir)	//横屏
	{
			psx = sx;
			psy = sy;
			pex = ex;
			pey = ey;
	}else			//竖屏
	{
			if (ex >= lcdltdc.pheight)
			{
				ex = lcdltdc.pheight - 1;  /* 限制范围 */
			}
			if (sx >= lcdltdc.pheight)
			{
				sx = lcdltdc.pheight - 1;  /* 限制范围 */
			}
			
			psx = sy;
			psy = lcdltdc.pheight - ex - 1;
			pex = ey;
			pey = lcdltdc.pheight - sx - 1;
	}
	
	offline = lcdltdc.pwidth - (pex - psx + 1);
	addr = ((uint32_t)ltdc_framebuf[lcdltdc.activelayer] + lcdltdc.pixsize * (lcdltdc.pwidth * psy + psx));
	
	__HAL_RCC_DMA2D_CLK_ENABLE();																//使能DM2D时钟
	DMA2D->CR &= ~(DMA2D_CR_START);															//先停止DMA2D
	DMA2D->CR = DMA2D_R2M;																			//寄存器到存储器模式
	DMA2D->OPFCCR = LTDC_PIXFORMAT;															//设置颜色格式
	DMA2D->OOR = offline;																				//设置行偏移 
	DMA2D->OMAR = addr;																					//输出存储器地址
	DMA2D->NLR = (pey - psy + 1) | ((pex - psx + 1) << 16);			//设定行数寄存器
	DMA2D->OCOLR = color;																         //设定输出颜色寄存器 
	DMA2D->CR |= DMA2D_CR_START;																	//启动DMA2D
	
	while((DMA2D->ISR & (DMA2D_FLAG_TC)) == 0)										//等待传输完成
	{
		timeout++;
		if(timeout > 0X1FFFFF)break;																//超时退出
	} 
	DMA2D->IFCR |= DMA2D_FLAG_TC;																	//清除传输完成标志 		
}
//LCD清屏
//color:颜色值
static void LTDC_Clear(uint32_t color)
{
	LTDC_Fill(0,0,lcdltdc.width-1,lcdltdc.height-1,color);
}

void LTDC_Init(void)
{
		lcdltdc.pwidth=800;		    //面板宽度,单位:像素
		lcdltdc.pheight=480;	    //面板高度,单位:像素
		lcdltdc.hbp=88;			    //水平后廊
		lcdltdc.hfp=40;		    	//水平前廊
		lcdltdc.hsw=48;			    //水平同步宽度
		lcdltdc.vbp=32;			    //垂直后廊
		lcdltdc.vfp=13;			    //垂直前廊
		lcdltdc.vsw=3;				//垂直同步宽度

		lcddev.width=lcdltdc.pwidth;
		lcddev.height=lcdltdc.pheight;
	
		lcdltdc.pixsize=2;				//每个像素占2个字节
		ltdc_framebuf[0]=(uint32_t*)&ltdc_lcd_framebuf;
	
		LTDC_Display_Dir(1);			//默认竖屏
		LTDC_Select_Layer(0); 			//选择第1层
		HAL_GPIO_WritePin(GPIOB,GPIO_PIN_5,GPIO_PIN_SET);       		        //点亮背光
		LTDC_Clear(0XFFFFFFFF);			//清屏
}

//清屏函数
//color:要清屏的填充色
void LCD_Clear(uint32_t color)
{
   LTDC_Clear(color);
}

/**
 * @brief       在指定区域内填充指定颜色块,DMA2D填充
 * @note        此函数仅支持uint16_t,RGB565格式的颜色数组填充.
 *              (sx,sy),(ex,ey):填充矩形对角坐标,区域大小为:(ex - sx + 1) * (ey - sy + 1)
 *              注意:sx,ex,不能大于lcddev.width - 1; sy,ey,不能大于lcddev.height - 1
 * @param       sx,sy       : 起始坐标
 * @param       ex,ey       : 结束坐标
 * @param       color       : 填充的颜色数组首地址
 * @retval      无
 */
void ltdc_color_fill(uint16_t sx, uint16_t sy, uint16_t ex, uint16_t ey, uint16_t *color)
{
    uint32_t psx, psy, pex, pey;   /* 以LCD面板为基准的坐标系,不随横竖屏变化而变化 */
    uint32_t timeout = 0; 
    uint16_t offline;
    uint32_t addr;
  
    /* 坐标系转换 */
    if (lcdltdc.dir)               /* 横屏 */
    {
        psx = sx;
        psy = sy;
        pex = ex;
        pey = ey;
    }
    else                          /* 竖屏 */
    {
        psx = sy;
        psy = lcdltdc.pheight - ex - 1;
        pex = ey;
        pey = lcdltdc.pheight - sx - 1;
    }
    
    offline = lcdltdc.pwidth - (pex - psx + 1);
    addr = ((uint32_t)ltdc_framebuf[lcdltdc.activelayer] + lcdltdc.pixsize * (lcdltdc.pwidth * psy + psx));

    RCC->AHB1ENR |= 1 << 23;            /* 使能DM2D时钟 */

    DMA2D->CR = 0 << 16;                /* 存储器到存储器模式 */
    DMA2D->FGPFCCR = LTDC_PIXFORMAT;    /* 设置颜色格式 */
    DMA2D->FGOR = 0;                    /* 前景层行偏移为0 */
    DMA2D->OOR = offline;               /* 设置行偏移 */
    DMA2D->CR &= ~(1 << 0);             /* 先停止DMA2D */
    DMA2D->FGMAR = (uint32_t)color;     /* 源地址 */
    DMA2D->OMAR = addr;                 /* 输出存储器地址 */
    DMA2D->NLR = (pey - psy + 1) | ((pex - psx + 1) << 16); /* 设定行数寄存器 */
    DMA2D->CR |= 1 << 0;                /* 启动DMA2D */

    while ((DMA2D->ISR & (1 << 1)) == 0)/* 等待传输完成 */
    {
        timeout++;

        if (timeout > 0X1FFFFF)break;   /* 超时退出 */
    }

    DMA2D->IFCR |= 1 << 1;              /* 清除传输完成标志 */
}  


void LDC_Display_Dir(uint8_t dir)
{
		 lcdltdc.dir = dir;    /* 显示方向 */

    if (dir == 0)         /* 竖屏 */
    {
        lcdltdc.width = lcdltdc.pheight;
        lcdltdc.height = lcdltdc.pwidth;
    }
    else if (dir == 1)    /* 横屏 */
    {
        lcdltdc.width = lcdltdc.pwidth;
        lcdltdc.height = lcdltdc.pheight;
    }
		lcddev.width = lcdltdc.width;
    lcddev.height = lcdltdc.height;
}
