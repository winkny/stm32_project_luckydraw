#include "delay.h"

static u8  fac_us=0;//us延时倍乘数
static u16 fac_ms=0;//ms延时倍乘数,在ucos下,代表每个节拍的ms数

void delay_init()
{
    SysTick_CLKSourceConfig(SysTick_CLKSource_HCLK_Div8);
    fac_us=SystemCoreClock/8000000;

    fac_ms=(u16)fac_us*1000;
}

//延时nms
//注意nms的范围
//SysTick->LOAD为24位寄存器,所以,最大延时为:
//nms<=0xffffff*8*1000/SYSCLK
//SYSCLK单位为Hz,nms单位为ms
//对72M条件下,nms<=1864 
void delay_ms(u16 nms)
{
    u32 temp;
    SysTick->LOAD=(u32)nms*fac_ms;//时间加载(SysTick->LOAD为24bit)
    SysTick->VAL =0x00;//清空计数器
    SysTick->CTRL|=SysTick_CTRL_ENABLE_Msk ;//开始倒数
    do
    {
        temp=SysTick->CTRL;
    }while((temp&0x01)&&!(temp&(1<<16)));//等待时间到达   
    SysTick->CTRL&=~SysTick_CTRL_ENABLE_Msk;//关闭计数器
    SysTick->VAL =0X00;//清空计数器
}

/*
void delay_set(u32 nms)
{
    systemTimeInMS = 0;
    systickDelayTimeInMs = nms;
}
void SysTick_Handler(void)
{
    systemTimeInMS++;
    if (systemTimeInMS % systickDelayTimeInMs == 0)
    {
        GPIO_WriteBit(GPIOB, GPIO_Pin_5,!GPIO_ReadOutputDataBit(GPIOB, GPIO_Pin_5));
    }
}


volatile u32 systemTimeInMS = 0;
void delay_IRQ(u32 nms)
{
    systemTimeInMS = 0;
    while(systemTimeInMS < nms) ;
}

void SysTick_Handler(void)
{
    systemTimeInMS++;
}

*/




































