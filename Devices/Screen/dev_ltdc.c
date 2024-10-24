/**
 ****************************************************************************************************
 * @file        ltdc.c
 * @author      正点原子团队(ALIENTEK)
 * @version     V1.0
 * @date        2022-4-20
 * @brief       LTDC 驱动代码
 * @license     Copyright (c) 2020-2032, 广州市星翼电子科技有限公司
 ****************************************************************************************************
 * @attention
 *
 * 实验平台:正点原子 阿波罗 F429开发板
 * 在线视频:www.yuanzige.com
 * 技术论坛:www.openedv.com
 * 公司网址:www.alientek.com
 * 购买地址:openedv.taobao.com
 *
 * 修改说明
 * V1.0 20220420
 * 第一次发布
 *
 ****************************************************************************************************
 */
#include "dev_ltdc.h"
#include "dev_touch.h"
#include "ltdc.h"

extern uint8_t PressFlg;
extern uint16_t Gain;

#if !(__ARMCC_VERSION >= 6010050)                                                    /* 不是AC6编译器，即使用AC5编译器时 */

/* 根据不同的颜色格式,定义帧缓存数组 */
#if LTDC_PIXFORMAT == LTDC_PIXFORMAT_ARGB8888 || LTDC_PIXFORMAT == LTDC_PIXFORMAT_RGB888
    uint32_t ltdc_lcd_framebuf[1280][800] __attribute__((at(LTDC_FRAME_BUF_ADDR)));   /* 定义最大屏分辨率时,LTDC所需的帧缓存数组大小 */
#else
    uint16_t ltdc_lcd_framebuf[800][1280] __attribute__((at(LTDC_FRAME_BUF_ADDR)));   /* 定义最大屏分辨率时,LTDC所需的帧缓存数组大小 */
//    uint16_t ltdc_lcd_framebuf1[1280][800] __attribute__((at(LTDC_FRAME_BUF_ADDR + 1280 * 800 * 2)));   /* 使能LTDC层2时使用(默认使用LTDC层1) */
#endif

#else      /* 使用AC6编译器时 */

/* 根据不同的颜色格式,定义帧缓存数组 */
#if LTDC_PIXFORMAT == LTDC_PIXFORMAT_ARGB8888 || LTDC_PIXFORMAT == LTDC_PIXFORMAT_RGB888
    uint32_t ltdc_lcd_framebuf[1280][800] __attribute__((section(".bss.ARM.__at_0XC0000000")));  /* 定义最大屏分辨率时,LTDC所需的帧缓存数组大小 */
#else
    uint16_t ltdc_lcd_framebuf[1280][800] __attribute__((section(".bss.ARM.__at_0XC0000000")));  /* 定义最大屏分辨率时,LTDC所需的帧缓存数组大小 */
#endif

#endif

/* 管理LCD重要参数 */
_lcd_dev lcddev;
_ltdc_dev lcdltdc;
uint32_t *g_ltdc_framebuf[2];                /* LTDC LCD帧缓存数组指针,必须指向对应大小的内存区域 */
/**
 * @brief       LTDC选择层
 * @param       layerx   : 层号;0,第一层; 1,第二层;
 * @retval      无
 */
void ltdc_select_layer(uint8_t layerx)
{
    lcdltdc.activelayer = layerx;
}
/**
 * @brief       LTDC显示方向设置
 * @param       dir          : 0,竖屏；1,横屏
 * @retval      无
 */
void ltdc_display_dir(uint8_t dir)
{
    lcdltdc.dir = dir;    /* 显示方向 */

    if (dir == 0)         /* 竖屏 */
    {
        lcdltdc.width = lcdltdc.pheight;
				lcddev.width = lcdltdc.width;
        lcdltdc.height = lcdltdc.pwidth;
			  lcddev.height = lcdltdc.height;
    }
    else if (dir == 1)    /* 横屏 */
    {
        lcdltdc.width = lcdltdc.pwidth;
				lcddev.width = lcdltdc.width;
        lcdltdc.height = lcdltdc.pheight;
				lcddev.height = lcdltdc.height;
    }
}

