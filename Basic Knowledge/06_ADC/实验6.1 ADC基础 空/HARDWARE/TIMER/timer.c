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

    //使能定时器3时钟
    //使能GPIO外设和AFIO复用功能模块时钟RCC_APB2Periph_AFIO

    //开启GPIO口的部分重映射，使用GPIO_PinRemapConfig，将Timer3部分重映射（GPIO_PartialRemap_TIM3），使TIM3_CH2可输出至PB5

    //设置PB5引脚为复用输出功能，可输出TIM3 CH2的PWM脉冲波形
    //选择PB5
    //复用推挽输出模式
    //驱动频率50MHz
    //完成初始化GPIO PB5

    //初始化TIM3
    //设置在下一个更新事件装入活动的自动重装载寄存器周期的值
    //设置用来作为TIMx时钟频率除数的预分频值
    //设置时钟分割:TDTS = Tck_tim，不分割
    //TIM向上计数模式
    //根据TIM_TimeBaseInitStruct中指定的参数初始化TIMx的时间基数单位

    //初始化TIM3 Channel2 PWM模式
    //选择定时器模式:TIM脉冲宽度调制模式2
    //比较输出使能
    //输出极性:TIM输出比较极性为高电平
    //根据指定的参数初始化外设TIM3 OC2

    //使能TIM3在CCR2上的预装载寄存器

    //使能TIM3
}


