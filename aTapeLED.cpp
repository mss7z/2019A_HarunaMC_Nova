#include "aTapeLED.hpp"

namespace aTapeLEDlib{
	void colorful(aTapeLED &obj){
		for(float s=0.0;s<M_PI*2;s+=0.0001){
			colorCode v=0;
			v.c.r=(sin(s)+1.0)*0xff/2;
			v.c.g=(sin(s-((2.0/3.0)*M_PI))+1.0)*0xff/2;
			v.c.b=(sin(s-((4.0/3.0)*M_PI))+1.0)*0xff/2;
			obj.color(v);
			//wait(0.001);
		}
	}
}