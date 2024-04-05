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
	Tile(int tile_number, int tile_value, bool geese, Resource resource); // constructor
	// print functions for the tile number, tile resource, tile value, and if geese is on the tile
	string print_num() const;
	string print_resource() const;
	string print_value() const;
	string print_geese() const;

	bool have_geese() const; // returns true if geese is on the tile
	void set_geese(bool value); // set the tile to have or not have geese
	int get_num() const; // return the tile number
	int get_value() const; // return the tile value
	Resource get_resource() const; // return the tile resource
};

#endif
