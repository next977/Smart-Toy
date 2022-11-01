//MPU6050 I2C library for ARM STM32F103xx Microcontrollers - Main source file
//Has bit, byte and buffer I2C R/W functions
// 23/05/2012 by Harinadha Reddy Chintalapalli <harinath.ec@gmail.com>
// Changelog:
//     2012-05-23 - initial release. Thanks to Jeff Rowberg <jeff@rowberg.net> for his AVR/Arduino
//                  based MPU6050 development which inspired me & taken as reference to develop this.
/* ============================================================================================
   MPU6050 device I2C library code for ARM STM32F103xx is placed under the MIT license
   Copyright (c) 2012 Harinadha Reddy Chintalapalli


   Permission is hereby granted, free of charge, to any person obtaining a copy
   of this software and associated documentation files (the "Software"), to deal
   in the Software without restriction, including without limitation the rights
   to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
   copies of the Software, and to permit persons to whom the Software is
   furnished to do so, subject to the following conditions:


   The above copyright notice and this permission notice shall be included in
   all copies or substantial portions of the Software.


   THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
   IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
   FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
   AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
   LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
   OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
   THE SOFTWARE.
   ================================================================================================
 */


/* Includes */
#include "mpu9150.h"
#include "platform_config.h"


int GyroOffset[3];
int GyroZOffset=0;
int GyroZOffsetSum=0;
int GyroOffset_X_Sum, GyroOffset_Y_Sum, GyroOffset_Z_Sum;
extern uint32_t gamedata [256];

__IO uint32_t I2CDirection = I2C_DIRECTION_TX;
__IO uint32_t NumbOfBytes1;
__IO uint32_t NumbOfBytes2;
__IO uint8_t Address1;

/** @defgroup MPU6050_Library
 * @{
 */


/** Power on and prepare for general usage.
 * This will activate the device and take it out of sleep mode (which must be done
 * after start-up). This function also sets both the accelerometer and the gyroscope
 * to their most sensitive settings, namely +/- 2g and +/- 250 degrees/sec, and sets
 * the clock source to use the X Gyro for reference, which is slightly better than
 * the default internal clock source. 한글.
 */
void MPU6050_Initialize(void) 
{
	
	uint8_t buffer[5];
	// AGE-1000 오면 테스트   데이터 삭제 되서 다시 만들었음.

	buffer[0] = MPU6050_RA_PWR_MGMT_1;
	buffer[1] = 0x01;
	
	I2C_Master_BufferWrite(I2C1, buffer, 2, MPU6050_DEFAULT_ADDRESS);
	
	delay_ms(4);
	
	buffer[0] = MPU6050_RA_SMPLRT_DIV;
	buffer[1] = 0x01; //MPU6050_RA_SMPLRT_DIV 
	buffer[2] = 0x01; //MPU6050_RA_CONFIG
	buffer[3] = 0x08; //MPU6050_RA_GYRO_CONFIG
	buffer[4] = 0x10; //MPU6050_RA_ACCEL_CONFIG
	
	I2C_Master_BufferWrite(I2C1, buffer, 5, MPU6050_DEFAULT_ADDRESS);

	buffer[0] = MPU6050_RA_GYRO_CONFIG;
	
	I2C_Master_BufferWrite(I2C1, buffer, 1, MPU6050_DEFAULT_ADDRESS);
	I2C_Master_BufferRead(I2C1, buffer, 2, MPU6050_DEFAULT_ADDRESS);
	
	buffer[0] = buffer[0]>>3;
	buffer[1] = buffer[1]>>3;
	DPRINTF("gyro : %d\r\n", buffer[0]);
	DPRINTF("accel : %d\r\n",buffer[1]);
	
}

void MPU6050_Initialize_straight(void) 
{

	MPU6050_WriteBits(MPU6050_DEFAULT_ADDRESS, MPU6050_RA_CONFIG , 2, 3, 0);
	delay_ms(4);
}

void MPU6050_Initialize_rotate(void) 
{

	MPU6050_WriteBits(MPU6050_DEFAULT_ADDRESS, MPU6050_RA_CONFIG , 2, 3, 6);
	delay_ms(4);
}

/** Verify the I2C connection.
 * Make sure the device is connected and responds as expected.
 * @return 1 if connection is valid, 0 otherwise
 */
