#include "creategame.h"
#include <iostream>
using namespace std;

int main() {
	Game g = CreateGame{"save.txt", LoadType::Save}.create();
	g.run_io();
	return 0;
}
