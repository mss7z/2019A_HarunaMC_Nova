#ifndef __A_AE_GYRO_SMD__
#define __A_AE_GYRO_SMD__

#include "mbed.h"

class aAeGyroSmd{
	private:
		Ticker tc;
		AnalogIn in;
		
		static const float deltaT=0.01;//second
		void procRegular();
		
		float deg;
		
		float offsetV;
		float getOffsetV();
		float mult;
		
		float getV(){return in.read()*3.3;};
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
};

#endif