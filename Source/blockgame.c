#include "platform_config.h"
#include "blockgame.h"

uint32_t hoojintime = 0;
int BGM;
bool blockGameAction = false;
uint32_t gametime = 0;
uint32_t blockGameTime = 0;
uint32_t blockGameBlockCount = 0;
uint8_t Direction = 0;
uint16_t FirstSensorBuffer_F;
uint16_t FirstSensorBuffer_R;
uint16_t SecondSensorBuffer_F;
uint16_t SecondSensorBuffer_R;
uint8_t Backtime = 0;
float gyro_sum;



void (*funcBlockGame[16])(void) = {BGM_Nothing, BGM_JeonJin, BGM_BlockDetect, BGM_GoalInCheck, BGM_WhatDirection, BGM_FistDistance, BGM_ExcuteDirection, BGM_DirectionStop, BGM_SecondDistance, BGM_Back, BGM_BackStop, BGM_Parallel };
/*
BGM -> Block Game Mode
BGM_Nothing : No Action
BGM_Jeonjin : Just go ahead
BGM_BlockDetect : Front IR Sensor Detecting....and Motor Stop
BGM_GoalInCheck : Side IR Sensor Check....Goal In when sensor detect both Lsensor and Rsensor
.....
...
..



*/





void BlockGame_Action(uint8_t * bgameAction)
{
	
	if(*bgameAction)
	{
		
		
		funcBlockGame[BGM]();
		
		
	}
	
}

void BlockGameReady(void)
{
	DPRINTF("%s\r\n", "BlockGameReady");
	Block_Game_Mode = BLOCKGAMEMODE_READY;
	gametime = 0;
	blockGameTime = 0;
	blockGameBlockCount = 0;
	ledAction = true;
	
}

void BlockGameStart(void)
{
	DPRINTF("%s\r\n", "BlockGameStart");
	Block_Game_Mode = BLOCKGAMEMODE_RUN;
	blockGameAction = true;
	IRSENSOR_ON();
	BGM = 1;
	ledAction = true;

	
}

void BlockGameStop(void)
{
	
	DPRINTF("%s\r\n", "BlockGameStop");
	Block_Game_Mode = BLOCKGAMEMODE_NONE;
	blockGameAction = false;
	IRSENSOR_OFF();
	MotorStop();
	//MelodyOff();
	BGM = 0;
	ledAction = true;
	
}

void BlockGameResult(void)
{

	
	MelodyStart(SUCCESSMELODY);
	
	if(Game_Mode == GAMEMODE_BLOCKGAME)
	{
		
		afdata.agedata.bgdata[0].flag[0] = 2;
		Data_save();
		Flash_write();
		
	
		
		if(afdata.agedata.bgdata[0].flag[0] ==2)
		{
			Data_send();
			
		}
	}
	Block_Game_Mode = BLOCKGAMEMODE_GOALIN;
	ledAction = true;

}


void BGM_Nothing(void)
{
	if(GetSensorValueReal(F_SENSOR) > 1000)
	{
		BlockGameStop();
		
	}
	
}
void BGM_JeonJin(void)
{
	MotorJeonJin(1);//기기 전진, 속도 : 1 ~ 9 단계 까지
	BGM++;// 다음 함수 진행
}
void BGM_BlockDetect(void)
{
	
	if( GetSensorValueReal(F_SENSOR) < F_Sensor)// F_Sensor : 블록과 기기간의 거리가 5mm정도 됐을 때의 센서 값
	{
		
		MotorStop();
		BGM++;
		MelodyStart(BLOCKDETECTMELODY);
		
	}
	
	
}
void BGM_GoalInCheck(void)
{
	if(IsSensorCheck(F_SENSOR, F_Sensor) && 
		 IsSensorCheck(L_SENSOR, GOALINSENSORVALUE) &&
		 IsSensorCheck(R_SENSOR, GOALINSENSORVALUE))
	{
		BGM = 0;// 게임 종료
		BlockGameResult();//게임 결과 전송
		
	}
	else
	{
		blockGameBlockCount ++;
		BGM++;
	}
	
	
}
void BGM_WhatDirection(void)
{
	if(GetSensorValue(L_SENSOR) - GetSensorValue(R_SENSOR) >= 0) //오른쪽에 블록이 있을 때의 경우
	{
		Direction = D_LEFT;
	}
	else
	{
		Direction = D_RIGHT;
	}
	BGM++;
}
void BGM_FistDistance(void)
{
	if(Direction == D_LEFT)
	{
		FirstSensorBuffer_F = GetNewSensorValue(FR_SENSOR);
		FirstSensorBuffer_R = GetNewSensorValue(R_SENSOR);
	}
	else if(Direction == D_RIGHT)
	{
		FirstSensorBuffer_F = GetNewSensorValue(FL_SENSOR);
		FirstSensorBuffer_R = GetNewSensorValue(L_SENSOR);
	}
	BGM++;
}


