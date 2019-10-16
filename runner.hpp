#ifndef __RUNNER_HPP__
#define __RUNNER_HPP__

#include "mbed.h"

#include "aMotor.hpp"
#include "aAeGyroSmd.hpp"
#include "aGyro_imu03a.hpp"
#include "aPid.hpp"
#include "aRotaryEncoder.hpp"
#include "aRedUS.hpp"
#include "aTapeLED.hpp"

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
	
	//extern aAeGyroSmd gyro;
	extern a_imu03a gyro;
	extern aRotaryEncoder xenc;
	extern aRotaryEncoder yenc;
	
	namespace redus{
		extern aRedUS bluef,blueb,redf,redb;
		extern aRedUS &blues,&reds;
	}
	//extern aRedUS *fp,*bp;
	
	inline float deg(){return gyro.getDeg();}
	inline float rad(){return (M_PI*(deg()))/180.0;}
	float x();
	float y();
	void setX(float);
	void setY(float);
	
	/*bool isReadBlueSuc();
	void reviseDegByBlue();
	bool isReadRedSuc();
	void reviseDegByRed();*/
	void resetFarw();
	void resetHomew();
	void reviseByFarw();
	void reviseByHomew();
	
	void resetFarPole();
	void resetHomePole();
	void reviseByFarPole();
	void reviseByHomePole();
	
	void resetBackPole();
	void reviseByBackPole();
}

namespace motor{
	void setup();
	void loop();
	
	extern bool isStop;
	extern bool isRunning;
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
				if(val>0.1 || val<-0.1){
					isRunning=true;
				}
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
	
	void on(bool);
	void emergStopIs(bool);
	inline bool isOut(){return isRunning;}
	
	void fatalError();
}
namespace mt=motor;

//movement control runnerの長
namespace mc{
	extern aTapeLED tl;
	
	void setup();
	void loop();
	
	void fatalError();
	
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
	extern int interval;
	
	void setup();
	void loop();
	extern aPid<float> pidX,pidY,pidR;
	void psetX(float xa);
	void psetY(float ya);
	void psetR(float ra);
	
	float preadX();
	float preadY();
	//XY軸の制御を有効にするか
	void turnX(bool);
	void turnY(bool);
	
	enum gainMode{
		BY_INWORLD,
		BY_OUTWORLD,
		BY_HOMEW,
		BY_FARW,
	};
	
	void psetGain(gainMode);
}


#endif