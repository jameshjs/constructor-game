#include "game.h"
using namespace std;

Game::Game() : board{ReadBoard().create()}, td{TextDisplay{&board}} {
	players.insert(make_pair(Colour::Blue, Player(Colour::Blue)));
	players.insert(make_pair(Colour::Red, Player(Colour::Red)));
	players.insert(make_pair(Colour::Orange, Player(Colour::Orange)));
	players.insert(make_pair(Colour::Yellow, Player(Colour::Yellow)));
}

bool Game::build_initial(Colour colour, int vertex) {
	if (not board.build_initial(colour, vertex)) return false;
	for (auto& [c, p] : players) if (c == colour) p.add_building(vertex);
	return true;
}

void Game::game_start() {
}

void Game::run() {
	build_initial(Colour::Blue, 21);
	build_initial(Colour::Orange, 3);
	board.build_road(Colour::Orange, 6);
	board.build_building(Colour::Yellow, 11);
	board.build_road(Colour::Orange, 20);
	board.build_road(Colour::Orange, 14);
	board.move_geese(16);
	td.print(cout);
	for (auto& [c, p] : players) p.print_residences(cout);
	for (auto& [c, p] : players) p.print_resources(cout);
}

void roll_dice() {}
bool build_road(Colour colour, int edge) {return false;}
bool improve(Colour colour, int vertex) {return false;}
void help() {}
void geese() {}
void steal() {}
void trade(Colour c1, Colour c2, Resource r1, Resource r2) {}
void save() {}

void turn_start() {}
void turn_middle() {}
