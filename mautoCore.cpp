#include "mautoCore.hpp"

//夢を見て何が悪い←え？？
namespace player{
	coordFunc nowf=NULL;
	Timer t;
	bool isTimerRun;
	float xMult=1.0;
	
	void set(coordFunc);
	bool isPlayEnd();
	
	void loop(){
		if(mc::isBlueField()){
			//pc.printf("blue !");
			xMult=-1.0;
		}else{
			xMult=1.0;
		}
	}
	
	void set(coordFunc f){
		nowf=f;
		t.reset();
		t.start();
		isTimerRun=true;
	}
	#define SQ(X) ((X)*(X))
	float distSq(pointc val){
		float x=sensor::x(),y=sensor::y();
		return SQ(val.x-x)+SQ(val.y-y);
	}
	bool isPlayEnd(){
		pointc val;
		if(( val=nowf(t.read_ms()) ) ==coord::ENDCOORD){
			t.stop();
			isTimerRun=false;
			return true;
		}else{
			if(distSq(val)>SQ(500)){
				if(isTimerRun){
					t.stop();
					isTimerRun=false;
				}
			}else{
				if(!isTimerRun){
					t.start();
					isTimerRun=true;
				}
			}
			pid::psetX(xMult*val.x);
			pid::psetY(val.y);
			return false;
		}
	}
};

namespace auco{
	bool isEmerg=false;
	
	parentCmd cmdnow;
	statusCmd cmdsts;
	void procCmdnow();
	statusCmd readCmdsts();
	void procWalker();
	
	void setup(){
		pointc startp=coord::otsk(0);
		sensor::setX(startp.x);
		sensor::setY(startp.y);
		
		turnCmd(STOP);
	}
	void loop(){
		procCmdnow();
		player::loop();
	}
	
	//cmdを切り替えるときに呼ぶ　初期化などをする
	void turnCmd(parentCmd cmd){//setupてきな
		if(isEmerg){
			pc.printf("emg!\n");
			return;
		}
		cmdnow=cmd;
		cmdsts=MOVING;
		pc.printf("turn to %d",(int)cmd);
		switch((int)cmd){
			case STOP:
			mc::setIsiStop(true);
			pid::turnX(false);
			pid::turnY(false);
			cmdsts=MOVED;
			break;
			
			case OTSK:
			mc::setIsiStop(false);
			pid::turnX(true);
			pid::turnY(true);
			player::set(coord::otsk);
			break;
			
			case WALKER:
			mc::setIsiStop(false);
			pid::turnX(true);
			pid::turnY(true);
			sensor::setX(0);
			sensor::setY(0);
			break;
			
			default:
			pc.printf("unk cmd! %3d(0x%2X)\n",(int)cmd,(int)cmd);
			break;
		}
	}
	void procCmdnow(){//loop的な
		if(cmdsts==MOVING){
			switch((int)cmdnow){
				case STOP:
				//何もしない
				break;
				
				case OTSK:
				if(player::isPlayEnd()){
					cmdsts=MOVED;
				}
				break;
				
				case WALKER:
				procWalker();
				break;
				
				default:
				pc.printf("FATAL ERR in mautoCore procCmdnow default called!!\n");
				break;
			}
		}
	}
	statusCmd readCmdsts(){
		return cmdsts;
	}
	void emergIs(bool is){
		if(is){
			turnCmd(STOP);
			isEmerg=is;
			cmdsts=EMERG;
		}else{
			isEmerg=is;
			//cmdsts=MOVED;
		}
	}
	void procWalker(){
		static int cont=0;
		switch(cont){
			case 0:
			player::set(coord::walkerGo);
			cont++;
			//意図的にbreakなし
			case 1:
			if(player::isPlayEnd()){
				player::set(coord::walkerBack);
				cont++;
			}
			break;
			
			case 2:
			if(player::isPlayEnd()){
				cont=0;
				cmdsts=MOVED;
			}
			break;
		}
	}
};