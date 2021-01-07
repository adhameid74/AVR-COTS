/**
 * @file OS_config.h
 * @author Adham Eid (adhameid0@gmail.com)
 * @brief 
 * @version 1.0
 * @date 06-01-2021
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "OS_interface.h"
#include "OS_private.h"
#include "OS_config.h"

TASK_t TASKS[TASKS_NUM];

void OS_voidStart()
{
	Timer0_voidSetCallBack(&OS_voidSchedular);
	Timer0_voidInit();
}

void OS_voidCreateTask(u16 Copy_u16Periodicity, u16 Copy_u16Priority, void (*Copy_pvFunc)(void))
{
	TASKS[Copy_u16Priority].periodicity = Copy_u16Periodicity;
	TASKS[Copy_u16Priority].TaskFunc = Copy_pvFunc;
}

void OS_voidSchedular()
{
	u8 Local_u8TasksCounter;
	static u8 Local_u8TicksCounter;
	for(Local_u8TasksCounter=0;Local_u8TasksCounter<TASKS_NUM;Local_u8TasksCounter++)
	{
		if(Local_u8TicksCounter%TASKS[Local_u8TasksCounter].periodicity == 0)
		{
			TASKS[Local_u8TasksCounter].TaskFunc();
		}
	}
}
