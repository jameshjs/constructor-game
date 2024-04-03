#ifndef __EDGE_H__
#define __EDGE_H__

#include <vector>
#include <string>
#include "colour.h"
using namespace std;

class Road {
	Colour colour;
	
	public:
	Road();
	Road(Colour colour);
	string print() const;
	Colour getColour() const;
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
	vector<int>& get_neighbour_vertices();
	vector<int>& get_neighbour_edges();
	bool road_exist() const;
	void place_road(Colour colour);
	Road getRoad() const;
};

#endif
