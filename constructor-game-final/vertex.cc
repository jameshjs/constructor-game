#include "vertex.h"

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

bool Vertex::building_exist() const {return building_built;}

void Vertex::place_basement(Colour colour) {
	building_built = true;
	building = Building(colour);
}

void Vertex::improve() {building.improve();}

vector<int>& Vertex::get_neighbour_vertices() {return neighbouring_vertices;}
vector<int>& Vertex::get_neighbour_edges() {return neighbouring_edges;}
vector<int>& Vertex::get_neighbour_tiles() {return neighbouring_tiles;}

Building Vertex::getBuilding() const {return building;}