/**
 * @brief       LTDC画点函数
 * @param       x,y         : 写入坐标
 * @param       color       : 颜色值
 * @retval      无
 */
void ltdc_draw_point(uint16_t x, uint16_t y, uint32_t color)
{ 
#if LTDC_PIXFORMAT == LTDC_PIXFORMAT_ARGB8888 || LTDC_PIXFORMAT == LTDC_PIXFORMAT_RGB888
    if (lcdltdc.dir)   /* 横屏 */
    {
        *(uint32_t *)((uint32_t)g_ltdc_framebuf[lcdltdc.activelayer] + lcdltdc.pixsize * (lcdltdc.pwidth * y + x)) = color;
    }
    else               /* 竖屏 */
    {
        *(uint32_t *)((uint32_t)g_ltdc_framebuf[lcdltdc.activelayer] + lcdltdc.pixsize * (lcdltdc.pwidth * (lcdltdc.pheight - x - 1) + y)) = color; 
    }
#else
   // if (lcdltdc.dir)   /* 横屏 */
   // {
        *(uint16_t *)((uint32_t)g_ltdc_framebuf[lcdltdc.activelayer] + lcdltdc.pixsize * (lcdltdc.pwidth * y + x)) = color;
   // }
   // else              /* 竖屏 */
   // {
    //    *(uint16_t *)((uint32_t)g_ltdc_framebuf[lcdltdc.activelayer] + lcdltdc.pixsize * (lcdltdc.pwidth * (lcdltdc.pheight - x - 1) + y)) = color; 
   // }
#endif
}
 #define LV_FIND_MIN(a,b) (a < b ? a : b)
/**
 * @brief       LTDC填充矩形,DMA2D填充
 *  @note       (sx,sy),(ex,ey):填充矩形对角坐标,区域大小为:(ex - sx + 1) * (ey - sy + 1)
 *              注意:sx,ex,不能大于lcddev.width - 1; sy,ey,不能大于lcddev.height - 1
 * @param       sx,sy       : 起始坐标
 * @param       ex,ey       : 结束坐标
 * @param       color       : 填充的颜色
 * @retval      无
 */
void ltdc_fill(uint16_t sx, uint16_t sy, uint16_t ex, uint16_t ey, uint32_t color)
{ 
	
	#if 0
    uint32_t psx, psy, pex, pey;   /* 以LCD面板为基准的坐标系,不随横竖屏变化而变化 */
    uint32_t timeout = 0; 
    uint16_t offline;
    uint32_t addr;
  
		psx = sx;
		psy = sy;
		pex = ex;
		pey = ey;
    
    offline = lcdltdc.pwidth - (pex - psx + 1);
    addr = ((uint32_t)g_ltdc_framebuf[lcdltdc.activelayer] + lcdltdc.pixsize * (lcdltdc.pwidth * psy + psx));

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
		#else
		uint16_t fillw,fillh;
		uint16_t x,y,i,j;
		fillw=((ex-sx)>0)?(ex-sx+1):(sx-ex + 1);
		fillh=((ey-sy)>0)?(ey-sy+1):(sy - ey + 1);
		x= 0;//LV_FIND_MIN(sx,ex);
		y = 0;//LV_FIND_MIN(sy,ey);
		
		for(i=0;i<800 ;i ++)
		{
				for(j =0 ;j< 480 ;j ++)
				{
					ltdc_draw_point(j,i,color);
					//color ++;
				}
		}
		#endif
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
		
#if 1
    uint32_t psx, psy, pex, pey;   /* 以LCD面板为基准的坐标系,不随横竖屏变化而变化 */
    uint32_t timeout = 0; 
    uint16_t offline;
    uint32_t addr;
  
		psx = sx;
		psy = sy;
		pex = ex;
		pey = ey;
    
    offline = lcdltdc.pwidth - (pex - psx + 1);
    addr = ((uint32_t)g_ltdc_framebuf[lcdltdc.activelayer] + lcdltdc.pixsize * (lcdltdc.pwidth * psy + psx));

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
#else
    uint16_t fillw,fillh;
		uint16_t x,y,i,j;
		fillw=((ex-sx)>0)?(ex-sx+1):(sx-ex + 1);
		fillh=((ey-sy)>0)?(ey-sy+1):(sy - ey + 1);
		x= LV_FIND_MIN(sx,ex);
		y = LV_FIND_MIN(sy,ey);
		
		for(i=y;i<y+ fillh ;i ++)
		{
				for(j =x ;j<x+ fillw ;j ++)
				{
					ltdc_draw_point(j,i,(uint16_t)*(color));
					color ++;
				}
		}
#endif
}  

