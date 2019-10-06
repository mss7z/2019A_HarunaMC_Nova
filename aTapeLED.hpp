#ifndef __A_TAPE_LED_HPP__
#define __A_TAPE_LED_HPP__

#include "mbed.h"

struct colorCodeInternal{
	uint32_t b:8;
	uint32_t g:8;
	uint32_t r:8;
	uint32_t trs:8;
};

union colorCode{
	uint32_t v;
	colorCodeInternal c;
	colorCode(uint32_t va):v(va){}
	//colorCode operator colorCode(){return *this;}
	operator uint32_t(){return v;}
	colorCode operator=(colorCode va){v=(uint32_t)va;return va;}
	colorCode operator=(uint32_t va){v=(colorCode)va;return v;}
	const colorCode operator*(float mult) const{
		colorCode newVal=mult;
		newVal.c.trs=mult*c.trs;
		newVal.c.r=mult*c.r;
		newVal.c.g=mult*c.g;
		newVal.c.b=mult*c.b;
		return newVal;
	}
};

class aTapeLED{
	public:
	PwmOut r,g,b;
	colorCode pre;
	
	uint8_t colorCalc(uint8_t a,uint8_t b,float trans){
		return (uint8_t)((a*(1.0-trans))+(b*(trans)));
	}
	
	public:
	aTapeLED(PinName ra,PinName ga,PinName ba):
		r(ra),g(ga),b(ba),pre(0x0)
	{
		const int PERIODV=1000;
		r.period_us(PERIODV);
		g.period_us(PERIODV);
		b.period_us(PERIODV);
	}
	void color(colorCode v){
		const float transparency=((float)(v.c.trs))/(float)0xFF;
		//pc.printf("trans %5s\n",flt(transparency));
		colorCode now=0;
		now.c.r=colorCalc(v.c.r,pre.c.r,transparency);
		now.c.g=colorCalc(v.c.g,pre.c.g,transparency);
		now.c.b=colorCalc(v.c.b,pre.c.b,transparency);
		//pc.printf("0x%08X\n",now.v);
		r.pulsewidth_us(((int)now.c.r)<<2);
		g.pulsewidth_us(((int)now.c.g)<<2);
		b.pulsewidth_us(((int)now.c.b)<<2);
		pre=now;
	}
	void color(uint32_t v){
		color((colorCode)v);
	}
	colorCode operator=(colorCode va){color(va);return va;}
	uint32_t operator=(uint32_t va){color(va);return va;}
};


namespace aTapeLEDlib{
	void colorful(aTapeLED&);
	const colorCode
		RED=0xFF0000,
		GREEN=0x00FF00,
		BLUE=0x0000FF,
		BLACK=0x000000,
		WHITE=0xFFFFFF
	;
}

#endif