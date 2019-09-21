#ifndef __AUTO_CORE_HPP__
#define __AUTO_CORE_HPP__

#include "runner.hpp"
#include "mbed.h"
#include "coord.hpp"
#include "useful.hpp"

namespace auco{
	void setup();
	void loop();
	
	enum parentCmd{
		STOP=0,
		OTSK=1,
		SHOT,
		GOBACK,
	};
	enum statusCmd{
		MOVING,
		MOVED,
	};
	
	void turnCmd(parentCmd cmd);
	statusCmd readCmdsts();
};

#endif