#include "board.h"
#include "readboard.h"
#include "textdisplay.h"
#include <iostream>
using namespace std;

// this is for testing 3
int main() {
	Board board = ReadBoard().create();
	TextDisplay td{&board};
	td.print(cout);
	return 0;
}
