#include "led.h"
#include "delay.h"
#include "key.h"
#include "sys.h"
#include "usart.h"
#include "dma.h"

#define SEND_BUF_SIZE 8200  //发送数据长度,最好等于sizeof(TEXT_TO_SEND)+2的整数倍.

u8 SendBuff[SEND_BUF_SIZE]; //发送数据缓冲区
const u8 TEXT_TO_SEND[]={"STM32F1 DMA 串口实验"};
int main(void)
{
    u16 i;
    u8 t=0;
    u8 j,mask=0;
    float pro=0;//进度

    delay_init();   //延时函数初始化
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//设置中断优先级分组为组2：2位抢占优先级，2位响应优先级
    uart_init(9600);    //串口初始化为9600
    LED_Init(); //初始化与LED连接的硬件接口
    KEY_Init(); //按键初始化
    //DMA1通道4,外设为串口1,存储器为SendBuff,长度为SEND_BUF_SIZE.

    j=sizeof(TEXT_TO_SEND);
    for(i=0;i<SEND_BUF_SIZE;i++)//填充数据到SendBuff
    {
        if(t>=j)//加入换行符
        {
            if(mask)
            {
                SendBuff[i]=0x0a;
                t=0;
            }else 
            {
                SendBuff[i]=0x0d;
                mask++;
            }
        }else//复制TEXT_TO_SEND语句
        {
            mask=0;
            SendBuff[i]=TEXT_TO_SEND[t];
            t++;
        }
    }
    i=0;
    // 主循环
    while(1)
    {
        t=KEY_Scan(0);//搜索KEY0的状态
        if(t==KEY0_PRES)//KEY0按下
        {
            // 传输开始，红灯亮
            USART_DMACmd (USART1,USART_DMAReq_Tx ,ENABLE );//使能串口1的DMA发送，使用USART_DMACmd
            MYDMA_Enable (DMA1_Channel4 );//调用MYDMA_Enable，开始一次DMA传输
            //等待DMA传输完成，此时我们来做另外一些事，如点灯或灭灯
            //实际应用中，传输数据期间，可以执行另外的任务
            if(DMA_GetFlagStatus (DMA1_FLAG_TC4))//检查DMA通道4传输是否完成
            {//已完成
                DMA_ClearFlag(DMA1_FLAG_TC4);//清除通道4传输完成标志
								break;
            }
        }
        t=KEY_Scan(1);//搜索KEY1的状态
        if(t==KEY1_PRES)//KEY1按下
        {
            // 传输开始，绿灯亮
            for(i=0;i<SEND_BUF_SIZE;i++)
            {//依次发送缓冲区的数据
                USART_SendData(USART1,USART_RX_BUF[i]); //使用USART_SendData发送一个字节
                while(USART_GetFlagStatus(USART1,USART_FLAG_TC)!=SET);//利用USART_GetFlagStatus检查USART1的USART_FLAG_TC标记位，配合while，等待USART1发送完成
            }
            // 传输结束，绿灯熄灭
        }

    }
}
