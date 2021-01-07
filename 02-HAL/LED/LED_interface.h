#ifndef LED_INTERFACE_H_
#define LED_INTERFACE_H_

#define LED_u8_ACTIVE_HIGH		1
#define LED_u8_ACTIVE_LOW		0

typedef struct
{
	u8 LED_PORT;
	u8 LED_PIN;
	u8 LED_ACTIVE_STATE;
} LED_t;

void LED_voidOn(LED_t* LED);
void LED_voidOff(LED_t* LED);

#endif
