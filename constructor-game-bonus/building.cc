#include "building.h"

ostream& operator<<(ostream& out, const BuildingType type) {
	if (type == BuildingType::Basement) return out << "Basement";
	if (type == BuildingType::House) return out << "House";
	return out << "Tower";
}

Building::Building() {}
Building::Building(Colour colour) : colour{colour}, type{BuildingType::Basement} {}

string Building::print() const {
	if (type == BuildingType::Basement) return td_colour(colour) + "B";
	if (type == BuildingType::House) return td_colour(colour) + "H";
	return td_colour(colour) + "T";
}

Colour Building::getColour() const {return colour;}
BuildingType Building::getType() const {return type;}

void Building::improve() {
	if (type == BuildingType::Basement) type = BuildingType::House;
	if (type == BuildingType::House) type = BuildingType::Tower;
}
