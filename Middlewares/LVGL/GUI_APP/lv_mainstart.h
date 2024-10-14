#ifndef __LV_MAINSTART_H
#define __LV_MAINSTART_H

typedef enum
{
	READY,
	STOP,
	WORK,
}SCREENSTATE;

void lv_mainstart(void);
void ScreenFunc(void);

#endif
