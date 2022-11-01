#ifndef __MELODYDATA_H__
#define __MELODYDATA_H__


#include "stm32f10x.h"
#include "melody.h"
/*
uint16_t tone1 [] = {DO5, DO5, DO5, DO5, DO5,      MI5, SOL5, SOL5, MI5, DO5,        SOL5, SOL5, MI5, SOL5, SOL5, MI5,   DO5, DO5, DO5,      SOL5, SOL5, MI5, DO5,     SOL5, SOL5, SOL5,      SOL5, SOL5, MI5, DO5,    SOL5, SOL5, SOL5,       SOL5, SOL5, MI5, DO5,    SOL5, SOL5, SOL5, RA5, SOL5,     DO6, SOL5, DO6, SOL5,       MI5, RE5, DO5};
uint16_t time1 [] =  { 1,20,  10,  10,  20,  20,       20,   10,   10,  20,  20,          10,   10,  20,   10,   10,  20,    20,  20,  40,        20,   20,  20,  20,       20,   20,   40,        20,   20,  20,  20,      20,   20,   40,         20,   20,  20,  20,      10,   10,   10,  10,   40,      20,   20,  20,   20,        20,  20,  40,0};
uint16_t tone2 [] = {NONMEL, SOL5, MI5, DO5,                   RE5, RE5, SOL4, SOL4, NONMEL,           NONMEL, SOL5, SOL5, MI5, DO5,      RE5, RA5, SOL5, NONMEL,       RA5, RA5, SI5, NONMEL,   SOL5, SOL5, RA5, NONMEL,      
	MI5, RA5, MI5, DO5,      MI5, RE5, RE5, NONMEL,      NONMEL, SOL5, MI5, DO5,       RE5, RE5, SOL4, SOL4, NONMEL,      NONMEL, SOL5, SOL5, MI5, DO5,      RE5, RE5, RA5, SOL5, NONMEL,      RA5, RE6, SI5, NONMEL,    
	SOL5, DO6, SOL5, NONMEL,     RE5, MI5, PA5, SOL5, RA5, SI5, DO6, RE6,     DO6, NONMEL, SI5, NONMEL, DO6, NONMEL,     RA5, SOL5, PA5, RA5, SOL5, PA5,    SOL5, MI5, MI5, NONMEL, MI5, MI5,   PA5, PA5, RE5, RE5, SOL5, 
	NONMEL, PA5, PA5,     SOL5, SOL5, MI5, MI5, RA5, NONMEL,    DO6, SI5, RA5, SI5, DO6, SI5, RA5, SI5, DO6, SI5, RA5, SI5, DO6, RE6,     SI5, NONMEL, DO6, NONMEL, RE6, NONMEL,      NONMEL, SOL5, MI5, DO5,   
	RE5, RE5, SOL4, SOL4, NONMEL,     NONMEL, SOL5, MI5, DO5,     RE5, RA5, SOL5, NONMEL,   RA5,  RE6,  SI5, NONMEL,   SOL5,  DO6, SOL5,  NONMEL,     RE5, MI5, PA5, SOL5, RA5, SI5, DO6, RE6,      
	DO6, NONMEL, SI5, NONMEL, DO6, NONMEL}  ;
uint16_t time2 [] = {  1, 20,     20,  20,  20,                    15,   5,   20,   20,     20,               20,   15,    5,  20,  20,       20,  20,   20,     20,        20,  20,  20,     20,     20,   20,  20,     20,       20,  20,   20, 20,       20,  20,  20,     20,          20,   20,  20,  20,        
	10,  10,   20,   20,     20,          20,   15,    5,  20,  20,       10,  10,  20,   20,     20,        20,   20, 20,    20,       20,  20,   20,     20,      10,   10, 10,   10,  10,  10,  10,  10,       10,    10,  10,    10,   10,    30 ,      30,  10,   10,  10,  10,   10,     
	20,  20,  20,    10,    5,   5,     5,   5,   5,   5,   10,    40,    5,   5,        5,    5,   5,   5,   10,    50,      5,   5,   5,   5,   5,   5,   5,   5,   5,   5,   5,   5,   10,  10,      10,   10,    10,   10,    10,    30,          20,   20,  20,  20,      15,  5,   20,   20,    20,         
	20,    20,   20, 20,      20,  20,   20,    20,     20,   20,   20,    20,      20,   20,   20,     20,       10,  10,  10,   10,  10,  10,  10,  10,     10,  10, 10,  10,  10,  30 , 0};
*/
uint16_t StartMelodyTone [] = { SOL7, NONMEL, RA7, NONMEL, SI7, NONMEL, DO8, NONMEL};
uint16_t StartMelodyTime [] = {   3,           1,        3,          1,            3,           1,      3,        1};

