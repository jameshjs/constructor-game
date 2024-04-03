#ifndef __PLAYER_H__
#define __PLAYER_H__

#include <iostream>
#include <sstream>
#include <string>
#include <map>
#include <vector>
#include "vertex.h"
#include "edge.h"
#include "colour.h"
#include "resource.h"
#include "random.h"
using namespace std;

class Player {
private:
	Colour colour;
	int brick; // number of bricks the player currently has
	int energy; // number of energies the player currently has
	int glass;
	int heat;
	int wifi;
	map<int, Building> buildings;
	map<int, Road> roads;
	Random random;
	
	bool can_improve_h() const;
	bool can_improve_t() const;
public:
	friend class HumanPlayer;
	friend class ComputerPlayer;

	Player(Colour colour);
	Player(Colour colour, int brick, int energy, int glass, int heat, int wifi);

	ostream& print_resources(ostream& out);
	ostream& print_residences(ostream& out);
	
	int building_points() const;

	Colour get_colour() const;
	map<int, Building> get_buildings();
	map<int, Road> get_roads();
	int resource_total() const;
	bool have_resource(Resource r) const;
	
	void add_building(int index); // add to vector
	void add_road(int index); // add to vector
	void add_improve(int index);
	void build_building(int index); // add to vector and deduct cost
	void build_road(int index); // add to vector and deduct cost
	void improve(int index); 
	bool can_build_b() const; // check for resources
	bool can_build_r() const;
	bool can_improve(int index) const;

	void lost_to_geese(); // lost to geese
	Resource stolen(); // got stolen from
	void gain_resource(Resource resource, int num); // dice roll or trade or steal
	void lose_resource(Resource resource);

	string save_player_data();// unimplemented 

	bool isWon();
	virtual int roll_dice();
};

#endif
