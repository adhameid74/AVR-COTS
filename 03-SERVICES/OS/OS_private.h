/**
 * @file OS_private.h
 * @author Adham Eid (adhameid0@gmail.com)
 * @brief 
 * @version 1.0
 * @date 06-01-2021
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#ifndef OS_PRIVATE_H_
#define OS_PRIVATE_H_

typedef struct
{
	u16 periodicity;
	void (*TaskFunc)(void);
}TASK_t;

#endif
