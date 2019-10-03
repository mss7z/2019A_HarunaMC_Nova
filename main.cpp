//NIT,Akita College Robocon Akita
//2019 A-team Haruna Movement Controller
//Project Nova by mss7z
//
//抵抗は外すべき

#include "mbed.h"

#include "aMotor.hpp"
#include "aXBee.hpp"
#include "aAeGyroSmd.hpp"

#include "com.hpp"
#include "useful.hpp"
#include "mautoCore.hpp"

/*
	構造☆彡
	
	下級
	aSeries
	|
	runner
	|	|
	|	|	coord
	|	|	|
	|	mautoCore
	|	|
	com
	|
	main
	上級
*/


namespace monitor{
	void loop(){
		static mylib::regularC pt(500);
		if(pt.ist()){
			pc.printf("xenc:%6d yenc:%6d ",sensor::xenc.readRaw(),sensor::yenc.readRaw());
			pc.printf("target x:%10smm y:%10smm r:%10s ",flt(pid::pidX.read()),flt(pid::pidY.read()),flt(pid::pidR.read()));
			pc.printf("x: %10smm y:%10smm ",flt(sensor::x()),flt(sensor::y()));
			pc.printf("r:%10sdeg BF:%s",flt(sensor::deg()),(mc::isBlueField() ? "true" : "false"));
			pc.printf("\n");
		}/*
		if(pt.ist()){
			pc.printf("target x:%10smm y:%10smm r:%10s ",flt(pid::pidX.read()),flt(pid::pidY.read()),flt(pid::pidR.read()));
			pc.printf("\n");
		}*/
	}
}



int main(){
	sensor::setup();
	mc::setup();
	auco::setup();
	rcv::setup();
	emerg::setup();
	
	//return 0;
	
	pc.printf("\nWelcome to Haruna's Movement Controller Nova\n");
	/*
	mt::m1.set(0.1);
	mt::m2.set(0.3);
	mt::m3.set(0.6);
	mt::m4.set(1.0);
	return 0;
	*/
	/*
	mt::q1.set(0.1);
	mt::q2.set(0.3);
	mt::q3.set(0.6);
	mt::q4.set(1.0);
	return 0;*/
	/*mt::q4.set(0.3);
	return 0;*/
	/*out::setX(0.0);
	out::setY(0.5);
	mc::loop();
	return 0;*/
	
	while (true){
		monitor::loop();
		
		sensor::loop();
		auco::loop();
		rcv::loop();
		emerg::loop();
		
		//mcLoopは最後に呼ばれなければならない
		mc::loop();
	}
	
    return 0;
}

