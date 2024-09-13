#include "touch.h"
#include "gt911.h"
#include "ltdc.h"

_m_tp_dev tp_dev =
{
    touch_init,
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

uint8_t touch_init(void)
{
		tp_dev.touchtype = 0;                                                                           /* 默认设置(电阻屏 & 竖屏) */
    tp_dev.touchtype |= lcddev.dir & 0X01;        
	
		if (gt911_init() == 0) /* 初始化GT系列触摸屏成功,即当前3.5寸屏为电容触摸屏 */
		{
				tp_dev.scan = gt911_scan;    /* 扫描函数指向GT911触摸屏扫描 */
				tp_dev.touchtype |= 0X80;    /* 电容屏 */
				return 0;
		}
		return 1;
}
