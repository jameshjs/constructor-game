#ifndef __VERTEX_H__
#define __VERTEX_H__

#include <vector>
#include <string>
#include "building.h"
#include "colour.h"
using namespace std;

// 54 instances
class Vertex {
	int vertex_number;
	Building building;
	bool building_built;
	vector<int> neighbouring_tiles;
	vector<int> neighbouring_edges;
	vector<int> neighbouring_vertices;

	public:
	Vertex(int vertex_number, vector<int> neighbouring_tiles, vector<int> neighbouring_edges, vector<int> neighbouring_vertices); // constructor
	string print() const; // print the vertex number
	vector<int>& get_neighbour_vertices(); // return neighbouring vertices
	vector<int>& get_neighbour_edges();// return neighbouring edges
	vector<int>& get_neighbour_tiles();// return neighbouring tiles
	bool building_exist() const; // returns true if building exist on the vertex
	void place_basement(Colour colour); // place a basement of give color on the vertex
	void improve(); // improve the building on the vertex
	Building getBuilding() const; // return the building type of the building on the vertex
};

#endif