void BGM_ExcuteDirection(void)
{
	if(Direction == D_LEFT)
	{
		MotorRotateL(1);
		
	}
	else if(Direction == D_RIGHT)
	{
		MotorRotateR(1);
	}
	gyro_sum = 0;
	BGM++;
	ledAction = true;
}
	
void BGM_DirectionStop(void)
{
	if(gyro_time>2)
	{
		gyro_time = 0;
		gyro_sum+=(get_Gyro_Z_Float()/250.0);
		if(Direction == D_LEFT)
		{
			if(gyro_sum > 100)
			{
				MotorStop();
				BGM++;
				ledAction = true;
				//delay_ms(100);
				return;
			}
			
		}
		else if(Direction == D_RIGHT)
		{
			if(gyro_sum < -100)
			{
				MotorStop();
				BGM++;
				ledAction = true;
				//delay_ms(100);
				return;
			}
			
			
		}
	}
	
	
}
void BGM_SecondDistance(void)
{
	if(Direction == D_LEFT)
	{
		SecondSensorBuffer_F = GetNewSensorValue(FR_SENSOR);
		SecondSensorBuffer_R = GetNewSensorValue(R_SENSOR);
	}
	else if(Direction == D_RIGHT)
	{
		SecondSensorBuffer_F = GetNewSensorValue(FL_SENSOR);
		SecondSensorBuffer_R = GetNewSensorValue(L_SENSOR);
	}
	Backtime = 0;
	BGM++;
}
void BGM_Back(void)
{
	
	if(FirstSensorBuffer_R >3000  ) //회전 전에 간격이 30mm 이상 떨어져 있으면 후진
	{

		Backtime ++;
	}
	
	if(SecondSensorBuffer_F > 3000)
	{
		Backtime ++;
		
	}
	
	
	if(Backtime)
	{
		
		MotorHooJin(1);
		BGM++;
		MelodyStart(BLOCKHOOJINMELODY);
		hoojintime = 0;

		
	}
	else
	{
		BGM+=2;
	}
}

void BGM_BackStop(void)
{
	
	if(Backtime == 1)
	{
		if(hoojintime > 350)
		{
			MotorStop();
			BGM++;
			
		}
	}
	else if(Backtime == 2)
	{
		if(hoojintime > 500)
		{
			MotorStop();
			BGM++;
			
		}
	}
	else
	{
		
	}
	
}

