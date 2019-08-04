#ifndef __A_MOTOR_HPP__
#define __A_MOTOR_HPP__

#define DEFO_PWM_PERIOD 1000 //us
#define AMOTOR_MULT_MAX 1.0

#include "mbed.h"

namespace MSPEED {
	const float MAX=0.95;
	const float MIN=-0.95;
	const float STOP=0.0;
}

class aMotorParent {
	protected:
		float forwardMult;
		float reversalMult;
		static float baseForwardMult;
		static float baseReversalMult;
		float checkSpeed(float*);
	public:
		aMotorParent();
		static void baseMult(float multArg=1.0,float forwardMultArg=1.0,float reversalMultArg=1.0);
		void mult(float multArg=1.0,float forwardMult=1.0,float reversalMultArg=1.0);
		virtual void set(float speed)=0;
};

inline float aMotorParent::checkSpeed(float *valP){
	if(MSPEED::MAX<*valP){
		*valP=MSPEED::MAX;
	}else if(*valP<MSPEED::MIN){
		*valP=MSPEED::MIN;
	}
	return *valP;
}

class aMotorDire:
	aMotorParent
{
	private:
		PwmOut pwm;
		DigitalOut dire;
	public:
		void set(float speed);
		aMotorDire(
			PinName pwmPin,
			PinName direPin,
			int pwmPeriod=DEFO_PWM_PERIOD,
			float multArg=1.0,
			float forwardMultArg=1.0,
			float reversalMultArg=1.0
		);
};

class aMotorPwm:
	aMotorParent
{
	private:
		PwmOut pwmA;
		PwmOut pwmB;
	public:
		void set(float speed);
		aMotorPwm(
			PinName pwmAPin,
			PinName pwmBPin,
			int pwmPeriod=DEFO_PWM_PERIOD,
			float multArg=1.0,
			float forwardMultArg=1.0,
			float reversalMultArg=1.0
		);
};


#endif