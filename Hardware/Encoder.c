#include "stm32f10x.h"                  // Device header
void Encoder_Init(void)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3,ENABLE);
	
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_IPU;
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_6|GPIO_Pin_7;
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIO_InitStructure);
	
	TIM_TimeBaseInitTypeDef TIM_InitStrucutre;
	TIM_InitStrucutre.TIM_ClockDivision=TIM_CKD_DIV1;
	TIM_InitStrucutre.TIM_CounterMode=TIM_CounterMode_Up;//被编码器托管无效
	TIM_InitStrucutre.TIM_Period=65535;
	TIM_InitStrucutre.TIM_Prescaler=0;
	TIM_TimeBaseInit(TIM3,&TIM_InitStrucutre);
	
	TIM_ICInitTypeDef TIM_ICInitStructure;
	TIM_ICStructInit(&TIM_ICInitStructure);//给结构体赋一个初始值
	TIM_ICInitStructure.TIM_Channel=TIM_Channel_1;
	TIM_ICInitStructure.TIM_ICFilter=0xF;
	TIM_ICInitStructure.TIM_ICPolarity=TIM_ICPolarity_Rising;//其余参数与编码器无关
	TIM_ICInit(TIM3,&TIM_ICInitStructure);

	TIM_ICInitStructure.TIM_Channel=TIM_Channel_2;
	TIM_ICInitStructure.TIM_ICFilter=0xF;
	TIM_ICInitStructure.TIM_ICPolarity=TIM_ICPolarity_Rising;//对于编码器来说并不意味着只有上升沿有效，对于他来说上升沿和下降沿都有效。这里设置为Rising意思是电平极性不反转，即TI2不反相
	TIM_ICInit(TIM3,&TIM_ICInitStructure);
	//Encoder函数必须在ICInit函数下面
	TIM_EncoderInterfaceConfig(TIM3,TIM_EncoderMode_TI12,TIM_ICPolarity_Rising,TIM_ICPolarity_Rising);
	TIM_Cmd(TIM3,ENABLE);
}
int16_t Encoder_Get(void)
{
	int16_t you;
	you=TIM_GetCounter(TIM3);
	TIM_SetCounter(TIM3,0);
	return you;
}