#include "platform_config.h"
#include "stm32f10x_it.h"
extern uint32_t BatteryCheckTime;
uint8_t btreceivedata;
uint32_t pdatacount = 0;
void USART1_IRQHandler(void)  //디버그 통신
{

	static uint8_t receivedata;
	
	if(USART_GetITStatus(USART1, USART_IT_RXNE) != RESET)
	{
		receivedata = USART_ReceiveData(USART1);
		while(USART_GetFlagStatus(USART2, USART_FLAG_TXE) == RESET);
 			USART_SendData(USART2, receivedata);
		USART_ClearITPendingBit(USART1, USART_IT_RXNE); //PendingBit Ŭخ߮
	}



}

void USART2_IRQHandler(void) //블루투스 통신
{

	if(USART_GetITStatus(USART2, USART_IT_RXNE) != RESET)
	{
		
		btreceivedata = USART_ReceiveData(USART2);
		// while(USART_GetFlagStatus(USART1, USART_FLAG_TXE) == RESET);
 		//	USART_SendData(USART1, btreceivedata);
		btdata[BT_DataPointer].data[pdatacount] = btreceivedata;
		pdatacount++;
		
		if(btreceivedata == '@')
		{
			btdata[BT_DataPointer].datalength = pdatacount;
			btdata[BT_DataPointer].datatype = PHONE_DATA;
			bltAction |= (1<<BT_DataPointer);
			pdatacount = 0;
			BT_DataPointer++;
		}
		else if(btreceivedata == '\n')
		{
			btdata[BT_DataPointer].datalength = pdatacount;
			btdata[BT_DataPointer].datatype = BT_DATA;
			bltAction |= (1<<BT_DataPointer);
			pdatacount = 0;
			BT_DataPointer++;
		}
		if(BT_DataPointer>4)
		{
			BT_DataPointer = 0;
		}
		
		USART_ClearITPendingBit(USART2, USART_IT_RXNE); //PendingBit Ŭخ߮

	}

}

void TIM2_IRQHandler(void) // 타이머 ms
{

	if(TIM_GetITStatus(TIM2,TIM_IT_Update) != RESET)
	{
		
		if(MelodyOn)
		{
			
			MelodyTimer ++ ;
			if(MelodyTimer == m.MelodyTime[MelodyPointer])
			{
				
				MelodyTimer = 0;
				MelodyPointer ++;
				
				if(MelodyPointer == m.Length)
				{
					if(m.Continue)
					{
						MelodyPointer = 0;
						Buzzer_sound(m.MelodyTone[0]);
						
					}
					else
					{
						MelodyOff();
						
					}
				}
				else
				{
					
					Buzzer_sound(m.MelodyTone[MelodyPointer]);
				}
				
				
			}
			
			
			
		}
		else
		{
			
			MelodyOff();
		}
		
		

		TIM_ClearITPendingBit(TIM2,TIM_IT_Update);

	}

}


void EXTI15_10_IRQHandler(void) //버튼 인터럽트
{
	



	if(EXTI_GetITStatus(EXTI_Line14) != RESET)
	{


		bAction = true;
		button_time = 0;
		EXTI_ClearITPendingBit(EXTI_Line14);
	}


}

void SysTick_Handler(void)
{ 
	
	
	delay_time--;
	button_time++;
	hoojintime ++;
	gyro_time++;
	ledtime++;
	if(gametime++ == 1000)
	{
		BatteryCheckTime++;
		gametime = 0;
		blockGameTime++;
		
	}
}




