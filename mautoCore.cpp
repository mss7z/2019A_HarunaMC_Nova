#include "mautoCore.hpp"

//夢を見て何が悪い←え？？
namespace player{
	coordFunc nowf=NULL;
	Timer t;
	void set(coordFunc f){
		nowf=f;
		t.reset();
		t.start();
	}
	bool isPlayEnd(){
		pointc val;
		if(( val=nowf(t.read_ms()) ) ==coord::ENDCOORD){
			t.stop();
			return true;
		}else{
			pid::psetX(val.x);
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
	
	void setup(){
		turnCmd(STOP);
	}
	void loop(){
		procCmdnow();
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
			
			default:
			pc.printf("unk cmd! %3d(0x%2X)\n",(int)cmd,(int)cmd);
			break;
		}
	}
	void procCmdnow(){//loop的な
		switch((int)cmdnow){
			case STOP:
			//何もしない
			break;
			
			case OTSK:
			if(player::isPlayEnd()){
				cmdsts=MOVED;
			}
			break;
			
			default:
			pc.printf("FATAL ERR in mautoCore procCmdnow default called!!\n");
			break;
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
};