int MPU6050_TestConnection(void) 
{
	if(MPU6050_GetDeviceID() == 0x34) //0b110100; 8-bit representation in hex = 0x34
		return 1;
	else
		return 0;
}
// WHO_AM_I register


/** Get Device ID.
 * This register is used to verify the identity of the device (0b110100).
 * @return Device ID (should be 0x68, 104 dec, 150 oct)
 * @see MPU6050_RA_WHO_AM_I
 * @see MPU6050_WHO_AM_I_BIT
 * @see MPU6050_WHO_AM_I_LENGTH
 */
uint8_t MPU6050_GetDeviceID(void)
{
	uint8_t tmp;
	MPU6050_ReadBits(MPU6050_DEFAULT_ADDRESS, MPU6050_RA_WHO_AM_I, MPU6050_WHO_AM_I_BIT, MPU6050_WHO_AM_I_LENGTH, &tmp);
	return tmp; 
}
/** Set clock source setting.
 * An internal 8MHz oscillator, gyroscope based clock, or external sources can
 * be selected as the MPU-60X0 clock source. When the internal 8 MHz oscillator
 * or an external source is chosen as the clock source, the MPU-60X0 can operate
 * in low power modes with the gyroscopes disabled.
 *
 * Upon power up, the MPU-60X0 clock source defaults to the internal oscillator.
 * However, it is highly recommended that the device be configured to use one of
 * the gyroscopes (or an external clock source) as the clock reference for
 * improved stability. The clock source can be selected according to the following table:
 *
 * <pre>
 * CLK_SEL | Clock Source
 * --------+--------------------------------------
 * 0       | Internal oscillator
 * 1       | PLL with X Gyro reference
 * 2       | PLL with Y Gyro reference
 * 3       | PLL with Z Gyro reference
 * 4       | PLL with external 32.768kHz reference
 * 5       | PLL with external 19.2MHz reference
 * 6       | Reserved
 * 7       | Stops the clock and keeps the timing generator in reset
 * </pre>
 *
 * @param source New clock source setting
 * @see MPU6050_GetClockSource()
 * @see MPU6050_RA_PWR_MGMT_1
 * @see MPU6050_PWR1_CLKSEL_BIT
 * @see MPU6050_PWR1_CLKSEL_LENGTH
 */
void MPU6050_SetClockSource(uint8_t source) 
{
	MPU6050_WriteBits(MPU6050_DEFAULT_ADDRESS, MPU6050_RA_PWR_MGMT_1, MPU6050_PWR1_CLKSEL_BIT, MPU6050_PWR1_CLKSEL_LENGTH, source);
	delay_ms(4);

}


/** Set full-scale gyroscope range.
 * @param range New full-scale gyroscope range value
 * @see MPU6050_GetFullScaleGyroRange()
 * @see MPU6050_GYRO_FS_250
 * @see MPU6050_RA_GYRO_CONFIG
 * @see MPU6050_GCONFIG_FS_SEL_BIT
 * @see MPU6050_GCONFIG_FS_SEL_LENGTH
 */
void MPU6050_SetFullScaleGyroRange(uint8_t range) 
{
	MPU6050_WriteBits(MPU6050_DEFAULT_ADDRESS, MPU6050_RA_GYRO_CONFIG, MPU6050_GCONFIG_FS_SEL_BIT, MPU6050_GCONFIG_FS_SEL_LENGTH, range);
	delay_ms(4);
}


// GYRO_CONFIG register


/** Get full-scale gyroscope range.
 * The FS_SEL parameter allows setting the full-scale range of the gyro sensors,
 * as described in the table below.
 *
 * <pre>
 * 0 = +/- 250 degrees/sec
 * 1 = +/- 500 degrees/sec
 * 2 = +/- 1000 degrees/sec
 * 3 = +/- 2000 degrees/sec
 * </pre>
 *
 * @return Current full-scale gyroscope range setting
 * @see MPU6050_GYRO_FS_250
 * @see MPU6050_RA_GYRO_CONFIG
 * @see MPU6050_GCONFIG_FS_SEL_BIT
 * @see MPU6050_GCONFIG_FS_SEL_LENGTH
 */
