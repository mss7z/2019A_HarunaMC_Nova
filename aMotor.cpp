#include "aMotor.hpp"

aMotorParent::aMotorParent()
{}

float aMotorParent::baseForwardMult=1.0;
float aMotorParent::baseReversalMult=1.0;

void aMotorParent::baseMult(float multArg,float forwardMultArg,float reversalMultArg){
	baseForwardMult=multArg*forwardMultArg;
	baseReversalMult=multArg*reversalMultArg;
	if(baseForwardMult>AMOTOR_MULT_MAX){
		baseForwardMult=AMOTOR_MULT_MAX;
	}
	if(baseReversalMult>AMOTOR_MULT_MAX){
		baseReversalMult=AMOTOR_MULT_MAX;
	}
}
void aMotorParent::mult(float multArg,float forwardMultArg,float reversalMultArg){
	forwardMult=multArg*forwardMultArg;
	reversalMult=multArg*reversalMultArg;
	if(forwardMult>AMOTOR_MULT_MAX){
		forwardMult=AMOTOR_MULT_MAX;
	}
	if(reversalMult>AMOTOR_MULT_MAX){
		reversalMult=AMOTOR_MULT_MAX;
	}
}

aMotorDire::aMotorDire (PinName pwmPin,PinName direPin,int pwmPeriod,float multArg,float forwardMultArg,float reversalMultArg):
	pwm(pwmPin),
	dire(direPin)
{
	pwm.period_us(pwmPeriod);
	pwm = 0.0;
	aMotorParent::mult(multArg,forwardMultArg,reversalMultArg);
}

void aMotorDire::set (float speed){
	checkSpeed(&speed);
	if(speed<MSPEED::STOP){
		dire=1;
		speed*=reversalMult*baseReversalMult*(-1.0);
	}else{
		dire=0;
		speed*=forwardMult*baseForwardMult;
	}
	//aMotorPwm::set関数のコメント参照
	pwm = speed;
}


aMotorPwm::aMotorPwm (PinName pwmAPin,PinName pwmBPin,int pwmPeriod,float multArg,float forwardMultArg,float reversalMultArg):
	pwmA(pwmAPin),
	pwmB(pwmBPin)
{
	pwmA.period_us(pwmPeriod);
	pwmB.period_us(pwmPeriod);
	pwmA = 0.0;
	pwmB = 0.0;
	aMotorParent::mult(multArg,forwardMultArg,reversalMultArg);
}

void aMotorPwm::set (float speed){
	/*if(speed<MSPEED::STOP){
		pwmA=stopPwm+(speed*reversalMult*baseReversalMult*(-1.0));
		pwmB=stopPwm;
	}else{
		
		pwmが負論理の時forwardMultは負の値になっているので
		(speed*forwardMult*baseForwardMult)は負の値になる
		また、この時stopPwmには1.0が入っているので
		stopPwm+(speed*forwardMult*baseForwardMult)で　1.0+負の値　ということになる
		つまり、1.0からspeed分が引かれ、pwmBに代入される値は逆転する(speedが0.7のとき0.3 など)
		
		pwmA=stopPwm;
		pwmB=stopPwm+(speed*forwardMult*baseForwardMult);
	}*/
	checkSpeed(&speed);
	
	if(speed<MSPEED::STOP){
		pwmA=-1.0*speed*reversalMult*baseReversalMult;
		pwmB=0.0;
	}else{
		pwmA=0.0;
		pwmB=speed*forwardMult*baseForwardMult;
	}
}