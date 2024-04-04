#ifndef __GAME_H__
#define __GAME_H__

#include "board.h"
#include "player.h"
#include "textdisplay.h"
#include "colour.h"
#include "random.h"
#include <map>
#include <set>
#include <stdexcept>
#include <fstream>
#include <sstream>
#include <string>
using namespace std;

class Game {
	Board board;
	TextDisplay td;
	Colour current_player;
	map<Colour, Player> players;
	map<Colour, bool> dice_fair;
	bool start_of_game;
	Random random;
	
	int req_int();
	Colour req_colour();
	Resource req_resource(); 
	bool req_bool(); 

	int roll_dice(); 
	void obtain_resource(int roll); 
	bool build_initial(Colour colour, int vertex);
	bool build_building(Colour colour, int vertex);
	bool build_road(Colour colour, int edge); 
	bool improve(Colour colour, int vertex); 

	void help();
	void geese(); 
	void trade(Colour c2, Resource r1, Resource r2); 

	void game_start(); 
	void turn_start(); 
	void turn_middle(); // returns true if a player won

	public:
	Game(Board b);
	Game(Board b, string filename);
	void run();
	void save(string filename);
};

#endif
