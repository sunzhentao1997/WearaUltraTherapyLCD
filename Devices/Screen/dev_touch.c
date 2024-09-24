#include "dev_touch.h"
#include "dev_ltdc.h"
#include "dev_malloc.h"
#include <stdlib.h>

_m_tp_dev tp_dev =
{
    tp_init,
    NULL,
    NULL,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
};

/**
 * @brief       触摸屏初始化
 * @param       无
 * @retval      0,没有进行校准
 *              1,进行过校准
 */
uint8_t tp_init(void)
{
    tp_dev.touchtype = 0;                                                                           /* 默认设置(电阻屏 & 竖屏) */
    tp_dev.touchtype |= lcdltdc.dir & 0X01;                                                          /* 根据LCD判定是横屏还是竖屏 */

		if (gt9xxx_init() == 0) /* 初始化GT系列触摸屏成功,即当前3.5寸屏为电容触摸屏 */
		{
				tp_dev.scan = gt9xxx_scan;  /* 扫描函数指向GT9147触摸屏扫描 */
				tp_dev.touchtype |= 0X80;   /* 电容屏 */
				return 0;
		}
    
    return 1;
}
