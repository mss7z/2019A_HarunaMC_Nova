//NIT,Akita College Robocon Akita
//2019 A-team Haruna Movement Controller
//Project Nova by mss7z

#include "mbed.h"

#include "aMotor.hpp"
#include "aXBee.hpp"
#include "useful.hpp"
#include "aAeGyroSmd.hpp"

/*Serial pc(USBTX,USBRX);
DigitalOut led(LED1);*/

namespace motor{
	/*aMotorPwm m1(PC_1,PC_0);
	aMotorPwm m2(PC_3,PC_2);
	aMotorPwm m3(PC_8,PC_6);
	aMotorPwm m4(PC_9,PB_8);
	*/
	aMotorPwm m1(PC_6,PC_8);
	aMotorPwm m2(PB_8,PC_9);
	aMotorPwm m3(PA_10,PB_3);
	aMotorPwm m4(PB_5,PB_10);
	
	aMotorPwm &q1=m1;
	aMotorPwm &q2=m2;
	aMotorPwm &q3=m3;
	aMotorPwm &q4=m4;
}
namespace mt=motor;

namespace rcv{
	
	enum{
		X,
		Y,
		SN,//solenoid
		RECEIVE_DS,
	};
	//Serial cmd(PA_0,PA_1);
	//Serial cmd(PC_10,PC_11);
	
	Serial cmd(PA_9,PB_7);
	
	extern float pw[];
	
	void ifReceive();
	float mc(uint8_t);
	void procRecieve(uint8_t[]);
}

namespace emergency{
	extern bool isEmerg;
	
	extern aXBee xbee;
	
	void setup();
	void loop();
	void request();
	void receive(uint8_t data[],uint16_t size);
	void procCmdReponse(uint8_t data[],uint16_t size);
		
}
namespace emerg=emergency;

namespace sensor{
	//a_imu03a gyro(D11,D12,D13,D10);
	//a_imu03a gyro(PB_15,PB_14,PB_13,PC_4);
	aAeGyroSmd gyro(A5,1.2);
}

namespace monitor{
	void loop(){
		static mylib::regularC pt(500);
		if(pt.ist()){
			for(int i=0;i<4;i++){
				pc.printf("pw[%d]=%d ",i,(int)(rcv::pw[i]*1000));
			}
		}
	}
}



int main(){
	//mt::m3.set(0.3);
	//return 0;
	rcv::cmd.attach(rcv::ifReceive,Serial::RxIrq);
	pc.printf("hello monkey\n");
	
	//sensor::gyro.startDeg();
	
	emerg::setup();
	
	while (true){
		emerg::loop();
		
		monitor::loop();
	}
	
    return 0;
}

namespace emergency{
	bool isEmerg=false;
	aXBee xbee(PA_0,PA_1,38400);
	
	void setup(){
		xbee.attachFrame(receive);
	}
	
	void loop(){
		static mylib::regularC ct(800);//ct=check time
		if(ct.ist()){
			request();
		}
	}
	
	void request(){
		//check は非常停止が押されているか
		static const uint8_t check[]={
			0x17,//remote at cmd request
			0x01,//frame id
			0x00,0x13,0xA2,0x00,0x40,0xCA,0x9D,0x64,
			0xFF,0xFE,
			0x02,//Remote cmd. options
			'I','S',//AT cmd
		};
		xbee.sendFrame(check,sizeof(check)/sizeof(check[0]));
		
		//ledは一応確認用に点滅させる
		static uint8_t led[]={
			0x17,//remote at cmd request
			0x01,//frame id
			0x00,0x13,0xA2,0x00,0x40,0xCA,0x9D,0x64,
			0xFF,0xFE,
			0x02,//Remote cmd. options
			'D','2',//AT cmd
			0x04,//value
		};
		if(led[15]==0x04){
			//pc.printf("0x04\n");
			led[15]=0x05;//output low
		}else{
			led[15]=0x04;//output high
		}
		xbee.sendFrame(led,sizeof(led)/sizeof(led[0]));
	}
	
	void receive(uint8_t data[],uint16_t size){
		switch(data[0]){
		case 0x97://remote at command response
			/*for(int i=0;i<size;i++){
				pc.printf("%02X ",data[i]);
			}*/
			procCmdReponse(data,size);
			break;
		default:
			break;
		}
		return;
	}
	
	void procCmdReponse(uint8_t data[],uint16_t size){
		if(data[12]=='I' && data[13]=='S'){//at cmd
			if(data[14]==0x00){//at cmd statusが0x00(SUCCESS)なら
				isEmerg=!((data[20]>>1)&0x1);//DIO1がHIGHか？
			}
		}
	}
}

namespace rcv{
	
	void ifReceive(){
		static int cont=0,contVals=0;
		static uint8_t vals[RECEIVE_DS];
		uint8_t c=cmd.getc();
		//pc.printf("0x%02X ",c);
		
		switch(cont){
			case 0:
			if(c==0x3E){
				cont++;
				contVals=0;
			}
			break;
			
			case 1:
			vals[contVals]=c;
			contVals++;
			if(!(contVals<RECEIVE_DS)){
				cont=0;
				procRecieve(vals);
			}
			break;
		}
		return;
	}
	
	float mc(uint8_t v){
		return ((float)v-128.0)/128.0;
	}
	float pw[4];
	void procRecieve(uint8_t vals[]){
		//pc.printf("get ");
	/*	for(int i=0;i<Q4+1;i++){
			pc.printf("vals[%d]=%d ",i,(int)(  mc(vals[i])*100.0   ));
		}*/
		//pc.printf("\n");
		float x=mc(vals[X]),y=mc(vals[Y]);
		
		const float pi=3.1415926535;
		const float rads[]={
			pi/4,
			3*pi/4,
			-3*pi/4,
			-pi/4,
		};
		
		for(int i=0;i<4;i++){
			pw[i]=(x*cos(rads[i])+y*sin(rads[i]));
			//pc.printf("pw[%d]=%d ",i,(int)(pw[i]*1000));
		}
		//pc.printf("\n");
		
		mt::q1.set(pw[0]);
		mt::q2.set(pw[1]);
		mt::q3.set(pw[2]);
		mt::q4.set(pw[3]);
		return;
	}
}