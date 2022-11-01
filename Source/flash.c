#include "platform_config.h"
#include "flash.h"

#define FLASH_PAGE_SIZE    ((uint16_t)0x400)
#define BANK1_WRITE_START_ADDR  ((uint32_t)0x0801FC00)
#define BANK1_WRITE_END_ADDR    ((uint32_t)0x08020000)


typedef enum {FAILED = 0, PASSED = !FAILED} TestStatus;

age1000_flash_data afdata;


uint32_t EraseCounter = 0x00, Address = 0x00;
uint32_t NbrOfPage = 0x00;


volatile FLASH_Status FLASHStatus = FLASH_COMPLETE;
volatile TestStatus MemoryProgramStatus = PASSED;



static void SensorData_Init(void)
{
	if(afdata.agedata.Issdata != 0)
	{
		
		afdata.agedata.Issdata = 0;
		IRSensor_DataWrite();
		
		
	}
	else
	{
		
		
		IRSensor_DataRead();
		
	}
}
static void BlockGameData_Init(void)
{
	
	if(afdata.agedata.Isbgdata != 0)
	{
		
		
		
	}
	else
	{
		
		
		
	}
	
}
static void MotorData_Init(void)
{
	int i;
	

		

	mv.motorlevelL[0] = 0;
	mv.motorlevelR[0] = 0;
	mv.BmotorlevelL[0] = 0;
	mv.BmotorlevelR[0] = 0;
	
	mv.motorlevelL[1] = MOTOR_SPEED_MIN_D;
	mv.motorlevelR[1] = MOTOR_SPEED_MIN_D;
	mv.BmotorlevelL[1] = MOTOR_SPEED_MIN_R;
	mv.BmotorlevelR[1] = MOTOR_SPEED_MIN_R;
	
	mv.motorlevelL[MOTOR_MAX_LEVEL] = MOTOR_SPEED_MAX_D;
	mv.motorlevelR[MOTOR_MAX_LEVEL] = MOTOR_SPEED_MAX_D;
	mv.BmotorlevelL[MOTOR_MAX_LEVEL] = MOTOR_SPEED_MAX_R;
	mv.BmotorlevelR[MOTOR_MAX_LEVEL] = MOTOR_SPEED_MAX_R;
	
	for(i=2;i<MOTOR_MAX_LEVEL ; i++)
	{
		
		mv.motorlevelL[i] = MOTOR_SPEED_MIN_D + (((MOTOR_SPEED_MAX_D - MOTOR_SPEED_MIN_D)/(MOTOR_MAX_LEVEL-1))*(i-1));
		mv.motorlevelR[i] = MOTOR_SPEED_MIN_D + (((MOTOR_SPEED_MAX_D - MOTOR_SPEED_MIN_D)/(MOTOR_MAX_LEVEL-1))*(i-1));
		mv.BmotorlevelL[i] = MOTOR_SPEED_MIN_R + (((MOTOR_SPEED_MAX_R - MOTOR_SPEED_MIN_R)/(MOTOR_MAX_LEVEL-1))*(i-1));
		mv.BmotorlevelR[i] = MOTOR_SPEED_MIN_R + (((MOTOR_SPEED_MAX_R - MOTOR_SPEED_MIN_R)/(MOTOR_MAX_LEVEL-1))*(i-1));
		
	}
		

	
	if(afdata.agedata.Ismdata != 0)
	{
		
		
		afdata.agedata.Ismdata = 0;
		Motor_DataWrite();
		
		
	}
	else
	{
		
		
		Motor_DataRead();
		
	}
	
}
static void GyroData_Init(void)
{
	int32_t sum=0;
	int i;
	
	if(afdata.agedata.Isgdata != 0)
	{
		
		afdata.agedata.Isgdata = 0;
		
		for(i=0 ; i<100 ; i++)
		{
			sum += get_Gyro_Z();
			delay_ms(2);
		}
		sum = (int32_t) (sum/100.0);
		afdata.agedata.gdata.gyro_z_offset = (int16_t)sum;
		Flash_write();
		
	}
	
}


void Flash_write(void)
{

	int i=0;

	FLASH_UnlockBank1();

	/* Define the number of page to be erased */
	NbrOfPage = (BANK1_WRITE_END_ADDR - BANK1_WRITE_START_ADDR) / FLASH_PAGE_SIZE;

	/* Clear All pending flags */
	FLASH_ClearFlag(FLASH_FLAG_EOP | FLASH_FLAG_PGERR | FLASH_FLAG_WRPRTERR);	

	/* Erase the FLASH pages */
	for(EraseCounter = 0; (EraseCounter < NbrOfPage) && (FLASHStatus == FLASH_COMPLETE); EraseCounter++)
	{
		FLASHStatus = FLASH_ErasePage(BANK1_WRITE_START_ADDR + (FLASH_PAGE_SIZE * EraseCounter));
	}

	/* Program Flash Bank1 */
	Address = BANK1_WRITE_START_ADDR;

	while((Address < BANK1_WRITE_END_ADDR) && (FLASHStatus == FLASH_COMPLETE))
	{
		FLASHStatus = FLASH_ProgramWord(Address, afdata.flashdata[i]);
		Address = Address + 4;
		i++;
	}

	FLASH_LockBank1();

	


}

void Flash_read(void)
{
	int i=0;
	Address = BANK1_WRITE_START_ADDR;

	while((Address < BANK1_WRITE_END_ADDR) )
	{
		afdata.flashdata[i]=(*(__IO uint32_t*) Address);
		Address += 4;
		i++;
	}
	

}

void AGE_Data_Init(void)
{
	
	//char ag[]="QUUQ-1160400002";
	//int i;
	SensorData_Init();
	BlockGameData_Init();
	MotorData_Init();
	GyroData_Init();
	//for(i=0 ; i<15 ; i++)
	//{
	//	afdata.agedata.SerialNumber[i] = ag[i];
	//}
	
	//Flash_write();
	
}








