#include "platform_config.h"

#define ADC1_DR_Address    ((uint32_t)0x4001244C)
__IO uint16_t ADCConvertedValue[7];
uint16_t PrescalerValue = 0;
TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
TIM_OCInitTypeDef  TIM_OCInitStructure;
TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure3;
TIM_OCInitTypeDef  TIM_OCInitStructure3;
TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure2;
TIM_OCInitTypeDef  TIM_OCInitStructure2;

void Device_Init(void)
{
	BLUETOOTH_Configuration();
	DEBUG_Configuration();
	BUZZER_Configuration();
	MOTOR_Configuration();
	TIMER_Configuration();
	DMA_Configuration(); //sensor
	ADC1_Configuration(); //sensor
	NVIC_SetVectorTable(0x8003200, 0);
	NVIC_Configuration(); //interrupt
	EXTI14_Configuration(); //button setting
	LED_Configuration();
	I2C_Configuration(); //gyro sensor setting
	

}



void BLUETOOTH_Configuration(void)
{


	USART_InitTypeDef USART_InitStructure;
	GPIO_InitTypeDef GPIO_InitStructure;

	RCC_APB2PeriphClockCmd(BLUETOOTH_GPIO_CLK | RCC_APB2Periph_AFIO, ENABLE);
	RCC_APB1PeriphClockCmd(BLUETOOTH_CLK, ENABLE);





	USART_InitStructure.USART_BaudRate = 115200;
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;
	USART_InitStructure.USART_StopBits = USART_StopBits_1;
	USART_InitStructure.USART_Parity = USART_Parity_No;
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;


	USART_Init(BLUETOOTH_USART, &USART_InitStructure);
	USART_ITConfig(BLUETOOTH_USART, USART_IT_RXNE, ENABLE);
	USART_Cmd(BLUETOOTH_USART, ENABLE);


	GPIO_InitStructure.GPIO_Pin = BLUETOOTH_RxPin;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_Init(BLUETOOTH_GPIO, &GPIO_InitStructure);  


	GPIO_InitStructure.GPIO_Pin = BLUETOOTH_TxPin;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_Init(BLUETOOTH_GPIO, &GPIO_InitStructure); 


	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1  ;  //PIO_5   , Bluetooth Reset
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);


	//GPIO_ResetBits(GPIOA, GPIO_Pin_0);
	GPIO_SetBits(GPIOA, GPIO_Pin_0);
	GPIO_SetBits(GPIOA, GPIO_Pin_1);

	GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable, ENABLE); //Paring Switch
	
	
	//init_Queue(&bluetoothRX);


}




/* ---------------- */



/* -- Debug -- */

void DEBUG_Configuration(void)
{

	USART_InitTypeDef USART_InitStructure;
	GPIO_InitTypeDef GPIO_InitStructure;



	RCC_APB2PeriphClockCmd(DEBUG_GPIO_CLK | RCC_APB2Periph_AFIO, ENABLE);
	RCC_APB2PeriphClockCmd(DEBUG_CLK, ENABLE); 





	USART_InitStructure.USART_BaudRate = 115200;
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;
	USART_InitStructure.USART_StopBits = USART_StopBits_1;
	USART_InitStructure.USART_Parity = USART_Parity_No;
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;


	USART_Init(DEBUG_USART, &USART_InitStructure);
	USART_ITConfig(DEBUG_USART, USART_IT_RXNE, ENABLE);
	USART_Cmd(DEBUG_USART, ENABLE);



	GPIO_InitStructure.GPIO_Pin = DEBUG_RxPin;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU ;
	GPIO_Init(DEBUG_GPIO, &GPIO_InitStructure);


	GPIO_InitStructure.GPIO_Pin = DEBUG_TxPin;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_Init(DEBUG_GPIO, &GPIO_InitStructure);

}		



/* ---------------- */


/* -- LED -- */

