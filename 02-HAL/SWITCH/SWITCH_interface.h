#ifndef SWITCH_INTERFACE_H_
#define SWITCH_INTERFACE_H_

#define SWITCH_u8_PRESSED			1
#define SWITCH_u8_NOT_PRESSED		0

#define SWITCH_u8_ACTIVE_HIGH		1
#define SWITCH_u8_ACTIVE_LOW		0

typedef struct
{
	u8 PORT;
	u8 PIN;
	u8 ACTIVE_STATE;
} SWITCH_t;

u8 SWITCH_u8IsPressed(SWITCH_t* SWITCH);

#endif
