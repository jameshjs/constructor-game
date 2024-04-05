#ifndef __PLAYER_H__
#define __PLAYER_H__

#include <iostream>
#include <sstream>
#include <string>
#include <map>
#include <vector>
#include "building.h"
#include "road.h"
#include "colour.h"
#include "resource.h"
#include "random.h"
using namespace std;

class Player {
private:
	Colour colour;
	int brick; // number of each resources that the player currently has
	int energy;
	int glass;
	int heat;
	int wifi;
	map<int, Building> buildings; // list of buildings the player currently has
	map<int, Road> roads; // list of roads the player currently has
	Random random;
	
	// check if there are enough resources to improve the building to house and tower	
	bool can_improve_h() const;
	bool can_improve_t() const;
public:
	Player(Colour colour); // initialize the player from a new setup with a given color
	Player(Colour colour, int brick, int energy, int glass, int heat, int wifi); // initialize the player from data stored in a save file

	ostream& print_resources(ostream& out) const; // print the resources the player currently has
	ostream& print_residences(ostream& out) const; // print the buildings and roads the player currently has
	
	int building_points() const; // returns the building points the player has
	bool isWon() const; // returns true if the player has more than ten building points
	
	// accessor functions that returns the player's color, list of buildings and roads, total resources
	Colour get_colour() const;
	map<int, Building>& get_buildings();
	map<int, Road>& get_roads();
	int resource_total() const;

	bool have_resource(Resource r) const; // check if the player has the certain resource
	
	void add_building(int index); // add a new building at the given vertex to the player without deducting resources
	void add_road(int index); // add a new road at the given edge to the player without deducting resources
	void add_improve(int index); // improve the building at the given vertex without deducting resources
	void build_building(int index); // add a new building at the given vertex to the player and deducting resources
	void build_road(int index); // add a new road at the given vertex to the player and deducting resources
	void improve(int index); // improve the building at the given vertex and deducting resources
	bool can_build_b() const; // check if player has enough resources to build a basement
	bool can_build_r() const; // check if player has enough resources to build a road
	bool own(int index) const; // check if the player owns a building on the given vertex
	bool can_improve(int index) const; // checks if the player has enough resources to improve the building
	bool tower(int index) const; // returns true if the building on the location is a tower, which cannot be improved

	void lost_to_geese(); // lost to geese one resource when the player was chosen
	Resource stolen(); // got stolen if the player has more than ten resources when someone rolled a seven
	void gain_resource(Resource resource, int num); // dice roll or trade or steal
	void lose_resource(Resource resource); // lose one unit of the certain resource from trade

	string save_player_data() const; // output the player's data into the save file
};

#endif
