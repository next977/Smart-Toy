#ifndef __BLUETOOTH_H__
#define __BLUETOOTH_H__
#include "platform_config.h"

#define BT_BUFFERSIZE 100
#define BT_DATA 0
#define PHONE_DATA 1



#define MESSAGE_ID 4
#define ID_MOTOR '1'
#define ID_REQUEST '2'
#define ID_RESPONSE '3'
#define ID_EVENT '4'
#define ID_CALIBRATION '8'
#define ID_TEST '9'

#define MESSAGE_LENGTH 6

#define MESSAGE_CMD0 8   //8,9  9=0
#define CMD0_MOTOR_JEONJIN '1'
#define CMD0_MOTOR_HOOJIN '2'
#define CMD0_MOTOR_ROTATE '3'

#define MESSAGE_CMD1 9
#define CMD0_REQUESET_GAMEMODE '1'
#define CMD0_REQUESET_BLOCKGAME '2'
	#define CMD1_BLOCKGAME_READY '0'
	#define CMD1_BLOCKGAME_START '1'
	#define CMD1_BLOCKGAME_STOP '2'


#define CMD0_REQUESET_GAMEDATA '3'
	#define CMD1_GAMEDATA_REQUEST '0'
	#define CMD1_GAMEDATA_DELETE '1'
	
#define CMD0_REQUESET_TEAMSET '4'
#define CMD0_REQUEST_BAT '5'

#define MESSAGE_DATA1 11
#define DATA1_ROTATIONSTOP '0'
#define DATA1_L_ROTATION '1'
#define DATA1_R_ROTATION '2'

#define DATA1_GAMEMODE_NONE '0'
#define DATA1_GAMEMODE_BLOCK '1'
#define DATA1_GAMEMODE_MULTI '2'

#define DATA1_TEAMSET_NONE '0'
#define DATA1_TEAMSET_RED '1'
#define DATA1_TEAMSET_BLUE '2'
#define DATA1_TEAMSET_GREEN '3'

#define DATA1_GAMEDATA_REQUEST_FAIL '0'
#define DATA1_GAMEDATA_REQUEST_SUCCESS '1'












typedef struct
{
	uint8_t datatype;
	uint8_t datalength;
	uint8_t data[100];
	
}BT_Data;
extern uint32_t BT_DataPointer;
extern BT_Data btdata[5];
extern uint8_t bltAction;
extern bool BT_ConnectionIs;
extern void Bluetooth_Action(uint8_t * bltAction);
extern void BT_SendData(uint8_t * buffer, uint16_t length);
extern void BT_SendString(char string[]);
extern void BT_SendStringOff(char string[]);
#endif // __BLUETOOTH_H__

