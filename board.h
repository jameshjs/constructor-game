#ifndef __BOARD_H__
#define __BOARD_H__

#include <iostream>
#include <vector>
using namespace std;

enum class Colour {Blue, Red, Orange, Yellow};
enum class Resource {BRICK, ENERGY, GLASS, HEAT, WIFI, PARK};
Resource translateResource(int i);

class Road;
class Building;

// 19 instances
class Tile {
	int tile_number;
	int tile_value; // winning number for dice roll
	bool geese;
	Resource resource; // the resouce type that the tile gives
	
	public:
	Tile(int tile_number, int tile_value, bool geese, Resource resource);
	std::string print_num();
	std::string print_resource();
	std::string print_value();
	std::string print_geese();
};

// 72 instances
class Edge {
	int edge_number;
	Road* road; 
	std::vector<int> neighbouring_edges;
	std::vector<int> neighbouring_vertices;
	
	public:
	Edge(int edge_number, vector<int> neighbouring_edges, vector<int> neighbouring_vertices);
	string print();
};

// 54 instances
class Vertex {
	int vertex_number;
	Building* building;
	std::vector<int> neighbouring_tiles; 
	std::vector<int> neighbouring_edges; 
	std::vector<int> neighbouring_vertices;

	public:
	Vertex(int vertex_number, vector<int> neighbouring_tiles, vector<int> neighbouring_edges, vector<int> neighbouring_vertices);
	std::string print();
};

// 1 instance
class Board {
	public:
	std::vector<Tile> tiles; // 19 tiles in the vector, one for each on the map
	std::vector<Edge> edges; // 72 edges
	std::vector<Vertex> vertices; // 54 vertices
};


#endif
