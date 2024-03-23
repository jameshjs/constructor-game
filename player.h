#include <iostream>
#include <string>
#include <vector>
#include <sketch.h>

class Player {
private:
	Colour colour; // player colour, cannot be Colour::None
	int building_points; // current number of building points
	int brick; // number of bricks the player currently has
	int energy; // number of energies the player currently has
	int glass;
	int heat;
	int wifi;
	std::vector<Building> buildings;
	std::vector<Road> roads;
public:
	Player(Colour colour);
	~Player();

	std::string stringColour();
	std::string stringResource(Resource res);
	std::string stringBuilding(BuildingType bui);

	void print_resources();
	void print_residences();

	void add_resource(Resource type, int num);
	void geese_remove_resource(Resource type, int num);

	bool on_the_road(int vertex_number, Board board); // returns true if the vertex is connected to the player's road

	bool add_initial_basement(int vertex_number);
	bool build_residence(int vertex_number); // active_player attempts to build residence at vertex_number, returns true if succeeds and returns false if fails
	bool improve_building(int vertex_number);
	bool build_road(int edge_number);

	bool request_trade(Colour colour, Resource give, Resource take); // true if trade agreed, false if declined
	void resolve_trade(Colour colour, Resource give, Resource take); // called if trade agreed
	bool place_geese(); // if trying to place geese at invalid location, call it again to make the player try again
};

