#include "platform_config.h"
#include "bluetooth.h"
void BT_MessageParsing(BT_Data * btdata);
void PHONE_MessageParsing(BT_Data * btdata);
uint8_t bltAction = 0;
uint32_t BT_DataPointer = 0;
BT_Data btdata[5];

bool BT_ConnectionIs = false;
void Bluetooth_Action(uint8_t * bltAction)
{
	
	if(*bltAction)
	{
		int i;
		
		for(i=0 ; i<5 ; i++)
		{
			
			if((*bltAction)&(1<<i))
			{
				
				if(btdata[i].datatype == PHONE_DATA) 
				{
					
					PHONE_MessageParsing(&btdata[i]);
				}
				else  // BT_DATA
				{
					
					BT_MessageParsing(&btdata[i]);
					
				}
				(*bltAction)&=~(1<<i);
			}
		}
		
		
		
		
	}
	
}
void BT_SendData(uint8_t * buffer, uint16_t length)
{
	
	int i;
	
	for(i=0; i<length; i++)
	{

	
		while(!USART_GetFlagStatus(BLUETOOTH_USART, USART_FLAG_TXE));
		USART_SendData(BLUETOOTH_USART, buffer[i]);
	}
}

void BT_SendString(char string[])
{
	
	uint8_t * str = (uint8_t *) string;

			
	if(BT_ConnectionIs)
	{		
		while(*str)
		{
			while(!USART_GetFlagStatus(BLUETOOTH_USART, USART_FLAG_TXE));
			USART_SendData(BLUETOOTH_USART, *str++);
		}
	}

}
void BT_SendStringOff(char string[])
{
	
	uint8_t * str = (uint8_t *) string;

		
	while(*str)
	{
		while(!USART_GetFlagStatus(BLUETOOTH_USART, USART_FLAG_TXE));
		USART_SendData(BLUETOOTH_USART, *str++);
	}
	

}
void BT_MessageParsing(BT_Data * btdata)
{
	
	//btdata->data[btdata->datalength] = 0;
	//DPRINTF("%s",btdata->data);
	//DPRINTF("%s\r\n", "BT Message");

	if(btdata->datalength < 6) //BT 명령 아님
	{
		
		return;
	}
	
	
	if(btdata->data[6] == 'C')
	{
		
		if(btdata->data[16]  == 'U')
		{
			MelodyStart(BTCONNECTMELODY);
			
			DPRINTF("%s\r\n", "BT ConnectionUp(Android)");
			BT_ConnectionIs = true;
			Team_Color = 0;
			ledAction = true;
			Game_Mode = GAMEMODE_NONE;
			if(afdata.agedata.bgdata[0].flag[0] == 2)
			{
				Data_send();
			}
			else if(afdata.agedata.bgdata[0].flag[0] == 0xff)
			{
				afdata.agedata.bgdata[0].flag[0] = 0;
			}
			BlockGameStop();
			
			
		}
		if(btdata->data[16]  == 'D')
		{
			MelodyStart(BTDISCONNECTMELODY);
			DPRINTF("%s\r\n", "BT ConnectionDown(Android)");
			BT_ConnectionIs = false;
			Team_Color = 0;
			ledAction = true;
			BlockGameStop();
		}
	}
	if(btdata->data[11] == 'C')
	{
		
		if(btdata->data[21]  == 'U')
		{
			MelodyStart(BTCONNECTMELODY);
			
			DPRINTF("%s\r\n", "BT ConnectionUp(iOS)");
			BT_ConnectionIs = true;
			Team_Color = 0;
			ledAction = true;
			Game_Mode = GAMEMODE_NONE;
			if(afdata.agedata.bgdata[0].flag[0] == 2)
			{
				Data_send();
			}
			else if(afdata.agedata.bgdata[0].flag[0] == 0xff)
			{
				afdata.agedata.bgdata[0].flag[0] = 0;
			}
			BlockGameStop();
			
			
		}
		if(btdata->data[21]  == 'D')
		{
			MelodyStart(BTDISCONNECTMELODY);
			DPRINTF("%s\r\n", "BT ConnectionDown(iOS)");
			BT_ConnectionIs = false;
			Team_Color = 0;
			ledAction = true;
			BlockGameStop();
		}
	}
	if(btdata->data[6]  == 'B' && btdata->data[7] == 'D' && btdata->data[8]  == 'A' &&btdata->data[9]  == 'd' &&btdata->data[10]  == 'd' )
	{
		
		DPRINTF("%s\r\n", "BT Ready");
		//BT_SendStringOff("at+ab config DeviceName = ");
		//BT_SendData((uint8_t *)afdata.agedata.SerialNumber,15);
		//BT_SendString("\r\n");
		//BT_SendStringOff("at+ab config DeviceName = QUUQ-1160300305\r\n");
		if(afdata.agedata.Isbluetoothdata != 0)
		{
			afdata.agedata.Isbluetoothdata = 0;
			
			//vTaskDelay(500);
			//Flash_write();
			//printf("send\r\n");
		}
	}
	
	
	
}

