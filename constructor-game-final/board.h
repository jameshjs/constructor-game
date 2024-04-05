#ifndef __BOARD_H__
#define __BOARD_H__

#include <iostream>
#include <vector>
#include "colour.h"
#include "tile.h"
#include "edge.h"
#include "vertex.h"
#include "random.h"
using namespace std;


// 1 instance
class Board {
	vector<Tile> tiles; // 19 tiles in the vector, one for each on the map
	vector<Edge> edges; // 72 edges
	vector<Vertex> vertices; // 54 vertices
	
	public:
	Board(vector<Tile> tiles, vector<Edge> edges, vector<Vertex> vertices); // constructor of the board
	
	// print functions for selected edge, vertex, tile number, tile resource, tile value, and if geese is on a tile
	string print_edge(int index) const;
	string print_vertex(int index) const;
	string print_tile_num(int index) const;
	string print_tile_resource(int index) const;
	string print_tile_value(int index) const;
	string print_tile_geese(int index) const;
	
	int obtain_resource(int tile, BuildingType type, int roll) const; // return the resource with the quantity granted from the buildingtype
	Resource resource_type(int tile) const; // return the resource on the given tile
	vector<int>& get_neighbour_tiles(int vertex); // return the neighbouring tiles of the vertex
	bool build_initial(Colour colour, int vertex); // returns false if the location is not avialable, otherwise place a basement
	bool build_building(Colour colour, int vertex); // returns false if the not available, otherwise build
	bool improve_building(int vertex); // returns false if the building is not avaialable, otherwise improve
	bool build_road(Colour colour, int edge); // returns false if the edge is not available, otherwise place road
	void place_road(Colour colour, int edge); // place the road at the given edge
	bool move_geese(int tile); // move the geese to the certain tile
	string board_save(); // out put the data of the board to the save file
	
	// return the neighbouring vertices of an edge or the neighbouring edges of a vertex
	vector<int>& get_neighbour_vertex(int edge);
	vector<int>& get_neighbour_edge(int vertex);
};


#endif
