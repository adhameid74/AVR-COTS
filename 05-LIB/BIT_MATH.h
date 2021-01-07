#ifndef BIT_MATH_H_
#define BIT_MATH_H_

#define SET_BIT(VAR,BIT_NB) (VAR)|=(1<<(BIT_NB))
#define CLR_BIT(VAR,BIT_NB) (VAR)&=~(1<<(BIT_NB))
#define TOGGLE_BIT(VAR,BIT_NB) (VAR)^=(1<<(BIT_NB))
#define GET_BIT(VAR,BIT_NB) ((VAR>>BIT_NB)&0x01)


#endif