uint8_t MPU6050_GetFullScaleGyroRange(void) 
{
	uint8_t tmp;
	

	MPU6050_ReadBits(MPU6050_DEFAULT_ADDRESS, MPU6050_RA_GYRO_CONFIG, MPU6050_GCONFIG_FS_SEL_BIT, MPU6050_GCONFIG_FS_SEL_LENGTH, &tmp);
	
	return tmp;
}
/** Get full-scale accelerometer range.
 * The FS_SEL parameter allows setting the full-scale range of the accelerometer
 * sensors, as described in the table below.
 *
 * <pre>
 * 0 = +/- 2g
 * 1 = +/- 4g
 * 2 = +/- 8g
 * 3 = +/- 16g
 * </pre>
 *
 * @return Current full-scale accelerometer range setting
 * @see MPU6050_ACCEL_FS_2
 * @see MPU6050_RA_ACCEL_CONFIG
 * @see MPU6050_ACONFIG_AFS_SEL_BIT
 * @see MPU6050_ACONFIG_AFS_SEL_LENGTH
 */
uint8_t MPU6050_GetFullScaleAccelRange(void) 
{
	uint8_t tmp;
	MPU6050_ReadBits(MPU6050_DEFAULT_ADDRESS, MPU6050_RA_ACCEL_CONFIG, MPU6050_ACONFIG_AFS_SEL_BIT, MPU6050_ACONFIG_AFS_SEL_LENGTH, &tmp);
	return tmp;
}
/** Set full-scale accelerometer range.
 * @param range New full-scale accelerometer range setting
 * @see MPU6050_GetFullScaleAccelRange()
 */
void MPU6050_SetFullScaleAccelRange(uint8_t range) 
{
	MPU6050_WriteBits(MPU6050_DEFAULT_ADDRESS, MPU6050_RA_ACCEL_CONFIG, MPU6050_ACONFIG_AFS_SEL_BIT, MPU6050_ACONFIG_AFS_SEL_LENGTH, range);
	delay_ms(4);
}


/** Get sleep mode status.
 * Setting the SLEEP bit in the register puts the device into very low power
 * sleep mode. In this mode, only the serial interface and internal registers
 * remain active, allowing for a very low standby current. Clearing this bit
 * puts the device back into normal mode. To save power, the individual standby
 * selections for each of the gyros should be used if any gyro axis is not used
 * by the application.
 * @return Current sleep mode enabled status
 * @see MPU6050_RA_PWR_MGMT_1
 * @see MPU6050_PWR1_SLEEP_BIT
 */
int MPU6050_GetSleepModeStatus(void) 
{
	uint8_t tmp;
	MPU6050_ReadBit(MPU6050_DEFAULT_ADDRESS, MPU6050_RA_PWR_MGMT_1, MPU6050_PWR1_SLEEP_BIT, &tmp);
	if(tmp == 0x00)
		return 0;
	else
		return 1;    
}
/** Set sleep mode status.
 * @param enabled New sleep mode enabled status
 * @see MPU6050_GetSleepModeStatus()
 * @see MPU6050_RA_PWR_MGMT_1
 * @see MPU6050_PWR1_SLEEP_BIT
 */
void MPU6050_SetSleepModeStatus(FunctionalState NewState) 
{
	MPU6050_WriteBit(MPU6050_DEFAULT_ADDRESS, MPU6050_RA_PWR_MGMT_1, MPU6050_PWR1_SLEEP_BIT, NewState);
	delay_ms(4);
}


/** Get raw 6-axis motion sensor readings (accel/gyro).
 * Retrieves all currently available motion sensor values.
 * @param AccelGyro 16-bit signed integer array of length 6
 * @see MPU6050_RA_ACCEL_XOUT_H
 */
void MPU6050_GetRawAccelGyro(s16* AccelGyro) 
{
	int i;
	uint8_t tmpBuffer[14]; 
	I2C1_BufferRead(MPU6050_DEFAULT_ADDRESS, tmpBuffer, MPU6050_RA_ACCEL_XOUT_H, 14); 
	/* Get acceleration */
	for( i=0; i<3; i++) 
		AccelGyro[i]=((s16)((u16)tmpBuffer[2*i] << 8) + tmpBuffer[2*i+1]) - GyroOffset[i] ;
	/* Get Angular rate */
	for( i=4; i<7; i++)
		AccelGyro[i-1]=((s16)((u16)tmpBuffer[2*i] << 8) + tmpBuffer[2*i+1]);        


	//AccelGyro[5]+=295;
}




