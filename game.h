#ifndef __GAME_H__
#define __GAME_H__

#include "board.h"
#include "player.h"
#include "readboard.h"
#include "textdisplay.h"
#include <vector>
#include <string>
using namespace std;

class Game {
	Board board;
	TextDisplay td;
	vector<Player> players;
	
	bool build_initial(Colour colour, int vertex);

	public:
	Game();
	void game_start();
};

#endif