uint16_t tone4 [] = { SOL5, NONMEL, SOL5, NONMEL, SOL5, NONMEL, SOL5, NONMEL};
uint16_t time4 [] = {1,      10,           10,        10,          10,            10,           10,      10,        10,   0};

uint16_t tone5 [] = { SOL5, DO5, SOL5, DO5, SOL5, DO5, SOL5, DO5};
uint16_t time5 [] = {1,      10,           10,        10,          10,            10,           10,      10,        10,   0};


uint16_t RotateMelodyTone [] = { SOL4, SOLS4, RA4, RAS4, SI4, DO5, DOS5, RE5, RES5, MI5, PA5, PAS5, SOL5, SOLS5, RA5, RAS5};
uint16_t RotateMelodyTime [] = {   1,           1,       1,           1,   1,           1,   1,           1,   1,           1,      1,           1,   1,           1,   1,           1};

uint16_t tone7 [] = { SOL2, NONMEL,  SOL2, NONMEL,SOL2, NONMEL,SOL2, NONMEL,SOL2, NONMEL,SOL2, NONMEL,SOL2, NONMEL,SOL2, NONMEL};
uint16_t time7 [] = {1,   3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3, 0};

uint16_t HooJinMelodyTone [] = {   MI5,RES5,MI5,RES5,MI5,SI4,RE5,DO5,RA4,NONMEL,DO4,MI4,RA4,SI4,NONMEL,MI4,SOLS4,SI4,DO5,NONMEL,MI4,MI5,RES5,MI5,RES5,MI5,SI4,RE5,DO5,RA4,NONMEL,DO4,MI4,RA4,SI4,NONMEL,RE4,DO5,SI4,RA4,MI5,RES5,MI5,RES5,MI5,SI4,RE5,DO5,RA4,NONMEL,DO4,MI4,RA4,SI4,NONMEL,MI4,SOLS4,SI4,DO5,NONMEL,MI4,MI5,RES5,MI5,RES5,MI5,SI4,RE5,DO5,RA4,NONMEL,DO4,MI4,RA4,SI4,NONMEL,RE4,DO5,SI4, RA4};
uint16_t HooJinMelodyTime [] = { 10,10,10,10,10,10,10,10,20,10,10,10,10,20,10,10,10,10,20,10,10,10,10,10,10,10,10,10,10,20,10,10,10,10,20,10,10,10,10,40,10,10,10,10,10,10,10,10,20,10,10,10,10,20,10,10,10,10,20,10,10,10,10,10,10,10,10,10,10,20,10,10,10,10,20,10,10,10,10,40 };


uint16_t tone9 [] = {  DO8,NONMEL, SI7, NONMEL,  RA7,NONMEL,  SOL7,NONMEL};
uint16_t time9 [] = {1,      3,           1,        3,          1,            3,           1,      3,        1,   0};

uint16_t ParingMelodyTone [] = {  DO8,NONMEL, DO8, NONMEL };
uint16_t ParingMelodyTime [] = {  3,           2,        3,          2};

uint16_t SuccessMelodyTone [] = {  DO6,NONMEL, MI6, NONMEL, SOL6, NONMEL, DO6, NONMEL };
uint16_t SuccessMelodyTime [] = {  3,           2,        3,          2,        3,          2,        3,          2};

uint16_t BTConnectMelodyTone [] = {  RA5, NONMEL,  DO6, NONMEL };
uint16_t BTConnectMelodyTime [] = {  3,   1,  3, 1  };

uint16_t BTDisconnectMelodyTone [] = {  DO6, NONMEL, RA5, NONMEL };
uint16_t BTDisconnectMelodyTime [] = {  3,  1,   3 , 1  };

uint16_t BlockDetectMelodyTone [] = {  1000 , NONMEL};
uint16_t BlockDetectMelodyTime [] = {  2,  1 };

uint16_t BlockHoojinMelodyTone [] = {  2000 , NONMEL};
uint16_t BlockHoojinMelodyTime [] = {  2,  1 };

uint16_t BlockParallelMelodyTone [] = {  DO6 , NONMEL};
uint16_t BlockParallelMelodyTime [] = {  2,  1 };

#endif // __MELODYDATA_H__
