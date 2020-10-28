#ifndef __LED_H
#define __LED_H	 
#include "sys.h"
	   
typedef struct
{
     u16 LedonTime;
	 u16 LedoffTime;
	 u8  LedStatus;
	 u32 LedTick;
	 u32 BlinkTick;
	 u32* LedGPIO; 
}BLINK_PARA;

#define LED_STATUS_INIT   0
#define LED_STATUS_ON     2
#define LED_STATUS_OFF    3
//LED¶Ë¿Ú¶¨Òå
//#define LED1           PBout(3)
//#define LED2           PBout(1)
#define LED1           PAout(6)
#define LED2           PAout(6)
#define LED3           PAout(6)
void LED_Init(void);
void _LED_TASK10MS(void);
void _LED_SetTime(u8 Lednum,u16 Ontime,u16 Offtime,u16 Blinktime);

#endif


















