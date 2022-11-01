/**
  ******************************************************************************
  * @file    miscellaneous.c 
  * @author  MMY Application Team
  * @version V1.1
  * @date    15/03/2011
  * @brief   miscellaneaous functions
  ******************************************************************************
  * @copy
  *
  * THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
  * WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE
  * TIME. AS A RESULT, STMICROELECTRONICS SHALL NOT BE HELD LIABLE FOR ANY
  * DIRECT, INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING
  * FROM THE CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE
  * CODING INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
  *
  * <h2><center>&copy; COPYRIGHT 2011 STMicroelectronics</center></h2>
  */ 

#include "miscellaneous.h"
uint16_t counter_delay_ms;
extern uint32_t delay_time;
/** @addtogroup MISC
 * 	@{
 */


/**  
 * @brief  returns the char correspondint to the int value
 * @param  Line : the Line to be cleared.
 *   This parameter can be @e LineX: where X can be 0..9
 * @retval None
 */
uint8_t HexIntToChar (uint8_t HexInt)
{
	
   HexInt = HexInt & 0x0F;
   switch (HexInt)
   {
   		case 0 : 
			return '0';
		case 1 : 
			return '1'; 
		case 2 : 
			return '2';
		case 3 : 
			return '3';
		case 4 : 
			return '4'; 
		case 5 : 
			return '5';
		case 6 : 
			return '6'; 
		case 7 : 
			return '7';
		case 8 : 
			return '8'; 
		case 9 : 
			return '9';
		case 10 : 
			return 'A'; 
		case 11 : 
			return 'B';
		case 12 : 
			return 'C'; 
		case 13 : 
			return 'D'; 
		case 14 : 
			return 'E';
		case 15 : 
			return 'F'; 
		default : return 'x';
	}
}

/**  
 * @brief  returns the char correspondint to the int value
 * @param  Line : the Line to be cleared.
 *   This parameter can be @e LineX: where X can be 0..9
 * @retval None
 */
int8_t HexToString (uint8_t *HexString,uint8_t NbVal,uint8_t *ASCIIString)
{
uint8_t NthVal;
 	
	ASCIIString[0]=0x00;
	if (NbVal==0)
		return ERRORCODE_GENERIC;
		
	for (NthVal=0;NthVal<NbVal;NthVal++)
	{
		ASCIIString[2*NthVal+1] = HexIntToChar (HexString[NthVal] & 0x0F);
		ASCIIString[2*NthVal] = HexIntToChar ((HexString[NthVal]& 0xF0)>>4 );
	}	

	return RESULTOK;

}

/**  
 * @brief  
 * @param  
 * @retval None
 */
u8* itoa(u32 val, u8 base )
{            
static u8 buf[32] = {0};  // 32 bits
int i = 30;

	for(; val && i ; --i, val /= base)
	 	buf[i] = "0123456789abcdef"[val % base];

	return &buf[i+1];
}

/**  
 * @brief  this function return a 2 byte word from a array of 1 byte
 * @param  data : 1 byte word
 * @retval value on 2 bytes
 */
uint16_t Uint8ToUint16 (uc8 *data)
{
 	
   	return ( (data [1]<<8) | data [0] );

}

/**  
 * @brief  this function return a 2 byte word from a array of 1 byte
 * @param  data : 1 byte word
 * @retval value on 2 bytes
 */
void Uint16ToUint8 (uc16 data,uint8_t *uint8tab)
{
 	
   	uint8tab [0] = data & 0xFF;
	uint8tab [1] = (data>>8) & 0xFF;

}

/**  
 * @brief  this function return a 4 byte word from a array of 1 byte
 * @param  data : 1 byte word
 * @retval value on 4 bytes
 */
uint32_t Uint8ToUint32 (uc8 *data)
{
 	
   	return ( (data [3]<<24) | (data [2]<<16) | (data [1]<<8) | data [0] );

}

/**  
 * @brief  this function return a 2 byte word from a array of 1 byte
 * @param  data : 1 byte word
 * @retval value on 2 bytes
 */
void Uint32ToUint8 (uc32 data,uint8_t *uint8tab)
{
 	
   	uint8tab [0] = data & 0xFF;
	uint8tab [1] = (data>>8) & 0xFF;
	uint8tab [2] = (data>>16) & 0xFF;
	uint8tab [3] = (data>>24) & 0xFF;

}

void delay_ms(uint16_t delay)
{
	delay_time = delay;
	while(delay_time)
	{
		
	}
	
}
/******************* (C) COPYRIGHT 2011 STMicroelectronics *****END OF FILE****/

float Kalman_Filter( float Source_Value, float *X, float *P, float Q, float R )
{
	float g_K;

	// predict..
	float g_xPredict = *X;
	float g_pPredict = *P + Q;

	// correct..
	g_K = g_pPredict / ( g_pPredict + R );
	*X = g_xPredict + ( g_K * ( Source_Value - g_xPredict ) );
	*P = ( 1 - g_K ) * g_pPredict;

	return *X;
}

