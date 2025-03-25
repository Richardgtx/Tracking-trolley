#include "stm32f10x.h"                  // Device header

void Rudder_Init(void)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);//RCC时钟
	
	TIM_InternalClockConfig(TIM1);//时钟源选择
	
	TIM_TimeBaseInitTypeDef Sa;
	Sa.TIM_ClockDivision=TIM_CKD_DIV1;
	Sa.TIM_CounterMode=TIM_CounterMode_Up;
	Sa.TIM_Period=200-1;
	Sa.TIM_Prescaler=7200-1;
	Sa.TIM_RepetitionCounter=0;
	TIM_TimeBaseInit(TIM1,&Sa);//初始化时基单元
	
	
	TIM_OCInitTypeDef Ta;
	TIM_OCStructInit(&Ta);
	Ta.TIM_OCMode=TIM_OCMode_PWM1;
	Ta.TIM_OutputState=TIM_OutputState_Enable;
	Ta.TIM_Pulse=5;
	Ta.TIM_OCPolarity=TIM_OCPolarity_High;
	TIM_OC2Init(TIM1, &Ta);//配置输出比较单元
	
	GPIO_InitTypeDef GPIO_InitStrucuture;
	GPIO_InitStrucuture.GPIO_Mode=GPIO_Mode_AF_PP;
	GPIO_InitStrucuture.GPIO_Pin=GPIO_Pin_9;
	GPIO_InitStrucuture.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIO_InitStrucuture);//配置GPIO
	
//	TIM_ITConfig(TIM2,TIM_IT_Update,ENABLE);
//	NVIC_InitTypeDef Pa;
//	Pa.NVIC_IRQChannel=TIM2_IRQn;
//	Pa.NVIC_IRQChannelCmd=ENABLE;
//	Pa.NVIC_IRQChannelPreemptionPriority=1;
//	Pa.NVIC_IRQChannelSubPriority=1;
//	NVIC_Init(&Pa);
	 TIM_CtrlPWMOutputs(TIM1,ENABLE);
	TIM_Cmd(TIM1,ENABLE);//运行控制
}
void Rudder_Get(uint16_t Num)
{
	TIM_SetCompare2(TIM1,Num);
}

//void TIM2_IRQHandler(void)
//{
//	if(TIM_GetITStatus(TIM2,TIM_IT_Update)==SET)
//	{
//		TIM_ClearITPendingBit(TIM2,TIM_IT_Update);
//	}
//	
//}
