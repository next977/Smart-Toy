#include "sensor.h"
#include "platform_config.h"

#define SNUMBER 162


//2-5-2
/*
uint16_t F_Sensor = 300;
static s16 FL_SensorTable[18]=	{0	,196	,206	,217	,228	,240	,253	,269	,290	,328	,559	,959	,1343	,1689	,1930	,2154	,4100};
static s16 L_SensorTable[18]=	{0	,188	,198	,208	,219	,231	,242	,257	,275	,305	,376	,745	,1199	,1584	,1852	,2081	,4100};
static s16 FR_SensorTable[18]=	{0	,190	,201	,212	,226	,243	,260	,288	,380	,903	,1358	,1724	,2037	,2318	,2551	,2729	,4100};
static s16 R_SensorTable[18]=	{0	,188	,198	,208	,219	,232	,242	,257	,275	,303	,376	,815	,1252	,1654	,1991	,2236	,4100};
*/

// 3-3
#if SNUMBER == 33
uint16_t F_Sensor = 300;
static s16 FL_SensorTable[18]=	{0	,202	,210	,220	,233	,246	,261	,284	,316	,587	,1054	,1485	,1802	,2081	,2275	,2434	,5000};
static s16 L_SensorTable[18]=	{0	,179	,188	,198	,210	,220	,231	,244	,258	,280	,309	,498	,923	,1313	,1623	,1889	,5000};
static s16 FR_SensorTable[18]=	{0	,190	,201	,212	,224	,238	,254	,273	,302	,384	,813	,1331	,1709	,2009	,2261	,2435	,5000};
static s16 R_SensorTable[18]=	{0	,186	,197	,208	,218	,230	,243	,257	,274	,296	,344	,708	,1105	,1446	,1720	,1937	,5000};


// 3-4
#elif SNUMBER == 34
uint16_t F_Sensor = 300;
static s16 FL_SensorTable[18]=	{0	,195	,202	,212	,223	,234	,250	,268	,294	,363	,849	,1335	,1751	,2084	,2312	,2516	,5000};
static s16 L_SensorTable[18]=	{0	,180	,185	,194	,203	,210	,222	,233	,245	,257	,275	,305	,402	,849	,1173	,1459	,5000};
static s16 FR_SensorTable[18]=	{0	,192	,201	,211	,221	,233	,243	,258	,275	,303	,413	,858	,1261	,1606	,1882	,2098	,5000};
static s16 R_SensorTable[18]=	{0	,200	,210	,221	,231	,244	,258	,273	,299	,366	,775	,1187	,1516	,1810	,2056	,2249	,5000};


//4-1
#elif SNUMBER == 40
uint16_t F_Sensor = 300;
static s16 FL_SensorTable[18]=	{0	,181	,186	,195	,205	,219	,231	,245	,258	,275	,306	,396	,819	,1193	,1525	,1793	,5000};
static s16 L_SensorTable[18]=	{0	,204	,206	,215	,229	,248	,275	,342	,825	,1384	,1869	,2266	,2545	,2766	,2967	,3114	,5000};
static s16 FR_SensorTable[18]=	{0	,202	,215	,228	,244	,264	,286	,335	,698	,1169	,1589	,1959	,2260	,2482	,2671	,2803	,5000};
static s16 R_SensorTable[18]=	{0	,185	,196	,207	,219	,233	,244	,260	,280	,310	,446	,882	,1276	,1582	,1840	,2043	,5000};


//4-1-2
#elif SNUMBER == 41
uint16_t F_Sensor = 300;
static s16 FL_SensorTable[18]=	{0	,184	,193	,201	,213	,224	,234	,243	,259	,276	,310	,591	,1066	,1437	,1666	,1892	,5000};
static s16 L_SensorTable[18]=	{0	,203	,213	,226	,244	,267	,311	,627	,1223	,1728	,2132	,2514	,2715	,2903	,3033	,3159	,5000};
static s16 FR_SensorTable[18]=	{0	,203	,215	,227	,240	,252	,271	,294	,345	,843	,1431	,1830	,2143	,2386	,2577	,2748	,5000};
static s16 R_SensorTable[18]=	{0	,181	,191	,201	,210	,219	,230	,240	,254	,273	,306	,416	,892	,1232	,1527	,1791	,5000};

//4-2
#elif SNUMBER == 42
uint16_t F_Sensor = 300;
static s16 FL_SensorTable[18]=	{0	,196	,207	,217	,229	,241	,254	,271	,292	,331	,667	,1170	,1644	,1965	,2182	,2418	,4100};
static s16 L_SensorTable[18]=	{0	,193	,204	,214	,226	,238	,252	,271	,298	,377	,886	,1364	,1816	,2135	,2352	,2553	,4100};
static s16 FR_SensorTable[18]=	{0	,187	,196	,204	,213	,223	,233	,246	,260	,275	,305	,368	,771	,1227	,1557	,1818	,4100};
static s16 R_SensorTable[18]=	{0	,183	,192	,201	,212	,222	,234	,248	,266	,288	,345	,676	,1165	,1582	,1881	,2109	,4100};




