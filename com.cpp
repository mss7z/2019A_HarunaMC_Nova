#include "com.hpp"

//親マイコンからの移動指令を処理
namespace receive{
	void setup(){
		rcv::cmd.attach(rcv::ifReceive,Serial::RxIrq);
	}
	void loop(){
	}
	
	//変数
	float pw[4];
	Serial cmd(PA_9,PB_7);
	
	//関数
	void ifReceive(){
		static int cont=0,contVals=0;
		static uint8_t vals[RDS];
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
			if(!(contVals<RDS)){
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

	void procRecieve(uint8_t vals[]){
		//pc.printf("get ");
	/*	for(int i=0;i<Q4+1;i++){
			pc.printf("vals[%d]=%d ",i,(int)(  mc(vals[i])*100.0   ));
		}*/
		//pc.printf("\n");
		float x=mc(vals[X]),y=mc(vals[Y]),k=mc(vals[K]);
		pw[0]=x;
		pw[1]=y;
		pw[2]=k;
		//pc.printf("x:%5d y:%5d r:%5d\n",(int)(x*1000),(int)(y*1000),(int)(r*1000));
		
		if(vals[X]==128 && vals[Y]==128){
			mc::isIsiStop=true;
		}else{
			mc::isIsiStop=false;
			out::setStop(false);
		}
		
		out::setXY(x,y);
		return;
	}
}

//遠隔非常停止
namespace emergency{
	bool isEmerg=false;
	aXBee xbee(PA_0,PA_1,38400);
	
	void setup(){
		xbee.attachFrame(receive);
	}
	
	void loop(){
		static mylib::regularC ct(300);//ct=check time
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
				mt::isStop=isEmerg;
			}
		}
	}
}
