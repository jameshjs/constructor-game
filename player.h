#include <iostream>
#include <vector>

class Player {
private:
	Colour colour; // player colour, cannot be Colour::None
	int building_points; // current number of building points
	int brick; // number of bricks the player currently has
	int energy; // number of energies the player currently has
	int glass;
	int heat;
	int wifi;
public:
	std::vector<Building> buildings;
	std::vector<Road> roads;
	void print();
	void print_residences();
};