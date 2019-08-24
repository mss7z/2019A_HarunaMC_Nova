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


namespace monitor{
	void loop(){
		static mylib::regularC pt(500);
		if(pt.ist()){
			pc.printf("x: %10smm y:%10smm",flt(sensor::x()),flt(sensor::y()));
			pc.printf("deg:%5dm",(int)(sensor::deg()*1000));
			pc.printf("\n");
		}
	}
}



int main(){
	rcv::setup();
	emerg::setup();
	sensor::setup();
	mc::setup();
	
	
	pc.printf("\nWelcome to Haruna's Movement Controller Nova\n");
	/*
	mt::m1.set(0.1);
	mt::m2.set(0.4);
	mt::m3.set(0.7);
	mt::m4.set(1.0);
	return 0;*/
	
	while (true){
		rcv::loop();
		emerg::loop();
		sensor::loop();
		
		monitor::loop();
		//pc.printf("hey\n");
		
		//mcLoopは最後に呼ばれなければならない
		mc::loop();
	}
	
    return 0;
}

