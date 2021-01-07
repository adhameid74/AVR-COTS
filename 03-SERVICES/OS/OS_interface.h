/**
 * @file OS_interface.h
 * @author Adham Eid (adhameid0@gmail.com)
 * @brief 
 * @version 1.0
 * @date 06-01-2021
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#ifndef OS_INTERFACE_H_
#define OS_INTERFACE_H_

/**
 * @brief Initilizes the OS
 * 
 */
void OS_voidStart();

/**
 * @brief Creates a task in the OS
 * 
 * @param Copy_u16Periodicity the periodicity of the task
 * @param Copy_u16Priority the priority of the task
 * @param Copy_pvFunc the function of the task
 */
void OS_voidCreateTask(u16 Copy_u16Periodicity, u16 Copy_u16Priority, void (*Copy_pvFunc)(void));

/**
 * @brief The schedular that handles the tasks
 * 
 */
void OS_voidSchedular();

#endif
