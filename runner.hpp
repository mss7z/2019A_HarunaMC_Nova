#ifndef __RUNNER_HPP__
#define __RUNNER_HPP__

#include "mbed.h"

#include "aMotor.hpp"
#include "aAeGyroSmd.hpp"
#include "aPid.hpp"
#include "aRotaryEncoder.hpp"

#include "useful.hpp"

namespace sensor{
	void setup();
	void loop();
	
	extern aAeGyroSmd gyro;
	extern aRotaryEncoder x;
	
	void reviseGyro();
	inline float deg(){return gyro.getDeg();}
}

namespace motor{
	extern bool isStop;
	class aMt:aMotorPwm{
		//汚いコンストラクタ
		//継承コンストラクタを使いたい。いい方法あったら教えてください。
		public:
			aMt(
				PinName pwmAPin,
				PinName pwmBPin,
				float multArg=1.0,
				float forwardMultArg=1.0,
				float reversalMultArg=1.0
			):aMotorPwm(
				pwmAPin,
				pwmBPin,
				1000,//pwm period
				multArg=1.0,
				forwardMultArg=1.0,
				reversalMultArg=1.0
			){};
			void set(float val){
				if(isStop){
					aMotorPwm::set(0.0);
				}else{
					aMotorPwm::set(val);
				}
			}
	};
	extern aMt m1,m2,m3,m4;
	
	extern aMt &q1,&q2,&q3,&q4;
	
	extern aMt *q[];
	extern float o[];
}
namespace mt=motor;

namespace mc{
	void loop();
	
	extern bool isIsiStop;
	extern bool isMustStop;
}

namespace xyrOut{
	void setXY(float xa,float ya);
	void setR(float ra);
	void actXY();
	void actR();
	void actStop();
	void out();
}

namespace pid{
	void setup();
	void loop();
	extern aPid<float> degPid;
	//haisi->移動の意思を持たないが、PID層が動作可能な状況において、PID層を停止し、動作を完全に止める
	extern bool isStopPid;
	const float deltaT=0.02;
	void deg();
}


#endif