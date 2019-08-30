#ifndef __RUNNER_HPP__
#define __RUNNER_HPP__

#include "mbed.h"

#include "aMotor.hpp"
#include "aAeGyroSmd.hpp"
#include "aPid.hpp"
#include "aRotaryEncoder.hpp"
#include "aRedUS.hpp"

#include "useful.hpp"
#include <math.h>

/*
	runner の構造
	
	namespace mc
	|	|
	|	PID☆彡
	|	namespace pid{
	|		private
	|			deg()
	|		public
	|			setup()
	|			loop()
	|	}
	|	|	|
	|	|	namespace sensor
	|	|	|
	各モータのすぐ上
	xy軸方向の出力を受けて各モータの出力を決定
	namespace out{
		private
			actXY()
			actR()
			actStop()
			out()
		public
			出力を設定
			setXY(x,y)
			setR(r)
			setStop(is)
	}
	|
	namespace motor(mt)
*/

namespace sensor{
	void setup();
	void loop();
	
	extern aAeGyroSmd gyro;
	extern aRotaryEncoder xenc;
	extern aRotaryEncoder yenc;
	
	namespace redus{
		extern aRedUS bluef,blueb,redf,redb;
	}
	extern aRedUS *fp,*bp;
	
	inline float deg(){return gyro.getDeg();}
	inline float rad(){return (M_PI*(deg()))/180.0;}
	float x();
	float y();
	void setX(float);
	void setY(float);
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
				multArg,
				forwardMultArg,
				reversalMultArg
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

//movement control runnerの長
namespace mc{
	void setup();
	void loop();
	
	void setIsiStop(bool);
	bool isIsiStop();
	
	void setBlueField(bool);
	bool isBlueField();
}

namespace out{
	void setup();
	void loop();
	void setX(float xa);
	void setY(float ya);
	void setR(float ra);
	void setStop(bool);
}

namespace pid{
	void setup();
	void loop();
	extern aPid<float> pidX,pidY,pidR;
	void psetX(float xa);
	void psetY(float ya);
	void psetR(float ra);
	//XY軸の制御を有効にするか
	void turnX(bool);
	void turnY(bool);
}


#endif