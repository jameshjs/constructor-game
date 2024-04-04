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
	Vertex(int vertex_number, vector<int> neighbouring_tiles, vector<int> neighbouring_edges, vector<int> neighbouring_vertices);
	string print() const;
	vector<int>& get_neighbour_vertices();
	vector<int>& get_neighbour_edges();
	vector<int>& get_neighbour_tiles();
	bool building_exist() const;
	void place_basement(Colour colour);
	void improve();
	Building getBuilding() const;
};

#endif