//5-1   ,9- 141
#elif SNUMBER == 141
uint16_t F_Sensor = 220;
static s16 FL_SensorTable[18]=	{0	,205	,218	,231	,246	,262	,289	,349	,728	,1206	,1595	,1933	,2179	,2383	,2563	,2711	,5000};
static s16 L_SensorTable[18]=	{0	,172	,182	,191	,201	,210	,220	,230	,242	,253	,269	,287	,303	,355	,610	,986	,5000};
static s16 FR_SensorTable[18]=	{0	,168	,177	,186	,195	,203	,212	,221	,229	,238	,246	,258	,276	,301	,339	,481	,5000};
static s16 R_SensorTable[18]=	{0	,170	,179	,188	,198	,207	,216	,224	,234	,243	,253	,265	,280	,302	,339	,467	,5000};

//5-2    , 9- 151 -> mcu 교체 후9- 161

#elif SNUMBER == 161
uint16_t F_Sensor = 300;
static s16 FL_SensorTable[18]=	{0	,171	,177	,187	,200	,208	,218	,228	,238	,250	,262	,275	,295	,335	,439	,734	,5000};
static s16 L_SensorTable[18]=	{0	,177	,185	,196	,206	,214	,225	,235	,248	,261	,277	,303	,372	,734	,1078	,1351	,5000};
static s16 FR_SensorTable[18]=	{0	,173	,182	,191	,200	,211	,222	,232	,245	,259	,279	,308	,407	,794	,1157	,1514	,5000};
static s16 R_SensorTable[18]=	{0	,171	,178	,186	,195	,204	,214	,224	,235	,245	,258	,274	,298	,339	,533	,898	,5000};


//5-4  , 9-162
#elif SNUMBER == 162
uint16_t F_Sensor = 215;
static s16 FL_SensorTable[18]=	{0	,178	,185	,196	,204	,214	,227	,239	,254	,269	,291	,324	,557	,882	,1189	,1449	,5000};
static s16 L_SensorTable[18]=	{0	,176	,184	,193	,202	,212	,222	,232	,241	,253	,267	,285	,318	,429	,760	,1061	,5000};
static s16 FR_SensorTable[18]=	{0	,160	,170	,178	,189	,198	,207	,217	,227	,237	,252	,265	,284	,307	,377	,718	,5000};
static s16 R_SensorTable[18]=	{0	,175	,184	,193	,203	,213	,224	,234	,244	,257	,273	,290	,324	,438	,743	,992	,5000};

//5-5   , 9- 163
#elif SNUMBER == 163
uint16_t F_Sensor = 208;
static s16 FL_SensorTable[18]=	{0	,178	,188	,198	,208	,217	,229	,240	,252	,265	,282	,311	,365	,732	,993	,1266	,5000};
static s16 L_SensorTable[18]=	{0	,179	,188	,198	,208	,217	,227	,239	,250	,263	,280	,309	,383	,794	,1091	,1358	,5000};
static s16 FR_SensorTable[18]=	{0	,174	,182	,192	,201	,211	,221	,230	,241	,254	,268	,289	,325	,444	,808	,1107	,5000};
static s16 R_SensorTable[18]=	{0	,167	,174	,183	,193	,201	,210	,219	,228	,237	,248	,263	,281	,303	,361	,599	,5000};
#endif
uint16_t GetSensorValue(int sensor)
{
	
	return ADCConvertedValue[sensor];
}

uint16_t GetNewSensorValue(int sensor)
{
	
	uint16_t sensorvalue;
	int temp;
	int i;

	sensorvalue = ADCConvertedValue[sensor];
	switch(sensor)
	{
		
		case FL_SENSOR :
			
		for(i=0;i<16;i++)
		{
			
			if(FL_SensorTable[i]>sensorvalue)
			{
				break;
			}
			
		}
		
		temp = 200*(i-1) + ((sensorvalue-FL_SensorTable[i-1])*200)/(FL_SensorTable[i]-FL_SensorTable[i-1]);
		
		
		break;
		
		case L_SENSOR :
			
		for(i=0;i<16;i++)
		{
			
			if(L_SensorTable[i]>sensorvalue)
			{
				break;
			}
			
		}
		
		temp = 200*(i-1) + ((sensorvalue-L_SensorTable[i-1])*200)/(L_SensorTable[i]-L_SensorTable[i-1]);
			
		break;
		
		case FR_SENSOR :
			
		for(i=0;i<16;i++)
		{
			
			if(FR_SensorTable[i]>sensorvalue)
			{
				break;
			}
			
		}
		
		temp = 200*(i-1) + ((sensorvalue-FR_SensorTable[i-1])*200)/(FR_SensorTable[i]-FR_SensorTable[i-1]);
			
		break;
		
		case R_SENSOR :
			
		for(i=0;i<16;i++)
		{
			
			if(R_SensorTable[i]>sensorvalue)
			{
				break;
			}
			
		}
		
		temp = 200*(i-1) + ((sensorvalue-R_SensorTable[i-1])*200)/(R_SensorTable[i]-R_SensorTable[i-1]);
			
		break;
		
		
		
	}
	
	return (uint16_t)temp;
	
	
}

