#ifndef SSD_INTERFACE_H_
#define SSD_INTERFACE_H_

#define SSD_u8_COMMON_ANODE			1
#define SSD_u8_COMMON_CATHODE		0

typedef struct
{
	u8 SSD_PORT;
	u8 SSD_MODE;
	u8 SSD_ENABLE_PORT;
	u8 SSD_ENABLE_PIN;
} SSD_t;

void SSD_voidDisplayNumber(SSD_t* SSD, u8 Copy_u8Number);
void SSD_voidDisplayPattern(SSD_t* SSD, u8 Copy_u8Pattern);

#endif
