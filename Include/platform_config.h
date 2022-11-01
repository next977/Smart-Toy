
#ifndef __PLATFORM_CONFIG_H
#define __PLATFORM_CONFIG_H


typedef enum{ false, true} bool ;

#include "stm32f10x.h"
#include "stm32f10x_it.h"
#include "melody.h"
#include "MCUSettings.h"
#include "button.h"
#include "miscellaneous.h"
#include "bluetooth.h"
#include "mpu9150.h"
#include "motor.h"
#include "flash.h"
#include "gyro.h"
#include "led.h"
#include "blockgame.h"
#include "sensor.h"


#include <stdio.h>

#define DEBUG

#ifdef DEBUG
#define DPRINTF(fmt,args,...) printf( "%s:%s:%d: " fmt, __FILE__,  __FUNCTION__, __LINE__, ##args)
#else
#define DPRINTF
#endif


#define GAMEMODE_NONE 0
#define GAMEMODE_BLOCKGAME 1
#define GAMEMODE_MULTIMODE 2

#define BLOCKGAMEMODE_NONE 0
#define BLOCKGAMEMODE_READY 1
#define BLOCKGAMEMODE_RUN 2
#define BLOCKGAMEMODE_GOALIN 3
#define BLOCKGAMEMODE_ERROR 4

#define TEAMCOLOR_NOTHING 0
#define TEAMCOLOR_RED 1
#define TEAMCOLOR_GREEN 2
#define TEAMCOLOR_BLUE 3

extern uint32_t delay_time;
extern uint32_t button_time;
extern uint8_t Game_Mode;
extern uint8_t Team_Color;
extern uint8_t Block_Game_Mode;
#endif /* __PLATFORM_CONFIG_H */


