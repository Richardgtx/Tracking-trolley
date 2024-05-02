#include "stm32f10x.h"                  // Device header

void Pwm_Init(void)
{
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);//RCC时钟
	
	TIM_InternalClockConfig(TIM2);//时钟源选择
	
	TIM_TimeBaseInitTypeDef Sa;
	Sa.TIM_ClockDivision=TIM_CKD_DIV1;
	Sa.TIM_CounterMode=TIM_CounterMode_Up;
	Sa.TIM_Period=200-1;
	Sa.TIM_Prescaler=7200-1;
	Sa.TIM_RepetitionCounter=0;
	TIM_TimeBaseInit(TIM2,&Sa);//初始化时基单元
	
	
	TIM_OCInitTypeDef Ta;
	Ta.TIM_OCMode=TIM_OCMode_PWM1;
	Ta.TIM_OutputState=TIM_OutputState_Enable;
	Ta.TIM_Pulse=40;
	Ta.TIM_OCPolarity=TIM_OCPolarity_High;
	TIM_OC3Init(TIM2, &Ta);//配置输出比较单元
	
	GPIO_InitTypeDef GPIO_InitStrucuture;
	GPIO_InitStrucuture.GPIO_Mode=GPIO_Mode_AF_PP;
	GPIO_InitStrucuture.GPIO_Pin=GPIO_Pin_2;
	GPIO_InitStrucuture.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIO_InitStrucuture);//配置GPIO
	
	
//	TIM_ITConfig(TIM2,TIM_IT_Update,ENABLE);
//	NVIC_InitTypeDef Pa;
//	Pa.NVIC_IRQChannel=TIM2_IRQn;
//	Pa.NVIC_IRQChannelCmd=ENABLE;
//	Pa.NVIC_IRQChannelPreemptionPriority=1;
//	Pa.NVIC_IRQChannelSubPriority=1;
//	NVIC_Init(&Pa);
	TIM_Cmd(TIM2,ENABLE);//运行控制
	
	GPIO_ResetBits(GPIOA,GPIO_Pin_4);
	GPIO_SetBits(GPIOA,GPIO_Pin_5); 
}
void Pwm_Get(uint16_t Num)
{
	TIM_SetCompare3(TIM2,Num);
}

//void TIM2_IRQHandler(void)
//{
//	if(TIM_GetITStatus(TIM2,TIM_IT_Update)==SET)
//	{
//		TIM_ClearITPendingBit(TIM2,TIM_IT_Update);
//	}
//	
//}
