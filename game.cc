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
	players.at(colour).add_building(vertex);
	return true;
}

bool Game::build_building(Colour colour, int vertex) {
	if (not players.at(colour).can_build_b()) return false;
	if (not board.build_building(colour, vertex)) return false;
	players.at(colour).build_building(vertex);
	return true;
}

bool Game::build_road(Colour colour, int edge) {
	if (not players.at(colour).can_build_r()) return false;
	if (not board.build_road(colour, edge)) return false;
	players.at(colour).build_road(edge);
	return true;
}

void Game::game_start() {
}

void Game::run() {
	build_initial(Colour::Blue, 21);
	build_initial(Colour::Orange, 3);
	build_road(Colour::Orange, 6);
	board.build_building(Colour::Yellow, 11);
	build_road(Colour::Orange, 20);
	build_road(Colour::Orange, 14);
	board.move_geese(16);
	obtain_resource(3);
	obtain_resource(2);
	td.print(cout);
	for (auto& [c, p] : players) p.print_residences(cout);
	for (auto& [c, p] : players) p.print_resources(cout);
}

int Game::roll_dice() {}

void Game::obtain_resource(int roll) {
	for (auto& [c, p] : players) {
		for (auto [v, b] : p.get_buildings()) {
			for (auto t : board.get_neighbour_tiles(v)) 
				p.gain_resource(board.resource_type(t), board.obtain_resource(t, b.getType(), roll));
		}
	}
}

bool Game::improve(Colour colour, int vertex) {
	if (not players.at(colour).can_improve(vertex)) return false;
	board.improve_building(vertex);
	players.at(colour).improve(vertex);
	return true;
}

void help() {}
void geese() {}
void steal() {}
void trade(Colour c1, Colour c2, Resource r1, Resource r2) {}
void save() {}

void turn_start() {}
void turn_middle() {}
