#include "platform_config.h"
#include "button.h"


bool bAction = false;



void Button_Action(bool * bAction)
{
	static uint8_t b_key = 0;
	
	if(*bAction)
	{
		
		
		
		if(!(GPIO_ReadInputDataBit(GPIOC, GPIO_Pin_14)))
		{
			b_key = 0;
			
			
			if(button_time > 20)
			{
				b_key = 1;  //short button
			}
			
			if(button_time > 2000)
			{
				b_key = 2; // long button
			}

		}
		else
		{
			
			*bAction = false;

			
			if(b_key == 1)// short button
			{
				DPRINTF("%s\r\n", "Button Action 1");
				if(BT_ConnectionIs)
				{
					
				}
				else
				{
					if(blockGameAction)
					{
						BlockGameStop();
					}
					else
					{
						BlockGameStart();
					}
				}
			}
			else if(b_key == 2)
			{
				//No Action
				DPRINTF("%s\r\n", "Button Action 2");
			}
			else
			{
				//No Action
				DPRINTF("%s\r\n", "Button Action 0");
			}
			
			ledAction = true;
			
		}
		
		
		
		
		
		
	}
	else
	{
		
		
		
		
	}
	
	
	
	
	
	
}
