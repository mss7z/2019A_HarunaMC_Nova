#include "runner.hpp"


namespace sensor{
	float xv=0.0,yv=0.0;
	Ticker calcXYtime;
	mylib::delta<float> dx,dy;
	static const int readRedUSinterval=40;
	
	void reviseGyroOwn();
	void reviseByRedUS();
	void reviseGyroExt();
	void reviseXExt();
	void calcXY();
	
	void setup(){
		gyro.startDeg();
		calcXYtime.attach(calcXY,0.01);
		dx.reset();
		dy.reset();
	}
	void loop(){
		//reviseGyroOwn();
		reviseByRedUS();
		
		if(mc::isBlueField()){
			fp=&redus::bluef;
			bp=&redus::blueb;
		}else{
			fp=&redus::redf;
			bp=&redus::redb;
		}
			
	}

	aAeGyroSmd gyro(PC_5,1.0);
	
	aRotaryEncoder yenc(A5,A4,PullDown,false);
	aRotaryEncoder xenc(A2,A3,PullDown);
	
	namespace redus{
		const int TIMEOUT=5*1000;//us?
		aRedUS bluef(PC_3,TIMEOUT);
		aRedUS blueb(PC_2,TIMEOUT);
		aRedUS redf(PH_1,TIMEOUT);
		aRedUS redb(PA_15,TIMEOUT);
		aRedUS front(PB_13,TIMEOUT);
		aRedUS back(PB_14,TIMEOUT);
		//aRedUSはプルダウン
	}
	aRedUS *fp=NULL,*bp=NULL;
	
	void calcXY(){
		//エンコーダ1カウント当たり何ミリメートルか？
		//static const float mmPerREcont=0.6258641615;//------------------------------------------------------sitei
		static const float mmPerREcont=0.3098641192;//1回転1024パルス、円周101Pi、(101Pi)/1024
		//書いてて気が付いたけど、これって線形変換の回転移動？
		const float dxv=dx.f(xenc.readRaw()), dyv=dy.f(yenc.readRaw());
		xv+=(dxv*cos(rad())-dyv*sin(rad()))*mmPerREcont;
		yv+=(dxv*sin(rad())+dyv*cos(rad()))*mmPerREcont;
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
	
	//RedUSによるセンサー補正の管理人
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
			//reviseXExt();
			//pc.printf("hey\n");
		}
	}
	//超音波距離計による角度算出とジャイロの補正
	void reviseGyroExt(){
		static mylib::delta<float> dg((float)readRedUSinterval/1000.0);
		if(!(fp->isTimeout()) && !(bp->isTimeout())){
			//400はセンサー間の距離400mm
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
	void reviseXExt(){
		if(!(fp->isTimeout()) && !(bp->isTimeout())){
			//マシンの外から中央までの距離280mm???????????????????????????????????????????????????????????????????
			xv=((fp->readMM()+bp->readMM())/2.0)+280.0;
		}
	}
}

namespace motor{
	
	bool isStop=false;
	DigitalOut mton(PC_4);
	
	void setup(){
		on(true);
	}
	
	enum{
		Q1,
		Q2,
		Q3,
		Q4,
		MTDS,//motor data size
	};
	
	aMt m1(PC_6,PC_8);
	aMt m2(PC_9,PB_8);
	aMt m3(PB_3,PA_10);
	aMt m4(PB_10,PB_5);
	
	aMt &q1=m3;
	aMt &q2=m1;
	aMt &q3=m2;
	aMt &q4=m4;
	
	aMt *q[MTDS]={&q1,&q2,&q3,&q4};
	float o[MTDS];
	
	void on(bool is){
		mton=is;
	}
	void emergStopIs(bool is){
		isStop=is;
		on(!is);
	}
}
namespace mt=motor;

//move control
namespace mc{
	DigitalIn fieldSw(PB_15);
	bool isBlueFieldVal=true;
	
	void setup(){
		pid::setup();
		out::setup();
		mt::setup();
	}
	void loop(){
		isBlueFieldVal=fieldSw;
		
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
	//set権限はあちこち変わる
	void setX(float xa){
		x=xa;
	}
	void setY(float ya){
		y=ya;
	}
	void setR(float ra){
		r=ra;
	}
	void setStop(bool is){
		isMustStop=is;
	}
	void actXY(){
		const float pi=M_PI;
		const float rads[]={
			3*pi/4,
			-3*pi/4,
			-pi/4,
			pi/4,
		};
		
		for(int i=0;i<mt::MTDS;i++){
			mt::o[i]=(x*cos(rads[i]+sensor::rad())+y*sin(rads[i]+sensor::rad()));
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
	aPid<float> pidR(0.00008,0.00003,0.00005,deltaT);
	aPid<float> pidX(0.00002,0.00002,0.00000,deltaT);
	aPid<float> pidY(0.00002,0.00002,0.00000,deltaT);
	
	void pactR();
	void pactX();
	void pactY();
	
	//outと同じ構造につまりsetとactおよびx,y,r変数にすべき?
	
	void setup(){
		psetR(sensor::deg());
		psetX(sensor::x());
		psetY(sensor::y());
		turnX(true);
		turnY(true);
	}
	void loop(){
		static mylib::regularC pidt((int)(deltaT*1000.0));
		if(pidt.ist()){
			if(isRunX){
				pactX();
			}
			if(isRunY){
				pactY();
			}
			pactR();
		}
	}
	void turnX(bool is){
		if(is)pidX.reset();
		isRunX=is;
	}
	void turnY(bool is){
		if(is)pidY.reset();
		isRunY=is;
	}
	
	void psetX(float xa){
		pidX.set(xa);
	}
	void psetY(float ya){
		pidY.set(ya);
	}
	void psetR(float ra){
		pidR.set(ra);
	}
	float preadX(){return pidX.read();}
	float preadY(){return pidY.read();}
	
	void pactR(){
		out::setR(pidR.calc(sensor::deg()));
	}
	void pactX(){
		out::setX(pidX.calc(sensor::x()));
	}
	void pactY(){
		out::setY(pidY.calc(sensor::y()));
	}
}

