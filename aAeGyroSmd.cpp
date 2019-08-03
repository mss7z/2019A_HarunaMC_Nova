#include "aAeGyroSmd.hpp"

aAeGyroSmd::aAeGyroSmd(PinName pin,float multArg):
	in(pin),mult(multArg)
{
	reset();
}

float aAeGyroSmd::getOffsetV(){
	const int N=2000;
	float offset=0;
	for(int i=0;i<N;i++){
		offset+=getV();
		wait_ms(2);
	}
	return offset/N;
}

float aAeGyroSmd::getDdeg(){
	const int N=10;
	float voltTotal=0;
	for(int i=0;i<N;i++){
		voltTotal+=getV();
	}
	return (int)(mult*(((voltTotal/N)-offsetV)/(0.67/100.0)));
}

void aAeGyroSmd::startDeg(){
	tc.attach(callback(this,&aAeGyroSmd::procRegular),deltaT);
}

void aAeGyroSmd::resetDeg(){
	stopDeg();
	deg=0.0;
}

void aAeGyroSmd::stopDeg(){
	tc.detach();
}

void aAeGyroSmd::procRegular(){
	deg+=getDdeg()*deltaT;
}

void aAeGyroSmd::reset(){
	offsetV=getOffsetV();
	resetDeg();
}