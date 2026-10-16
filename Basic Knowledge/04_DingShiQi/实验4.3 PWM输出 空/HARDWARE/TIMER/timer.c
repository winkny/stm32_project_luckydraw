//pwm
#include "timer.h"
#include "led.h"

//TIM3 PWM部分初始化 
//PWM输出初始化
//arr：自动重装值
//psc：时钟预分频数
void TIM3_PWM_Init(u16 arr,u16 psc)
{  
    GPIO_InitTypeDef GPIO_InitStructure;
    TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
    TIM_OCInitTypeDef  TIM_OCInitStructure;

    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE); ///使能定时器3时钟
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO|RCC_APB2Periph_GPIOB, ENABLE);//使能GPIO外设和AFIO复用功能模块时钟RCC_APB2Periph_AFIO

    //开启GPIO口的部分重映射，使用GPIO_PinRemapConfig，将Timer3部分重映射（GPIO_PartialRemap_TIM3），使TIM3_CH2可输出至PB5
    GPIO_PinRemapConfig(GPIO_PartialRemap_TIM3, ENABLE);
    
    //设置PB5引脚为复用输出功能，可输出TIM3 CH2的PWM脉冲波形
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5;//选择PB5
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;//复用推挽输出模式
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;//驱动频率50MHz
    GPIO_Init(GPIOB, &GPIO_InitStructure);//完成初始化GPIO PB5

    //初始化TIM3
    TIM_TimeBaseStructure.TIM_Period = arr;//设置在下一个更新事件装入活动的自动重装载寄存器周期的值
    TIM_TimeBaseStructure.TIM_Prescaler =psc;//设置用来作为TIMx时钟频率除数的预分频值
    TIM_TimeBaseStructure.TIM_ClockDivision = 0; ///设置时钟分割:TDTS = Tck_tim，不分割
    TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;///TIM向上计数模式
    TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure);//根据TIM_TimeBaseInitStruct中指定的参数初始化TIMx的时间基数单位

    //初始化TIM3 Channel2 PWM模式
    TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM2;//选择定时器模式:TIM脉冲宽度调制模式2
    TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;//比较输出使能
    TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;//输出极性:TIM输出比较极性为高电平
    TIM_OC2Init(TIM3, &TIM_OCInitStructure);//根据指定的参数初始化外设TIM3 OC2

    //使能TIM3在CCR2上的预装载寄存器
    TIM_OC2PreloadConfig(TIM3, TIM_OCPreload_Enable);
    TIM_Cmd(TIM3, ENABLE);//使能TIM3
}


