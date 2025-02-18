#ifndef __AUTO_CORE_HPP__
#define __AUTO_CORE_HPP__

#include "runner.hpp"
#include "mbed.h"
#include "coord.hpp"
#include "useful.hpp"

namespace player{
	void loop();
};

namespace auco{
	void setup();
	void loop();
	
	enum parentCmd{
		STOP=0,
		TOWEL1,
		TOWEL2,
		SHEETS,
		SHEETS_SET,
		SHEETS_BOM,
		GOBACK,
		WALKER=7,
		OTSK=8,
	};
	enum statusCmd{
		EMERG=1,
		MOVING,
		MOVED,
	};
	
	void turnCmd(parentCmd cmd);
	statusCmd readCmdsts();
	void emergIs(bool);
};

#endif