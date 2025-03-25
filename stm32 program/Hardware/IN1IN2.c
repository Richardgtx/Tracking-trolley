#include "stm32f10x.h"                  // Device header
void In_Init(void)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	GPIO_InitTypeDef TT;
	TT.GPIO_Mode=GPIO_Mode_Out_PP;
	TT.GPIO_Pin=GPIO_Pin_4|GPIO_Pin_5;
	TT.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&TT);
	GPIO_ResetBits(GPIOA,GPIO_Pin_5);
	GPIO_SetBits(GPIOA,GPIO_Pin_4);
	
}
void Turn(void)
{
	if(GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_5)==0)
		GPIO_SetBits(GPIOA,GPIO_Pin_5);
	
	else
		GPIO_ResetBits(GPIOA,GPIO_Pin_5);
	if(GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_4)==0)
		GPIO_SetBits(GPIOA,GPIO_Pin_4);
	
	
	else
		GPIO_ResetBits(GPIOA,GPIO_Pin_4);
	
}