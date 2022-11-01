

#ifndef __MOTOR_H__
#define __MOTOR_H__

#include "platform_config.h"

#define MOTOR_ON 1
#define MOTOR_OFF 0

#define MOTORR 0
#define MOTORL 0



// Motor Configuration----------------------------------------------

#define MOTOR_SPEED_MIN_D 3500
#define MOTOR_SPEED_MAX_D 22000
#define MOTOR_SPEED_MIN_R 2500
#define MOTOR_SPEED_MAX_R 15000
#define MOTOR_MAX_LEVEL 9
#define MOTOR_SPEED_ROTATE_INSTOP 2800
#define MOTOR_SPEED_ROTATE_DIV 2
#define MOTOR_CONTROL_MAX_RANGE 1999
#define MOTOR_CONTROL_MIN_RANGE 1999
//#define BLOCKZIGZAG 5000
#define BLOCKZIGZAG 2000


//--------------------------------------------------------------------


typedef enum {STOP, JEONJIN, ROTATE, HOOJIN, ROTATESTOP, LROTATE, RROTATE} MotorState;
typedef struct
{

	MotorState mState;
	MotorState mStateRotate;
	MotorState mStateLRotate;

	
	uint16_t motorlevelL[10];
	uint16_t motorlevelR[10];
	uint16_t BmotorlevelL[10];
	uint16_t BmotorlevelR[10];
	
	
} MotorValue;









extern MotorValue mv;

extern uint16_t LSPEED;
extern uint16_t RSPEED;
extern uint16_t MOTORLEVEL;


extern void Motor_DataRead(void);


extern void Motor_DataWrite(void);

extern void vMotorCtrl(uint8_t lccw, uint16_t lspeed, uint8_t rccw, uint16_t rspeed);
extern void MotorOnOff(uint32_t OnOff);
extern void MotorRotateR(uint16_t div);
extern void MotorRotateL(uint16_t div);
extern void MotorRotateStop(void);
extern void BL_MotorRotateR(uint16_t l, uint16_t r);
extern void BL_MotorRotateL(uint16_t l, uint16_t r);
extern void MotorStop(void);
extern void MotorJeonJin(uint8_t level);
extern void MotorHooJin(uint8_t level);
extern void MotorRotateSet_D(int16_t gyrovalue);
extern void MotorRotateSet_R(int16_t gyrovalue);
extern float JeonJinPid(float gyro);


#endif //__MOTOR_H__