void LED_Configuration(void)
{
	
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIOB | RCC_APB2Periph_GPIOC | RCC_APB2Periph_AFIO, ENABLE);
	
	
	
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_PWR | RCC_APB1Periph_BKP, ENABLE);
	PWR_BackupAccessCmd(ENABLE);
	BKP_DeInit();
	RCC_LSEConfig(RCC_LSE_OFF); 
	
	
	
		/* ---------------LED -----------------*/
	GPIO_InitStructure.GPIO_Pin =  LED1_OutPin|LED2_OutPin|GPIO_Pin_15 ;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	

	GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_2 |GPIO_Pin_3 |GPIO_Pin_5 ;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_InitStructure);

	
	
	
	
	
	
	/*-------------------POWER------------------------*/
	 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
	GPIO_InitStructure.GPIO_Pin =   GPIO_Pin_15 ;
	GPIO_Init(GPIOC, &GPIO_InitStructure);
	
	GPIO_ResetBits(GPIOC, GPIO_Pin_15);
	GPIO_SetBits(GPIOA, GPIO_Pin_11| GPIO_Pin_12| GPIO_Pin_15);
	GPIO_SetBits(GPIOB, GPIO_Pin_2 |GPIO_Pin_3 |GPIO_Pin_5 );


	
}



/* ---------------- */



/* -- Gyro Sensor -- */

void I2C_Configuration(void)
{
	
	I2C_InitTypeDef I2C_InitStructure;
	GPIO_InitTypeDef GPIO_InitStructure;
	
	I2C_DeInit(I2C1);
	
	//GPIO_PinRemapConfig(GPIO_Remap_I2C1, ENABLE);
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_I2C1, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB , ENABLE);
	
	GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_6 | GPIO_Pin_7;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_OD;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_InitStructure);
	
	
	I2C_InitStructure.I2C_Mode = I2C_Mode_I2C;
	I2C_InitStructure.I2C_DutyCycle = I2C_DutyCycle_2;
	I2C_InitStructure.I2C_OwnAddress1= MPU6050_DEFAULT_ADDRESS; 
	I2C_InitStructure.I2C_Ack = I2C_Ack_Enable;
	
	I2C_InitStructure.I2C_AcknowledgedAddress = I2C_AcknowledgedAddress_7bit;
	I2C_InitStructure.I2C_ClockSpeed = 100000;
	I2C_Init(I2C1, &I2C_InitStructure);
	
	
	I2C_Cmd(I2C1, ENABLE);
	
	

}

/* ---------------- */


/* -- Motor -- */

void MOTOR_Configuration(void)
{

	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB | RCC_APB2Periph_AFIO, ENABLE);


	/* ---------------PWM -----------------*/
	GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_8 | GPIO_Pin_9;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_InitStructure);


	/*--------------------MOTOR CONTROL------------------------------*/
	GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_10 | GPIO_Pin_11 | GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_InitStructure);


	GPIO_SetBits(GPIOB, GPIO_Pin_12 | GPIO_Pin_15);
	GPIO_ResetBits(GPIOB, GPIO_Pin_11 |  GPIO_Pin_14 );
	GPIO_SetBits(GPIOB, GPIO_Pin_10 | GPIO_Pin_13 );



}


/* ---------------- */


/* -- IR Sensor -- */

void DMA_Configuration(void)
{
	DMA_InitTypeDef DMA_InitStructure;

	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1, ENABLE);

	DMA_DeInit(DMA1_Channel1);
	DMA_InitStructure.DMA_PeripheralBaseAddr = ADC1_DR_Address;
	DMA_InitStructure.DMA_MemoryBaseAddr = (uint32_t)&ADCConvertedValue;
	DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralSRC;
	DMA_InitStructure.DMA_BufferSize = 7;
	DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
	DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;
	DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_HalfWord;
	DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_HalfWord;
	DMA_InitStructure.DMA_Mode = DMA_Mode_Circular;
	DMA_InitStructure.DMA_Priority = DMA_Priority_High;
	DMA_InitStructure.DMA_M2M = DMA_M2M_Disable;
	DMA_Init(DMA1_Channel1, &DMA_InitStructure);

	/* Enable DMA1 channel1 */
	DMA_Cmd(DMA1_Channel1, ENABLE);

}

