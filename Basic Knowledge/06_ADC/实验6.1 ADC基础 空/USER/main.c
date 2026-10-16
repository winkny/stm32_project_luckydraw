#include "led.h"
#include "delay.h"
#include "key.h"
#include "sys.h"
#include "usart.h"
#include "adc.h"

int main(void)
{
    u16 adcx;
    float adcV;
		float adcT;
		float adcL;
    delay_init();   //延时函数初始化
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//设置中断优先级分组为组2：2位抢占优先级，2位响应优先级
    uart_init(115200);  //串口初始化为115200
    LED_Init(); //LED端口初始化
    Adc_Init(); //ADC初始化
    while(1)
    {
			
			//val
			adcx=Get_Adc_Average(ADC_Channel_1,10);
			adcV =(float)adcx*(3.3/4096);
			adcx=adcV ;
			printf("ADC: %d\r\n", adcx);
			adcV-=adcx;
			adcV *=1000;
			printf("ADC(V): %f V\r\n", adcV);
			LED0=!LED0;
			delay_ms(250);
			
			//tempt
			adcT =Get_Temprate(); 
			if(adcT <0)
			{
					adcT =-adcT ;
					printf("-");
			}
			else
					printf(" ");
			adcT =adcT/100;
			printf("ADC(T): %f C\r\n", adcT );
			LED0=!LED0;
			delay_ms(250);
		
			//light
			adcL=Get_Light();
			printf("ADC(L): %d \r\n", adcL);
			LED0=!LED0;
			delay_ms(250);
		
    }
}

