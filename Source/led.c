#include "led.h"
#include "platform_config.h"
uint32_t ledtime=0;
uint8_t togglekey = 0;
uint8_t rgbkey=0;
uint8_t rgbtime=0;
uint8_t rgbnum=0;
bool ledAction = false;
void Led_Action(uint8_t * ledAction)
{
	if(* ledAction)
	{
		if(BT_ConnectionIs)
		{
			if(Game_Mode == GAMEMODE_BLOCKGAME)
			{
				if(Block_Game_Mode == BLOCKGAMEMODE_READY)
				{
					if(ledtime > 500)
					{
						ledtime = 0;
						rgbkey = 1<<rgbtime;
						LED_Control((rgbnum&1)+1,rgbkey);
						rgbnum++;
						rgbtime++;
						if(rgbtime==3)
						{
							rgbtime=0;
						}
					}
					
				}
				else if(Block_Game_Mode == BLOCKGAMEMODE_RUN)
				{
					LED_Control(LED_LEFT|LED_RIGHT, RED|BLUE);
					*ledAction = false;
				}
				else if(Block_Game_Mode == BLOCKGAMEMODE_GOALIN)
				{
					
					
				}
				else if(Block_Game_Mode == BLOCKGAMEMODE_ERROR)
				{
					if(ledtime > 500)
					{
						ledtime = 0;
						if(togglekey)
						{
							LED_Control(LED_LEFT|LED_RIGHT, RED);
							togglekey = 0;
						}
						else
						{
							LED_Control(LED_LEFT|LED_RIGHT,0);
							togglekey = 1;
						}
					}
				}
				else
				{
					LED_Control(LED_LEFT|LED_RIGHT, BLUE|GREEN);
					*ledAction = false;
				}
			}
			else if(Game_Mode == GAMEMODE_MULTIMODE)
			{
				if(Team_Color == TEAMCOLOR_RED)
				{
					LED_Control(LED_LEFT|LED_RIGHT, RED);
					*ledAction = false;
				}
				else if(Team_Color == TEAMCOLOR_GREEN)
				{
					LED_Control(LED_LEFT|LED_RIGHT, GREEN);
					*ledAction = false;
				}
				else if(Team_Color == TEAMCOLOR_BLUE)
				{
					LED_Control(LED_LEFT|LED_RIGHT, BLUE);
					*ledAction = false;
					
				}
				else
				{
					if(ledtime > 500)
					{
						ledtime = 0;
						
						rgbkey = 1<<rgbtime;
						LED_Control(3,rgbkey);
						rgbtime++;
						if(rgbtime==3)
						{
							rgbtime=0;
						}
						
					}
				}
				
				
			}
			else
			{
				
				LED_Control(LED_LEFT|LED_RIGHT, BLUE|GREEN);
				*ledAction = false;
			}
			
			
		}
		else
		{
			if(Block_Game_Mode == BLOCKGAMEMODE_RUN)
			{
				LED_Control(LED_LEFT|LED_RIGHT, RED|BLUE);
				*ledAction = false;
			}
			else if(Block_Game_Mode == BLOCKGAMEMODE_GOALIN)
			{
				
				
			}
			else if(Block_Game_Mode == BLOCKGAMEMODE_ERROR)
			{
				if(ledtime > 500)
				{
					ledtime = 0;
					if(togglekey)
					{
						LED_Control(LED_LEFT|LED_RIGHT, RED);
						togglekey = 0;
					}
					else
					{
						LED_Control(LED_LEFT|LED_RIGHT,0);
						togglekey = 1;
					}
				}
			}
			else
			{
				LED_Control(LED_LEFT|LED_RIGHT, RED|BLUE|GREEN);
				*ledAction = false;
			}
		}
		
		if(mv.mStateRotate == ROTATE)
		{
			
			if(mv.mStateLRotate == LROTATE)
			{
				
				LED_Control(LED_LEFT, RED|GREEN);
				*ledAction = false;
				
			}
			else if(mv.mStateLRotate == RROTATE)
			{
				
				LED_Control(LED_RIGHT, RED|GREEN);
				*ledAction = false;
			}
			
		}
	}
}

void LED_Control(uint8_t side, uint8_t rgb)
{
	
	if(side == LED_LEFT)
	{
		GPIOA->ODR |= ((1<<11)|(1<<12)|(1<<15));
		
		GPIOA->ODR &= ~(((rgb&3)<<11)|((rgb&4)<<13));
		
		
	}
	else if(side == LED_RIGHT)
	{
		
		GPIOB->ODR |= ((1<<2)|(1<<3)|(1<<5));
		GPIOB->ODR &= ~(((rgb&3)<<2)|((rgb&4)<<3));
	}
	else
	{
		GPIOA->ODR |= ((1<<11)|(1<<12)|(1<<15));
		GPIOB->ODR |= ((1<<2)|(1<<3)|(1<<5));
		GPIOB->ODR &= ~(((rgb&3)<<2)|((rgb&4)<<3));
		GPIOA->ODR &= ~(((rgb&3)<<11)|((rgb&4)<<13));
	}
	
}


