#include "board.h"
using namespace std;

string print_colour(Colour colour) {
	switch(colour) {
		case Colour::Blue : return "B";
		case Colour::Red : return "R";
		case Colour::Orange : return "O";
		case Colour::Yellow : return "Y";
	}
}

string print_Building(BuildingType bui){
    if(bui == BuildingType::Basement) return "basement";
    else if(bui == BuildingType::House) return "house";
    else if(bui == BuildingType::Tower) return "tower";
}

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

string print_resource(Resource res){
    if(res == Resource::BRICK) return "brick";
    else if(res == Resource::ENERGY) return "energy";
    else if(res == Resource::GLASS) return "glass";
    else if(res == Resource::HEAT) return "heat";
    else if(res == Resource::WIFI) return "wifi";
}

Tile::Tile(int tile_number, int tile_value, bool geese, Resource resource) :
	tile_number{tile_number}, tile_value{tile_value}, geese{geese}, resource{resource} {}

Edge::Edge(int edge_number, vector<int> neighbouring_edges, vector<int> neighbouring_vertices) :
	edge_number{edge_number}, road_built{false}, neighbouring_edges{std::move(neighbouring_edges)}, neighbouring_vertices{std::move(neighbouring_vertices)} {}
bool Edge::road_exist(){return road_built;}
Road Edge::getRoad(){return road;}
vector<int> Edge::get_neighbour_vertices(){return neighbouring_vertices;}
vector<int> Edge::get_neighbour_edges(){return neighbouring_edges;}
void Edge::add_road_exist(bool status){road_built = status;};

Vertex::Vertex(int vertex_number, vector<int> neighbouring_tiles, vector<int> neighbouring_edges, vector<int> neighbouring_vertices) :
	vertex_number{vertex_number}, building_built{false}, neighbouring_tiles{neighbouring_tiles}, neighbouring_edges{neighbouring_edges}, neighbouring_vertices{neighbouring_vertices} {}
bool Vertex::building_exist(){return building_built;}
void Vertex::add_building_exist(bool status){building_built = status;}
vector<int> Vertex::get_neighbour_vertices(){return neighbouring_vertices;}
vector<int> Vertex::get_neighbour_edges(){return neighbouring_edges;}
Building Vertex::getBuilding(){return building;}

Road::Road(){}
Road::Road(Colour colour) : colour(colour){}

Building::Building(){}
Building::Building(Colour colour, BuildingType type):colour(colour), type(type){}
BuildingType Building::getType(){return type;}
Colour Building::getColour(){return colour;}

Board::Board(){}
Board::Board(vector<Tile> tiles, vector<Edge> edges, vector<Vertex> vertices) :
	tiles{tiles}, edges{edges}, vertices{vertices} {}
bool Board::can_i_build_initial(int vertex_number, Colour colour){
	if (vertices[vertex_number].building_exist() == true){
		return false;
	}
	for (int item : vertices[vertex_number].get_neighbour_vertices()){
		if (vertices[item].building_exist() == true){
			return false;
		}
	}
	return false;
}
bool Board::can_i_build(int vertex_number, Colour colour){
	if (vertices[vertex_number].building_exist() == true){
		return false;
	}
	for (int item : vertices[vertex_number].get_neighbour_vertices()){
		if (vertices[item].building_exist() == true){
			return false;
		}
	}
	for (int item: vertices[vertex_number].get_neighbour_edges()){
		if (edges[item].road_exist() == true){
			if (edges[item].getRoad().getColour() == colour)
				return true;
		}
	}
	return false;
}

bool Board::can_i_build_road(int edge_number, Colour colour){
		//if there's adjacent road
		//if there's adjacent residence
		if (edges[edge_number].road_exist() == true){
			return false;
		}
		for (int item : edges[edge_number].get_neighbour_vertices()){
			if (vertices[item].building_exist() == true){
				if (vertices[item].getBuilding().getColour() == colour)
					return true;
			}
		}
		for (int item: edges[edge_number].get_neighbour_edges()){
			if (edges[item].road_exist() == true){
				if (edges[item].getRoad().getColour() == colour)
					return true;
			}
		}
		return false;
	}

string Road::print() const {
	return print_colour(colour) + "R"; 
}
Colour Road::getColour(){return colour;}
 
string Building::print() const {
	switch(type) {
		case BuildingType::Basement : return print_colour(colour) + "B";
		case BuildingType::House : return print_colour(colour) + "H";
		case BuildingType::Tower : return print_colour(colour) + "T";
	}
	return print_colour(colour) + "T";
}

string Vertex::print() const {
	if (building_built) return building.print();
	string padding = (vertex_number < 10) ? " " : "";
	return padding + to_string(vertex_number);
}

string Edge::print() const {
	if (road_built) return road.print();
	string padding = (edge_number < 10) ? " " : "";
	return padding + to_string(edge_number);
}

string Tile::print_num() const {
	string padding = (tile_number < 10) ? " " : "";
	return "  " + padding + to_string(tile_number) + "  ";
}

string Tile::print_resource() const {
	if (resource == Resource::BRICK) return " BRICK";
	if (resource == Resource::ENERGY) return "ENERGY";
	if (resource == Resource::GLASS) return " GLASS";
	if (resource == Resource::HEAT) return " HEAT ";
	if (resource == Resource::WIFI) return " WIFI ";
	return " PARK ";
}

string Tile::print_value() const {
	if (tile_value == 7) return "      ";
	string padding = (tile_value < 10) ? " " : "";
	return "  " + padding + to_string(tile_value) + "  ";
}

string Tile::print_geese() const {
	if (geese) return " GEESE";
	return "      ";
}

string Board::print_edge(int index) const {
	return edges[index].print();
}

string Board::print_vertex(int index) const {
	return vertices[index].print();
}

string Board::print_tile_num(int index) const {
	return tiles[index].print_num();
}

string Board::print_tile_resource(int index) const {
	return tiles[index].print_resource();
}

string Board::print_tile_value(int index) const {
	return tiles[index].print_value();
}

string Board::print_tile_geese(int index) const {
	return tiles[index].print_geese();
}
