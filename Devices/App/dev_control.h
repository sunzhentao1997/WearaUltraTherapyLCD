#ifndef __DEV_CONTROL_H
#define __DEV_CONTROL_H


typedef enum
{
		IDLE_STATE,			//空闲
		PASUE_STATE,		//挂起
		CHARGE_STATE,		//充电
		WORK_STATE,			//工作
		CLOSE_STATE,		//关机
}Dev_Work_State;

void DevSystem_Init(void);



#endif
