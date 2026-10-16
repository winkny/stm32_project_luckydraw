#ifndef __ADC_H
#define __ADC_H	
#include "stm32f10x.h"
void Adc_Init(void);
u16  Get_Adc(u8 ch);
u16  Get_Adc3(u8 ch);
u16 Get_Adc_Average(u8 ch,u8 times); 
u16 Get_Adc_Average3(u8 ch,u8 times); 

u16 Get_Temprate(void);
u8 Get_Light(void);
#endif 
