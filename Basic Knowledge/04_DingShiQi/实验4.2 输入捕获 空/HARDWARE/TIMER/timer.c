//捕获
#include "timer.h"
#include "led.h"

//通用定时器3中断初始化
//这里时钟选择为APB1时钟的2倍，APB1时钟为36MHz
//arr：自动重装值。
//psc：时钟预分频数
//这里使用的是定时器3!
void TIM3_Int_Init(u16 arr,u16 psc)
{
    TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
    NVIC_InitTypeDef NVIC_InitStructure;

    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE); //时钟使能

    //定时器TIM3初始化
    TIM_TimeBaseStructure.TIM_Period = arr; //设置在下一个更新事件装入活动的自动重装载寄存器周期的值
    TIM_TimeBaseStructure.TIM_Prescaler =psc; //设置用来作为TIMx时钟频率除数的预分频值
    TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1; //设置时钟分割:TDTS = Tck_tim
    TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIM向上计数模式
    TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure); //根据指定的参数初始化TIMx的时间基数单位

    TIM_ITConfig(TIM3,TIM_IT_Update,ENABLE ); //使能指定的TIM3中断,允许更新中断

    //中断优先级NVIC设置
    NVIC_InitStructure.NVIC_IRQChannel = TIM3_IRQn;  //TIM3中断
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;  //先占优先级0级
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;  //从优先级3级
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; //IRQ通道被使能
    NVIC_Init(&NVIC_InitStructure);  //初始化NVIC寄存器

    TIM_Cmd(TIM3, ENABLE);  //使能TIMx
}
//定时器3中断服务程序
void TIM3_IRQHandler(void)   //TIM3中断
{
    if (TIM_GetITStatus(TIM3, TIM_IT_Update) != RESET)  //检查TIM3更新中断发生与否
    {
        TIM_ClearITPendingBit(TIM3, TIM_IT_Update  );  //清除TIMx更新中断标志 
        LED1=!LED1;
    }
}


// 输入捕获实验
//定时器5通道1输入捕获配置
void TIM5_Cap_Init(u16 arr,u16 psc)
{
    GPIO_InitTypeDef GPIO_InitStructure;
    TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
    NVIC_InitTypeDef NVIC_InitStructure;
    TIM_ICInitTypeDef  TIM5_ICInitStructure;

    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM5, ENABLE);//使能TIM5时钟：RCC_APB1Periph_TIM5
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);//使能GPIOA时钟

    //初始化定时器5 TIM5
    TIM_TimeBaseStructure.TIM_Period = arr;//设定计数器自动重装值 
    TIM_TimeBaseStructure.TIM_Prescaler =psc;//预分频器   
    TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;//设置时钟分割为TIM_CKD_DIV1，即TDTS = Tck_tim
    TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;//TIM向上计数模式
    TIM_TimeBaseInit(TIM5, &TIM_TimeBaseStructure);//根据TIM_TimeBaseInitStruct中指定的参数初始化TIMx的时间基数单位
    /*
    *初始化TIM5输入捕获参数
    *CC1S=01   选择输入端 IC1映射到TI1上
    *上升沿捕获
    *映射到TI1上
    *配置输入分频,不分频 
    *IC1F=0000 配置输入滤波器 不滤波
    *使用TIM_ICInit完成初始化
    */
    TIM5_ICInitStructure.TIM_Channel = TIM_Channel_1;
    TIM5_ICInitStructure.TIM_ICPolarity = TIM_ICPolarity_Rising;
    TIM5_ICInitStructure.TIM_ICSelection = TIM_ICSelection_DirectTI;
    TIM5_ICInitStructure.TIM_ICPrescaler = TIM_ICPSC_DIV1;
    TIM5_ICInitStructure.TIM_ICFilter = 0x00;
    TIM_ICInit(TIM5, &TIM5_ICInitStructure);

    //中断分组初始化
    //TIM5中断
    //先占优先级2级
    //从优先级0级
    //IRQ通道被使能
    //根据NVIC_InitStruct中指定的参数初始化外设NVIC寄存器 
    NVIC_InitStructure.NVIC_IRQChannel = TIM5_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; 
    NVIC_Init(&NVIC_InitStructure);
    TIM_ITConfig( TIM5,TIM_IT_Update|TIM_IT_CC1,ENABLE);//允许更新中断 ,允许CC1捕获中断
    TIM_Cmd(TIM5,ENABLE );//使能定时器5
}

//声明4个全局变量，用于存储
//1、标记
//1.1 是否已完成完整高电平捕获标记位
//1.2 是否已完成上升沿捕获标记位
u8 TIM5CH1_CAPTURE_STA=0;
u16 TIM5CH1_CAPTURE_VAL;
//2、存储
//2.1 存储高电平已持续了多少个定时器更新周期
//2.2 记录完成完整高电平捕获时，捕获比较寄存器的值
///////////////////////////////??????????????????

//定时器5中断服务程序
void TIM5_IRQHandler(void)
{ 

    if((TIM5CH1_CAPTURE_STA&0X80)==0)// 检查捕获状态，是否已完成一次高电平的完整捕获？
    {//还未成功捕获
        if (TIM_GetITStatus(TIM5, TIM_IT_Update) != RESET)// 检查是否因为定时器更新中断进入此函数
        {//是定时器更新中断
            if(TIM5CH1_CAPTURE_STA&0X40)// 检查是否已经捕获到上升沿了
            {// 已捕获到上升沿（还没有捕获到下降沿）
                if((TIM5CH1_CAPTURE_STA&0X3F)==0X3F)//高电平持续时间太长，可直接结束捕获，并认为已经完成一次捕获
                {
                    TIM5CH1_CAPTURE_STA|=0X80;//标记成功捕获了一次
                    TIM5CH1_CAPTURE_VAL=0XFFFF;//存储当前捕获比较寄存器的值为0xFFFF
                }
                else //高电平仍在持续中，但还未超出预定时间长度
                {
                    TIM5CH1_CAPTURE_STA++;//记录高电平持续时间又过了一个定时器周期
                }
            }
        }
        // 检查是否因为定时器捕获中断进入此函数
        if (TIM_GetITStatus(TIM5, TIM_IT_CC1) != RESET)
        {
            if(TIM5CH1_CAPTURE_STA&0X40)
            {
                TIM5CH1_CAPTURE_STA|=0X80;
                TIM5CH1_CAPTURE_VAL=TIM_GetCapture1(TIM5);
                TIM_OC1PolarityConfig(TIM5,TIM_ICPolarity_Rising);
            }
            else
            {
                TIM5CH1_CAPTURE_STA=0; 
                TIM5CH1_CAPTURE_VAL=0;
                TIM_SetCounter(TIM5,0);
                TIM5CH1_CAPTURE_STA|=0X40;
                TIM_OC1PolarityConfig(TIM5,TIM_ICPolarity_Falling); 
            } 
        }
    }
    TIM_ClearITPendingBit(TIM5, TIM_IT_CC1|TIM_IT_Update); //清除中断标志位
}










