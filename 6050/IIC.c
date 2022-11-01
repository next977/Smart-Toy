#include "IIC.h"

//�޸Ĳ���
#define SCL  PBout(6)    	//   GPIOE->BSRR = GPIO_Pin_8 /* GPIO_SetBits(GPIOB , GPIO_Pin_10)   */

#define SDA  PBout(7)		//   GPIOE->BSRR = GPIO_Pin_9 /* GPIO_SetBits(GPIOB , GPIO_Pin_11)   */

#define SDA_read  PBin(7)	//   GPIOE->IDR  & GPIO_Pin_9 /* GPIO_ReadInputDataBit(GPIOB , GPIO_Pin_11) */

static void I2C_delay(void)
{
    volatile int i = 7;
    while (i)
        i--;
}

static u8 I2C_Start(void)
{
    SDA=1;
    SCL=1;
    I2C_delay();
    if (!SDA_read)
        return false;
    SDA=0;
    I2C_delay();
    if (SDA_read)
        return false;
    SDA=0;
    I2C_delay();
    return true;
}

static void I2C_Stop(void)
{
    SCL=0;
    I2C_delay();
    SDA=0;
    I2C_delay();
    SCL=1;
    I2C_delay();
    SDA=1;
    I2C_delay();
}

static void I2C_Ack(void)
{
    SCL=0;
    I2C_delay();
    SDA=0;
    I2C_delay();
    SCL=1;
    I2C_delay();
    SCL=0;
    I2C_delay();
}

static void I2C_NoAck(void)
{
    SCL=0;
    I2C_delay();
    SDA=1;
    I2C_delay();
    SCL=1;
    I2C_delay();
    SCL=0;
    I2C_delay();
}

static u8 I2C_WaitAck(void)
{
    SCL=0;
    I2C_delay();
    SDA=1;
    I2C_delay();
    SCL=1;
    I2C_delay();
    if (SDA_read) {
        SCL=0;
        return false;
    }
    SCL=0;
    return true;
}

static void I2C_SendByte(u8 byte)
{
    u8 i = 8;
    while (i--) {
        SCL=0;
        I2C_delay();
        if (byte & 0x80)
            SDA=1;
        else
            SDA=0;
        byte <<= 1;
        I2C_delay();
        SCL=1;
        I2C_delay();
    }
    SCL=0;
}

static u8 I2C_ReceiveByte(void)
{
    u8 i = 8;
    u8 byte = 0;

    SDA=1;
    while (i--) {
        byte <<= 1;
        SCL=0;
        I2C_delay();
        SCL=1;
        I2C_delay();
        if (SDA_read) {
            byte |= 0x01;
        }
    }
    SCL=0;
    return byte;
}

void i2cInit(void)
{
//	//�˿�Eʹ��  PE8.PE9�˿�ģʽ�趨
//	RCC->APB2ENR|=1<<6;   //ʹ��PORTE��ʱ��  
//	GPIOE->CRH&=0XFFFFFF00; 
//	GPIOE->CRH|=0X00000055;//IO״̬����

	//�˿�Bʹ��  PB10.PB11�˿�ģʽ�趨
	RCC->APB2ENR|=1<<3;   //ʹ��PORTE��ʱ��  
	GPIOB->CRH&=0XFFFF00FF; 
	GPIOB->CRH|=0X00005500;//IO״̬����

}

u8 i2cWriteBuffer(u8 addr, u8 reg, u8 len, u8 * data)
{
    int i;
    if (!I2C_Start())
        return false;
    I2C_SendByte(addr << 1 | I2C_Direction_Transmitter);
    if (!I2C_WaitAck()) {
        I2C_Stop();
        return false;
    }
    I2C_SendByte(reg);
    I2C_WaitAck();
    for (i = 0; i < len; i++) {
        I2C_SendByte(data[i]);
        if (!I2C_WaitAck()) {
            I2C_Stop();
            return false;
        }
    }
    I2C_Stop();
    return true;
}
/////////////////////////////////////////////////////////////////////////////////
int i2cwrite(u8 addr, u8 reg, u8 len, u8 * data)
{
	if(i2cWriteBuffer(addr,reg,len,data))
	{
		return TRUE;
	}
	else
	{
		return FALSE;
	}
	//return FALSE;
}
int i2cread(u8 addr, u8 reg, u8 len, u8 *buf)
{
	if(i2cRead(addr,reg,len,buf))
	{
		return TRUE;
	}
	else
	{
		return FALSE;
	}
	//return FALSE;
}
//////////////////////////////////////////////////////////////////////////////////
u8 i2cWrite(u8 addr, u8 reg, u8 data)
{
    if (!I2C_Start())
        return false;
    I2C_SendByte(addr << 1 | I2C_Direction_Transmitter);
    if (!I2C_WaitAck()) {
        I2C_Stop();
        return false;
    }
    I2C_SendByte(reg);
    I2C_WaitAck();
    I2C_SendByte(data);
    I2C_WaitAck();
    I2C_Stop();
    return true;
}

u8 i2cRead(u8 addr, u8 reg, u8 len, u8 *buf)
{
    if (!I2C_Start())
        return false;
    I2C_SendByte(addr << 1 | I2C_Direction_Transmitter);
    if (!I2C_WaitAck()) {
        I2C_Stop();
        return false;
    }
    I2C_SendByte(reg);
    I2C_WaitAck();
    I2C_Start();
    I2C_SendByte(addr << 1 | I2C_Direction_Receiver);
    I2C_WaitAck();
    while (len) {
        *buf = I2C_ReceiveByte();
        if (len == 1)
            I2C_NoAck();
        else
            I2C_Ack();
        buf++;
        len--;
    }
    I2C_Stop();
    return true;
}

u16 i2cGetErrorCounter(void)
{
    // TODO maybe fix this, but since this is test code, doesn't matter.
    return 0;
}


