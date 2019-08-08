#include "runner.hpp"


namespace sensor{
	void setup(){
		gyro.startDeg();
	}
	void loop(){
		reviseGyroOwn();
		reviseGyroExt();
	}

	aAeGyroSmd gyro(PC_4,1.0);
	aRotaryEncoder x(A2,A3,PullDown);
	aRotaryEncoder y(A4,A5,PullDown);
	
	namespace blue{
		aRedUS f(PH_1);
		aRedUS b(PH_0);
	}

	void reviseGyroOwn(){
		static mylib::regularC rt(100);
		static int cont=0,stTime=0,stpTime=0;
		if(rt.ist()){
			switch (cont){
				case 0:
				if(mc::isIsiStop){
					stTime++;
				}else{
					stTime=0;
				}
				if(stTime>24){
					cont++;
					mc::isMustStop=true;
				}
				break;
				
				case 1:
				stpTime++;
				//pc.printf("stp %d\n",stpTime);
				if(stpTime>12){
					stpTime=0;
					cont++;
				}
				break;
				
				case 2:
				//pc.printf("rec\n");
				mc::isMustStop=false;
				gyro.stopDeg();
				gyro.updateOffset();
				gyro.startDeg();
				cont=0;
				break;
			}
		}
		return;
	}
	void reviseGyroExt(){
		static mylib::regularC rt(500);
		static mylib::trueFalse witch(true);
		if(rt.ist()){
			if(witch.get()){
				blue::f.update();
			}else{
				blue::b.update();
			}
			if(!(blue::f.isTimeout()) && !(blue::b.isTimeout())){
				gyro.setDeg((180*atan((blue::f.readMM()-blue::b.readMM())/500))/M_PI);
				pc.printf("f%4dmm  b%4dmm\n",blue::f.readMM(),blue::b.readMM());
			}
			//pc.printf("hey\n");
		}
	}
}

namespace motor{
	bool isStop=false;
	
	enum{
		Q1,
		Q2,
		Q3,
		Q4,
		MTDS,//motor data size
	};
	
	aMt m1(PC_6,PC_8);
	aMt m2(PB_8,PC_9);
	aMt m3(PA_10,PB_3);
	aMt m4(PB_5,PB_10);
	
	aMt &q1=m1;
	aMt &q2=m2;
	aMt &q3=m3;
	aMt &q4=m4;
	
	aMt *q[MTDS]={&q1,&q2,&q3,&q4};
	float o[MTDS];
}
namespace mt=motor;

namespace mc{
	void loop(){
		if(isMustStop){
			xyrOut::actStop();
		}else{
			xyrOut::actXY();
			xyrOut::actR();
		}
		
		xyrOut::out();
	}
	
	bool isIsiStop=false;
	bool isMustStop=false;
}

namespace xyrOut{
	float x;
	float y;
	float r;
	void setXY(float xa,float ya){
		x=xa;
		y=ya;
	}
	void setR(float ra){
		r=ra;
	}
	void actXY(){
		const float pi=3.1415926535;
		const float rads[]={
			3*pi/4,
			-3*pi/4,
			-pi/4,
			pi/4,
		};
		
		for(int i=0;i<mt::MTDS;i++){
			mt::o[i]=(x*cos(rads[i])+y*sin(rads[i]));
			//pc.printf("pw[%d]=%d ",i,(int)(pw[i]*1000));
		}
	}
	void actR(){
		float pm;
		if(r>0){
			//最大値の発見
			float max=0.0;
			for(int i=0;i<mt::MTDS;i++){
				if(mt::o[i]>max){
					max=mt::o[i];
				}
			}
			//(1.0-max)　可能な増加量
			if((1.0-max)<r){
				pm=(1.0-max);
			}else{
				pm=r;
			}
		}else{
			//最小値の発見
			float min=0.0;
			for(int i=0;i<mt::MTDS;i++){
				if(mt::o[i]<min){
					min=mt::o[i];
				}
			}
			//(-1.0-min)　可能な減少量
			if((-1.0-min)>r){
				pm=(-1.0-min);
			}else{
				pm=r;
			}
		}
		for(int i=0;i<mt::MTDS;i++){
			mt::o[i]+=pm;
		}
	}
	void actStop(){
		for(int i=0;i<mt::MTDS;i++){
			mt::o[i]=0.0;
		}
	}
	void out(){
		for(int i=0;i<mt::MTDS;i++){
			mt::q[i]->set(mt::o[i]);
		}
	}
	
}

namespace pid{
	//xyrOutと同じ構造につまりsetとactおよびx,y,r変数にすべき?
	
	void setup(){
		degPid.set(0.0);
	}
	void loop(){
		if(isStopPid){
			
		}else{
			deg();
		}
	}
	
	bool isStopPid=false;
	aPid<float> degPid(0.0002,0.00003,0.0001,deltaT);
	void deg(){
		static mylib::regularC pidt((int)(deltaT*1000.0));
		
		if(pidt.ist()){
			xyrOut::setR(degPid.calc(sensor::deg()));
		}
	}
}

