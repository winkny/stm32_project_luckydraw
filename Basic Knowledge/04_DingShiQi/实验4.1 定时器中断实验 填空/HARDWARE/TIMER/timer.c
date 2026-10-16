//timer
#include "timer.h"
#include "led.h"

//通用定时器3中断初始化
//这里时钟选择为APB1时钟的2倍，APB1时钟为36MHz
//arr：自动重装值。
//psc：时钟预分频数
//这里使用的是定时器3!
void TIM3_Int_Init(u16 arr,u16 psc)
{
    // TODO: 声明变量，类型为TIM_TimeBaseInitTypeDef、NVIC_InitTypeDef
    TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
    NVIC_InitTypeDef NVIC_InitStructure;
    // TODO: 使能TIM3的时钟，使用RCC_APB1PeriphClockCmd
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3,ENABLE);
    //定时器TIM3初始化
    // TODO: 配置TIM3，设定自动重装载寄存器周期、预分频值、时钟分割、计数模式，完成时基单元的初始化
    TIM_TimeBaseStructure.TIM_Period = 5000;
    TIM_TimeBaseStructure.TIM_Prescaler =7199; 
    TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1; 
    TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
    TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure);
    // TODO: 使能定时器更新中断TIM_IT_Update
    TIM_ITConfig(TIM3,TIM_IT_Update,ENABLE );
    //NVIC设置
    // TODO: 配置NVIC通道，选择TIM3_IRQn中断通道、设定中断优先级、使能中断通道
    NVIC_InitStructure.NVIC_IRQChannel = TIM3_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x02;// TODO: 设定抢占优先级2
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x03;// TODO: 设定子优先级3
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;// TODO: 使能外部中断通道
    NVIC_Init(&NVIC_InitStructure);// TODO: 根据NVIC_InitStruct中指定的参数初始化外设NVIC寄存器
    // TODO: 使能定时器TIM3
    TIM_Cmd(TIM3, ENABLE);
}
//定时器3中断服务程序
void TIM3_IRQHandler(void)
{
    if (TIM_GetITStatus(TIM3, TIM_IT_Update) != RESET)// TODO: 检查中断源是否为定时器更新中断TIM_IT_Update，使用TIM_GetITStatus
    {
        TIM_ClearITPendingBit(TIM3, TIM_IT_Update );// TODO: 清除TIM3的更新中断标志位
        LED1=!LED1;// TODO: 切换LED1的状态
    }
}












