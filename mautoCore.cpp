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
			if(distSq(val)>SQ(400)){
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
	
	void procTowel1();
	void procTowel2();
	void procSheets();
	void procSheetsSet();
	void procWalker();
	
	void setCoord(coordFunc f, int t){
		pointc startp=f(t);
		sensor::setX(startp.x);
		sensor::setY(startp.y);
	}
	
	void setup(){
		
		
		turnCmd(STOP);
	}
	void loop(){
		static mylib::regularC time(500);
		if(time){
			pc.printf("cmdnow=%d cmdsts=%d\n",(int)cmdnow,(int)cmdsts);
		}
		procCmdnow();
		player::loop();
	}
	
	//cmdを切り替えるときに呼ぶ　初期化などをする
	void turnCmd(parentCmd cmd){//setupてきな
		if(isEmerg){
			//pc.printf("emg!\n");
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
			
			case OTSK:{
			mc::setIsiStop(false);
			pid::turnX(true);
			pid::turnY(true);
			player::set(coord::otsk);
			pointc startp=coord::otsk(0);
			sensor::setX(startp.x);
			sensor::setY(startp.y);
			break;
			}
			case TOWEL1:
			mc::setIsiStop(false);
			pid::turnX(true);
			pid::turnY(true);
			break;
			
			case TOWEL2:
			mc::setIsiStop(false);
			pid::turnX(true);
			pid::turnY(true);
			break;
			
			case SHEETS:
			mc::setIsiStop(false);
			pid::turnX(true);
			pid::turnY(true);
			break;
			
			case SHEETS_SET:
			mc::setIsiStop(false);
			pid::turnX(true);
			pid::turnY(true);
			break;
			
			case SHEETS_BOM:
			mc::setIsiStop(false);
			pid::turnX(true);
			pid::turnY(true);
			player::set(coord::sheetsBom);
			break;
			
			case GOBACK:
			mc::setIsiStop(false);
			pid::turnX(true);
			pid::turnY(true);
			player::set(coord::goback);
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
				
				case TOWEL1:
				procTowel1();
				break;
				
				case TOWEL2:
				procTowel2();
				break;
				
				case SHEETS:
				procSheets();
				break;
				
				case SHEETS_SET:
				procSheetsSet();
				break;
				
				case SHEETS_BOM:
				if(player::isPlayEnd()){
					cmdsts=MOVED;
				}
				break;
				
				case GOBACK:
				if(player::isPlayEnd()){
					cmdsts=MOVED;
				}
				break;
				
				case WALKER:
				procWalker();
				break;
				
				default:
				pc.printf("FATAL ERR in mautoCore procCmdnow : default was called!!\n");
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
	
	void procTowel1(){
		static int cont=0;
		static Timer time;
		switch(cont){
			case 0:
			player::set(coord::towel1);
			setCoord(coord::towel1,0);
			cont++;
			//意図的にbreakなし
			case 1:
			if(player::isPlayEnd()){
				cont++;
			}
			break;
			
			case 2:
			time.reset();
			time.start();
			cont++;
			//ib
			
			case 3:
			if(time.read_ms()>3000){
				cont=0;
				cmdsts=MOVED;
			}
			break;
		}
	}
	void procTowel2(){
		static int cont=0;
		static Timer time;
		switch(cont){
			case 0:
			player::set(coord::towel2);
			cont++;
			//意図的にbreakなし
			case 1:
			if(player::isPlayEnd()){
				cont++;
			}
			break;
			
			case 2:
			time.reset();
			time.start();
			cont++;
			//ib
			
			case 3:
			if(time.read_ms()>3000){
				cont=0;
				cmdsts=MOVED;
			}
			break;
		}
	}
			
	void procSheets(){
		static int cont=0;
		static Timer time;
		switch(cont){
			case 0:
			player::set(coord::sheetsReadWall);
			cont++;
			//意図的にbreakなし
			
			case 1:
			if(player::isPlayEnd()){
				sensor::resetFarw();
				cont++;
				time.reset();
				time.start();
			}
			break;
			
			case 2:
			sensor::reviseByFarw();
			if(time.read_ms()>3000){
				cont++;
				time.stop();
			}
			break;
			
			case 3:
			player::set(coord::sheetsExtendPoll);
			cont++;
			//意図的にbreakなし
			
			case 4:
			if(player::isPlayEnd()){
				cmdsts=MOVED;
				cont=0;
			}
			break;
		}
	}
	/*void procSheetsBom(){
		static int cont=0;
		switch(cont){
			case 0:
			player::set(coord::sheetsBomStarting);
			cont++;
			//意図的にbreakなし
			case 1:
			if(player::isPlayEnd()){
				player::set(coord::sheetsBomRunning);
				cont++;
			}
			break;
			
			case 2:
			if(player::isPlayEnd()){
				cmdsts=MOVED;
				cont=0;
			}
			break;
		}
	}*/
	void procSheetsSet(){
		static int cont=0;
		static Timer time;
		switch(cont){
			case 0:
			player::set(coord::sheetsSet);
			cont++;
			//意図的にbreakなし
			case 1:
			if(player::isPlayEnd()){
				cont++;
			}
			break;
			
			case 2:
			time.reset();
			time.start();
			cont++;
			//ib
			
			case 3:
			if(time.read_ms()>3000){
				cont=0;
				cmdsts=MOVED;
			}
			break;
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