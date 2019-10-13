#ifndef __COORD_HPP__
#define __COORD_HPP__

struct pointc{
	int x;
	int y;
	bool operator==(pointc val){
		return x==val.x && y==val.y;
	}
};
//using coordFunc = pointc (*)(int);
typedef pointc (*coordFunc)(int);

namespace coord{
	
	const pointc ENDCOORD={0xfffffff,0xfffffff};
	pointc otsk(int);
	
	pointc walkerGo(int);
	pointc walkerBack(int);
	
	pointc towel1ByHomew(int);
	pointc towel1(int);
	pointc towel2(int);
	
	pointc sheetsReadWall(int);
	pointc sheetsExtendPoll(int);
	pointc sheetsSet(int);
	pointc sheetsBom(int);
	
	pointc goback(int);
};

#endif