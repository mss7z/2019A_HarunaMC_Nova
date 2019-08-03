#include "aRotaryEncoder.hpp"

namespace __aRotaryEncoder_internal__{

	template<int BS>
	roll<BS>::roll(){
		for(int i=0;i<BS;i++){
			buff[i]=0;
		}
		cont=0;
	}
	template<int BS>
	int roll<BS>::next(int val){
		const int ans=buff[cont];
		buff[cont]=val;
		cont++;
		if(!(cont<BS)){
			cont=0;
		}
		return ans;
	}
	template<int BS>
	int roll<BS>::delta(int val){
		const int preVal=next(val);
		return val-preVal;
	}

	aRotaryEncoder::aRotaryEncoder(PinName AphsPin,PinName BphsPin,bool isForward):
		Aphs(AphsPin),//ここで初期化
		BphsInter(BphsPin)
	{
		if(isForward){
			BphsInter.rise(callback(this, &aRotaryEncoder::BphsRiseProcF));
			BphsInter.fall(callback(this, &aRotaryEncoder::BphsFallProcF));
		}else{
			BphsInter.fall(callback(this, &aRotaryEncoder::BphsRiseProcF));
			BphsInter.rise(callback(this, &aRotaryEncoder::BphsFallProcF));
		}
		speedTime.attach(callback(this, &aRotaryEncoder::check),CHECK_INTERVAL);
		val=0;
		diff=0;
		isPlusCheck=false;
		isMinusCheck=false;
		
		speed=0;
		accel=0;
	}

	bool aRotaryEncoder::isPlusMinusCheck(){
		if(val>0){
			isPlusCheck=true;
		}else if(val<0){
			isMinusCheck=true;
		}
		//return isMinusCheck;
		return (isPlusCheck && isMinusCheck);
	}

	void aRotaryEncoder::check(){
		//*(1/CHECK_INTERVAL)で毎秒に直す
		speed=rollVal.delta(val)*(1/CHECK_INTERVAL);
		accel=rollSpeed.delta(speed)*(1/CHECK_INTERVAL);
		return;
	}

	void aRotaryEncoder::BphsRiseProcF(){
		if(Aphs)
			val++;
		else
			val--;
		return;
	}

	void aRotaryEncoder::BphsFallProcF(){
		if(Aphs)
			val--;
		else
			val++;
		return;
	}

}//end of __aRotaryEncoder_internal__