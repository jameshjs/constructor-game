#include "vertex.h"

ostream& operator<<(ostream& out, const BuildingType type) {
	switch(type) {
		case BuildingType::Basement : return out << "Basement";
		case BuildingType::House : return out << "House";
		case BuildingType::Tower : return out << "Tower";
	}
	return out;
}

Building::Building() {}
Building::Building(Colour colour) : colour{colour}, type{BuildingType::Basement} {}

string Building::print() const {
	switch(type) {
		case BuildingType::Basement : return td_colour(colour) + "B";
		case BuildingType::House : return td_colour(colour) + "H";
		case BuildingType::Tower : return td_colour(colour) + "T";
	}
	return td_colour(colour) + "T";
}

Colour Building::getColour() const {return colour;}
BuildingType Building::getType() const {return type;}

Vertex::Vertex(int vertex_number, vector<int> neighbouring_tiles, vector<int> neighbouring_edges, vector<int> neighbouring_vertices) :
	vertex_number{vertex_number}, 
	building_built{false}, 
	neighbouring_tiles{neighbouring_tiles}, 
	neighbouring_edges{neighbouring_edges}, 
	neighbouring_vertices{neighbouring_vertices} 
	{}

string Vertex::print() const {
	if (building_built) return building.print();
	string padding = (vertex_number < 10) ? " " : "";
	return padding + to_string(vertex_number);
}

bool Vertex::building_exist() const {
	return building_built;
}

void Vertex::place_basement(Colour colour) {
	building_built = true;
	building = Building(colour);
}

vector<int>& Vertex::get_neighbour_vertices() {return neighbouring_vertices;}
vector<int>& Vertex::get_neighbour_edges() {return neighbouring_edges;}

Building Vertex::getBuilding() const {return building;}
