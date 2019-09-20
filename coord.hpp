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
};

#endif