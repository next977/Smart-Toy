#include "platform_config.h"

uint32_t BatteryCheckTime = 0;
uint32_t delay_time=0;
uint32_t button_time=0;
uint8_t Game_Mode = GAMEMODE_NONE;
uint8_t Block_Game_Mode = 0;
uint8_t Team_Color = TEAMCOLOR_NOTHING;

int main(void)
{
	

	//uint16_t test[5];
	Device_Init();
	LED_Control(LED_LEFT|LED_RIGHT, GREEN);
	DPRINTF("%s\r\n", "Device Init Complete");
	SysTick_Config(72000);
	
	
	
	Flash_read();
	DPRINTF("%s\r\n", "Flash Read Complete");
	
	MelodyStart(STARTMELODY);
	//MelodyStart(BTCONNECTMELODY);
	delay_ms(500);
	
	MPU6050_Initialize();
	DPRINTF("%s\r\n", "MPU6050 Init Complete");
	
	AGE_Data_Init();
	DPRINTF("AGE Data Size : %d Byte\r\n", sizeof(age1000_flash_data));
	DPRINTF("%s\r\n", "AGE1000 Data Init Complete");
	
	//LED_Control(LED_LEFT|LED_RIGHT, RED);
	ledAction = true;
	//IRSENSOR_ON();
	while(true)
	{
		
		Button_Action(&bAction);
		Bluetooth_Action(&bltAction);
		BlockGame_Action(&blockGameAction);
		Gyro_Action(&gyroAction);
		Led_Action(&ledAction);
		
		//battery time check . every 30sec
		if(BatteryCheckTime > 5)
		{
			BatteryCheckTime = 0;
			if(BT_ConnectionIs)
			{
				Battery_Check('4');
				DPRINTF("%s\r\n", "Bat Info Send");
			}
		}
		//test[0] = ADCConvertedValue[0];
		//test[1] = ADCConvertedValue[1];
		//test[2] = ADCConvertedValue[2];
		//test[3] = ADCConvertedValue[4];
		//test[4] = ADCConvertedValue[5];
		//printf("%d,%d,%d,%d,%d\r\n",test[0],test[1],test[2],test[3],test[4]);
		//delay_ms(100);
		
	}

	
	
}



//Use Printf
#pragma import(__use_no_semihosting_swi)
 
struct __FILE { int handle; /* Add whatever you need here */ };
FILE __stdout;
FILE __stdin;
 
int fputc(int ch, FILE *f)
{
    while(USART_GetFlagStatus(USART1, USART_FLAG_TXE) == RESET);
 
  USART_SendData(USART1, ch);
 
  return(ch);
}
 
int fgetc(FILE *f)
{
    char ch;
 
    while(USART_GetFlagStatus(USART1, USART_FLAG_RXNE) == RESET);
 
    ch = USART_ReceiveData(USART1);
 
  return((int)ch);
}
 
int ferror(FILE *f)
{
  /* Your implementation of ferror */
  return EOF;
}
 
void _ttywrch(int ch)
{
    while(USART_GetFlagStatus(USART1, USART_FLAG_TXE) == RESET);
 
  USART_SendData(USART1, ch);
}
 
void _sys_exit(int return_code)
{
label:  goto label;  /* endless loop */


}
