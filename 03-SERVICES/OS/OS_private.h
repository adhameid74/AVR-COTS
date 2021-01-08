/**
 * @file OS_private.h
 * @author Adham Eid (adhameid0@gmail.com)
 * @brief 
 * @version 1.1
 * @date 07-01-2021
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#ifndef OS_PRIVATE_H_
#define OS_PRIVATE_H_

typedef struct
{
	u16 Periodicity;
	u16 FirstDelay;
	void (*TaskFunc)(void);
	u8 State;
}TASK_t;

#define SUSPENDED		0
#define AVAILABLE		1

#endif
