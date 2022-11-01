

#include "platform_config.h"
#include "MelodyData.h"
#include "melody.h"




extern TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure3;
extern TIM_OCInitTypeDef  TIM_OCInitStructure3;

bool MelodyOn = false;
int MELODY;
uint32_t MelodyTimer = 0;
uint32_t MelodyPointer = 0;
Melody  m;
uint16_t * MelodyToneArray [15] = {StartMelodyTone, RotateMelodyTone, HooJinMelodyTone};
uint16_t * MelodyTimeArray [15] =  {StartMelodyTime, RotateMelodyTime, HooJinMelodyTime};





void MelodyStart(int melody)
{
	
	MELODY = melody;
	
	switch(melody)
	{
		case STARTMELODY:
			m.Length = sizeof(StartMelodyTone)/sizeof(uint16_t);
			m.MelodyTime = &StartMelodyTime[0];
			m.MelodyTone = &StartMelodyTone[0];
			m.Continue = 0;
			break;
		
		case ROTATEMELODY:
			m.Length = sizeof(RotateMelodyTone)/sizeof(uint16_t);
			m.MelodyTime = &RotateMelodyTime[0];
			m.MelodyTone = &RotateMelodyTone[0];
			m.Continue = 0;
			break;
		
		case HOOJINMELODY:
			m.Length = sizeof(HooJinMelodyTone)/sizeof(uint16_t);
			m.MelodyTime = &HooJinMelodyTime[0];
			m.MelodyTone = &HooJinMelodyTone[0];
			m.Continue = 1;
			break;
		
		case PARINGMELODY:
			m.Length = sizeof(ParingMelodyTone)/sizeof(uint16_t);
			m.MelodyTime = &ParingMelodyTime[0];
			m.MelodyTone = &ParingMelodyTone[0];
			m.Continue = 0;
			break;
		case SUCCESSMELODY:
			m.Length = sizeof(SuccessMelodyTone)/sizeof(uint16_t);
			m.MelodyTime = &SuccessMelodyTime[0];
			m.MelodyTone = &SuccessMelodyTone[0];
			m.Continue = 0;
			break;
		case BTCONNECTMELODY:
			m.Length = sizeof(BTConnectMelodyTone)/sizeof(uint16_t);
			m.MelodyTime = &BTConnectMelodyTime[0];
			m.MelodyTone = &BTConnectMelodyTone[0];
			m.Continue = 0;
			break;
		case BTDISCONNECTMELODY:
			m.Length = sizeof(BTDisconnectMelodyTone)/sizeof(uint16_t);
			m.MelodyTime = &BTDisconnectMelodyTime[0];
			m.MelodyTone = &BTDisconnectMelodyTone[0];
			m.Continue = 0;
			break;
		case BLOCKDETECTMELODY:
			m.Length = sizeof(BlockDetectMelodyTone)/sizeof(uint16_t);
			m.MelodyTime = &BTDisconnectMelodyTime[0];
			m.MelodyTone = &BTDisconnectMelodyTone[0];
			m.Continue = 0;
			break;
		case BLOCKHOOJINMELODY:
			m.Length = sizeof(BlockHoojinMelodyTone)/sizeof(uint16_t);
			m.MelodyTime = &BlockHoojinMelodyTime[0];
			m.MelodyTone = &BlockHoojinMelodyTone[0];
			m.Continue = 0;
			break;
		case BLOCKPARALLELMELODY:
			m.Length = sizeof(BlockParallelMelodyTone)/sizeof(uint16_t);
			m.MelodyTime = &BlockParallelMelodyTime[0];
			m.MelodyTone = &BlockParallelMelodyTone[0];
			m.Continue = 0;
			break;
	}
	
	MelodyOn = true ;
	MelodyTimer = 0;
	MelodyPointer = 0;
	TIM_SetCounter(TIM2, 0);
	Buzzer_sound(m.MelodyTone[0]);
	TIM_Cmd(TIM2, ENABLE);
	
	
	
}

void Buzzer_sound(int value)
{
	uint16_t period;
	period = (1000000/value);
	TIM_TimeBaseStructure3.TIM_Period = period;
	TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure3);
	TIM_OCInitStructure3.TIM_Pulse = period/2;
	TIM_OC1Init(TIM3, &TIM_OCInitStructure3);
}




void MelodyOff(void)
{
	MELODY = NONEMELODY;
	MelodyOn = false;
	MelodyTimer = 0;
	MelodyPointer = 0;
	TIM_Cmd(TIM2, DISABLE);
	TIM_OCInitStructure3.TIM_Pulse = 0;
	TIM_OC1Init(TIM3, &TIM_OCInitStructure3);

}



