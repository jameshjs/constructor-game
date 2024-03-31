#include "board.h"
using namespace std;


Board::Board(vector<Tile> tiles, vector<Edge> edges, vector<Vertex> vertices) :
	tiles{tiles}, edges{edges}, vertices{vertices} {}

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

int Board::obtain_resource(int tile, BuildingType type, int roll) const {
	if (tiles[tile].get_value() != roll) return 0;
	if (tiles[tile].have_geese()) return 0;
	if (type == BuildingType::Basement) return 1;
	if (type == BuildingType::House) return 2;
	return 3;
}

Resource Board::resource_type(int tile) const {
	return tiles[tile].get_resource();
}

vector<int>& Board::get_neighbour_tiles(int vertex) {
	return vertices[vertex].get_neighbour_tiles();
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

void Board::improve_building(int vertex) {
	vertices[vertex].improve();
}

string Board::board_save(){
	string save;
	int geese_location;
	for (auto& T : tiles){
		save += T.get_value() + " ";

		if(T.have_geese() == true) geese_location=T.get_value();
		Resource res = T.get_resource();
		if(res == Resource::BRICK) save += 0 + " ";
		else if(res == Resource::ENERGY) save += 1 + " ";
		else if(res == Resource::GLASS) save += 2 + " ";
		else if(res == Resource::HEAT) save += 3 + " ";
		else if(res == Resource::WIFI) save += 4 + " ";
		else if(res == Resource::PARK) save += 5 + " ";
	}
	save += "\ngeese.location";
	return save;
}
