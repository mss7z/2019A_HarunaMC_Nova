#include "aGyro_imu03a.hpp"

a_imu03a::a_imu03a(
	PinName mosi,
	PinName miso,
	PinName sclk,
	PinName csPin
):	
	sp(mosi,miso,sclk),
	cs(csPin)
{
	sp.format(8,3);
	sp.frequency(1000000);
	comE();
	resetModule();
	
	resetDeg();
}

void a_imu03a::resetModule(){
	//CTRL3_C に値を書き込んでModuleをリセットする
	//set CTRL3_C register
	comS();
	sp.write(0x12);
	sp.write(0x1);
	comE();
	
	//CTRL2_G に設定値を書きこんでgyroを起動
	//設定値は833Hz 125dps
	comS();
	sp.write(0x11);
	sp.write(0b01110010);
	comE();
	
	offsetDdeg=getOffset();
}

void a_imu03a::resetDeg(){
	deg=0.0;
	tc.detach();
}

void a_imu03a::startDeg(){
	tc.attach_us(callback(this,&a_imu03a::sumDdeg),deltaT);
}

void a_imu03a::stopDeg(){
	tc.detach();
}

void a_imu03a::sumDdeg(){
	deg+=((double)deltaT/1000000.0)*getDdeg();
}
	

double a_imu03a::getOffset(){
	const int N=10000;
	double ddegOffset=0.0;
	//pc.printf("getOffset called\n");
	for(int i=0;i<N;i++){
		ddegOffset+=getRawDdeg();
		//wait_us(300);
	}
	return ddegOffset/(double)N;
}

double a_imu03a::getDdeg(){
	const int N=10;
	double ddeg=0.0;
	for(int i=0;i<N;i++){
		ddeg+=getRawDdeg()-offsetDdeg;
	}
	return ddeg/(double)N;
}
double a_imu03a::getRawDdeg(){
	//z軸のみ
	int16_t rval;
	
	comS();
	sp.write(0x80|0x26);
	rval=sp.write(0x00);
	comE();
	
	comS();
	sp.write(0x80|0x27);
	rval|=sp.write(0x00)<<8;
	comE();
	
	return (rval*125.0)/(double)0x7fff;
}