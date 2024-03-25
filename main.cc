#include "board.h"
#include "readboard.h"
#include "textdisplay.h"
#include <iostream>
using namespace std;

int main() {
	Board board = ReadBoard().create();
	TextDisplay td{&board};
	board.build_initial(Colour::Blue, 21);
	board.build_initial(Colour::Orange, 3);
	board.build_road(Colour::Orange, 6);
	board.build_building(Colour::Yellow, 11);
	board.build_road(Colour::Orange, 20);
	board.build_road(Colour::Orange, 14);
	board.move_geese(16);
	td.print(cout);
	return 0;
}
