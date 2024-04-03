#include "textdisplay.h"
using namespace std;

TextDisplay::TextDisplay(Board* board) : board{board} {}

string TextDisplay::horizontal_edge(int index) {
	return "--" + board->print_edge(index) + "--";
}

string TextDisplay::vertical_edge(int index) {
        return " " + board->print_edge(index) + " ";
}

string TextDisplay::edge_filler() {
	return "  | ";
}

string TextDisplay::vertex(int index) {
	return "|" + board->print_vertex(index) + "|";
}

string TextDisplay::tile_filler() {
	return "      ";
}

string TextDisplay::tile_num(int index) {
	return board->print_tile_num(index);
}

string TextDisplay::tile_resource(int index) {
        return board->print_tile_resource(index);
}

string TextDisplay::tile_value(int index) {
        return board->print_tile_value(index);
}

string TextDisplay::tile_geese(int index) {
        return board->print_tile_geese(index);
}

ostream& TextDisplay::print(ostream& out) {
	ifstream ifs{"display.txt"};
	string line;
	while (getline(ifs, line)) {
		istringstream iss{line};
		string cmd;
		int num;
		while (iss >> cmd >> num) {
			if (cmd == "s") out << string(num, ' ');
			if (cmd == "vx") out << vertex(num);
			if (cmd == "he") out << horizontal_edge(num);
			if (cmd == "tn") out << tile_num(num);
			if (cmd == "ve") out << vertical_edge(num);
			if (cmd == "tg") out << tile_geese(num);
			if (cmd == "tr") out << tile_resource(num);
			if (cmd == "tv") out << tile_value(num);
			if (cmd == "tf") out << tile_filler();
			if (cmd == "ef") out << edge_filler();
		}
		out << endl;
	}
	return out;
}
