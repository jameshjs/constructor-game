#ifndef __TILE_H__
#define __TILE_H__

#include <string>
#include "resource.h"
using namespace std;

// 19 instances
class Tile {
	int tile_number;
	int tile_value; // winning number for dice roll
	bool geese;
	Resource resource; // the resouce type that the tile gives
	
	public:
	Tile(int tile_number, int tile_value, bool geese, Resource resource);
	string print_num() const;
	string print_resource() const;
	string print_value() const;
	string print_geese() const;
	bool have_geese() const;
	void set_geese(bool value);
	int get_num() const;
	int get_value() const;
	Resource get_resource() const;
};

#endif
