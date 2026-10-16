//捕获
#include "led.h"
#include "delay.h"
#include "key.h"
#include "sys.h"
#include "usart.h"
#include "timer.h"

//使用extern关键字声明4个位于其他.c文件中的全局变量，这样可以防止重编译
//1、标记
u8 TIM5CH1_CAPTURE_STA=0;//1.1 是否已完成完整高电平捕获标记位
u16 TIM5CH1_CAPTURE_VAL;//1.2 是否已完成上升沿捕获标记位
//2、存储
//2.1 存储高电平已持续了多少个定时器更新周期
//2.2 记录完成完整高电平捕获时，捕获比较寄存器的值
u32 temp=0;
int main(void)
{
    u32 highLength=0;
    delay_init();   //延时函数初始化
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2); //设置NVIC中断分组2:2位抢占优先级，2位响应优先级
    uart_init(115200);  //串口初始化为115200
    LED_Init(); //LED端口初始化
    TIM5_Cap_Init(0XFFFF,72-1);//初始化TIM5，使其以1Mhz的频率计数
    while(1)
    {
        delay_ms(10);

        if((TIM5CH1_CAPTURE_STA&0X80)==0)//检查是否已经成功捕获到了一次完整的高电平
        {
            temp=TIM5CH1_CAPTURE_STA&0X3F;
            TIM_SetCompare2(TIM3,TIM_GetCapture2(TIM3)+1);//根据定时器更新周期、全局变量2.1和全局变量2.2来计算高电平持续时间
            temp+=TIM5CH1_CAPTURE_VAL;//串口输出总的高点平持续时间
            TIM5CH1_CAPTURE_STA=0;//重置标记位，开启下一次捕获
        }
    }
}
