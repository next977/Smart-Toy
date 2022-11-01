
#include "platform_config.h"
#include "gyro.h"

bool gyroAction = false;
uint32_t gyro_time =0;
static int16_t  gyrovalue;
static int16_t  accelvalue;
int16_t GetGyroValue(void)
{
	
	return get_Gyro_Z()-afdata.agedata.gdata.gyro_z_offset;
}

void Gyro_Action(uint8_t * gyroAction)
{
	//static int testtime = 0;
	//static float x = 0;
	//static float p = 1;
	//static float x1 = 0;
	//static float p1 = 1;
	//static float x2 = 0;
	//static float p2 = 1;
	//static uint8_t buffer[5];
	
	if(*gyroAction)
	{
		if(gyro_time > 2)
		{
			gyro_time = 0;
			gyrovalue = GetGyroValue();
			accelvalue = get_Accel_X_Real();
			if(mv.mState == JEONJIN)
			{
				
				if(gyrovalue > 50 || gyrovalue < - 50)
				{
					
					MotorRotateSet_D(gyrovalue);
					
				}
				
			}
			else if(mv.mState == HOOJIN)
			{
				
				if(gyrovalue > 50 || gyrovalue < - 50)
				{
					
					MotorRotateSet_R(gyrovalue);
					
				}
			}
			
			if(accelvalue>25000 || accelvalue<-25000)
			{
				BT_SendString("AE$|4|1|20|E@");
			}
			/*
			testtime ++ ;
			if(testtime > 50)
			{
				testtime = 0;
				printf("%4d,%4f,%4f,%4f\r\n",gyrovalue,Kalman_Filter((float)gyrovalue, &x, &p, 0.0005, 0.05),Kalman_Filter((float)gyrovalue, &x1, &p1, 0.001, 0.01),Kalman_Filter((float)gyrovalue, &x2, &p2, 0.00001, 0.01));
			}
			*/
			/*
			testtime ++ ;
			if(testtime > 100)
			{
				
				testtime = 0;
				BT_SendString("%|");
				if(gyrovalue < 0)
				{
					buffer[0] = '-';
					BT_SendData(buffer, 1);
					gyrovalue = gyrovalue  * (-1);
					
				}
				else
				{
					
				}
				if((gyrovalue/10000) > 0)
				{
					buffer[0] = (gyrovalue/10000)  + '0';
					BT_SendData(buffer, 1);
				}
				if((gyrovalue/1000) > 0)
				{
					buffer[0] = ((gyrovalue%10000)/1000)  + '0';
					BT_SendData(buffer, 1);
				}
				if((gyrovalue/100) > 0)
				{
					buffer[0] = ((gyrovalue%1000)/100)  + '0';
					BT_SendData(buffer, 1);
				}
				if((gyrovalue/10) > 0)
				{
					buffer[0] = ((gyrovalue%100)/10)  + '0';
					BT_SendData(buffer, 1);
				}

					buffer[0] = ((gyrovalue%10)/1)  + '0';
					BT_SendData(buffer, 1);

				BT_SendString("|0|#");
				//BT_SendString("%|-1000|0|#");
			}
			*/
			
		}
		
		
		
	}
	
}