void ADC1_Configuration(void)
{
	ADC_InitTypeDef ADC_InitStructure;
	GPIO_InitTypeDef GPIO_InitStructure;


	RCC_ADCCLKConfig(RCC_PCLK2_Div4); 
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1 , ENABLE);

ADC1->CR2 |= ADC_CR2_TSVREFE;


	ADC_InitStructure.ADC_Mode = ADC_Mode_Independent;
	ADC_InitStructure.ADC_ScanConvMode = ENABLE;
	ADC_InitStructure.ADC_ContinuousConvMode = ENABLE;
	ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;
	ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;
	ADC_InitStructure.ADC_NbrOfChannel = 7;
	ADC_Init(ADC1, &ADC_InitStructure);

	/* ADC1 regular channel14 configuration */ 
	ADC_RegularChannelConfig(ADC1, ADC_Channel_4, 1, ADC_SampleTime_55Cycles5);
	ADC_RegularChannelConfig(ADC1, ADC_Channel_5, 2, ADC_SampleTime_55Cycles5);
	ADC_RegularChannelConfig(ADC1, ADC_Channel_6, 3, ADC_SampleTime_55Cycles5);
	ADC_RegularChannelConfig(ADC1, ADC_Channel_7, 4, ADC_SampleTime_55Cycles5);
	ADC_RegularChannelConfig(ADC1, ADC_Channel_8, 5, ADC_SampleTime_55Cycles5);
	ADC_RegularChannelConfig(ADC1, ADC_Channel_9, 6, ADC_SampleTime_55Cycles5);
	ADC_RegularChannelConfig(ADC1, ADC_Channel_16, 7, ADC_SampleTime_55Cycles5);

	/* Enable ADC1 DMA */
	ADC_DMACmd(ADC1, ENABLE);

	/* Enable ADC1 */
	ADC_Cmd(ADC1, ENABLE);

	/* Enable ADC1 reset calibration register */   
	ADC_ResetCalibration(ADC1);
	/* Check the end of ADC1 reset calibration register */
	while(ADC_GetResetCalibrationStatus(ADC1));

	/* Start ADC1 calibration */
	ADC_StartCalibration(ADC1);
	/* Check the end of ADC1 calibration */
	while(ADC_GetCalibrationStatus(ADC1));

	/* Start ADC1 Software Conversion */ 
	ADC_SoftwareStartConvCmd(ADC1, ENABLE);

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4 | GPIO_Pin_5 | GPIO_Pin_6  | GPIO_Pin_7;   // IR Sensor 1  | IR Sensor 2 | IR Sensor 3| BAT
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;
	GPIO_Init(GPIOA, &GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1;   // IR Sensor 4 | IR Sensor 5
	GPIO_Init(GPIOB, &GPIO_InitStructure);



	GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_8 ;  //IR Sensor On/off
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);






}




/* ---------------- */


/* -- Battery -- */






/* ---------------- */


/* -- Buzzer -- */


void BUZZER_Configuration(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_APB2PeriphClockCmd( BUZZER_GPIO_CLK |   RCC_APB2Periph_AFIO , ENABLE);




	/* ---------------BUZZER-----------------*/
	GPIO_InitStructure.GPIO_Pin =  BUZZER_OutPin;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_InitStructure);




	GPIO_PinRemapConfig(GPIO_Remap_SWJ_NoJTRST, ENABLE);   // BUZZER REMAP
}



/* ---------------- */


/* -- Button -- */


void EXTI14_Configuration(void)
{
	EXTI_InitTypeDef   EXTI_InitStructure;

	GPIO_InitTypeDef GPIO_InitStructure1;


	GPIO_InitStructure1.GPIO_Pin = GPIO_Pin_14;
	GPIO_InitStructure1.GPIO_Speed = GPIO_Speed_2MHz;
	GPIO_InitStructure1.GPIO_Mode = GPIO_Mode_IPU;
	GPIO_Init(GPIOC, &GPIO_InitStructure1);

	GPIOC->ODR &= ~ (1<<14);
	GPIOC->ODR |= (1<<14);


	GPIO_EXTILineConfig(GPIO_PortSourceGPIOC, GPIO_PinSource14);

	GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable, ENABLE);
	EXTI_InitStructure.EXTI_Line = EXTI_Line14;
	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;  
	EXTI_InitStructure.EXTI_LineCmd = ENABLE;
	EXTI_Init(&EXTI_InitStructure);

	//GPIO_SetBits(GPIOC, GPIO_Pin_14);


}



