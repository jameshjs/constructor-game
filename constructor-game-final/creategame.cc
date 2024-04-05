#include "creategame.h"

CreateGame::CreateGame(const string filename, LoadType type, uint32_t seed) : 
	filename{filename}, type{type}, seed{seed} {random.seed(seed);}

Game CreateGame::create() {
	Board b = create_board();
	if (type == LoadType::Save) return Game{b, filename};
	return Game{b};
}

Board CreateGame::create_board() {
	string input;
	if (type == LoadType::Board) {
		ifstream ifs{filename};
		getline(ifs, input);
	} else if (type == LoadType::Save) {
		ifstream ifs{filename};
		for (int i=0; i<6; ++i) getline(ifs, input);
	} else {
		// randomly generate the board layout string as if it was read in
		vector<string> tmp_r;
		for (int i=0; i<3; ++i) tmp_r.push_back("4");
		for (int i=0; i<3; ++i) tmp_r.push_back("3");
		for (int i=0; i<4; ++i) tmp_r.push_back("0");
		for (int i=0; i<4; ++i) tmp_r.push_back("1");
		for (int i=0; i<4; ++i) tmp_r.push_back("2");

		vector<string> tmp_val;
		for (int i=0; i<1; ++i) tmp_val.push_back("2");
		for (int i=0; i<1; ++i) tmp_val.push_back("12");
		for (int i=0; i<2; ++i) tmp_val.push_back("3");
		for (int i=0; i<2; ++i) tmp_val.push_back("4");
		for (int i=0; i<2; ++i) tmp_val.push_back("5");
		for (int i=0; i<2; ++i) tmp_val.push_back("6");
		for (int i=0; i<2; ++i) tmp_val.push_back("8");
		for (int i=0; i<2; ++i) tmp_val.push_back("9");
		for (int i=0; i<2; ++i) tmp_val.push_back("10");
		for (int i=0; i<2; ++i) tmp_val.push_back("11");

		int park = random(0, 18);
		for (int i=18; i>0; --i) {
			if (i == park) input.append("5 7 ");
			int index = random(0, i-1);
			input.append(tmp_r.at(index)+" ");
			tmp_r.erase(tmp_r.begin() + index);
			index = random(0, i-1);
			input.append(tmp_val.at(index)+" ");
			tmp_val.erase(tmp_val.begin() + index);
		}
		if (park == 0) input.append("5 7 ");
	}

	// load in tiles
	vector<Tile> tiles;
	istringstream ifs{input};
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
	
	// load in edges	
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
	
	// load in vertices
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
