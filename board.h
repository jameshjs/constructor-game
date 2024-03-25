#ifndef __BOARD_H__
#define __BOARD_H__

#include <iostream>
#include <vector>
using namespace std;

enum class Colour {Blue, Red, Orange, Yellow};
string print_colour(Colour colour);

enum class BuildingType{Basement, House, Tower};
string print_building(BuildingType bui);

enum class Resource {BRICK, ENERGY, GLASS, HEAT, WIFI, PARK};
Resource translateResource(int i);
string print_resource(Resource res);

class Road {
	Colour colour;
	
	public:
	Road();
	Road(Colour colour);
	string print() const;
	
	Colour getColour();
};

class Building {
	Colour colour;
	BuildingType type;

	public:
	Building();
	Building(Colour colour, BuildingType type);
	string print() const;
	BuildingType getType();
	Colour getColour();
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
	vector<int> get_neighbour_vertices();
	vector<int> get_neighbour_edges();
	bool road_exist();
	Road getRoad();
	void add_road_exist(bool status);
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

	bool building_exist();
	void add_building_exist(bool status);
	vector<int> get_neighbour_vertices();
	vector<int> get_neighbour_edges();
	Building getBuilding();

};

// 1 instance
class Board {
	vector<Tile> tiles; // 19 tiles in the vector, one for each on the map
	vector<Edge> edges; // 72 edges
	vector<Vertex> vertices; // 54 vertices
	
	public:
	Board();
	Board(vector<Tile> tiles, vector<Edge> edges, vector<Vertex> vertices);
	string print_edge(int index) const;
	string print_vertex(int index) const;
	string print_tile_num(int index) const;
	string print_tile_resource(int index) const;
	string print_tile_value(int index) const;
	string print_tile_geese(int index) const;

	vector<Tile> getTiles(){return tiles;}
	vector<Edge> getEdges(){return edges;}
	vector<Vertex> getVertices(){return vertices;}

	bool can_i_build_initial(int vertex_number, Colour colour);
	bool can_i_build(int vertex_number, Colour colour);
	bool can_i_build_road(int edge_number, Colour colour);
};


#endif
