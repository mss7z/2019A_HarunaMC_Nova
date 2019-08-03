#include "aXBee.hpp"

//const int aXBee::rbuffSize=255;

aXBee::aXBee(PinName tx,PinName rx,int baudrate):
	srl(tx,rx),
	rcounter(0),
	ifReceiveFrame(NULL)
{
	srl.baud(baudrate);
	srl.attach(callback(this,&aXBee::ifReceive),Serial::RxIrq);
}


//送信の本体(APIのフレームにして送信)
//フレームデータ(Frame-Specific Data)の入った配列とその長さを受けっとって送信する
//後でエスケープに対応させること(api=2)
//2019miniroboのコントローラのArduinoプログラムを改造（もとは2018春のAPI一号か？）
void aXBee::sendFrame(const uint8_t frameData[],const uint16_t frameDataSize){
	unsigned int frameDataTotal=0;

	//Start Delimiter
	srl.putc(0x7E);

	//Length MSB
	srl.putc((frameDataSize>>8)&0xFF);

	//Length LSB
	srl.putc(frameDataSize&0xFF);

	//Frame-Specific Data (FrameData)
	for(int i=0;i<frameDataSize;i++){
		frameDataTotal += frameData[i];
		srl.putc(frameData[i]);
	}

	//CheckSum
	srl.putc(0xFF - (frameDataTotal & 0xFF));

	return;
}

void aXBee::ifReceive(){
	const uint8_t data=(uint8_t)srl.getc();
	switch(rcounter){
	case 0:
		if(data==0x7E){
			rcounter++;
		}
		break;
	case 1:
		rframeSize=(uint16_t)(data<<8);
		rcounter++;
		break;
	case 2:
		rframeSize|=(uint16_t)data;
		if(rframeSize>AXBEE_RBUFF_SIZE){
			rcounter=0;
		}else{
			rcounter++;
			rframeCounter=0;
			rbuffTotal=0;
		}
		break;
	case 3:
		rbuff[rframeCounter]=data;
		rbuffTotal+=data;
		rframeCounter++;
		if(!(rframeCounter<rframeSize)){
			rcounter++;
		}
		break;
	case 4:
		//if((0xFF-(rbuffTotal&0xFF)) == data){
		if(((rbuffTotal+data)&0xFF)==0xFF){
			if(NULL!=ifReceiveFrame){
				(*ifReceiveFrame)(rbuff,rframeSize);
			}
		}
		rcounter=0;
		break;
	}
}

void aXBee::attachFrame(void (*fp)(uint8_t*,uint16_t)){
	ifReceiveFrame=fp;
	return;
}