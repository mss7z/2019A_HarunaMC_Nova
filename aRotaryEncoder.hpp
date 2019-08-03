/*
	名前の通りrotaryEcoderを操るクラス
*/

#ifndef __A_ROTARY_ENCODER_HPP__
#define __A_ROTARY_ENCODER_HPP__

#include "mbed.h"

namespace __aRotaryEncoder_internal__{

	template <int BS=10>
	class roll{
	private:
		int buff[BS];
		unsigned cont;
	public:
		roll();
		int next(int val);
		int delta(int val);
	};

	class aRotaryEncoder {
	private:
		static const float CHECK_INTERVAL=0.01;
		static const int BUFF_SIZE=10;
		
		DigitalIn Aphs;
		InterruptIn BphsInter;
		Ticker speedTime;
		
		roll<BUFF_SIZE> rollVal;
		roll<BUFF_SIZE> rollSpeed;
		
		int val;
		int diff;

		bool isPlusCheck;
		bool isMinusCheck;
		
		void BphsRiseProcF();
		void BphsFallProcF();
		
		int speed;
		int accel;
		void check();
	public:
		aRotaryEncoder(PinName AphsPin,PinName BphsPin,bool isForward=true);
		//inline関数化
		void reset()	{val = 0;diff = 0;}
		int read()  {return val-diff;}
		void set(const int);
		int readRaw() {return val;}
		
		int readSpeed() {return speed;}
		int readAccel() {return accel;}

		bool isPlusMinusCheck();
		//operator int()	{return val;}
		//operator int() {return val;}
	};
	inline void aRotaryEncoder::set(const int comp){
		diff=val-comp;
		return;
	}

}//end of __aRotaryEncoder_internal__
using __aRotaryEncoder_internal__::aRotaryEncoder;

#endif