/**
 * @file BIT_MATH.h
 * @author Adham Eid (adhameid0@gmail.com)
 * @brief 
 * @version 0.1
 * @date 10-11-2020
 * 
 * @copyright Copyright (c) 2020
 * 
 */

#ifndef BIT_MATH_H_
#define BIT_MATH_H_

#define SET_BIT(REG,BIT) 	(REG)|=(1<<(BIT))
#define CLR_BIT(REG,BIT) 	(REG)&=~(1<<(BIT))
#define TOGGLE_BIT(REG,BIT) (REG)^=(1<<(BIT))
#define GET_BIT(REG,BIT) 	((REG>>BIT)&0x01)

#endif
