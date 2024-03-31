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
	build_initial(Colour::Orange, 6);
	build_road(Colour::Orange, 6);
	board.build_building(Colour::Yellow, 11);
	build_road(Colour::Orange, 20);
	build_road(Colour::Orange, 14);
	board.move_geese(16);
	obtain_resource(3);
	obtain_resource(2);
	players.at(Colour::Red).gain_resource(Resource::WIFI, 11);
	players.at(Colour::Red).gain_resource(Resource::HEAT, 19);
	geese();
	trade(Colour::Red, Resource::BRICK, Resource::WIFI);
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

void Game::help() {
	cout<<"Valid commands:"<<endl<<"board"<<endl<<"status"<<endl<<"residences"<<endl<<"build-road <edge#>"<<endl;
	cout<<"build-res <housing#>"<<endl<<"improve <housing#>"<<endl<<"trade <colour> <give> <take>"<<endl;
	cout<<"next"<<endl<<"save <file>"<<endl<<"help"<<endl;
}

void Game::geese() {
	for (auto& [c, p] : players) p.lost_to_geese();

	cout << "Choose where to place the GEESE." << endl;
	int tile = req_int();
	while (not board.move_geese(tile)) tile = req_int();
	
	set<Colour> can_steal;
	for (auto& [c, p] : players) {
		if (c == current_player) continue;
		if (p.resource_total() == 0) continue;
		for (auto [v, b] : p.get_buildings()) {
			for (auto t : board.get_neighbour_tiles(v)) {
				if (t == tile) can_steal.insert(c);
			}
		}
	}
	if (can_steal.size() == 0) {
		cout << "Builder " << current_player << " has no builders to steal from." << endl;
		return;
	}
	cout << "Builder " << current_player << " can choose to steal from ";
	bool first = true;
	for (auto c : can_steal) {
		if (not first) cout << ", ";
		cout << c;
		first = false;
	}
	cout << "." << endl;
	cout << "Choose a builder to steal from." << endl;
	Colour steal_from = req_colour();
	while (can_steal.count(steal_from) == 0) steal_from = req_colour();
	Resource r = players.at(steal_from).stolen();
	players.at(current_player).gain_resource(r, 1);
	cout << "Builder " << current_player << " steals " << print_resource(r) << " from builder " << steal_from << "." << endl;
}

void Game::trade(Colour c2, Resource r1, Resource r2) {//check resource availability
	if (current_player == c2) return;
	if (not players.at(current_player).have_resource(r1)) return;
	if (not players.at(c2).have_resource(r2)) return;
	cout << current_player << " offers " << c2 << " one " << print_resource(r1) << " for one " << print_resource(r2) << "." << endl;
	cout << "Does " << c2 << " accept this offer?" << endl;
	if (req_bool()) {
		players.at(current_player).gain_resource(r2, 1);
		players.at(current_player).lose_resource(r1);
		players.at(c2).gain_resource(r1, 1);
		players.at(c2).lose_resource(r2);
	}
}

void Game::save(string filename) {
    std::ofstream outputFile(filename);

	outputFile<<round_number<<endl;
	for (auto& [c, p] : players) outputFile<<p.save_player_data()<<endl;
	outputFile<<board.board_save()<<endl;
	

}

void turn_start() {}
void turn_middle() {}

int Game::req_int() {
	return 0;
}

int Game::req_int(){
	int number;
    while (true) {
        if (cin >> number) return number;
     	else cout << "Please enter an integer." << endl;
    }
}

string Game::req_command(){
	string comm;
    while (true) {
        if (cin >> comm){
			if(comm=="board" or comm=="status" or comm=="residences" or comm=="build-road" 
			 or comm=="buid-res" or comm=="improve" or comm=="trade" or comm=="next"
			 or comm=="save" or comm=="help"){
				return comm;
			 }
			else std::cout << "Invalid command, please enter again." << std::endl;
		}
     	else cout << "Please enter a string." << endl;
    }
}

Colour Game::req_colour() {
	string tmp;
	while (cout << ">" and cin >> tmp) {
		if (tmp == "Blue") return Colour::Blue;
		if (tmp == "Orange") return Colour::Orange;
		if (tmp == "Red") return Colour::Red;
		if (tmp == "Yellow") return Colour::Yellow;
	}
	return Colour::Blue;
}

bool Game::req_bool() {
	return true;
}

Resource Game::req_resource(){
	string res;
    while (true) {
        if (cin >> res){
			if(res == "brick") return Resource::BRICK;
			else if(res == "energy") return Resource::ENERGY;
			else if(res == "glass")return Resource::GLASS;
			else if(res == "heat")return Resource::HEAT;
			else if(res == "wifi")return Resource::WIFI;
			else std::cout << "Invalid resource, please enter again." << std::endl;
		} 
     	else cout << "Please enter a string." << endl;
    }
	return Resource::BRICK;
}