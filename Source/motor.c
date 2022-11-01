
#include "platform_config.h"
#include "motor.h"

MotorValue mv;
uint16_t LSPEED = 0;
uint16_t RSPEED = 0;
uint16_t MOTORLEVEL = 0;
int16_t gyrocontrolvalue = 0;
int16_t gyroproportion = 0;
void vMotorCtrl(uint8_t lccw, uint16_t lspeed, uint8_t rccw, uint16_t rspeed)
{

#if MOTORL

	GPIOB->ODR &= ~(0x03<<10);
	GPIOB->ODR |= (lccw & 1)<<10;
	GPIOB->ODR |= (lccw & 2)<<10;



#else

	GPIOB->ODR &= ~(0x03<<10);
	GPIOB->ODR |= ((lccw & 1)<<11);
	GPIOB->ODR |= ((lccw & 2)<<9);


#endif

#if MOTORR
	GPIOB->ODR &= ~(0x03<<13);
	GPIOB->ODR |= (rccw & 1)<<13;
	GPIOB->ODR |= (rccw & 2)<<13;



#else

	GPIOB->ODR &= ~(0x03<<13);
	GPIOB->ODR |= ((rccw & 1)<<14);
	GPIOB->ODR |= ((rccw & 2)<<12);


#endif
	
	LSPEED = lspeed;
	RSPEED = rspeed;
	TIM_OCInitStructure.TIM_Pulse = lspeed;
	TIM_OC3Init(TIM4, &TIM_OCInitStructure);
	TIM_OCInitStructure.TIM_Pulse = rspeed;
	TIM_OC4Init(TIM4, &TIM_OCInitStructure);


}


void MotorRotateSet_D(int16_t gyrovalue)
{
	
	//if(MOTORLEVEL == 1)
	//{
	//	gyroproportion = 30;
	//	gyrocontrolvalue = gyrovalue/gyroproportion;
		
		
		
	//}
	//else
	//{
		gyrocontrolvalue = (int16_t)JeonJinPid((float)gyrovalue);
		
	//}
	mv.motorlevelR[MOTORLEVEL]-=gyrocontrolvalue;
	mv.motorlevelL[MOTORLEVEL]+=gyrocontrolvalue;
	
	if(mv.motorlevelR[MOTORLEVEL] > 23999)
	{
		mv.motorlevelR[MOTORLEVEL] = 23999;
	}
	else
	{
		if(mv.motorlevelR[MOTORLEVEL]> afdata.agedata.mdata.motorlevelR[MOTORLEVEL]+MOTOR_CONTROL_MAX_RANGE)
		{
			mv.motorlevelR[MOTORLEVEL] = afdata.agedata.mdata.motorlevelR[MOTORLEVEL]+MOTOR_CONTROL_MAX_RANGE;
		}
		else if(mv.motorlevelR[MOTORLEVEL]< afdata.agedata.mdata.motorlevelR[MOTORLEVEL]-MOTOR_CONTROL_MIN_RANGE)
		{
			mv.motorlevelR[MOTORLEVEL] = afdata.agedata.mdata.motorlevelR[MOTORLEVEL]-MOTOR_CONTROL_MIN_RANGE;
		}
	}
	
	
	
	if(mv.motorlevelL[MOTORLEVEL] > 23999)
	{
		mv.motorlevelL[MOTORLEVEL] = 23999;
	}
	else
	{
		if(mv.motorlevelL[MOTORLEVEL]> afdata.agedata.mdata.motorlevelL[MOTORLEVEL]+MOTOR_CONTROL_MAX_RANGE)
		{
			mv.motorlevelL[MOTORLEVEL] = afdata.agedata.mdata.motorlevelL[MOTORLEVEL]+MOTOR_CONTROL_MAX_RANGE;
		}
		else if(mv.motorlevelL[MOTORLEVEL]< afdata.agedata.mdata.motorlevelL[MOTORLEVEL]-MOTOR_CONTROL_MIN_RANGE)
		{
			mv.motorlevelL[MOTORLEVEL] = afdata.agedata.mdata.motorlevelL[MOTORLEVEL]-MOTOR_CONTROL_MIN_RANGE;
		}
	}
	
	
	TIM_OCInitStructure.TIM_Pulse = mv.motorlevelL[MOTORLEVEL];
	TIM_OC3Init(TIM4, &TIM_OCInitStructure);
	TIM_OCInitStructure.TIM_Pulse = mv.motorlevelR[MOTORLEVEL];
	TIM_OC4Init(TIM4, &TIM_OCInitStructure);
}

