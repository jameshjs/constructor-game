#include <iostream>
#include <string>
#include <vector>
#include "board.h"

class Player {
private:
	Colour colour; // player colour, cannot be Colour::None
	int building_points; // current number of building points
	int brick; // number of bricks the player currently has
	int energy; // number of energies the player currently has
	int glass;
	int heat;
	int wifi;
	std::vector<int> buildings;
	std::vector<int> roads;
public:
	Player(Colour colour);

	void print_resources();
	void print_residences(Board b);

	void add_resource(Resource type, int num);
	void remove_resource(Resource type, int num);

	bool request_trade(Colour colour, Resource give, Resource take); // true if trade agreed, false if declined
	void resolve_trade(Colour colour, Resource give, Resource take); // called if trade agreed
	bool place_geese(); // if trying to place geese at invalid location, call it again to make the player try again

	void save_player_data(std::string filename, Board b); // output the player data to the document to save file

	bool build_residence(int vertex_number, Board b);
	bool add_initial_basement(int vertex_number, Board b);
	bool build_road(int edge_number, Board b);
	bool add_initial_road(int edge_number, Board b);
	bool improve_building(int vertex_number, Board b);

};