void PHONE_MessageParsing(BT_Data * btdata)
{
	static uint8_t Tmode = 0;
	//btdata->data[btdata->datalength] = 0;
	//DPRINTF("%s",btdata->data);
	//DPRINTF("%s\r\n", "Phone Message");
	if(Team_Color &&  Game_Mode == GAMEMODE_MULTIMODE && btdata->data[MESSAGE_ID] == ID_MOTOR)  //motor control
	{
		
		
		if(btdata->data[MESSAGE_CMD0] == CMD0_MOTOR_JEONJIN)
		{

			MelodyOff();
			MotorJeonJin(btdata->data[MESSAGE_DATA1]-'0');
			//MotorJeonJin(9);
		}
		if(btdata->data[MESSAGE_CMD0] == CMD0_MOTOR_HOOJIN)
		{
			
			if(MELODY != HOOJINMELODY)
			{
				MelodyStart(HOOJINMELODY);
			}

			MotorHooJin(btdata->data[MESSAGE_DATA1]-'0');

		}
		if(btdata->data[MESSAGE_CMD0] == CMD0_MOTOR_ROTATE)
		{
			if(btdata->data[MESSAGE_DATA1]==DATA1_ROTATIONSTOP)
			{

				
				MotorRotateStop();
				
			}
			if(btdata->data[MESSAGE_DATA1]==DATA1_L_ROTATION)
			{
				

				
				MotorRotateL(MOTOR_SPEED_ROTATE_DIV);
				if(MELODY != HOOJINMELODY)
				{
					MelodyStart(ROTATEMELODY);
				}

			}
			if(btdata->data[MESSAGE_DATA1]==DATA1_R_ROTATION)
			{
				

				
				
				MotorRotateR(MOTOR_SPEED_ROTATE_DIV);
				if(MELODY != HOOJINMELODY)
				{
					MelodyStart(ROTATEMELODY);
				}

			}
		}
		
		
	}
	if(btdata->data[MESSAGE_ID] == ID_REQUEST) // requeset from phone
	{
		if(btdata->data[MESSAGE_CMD0] == CMD0_REQUESET_GAMEMODE) //game mode 0: NONE, 1: BLOCK, 2: MULTI
		{
			if(btdata->data[MESSAGE_DATA1] == DATA1_GAMEMODE_NONE)
			{
				Game_Mode = GAMEMODE_NONE;
				
			}
			if(btdata->data[MESSAGE_DATA1] == DATA1_GAMEMODE_BLOCK)
			{
				Game_Mode = GAMEMODE_BLOCKGAME;
				
				
			}
			if(btdata->data[MESSAGE_DATA1] == DATA1_GAMEMODE_MULTI)
			{
				Game_Mode = GAMEMODE_MULTIMODE;
				
				
			}
			BT_SendString("AE$|3|2|10|1|E@");
		}
		if(btdata->data[MESSAGE_CMD0] == CMD0_REQUESET_BLOCKGAME) 
		{
			if(btdata->data[MESSAGE_CMD1] == CMD1_BLOCKGAME_READY && afdata.agedata.bgdata[0].flag[0] == 0)//block game ready
			{
				if(Game_Mode ==GAMEMODE_BLOCKGAME)
				{
					
					afdata.agedata.bgdata[0].flag[0]  = 1;
					
					afdata.agedata.bgdata[0].gamestartdate[0] = btdata->data[11];
					afdata.agedata.bgdata[0].gamestartdate[1] = btdata->data[12];
					afdata.agedata.bgdata[0].gamestartdate[2] = btdata->data[13];
					afdata.agedata.bgdata[0].gamestartdate[3] = btdata->data[14];
					afdata.agedata.bgdata[0].gamestartdate[4] = btdata->data[15];
					afdata.agedata.bgdata[0].gamestartdate[5] = btdata->data[16];
					afdata.agedata.bgdata[0].gamestartdate[6] = btdata->data[17];
					afdata.agedata.bgdata[0].gamestartdate[7] = btdata->data[18];
					
					afdata.agedata.bgdata[0].gamestarttime[0] = btdata->data[20];
					afdata.agedata.bgdata[0].gamestarttime[1] = btdata->data[21];
					afdata.agedata.bgdata[0].gamestarttime[2]= btdata->data[22];
					afdata.agedata.bgdata[0].gamestarttime[3] = btdata->data[23];
					
					afdata.agedata.bgdata[0].studentID[0] = btdata->data[25];
					afdata.agedata.bgdata[0].studentID[1] = btdata->data[26];
					afdata.agedata.bgdata[0].studentID[2] = btdata->data[27];
					afdata.agedata.bgdata[0].studentID[3] = btdata->data[28];
					afdata.agedata.bgdata[0].studentID[4] = btdata->data[29];
					afdata.agedata.bgdata[0].studentID[5] = btdata->data[30];
					afdata.agedata.bgdata[0].studentID[6] = btdata->data[31];
					afdata.agedata.bgdata[0].studentID[7] = btdata->data[32];
					afdata.agedata.bgdata[0].studentID[8] = btdata->data[33];
					afdata.agedata.bgdata[0].studentID[9] = btdata->data[34];

					BlockGameReady();
					BT_SendString("AE$|3|2|20|1|E@");
				}
				else
				{
					BT_SendString("AE$|3|2|20|0|E@");
				}
			}
			if(btdata->data[MESSAGE_CMD1] == CMD1_BLOCKGAME_START)//block game start
			{
				if(Game_Mode==GAMEMODE_BLOCKGAME&&Block_Game_Mode==BLOCKGAMEMODE_READY)
				{
					BlockGameStart();
				}
				else
				{
					BT_SendString("AE$|3|2|21|0|E@");
				}
				
			}
			if(btdata->data[MESSAGE_CMD1] == CMD1_BLOCKGAME_STOP)//machine stop
			{
				if(Block_Game_Mode!=BLOCKGAMEMODE_NONE)
				{
					BlockGameStop();
					afdata.agedata.bgdata[0].flag[0] = 0;
					BT_SendString("AE$|3|2|22|1|E@");
				}
				else
				{
					BT_SendString("AE$|3|2|22|0|E@");
				}
			}
			
		}
		if(btdata->data[MESSAGE_CMD0] == CMD0_REQUESET_GAMEDATA) 
		{
			if(btdata->data[MESSAGE_CMD1] == CMD1_GAMEDATA_REQUEST)// data request
			{
				if(btdata->data[MESSAGE_DATA1] == DATA1_GAMEDATA_REQUEST_FAIL)
				{
					
					BlockGameStop();
					afdata.agedata.bgdata[0].flag[0] = 0;
					
				}
				if(btdata->data[MESSAGE_DATA1]==DATA1_GAMEDATA_REQUEST_SUCCESS)
				{
					BlockGameStop();
					afdata.agedata.bgdata[0].flag[0] = 2;
					Data_save();
					if(afdata.agedata.bgdata[0].flag[0] ==2)
					{
						Data_send();
						
					}
				}
				
			}
			if(btdata->data[MESSAGE_CMD1] == CMD1_GAMEDATA_DELETE)//data delete
			{
				
				if(afdata.agedata.bgdata[0].flag[0] !=0)
				{
					afdata.agedata.bgdata[0].flag[0] = 0;
					Flash_write();
					BT_SendString("AE$|3|2|31|1|E@");
				}
				else
				{
					BT_SendString("AE$|3|2|31|0|E@");
				}
				
			}
		}
		if(btdata->data[MESSAGE_CMD0] == CMD0_REQUESET_TEAMSET) //team setting
		{
			if(Game_Mode==GAMEMODE_MULTIMODE)
			{
					
				
				if(btdata->data[MESSAGE_DATA1]==DATA1_TEAMSET_NONE)
				{
					Team_Color = TEAMCOLOR_NOTHING;
				}
				if(btdata->data[MESSAGE_DATA1]==DATA1_TEAMSET_RED)
				{
					Team_Color = TEAMCOLOR_RED;
				}
				if(btdata->data[MESSAGE_DATA1]==DATA1_TEAMSET_BLUE)
				{
					Team_Color = TEAMCOLOR_BLUE;
				}
				if(btdata->data[MESSAGE_DATA1]==DATA1_TEAMSET_GREEN)
				{
					Team_Color = TEAMCOLOR_GREEN;
				}
				
				//BT_SendString("AE$|3|2|40|1|E@");
			}
			else
			{
				BT_SendString("AE$|3|2|40|0|E@");
			}
			
		}
		if(btdata->data[MESSAGE_CMD0] == CMD0_REQUEST_BAT) //battery status
		{
			Battery_Check('3');
		}
	
	}
	
	
	
	if(btdata->data[MESSAGE_ID] == ID_CALIBRATION) //calibration
	{
		if(btdata->data[MESSAGE_CMD0] == '1')
		{
			if(btdata->data[MESSAGE_DATA1] == '0')
			{
				IRSENSOR_OFF();
				BT_SendString("AE$|8|E@");
			}
			else if(btdata->data[MESSAGE_DATA1] == '1')
			{
				IRSENSOR_ON();
				BT_SendString("AE$|8|E@");
			}
			
			
		}			
		else if(btdata->data[MESSAGE_CMD0] == '2')
		{
			
			
			IRSensor_CalibrationF();
			BT_SendString("AE$|8|E@");
			
		}
		else if(btdata->data[MESSAGE_CMD0] == '3')
		{
			
			
			IRSensor_Calibration(((btdata->data[11]-'0')*10)+((btdata->data[12]-'0')));
			BT_SendString("AE$|8|E@");
			
			
		}
		else if(btdata->data[MESSAGE_CMD0] == '4')
		{
			
			if(btdata->data[MESSAGE_DATA1] == '1')
			{
				IRSensor_DataWrite();
				Flash_write();
				BT_SendString("AE$|8|E@");
			}
			
		}
	}
	if(btdata->data[MESSAGE_ID] == ID_TEST) //test
	{
		
		
		if(btdata->data[12] == '1')
		{
			
			if(Tmode == 0)
			{
				Tmode = 1;
				BT_SendString("Fsensor");
			}
			else
			{
				Tmode = 0;
				BT_SendString("Motor");
			}

		}
		
		
		
		if(btdata->data[12] == '2')
		{

			if(Tmode == 0)
			{
				Motor_DataWrite();
			}
			else
			{
				F_Sensor -= 5;
				afdata.agedata.sdata.f_sensor = F_Sensor;
				BT_SendString("-Ok");
			}

			
		}
		if(btdata->data[12] == '3')
		{

			if(Tmode == 0)
			{
				Flash_write();
			}
			else
			{
				
				F_Sensor += 5;
				afdata.agedata.sdata.f_sensor = F_Sensor;
				BT_SendString("-Ok");
			}
			
		}
		
	}
	
	
	
	ledAction = true;
}

