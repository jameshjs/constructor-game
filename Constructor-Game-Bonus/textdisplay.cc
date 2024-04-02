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
	out << string(26, ' ') << vertex(0) << horizontal_edge(0) << vertex(1) << endl;
	out << string(26, ' ') << edge_filler() << tile_filler() << edge_filler() << endl; 
	out << string(26, ' ') << vertical_edge(1) << tile_num(0) << vertical_edge(2) << endl;
	out << string(26, ' ') << edge_filler() << tile_resource(0) << edge_filler() << endl;
	out << string(16, ' ') << vertex(2) << horizontal_edge(3) << vertex(3) << tile_value(0) << 
		vertex(4) << horizontal_edge(4) << vertex(5) << endl;
	out << string(16, ' ') << edge_filler() << tile_filler() << edge_filler() << tile_geese(0) << 
		edge_filler() << tile_filler() << edge_filler() << endl;
	out << string(16, ' ') << vertical_edge(5) << tile_num(1) << vertical_edge(6) << tile_filler() <<
		vertical_edge(7) << tile_num(2) << vertical_edge(8) << endl;
	out << string(16, ' ') << edge_filler() << tile_resource(1) << edge_filler() << tile_filler() << 
		edge_filler() << tile_resource(2) << edge_filler() << endl;
	out << string(6, ' ') << vertex(6) << horizontal_edge(9) << vertex(7) << tile_value(1) << 
		vertex(8) << horizontal_edge(10) << vertex(9) << tile_value(2) << vertex(10) << 
		horizontal_edge(11) << vertex(11) << endl;
	out << string(6, ' ') << edge_filler() << tile_filler() << edge_filler() << tile_geese(1) << edge_filler() << 
		tile_filler() << edge_filler() << tile_geese(2) << edge_filler() << tile_filler() << 
		edge_filler() << endl;
	out << string(6, ' ') << vertical_edge(12) << tile_num(3) << vertical_edge(13) << tile_filler() << 
		vertical_edge(14) << tile_num(4) << vertical_edge(15) << tile_filler() << vertical_edge(16) << 
		tile_num(5) << vertical_edge(17) << endl;
	out << string(6, ' ') << edge_filler() << tile_resource(3) << edge_filler() << tile_filler() << edge_filler() << 
		tile_resource(4) << edge_filler() << tile_filler() << edge_filler() << tile_resource(5) << 
		edge_filler() << endl;
	out << string(6, ' ') << vertex(12) << tile_value(3) << vertex(13) << horizontal_edge(18) << 
		vertex(14) << tile_value(4) << vertex(15) << horizontal_edge(19) <<  vertex(16) << 
		tile_value(5) << vertex(17) << endl;
	out << string(6, ' ') << edge_filler() << tile_geese(3) << edge_filler() << tile_filler() << edge_filler() << 
		tile_geese(4) << edge_filler() << tile_filler() << edge_filler() << tile_geese(5) << 
		edge_filler() << endl;
	out << string(6, ' ') << vertical_edge(20) << tile_filler() << vertical_edge(21) << tile_num(6) << 
		vertical_edge(22) << tile_filler() << vertical_edge(23) << tile_num(7) << vertical_edge(24) << 
		tile_filler() << vertical_edge(25) << endl;
	out << string(6, ' ') << edge_filler() << tile_filler() << edge_filler() << tile_resource(6) << edge_filler() << 
		tile_filler() << edge_filler() << tile_resource(7) << edge_filler() << tile_filler() << 
		edge_filler() << endl;
	out << string(6, ' ') << vertex(18) << horizontal_edge(26) << vertex(19) << tile_value(6) << 
		vertex(20) << horizontal_edge(27) << vertex(21) << tile_value(7) << vertex(22) << 
		horizontal_edge(28) << vertex(23) << endl;
	out << string(6, ' ') << edge_filler() << tile_filler() << edge_filler() << tile_geese(6) << edge_filler() << 
		tile_filler() << edge_filler() << tile_geese(7) << edge_filler() << tile_filler() << 
		edge_filler() << endl;
	out << string(6, ' ') << vertical_edge(29) << tile_num(8) << vertical_edge(30) << tile_filler() << 
		vertical_edge(31) << tile_num(9) << vertical_edge(32) << tile_filler() << vertical_edge(33) << 
		tile_num(10) << vertical_edge(34) << endl;
	out << string(6, ' ') << edge_filler() << tile_resource(8) << edge_filler() << tile_filler() << edge_filler() << 
		tile_resource(9) << edge_filler() << tile_filler() << edge_filler() << tile_resource(10) << 
		edge_filler() << endl;
	out << string(6, ' ') << vertex(24) << tile_value(8) << vertex(25) << horizontal_edge(35) << 
		vertex(26) << tile_value(9) << vertex(27) << horizontal_edge(36) <<  vertex(28) << 
		tile_value(10) << vertex(29) << endl;
	out << string(6, ' ') << edge_filler() << tile_geese(8) << edge_filler() << tile_filler() << edge_filler() << 
		tile_geese(9) << edge_filler() << tile_filler() << edge_filler() << tile_geese(10) << 
		edge_filler() << endl;
	out << string(6, ' ') << vertical_edge(37) << tile_filler() << vertical_edge(38) << tile_num(11) << 
		vertical_edge(39) << tile_filler() << vertical_edge(40) << tile_num(12) << vertical_edge(41) << 
		tile_filler() << vertical_edge(42) << endl;
	out << string(6, ' ') << edge_filler() << tile_filler() << edge_filler() << tile_resource(11) << edge_filler() << 
		tile_filler() << edge_filler() << tile_resource(12) << edge_filler() << tile_filler() << 
		edge_filler() << endl;
	out << string(6, ' ') << vertex(30) << horizontal_edge(43) << vertex(31) << tile_value(11) << 
		vertex(32) << horizontal_edge(44) << vertex(33) << tile_value(12) << vertex(34) << 
		horizontal_edge(45) << vertex(35) << endl;
	out << string(6, ' ') << edge_filler() << tile_filler() << edge_filler() << tile_geese(11) << edge_filler() << 
		tile_filler() << edge_filler() << tile_geese(12) << edge_filler() << tile_filler() << 
		edge_filler() << endl;
	out << string(6, ' ') << vertical_edge(46) << tile_num(13) << vertical_edge(47) << tile_filler() << 
		vertical_edge(48) << tile_num(14) << vertical_edge(49) << tile_filler() << vertical_edge(50) << 
		tile_num(15) << vertical_edge(51) << endl;
	out << string(6, ' ') << edge_filler() << tile_resource(13) << edge_filler() << tile_filler() << edge_filler() << 
		tile_resource(14) << edge_filler() << tile_filler() << edge_filler() << tile_resource(15) << 
		edge_filler() << endl;
	out << string(6, ' ') << vertex(36) << tile_value(13) << vertex(37) << horizontal_edge(52) << 
		vertex(38) << tile_value(14) << vertex(39) << horizontal_edge(53) <<  vertex(40) << 
		tile_value(15) << vertex(41) << endl;
	out << string(6, ' ') << edge_filler() << tile_geese(13) << edge_filler() << tile_filler() << edge_filler() << 
		tile_geese(14) << edge_filler() << tile_filler() << edge_filler() << tile_geese(15) << 
		edge_filler() << endl;
	out << string(6, ' ') << vertical_edge(54) << tile_filler() << vertical_edge(55) << tile_num(16) << 
		vertical_edge(56) << tile_filler() << vertical_edge(57) << tile_num(17) << vertical_edge(58) << 
		tile_filler() << vertical_edge(59) << endl;
	out << string(6, ' ') << edge_filler() << tile_filler() << edge_filler() << tile_resource(16) << edge_filler() << 
		tile_filler() << edge_filler() << tile_resource(17) << edge_filler() << tile_filler() << 
		edge_filler() << endl;
	out << string(6, ' ') << vertex(42) << horizontal_edge(60) << vertex(43) << tile_value(16) << vertex(44) <<
		horizontal_edge(61) << vertex(45) << tile_value(17) << vertex(46) << horizontal_edge(62) << 
		vertex(47) << endl;
	out << string(16, ' ') << edge_filler() << tile_geese(16) << edge_filler() << tile_filler() << 
		edge_filler() << tile_geese(17) << edge_filler() << endl;
	out << string(16, ' ') << vertical_edge(63) << tile_filler() << vertical_edge(64) << tile_num(18) <<
		vertical_edge(65) << tile_filler() << vertical_edge(66) << endl;
	out << string(16, ' ') << edge_filler() << tile_filler() << edge_filler() << tile_resource(18) << 
		edge_filler() << tile_filler() << edge_filler() << endl;
	out << string(16, ' ') << vertex(48) << horizontal_edge(67) << vertex(49) << tile_value(18) << 
		vertex(50) << horizontal_edge(68) << vertex(51) << endl;
	out << string(26, ' ') << edge_filler() << tile_geese(18) << edge_filler() << endl; 
	out << string(26, ' ') << vertical_edge(69) << tile_filler() << vertical_edge(70) << endl;
	out << string(26, ' ') << edge_filler() << tile_filler() << edge_filler() << endl; 
	out << string(26, ' ') << vertex(52) << horizontal_edge(71) << vertex(53) << endl;
	return out;
}
