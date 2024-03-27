#ifndef __VERTEX_H__
#define __VERTEX_H__

#include <vector>
#include <string>
#include "colour.h"
using namespace std;

enum class BuildingType{Basement, House, Tower};
ostream& operator<<(ostream& out, const BuildingType type);

class Building {
	Colour colour;
	BuildingType type;

	public:
	Building();
	Building(Colour colour);
	string print() const;
	Colour getColour() const;
	BuildingType getType() const;
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
	vector<int>& get_neighbour_vertices();
	vector<int>& get_neighbour_edges();
	bool building_exist() const;
	void place_basement(Colour colour);
	Building getBuilding() const;
};

#endif
