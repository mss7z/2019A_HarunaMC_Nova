#ifndef __USEFUL_HPP__
#define __USEFUL_HPP__

#include "mbed.h"


extern Serial pc;
extern DigitalOut led;

namespace arduino{

	template<typename T>
	inline T map(T x, T in_min, T in_max, T out_min, T out_max){
	  return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
	}
}

namespace mylib{
	class regularC{
	private:
		unsigned long interval;
		unsigned long nextTime;
		Timer t;
	public:
		regularC(unsigned long intervalArg,unsigned long start=0):
		interval(intervalArg)
		{
			t.start();
			nextTime=start;
		}
		bool ist(){
			if(nextTime<(unsigned long)t.read_ms()){
				nextTime=interval+t.read_ms();
				return true;
			}else{
				return false;
			}
		}
		void set(unsigned long val){interval=val;}
		unsigned long read(){return interval;}
	};
}

#endif