#include "board.h"
#include "readboard.h"
#include "textdisplay.h"
#include <iostream>
using namespace std;

int main() {
	Board board = ReadBoard().create();
	TextDisplay td{&board};
	td.print(cout);
	return 0;
}
