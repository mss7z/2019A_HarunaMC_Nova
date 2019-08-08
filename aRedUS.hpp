#ifndef __A_RED_US_HPP__
#define __A_RED_US_HPP__


#include "mbed.h"

#include "useful.hpp"

namespace __aRedUS_internal__{
	template <int BS=5>
	class rollAve{
		private:
		int buff[BS];
		unsigned cont;
		bool isFullBuff;
		int total;
		
		public:
		rollAve();
		int next(int val);
		int ave(int val);
		void reset();
	};
	
	class aRedUS{
		private:
		DigitalInOut pin;
		Timer t;
		rollAve<5> ra;//お猿さん
		
		int pulseIn();
		int readus();
		const int pulseInTimeOut;
		
		int usRaw,usAve;
		bool isLastTimeout;
		
		public:
		static const int TIMEOUT=0;
		
		aRedUS(
			PinName pina,
			int pulseInTimeOuta=40*1000//us
		);
		//読み取る前に必ずこのupdate関数を呼ぶ
		//タイムアウトした場合の返値はTIMEOUT、それ以外はセンサーの返した生のパルス幅(us)
		int update();
		
		//↑↓で論理が逆転しているので注意
		
		//前回のupdate時にTIMEOUTだったか（つまり、readした値が無効かどうかわかる）
		//reset直後はtrue
		bool isTimeout(){return isLastTimeout;}
		
		//読み取る関数群
		//変換関数(ふつうは使わないけどupdateの返り値を渡すとcmもしくはmmに直される)
		float usToCM(int val){return val/29.0/2.0;}
		int usToMM(int val){return ((val*10)/29)>>1;}
		
		//直近の５回分を平均した値を返す
		float readCM(){return usToCM(usAve);}
		int readMM(){return usToMM(usAve);}
		
		//updateした時の生の値を返す
		float readRawCM(){return usToCM(usRaw);}
		int readRawMM(){return usToMM(usRaw);}
		
		//ローリングバッファをクリアし、リセットする
		void reset();
	};
	
	
}
using __aRedUS_internal__::aRedUS;

#endif