/**
 * @brief       LTCD清屏
 * @param       color          : 颜色值
 * @retval      无
 */
void ltdc_clear(uint32_t color)
{
    ltdc_fill(0, 0, lcdltdc.width - 1, lcdltdc.height - 1, color);
}

/**
 * @brief       LTDC层窗口设置, 窗口以LCD面板坐标系为基准
 * @note        此函数必须在ltdc_layer_parameter_config之后再设置.另外,当设置的窗口值不等于面板的尺
 *              寸时,GRAM的操作(读/写点函数),也要根据窗口的宽高来进行修改,否则显示不正常(本例程就未做修改).
 * @param       layerx      : 0,第一层; 1,第二层;
 * @param       sx, sy      : 起始坐标
 * @param       width,height: 宽度和高度
 * @retval      无
 */
void ltdc_layer_window_config(uint8_t layerx, uint16_t sx, uint16_t sy, uint16_t width, uint16_t height)
{
    HAL_LTDC_SetWindowPosition(&hltdc, sx, sy, layerx);   /* 设置窗口的位置 */
    HAL_LTDC_SetWindowSize(&hltdc, width, height, layerx);/* 设置窗口大小 */
}

/**
 * @brief       LTDC初始化函数
 * @param       无
 * @retval      无
 */
void ltdc_init(void)
{
		lcdltdc.pwidth = 480;
	  lcdltdc.pheight = 800;
    lcddev.width = lcdltdc.pwidth;      /* 设置lcddev的宽度参数 */
    lcddev.height = lcdltdc.pheight;    /* 设置lcddev的宽度参数 */
    
#if LTDC_PIXFORMAT == LTDC_PIXFORMAT_ARGB8888 || LTDC_PIXFORMAT == LTDC_PIXFORMAT_RGB888 
    g_ltdc_framebuf[0] = (uint32_t*) &ltdc_lcd_framebuf;
    lcdltdc.pixsize = 4;                        /* 每个像素占4个字节 */
#else
    g_ltdc_framebuf[0] = (uint32_t*)&ltdc_lcd_framebuf;
//  g_ltdc_framebuf[1] = (uint32_t*)&ltdc_lcd_framebuf1;
    lcdltdc.pixsize = 2;                        /* 每个像素占2个字节 */
#endif 
    /* 层配置 */
    ltdc_layer_window_config(0, 0, 0, lcdltdc.pwidth, lcdltdc.pheight);                                  /* 层窗口配置,以LCD面板坐标系为基准,不要随便修改! */
//	ltdc_layer_window_config(1,0,0,lcdltdc.pwidth,lcdltdc.pheight);                                    /* 层窗口配置,以LCD面板坐标系为基准,不要随便修改! */
    ltdc_select_layer(0);                 /* 选择第1层 */
//    LTDC_BL(1);                           /* 点亮背光 */
    ltdc_clear(0XFFFFFFFF);               /* 清屏 */
}