short get_Gyro_Z(void)
{
	uint8_t tmpBuffer[2];

	tmpBuffer[0] = MPU6050_RA_GYRO_ZOUT_H;
	I2C_Master_BufferWrite(I2C1, tmpBuffer, 1, MPU6050_DEFAULT_ADDRESS);
	I2C_Master_BufferRead(I2C1, tmpBuffer, 2, MPU6050_DEFAULT_ADDRESS);
	return ((short)((u16)tmpBuffer[0] << 8) + tmpBuffer[1]);

}

float get_Gyro_Z_Float(void)
{
	uint8_t tmpBuffer[2];
	tmpBuffer[0] = MPU6050_RA_GYRO_ZOUT_H;
	I2C_Master_BufferWrite(I2C1, tmpBuffer, 1, MPU6050_DEFAULT_ADDRESS);
	I2C_Master_BufferRead(I2C1, tmpBuffer, 2, MPU6050_DEFAULT_ADDRESS);

	return ((short)((u16)tmpBuffer[0] << 8) + tmpBuffer[1]-GyroZOffset)/65.536;

}

short get_Gyro_Z_Real(void)
{
	uint8_t tmpBuffer[2];

	I2C1_BufferRead(MPU6050_DEFAULT_ADDRESS, tmpBuffer, MPU6050_RA_GYRO_ZOUT_H, 2);
	return ((short)((u16)tmpBuffer[0] << 8) + tmpBuffer[1]);

}

short get_Accel_X_Real(void)
{
	uint8_t tmpBuffer[2]; 
	tmpBuffer[0] = MPU6050_RA_ACCEL_XOUT_H;
	I2C_Master_BufferWrite(I2C1, tmpBuffer, 1, MPU6050_DEFAULT_ADDRESS);
	I2C_Master_BufferRead(I2C1, tmpBuffer, 2, MPU6050_DEFAULT_ADDRESS);
	
	return ((short)((u16)tmpBuffer[0] << 8) + tmpBuffer[1]);

}
short get_Accel_Y_Real(void)
{
	uint8_t tmpBuffer[2]; 
	I2C1_BufferRead(MPU6050_DEFAULT_ADDRESS, tmpBuffer, MPU6050_RA_ACCEL_YOUT_H, 2);
	return ((short)((u16)tmpBuffer[0] << 8) + tmpBuffer[1]);

}
short get_Accel_Z_Real(void)
{
	uint8_t tmpBuffer[2]; 
	I2C1_BufferRead(MPU6050_DEFAULT_ADDRESS, tmpBuffer, MPU6050_RA_ACCEL_ZOUT_H, 2);
	return ((short)((u16)tmpBuffer[0] << 8) + tmpBuffer[1]);

}
void MPU6050_GetRawMag(s16* Meg) 
{
	

}


/** Write multiple bits in an 8-bit device register.
 * @param slaveAddr I2C slave device address
 * @param regAddr Register regAddr to write to
 * @param bitStart First bit position to write (0-7)
 * @param length Number of bits to write (not more than 8)
 * @param data Right-aligned value to write
 */
void MPU6050_WriteBits(uint8_t slaveAddr, uint8_t regAddr, uint8_t bitStart, uint8_t length, uint8_t data) 
{
	//      010 value to write
	// 76543210 bit numbers
	//    xxx   args: bitStart=4, length=3
	// 00011100 mask byte
	// 10101111 original value (sample)
	// 10100011 original & ~mask
	// 10101011 masked | value
	uint8_t tmp;
	uint8_t mask = ((1 << length) - 1) << (bitStart - length + 1);
	I2C1_BufferRead(slaveAddr, &tmp, regAddr, 1);  

	data <<= (bitStart - length + 1); // shift data into correct position
	data &= mask; // zero all non-important bits in data
	tmp &= ~(mask); // zero all important bits in existing byte
	tmp |= data; // combine data with existing byte
	while(I2C1_ByteWrite(slaveAddr,&tmp,regAddr)==Error); 

}
/** write a single bit in an 8-bit device register.
 * @param slaveAddr I2C slave device address
 * @param regAddr Register regAddr to write to
 * @param bitNum Bit position to write (0-7)
 * @param value New bit value to write
 */
