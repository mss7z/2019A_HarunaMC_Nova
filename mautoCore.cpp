#include "mautoCore.hpp"

//夢を見て何が悪い←え？？
namespace player{
	coordFunc nowf=NULL;
	Timer t;
	bool isTimerRun;
	float xMult=1.0;
	
	void set(coordFunc);
	bool isPlayEnd();
	pointc readFunc(coordFunc,int);
	
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
		if(( val=readFunc(nowf,t.read_ms()) ) ==coord::ENDCOORD){
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
			pid::psetX(val.x);
			pid::psetY(val.y);
			return false;
		}
	}
	pointc readFunc(coordFunc f,int t){
		pointc val=f(t);
		if(val==coord::ENDCOORD){
			return coord::ENDCOORD;
		}else{
			val.x*=xMult;
			return val;
		}
	}
};

namespace auco{
	bool isEmerg=false;
	
	parentCmd cmdnow;
	statusCmd cmdsts;
	void procCmdnow();
	statusCmd readCmdsts();
	
	void setCoord(coordFunc f, int t);
	void procOtsk();
	void procTowel1();
	void procTowel2();
	void procSheets();
	void procSheetsSet();
	void procWalker();
	void procGoback();
	
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
	
	void setCoord(coordFunc f, int t){
		pointc startp=player::readFunc(f,t);
		sensor::setX(startp.x);
		sensor::setY(startp.y);
	}
	void setPid(coordFunc f, int t){
		pointc startp=player::readFunc(f,t);
		pid::psetX(startp.x);
		pid::psetY(startp.y);
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
			
			case OTSK:
			mc::setIsiStop(false);
			pid::turnX(true);
			pid::turnY(true);
			//player::set(coord::otsk);
			//setCoord(coord::otsk,0);
			break;
			
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
			//player::set(coord::goback);
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
				/*if(player::isPlayEnd()){
					cmdsts=MOVED;
				}*/
				procOtsk();
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
				/*if(player::isPlayEnd()){
					cmdsts=MOVED;
				}*/
				procGoback();
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
			if(cmdnow==STOP){
				cmdsts=MOVED;
			}
			//cmdsts=MOVED;
		}
	}
	
	void procOtsk(){
		static int cont=0;
		static Timer time;
		switch(cont){
			case 0:
			setPid(coord::otsk,0);
			setCoord(coord::otsk,0);
			sensor::resetHomew();
			time.reset();
			time.start();
			cont++;
			
			case 1:
			sensor::reviseByHomew();
			if(time.read_ms()>3000){
				cont++;
				player::set(coord::otsk);
			}
			break;
			
			//意図的にbreakなし
			case 2:
			if(player::isPlayEnd()){
				cont++;
			}
			break;
			
			case 3:
			sensor::resetHomew();
			pid::psetGain(pid::BY_INWORLD);
			time.reset();
			time.start();
			cont++;
			//ib
			
			case 4:
			sensor::reviseByHomew();
			if(time.read_ms()>150000){
				cont=0;
				pid::psetGain(pid::BY_OUTWORLD);
				cmdsts=MOVED;
			}
			break;
		}
	}
	
	void procTowel1(){
		static int cont=0;
		static Timer time;
		switch(cont){
			case 0:
			player::set(coord::towel1ByHomew);
			setCoord(coord::towel1ByHomew,0);
			sensor::resetHomew();
			pid::psetGain(pid::BY_HOMEW);
			cont++;
			//意図的にbreakなし
			case 1:
			//if(-1000<sensor::x() && sensor::x()<1000){
				sensor::reviseByHomew();
			//}
			if(player::isPlayEnd()){
				player::set(coord::towel1);
				pid::psetGain(pid::BY_INWORLD);
				sensor::resetBackPole();
				cont++;
			}
			break;
			
			case 2:
			if((1400<sensor::x() && sensor::x()<1700) || (-1400>sensor::x() && sensor::x()>-1700)){
				sensor::reviseByBackPoleTshirt();
			}
			if(player::isPlayEnd()){
				time.reset();
				time.start();
				sensor::resetHomePole();
				pid::psetGain(pid::BY_OUTWORLD);
				cont++;
			}
			break;
		
			case 3:
			sensor::reviseByHomePole();
			if(time.read_ms()>3000){
				pid::psetGain(pid::BY_INWORLD);
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
			pid::psetGain(pid::BY_OUTWORLD);
			sensor::resetFarPole();
			//ib
			
			case 3:
			sensor::reviseByFarPole();
			if(time.read_ms()>3000){
				pid::psetGain(pid::BY_INWORLD);
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
			pid::psetGain(pid::BY_INWORLD);
			player::set(coord::sheetsReadWall);
			cont++;
			//意図的にbreakなし
			
			case 1:
			if(player::isPlayEnd()){
				sensor::resetFarw();
				sensor::resetBackPole();
				//setCoord(coord::sheetsExtendPoll,0);
				//pid::psetGain(pid::BY_INWORLD);
				pid::psetGain(pid::BY_FARW);
				cont++;
				time.reset();
				time.start();
			}
			break;
			
			case 2:
			sensor::reviseByFarw();
			sensor::reviseByBackPole();
			if(time.read_ms()>4000){
				pid::psetGain(pid::BY_INWORLD);
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
			sensor::resetFarPole();
			//pid::psetGain(pid::BY_INWORLD);
			cont++;
			//ib
			
			case 3:
			sensor::reviseByFarPole();
			if(time.read_ms()>3000){
				//pid::psetGain(pid::BY_INWORLD);
				cont=0;
				cmdsts=MOVED;
			}
			break;
		}
	}
	void procGoback(){
		static int cont=0;
		//static Timer time;
		switch(cont){
			case 0:
			player::set(coord::goback);
			cont++;
			
			//意図的にbreakなし
			case 1:
			//sensor::reviseByHomew();
			if(player::isPlayEnd()){
				cont++;
			}
			break;
			
			case 2:
			player::set(coord::gobackByHomew);
			sensor::resetHomew();
			pid::psetGain(pid::BY_HOMEW);
			cont++;
			//ib
			
			case 3:
			sensor::reviseByHomew();
			if(player::isPlayEnd()){
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