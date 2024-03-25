#include "board.h"
using namespace std;

string print_colour(Colour colour) {
	switch(colour) {
		case Colour::Blue : return "B";
		case Colour::Red : return "R";
		case Colour::Orange : return "O";
		case Colour::Yellow : return "Y";
	}
	return "Y";
}

string print_Building(BuildingType bui){
	if (bui == BuildingType::Basement) return "basement";
	else if (bui == BuildingType::House) return "house";
	else if (bui == BuildingType::Tower) return "tower";
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
	return Resource::PARK;
}

string print_resource(Resource res){
	if(res == Resource::BRICK) return "brick";
	else if(res == Resource::ENERGY) return "energy";
	else if(res == Resource::GLASS) return "glass";
	else if(res == Resource::HEAT) return "heat";
	else if(res == Resource::WIFI) return "wifi";
}

Road::Road() {}
Road::Road(Colour colour) : colour{colour} {}

Building::Building() {}
Building::Building(Colour colour) : colour{colour}, type{BuildingType::Basement} {}

Tile::Tile(int tile_number, int tile_value, bool geese, Resource resource) :
	tile_number{tile_number}, tile_value{tile_value}, geese{geese}, resource{resource} {}

Edge::Edge(int edge_number, vector<int> neighbouring_edges, vector<int> neighbouring_vertices) :
	edge_number{edge_number}, road_built{false}, neighbouring_edges{std::move(neighbouring_edges)}, neighbouring_vertices{std::move(neighbouring_vertices)} {}

Vertex::Vertex(int vertex_number, vector<int> neighbouring_tiles, vector<int> neighbouring_edges, vector<int> neighbouring_vertices) :
	vertex_number{vertex_number}, building_built{false}, neighbouring_tiles{neighbouring_tiles}, neighbouring_edges{neighbouring_edges}, neighbouring_vertices{neighbouring_vertices} {}

Board::Board(vector<Tile> tiles, vector<Edge> edges, vector<Vertex> vertices) :
	tiles{tiles}, edges{edges}, vertices{vertices} {}

string Road::print() const {
	return print_colour(colour) + "R"; 
}
 
Colour Road::getColour() const {return colour;}

string Building::print() const {
	switch(type) {
		case BuildingType::Basement : return print_colour(colour) + "B";
		case BuildingType::House : return print_colour(colour) + "H";
		case BuildingType::Tower : return print_colour(colour) + "T";
	}
	return print_colour(colour) + "T";
}

Colour Building::getColour() const {return colour;}

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

vector<int> Vertex::get_neighbour_vertices() const {return neighbouring_vertices;}
vector<int> Vertex::get_neighbour_edges() const {return neighbouring_edges;}

Building Vertex::getBuilding() const {return building;}

string Edge::print() const {
	if (road_built) return road.print();
	string padding = (edge_number < 10) ? " " : "";
	return padding + to_string(edge_number);
}

vector<int> Edge::get_neighbour_vertices() const {return neighbouring_vertices;}
vector<int> Edge::get_neighbour_edges() const {return neighbouring_edges;}

bool Edge::road_exist() const {
	return road_built;
}

void Edge::place_road(Colour colour) {
	road_built = true;
	road = Road(colour);
}

Road Edge::getRoad() const {return road;}

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

bool Tile::have_geese() const {
	return geese;
}

void Tile::set_geese(bool value) {
	geese = value;
	return;
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

bool Board::build_initial(Colour colour, int vertex) {
	if (vertices[vertex].building_exist()) return false;
	vertices[vertex].place_basement(colour);
	return true;
}

bool Board::build_building(Colour colour, int vertex) {
	if (vertices[vertex].building_exist()) return false;
	for (int n_vertex : vertices[vertex].get_neighbour_vertices()) {
		if (vertices[n_vertex].building_exist()) return false;
	}
	for (int n_edge : vertices[vertex].get_neighbour_edges()) {
		if (edges[n_edge].road_exist() and (edges[n_edge].getRoad().getColour() == colour)) {
			vertices[vertex].place_basement(colour);
			return true;
		}
	}
	return false;
}

bool Board::build_road(Colour colour, int edge) {
	if (edges[edge].road_exist()) return false;
	for (int n_vertex : edges[edge].get_neighbour_vertices()) {
		if (vertices[n_vertex].building_exist() and (vertices[n_vertex].getBuilding().getColour() == colour)) {
			edges[edge].place_road(colour);
			return true;
		}
		if (not vertices[n_vertex].building_exist()) {
			for (int n_edge : vertices[n_vertex].get_neighbour_edges()) {
				if (edges[n_edge].road_exist() and (edges[n_edge].getRoad().getColour() == colour)) {
					edges[edge].place_road(colour);
					return true;
				}
			}
		}
	}
	return false;
}

bool Board::move_geese(int tile) {
	if (tiles[tile].have_geese()) return false;
	for (auto& T : tiles) T.set_geese(false);
	tiles[tile].set_geese(true);
	return true;
}
