#ifndef START_TASK_H
#define START_TASK_H

#include "main.h"

/*  根据创建的任务列举Task Handle */
enum TASK_LIST
{
    CPU_TASK,
    CHASSIS_TASK,
	GIMBAL_TASK,
    TASK_NUM,
};


void CPU_task(void *pvParameters);
void startTast(void);

#endif
