#include "stm32f10x.h"                  // Device header
#include "Encoder.h"


void Timer_Init(void)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4,ENABLE);
	
	TIM_InternalClockConfig(TIM4);
	
	TIM_TimeBaseInitTypeDef TIM_InitStrucutre;
	TIM_InitStrucutre.TIM_ClockDivision=TIM_CKD_DIV1;
	TIM_InitStrucutre.TIM_CounterMode=TIM_CounterMode_Up;
	TIM_InitStrucutre.TIM_Period=7200-1;
	TIM_InitStrucutre.TIM_Prescaler=5000-1;
	TIM_TimeBaseInit(TIM4,&TIM_InitStrucutre);
	
	TIM_ITConfig(TIM4,TIM_IT_Update,ENABLE);
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	
	NVIC_InitTypeDef NVIC_InitStructure;
	NVIC_InitStructure.NVIC_IRQChannel=TIM4_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=0;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority=0;
	NVIC_InitStructure.NVIC_IRQChannelCmd=ENABLE;
	NVIC_Init(&NVIC_InitStructure);
	TIM_Cmd(TIM4,ENABLE);
}
