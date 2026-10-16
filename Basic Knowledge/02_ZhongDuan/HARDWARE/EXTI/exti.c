#include "exti.h"
#include "led.h"
#include "key.h"
#include "delay.h"
#include "beep.h"

//外部中断0服务程序
void EXTIX_Init(void)
{
    EXTI_InitTypeDef EXTI_InitStructure;
    NVIC_InitTypeDef NVIC_InitStructure;

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);//使能复用功能时钟

    // 开始GPIO和EXTI的初始化
    //GPIOE.3  中断线以及中断初始化配置 下降沿触发 //KEY1
    GPIO_EXTILineConfig(GPIO_PortSourceGPIOE,GPIO_PinSource3);// 初始化GPIOE3为EXTI中断输入线
    EXTI_InitStructure.EXTI_Line=EXTI_Line3; // 因为输入线为PE3，所以需要初始化EXTI Line3
    EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt; // 设为中断模式
    EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling; // 下降沿触发中断
    EXTI_Init(&EXTI_InitStructure);  //根据EXTI_InitStruct中指定的参数初始化外设EXTI寄存器

    //GPIOE.4  中断线以及中断初始化配置  下降沿触发 //KEY0
    GPIO_EXTILineConfig(GPIO_PortSourceGPIOE,GPIO_PinSource4);// TODO: 初始化GPIOE4为EXTI中断输入线
    EXTI_InitStructure.EXTI_Line=EXTI_Line4;// TODO: 因为输入线为PE4，所以需要初始化EXTI Line4
    EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;// TODO: 设为中断模式
    EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;// TODO: 下降沿触发中断
    EXTI_Init(&EXTI_InitStructure);// TODO: 根据EXTI_InitStruct中指定的参数初始化外设EXTI寄存器

    //GPIOA.0  中断线以及中断初始化配置 上升沿触发 PA0  WK_UP
    GPIO_EXTILineConfig(GPIO_PortSourceGPIOA,GPIO_PinSource0);// TODO: 初始化GPIOA0为EXTI中断输入线
    EXTI_InitStructure.EXTI_Line=EXTI_Line0;// TODO: 因为输入线为PA0，所以需要初始化EXTI Line0
    EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;// TODO: 设为中断模式
    EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising;// TODO: 上升沿触发中断
    EXTI_Init(&EXTI_InitStructure);// TODO: 根据EXTI_InitStruct中指定的参数初始化外设EXTI寄存器

    // 开始NVIC的初始化
    // EXTI3对应的NVIC通道
    NVIC_InitStructure.NVIC_IRQChannel = EXTI3_IRQn;//使能按键KEY1所在的外部中断通道
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x02;//抢占优先级2
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x01;//子优先级1
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;//使能外部中断通道
    NVIC_Init(&NVIC_InitStructure);//根据NVIC_InitStruct中指定的参数初始化外设NVIC寄存器

    // EXTI4对应的NVIC通道
    NVIC_InitStructure.NVIC_IRQChannel = EXTI4_IRQn;// TODO: 使能按键KEY0所在的外部中断通道: EXTI4_IRQn
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x02;// TODO: 设定抢占优先级2 
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x02;// TODO: 设定子优先级2
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;// TODO: 使能外部中断通道
    NVIC_Init(&NVIC_InitStructure);// TODO: 根据NVIC_InitStruct中指定的参数初始化外设NVIC寄存器
    
    // EXTI0对应的NVIC通道
    NVIC_InitStructure.NVIC_IRQChannel = EXTI0_IRQn;// TODO: 使能按键KEY0所在的外部中断通道: EXTI0_IRQn
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x02;// TODO: 设定抢占优先级2
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x03;// TODO: 设定子优先级3
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;// TODO: 使能外部中断通道
    NVIC_Init(&NVIC_InitStructure);// TODO: 根据NVIC_InitStruct中指定的参数初始化外设NVIC寄存器

}

//外部中断0服务程序 
void EXTI0_IRQHandler(void)
{
    u8 currPB8;
    delay_ms(10);//消抖
    currPB8 = GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_8);// TODO: 读取当前LED1灯的状态
    if(GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_0)==0)// TODO: 如当前PE3为低电平，说明按下的是按键KEY1
    {
        GPIO_WriteBit(GPIOB, GPIO_Pin_8, !currPB8);// TODO: 切换LED1灯的状态
    }
    EXTI_ClearITPendingBit(EXTI_Line0); //TODO: 清除EXTI LINE0上的中断标志位(重要)
}

//外部中断3服务程序
void EXTI3_IRQHandler(void)
{
    u8 currPE5;
    delay_ms(10);//消抖
    currPE5 = GPIO_ReadInputDataBit(GPIOE, GPIO_Pin_5); // 读取当前LED1灯的状态
    if(GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_3)==0) // 如当前PE3为低电平，说明按下的是按键KEY1
    {
        GPIO_WriteBit(GPIOE, GPIO_Pin_5, !currPE5); // 切换LED1灯的状态
    }
    EXTI_ClearITPendingBit(EXTI_Line3);  //清除EXTI LINE3上的中断标志位(重要)
}

//外部中断4服务程序
void EXTI4_IRQHandler(void)
{
    u8 currPB5;
    u8 currPE5;
    delay_ms(10);//消抖
    currPB5 = GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_5);
    currPE5 = GPIO_ReadInputDataBit(GPIOE, GPIO_Pin_5);// TODO: 读取当前LED0和LED1灯的状态
    if(GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_8)==0)// TODO: 如当前PE4为低电平，说明按下的是按键KEY0
    {
        GPIO_WriteBit(GPIOB, GPIO_Pin_5, !currPB5);
        GPIO_WriteBit(GPIOE, GPIO_Pin_5, !currPE5);// TODO: 同时切换LED0和1灯的状态
    }
    EXTI_ClearITPendingBit(EXTI_Line4);//TODO: 清除EXTI LINE4上的中断标志位(重要)
}
 
