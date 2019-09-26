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
#include "aTapeLED.hpp"

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
			//pc.printf("xenc:%6d yenc:%6d ",sensor::xenc.readRaw(),sensor::yenc.readRaw());
			pc.printf("target x:%10smm y:%10smm r:%10s ",flt(pid::pidX.read()),flt(pid::pidY.read()),flt(pid::pidR.read()));
			//pc.printf("x: %10smm y:%10smm ",flt(sensor::x()),flt(sensor::y()));
			//pc.printf("r:%10sdeg",flt(sensor::deg()));
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
	
	aTapeLED tape(PA_11,PB_2,PB_9);
	tape.r=0.5;
		tape.b=0.5;
		tape.g=0.5;
	while(true){
		pc.printf("0x808080 ");
		tape.color(0x808080);
		wait(0.5);
		pc.printf("0x800000 ");
		tape.color(0x800000);
		wait(0.5);
		pc.printf("0x008000 ");
		tape.color(0x008000);
		wait(0.5);
		pc.printf("0x000080 ");
		tape.color(0x000080);
		wait(0.5);
		pc.printf("\n");
		tape.color(0x000000);
		wait(0.5);
		
	}
	return 0;
	
	pc.printf("\nWelcome to Haruna's Movement Controller Nova\n");
	/*
	mt::m1.set(0.1);
	mt::m2.set(0.3);
	mt::m3.set(0.6);
	mt::m4.set(1.0);
	return 0;*/
	/*
	mt::q1.set(0.1);
	mt::q2.set(0.3);
	mt::q3.set(0.6);
	mt::q4.set(1.0);
	return 0;*/
	/*mt::q4.set(0.3);
	return 0;*/
	/*out::setX(0.5);
	out::setY(0.2);
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

