#include "stm32f10x.h" // Device header
#include "Delay.h"
#include "LED.h"
#include "Rudder.h"
uint16_t Num=14;
void Key_Init(void)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_IPU;
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_1;
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOB,&GPIO_InitStructure);
}

void Key_Move1(void)
{
	
	Delay_ms(20);
	if(GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_1)==0)
	{
		while(GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_1)==0);
//		LED2_TURN();
			Num+=4;
		if(Num>22) Num=14;
		Rudder_Get(Num);
	}
	
	Delay_ms(20);
}
uint16_t Key_get(void)
{
	return Num;
}
