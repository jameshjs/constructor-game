#ifndef __GAME_H__
#define __GAME_H__

#include "board.h"
#include "player.h"
#include "readboard.h"
#include "textdisplay.h"
#include <map>
#include <string>
using namespace std;

class Game {
	Board board;
	TextDisplay td;
	map<Colour, Player> players;
	
	void roll_dice(); // unimplemented
	bool build_initial(Colour colour, int vertex);
	bool build_road(Colour colour, int edge); // unimplemented
	bool improve(Colour colour, int vertex); // unimplemented
	void help(); // unimplemented
	void geese(); // unimplemented
	void steal(); // unimplemented
	void trade(Colour c1, Colour c2, Resource r1, Resource r2); // unimplemented
	void save(); // unimplemented

	public:
	Game();
	void game_start(); // unimplemented
	void turn_start(); // unimplemented
	void turn_middle(); // unimplemented
	void run();
};

#endif
