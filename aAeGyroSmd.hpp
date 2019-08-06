#ifndef __A_AE_GYRO_SMD__
#define __A_AE_GYRO_SMD__

#include "mbed.h"
#include "useful.hpp"

class aAeGyroSmd{
	private:
		Ticker tc;
		AnalogIn in;
		Timer fromPreOffset;//角度補正に使う
		
		static const float deltaT=0.01;//second
		void procRegular();
		
		float deg;
		
		float offsetV;
		float getOffsetV();
		float getOffsetVmini();
		float mult;
		
		float getV(){return in.read()*3.3;};
		float VtoDdeg(float v){return (mult*(v/(0.67/100.0)));}
	public:
		aAeGyroSmd(
			PinName pin,
			float multArg=1.0
		);
		float getDeg(){return deg;};
		float getDdeg();
		
		void startDeg();
		void resetDeg();
		void stopDeg();
		
		void reset();
		
		void updateOffset();
};

#endif