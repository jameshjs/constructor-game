#include "readboard.h"
using namespace std;

ReadBoard::ReadBoard(const std::string filename) :
	filename{filename} {}

Board ReadBoard::create() {
	vector<Tile> tiles;
	ifstream ifs{filename};
	int resource_type;
	int value;
	int num = 0;
	while (true) {
		if (not (ifs >> resource_type)) break;
		if (not (ifs >> value)) break;
		bool geese = (value == 7) ? true : false;
		Resource resource = translateResource(resource_type);
		tiles.push_back(Tile(num, value, geese, resource));
		++num;
	}
	
	vector<Edge> edges;
	ifstream ifs_ee{"ee.txt"};
	ifstream ifs_ev{"ev.txt"};
	string line_ee;
	string line_ev;
	num = 0;
	while (getline(ifs_ee, line_ee) and getline(ifs_ev, line_ev)) {
		istringstream iss_ee{line_ee};
		istringstream iss_ev{line_ev};
		vector<int> vec_ee;
		vector<int> vec_ev;
		int ee_num;
		int ev_num;
		while (iss_ee >> ee_num) vec_ee.push_back(ee_num);
		while (iss_ev >> ev_num) vec_ev.push_back(ev_num);
		edges.push_back(Edge(num, vec_ee, vec_ev));
		++num;
	}
	
	vector<Vertex> vertices;
	ifstream ifs_vv{"vv.txt"};
	ifstream ifs_vt{"vt.txt"};
	ifstream ifs_ve{"ve.txt"};
	string line_vv;
	string line_vt;
	string line_ve;
	num = 0;
	while (getline(ifs_vv, line_vv) and getline(ifs_vt, line_vt) and getline(ifs_ve, line_ve)) {
		istringstream iss_vv{line_vv};
		istringstream iss_vt{line_vt};
		istringstream iss_ve{line_ve};
		vector<int> vec_vv;
		vector<int> vec_vt;
		vector<int> vec_ve;
		int vv_num;
		int vt_num;
		int ve_num;
		while (iss_vv >> vv_num) vec_vv.push_back(vv_num);
		while (iss_vt >> vt_num) vec_vt.push_back(vt_num);
		while (iss_ve >> ve_num) vec_ve.push_back(ve_num);
		vertices.push_back(Vertex(num, vec_vt, vec_ve, vec_vv));
		++num;
	}

	return Board(tiles, edges, vertices);
}
