#ifndef __GYRO_H__
#define __GYRO_H__
#include "platform_config.h"

extern uint32_t gyro_time;
extern bool gyroAction;
extern int16_t GetGyroValue(void);
extern void Gyro_Action(uint8_t * gyroAction);

#endif
