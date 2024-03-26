#include "game.h"
using namespace std;

Game::Game() : board{ReadBoard().create()}, td{TextDisplay{&board}} {
	players.push_back(Colour::Blue);
	players.push_back(Colour::Red);
	players.push_back(Colour::Orange);
	players.push_back(Colour::Yellow);
}

bool Game::build_initial(Colour colour, int vertex) {
	if (not board.build_initial(colour, vertex)) return false;
	for (auto& player : players) if (player.get_colour() == colour) player.add_building(vertex);
	return true;
}

void Game::game_start() {
	for (auto& player : players) {
		// ask for vertex number
	}
}

/*
	board.build_initial(Colour::Blue, 21);
	board.build_initial(Colour::Orange, 3);
	board.build_road(Colour::Orange, 6);
	board.build_building(Colour::Yellow, 11);
	board.build_road(Colour::Orange, 20);
	board.build_road(Colour::Orange, 14);
	board.move_geese(16);
	td.print(cout);
}
*/