void MotorRotateSet_R(int16_t gyrovalue)
{
	//if(MOTORLEVEL == 1)
	//{
	//	gyroproportion = 30;
	//	gyrocontrolvalue = gyrovalue/gyroproportion;
	//	
		
		
	//}
	//else
	//{
		gyrocontrolvalue = (int16_t)JeonJinPid((float)gyrovalue);
		
	//}
	mv.BmotorlevelR[MOTORLEVEL]+=gyrocontrolvalue;
	mv.BmotorlevelL[MOTORLEVEL]-=gyrocontrolvalue;
	
	if(mv.BmotorlevelR[MOTORLEVEL] > 23999)
	{
		mv.BmotorlevelR[MOTORLEVEL] = 23999;
	}
	else
	{
		if(mv.BmotorlevelR[MOTORLEVEL]> afdata.agedata.mdata.BmotorlevelR[MOTORLEVEL]+MOTOR_CONTROL_MAX_RANGE)
		{
			mv.BmotorlevelR[MOTORLEVEL] = afdata.agedata.mdata.BmotorlevelR[MOTORLEVEL]+MOTOR_CONTROL_MAX_RANGE;
		}
		else if(mv.BmotorlevelR[MOTORLEVEL]< afdata.agedata.mdata.BmotorlevelR[MOTORLEVEL]-MOTOR_CONTROL_MIN_RANGE)
		{
			mv.BmotorlevelR[MOTORLEVEL] = afdata.agedata.mdata.BmotorlevelR[MOTORLEVEL]-MOTOR_CONTROL_MIN_RANGE;
		}
	}
	
	
	
	if(mv.BmotorlevelL[MOTORLEVEL] > 23999)
	{
		mv.BmotorlevelL[MOTORLEVEL] = 23999;
	}
	else
	{
		if(mv.BmotorlevelL[MOTORLEVEL]> afdata.agedata.mdata.BmotorlevelL[MOTORLEVEL]+MOTOR_CONTROL_MAX_RANGE)
		{
			mv.BmotorlevelL[MOTORLEVEL] = afdata.agedata.mdata.BmotorlevelL[MOTORLEVEL]+MOTOR_CONTROL_MAX_RANGE;
		}
		else if(mv.BmotorlevelL[MOTORLEVEL]< afdata.agedata.mdata.BmotorlevelL[MOTORLEVEL]-MOTOR_CONTROL_MIN_RANGE)
		{
			mv.BmotorlevelL[MOTORLEVEL] = afdata.agedata.mdata.BmotorlevelL[MOTORLEVEL]-MOTOR_CONTROL_MIN_RANGE;
		}
	}
	
	TIM_OCInitStructure.TIM_Pulse = mv.BmotorlevelL[MOTORLEVEL];
	TIM_OC3Init(TIM4, &TIM_OCInitStructure);
	TIM_OCInitStructure.TIM_Pulse = mv.BmotorlevelR[MOTORLEVEL];
	TIM_OC4Init(TIM4, &TIM_OCInitStructure);
}



void MotorOnOff(uint32_t OnOff)
{
	if(OnOff == MOTOR_OFF)
	{
		GPIO_ResetBits(GPIOB, GPIO_Pin_12 | GPIO_Pin_15);
	}
	else
	{
		GPIO_SetBits(GPIOB, GPIO_Pin_12 | GPIO_Pin_15);
	}

}




void MotorRotateR(uint16_t div)
{

	gyroAction = false;
	mv.mStateRotate = ROTATE;
	mv.mStateLRotate = RROTATE;
	if(MOTORLEVEL == 0)
	{
		vMotorCtrl(1,0,2,0);
		TIM_OCInitStructure.TIM_Pulse = MOTOR_SPEED_ROTATE_INSTOP;
		TIM_OC3Init(TIM4, &TIM_OCInitStructure);	
		TIM_OCInitStructure.TIM_Pulse = MOTOR_SPEED_ROTATE_INSTOP;
		TIM_OC4Init(TIM4, &TIM_OCInitStructure);
	}
	else
	{


		TIM_OCInitStructure.TIM_Pulse = RSPEED/div;
		TIM_OC4Init(TIM4, &TIM_OCInitStructure);


	}

}

void MotorRotateL(uint16_t div)
{
	
	gyroAction = false;
	mv.mStateRotate = ROTATE;
	mv.mStateLRotate = LROTATE;
	if(MOTORLEVEL == 0)
	{
		vMotorCtrl(2,0,1,0);
		TIM_OCInitStructure.TIM_Pulse = MOTOR_SPEED_ROTATE_INSTOP;
		TIM_OC3Init(TIM4, &TIM_OCInitStructure);	
		TIM_OCInitStructure.TIM_Pulse = MOTOR_SPEED_ROTATE_INSTOP;
		TIM_OC4Init(TIM4, &TIM_OCInitStructure);
	}
	else
	{
		


		TIM_OCInitStructure.TIM_Pulse = LSPEED/div;
		TIM_OC3Init(TIM4, &TIM_OCInitStructure);


	}
	

}


