 #include "adc.h"
 #include "delay.h"
//初始化ADC
//仅以规则通道为例
//默认将开启通道0~3
void  Adc_Init(void)
{
    ADC_InitTypeDef ADC_InitStructure; 
    GPIO_InitTypeDef GPIO_InitStructure;

    //时钟配置
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1|RCC_APB2Periph_GPIOA,ENABLE );//使能ADC1通道时钟，使用RCC_APB2PeriphClockCmd
    RCC_ADCCLKConfig(RCC_PCLK2_Div6);//将ADC分频因子设置为6，使得ADC的时钟信号源为72M/6=12 MHz,保证ADC最大采样频率不超过14MHz
    // 使用RCC_ADCCLKConfig函数和RCC_PCLK2_Div6参数

    GPIO_InitStructure.GPIO_Pin =GPIO_Pin_1;//PA1 作为模拟通道输入引脚，读取PA1上的电平
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;//模拟输入模式GPIO_Mode_AIN
    GPIO_Init(GPIOA, &GPIO_InitStructure);
	

    //复位ADC1,将外设 ADC1 的全部寄存器重设为缺省值，使用ADC_DeInit
    ADC_DeInit(ADC1);
    ADC_InitStructure.ADC_Mode = ADC_Mode_Independent;//ADC工作模式:工作在独立模式
    ADC_InitStructure.ADC_ScanConvMode = DISABLE;//模数转换工作在单通道模式
    ADC_InitStructure.ADC_ContinuousConvMode = DISABLE;//模数转换工作在单次转换模式
    ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;//转换由软件而不是外部触发启动
    ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;//ADC数据右对齐
    ADC_InitStructure.ADC_NbrOfChannel = 1;//顺序进行规则转换的ADC通道的数目
    ADC_Init(ADC1, &ADC_InitStructure);//根据ADC_InitStruct中指定的参数初始化外设ADCx的寄存器   

    ADC_Cmd(ADC1, ENABLE);//使能ADC1
    ADC_ResetCalibration(ADC1);//使能复位校准
    while(ADC_GetResetCalibrationStatus(ADC1));//等待复位校准结束
    ADC_StartCalibration(ADC1);//开启ADC自动校准
    while(ADC_GetCalibrationStatus(ADC1));//等待校准结束
		
		//tempt
		ADC_TempSensorVrefintCmd(ENABLE); 
		ADC_Cmd(ADC1, ENABLE);
		ADC_ResetCalibration(ADC1);
		while(ADC_GetResetCalibrationStatus(ADC1)); 
		ADC_StartCalibration(ADC1);
		while(ADC_GetCalibrationStatus(ADC1));
		
		//light  PF8
		
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC3|RCC_APB2Periph_GPIOF,ENABLE );//使能ADC1通道时钟，使用RCC_APB2PeriphClockCmd
    RCC_ADCCLKConfig(RCC_PCLK2_Div6);//将ADC分频因子设置为6，使得ADC的时钟信号源为72M/6=12 MHz,保证ADC最大采样频率不超过14MHz
    // 使用RCC_ADCCLKConfig函数和RCC_PCLK2_Div6参数

    GPIO_InitStructure.GPIO_Pin =GPIO_Pin_8;//PA1 作为模拟通道输入引脚，读取PA1上的电平
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;//模拟输入模式GPIO_Mode_AIN
    GPIO_Init(GPIOF, &GPIO_InitStructure);
		 //复位ADC3,将外设 ADC3 的全部寄存器重设为缺省值，使用ADC_DeInit
    ADC_DeInit(ADC3);
    ADC_InitStructure.ADC_Mode = ADC_Mode_Independent;//ADC工作模式:工作在独立模式
    ADC_InitStructure.ADC_ScanConvMode = DISABLE;//模数转换工作在单通道模式
    ADC_InitStructure.ADC_ContinuousConvMode = DISABLE;//模数转换工作在单次转换模式
    ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;//转换由软件而不是外部触发启动
    ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;//ADC数据右对齐
    ADC_InitStructure.ADC_NbrOfChannel = 1;//顺序进行规则转换的ADC通道的数目
    ADC_Init(ADC3, &ADC_InitStructure);//根据ADC_InitStruct中指定的参数初始化外设ADCx的寄存器   

    ADC_Cmd(ADC3, ENABLE);//使能ADC3
    ADC_ResetCalibration(ADC3);//使能复位校准
    while(ADC_GetResetCalibrationStatus(ADC3));//等待复位校准结束
    ADC_StartCalibration(ADC3);//开启ADC自动校准
    while(ADC_GetCalibrationStatus(ADC3));//等待校准结束
		
}
//获得ADC值
//ch:通道值 0~3
u16 Get_Adc(u8 ch)
{
    //设置指定ADC的规则组通道，一个序列，采样时间，使用ADC_RegularChannelConfig
    ADC_RegularChannelConfig(ADC1, ch, 1, ADC_SampleTime_239Cycles5 );//此处指定ADC1,ADC通道为输入的参数ch,采样时间为239.5周期（ADC_SampleTime_239Cycles5）
    ADC_SoftwareStartConvCmd(ADC1, ENABLE);//使能指定的ADC1的软件转换启动功能，使ADC开始采样转换工作，使用ADC_SoftwareStartConvCmd
    while(!ADC_GetFlagStatus(ADC1, ADC_FLAG_EOC ));//等待转换结束，使用while和ADC_GetFlagStatus函数
    return ADC_GetConversionValue(ADC1);//返回最近一次ADC1规则组的转换结果，使用ADC_GetConversionValue函数获取ADC转换结果
}
u16 Get_Adc3(u8 ch)
{
    //设置指定ADC的规则组通道，一个序列，采样时间，使用ADC_RegularChannelConfig
    ADC_RegularChannelConfig(ADC3, ch, 1, ADC_SampleTime_239Cycles5 );//此处指定ADC1,ADC通道为输入的参数ch,采样时间为239.5周期（ADC_SampleTime_239Cycles5）
    ADC_SoftwareStartConvCmd(ADC3, ENABLE);//使能指定的ADC1的软件转换启动功能，使ADC开始采样转换工作，使用ADC_SoftwareStartConvCmd
    while(!ADC_GetFlagStatus(ADC3, ADC_FLAG_EOC ));//等待转换结束，使用while和ADC_GetFlagStatus函数
    return ADC_GetConversionValue(ADC3);//返回最近一次ADC1规则组的转换结果，使用ADC_GetConversionValue函数获取ADC转换结果
}
// 多次采样计算平均值
u16 Get_Adc_Average(u8 ch,u8 times)
{
    u32 temp_val=0;
    u8 t;
    for(t=0;t<times;t++)
    {
        temp_val+=Get_Adc(ch);//使用Get_Adc获取ADC转换结果，并累加存入变量temp_val中
        delay_ms(5);
    }
    return temp_val/times;
}
u16 Get_Adc_Average3(u8 ch,u8 times)
{
    u32 temp_val=0;
    u8 t;
    for(t=0;t<times;t++)
    {
        temp_val+=Get_Adc3(ch);//使用Get_Adc获取ADC转换结果，并累加存入变量temp_val中
        delay_ms(5);
    }
    return temp_val/times;
}
//tempt
u16 Get_Temprate(void)
{
		u32 adct;
		short result;
		float  temperate;
		adct=Get_Adc_Average(ADC_Channel_16,20);
		temperate=(float)adct*(3.3/4096); 
		temperate=(1.43-temperate)/0.0043+25; 
		result=temperate*=100;
		return result;
}

//feel light
u8 Get_Light(void)
{
		u32 temp_val=0;
	  temp_val=Get_Adc_Average3(ADC_Channel_6,20);
		if(temp_val>4000)
					temp_val=4000;
		return (u8)(100-(temp_val/40));
}













