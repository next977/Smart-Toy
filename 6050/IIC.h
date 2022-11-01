#ifndef ___IIC_H
#define ___IIC_H
//#include "sys.h"

//#include "define.h"
#include "stm32f10x.h"

//typedef u8 char;
//
//#define false    0
//#define	true     1

#define CLI()      __set_PRIMASK(1)  
#define SEI()      __set_PRIMASK(0)

#define BYTE0(dwTemp)       (*(char *)(&dwTemp))
#define BYTE1(dwTemp)       (*((char *)(&dwTemp) + 1))
#define BYTE2(dwTemp)       (*((char *)(&dwTemp) + 2))
#define BYTE3(dwTemp)       (*((char *)(&dwTemp) + 3))

#define true 1
#define false 0 
#define   u8  u8

#define TRUE  0
#define FALSE -1


///////////////////////////////////////////////////////////////
//位带操作,实现51类似的GPIO控制功能
//具体实现思想,参考<<CM3权威指南>>第五章(87页~92页).
//IO口操作宏定义
#define BITBAND(addr, bitnum) ((addr & 0xF0000000)+0x2000000+((addr &0xFFFFF)<<5)+(bitnum<<2)) 
#define MEM_ADDR(addr)  *((volatile unsigned long  *)(addr)) 
#define BIT_ADDR(addr, bitnum)   MEM_ADDR(BITBAND(addr, bitnum)) 
//IO口地址映射
#define GPIOA_ODR_Addr    (GPIOA_BASE+12) //0x4001080C 
#define GPIOB_ODR_Addr    (GPIOB_BASE+12) //0x40010C0C 
#define GPIOC_ODR_Addr    (GPIOC_BASE+12) //0x4001100C 
#define GPIOD_ODR_Addr    (GPIOD_BASE+12) //0x4001140C 
#define GPIOE_ODR_Addr    (GPIOE_BASE+12) //0x4001180C 
#define GPIOF_ODR_Addr    (GPIOF_BASE+12) //0x40011A0C    
#define GPIOG_ODR_Addr    (GPIOG_BASE+12) //0x40011E0C    

#define GPIOA_IDR_Addr    (GPIOA_BASE+8) //0x40010808 
#define GPIOB_IDR_Addr    (GPIOB_BASE+8) //0x40010C08 
#define GPIOC_IDR_Addr    (GPIOC_BASE+8) //0x40011008 
#define GPIOD_IDR_Addr    (GPIOD_BASE+8) //0x40011408 
#define GPIOE_IDR_Addr    (GPIOE_BASE+8) //0x40011808 
#define GPIOF_IDR_Addr    (GPIOF_BASE+8) //0x40011A08 
#define GPIOG_IDR_Addr    (GPIOG_BASE+8) //0x40011E08 
 
//IO口操作,只对单一的IO口!
//确保n的值小于16!
#define PAout(n)   BIT_ADDR(GPIOA_ODR_Addr,n)  //输出 
#define PAin(n)    BIT_ADDR(GPIOA_IDR_Addr,n)  //输入 

#define PBout(n)   BIT_ADDR(GPIOB_ODR_Addr,n)  //输出 
#define PBin(n)    BIT_ADDR(GPIOB_IDR_Addr,n)  //输入 

#define PCout(n)   BIT_ADDR(GPIOC_ODR_Addr,n)  //输出 
#define PCin(n)    BIT_ADDR(GPIOC_IDR_Addr,n)  //输入 

#define PDout(n)   BIT_ADDR(GPIOD_ODR_Addr,n)  //输出 
#define PDin(n)    BIT_ADDR(GPIOD_IDR_Addr,n)  //输入 

#define PEout(n)   BIT_ADDR(GPIOE_ODR_Addr,n)  //输出 
#define PEin(n)    BIT_ADDR(GPIOE_IDR_Addr,n)  //输入

#define PFout(n)   BIT_ADDR(GPIOF_ODR_Addr,n)  //输出 
#define PFin(n)    BIT_ADDR(GPIOF_IDR_Addr,n)  //输入

#define PGout(n)   BIT_ADDR(GPIOG_ODR_Addr,n)  //输出 
#define PGin(n)    BIT_ADDR(GPIOG_IDR_Addr,n)  //输入
/////////////////////////////////////////////////////////////////
/*
#define MPU6050_READRATE			1000	//6050读取频率
#define MPU6050_READTIME			0.001	//6050读取时间间隔
#define EE_6050_ACC_X_OFFSET_ADDR	0
#define EE_6050_ACC_Y_OFFSET_ADDR	1
#define EE_6050_ACC_Z_OFFSET_ADDR	2
#define EE_6050_GYRO_X_OFFSET_ADDR	3
#define EE_6050_GYRO_Y_OFFSET_ADDR	4
#define EE_6050_GYRO_Z_OFFSET_ADDR	5
*/
//0表示写
#ifndef I2C_Direction_Transmitter
#define	I2C_Direction_Transmitter   0
#endif
//１表示读
#ifndef I2C_Direction_Receiver
#define	I2C_Direction_Receiver      1	 
#endif


/*====================================================================================================*/
/*====================================================================================================*/
u8 i2cWriteBuffer(u8 addr_, u8 reg_, u8 len_, u8 *data);
u8 i2cWrite(u8 addr_, u8 reg_, u8 data);
u8 i2cRead(u8 addr_, u8 reg_, u8 len, u8* buf);
void i2cInit(void);
u16 i2cGetErrorCounter(void);
static void i2cUnstick(void);

int i2cwrite(u8 addr, u8 reg, u8 len, u8 * data);
int i2cread(u8 addr, u8 reg, u8 len, u8 *buf);



/*====================================================================================================*/
/*====================================================================================================*/
#endif
