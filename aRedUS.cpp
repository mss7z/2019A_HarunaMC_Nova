#include "aRedUS.hpp"

namespace __aRedUS_internal__{
	template<int BS>
	rollAve<BS>::rollAve(){
		reset();
	}
	template<int BS>
	int rollAve<BS>::next(int val){
		const int ans=buff[cont];
		buff[cont]=val;
		total=total+val-ans;
		cont++;
		if(!(cont<BS)){
			isFullBuff=true;
			cont=0;
		}
		return ans;
	}
	template<int BS>
	int rollAve<BS>::ave(int val){
		next(val);
		if(isFullBuff){
			return total/BS;
		}else{
			return total/cont;
		}
	}
	template<int BS>
	void rollAve<BS>::reset(){
		for(int i=0;i<BS;i++){
			buff[i]=0;
		}
		cont=0;
		isFullBuff=false;
		total=0;
	}
	
	aRedUS::aRedUS(PinName pina,int pulseInTimeOuta):
		pin(pina),pulseInTimeOut(pulseInTimeOuta)
	{
		reset();
		t.start();
		pin.mode(PullDown);
	}

	int aRedUS::pulseIn(){
		//早朝(深夜)のプログラミングはいけない、バグの温床となる
		//センサーが正しく接続されていないときのtimeoutの処理に問題があった
		int start;
		t.reset();
		while(true){
			if(pin){
				start=t.read_us();
				break;
			}else if(t.read_us()>pulseInTimeOut){
				return TIMEOUT;
			}
		}
		while(true){
			if(!pin){
				return t.read_us()-start;
			}else if(t.read_us()>pulseInTimeOut){
				return TIMEOUT;
			}
		}
	}

	int aRedUS::readus(){
		pin.output();
		pin=0;
		wait_us(2);
		pin=1;
		wait_us(5);
		pin=0;
		pin.input();
		
		return pulseIn();
	}
	int aRedUS::update(){
		int val=readus();
		if(val==TIMEOUT){
			//pc.printf("timeout\n");
			isLastTimeout=true;
			return TIMEOUT;
		}else{
			//pc.printf("not timeout\n");
			isLastTimeout=false;
			usRaw=val;
			usAve=ra.ave(usRaw);
			return val;
		}
	}
	
	void aRedUS::reset(){
		ra.reset();
		t.reset();
		usRaw=usAve=0;
		isLastTimeout=true;
	}
}