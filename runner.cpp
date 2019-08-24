#include "runner.hpp"


namespace sensor{
	float xv=0.0,yv=0.0;
	Ticker calcXYtime;
	mylib::delta<float> dx,dy;
	static const int readRedUSinterval=40;
	
	void reviseGyroOwn();
	void reviseByRedUS();
	void reviseGyroExt();
	void reviseYExt();
	void calcXY();
	
	void setup(){
		gyro.startDeg();
		calcXYtime.attach(calcXY,0.01);
		dx.reset();
		dy.reset();
	}
	void loop(){
		reviseGyroOwn();
		reviseByRedUS();
		
		if(mc::isBlueField()){
			fp=&blue::f;
			bp=&blue::b;
		}
	}

	aAeGyroSmd gyro(PC_4,1.0);
	aRotaryEncoder xenc(A2,A3,PullDown);
	aRotaryEncoder yenc(A4,A5,PullDown);
	 
	namespace blue{
		aRedUS f(PH_1,5*1000);
		aRedUS b(PA_13,5*1000);
	}
	aRedUS *fp=NULL,*bp=NULL;
	
	void calcXY(){
		//エンコーダ1カウント当たり何ミリメートルか？
		static const float mmPerREcont=1.0;//------------------------------------------------------sitei
		//書いてて気が付いたけど、これって線形変換の回転移動？
		xv+=(dx.f(xenc.readRaw())*cos(rad())-dy.f(yenc.readRaw())*sin(rad()))*mmPerREcont;
		yv+=(dx.f(xenc.readRaw())*sin(rad())+dy.f(yenc.readRaw())*cos(rad()))*mmPerREcont;
	}
	
	float x(){
		return xv;
	}
	float y(){
		return yv;
	}
	
	void setX(float newVal){
		xv=newVal;
	}
	void setY(float newVal){
		yv=newVal;
	}

