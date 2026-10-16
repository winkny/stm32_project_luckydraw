#include "led.h"
#include "delay.h"
#include "key.h"
#include "sys.h"
#include "usart.h"
#include "dma.h"
#include <stdlib.h>
#include "wakeup.h"
#define N 200
int main()
{
//变量
	  u8 t=0;
	  u16 len;//用户输入的节点数的长度
		u8 i,j;//中间变量
		u16 m[N],n;
		u8 X[N];//char
	  u8 Y[N];
		u16 x,y;//记录节点数
		u16 flag=0;
	  u16 times=0;
	  u16 a=0,b=0;//record char length
//初始化
	  BEEP_Init();
	  delay_init();   //延时函数初始化
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//设置中断优先级分组为组2：2位抢占优先级，2位响应优先级
    uart_init(115200);    //串口初始化为12500
    LED_Init(); //初始化与LED连接的硬件接口
    KEY_Init(); //按键初始化
//运行
	  printf("/////////////\r\n 祝你好运！！！\r\n");
	  GPIO_ResetBits(GPIOB, GPIO_Pin_5);//亮
	  printf("请输入节点个数和中奖节点个数，并用空格分开):\r\n");
		while(1)
		{
			if(USART_RX_STA&0x8000)
			 {
						len=USART_RX_STA&0x3f;
							for(t=0;t<len;t++)
							{ 
									
									if(USART_RX_BUF[t]!=' ')
									{
												printf("X is \r\n");
											  USART_SendData(USART1, USART_RX_BUF[t]);
										    printf("\r\n"); 	  
												X[t]=USART_RX_BUF[t];
										    //printf("X=%s\r\n",X[t]);
												x=(u16)(X[t])-48;//ASC11 to num
												while(USART_GetFlagStatus(USART1,USART_FLAG_TC)!=SET);
												printf(" \r\n"); 
									}
									else 
									{
												printf("Y is \r\n");
												 t=t+1;
												USART_SendData(USART1, USART_RX_BUF[t]);
												printf("\r\n"); 
										    Y[t]=USART_RX_BUF[t];
										   // printf("Y=%s\r\n",Y[t]);
												y=(u16)(Y[t])-48;//ASC11 to num
												while(USART_GetFlagStatus(USART1,USART_FLAG_TC)!=SET);
												printf("\r\n"); 
									}
							    
							}
						USART_RX_STA=0;
						break;
				}
		}
    printf("x=%d,y=%d\r\n",x,y);
		printf("开始抽奖\r\n");
    printf("请按按钮\r\n");//key0
		
while(1)
{		
	  GPIO_ResetBits(GPIOB, GPIO_Pin_5);//亮
		LED1=0;
		for(i=0;i<y;i++)
		{
				m[i]=rand()%x;
				for(j=0;j<i;j++)
				{
					if(m[i]==m[j])i--;
				}
		}
		m[y]=rand()%x;


		t=KEY_Scan(0);//搜索KEY0的状态
				if(Check_WKUP()==1)
		{
				
        Sys_Enter_Standby();
    
		}
		else
		{
				if(t==KEY0_PRES)//KEY0按下
				{
						for(i=0;i<y;i++)
						{
							if(m[i]==m[y])
							{
								flag=1;
							}
						}
						if(flag==1)
						{
							printf("wooooo\r\n恭喜你抽中了!!!\r\n");
							GPIO_SetBits(GPIOB,GPIO_Pin_8);
							delay_ms(1000);
							delay_ms(1000);//delay 2s
							GPIO_ResetBits(GPIOB,GPIO_Pin_8);
							GPIO_SetBits(GPIOB, GPIO_Pin_5);//灭
							LED1=1;
							break;
						}
						else
						{
							printf("owo很遗憾没能抽中\r\n");
							GPIO_SetBits(GPIOB,GPIO_Pin_8);
							delay_ms(300);//delay 0.3s
							GPIO_ResetBits(GPIOB,GPIO_Pin_8);
						}
				}
			}
}
for(i=0;i<y;i++)
		{
				printf("%d ",m[i]);
		}

	return 0;
}