void MPU6050_WriteBit(uint8_t slaveAddr, uint8_t regAddr, uint8_t bitNum, uint8_t data) 
{
	uint8_t tmp;
	I2C1_BufferRead(slaveAddr, &tmp, regAddr, 1);  
	tmp = (data != 0) ? (tmp | (1 << bitNum)) : (tmp & ~(1 << bitNum));
	I2C1_ByteWrite(slaveAddr,&tmp,regAddr); 
}
/** Read multiple bits from an 8-bit device register.
 * @param slaveAddr I2C slave device address
 * @param regAddr Register regAddr to read from
 * @param bitStart First bit position to read (0-7)
 * @param length Number of bits to read (not more than 8)
 * @param data Container for right-aligned value (i.e. '101' read from any bitStart position will equal 0x05)
 * @param timeout Optional read timeout in milliseconds (0 to disable, leave off to use default class value in readTimeout)
 */
void MPU6050_ReadBits(uint8_t slaveAddr, uint8_t regAddr, uint8_t bitStart, uint8_t length, uint8_t *data) 
{
	// 01101001 read byte
	// 76543210 bit numbers
	//    xxx   args: bitStart=4, length=3
	//    010   masked
	//   -> 010 shifted
	uint8_t tmp;
	uint8_t mask = ((1 << length) - 1) << (bitStart - length + 1);
	I2C1_BufferRead(slaveAddr, &tmp, regAddr, 1); 

	tmp &= mask;
	tmp >>= (bitStart - length + 1);
	*data = tmp;
}


/** Read a single bit from an 8-bit device register.
 * @param slaveAddr I2C slave device address
 * @param regAddr Register regAddr to read from
 * @param bitNum Bit position to read (0-7)
 * @param data Container for single bit value
 * @param timeout Optional read timeout in milliseconds (0 to disable, leave off to use default class value in readTimeout)
 */
void MPU6050_ReadBit(uint8_t slaveAddr, uint8_t regAddr, uint8_t bitNum, uint8_t *data) 
{
	uint8_t tmp;
	I2C1_BufferRead(slaveAddr, &tmp, regAddr, 1);  
	*data = tmp & (1 << bitNum);
}






/*
 * @brief  Writes one byte to the  MPU6050.
 * @param  slaveAddr : slave address MPU6050_DEFAULT_ADDRESS
 * @param  pBuffer : pointer to the buffer  containing the data to be written to the MPU6050.
 * @param  writeAddr : address of the register in which the data will be written
 * @return None
 */



Status I2C1_ByteWrite(uint8_t slaveAddr, uint8_t* pBuffer, uint8_t writeAddr)
{
	    __IO uint32_t Timeout = 0;
	//  ENTR_CRT_SECTION();


	/* Send START condition */
	I2C_GenerateSTART(I2C1, ENABLE);
Timeout = 0xFFFF;

	/* Test on EV5 and clear it */
	while(!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_MODE_SELECT))
{
            if (Timeout-- == 0)
                return Error;
}

	/* Send MPU6050 address for write */
	I2C_Send7bitAddress(I2C1, slaveAddr, I2C_Direction_Transmitter);
Timeout = 0xFFFF;
//mdelay(1);
	/* Test on EV6 and clear it */
	while(!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED))
{
            if (Timeout-- == 0)
                return Error;
}

	/* Send the MPU6050's internal address to write to */
	I2C_SendData(I2C1, writeAddr);

Timeout = 0xFFFF;
	/* Test on EV8 and clear it */
	while(!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_BYTE_TRANSMITTED))
{
            if (Timeout-- == 0)
                return Error;
 }

	/* Send the byte to be written */
	I2C_SendData(I2C1, *pBuffer);

Timeout = 0xFFFF;
	/* Test on EV8 and clear it */
	while(!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_BYTE_TRANSMITTED))
{
            if (Timeout-- == 0)
                return Error;
 }

	/* Send STOP condition */
	I2C_GenerateSTOP(I2C1, ENABLE);

return Success;
	// EXT_CRT_SECTION();


}


/**
 * @brief  Reads a block of data from the MPU6050.
 * @param  slaveAddr  : slave address MPU6050_DEFAULT_ADDRESS
 * @param  pBuffer : pointer to the buffer that receives the data read from the MPU6050.
 * @param  readAddr : MPU6050's internal address to read from.
 * @param  NumByteToRead : number of bytes to read from the MPU6050 ( NumByteToRead >1  only for the Mgnetometer readinf).
 * @return None
 */


