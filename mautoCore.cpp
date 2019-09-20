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
		if(nowf(t.read_ms())==coord::ENDCOORD){
			t.stop();
			return true;
		}else{
			return false;
		}
	}
};

namespace auco{
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
		cmdnow=cmd;
		cmdsts=MOVING;
		switch((int)cmd){
			case STOP:
			mc::setIsiStop(true);
			pid::turnX(false);
			pid::turnY(false);
			break;
			
			case OTSK:
			mc::setIsiStop(false);
			pid::turnX(true);
			pid::turnY(true);
			player::set(coord::otsk);
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
		}
	}
	statusCmd readCmdsts(){
		return cmdsts;
	}
};