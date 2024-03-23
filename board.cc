#include "board.h"
using namespace std;

Resource translateResource(int i) {
	switch(i) {
		case 0 : return Resource::BRICK;
		case 1 : return Resource::ENERGY;
		case 2 : return Resource::GLASS;
		case 3 : return Resource::HEAT;
		case 4 : return Resource::WIFI;
		case 5 : return Resource::PARK;
	}
	cerr << "translate resource failure, returning park" << endl;
	return Resource::PARK;
}

Tile::Tile(int tile_number, int tile_value, bool geese, Resource resource) :
	tile_number{tile_number}, tile_value{tile_value}, geese{geese}, resource{resource} {}

Edge::Edge(int edge_number, vector<int> neighbouring_edges, vector<int> neighbouring_vertices) :
	edge_number{edge_number}, neighbouring_edges{std::move(neighbouring_edges)}, neighbouring_vertices{std::move(neighbouring_vertices)} {}

Vertex::Vertex(int vertex_number, vector<int> neighbouring_tiles, vector<int> neighbouring_edges, vector<int> neighbouring_vertices) :
	vertex_number{vertex_number}, neighbouring_tiles{neighbouring_tiles}, neighbouring_edges{neighbouring_edges}, neighbouring_vertices{neighbouring_vertices} {}

string Vertex::print() {
	//if (building) return ...;
	string padding = (vertex_number < 10) ? " " : "";
	return padding + to_string(vertex_number);
}

string Edge::print() {
	//if (road) return out << *road;
	string padding = (edge_number < 10) ? " " : "";
	return padding + to_string(edge_number);
}

string Tile::print_num() {
	string padding = (tile_number < 10) ? " " : "";
	return "  " + padding + to_string(tile_number) + "  ";
}

string Tile::print_resource() {
	if (resource == Resource::BRICK) return " BRICK";
	if (resource == Resource::ENERGY) return "ENERGY";
	if (resource == Resource::GLASS) return " GLASS";
	if (resource == Resource::HEAT) return " HEAT ";
	if (resource == Resource::WIFI) return " WIFI ";
	return " PARK ";
}

string Tile::print_value() {
	string padding = (tile_value < 10) ? " " : "";
	return "  " + padding + to_string(tile_value) + "  ";
}

string Tile::print_geese() {
	if (geese) return " GEESE";
	return "      ";
}
