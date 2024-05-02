#include "stm32f10x.h"                  // Device header
#include "PWM.h"
int16_t P=2000,I=20,D=2000;
int16_t PID(int16_t Encoder,int16_t Target)
{ 	
  static int16_t pwmout=0,last_error=0,last_last_error=0;
  int16_t error =Target  - Encoder;
	int16_t d_error=error-last_error;
  int16_t dd_error = -2*last_error+error+last_last_error; 
//	//ËÀÇøãÐÖµ	
//	if((error>-cu_error_zone)&&(error<cu_error_zone))
//	{
//		error=0;
//		d_error=0;
//		dd_error=0;
//	}
  pwmout+=P*d_error/10 +I*error/10+D*dd_error/10;
  last_last_error=last_error;
  last_error = error;
	//if(pwmout > 1000) pwmout = 1000;
	if(pwmout <=0) pwmout = 0;
	Pwm_Get(pwmout/200);
  return pwmout/200;
}