void MotorRotateStop(void)
{

	mv.mStateRotate = ROTATESTOP;
	TIM_OCInitStructure.TIM_Pulse = LSPEED;
	TIM_OC3Init(TIM4, &TIM_OCInitStructure);	
	TIM_OCInitStructure.TIM_Pulse = RSPEED;
	TIM_OC4Init(TIM4, &TIM_OCInitStructure);
	if(MOTORLEVEL != 0)
	{
		gyroAction = true;
		delay_ms(10);
	}
}

void BL_MotorRotateR(uint16_t l, uint16_t r)
{

	vMotorCtrl(1,0,2,0);
	TIM_OCInitStructure.TIM_Pulse = l;
	TIM_OC3Init(TIM4, &TIM_OCInitStructure);	
	TIM_OCInitStructure.TIM_Pulse = r;
	TIM_OC4Init(TIM4, &TIM_OCInitStructure);
}

void BL_MotorRotateL(uint16_t l, uint16_t r)
{

	vMotorCtrl(2,0,1,0);
	TIM_OCInitStructure.TIM_Pulse = l;
	TIM_OC3Init(TIM4, &TIM_OCInitStructure);	
	TIM_OCInitStructure.TIM_Pulse = r;
	TIM_OC4Init(TIM4, &TIM_OCInitStructure);
}


void MotorStop(void)
{
	MOTORLEVEL = 0;
	LSPEED=0;
	RSPEED=0;
	mv.mState = STOP;
	mv.mStateRotate = ROTATESTOP;
	vMotorCtrl(0,0,0,0);
	gyroAction = false;
	
}
void MotorJeonJin(uint8_t level)
{
	
	if(mv.mState == HOOJIN)
	{
		MotorStop();
		
	}
	
	if(level == 0)
	{
		MelodyOff();
		MotorStop();
		
	}
	else if(level > MOTOR_MAX_LEVEL)
	{
		
		DPRINTF("%s\r\n", "Motor Level Over");
		return;
	}
	else
	{
		gyroAction = true;
		mv.mState = JEONJIN;
		mv.motorlevelL[level] = afdata.agedata.mdata.motorlevelL[level];
		mv.motorlevelR[level] = afdata.agedata.mdata.motorlevelR[level];
		vMotorCtrl(1,mv.motorlevelL[level],1,mv.motorlevelR[level] );
	}
	
	MOTORLEVEL = level;

	
	

	
	
	
}
void MotorHooJin(uint8_t level)
{
	
	if(mv.mState == JEONJIN)
	{
		MotorStop();
	}
	
	if(level == 0)
	{
		MelodyOff();
		MotorStop();
	}
	else if(level > MOTOR_MAX_LEVEL)
	{
		
		DPRINTF("%s\r\n", "Motor Level Over");
	}
	else
	{
		gyroAction = true;
		mv.mState = HOOJIN;
		mv.BmotorlevelL[level] = afdata.agedata.mdata.BmotorlevelL[level];
		mv.BmotorlevelR[level] = afdata.agedata.mdata.BmotorlevelR[level];
		vMotorCtrl(2,mv.BmotorlevelL[level],2,mv.BmotorlevelR[level]);
		
	}
	
	
	MOTORLEVEL = level;
	

}

void Motor_DataRead(void)
{
	int i;
	
	for(i=1;i<MOTOR_MAX_LEVEL+1;i++)
	{
		mv.motorlevelL[i] = afdata.agedata.mdata.motorlevelL[i];
		mv.motorlevelR[i] = afdata.agedata.mdata.motorlevelR[i];;
		mv.BmotorlevelL[i] = afdata.agedata.mdata.BmotorlevelL[i];;
		mv.BmotorlevelR[i] = afdata.agedata.mdata.BmotorlevelR[i];;
	}


}

void Motor_DataWrite(void)
{
	int i;

	for(i=1;i<MOTOR_MAX_LEVEL+1;i++)
	{
		afdata.agedata.mdata.motorlevelL[i]=mv.motorlevelL[i];
		afdata.agedata.mdata.motorlevelR[i]=mv.motorlevelR[i];
		afdata.agedata.mdata.BmotorlevelL[i]=mv.BmotorlevelL[i];
		afdata.agedata.mdata.BmotorlevelR[i]=mv.BmotorlevelR[i];
	}

}

float JeonJinPid(float gyro)
{
		// PID
	const float Kp = 0.007; 
	const float Ki = 0;
	const float Kd = 0.001;
	static float pTerm, iTerm, dTerm, integrated_error, last_error, error;
	const float K =1;
	
	
	error = gyro;  // 180 = level

	
	
	
	
	pTerm = Kp * error;
	integrated_error += error;
	iTerm = Ki * integrated_error;
	dTerm = Kd * (last_error - error);
	last_error = error;
	
	return K*(pTerm + iTerm + dTerm);
}

