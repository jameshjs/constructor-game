#ifndef __BUILDING_H__
#define __BUILDING_H__

#include <string>
#include "colour.h"
using namespace std;

enum class BuildingType{Basement, House, Tower};

ostream& operator<<(ostream& out, const BuildingType type);

class Building {
	Colour colour;
	BuildingType type;

	public:
	Building();
	Building(Colour colour);
	string print() const;
	Colour getColour() const;
	BuildingType getType() const;
	void improve();
};

#endif
