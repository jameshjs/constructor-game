#ifndef __EDGE_H__
#define __EDGE_H__

#include <vector>
#include <string>
#include "road.h"
#include "colour.h"
using namespace std;

// 72 instances
class Edge {
	int edge_number;
	Road road;
	bool road_built;
	vector<int> neighbouring_edges;
	vector<int> neighbouring_vertices;

	public:
	Edge(int edge_number, vector<int> neighbouring_edges, vector<int> neighbouring_vertices); // constructo
	string print() const; // print the edge number
	vector<int>& get_neighbour_vertices(); // return neighbouring vertices
	vector<int>& get_neighbour_edges(); // return neighbouring edges
	bool road_exist() const; // return true if road exists on this edge
	void place_road(Colour colour); // add a road object to the edge with given color
	Road getRoad() const; // return the road object on the edge
};

#endif
