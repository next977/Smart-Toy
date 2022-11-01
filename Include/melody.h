#ifndef __MELODY_H__
#define __MELODY_H__
#include "platform_config.h"
#define MELODYSPEED 120

#define NONEMELODY 0
#define STARTMELODY 1
#define ROTATEMELODY 2
#define HOOJINMELODY 3
#define PARINGMELODY 4
#define SUCCESSMELODY 5
#define BTCONNECTMELODY 6
#define BTDISCONNECTMELODY 7
#define BLOCKDETECTMELODY 8
#define BLOCKHOOJINMELODY 9
#define BLOCKPARALLELMELODY 10


#define	DO1	33
#define	DOS1	35
#define	RE1	37
#define	RES1	39
#define	MI1	41
#define	PA1	44
#define	PAS1	46 
#define	SOL1	49
#define	SOLS1	52
#define	RA1	55
#define	RAS1	58
#define	SI1	62
#define	DO2	65
#define	DOS2	69
#define	RE2	73
#define	RES2	78
#define	MI2	82
#define	PA2	87
#define	PAS2	92
#define	SOL2	98
#define	SOLS2	104
#define	RA2	110
#define	RAS2	117
#define	SI2	123
#define	DO3	131
#define	DOS3	139
#define	RE3	147
#define	RES3	156
#define	MI3	165
#define	PA3	175
#define	PAS3	185
#define	SOL3	196
#define	SOLS3	208
#define	RA3	220
#define	RAS3	233
#define	SI3	247
#define	DO4	262
#define	DOS4	277
#define	RE4	294
#define	RES4	311
#define	MI4	330
#define	PA4	349
#define	PAS4	370
#define	SOL4	392
#define	SOLS4	415
#define	RA4	440
#define	RAS4	466
#define	SI4	494
#define	DO5	523
#define	DOS5	554
#define	RE5	587
#define	RES5	622
#define	MI5	659
#define	PA5	698
#define	PAS5	740
#define	SOL5	784
#define	SOLS5	831
#define	RA5	880
#define	RAS5	932
#define	SI5	988
#define	DO6	1047
#define	DOS6	1109
#define	RE6	1175
#define	RES6	1245
#define	MI6	1319
#define	PA6	1397
#define	PAS6	1480
#define	SOL6	1568
#define	SOLS6	1661
#define	RA6	1760
#define	RAS6	1865
#define	SI6	1976
#define	DO7	2093
#define	DOS7	2217
#define	RE7	2349
#define	RES7	2489
#define	MI7	2637
#define	PA7	2794
#define	PAS7	2960
#define	SOL7	3136
#define	SOLS7	3322
#define	RA7	3520
#define	RAS7	3729
#define	SI7	3951
#define	DO8	4186
#define	DOS8	4435
#define	RE8	4699
#define	RES8	4978
#define	MI8	5274
#define	PA8	5588
#define	PAS8	5920
#define	SOL8	6272
#define	SOLS8	6645
#define	RA8	7040
#define	RAS8	7459
#define	SI8	7902
#define NONMEL 1




typedef struct
{
	uint16_t * MelodyTime;
	uint16_t * MelodyTone;
	uint16_t  Length;
	uint16_t Continue;
} Melody;


extern bool MelodyOn;
extern void Buzzer_sound(int value);
extern void MelodyStart(int melody);
extern void MelodyOff(void);
extern uint32_t MelodyTimer;
extern Melody  m;
extern uint32_t MelodyPointer;
extern int MELODY;;

#endif // __MELODY_H__