void BGM_Parallel(void)
{
	

	static int frontside = 0,rearside =0;
	int i;
	
	
	
	if(Direction == D_LEFT)
	{
		
		for(i = 0; i<100 ; i++)
		{
			
			frontside += GetNewSensorValue(FR_SENSOR);
			rearside += GetNewSensorValue(R_SENSOR);
			
		}
		
		frontside = frontside/100;
		rearside = rearside/100;
		frontside = frontside-rearside;
		
		
		if(frontside>100)
		{
			BL_MotorRotateR(BLOCKZIGZAG,0);
			while(1)
			{
				for(i = 0; i<100 ; i++)
				{
					
					frontside += GetNewSensorValue(FR_SENSOR);
					rearside += GetNewSensorValue(R_SENSOR);
					
				}
				
				frontside = frontside/100;
				rearside = rearside/100;
				frontside = frontside-rearside;
				if(frontside < 100)
				{
					MotorStop();
					BGM = 1;
					delay_ms(100);
					return;
				}
				
			}
			
		}
		else if(frontside <-100)
		{
			BL_MotorRotateL(0,BLOCKZIGZAG);
			while(1)
			{
				for(i = 0; i<100 ; i++)
				{
					
					frontside += GetNewSensorValue(FR_SENSOR);
					rearside += GetNewSensorValue(R_SENSOR);
					
				}
				
				frontside = frontside/100;
				rearside = rearside/100;
				frontside = frontside-rearside;
				if(frontside > -100)
				{
					MotorStop();
					BGM = 1;
					delay_ms(100);
					
					return;
				}
				
			}

		}
		else
		{

			BGM = 1;
			delay_ms(100);
			return;

			
		}
		
	}
	else if(Direction == D_RIGHT)
	{
		
		for(i = 0; i<100 ; i++)
		{
			
			frontside += GetNewSensorValue(FL_SENSOR);
			rearside += GetNewSensorValue(L_SENSOR);
			
		}
		frontside = frontside/100;
		rearside = rearside/100;
		frontside = frontside-rearside;
		
		if(frontside>100)
		{
			BL_MotorRotateL(0,BLOCKZIGZAG);
			while(1)
			{
				for(i = 0; i<100 ; i++)
				{
					
					frontside += GetNewSensorValue(FL_SENSOR);
					rearside += GetNewSensorValue(L_SENSOR);
					
				}
				frontside = frontside/100;
				rearside = rearside/100;
				frontside = frontside-rearside;
				if(frontside < 100)
				{
					MotorStop();
					BGM = 1;
					delay_ms(100);
					return;
				}
			}
			
		}
		else if(frontside <-100)
		{
			BL_MotorRotateR(BLOCKZIGZAG,0);
			while(1)
			{
				for(i = 0; i<100 ; i++)
				{
					
					frontside += GetNewSensorValue(FL_SENSOR);
					rearside += GetNewSensorValue(L_SENSOR);
					
				}
				frontside = frontside/100;
				rearside = rearside/100;
				frontside = frontside-rearside;
				if(frontside > -100)
				{
					MotorStop();
					BGM = 1;
					delay_ms(100);
					return;
				}
			}

		}
		else
		{
			
			BGM = 1;
			delay_ms(100);
			return;

			
		}
		
	}
	

	
	
}
/*
void BGM_Parallel(void)
{
	

	int diffsidesensor //앞쪽 사이드 센서와 뒤쪽 사이드 센서 차이
	
	
	
	if(Direction == D_LEFT)
	{
		
		diffsidesensor = Diffsidesensor();
		
		
		if(diffsidesensor>100)
		{
			BL_MotorRotateR(BLOCKZIGZAG,0);
			while(1)
			{
				diffsidesensor = Diffsidesensor();
				if(diffsidesensor < 100)
				{
					MotorStop();
					BGM = 1;
					delay_ms(100);
					return;
				}
				
			}
			
		}
		else if(diffsidesensor <-100)
		{
			BL_MotorRotateL(0,BLOCKZIGZAG);
			while(1)
			{
				diffsidesensor = Diffsidesensor();
				if(diffsidesensor > -100)
				{
					MotorStop();
					BGM = 1;
					delay_ms(100);
					
					return;
				}
				
			}

		}
		else
		{

			BGM = 1;
			delay_ms(100);
			return;

			
		}
		
	}
	else if(Direction == D_RIGHT)
	{
		
		diffsidesensor = Diffsidesensor();
		
		if(diffsidesensor>100)
		{
			BL_MotorRotateL(0,BLOCKZIGZAG);
			while(1)
			{
				diffsidesensor = Diffsidesensor();
				if(diffsidesensor < 100)
				{
					MotorStop();
					BGM = 1;
					delay_ms(100);
					return;
				}
			}
			
		}
		else if(diffsidesensor <-100)
		{
			BL_MotorRotateR(BLOCKZIGZAG,0);
			while(1)
			{
				diffsidesensor = Diffsidesensor();
				if(diffsidesensor > -100)
				{
					MotorStop();
					BGM = 1;
					delay_ms(100);
					return;
				}
			}

		}
		else
		{
			
			BGM = 1;
			delay_ms(100);
			return;

			
		}
		
	}
	

	
	
}
*/