void I2C1_BufferRead(uint8_t slaveAddr, uint8_t* pBuffer, uint8_t readAddr, u16 NumByteToRead)
{
	int timeout=10000;
	//ENTR_CRT_SECTION();
	//taskENTER_CRITICAL();

	/* While the bus is busy */
	while(I2C_GetFlagStatus(I2C1, I2C_FLAG_BUSY))
	{
		timeout--;
		if(timeout==0)
		{
			timeout=10000;
			break;
		}
	}

	/* Send START condition */
	I2C_GenerateSTART(I2C1, ENABLE);
	

	/* Test on EV5 and clear it */
	while(!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_MODE_SELECT))
	{
		timeout--;
		if(timeout==0)
		{
			timeout=10000;
			break;
		}
	}


	/* Send MPU6050 address for write */
	I2C_Send7bitAddress(I2C1, slaveAddr, I2C_Direction_Transmitter); 


	/* Test on EV6 and clear it */
	while(!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED))
	{
		timeout--;
		if(timeout==0)
		{
			timeout=10000;
			break;
		}
	}


	/* Clear EV6 by setting again the PE bit */
	I2C_Cmd(I2C1, ENABLE);


	/* Send the MPU6050's internal address to write to */
	I2C_SendData(I2C1, readAddr);


	/* Test on EV8 and clear it */
	while(!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_BYTE_TRANSMITTED))
	{
		timeout--;
		if(timeout==0)
		{
			timeout=10000;
			break;
		}
	}

	/* Send STRAT condition a second time */
	I2C_GenerateSTART(I2C1, ENABLE);


	/* Test on EV5 and clear it */
	while(!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_MODE_SELECT))
		{
		timeout--;
		if(timeout==0)
		{
			timeout=10000;
			break;
		}
	}


	/* Send MPU6050 address for read */
	I2C_Send7bitAddress(I2C1, slaveAddr, I2C_Direction_Receiver);


	/* Test on EV6 and clear it */
	while(!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_RECEIVER_MODE_SELECTED))
		{
		timeout--;
		if(timeout==0)
		{
			timeout=10000;
			break;
		}
	}


	/* While there is data to be read */
	while(NumByteToRead)
	{
		if(NumByteToRead == 1)
		{
			/* Disable Acknowledgement */
			I2C_AcknowledgeConfig(I2C1, DISABLE);


			/* Send STOP Condition */
			I2C_GenerateSTOP(I2C1, ENABLE);
		}


		/* Test on EV7 and clear it */
		if(I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_BYTE_RECEIVED))
		{
			/* Read a byte from the MPU6050 */
			*pBuffer = I2C_ReceiveData(I2C1);


			/* Point to the next location where the byte read will be saved */
			pBuffer++;


			/* Decrement the read bytes counter */
			NumByteToRead--;
		}
		//if(pushbutton==1) break;
		
		
		timeout--;
		if(timeout==0)
		{
			timeout=10000;
			break;
		}
	}


	/* Enable Acknowledgement to be ready for another reception */
	I2C_AcknowledgeConfig(I2C1, ENABLE);
	//  EXT_CRT_SECTION();
//	taskEXIT_CRITICAL();

}


void Calibrate_Gyros(void)
{
	



}	

void Calibrate_GyroZ(void)
{
	

}	





Status I2C_Master_BufferRead(I2C_TypeDef* I2Cx, uint8_t* pBuffer,  uint32_t NumByteToRead , uint8_t SlaveAddress)

