#ifndef __SENSOR_H__
#define __SENSOR_H__
#include "platform_config.h"
#define ADC1_DR_Address    ((uint32_t)0x4001244C)
#define F_SENSOR 0
#define FL_SENSOR 1
#define FR_SENSOR 2
#define L_SENSOR 4
#define R_SENSOR 5
#define VAT_SENSOR 3

#define IRSENSOR_ON() GPIO_SetBits(GPIOA, GPIO_Pin_8), GPIO_SetBits(GPIOC, GPIO_Pin_15)
#define IRSENSOR_OFF() GPIO_ResetBits(GPIOA, GPIO_Pin_8), GPIO_ResetBits(GPIOC, GPIO_Pin_15)

#define BLOCKSPEED 1
#define SENSORLEVEL1 3400
#define SENSORLEVEL2 3200
#define SENSORLEVEL3 3000
#define BLOCKSENSORDETECT 300
#define SENSORLEVELAFTERTURN 3000
#define GOALINSENSORVALUE 2000

#define SENSOROFFSETFR 100
#define SENSOROFFSETR 0
#define SENSOROFFSETFL 100
#define SENSOROFFSETL 0
#define SENSOROFFSETF 0
#define SENSORBASE 0
#define SENSORDIFFN (SENSORBASE-30)
#define SENSORDIFFP (SENSORBASE+30)


uint16_t GetSensorValue(int sensor);
int IsSensorCheck(int sensor, int sensorlevel);
void IRSensor_Init(uint32_t *data);
uint16_t GetSensorValueReal(int sensor);
uint16_t GetNewSensorValue(int sensor);
extern uint16_t F_Sensor;
extern void Battery_Check(char id);
extern void IRSensor_DataRead(void);
extern void IRSensor_DataWrite(void);
extern void IRSensor_Calibration(int mm);
extern void IRSensor_CalibrationF(void);
#endif

