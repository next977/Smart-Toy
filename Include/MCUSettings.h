#ifndef __MCUSETTINGS_H
#define __MCUSETTINGS_H

#include "platform_config.h"


/* -- Bluetooth -- */

#define BLUETOOTH_USART       		USART2
#define BLUETOOTH_GPIO              	GPIOA
#define BLUETOOTH_CLK               		RCC_APB1Periph_USART2
#define BLUETOOTH_GPIO_CLK          	RCC_APB2Periph_GPIOA
#define BLUETOOTH_RxPin             	GPIO_Pin_3
#define BLUETOOTH_TxPin             	GPIO_Pin_2
#define BLUETOOTH_IRQn              		USART2_IRQn
#define BLUETOOTH_IRQHandler        	USART2_IRQHandler




/* ---------------- */



/* -- Debug -- */


#define DEBUG_USART        		USART1
#define DEBUG_GPIO              	GPIOA
#define DEBUG_CLK               		RCC_APB2Periph_USART1
#define DEBUG_GPIO_CLK          	RCC_APB2Periph_GPIOA
#define DEBUG_RxPin             	GPIO_Pin_10
#define DEBUG_TxPin             		GPIO_Pin_9
#define DEBUG_IRQn              		USART1_IRQn
#define DEBUG_IRQHandler        	USART1_IRQHandler



/* ---------------- */


/* -- LED -- */


#define LED1_GPIO			GPIOA
#define LED1_GPIO_CLK          RCC_APB2Periph_GPIOA
#define LED1_OutPin		GPIO_Pin_11 //Left LED

#define LED2_GPIO			GPIOA
#define LED2_GPIO_CLK          RCC_APB2Periph_GPIOA
#define LED2_OutPin		GPIO_Pin_12 //Right LED



/* ---------------- */


/* -- Motor -- */




/* ---------------- */


/* -- IR Sensor -- */






/* ---------------- */


/* -- Battery -- */






/* ---------------- */


/* -- Buzzer -- */


#define BUZZER_GPIO			GPIOB
#define BUZZER_GPIO_CLK          	RCC_APB2Periph_GPIOB
#define BUZZER_OutPin			GPIO_Pin_4 



/* ---------------- */


/* -- Button -- */






/* ---------------- */




extern __IO uint16_t ADCConvertedValue[7];
extern TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
extern TIM_OCInitTypeDef  TIM_OCInitStructure;
extern TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure3;
extern TIM_OCInitTypeDef  TIM_OCInitStructure3;
extern TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure2;
extern TIM_OCInitTypeDef  TIM_OCInitStructure2;


void Device_Init(void);
void BLUETOOTH_Configuration(void);
void DEBUG_Configuration(void);
void LED_Configuration(void);
void I2C_Configuration(void);
void MOTOR_Configuration(void);
void DMA_Configuration(void);
void ADC1_Configuration(void);
void BUZZER_Configuration(void);
void EXTI14_Configuration(void);
void NVIC_Configuration(void);
void TIMER_Configuration(void);




#endif /* __MCUSETTINGS_H */
