#include "stm32f10x.h"  // Device header
#include "Delay.h"
#include "OLED.h"
#include "PWM.h"
#include "Key.h"
#include "IN1In2.h"
#include "Timer.h"
#include "Encoder.h"
#include "PID.h"
int16_t Speed;
int16_t pwmout=0;
int main(void)
{
	OLED_Init();
	
	Pwm_Init();
	In_Init();
	Key_Init();
//	LED_Init();
//	LED2_OFF();
	OLED_ShowString(1,1,"Speed:");
	OLED_ShowString(2,1,"PID:");
	Encoder_Init();
	Timer_Init();
	
	while(1)
	{
			OLED_ShowSignedNum(1,8,Speed,5);
			pwmout=PID(Speed,40);
			OLED_ShowSignedNum(2,8,pwmout,5);
	}
}
void TIM4_IRQHandler(void)
{
	if(TIM_GetITStatus(TIM4,TIM_IT_Update)==SET)
	{
		Speed=Encoder_Get()/20;
		TIM_ClearITPendingBit(TIM4,TIM_IT_Update);
	}
}