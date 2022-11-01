

#ifndef __FLASH_H__
#define __FLASH_H__
#include "platform_config.h"





typedef struct
{
	uint8_t gamestartdate[8]; //게임 시작 날짜
	uint8_t gamestarttime[4]; // 게임 시작 시간
	uint8_t studentID[10]; //학생 아이디
	uint8_t flag[2];
	uint8_t gameruntime[4]; //진행 시간(초)
	uint8_t gameblockcount[3];//블럭 갯수
	uint8_t blank; //패딩용
}s_blockgamedata;


typedef struct
{
	uint16_t blank; //패딩용
	uint16_t f_sensor; //블럭 인식 거리
	uint16_t fl_sensortable[18]; //왼쪽 앞 센서
	uint16_t l_sensortable[18]; //왼쪽 뒤 센서
	uint16_t fr_sensortable[18]; //오른쪽 앞 센서
	uint16_t r_sensortable[18]; //오른쪽 뒤 센서
	
}s_sensordata;


typedef struct
{
	
	uint16_t motorlevelL[MOTOR_MAX_LEVEL+1];
	uint16_t motorlevelR[MOTOR_MAX_LEVEL+1];
	uint16_t BmotorlevelL[MOTOR_MAX_LEVEL+1];
	uint16_t BmotorlevelR[MOTOR_MAX_LEVEL+1];
	
}s_motordata; // 모터 레벨에 따른 PWM 듀티 값 (0~24000)

typedef struct
{
	
	int16_t gyro_x_offset;
	int16_t gyro_y_offset;
	int16_t gyro_z_offset;
	int16_t accel_x_offset;
	int16_t accel_y_offset;
	int16_t accel_z_offset;
	
}s_gyrodata;//자이로 초기화 값


typedef struct
{
	uint32_t Isbgdata;
	uint32_t Issdata;
	uint32_t Ismdata;
	uint32_t Isgdata;
	uint32_t Isbluetoothdata;
	s_blockgamedata bgdata[10];
	s_sensordata sdata;
	s_motordata mdata;
	s_gyrodata gdata;
	char SerialNumber[15];	
}age1000_data;

typedef union
{
	
	age1000_data agedata;
	uint32_t flashdata[256];
	
}age1000_flash_data;

extern age1000_flash_data afdata;






extern void Flash_write(void);
extern void Flash_read(void);
extern void AGE_Data_Init(void);




#endif //__FLASH_H__
