#ifndef __GYRO_IMU03A__
#define __GYRO_IMU03A__

#include "mbed.h"
#include "useful.hpp"

/*
	注意
	imu03aは角速度センサーと加速度センサーを搭載していますが
	このclassで読んでいるのはz軸の角速度センサーだけです
	
	つなぎ方
	imu03a 	NUCLEO
	
	Vin -	3V3
	GND - 	GND
	
	SDA -	MOSI
	SCL -	SLCK
	SDO -	MISO
	
	CS -	CS
*/

class a_imu03a{
	private:
		SPI sp;
		DigitalOut cs;
		Ticker tc;
		
		static const int deltaT=30*1000;//us
		
		void comS(){cs=0;}
		void comE(){cs=1;wait_us(100);}
		double getOffset();
		
		double offsetDdeg;
		double getRawDdeg();
		
		double deg;
		void sumDdeg();
	public:
		a_imu03a(
			PinName mosi,
			PinName miso,
			PinName sclk,
			PinName csPin
		);
		void resetModule();
		
		void resetDeg();
		void startDeg();
		void stopDeg();
		
		double getDdeg();
		double getDeg(){return deg;};
};



#endif