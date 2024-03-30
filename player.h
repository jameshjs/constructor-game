#ifndef __PLAYER_H__
#define __PLAYER_H__

#include <iostream>
#include <string>
#include <map>
#include <vector>
#include "vertex.h"
#include "edge.h"
#include "colour.h"
#include "resource.h"
using namespace std;

class Player {
private:
	Colour colour;
	int building_points; // current number of building points
	int brick; // number of bricks the player currently has
	int energy; // number of energies the player currently has
	int glass;
	int heat;
	int wifi;
	map<int, Building> buildings;
	map<int, Road> roads;
	
	bool can_improve_h() const;
	bool can_improve_t() const;
public:
	Player(Colour colour);
	ostream& print_resources(ostream& out);
	ostream& print_residences(ostream& out);

	Colour get_colour() const;
	map<int, Building> get_buildings();
	
	void add_building(int index); // add to vector
	void add_road(int index); // add to vector
	void build_building(int index); // add to vector and deduct cost
	void build_road(int index); // add to vector and deduct cost
	void improve(int index); 
	bool can_build_b() const; // check for resources
	bool can_build_r() const;
	bool can_improve(int index) const;

	void lost_to_geese(); // lost to geese// unimplemented 
	void gain_resource(Resource resource, int num); // dice roll or trade or steal

	void save_player_data();// unimplemented 
};

#endif
