#ifndef __BLOCKGAME_H
#define __BLOCKGAME_H
#include "platform_config.h"

//typedef enum
//{BGM_Nothing, BGM_JeonJin, BGM_BlockDetect, BGM_WhatDirection, BGM_FistDistance, BGM_ExcuteDirection, BGM_SecondDistance, BGM_FirstBack, BGM_SecondBack, BGM_Parallel }BlockGameMode;


#define D_LEFT 1
#define D_RIGHT 0
extern uint32_t hoojintime;
extern uint32_t gametime;
extern uint32_t blockGameTime;
extern uint32_t blockGameBlockCount;
extern bool blockGameAction;
extern void BlockGame_Action(uint8_t * bgameAction);
extern void BlockGameReady(void);
extern void BlockGameStart(void);
extern void BlockGameStop(void);
extern void BlockGameResult(void);
	
extern void BGM_Nothing(void);
extern void BGM_JeonJin(void);
extern void BGM_BlockDetect(void);
extern void BGM_GoalInCheck(void);
extern void BGM_WhatDirection(void);
extern void BGM_FistDistance(void);
extern void BGM_ExcuteDirection(void);
extern void BGM_DirectionStop(void);
extern void BGM_SecondDistance(void);
extern void BGM_Back(void);
extern void BGM_BackStop(void);
extern void BGM_Parallel(void);


extern void Data_save(void);
extern void Data_send(void);

#endif
