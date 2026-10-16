#include <stdio.h>
#include "led.h"
#include "stm32f10x_gpio.h"

/*
typedef struct 
{ 
    u16 GPIO_Pin; 
    GPIOSpeed_TypeDef GPIO_Speed; 
    GPIOMode_TypeDef GPIO_Mode; 
}GPIO_InitTypeDef;
*/
void ledInit(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;
    
//    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);
//    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOE,ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB | RCC_APB2Periph_GPIOE, ENABLE);
  //u32 i;
   // GPIO_InitTypeDef GPIO_InitStructure;
   //GPIO_StructInit(&GPIO_InitStructure);
    //结构体变量赋值
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5; //管脚
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz; //管脚速率
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_Init(GPIOB,&GPIO_InitStructure);
    GPIO_SetBits(GPIOB,GPIO_Pin_5);//????
    
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5;
    GPIO_Init(GPIOE,&GPIO_InitStructure);
    GPIO_SetBits(GPIOE,GPIO_Pin_5);
    //????????
//    //GPIOB和GPIOE时钟初始化
//    GPIO_Init(GPIOB, &GPIO_InitStructure);
//        //GPIO_ResetBits(GPIOB,GPIO_Pin_5);
//    GPIO_Init(GPIOE, &GPIO_InitStructure);
}
