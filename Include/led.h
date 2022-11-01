#ifndef __LED_H__
#define __LED_H__
#include "platform_config.h"

#define LED_LEFT 1
#define LED_RIGHT 2

#define RED 0x01
#define GREEN 0x02
#define BLUE 0x04


extern bool ledAction;
extern void Led_Action(uint8_t * ledAction);
extern void LED_Control(uint8_t side, uint8_t rgb);
extern uint32_t ledtime;
#endif // __LED_H__


