#ifndef __COM_HPP__
#define __COM_HPP__

#include "mbed.h"

#include "aXBee.hpp"

#include "useful.hpp"
#include "runner.hpp"
#include "mautoCore.hpp"

//親マイコンからの移動指令を処理
namespace receive{
	void setup();
	void loop();
	
	/*
	enum{
		X,
		Y,
		R,
		RDS,//receive data size
	};
	*/
	enum{
		CMD,
		RDS,//receive data size
	};
}
namespace rcv=receive;

//遠隔非常停止
namespace emergency{
	void setup();
	void loop();
	
	extern bool isEmerg;
	
	extern aXBee xbee;
	
	void request();
	void receive(uint8_t data[],uint16_t size);
	void procCmdReponse(uint8_t data[],uint16_t size);
}
namespace emerg=emergency;

#endif