void Data_save(void)
{


		
	afdata.agedata.bgdata[0].gameruntime[0] = (blockGameTime / 1000)+'0';
	afdata.agedata.bgdata[0].gameruntime[1] = ((blockGameTime % 1000)/100)+'0';
	afdata.agedata.bgdata[0].gameruntime[2] = ((blockGameTime % 100)/10)+'0';
	afdata.agedata.bgdata[0].gameruntime[3] = ((blockGameTime % 10)/1)+'0';
	
	afdata.agedata.bgdata[0].gameblockcount[0] =  ((blockGameBlockCount % 1000)/100)+'0';
	afdata.agedata.bgdata[0].gameblockcount[1] = ((blockGameBlockCount % 100)/10)+'0';
	afdata.agedata.bgdata[0].gameblockcount[2] = ((blockGameBlockCount % 10)/1)+'0';
		

}


void Data_send(void)
{
	
	

	
	char sendmsg [] = "AE$|3|6|30|00000000|0000|0000000000|0000|000|E@";

	

	
	sendmsg[11] = afdata.agedata.bgdata[0].gamestartdate[0];
	sendmsg[12] = afdata.agedata.bgdata[0].gamestartdate[1];
	sendmsg[13] = afdata.agedata.bgdata[0].gamestartdate[2];
	sendmsg[14] = afdata.agedata.bgdata[0].gamestartdate[3];
	sendmsg[15] = afdata.agedata.bgdata[0].gamestartdate[4];
	sendmsg[16] = afdata.agedata.bgdata[0].gamestartdate[5];
	sendmsg[17] = afdata.agedata.bgdata[0].gamestartdate[6];
	sendmsg[18] = afdata.agedata.bgdata[0].gamestartdate[7];
	
	sendmsg[20] = afdata.agedata.bgdata[0].gamestarttime[0];
	sendmsg[21] = afdata.agedata.bgdata[0].gamestarttime[1];
	sendmsg[22] = afdata.agedata.bgdata[0].gamestarttime[2];
	sendmsg[23] = afdata.agedata.bgdata[0].gamestarttime[3];

	sendmsg[25] = afdata.agedata.bgdata[0].studentID[0];
	sendmsg[26] = afdata.agedata.bgdata[0].studentID[1];
	sendmsg[27] = afdata.agedata.bgdata[0].studentID[2];
	sendmsg[28] = afdata.agedata.bgdata[0].studentID[3];
	sendmsg[29] = afdata.agedata.bgdata[0].studentID[4];
	sendmsg[30] = afdata.agedata.bgdata[0].studentID[5];
	sendmsg[31] = afdata.agedata.bgdata[0].studentID[6];
	sendmsg[32] = afdata.agedata.bgdata[0].studentID[7];
	sendmsg[33] = afdata.agedata.bgdata[0].studentID[8];
	sendmsg[34] = afdata.agedata.bgdata[0].studentID[9];
	
	sendmsg[36] = afdata.agedata.bgdata[0].gameruntime[0];
	sendmsg[37] = afdata.agedata.bgdata[0].gameruntime[1];
	sendmsg[38] = afdata.agedata.bgdata[0].gameruntime[2];
	sendmsg[39] = afdata.agedata.bgdata[0].gameruntime[3];
	
	sendmsg[41] = afdata.agedata.bgdata[0].gameblockcount[0];
	sendmsg[42] = afdata.agedata.bgdata[0].gameblockcount[1];
	sendmsg[43] = afdata.agedata.bgdata[0].gameblockcount[2];
	
	BT_SendString(sendmsg);


}
