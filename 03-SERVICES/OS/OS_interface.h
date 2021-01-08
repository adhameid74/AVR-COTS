/**
 * @file OS_interface.h
 * @author Adham Eid (adhameid0@gmail.com)
 * @brief 
 * @version 1.1
 * @date 07-01-2021
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#ifndef OS_INTERFACE_H_
#define OS_INTERFACE_H_

/**
 * @brief Initialzes the timer related to the OS
 * 
 */
void OS_voidStart();

/**
 * @brief Creates a task in the OS
 * 
 * @param Copy_u16Periodicity Periodicity of the task
 * @param Copy_u16Priority Priority of the task
 * @param Copy_pvFunc The function of the task (pointer)
 * @param Copy_u16FirstDelay First Delay of the task (selected to optimize the CPU load)
 */
void OS_voidCreateTask(u16 Copy_u16Periodicity, u16 Copy_u16Priority, void (*Copy_pvFunc)(void), u16 Copy_u16FirstDelay);

/**
 * @brief Puts the task in the suspend mode
 * 
 * @param Copy_u16Priority The task priority
 */
void OS_voidSuspendTask(u16 Copy_u16Priority);

/**
 * @brief Puts the task in the available mode
 * 
 * @param Copy_u16Priority The task priority
 */
void OS_voidResumeTask(u16 Copy_u16Priority);

/**
 * @brief Deletes the task and make its position (priority) available to associate a new task with
 * 
 * @param Copy_u16Priority The task priority
 */
void OS_voidDeleteTask(u16 Copy_u16Priority);

/**
 * @brief The schedular which is responsible of handling tasks
 * 
 */
void OS_voidSchedular();

#endif
