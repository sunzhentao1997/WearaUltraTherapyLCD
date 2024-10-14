#include "lv_mainstart.h"
#include "gui_guider.h"
#include "events_init.h"
#include "lvgl.h"

#include <stdio.h>

lv_ui guider_ui;
SCREENSTATE ScreenState = READY;
int16_t SliderVal = 1800;
char timebuf[] = "30:00";

uint32_t ScreenCount;

void lv_mainstart(void)
{
    setup_ui(&guider_ui);
   	events_init(&guider_ui);
}

static void get_time_buff(void)
{
		timebuf[0] = (char)(SliderVal / 60 / 10 + 0x30); 
		timebuf[1] = (char)(SliderVal / 60 % 10 + 0x30); 
		timebuf[3] = (char)(SliderVal % 60 / 10 + 0x30); 
		timebuf[4] = (char)(SliderVal % 10 + 0x30); 
}

void ScreenFunc(void)
{
		if(ScreenState == WORK)
		{
			  if(ScreenCount >= 1000)
				{
					SliderVal--;
					if(SliderVal < 0)
					{
						SliderVal = 0;
						ScreenState = STOP;
					}
					get_time_buff();
					lv_arc_set_value(guider_ui.main_arc_1, SliderVal);
					lv_label_set_text(guider_ui.main_label_2, timebuf);
					ScreenCount = 0;
				}
		}else if(ScreenState == READY)
		{
				if(ScreenCount >= 1000)
				{
					SliderVal = 1800;
					memcpy(timebuf,"30:00",5);
					lv_arc_set_value(guider_ui.main_arc_1, SliderVal);
					lv_label_set_text(guider_ui.main_label_2, timebuf);
					ScreenCount = 0;
				}
		}else if(ScreenState == STOP)
		{
				if(ScreenCount >= 1000)
				{
					SliderVal = 0;
					memcpy(timebuf,"00:00",5);
					lv_label_set_text(guider_ui.main_label_3, "治疗已完成 ");
					lv_arc_set_value(guider_ui.main_arc_1, SliderVal);
					lv_label_set_text(guider_ui.main_label_2, timebuf);
					ScreenCount = 0;
				}
		}else
		{
		}
}
