#include "wakeup.h"
#include "key.h"
#include "delay.h"
#include "led.h"
    
void Sys_Standby(void)
{ 
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_PWR, ENABLE); //使能pwr电源时钟
    PWR_WakeUpPinCmd(ENABLE); //使能唤醒管脚功能
    PWR_EnterSTANDBYMode(); //进入待机模式
}

void Sys_Enter_Standby(void)//系统进入待机状态
{
    RCC_APB2PeriphResetCmd(0X01FC,DISABLE); 
    Sys_Standby();
}

u8 Check_WKUP(void) 
{
    u8 time=0; //记录按下的时间
		u8  key=0;
    LED_Init(); 
	//	LED1=0;
	  key=KEY_Scan(1);
    while(1)
    {
			
        if(key==KEY1_PRES)
        {
            time++; //已经按下了
            delay_ms(30);
            if(time>=100) //按下超过三秒
            {
                LED1=1;
							  printf("EXIT!!!");
                return 1; //按下3秒以上
            }
        }
        else 
        { 
            LED1=0;
            return 0; //不足三秒
        }
    }
} 
