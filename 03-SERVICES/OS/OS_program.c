/**
 * @file OS_config.h
 * @author Adham Eid (adhameid0@gmail.com)
 * @brief 
 * @version 1.1
 * @date 07-01-2021
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "OS_interface.h"
#include "OS_private.h"
#include "OS_config.h"

TASK_t TASKS[TASKS_NUM] = {{NULL}};

void OS_voidStart()
{
	// set timer call back to OS_voidSchedular
	// Init timer
}

void OS_voidCreateTask(u16 Copy_u16Periodicity, u16 Copy_u16Priority, void (*Copy_pvFunc)(void), u16 Copy_u16FirstDelay)
{
	if(TASKS[Copy_u16Priority].TaskFunc == NULL)
	{
		TASKS[Copy_u16Priority].Periodicity = Copy_u16Periodicity;
		TASKS[Copy_u16Priority].TaskFunc = Copy_pvFunc;
		TASKS[Copy_u16Priority].FirstDelay = Copy_u16FirstDelay;
		TASKS[Copy_u16Priority].State = AVAILABLE;
	}
}

void OS_voidSuspendTask(u16 Copy_u16Priority)
{
	TASKS[Copy_u16Priority].State = SUSPENDED;
}

void OS_voidResumeTask(u16 Copy_u16Priority)
{
	TASKS[Copy_u16Priority].State = AVAILABLE;
}

void OS_voidDeleteTask(u16 Copy_u16Priority)
{
	TASKS[Copy_u16Priority].TaskFunc = NULL;
}

void OS_voidSchedular()
{
	u8 Local_u8TasksCounter;
	for(Local_u8TasksCounter=0;Local_u8TasksCounter<TASKS_NUM;Local_u8TasksCounter++)
	{
		if( (TASKS[Local_u8TasksCounter].FirstDelay == 0) && (TASKS[Local_u8TasksCounter].TaskFunc != NULL) && (TASKS[Local_u8TasksCounter].State == AVAILABLE) )
		{
			TASKS[Local_u8TasksCounter].TaskFunc();
			TASKS[Local_u8TasksCounter].FirstDelay = TASKS[Local_u8TasksCounter].Periodicity-1;
		}
		else
		{
			TASKS[Local_u8TasksCounter].FirstDelay--;
		}
	}
}
