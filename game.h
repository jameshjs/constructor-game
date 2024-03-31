#ifndef __GAME_H__
#define __GAME_H__

#include "board.h"
#include "player.h"
#include "readboard.h"
#include "textdisplay.h"
#include <map>
#include <set>
#include <string>
using namespace std;

class Game {
	Board board;
	TextDisplay td;
	Colour current_player;
	map<Colour, Player> players;
	int round_number; // the current round #
	
	int req_int(); // get an int from user via cin, keep asking until you get an int // unimplemented
	string req_command();
	Colour req_colour();
	Resource req_resource(); 
	bool req_bool(); 

	int roll_dice(); // unimplemented
	void obtain_resource(int roll); 
	bool build_initial(Colour colour, int vertex);
	bool build_building(Colour colour, int vertex);
	bool build_road(Colour colour, int edge); 
	bool improve(Colour colour, int vertex); 
	void help();
	void geese(); 
	void trade(Colour c2, Resource r1, Resource r2); 
	void save(string filename);

	void game_start(); // unimplemented
	void turn_start(); // unimplemented
	void turn_middle(); // unimplemented

	public:
	Game();
	void run();
};

#endif