{
    __IO uint32_t temp = 0;
    __IO uint32_t Timeout = 0;
	__IO uint8_t Address;
   

    /* Enable I2C errors interrupts (used in all modes: Polling, DMA and Interrupts */
    I2Cx->CR2 |= I2C_IT_ERR;

   



        if (NumByteToRead == 1)
        {
            Timeout = 0xFFFF;
            /* Send START condition */
            I2Cx->CR1 |= CR1_START_Set;
            /* Wait until SB flag is set: EV5  */
            while ((I2Cx->SR1&0x0001) != 0x0001)
            {
                if (Timeout-- == 0)
                    return Error;
            }
            /* Send slave address */
            /* Reset the address bit0 for read */
            SlaveAddress |= OAR1_ADD0_Set;
            Address = SlaveAddress;
            /* Send the slave address */
            I2Cx->DR = Address;
            /* Wait until ADDR is set: EV6_3, then program ACK = 0, clear ADDR
            and program the STOP just after ADDR is cleared. The EV6_3 
            software sequence must complete before the current byte end of transfer.*/
            /* Wait until ADDR is set */
            Timeout = 0xFFFF;
            while ((I2Cx->SR1&0x0002) != 0x0002)
            {
                if (Timeout-- == 0)
                    return Error;
            }
            /* Clear ACK bit */
            I2Cx->CR1 &= CR1_ACK_Reset;
            /* Disable all active IRQs around ADDR clearing and STOP programming because the EV6_3
            software sequence must complete before the current byte end of transfer */
            __disable_irq();
            /* Clear ADDR flag */
            temp = I2Cx->SR2;
            /* Program the STOP */
            I2Cx->CR1 |= CR1_STOP_Set;
            /* Re-enable IRQs */
            __enable_irq();
            /* Wait until a data is received in DR register (RXNE = 1) EV7 */
            while ((I2Cx->SR1 & 0x00040) != 0x000040);
            /* Read the data */
            *pBuffer = I2Cx->DR;
            /* Make sure that the STOP bit is cleared by Hardware before CR1 write access */
            while ((I2Cx->CR1&0x200) == 0x200);
            /* Enable Acknowledgement to be ready for another reception */
            I2Cx->CR1 |= CR1_ACK_Set;

        }

        else if (NumByteToRead == 2)
        {
            /* Set POS bit */
            I2Cx->CR1 |= CR1_POS_Set;
            Timeout = 0xFFFF;
            /* Send START condition */
            I2Cx->CR1 |= CR1_START_Set;
            /* Wait until SB flag is set: EV5 */
            while ((I2Cx->SR1&0x0001) != 0x0001)
            {
                if (Timeout-- == 0)
                    return Error;
            }
            Timeout = 0xFFFF;
            /* Send slave address */
            /* Set the address bit0 for read */
            SlaveAddress |= OAR1_ADD0_Set;
            Address = SlaveAddress;
            /* Send the slave address */
            I2Cx->DR = Address;
            /* Wait until ADDR is set: EV6 */
            while ((I2Cx->SR1&0x0002) != 0x0002)
            {
                if (Timeout-- == 0)
                    return Error;
            }
            /* EV6_1: The acknowledge disable should be done just after EV6,
            that is after ADDR is cleared, so disable all active IRQs around ADDR clearing and 
            ACK clearing */
            __disable_irq();
            /* Clear ADDR by reading SR2 register  */
            temp = I2Cx->SR2;
            /* Clear ACK */
            I2Cx->CR1 &= CR1_ACK_Reset;
            /*Re-enable IRQs */
            __enable_irq();
            /* Wait until BTF is set */
            while ((I2Cx->SR1 & 0x00004) != 0x000004);
            /* Disable IRQs around STOP programming and data reading because of the limitation ?*/
            __disable_irq();
            /* Program the STOP */
            I2C_GenerateSTOP(I2Cx, ENABLE);
            /* Read first data */
            *pBuffer = I2Cx->DR;
            /* Re-enable IRQs */
            __enable_irq();
            /**/
            pBuffer++;
            /* Read second data */
            *pBuffer = I2Cx->DR;
            /* Make sure that the STOP bit is cleared by Hardware before CR1 write access */
            while ((I2Cx->CR1&0x200) == 0x200);
            /* Enable Acknowledgement to be ready for another reception */
            I2Cx->CR1  |= CR1_ACK_Set;
            /* Clear POS bit */
            I2Cx->CR1  &= CR1_POS_Reset;

        }

        else

        {

            Timeout = 0xFFFF;
            /* Send START condition */
            I2Cx->CR1 |= CR1_START_Set;
            /* Wait until SB flag is set: EV5 */
            while ((I2Cx->SR1&0x0001) != 0x0001)
            {
                if (Timeout-- == 0)
                    return Error;
            }
            Timeout = 0xFFFF;
            /* Send slave address */
            /* Reset the address bit0 for write */
            SlaveAddress |= OAR1_ADD0_Set;;
            Address = SlaveAddress;
            /* Send the slave address */
            I2Cx->DR = Address;
            /* Wait until ADDR is set: EV6 */
            while ((I2Cx->SR1&0x0002) != 0x0002)
            {
                if (Timeout-- == 0)
                    return Error;
            }
            /* Clear ADDR by reading SR2 status register */
            temp = I2Cx->SR2;
            /* While there is data to be read */
            while (NumByteToRead)
            {
                /* Receive bytes from first byte until byte N-3 */
                if (NumByteToRead != 3)
                {
                    /* Poll on BTF to receive data because in polling mode we can not guarantee the
                    EV7 software sequence is managed before the current byte transfer completes */
                    while ((I2Cx->SR1 & 0x00004) != 0x000004);
                    /* Read data */
                    *pBuffer = I2Cx->DR;
                    /* */
                    pBuffer++;
                    /* Decrement the read bytes counter */
                    NumByteToRead--;
                }

                /* it remains to read three data: data N-2, data N-1, Data N */
                if (NumByteToRead == 3)
                {

                    /* Wait until BTF is set: Data N-2 in DR and data N -1 in shift register */
                    while ((I2Cx->SR1 & 0x00004) != 0x000004);
                    /* Clear ACK */
                    I2Cx->CR1 &= CR1_ACK_Reset;

                    /* Disable IRQs around data reading and STOP programming because of the
                    limitation ? */
                    __disable_irq();
                    /* Read Data N-2 */
                    *pBuffer = I2Cx->DR;
                    /* Increment */
                    pBuffer++;
                    /* Program the STOP */
                    I2Cx->CR1 |= CR1_STOP_Set;
                    /* Read DataN-1 */
                    *pBuffer = I2Cx->DR;
                    /* Re-enable IRQs */
                    __enable_irq();
                    /* Increment */
                    pBuffer++;
                    /* Wait until RXNE is set (DR contains the last data) */
                    while ((I2Cx->SR1 & 0x00040) != 0x000040);
                    /* Read DataN */
                    *pBuffer = I2Cx->DR;
                    /* Reset the number of bytes to be read by master */
                    NumByteToRead = 0;

                }
            }
            /* Make sure that the STOP bit is cleared by Hardware before CR1 write access */
            while ((I2Cx->CR1&0x200) == 0x200);
            /* Enable Acknowledgement to be ready for another reception */
            I2Cx->CR1 |= CR1_ACK_Set;

        }



   

    return Success;
}



