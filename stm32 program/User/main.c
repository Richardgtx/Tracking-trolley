#include "stm32f10x.h"  // Device header
#include "Delay.h"
#include "OLED.h"
#include "PWM.h"
#include "Key.h"
#include "IN1In2.h"
#include "Timer.h"
#include "Encoder.h"
#include "PID.h"
#include "Rudder.h"
int16_t Speed;
int16_t pwmout=0;
uint16_t a;
int main(void)
{
	OLED_Init();
	
	Pwm_Init();
	In_Init();
	
//	LED_Init();
//	LED2_OFF();
	OLED_ShowString(1,1,"Speed:");
	OLED_ShowString(2,1,"PID:");
	OLED_ShowString(3,1,"rudder: ");
	Encoder_Init();
	Key_Init();
	Timer_Init();
	Rudder_Init();
	while(1)
	{
			OLED_ShowSignedNum(1,8,Speed,5);
			pwmout=PID(Speed,40);
			OLED_ShowSignedNum(2,8,pwmout,5);
			Key_Move1();
			a=Key_get();
			OLED_ShowNum(3,9,a,3);

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