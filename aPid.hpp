#ifndef __A_PID_HPP__
#define __A_PID_HPP__

#include "mbed.h"

namespace __aPid_internal__{
	template <typename T>
	class delta{
	private:
		T preVal;
		T deltaT;
	public:
		delta(T dt=(T)1):preVal((T)0),deltaT(dt){}
		T f(T val){
			const T ans=(val-preVal)/deltaT;
			preVal=val;
			return ans;
		}
		void reset(){
			preVal=0;
		}
	};

	template <typename T>
	class aPid{
	private:
		const float KP,KI,KD;
		const T DT;
		T target;
		T preOpe;
		delta<T> dp;
		delta<T> dd1,dd2;
	public:
		aPid(float kPArg,float kIArg,float kDArg,float dtArg);
		T calc(T val);
		void set(T val){target=val;}
		void reset();
	};
	
	template<typename T>
	void aPid<T>::reset(){
		target=(T)0;
		preOpe=(T)0;
		dp.reset();
		dd1.reset();
		dd2.reset();
	}
		
	
	template<typename T>
	aPid<T>::aPid(float kPArg,float kIArg,float kDArg,float dtArg):
	KP(kPArg),KI(kIArg),KD(kDArg),DT(dtArg),
	dp(DT),dd1(DT),dd2(DT)
	{
		reset();
	}

	template<typename T>
	T aPid<T>::calc(T val){
		T diff=target-val;
		T deltaOpe,ope;
		
		deltaOpe=
		KP*dp.f(diff)+
		KI*diff+
		KD*dd1.f(dd2.f(diff));
		
		ope=deltaOpe+preOpe;
		preOpe=ope;
		return ope;
	}
}
using __aPid_internal__::aPid;

#endif