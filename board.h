#ifndef __BOARD_H__
#define __BOARD_H__

#include <iostream>
#include <vector>
using namespace std;

enum class Colour {Blue, Red, Orange, Yellow};
string print_colour(Colour colour);

enum class BuildingType{Basement, House, Tower};

enum class Resource {BRICK, ENERGY, GLASS, HEAT, WIFI, PARK};
Resource translateResource(int i);

class Road {
	Colour colour;
	
	public:
	string print() const;
};

class Building {
	Colour colour;
	BuildingType type;

	public:
	string print() const;
};


// 19 instances
class Tile {
	int tile_number;
	int tile_value; // winning number for dice roll
	bool geese;
	Resource resource; // the resouce type that the tile gives
	
	public:
	Tile(int tile_number, int tile_value, bool geese, Resource resource);
	string print_num() const;
	string print_resource() const;
	string print_value() const;
	string print_geese() const;
};

// 72 instances
class Edge {
	int edge_number;
	Road road;
	bool road_built;
	vector<int> neighbouring_edges;
	vector<int> neighbouring_vertices;
	
	public:
	Edge(int edge_number, vector<int> neighbouring_edges, vector<int> neighbouring_vertices);
	string print() const;
};

// 54 instances
class Vertex {
	int vertex_number;
	Building building;
	bool building_built;
	vector<int> neighbouring_tiles; 
	vector<int> neighbouring_edges; 
	vector<int> neighbouring_vertices;

	public:
	Vertex(int vertex_number, vector<int> neighbouring_tiles, vector<int> neighbouring_edges, vector<int> neighbouring_vertices);
	string print() const;
};

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
};


#endif
