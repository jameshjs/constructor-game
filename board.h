#ifndef __BOARD_H__
#define __BOARD_H__

#include <iostream>
#include <vector>
#include "colour.h"
#include "tile.h"
#include "edge.h"
#include "vertex.h"
using namespace std;


// 1 instance
class Board {
	vector<Tile> tiles; // 19 tiles in the vector, one for each on the map
	vector<Edge> edges; // 72 edges
	vector<Vertex> vertices; // 54 vertices
	
	public:
	Board(vector<Tile> tiles, vector<Edge> edges, vector<Vertex> vertices);
	
	string print_edge(int index) const;
	string print_vertex(int index) const;
	string print_tile_num(int index) const;
	string print_tile_resource(int index) const;
	string print_tile_value(int index) const;
	string print_tile_geese(int index) const;

	int obtain_resource(int tile, BuildingType type, int roll) const; 
	Resource resource_type(int tile) const;
	vector<int>& get_neighbour_tiles(int vertex);
	bool build_initial(Colour colour, int vertex);
	bool build_building(Colour colour, int vertex);
	void improve_building(int vertex); 
	bool build_road(Colour colour, int edge);
	bool move_geese(int tile);
	string board_save();
};


#endif
