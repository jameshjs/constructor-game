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
	~Player();

	Colour getColour();
	int getBrick();
	int getEnergy();
	int getGlass();
	int getHeat();
	int getWifi();
	std::vector<int> getBuildings();
	std::vector<int> getRoads();

	void changeBuildingPoint(int num);

	void print_resources();
	void print_residences();

	void add_resource(Resource type, int num);
	void remove_resource(Resource type, int num);

	bool request_trade(Colour colour, Resource give, Resource take); // true if trade agreed, false if declined
	void resolve_trade(Colour colour, Resource give, Resource take); // called if trade agreed
	bool place_geese(); // if trying to place geese at invalid location, call it again to make the player try again

	void save_player_data(std::string filename); // output the player data to the document to save file
};