/* ---------------- */

/* -- NVIC -- */

void NVIC_Configuration(void)
{

	NVIC_InitTypeDef NVIC_InitStructure;

	/* Configure the NVIC Preemption Priority Bits */  
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_4);
	/*
	   NVIC_InitStructure.NVIC_IRQChannel = EXTI3_IRQn;
	   NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
	   NVIC_InitStructure.NVIC_IRQChannelSubPriority=0;
	   NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	   NVIC_Init(&NVIC_InitStructure);
	 */

	NVIC_InitStructure.NVIC_IRQChannel = EXTI15_10_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority=0;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);


	/* Enable the USARTz Interrupt */

	NVIC_InitStructure.NVIC_IRQChannel = BLUETOOTH_IRQn ;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority=0;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);

	NVIC_InitStructure.NVIC_IRQChannel = DEBUG_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 3;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority=0;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);


	/* Enable the TIM2 Interrupt */
	NVIC_InitStructure.NVIC_IRQChannel = TIM2_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority=0;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
/*
	NVIC_InitStructure.NVIC_IRQChannel = TIM4_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority=0;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);

*/
	/* Enable the TIM1 Interrupt */
	/*
	   NVIC_InitStructure.NVIC_IRQChannel = TIM1_UP_IRQn;
	   NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
	   NVIC_InitStructure.NVIC_IRQChannelSubPriority=1;
	   NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	   NVIC_Init(&NVIC_InitStructure);
	 */

}