/**
  * @brief  Writes buffer of bytes.
  * @param pBuffer: Buffer of bytes to be sent to the slave.
  * @param NumByteToWrite: Number of bytes to be sent by the Master.
  * @param Mode: Polling or DMA or Interrupt having the highest priority in the application.
  * @param SlaveAddress: The address of the slave to be addressed by the Master.
  * @retval : None.
  */
Status I2C_Master_BufferWrite(I2C_TypeDef* I2Cx, uint8_t* pBuffer,  uint32_t NumByteToWrite  , uint8_t SlaveAddress )

{

    __IO uint32_t temp = 0;
    __IO uint32_t Timeout = 0;
		__IO uint8_t Address;

    /* Enable Error IT (used in all modes: DMA, Polling and Interrupts */
    I2Cx->CR2 |= I2C_IT_ERR;


        Timeout = 0xFFFF;
        /* Send START condition */
        I2Cx->CR1 |= CR1_START_Set;
        /* Wait until SB flag is set: EV5 */
        while ((I2Cx->SR1&0x0001) != 0x0001)
        {
            if (Timeout-- == 0)
                return Error;
        }

        /* Send slave address */
        /* Reset the address bit0 for write*/
        SlaveAddress &= OAR1_ADD0_Reset;
        Address = SlaveAddress;
        /* Send the slave address */
        I2Cx->DR = Address;
        Timeout = 0xFFFF;
        /* Wait until ADDR is set: EV6 */
        while ((I2Cx->SR1 &0x0002) != 0x0002)
        {
            if (Timeout-- == 0)
                return Error;
        }

        /* Clear ADDR flag by reading SR2 register */
        temp = I2Cx->SR2;
        /* Write the first data in DR register (EV8_1) */
        I2Cx->DR = *pBuffer;
        /* Increment */
        pBuffer++;
        /* Decrement the number of bytes to be written */
        NumByteToWrite--;
        /* While there is data to be written */
        while (NumByteToWrite--)
        {
            /* Poll on BTF to receive data because in polling mode we can not guarantee the
              EV8 software sequence is managed before the current byte transfer completes */
            while ((I2Cx->SR1 & 0x00004) != 0x000004);
            /* Send the current byte */
            I2Cx->DR = *pBuffer;
            /* Point to the next byte to be written */
            pBuffer++;
        }
        /* EV8_2: Wait until BTF is set before programming the STOP */
        while ((I2Cx->SR1 & 0x00004) != 0x000004);
        /* Send STOP condition */
        I2Cx->CR1 |= CR1_STOP_Set;
        /* Make sure that the STOP bit is cleared by Hardware */
        while ((I2Cx->CR1&0x200) == 0x200);





    return Success;

}




