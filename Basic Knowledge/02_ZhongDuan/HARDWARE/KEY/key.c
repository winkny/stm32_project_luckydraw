#include "stm32f10x.h"
#include "key.h"
#include "sys.h" 
//按键初始化函数
void KEY_Init(void) //IO初始化
{ 
    GPIO_InitTypeDef GPIO_InitStructure;

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_GPIOE,ENABLE);//使能PORTA,PORTE时钟

    GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_4;//KEY0
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; //设置成上拉输入
    GPIO_Init(GPIOE, &GPIO_InitStructure);//初始化GPIOE4

    // GPIOE3
    GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_4;//TODO: KEY1
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;//TODO: 设置成上拉输入
    GPIO_Init(GPIOE, &GPIO_InitStructure);//TODO: 初始化GPIOE4
    
    // GPIOA0
    GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_0;//TODO: 初始化 WK_UP-->GPIOA.0 下拉输入
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD;//TODO: PA0设置成输入，默认下拉	  
    GPIO_Init(GPIOA, &GPIO_InitStructure);//TODO: 初始化GPIOA.0
}

