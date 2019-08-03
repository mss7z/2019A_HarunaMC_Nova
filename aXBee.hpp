#ifndef __AXBEE_HPP__
#define __AXBEE_HPP__

#include "mbed.h"

#define AXBEE_RBUFF_SIZE 255

class aXBee{
protected:
	Serial srl;
	void ifReceive();
	int rcounter;
//	static const int rbuffSize;
	uint8_t rbuff[AXBEE_RBUFF_SIZE];
	unsigned int rbuffTotal;
	
	uint16_t rframeSize;
	int rframeCounter;
	void (*ifReceiveFrame)(uint8_t*,uint16_t);
public:
	aXBee(PinName tx,PinName rx,int baudrate=9600);
	
	void sendFrame(const uint8_t frameData[],const uint16_t frameDataSize);
	
	void attachFrame(void (*fp)(uint8_t*,uint16_t));
	void baud(int baudrate){srl.baud(baudrate);}
};

#endif