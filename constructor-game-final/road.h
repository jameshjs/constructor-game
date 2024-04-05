#ifndef __ROAD_H__
#define __ROAD_H__

#include <string>
#include "colour.h"
using namespace std;

class Road {
	Colour colour;
	
	public:
	Road();
	Road(Colour colour);
	string print() const;
	Colour getColour() const;
};

#endif