uint16_t GetSensorValueReal(int sensor)
{
	
	return ADCConvertedValue[sensor];
}

int IsSensorCheck(int sensor, int sensorlevel)
{
	uint16_t sensorvalue;
	sensorvalue = GetSensorValue(sensor);
	if(sensorvalue < sensorlevel)
	{
		return 1;
	}
	else
	{
		return 0;
	}
	
}



void Battery_Check(char id)
{
	uint16_t adcdatavat;
	uint16_t adcdatavatpercent;
	char stringbatterytest[18] ={'A','E','$','|','3','|','2','|','5','0','|','0','0','0','|','E','@',0};
	uint8_t adcchardata[5];
	adcdatavat = GetSensorValue(VAT_SENSOR);


		adcdatavatpercent = (uint16_t)(((adcdatavat-3660)/435.0)*100);
		adcchardata[0] = (adcdatavatpercent/100)+'0';
		adcchardata[1] = ((adcdatavatpercent%100)/10)+'0';
		adcchardata[2] = (adcdatavatpercent%10)+'0';
		stringbatterytest[4] = id;
		stringbatterytest[11]=(char)adcchardata[0];
		stringbatterytest[12] = (char) adcchardata[1];
		stringbatterytest[13] = (char) adcchardata[2];
	
	BT_SendString(stringbatterytest);

}

void IRSensor_DataRead(void)
{
	int i;
	F_Sensor = afdata.agedata.sdata.f_sensor;
	for(i=0; i<16; i++)
	{
		FL_SensorTable[i] = afdata.agedata.sdata.fl_sensortable[i];
		L_SensorTable[i]= afdata.agedata.sdata.l_sensortable[i];
		FR_SensorTable[i]= afdata.agedata.sdata.fr_sensortable[i];
		R_SensorTable[i]= afdata.agedata.sdata.r_sensortable[i];
		
		
	}
	
	
}

void IRSensor_DataWrite(void)
{
	int i;
	afdata.agedata.sdata.f_sensor = F_Sensor;
	for(i=0; i<16; i++)
	{
		afdata.agedata.sdata.fl_sensortable[i] = FL_SensorTable[i];
		afdata.agedata.sdata.l_sensortable[i] = L_SensorTable[i];
		afdata.agedata.sdata.fr_sensortable[i] = FR_SensorTable[i];
		afdata.agedata.sdata.r_sensortable[i] = R_SensorTable[i];
		
		
	}
	
}

void IRSensor_Calibration(int mm)
{
	int flsensor=0, frsensor=0, lsensor=0, rsensor=0 ;
	int i;
	if(mm<2)
	{
		//printf("Number > 1\r\n");
		return;
	}
	else if(mm>30)
	{
		//printf("Number < 31\r\n");
		return;
	}
	printf("%d mm start\r\n",mm);

	
	for( i=0 ; i<200 ; i++ )
	{
		flsensor+=(int)GetSensorValueReal(FL_SENSOR);
		frsensor+=(int)GetSensorValueReal(FR_SENSOR);
		lsensor+=(int)GetSensorValueReal(L_SENSOR);
		rsensor+=(int)GetSensorValueReal(R_SENSOR);
		delay_ms(5);

	}
	
	flsensor = flsensor/200;
	frsensor = frsensor/200;
	lsensor = lsensor/200;
	rsensor = rsensor/200;
	
	FL_SensorTable[(mm/2)-1]  =flsensor;
	L_SensorTable[(mm/2)-1]= lsensor;;
	FR_SensorTable[(mm/2)-1]= frsensor;
	R_SensorTable[(mm/2)-1]= rsensor;
	
	
	
}

void IRSensor_CalibrationF(void)
{
	
	int fsensor=0;
	int i;
	
	for( i=0 ; i<200 ; i++ )
	{
		fsensor+=(int)GetSensorValueReal(F_SENSOR);

		delay_ms(5);

	}
	F_Sensor = fsensor/200;
	
	printf("F Sensor : %d \r\n" , F_Sensor);
	
	
}
