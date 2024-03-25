#include "edge.h"

Road::Road() {}
Road::Road(Colour colour) : colour{colour} {}

string Road::print() const {
	return td_colour(colour) + "R";
}

Colour Road::getColour() const {return colour;}


Edge::Edge(int edge_number, vector<int> neighbouring_edges, vector<int> neighbouring_vertices) :
	edge_number{edge_number}, 
	road_built{false}, 
	neighbouring_edges{std::move(neighbouring_edges)}, 
	neighbouring_vertices{std::move(neighbouring_vertices)} 
	{}

string Edge::print() const {
	if (road_built) return road.print();
	string padding = (edge_number < 10) ? " " : "";
	return padding + to_string(edge_number);
}

vector<int>& Edge::get_neighbour_vertices() {return neighbouring_vertices;}
vector<int>& Edge::get_neighbour_edges() {return neighbouring_edges;}

bool Edge::road_exist() const {
	return road_built;
}

void Edge::place_road(Colour colour) {
	road_built = true;
	road = Road(colour);
}

Road Edge::getRoad() const {return road;}
