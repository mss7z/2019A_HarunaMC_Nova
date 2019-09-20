#ifndef __AUTO_CORE_HPP__
#define __AUTO_CORE_HPP__

#include "runner.hpp"
#include "mbed.h"
#include "coord.hpp"

namespace auco{
	void setup();
	void loop();
	
	enum parentCmd{
		OTSK,
		SHOT,
		GOBACK,
		STOP,
	};
	enum statusCmd{
		MOVING,
		MOVED,
	};
	
	void turnCmd(parentCmd cmd);
	statusCmd readCmdsts();
};

#endif