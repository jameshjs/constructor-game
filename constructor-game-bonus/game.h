#ifndef __GAME_H__
#define __GAME_H__

#include "board.h"
#include "player.h"
#include "textdisplay.h"
#include "colour.h"
#include "random.h"
#include "playertype.h"
#include <map>
#include <set>
#include <fstream>
#include <sstream>
#include <string>
#include <memory>
using namespace std;

class Game {
	Board board;
	TextDisplay td;
	Colour current_player;
	map<Colour, std::unique_ptr<Player>> players;
	bool start_of_game;
	Random random;
	
	int req_int(); // get an int from user via cin, keep asking until you get an int // unimplemented
	string req_string();
	Colour req_colour();
	Resource req_resource(); 
	bool req_bool(); 

	void obtain_resource(int roll); 
	bool build_initial(Colour colour, int vertex);
	bool build_building(Colour colour, int vertex);
	bool build_road(Colour colour, int edge); 
	bool improve(Colour colour, int vertex); 
	void help();
	void geese(Colour colour); 
	void trade(Colour c2, Resource r1, Resource r2); 
	void save(string filename);

	void game_start(); 
	void turn_start(Colour colour); 
	bool turn_middle(Colour colour); // returns true if a player won

	public:
	Game(Board b);
	Game(Board b, string filename);
	void run_io();
};

#endif