	//ジャイロのゼロ点調整を行う
	void reviseGyroOwn(){
		static mylib::regularC rt(100);
		static int cont=0,stTime=0,stpTime=0;
		if(rt.ist()){
			if(!mc::isIsiStop()){
				stTime=0;
				stpTime=0;
				cont=0;
				return;
			}
			switch (cont){
				case 0:
				if(mc::isIsiStop()){
					stTime++;
				}
				if(stTime>60){
					cont++;
					stTime=0;
					out::setStop(true);
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
				out::setStop(false);
				gyro.stopDeg();
				gyro.updateOffset();
				gyro.startDeg();
				cont=0;
				break;
			}
		}
		return;
	}
	
	//超音波距離計による角度算出とジャイロの補正
	/*void reviseGyroExt(){
		static mylib::regularC rvs(interval);//rvs=revise
		static mylib::trueFalse witch(true);
		static mylib::delta<float> dg((float)readRedUSinterval/1000.0);
		if(rvs.ist()){
			if(witch.get()){
				if(blue::f.update()==aRedUS::TIMEOUT){
					blue::f.reset();
				}
				//pc.printf("f\n");
			}else{
				if(blue::b.update()==aRedUS::TIMEOUT){
					blue::b.reset();
				}
				//pc.printf("b\n");
			}
			if(!(blue::f.isTimeout()) && !(blue::b.isTimeout())){
				//float newDeg=((180.0*atan((blue::f.readMM()-blue::b.readMM())/400.0))/M_PI)*0.01 + gyro.getDeg()*0.99;
				float newDeg=(180.0*atan((blue::f.readMM()-blue::b.readMM())/400.0))/M_PI;
				if(abs(dg.f(newDeg))<0.1){
					gyro.setDeg( newDeg*0.5 + gyro.getDeg()*0.5 );
					pc.printf("f%4dmm  b%4dmm %4dmDeg\n",blue::f.readMM(),blue::b.readMM(),(int)(gyro.getDeg()*1000.0));
				}
				//pc.printf("f%4dmm  b%4dmm %4dmDeg\n",blue::f.readMM(),blue::b.readMM(),(int)(gyro.getDeg()*1000.0));
			}else{
				dg.reset();
			}
			//pc.printf("hey\n");
		}
	}*/
	
	void reviseByRedUS(){
		static mylib::regularC rvs(readRedUSinterval);//rvs=revise
		static mylib::trueFalse witch(true);
		if(rvs.ist()){
			if(witch.get()){
				if(fp->update()==aRedUS::TIMEOUT){
					fp->reset();
				}
				//pc.printf("f\n");
			}else{
				if(bp->update()==aRedUS::TIMEOUT){
					bp->reset();
				}
				//pc.printf("b\n");
			}
			reviseGyroExt();
			reviseYExt();
			//pc.printf("hey\n");
		}
	}
	void reviseGyroExt(){
		static mylib::delta<float> dg((float)readRedUSinterval/1000.0);
		if(!(fp->isTimeout()) && !(bp->isTimeout())){
			//float newDeg=((180.0*atan((fp->readMM()-bp->readMM())/400.0))/M_PI)*0.01 + gyro.getDeg()*0.99;
			float newDeg=(180.0*atan((fp->readMM()-bp->readMM())/400.0))/M_PI;
			if(abs(dg.f(newDeg))<0.1){
				gyro.setDeg( newDeg*0.5 + gyro.getDeg()*0.5 );
				pc.printf("f%4dmm  b%4dmm %4dmDeg\n",fp->readMM(),bp->readMM(),(int)(gyro.getDeg()*1000.0));
			}
			//pc.printf("f%4dmm  b%4dmm %4dmDeg\n",fp->readMM(),bp->readMM(),(int)(gyro.getDeg()*1000.0));
		}else{
			dg.reset();
		}
	}
	void reviseYExt(){
		if(!(fp->isTimeout()) && !(bp->isTimeout())){
			yv=((fp->readMM()+bp->readMM())/2.0)+280.0;
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

//move control
namespace mc{
	
	void setup(){
		pid::setup();
		out::setup();
	}
	void loop(){
		pid::loop();
		//outLoopは最後に呼ばれなければならない
		out::loop();
	}
	
	//上級が停止の意思があるかを示す（上級は止めているが下級のほうでPIDなどでマシンが動いてもよい）
	bool isIsiStopVal;
	void setIsiStop(bool val){
		isIsiStopVal=val;
	}
	bool isIsiStop(){
		return isIsiStopVal;
	}
	
	bool isBlueFieldVal=true;
	void setBlueField(bool val){
		isBlueFieldVal=val;
	}
	bool isBlueField(){
		return isBlueFieldVal;
	}
}

namespace out{
	//強制停止かどうか(操作元は上級の場合と下級の場合がある)
	bool isMustStop=false;
	float x;
	float y;
	float r;
	
	void actXY();
	void actR();
	void actStop();
	void out();
	
	void setup(){
		x=y=r=0.0;
		isMustStop=false;
	}
	void loop(){
		if(isMustStop){
			actStop();
		}else{
			actXY();
			actR();
		}
		out();
	}
	
	void setXY(float xa,float ya){
		x=xa;
		y=ya;
	}
	void setR(float ra){
		r=ra;
	}
	void setStop(bool is){
		isMustStop=is;
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
	//XY軸の制御を有効にするか
	bool isRunX=false,isRunY=false;
	const float deltaT=0.02;
	aPid<float> degPid(0.00008,0.00003,0.00005,deltaT);
	//aPid<float> degPid(0.0002,0.00000,0.0001,deltaT);
	
	void pactR();
	
	//outと同じ構造につまりsetとactおよびx,y,r変数にすべき?
	
	void setup(){
		degPid.set(0.0);
	}
	void loop(){
		static mylib::regularC pidt((int)(deltaT*1000.0));
		if(pidt.ist()){
			if(isRunX){
				//XY軸の制御pactXYをここに書く
			}
			if(isRunY){
				//XY軸の制御pactXYをここに書く
			}
			pactR();
		}
	}
	void turnX(bool is){isRunX=is;}
	void turnY(bool is){isRunY=is;}
	
	void pactR(){
		out::setR(degPid.calc(sensor::deg()));
	}
}

