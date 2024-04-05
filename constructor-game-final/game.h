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
	
	//input handling methods for integer, colour, resource and boolean
	int req_int();
	Colour req_colour(); 
	Resource req_resource(); 
	bool req_bool(); 

	int roll_dice(); // roll the dice with two types: fair and load
	void obtain_resource(int roll); // allocate resrouces based on the number from dice roll
					
	bool build_initial(Colour colour, int vertex); // build initial basement, return false if invalid location
	bool build_building(Colour colour, int vertex); // return false if not enough resource or invalid location
	bool build_road(Colour colour, int edge); // returns false if not enough resource of invalid location
	bool improve(Colour colour, int vertex); // returns false if not enough resource

	void help(); // print list of commands
	void geese(); // run the geese mechanism when a seven is rolled
	void trade(Colour c2, Resource r1, Resource r2); 

	void game_start(); // intial placement og basements
	void turn_start(); // the dice roll and resource allocation from the rolled number
	bool turn_middle(); // returns true if a player won

	public:
	Game(Board b); // intialize a new board
	Game(Board b, string filename); // initialize a new board b loading from a savefile
	bool run(); // returns true if play again
	void save(string filename); // save the data of the game into a text file
};

#endif
