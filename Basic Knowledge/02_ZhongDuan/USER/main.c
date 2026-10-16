#include "led.h"
#include "delay.h"
#include "key.h"
#include "sys.h"
#include "exti.h"
#include "beep.h"

int main(void)
{
    delay_init();//延时函数初始化
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//设置NVIC中断分组2:2位抢占优先级，2位响应优先级
    LED_Init();//初始化与LED连接的硬件接口 
    BEEP_Init();//初始化蜂鸣器IO
    KEY_Init();//按键端口初始化
    EXTIX_Init();//初始化外部中断输入 
    GPIO_ResetBits(GPIOB, GPIO_Pin_5);//先点亮红灯
    while(1)
    {
        
    }
}