void TIMER_Configuration(void)
{


	
	
	RCC_SYSCLKConfig(RCC_SYSCLKSource_PLLCLK);


	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);
	//RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1, ENABLE);
	//RCC_APB2PeriphResetCmd(RCC_APB2Periph_TIM1,DISABLE);




	GPIO_PinRemapConfig(GPIO_PartialRemap_TIM3,ENABLE);

	/* -----------------------------------------------------------------------
	   TIM3 Configuration: generate 4 PWM signals with 4 different duty cycles:
	   The TIM3CLK frequency is set to SystemCoreClock (Hz), to get TIM3 counter
	   clock at 24 MHz the Prescaler is computed as following:
	   - Prescaler = (TIM3CLK / TIM3 counter clock) - 1
	   SystemCoreClock is set to 72 MHz for Low-density, Medium-density, High-density
	   and Connectivity line devices and to 24 MHz for Low-Density Value line and
	   Medium-Density Value line devices

	   The TIM3 is running at 36 KHz: TIM3 Frequency = TIM3 counter clock/(ARR + 1)
	   = 24 MHz / 666 = 36 KHz
	   TIM3 Channel1 duty cycle = (TIM3_CCR1/ TIM3_ARR)* 100 = 50%
	   TIM3 Channel2 duty cycle = (TIM3_CCR2/ TIM3_ARR)* 100 = 37.5%
	   TIM3 Channel3 duty cycle = (TIM3_CCR3/ TIM3_ARR)* 100 = 25%
	   TIM3 Channel4 duty cycle = (TIM3_CCR4/ TIM3_ARR)* 100 = 12.5%
	   ----------------------------------------------------------------------- */
	/* Compute the prescaler value */
	PrescalerValue = (uint16_t) (SystemCoreClock / 24000000) - 1;
	/* Time base configuration */
	TIM_TimeBaseStructure.TIM_Period = 23999;
	TIM_TimeBaseStructure.TIM_Prescaler = PrescalerValue;
	TIM_TimeBaseStructure.TIM_ClockDivision = 0;
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_ClearFlag(TIM4,TIM_FLAG_Update);
	TIM_ITConfig(TIM4, TIM_IT_Update, ENABLE);
	TIM_TimeBaseInit(TIM4, &TIM_TimeBaseStructure);

	TIM_TimeBaseStructure3.TIM_Period = 2400;
	TIM_TimeBaseStructure3.TIM_Prescaler = 71;
	TIM_TimeBaseStructure3.TIM_ClockDivision = 0;
	TIM_TimeBaseStructure3.TIM_CounterMode = TIM_CounterMode_Up;

	TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure3);



	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
	TIM_OCInitStructure3.TIM_OCMode = TIM_OCMode_PWM1;
	TIM_OCInitStructure2.TIM_OCMode = TIM_OCMode_Timing;


	/* PWM1 Mode configuration: Channel3 */
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
	TIM_OCInitStructure.TIM_Pulse = 0;
	TIM_OC3Init(TIM4, &TIM_OCInitStructure);
	TIM_OC3PreloadConfig(TIM4, TIM_OCPreload_Enable);

	/* PWM1 Mode configuration: Channel4 */
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
	TIM_OCInitStructure.TIM_Pulse = 0;
	TIM_OC4Init(TIM4, &TIM_OCInitStructure);
	TIM_OC4PreloadConfig(TIM4, TIM_OCPreload_Enable);


	TIM_OCInitStructure3.TIM_OutputState = TIM_OutputState_Enable;
	TIM_OCInitStructure3.TIM_Pulse = 0;
	TIM_OC1Init(TIM3, &TIM_OCInitStructure3);
	TIM_OC1PreloadConfig(TIM3, TIM_OCPreload_Enable);



	TIM_ARRPreloadConfig(TIM4, ENABLE);
	TIM_ARRPreloadConfig(TIM3, ENABLE);

	/* TIM4 enable counter */
	TIM_Cmd(TIM4, ENABLE);
	TIM_Cmd(TIM3, ENABLE);


	TIM_TimeBaseStructure2.TIM_Period = 36000/MELODYSPEED;
	TIM_TimeBaseStructure2.TIM_Prescaler = 5999;
	TIM_TimeBaseStructure2.TIM_ClockDivision = 0;
	TIM_TimeBaseStructure2.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure2);
	TIM_ARRPreloadConfig(TIM2, ENABLE);
	TIM_ClearFlag(TIM2,TIM_FLAG_Update);
	TIM_ITConfig(TIM2, TIM_IT_Update, ENABLE);

	/*
	   TIM_OCInitStructure1.TIM_OCMode = TIM_OCMode_Timing;
	   TIM_OCInitStructure1.TIM_OutputState=TIM_OutputState_Disable;
	   TIM_OCInitStructure1.TIM_OutputNState=TIM_OutputNState_Disable;

	   TIM_OC1Init(TIM1, &TIM_OCInitStructure1);
	   TIM_OC2Init(TIM1, &TIM_OCInitStructure1);
	   TIM_OC3Init(TIM1, &TIM_OCInitStructure1);
	   TIM_OC4Init(TIM1, &TIM_OCInitStructure1);


	   TIM_TimeBaseStructure1.TIM_Period = 120;
	   TIM_TimeBaseStructure1.TIM_Prescaler = 5999;
	   TIM_TimeBaseStructure1.TIM_ClockDivision = TIM_CKD_DIV1;
	   TIM_TimeBaseStructure1.TIM_CounterMode = TIM_CounterMode_Up;
	   TIM_TimeBaseStructure1.TIM_RepetitionCounter = 0;
	   TIM_TimeBaseInit(TIM1, &TIM_TimeBaseStructure1);
	   TIM_ARRPreloadConfig(TIM1, ENABLE);
	   TIM_ClearFlag(TIM1,TIM_FLAG_Update);
	   TIM_ITConfig(TIM1, TIM_IT_Update, ENABLE);
	   TIM_Cmd(TIM1, ENABLE);

	 */


	
}


/* ---------------- */
