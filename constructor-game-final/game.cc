#include "game.h"
using namespace std;

Game::Game(Board b) : board{b}, td{TextDisplay{&board}}, current_player{Colour::Blue}, start_of_game{true} {
	Colour c = Colour::Blue;
	players.insert(make_pair(c, Player(c)));
	dice_fair.insert(make_pair(c, false));
	while (c++ != Colour::Blue) {
		players.insert(make_pair(c, Player(c)));
		dice_fair.insert(make_pair(c, false));
	}
}

Game::Game(Board b, string filename) : board{b}, td{TextDisplay{&board}}, start_of_game{false} {
	ifstream ifs{filename};
	string line;
	getline(ifs, line);
	current_player = colour_int(stoi(line));
	for (int i=0; i<4; ++i) {
		getline(ifs, line);
		int r1, r2, r3, r4, r5;
		istringstream iss{line};
		iss >> r1 >> r2 >> r3 >> r4 >> r5;
		players.insert(make_pair(colour_int(i), Player(colour_int(i), r1, r2, r3, r4, r5)));
		dice_fair.insert(make_pair(colour_int(i), false));
		string index, type;
		while (iss >> index) {
			if (index == "r") continue;
			if (index == "h") break;
			players.at(colour_int(i)).add_road(stoi(index));
			board.place_road(colour_int(i), stoi(index));
		}
		while (iss >> index and iss >> type) {
			players.at(colour_int(i)).add_building(stoi(index));
			board.build_initial(colour_int(i), stoi(index));
			if (type == "H") {
				players.at(colour_int(i)).add_improve(stoi(index));
				board.improve_building(stoi(index));	
			} else if (type == "T") {
				players.at(colour_int(i)).add_improve(stoi(index));
				players.at(colour_int(i)).add_improve(stoi(index));
				board.improve_building(stoi(index));
				board.improve_building(stoi(index));
			}
		}
	}
	getline(ifs, line);
	getline(ifs, line);
	board.move_geese(stoi(line));
}

bool Game::build_initial(Colour colour, int vertex) {
	if (not board.build_initial(colour, vertex)) {
		cout << "You cannot build here." << endl;
		return false;
	}
	players.at(colour).add_building(vertex);
	return true;
}

bool Game::build_building(Colour colour, int vertex) {
	if (not players.at(colour).can_build_b()) {
		cout << "You do not have enough resources." << endl;
		return false;
	}
	if (not board.build_building(colour, vertex)) {
		cout << "You cannot build here." << endl;
		return false;
	}
	players.at(colour).build_building(vertex);
	return true;
}

bool Game::build_road(Colour colour, int edge) {
	if (not players.at(colour).can_build_r()) {
		cout << "You do not have enough resources." << endl;
		return false;
	}
	if (not board.build_road(colour, edge)) {
		cout << "You cannot build here." << endl;
		return false;
	}
	players.at(colour).build_road(edge);
	return true;
}

int Game::roll_dice() {
	string decision;
	int roll_num;
	while (true) {
		cout << ">";
		cin >> decision;
		if (decision == "load") dice_fair.at(current_player) = false;
		if (decision == "fair") dice_fair.at(current_player) = true;
		if (decision == "roll") {
			if (not dice_fair.at(current_player)) {
				cout << "Input a roll between 2 and 12:" << endl;
				while (true) {
					try {
						roll_num = req_int();
						if (roll_num >= 2 and roll_num <= 12) break;
						cout << "Invalid roll." << endl;
					} catch (std::logic_error const& ex) {
						cout << "Invalid roll." << endl;
					}
				}
				break;
			} else {
				int roll1 = random(1, 6);
				int roll2 = random(1, 6);
				roll_num = roll1 + roll2;
				break;
			}
		}
	}
	return roll_num;
}

void Game::obtain_resource(int roll) {
	bool gained = false;
	for (auto& [c, p] : players) {
		bool p_gained = false;
		map<Resource, int> gains;
		for (int i=0; i<6; ++i) gains[translateResource(i)] = 0;
		for (auto [v, b] : p.get_buildings()) {
			for (auto t : board.get_neighbour_tiles(v)) gains[board.resource_type(t)] += board.obtain_resource(t, b.getType(), roll);
		}
		for (auto [r, n] : gains) {
			if ((r != Resource::PARK) and (n > 0)) {
				p_gained = true;
				gained = true;
				p.gain_resource(r, n);
			}
		}
		if (p_gained) {
			cout << "Builder " << c << " gained:" << endl;
			for (auto [r, n] : gains) {
				if ((r != Resource::PARK) and (n > 0)) {
					cout << n << " " << print_resource(r) << endl;
				}
			}
		}
	}
	if (not gained) cout << "No builders gained resources." << endl;
}

bool Game::improve(Colour colour, int vertex) {
	if (not players.at(colour).own(vertex)) {
		cout << "You do not have a residence there." << endl;
		return false;
	}
	if (players.at(colour).tower(vertex)) {
		cout << "You cannot improve this residence further." << endl;
		return false;
	}
	if (not players.at(colour).can_improve(vertex)) {
		cout << "You do not have enough resources." << endl;
		return false;
	}
	if (not board.improve_building(vertex)) {
		cout << "You cannot build here." << endl;
		return false;
	}
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
	int tile;
	while (true) {
		try {
			tile = req_int();
			if (board.move_geese(tile)) break;
		} catch (std::logic_error const& ex) {}
	}
	
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
	Colour steal_from;
	while (true) {
		try {
			steal_from = req_colour();
			if (can_steal.count(steal_from) > 0) break;
		} catch (std::logic_error const& ex) {}
	}
	Resource r = players.at(steal_from).stolen();
	players.at(current_player).gain_resource(r, 1);
	cout << "Builder " << current_player << " steals " << print_resource(r) << " from builder " << steal_from << "." << endl;
}

void Game::trade(Colour c2, Resource r1, Resource r2) {//check resource availability
	if (current_player == c2) {
		cout << "You cannot trade with yourself." << endl;
		return;
	}
	if (not players.at(current_player).have_resource(r1)) {
		cout << "You don't have the resource to give." << endl;
		return;
	}
	if (not players.at(c2).have_resource(r2)) {
		cout << c2 << " does not have the resource to trade." << endl;
		return;
	}
	cout << current_player << " offers " << c2 << " one " << print_resource(r1) << " for one " << print_resource(r2) << "." << endl;
	cout << "Does " << c2 << " accept this offer?" << endl;
	bool agreed;
	while (true) {
		try {
			agreed = req_bool();
			break;
		} catch (std::logic_error const& ex) {}
	}
	if (agreed) {
		players.at(current_player).gain_resource(r2, 1);
		players.at(current_player).lose_resource(r1);
		players.at(c2).gain_resource(r1, 1);
		players.at(c2).lose_resource(r2);
	}
}

void Game::save(string filename) {
	if (start_of_game) return; // don't save the game if called during setup phase
	std::ofstream outputFile(filename);
	current_player++;
	if (current_player == Colour::Blue) outputFile << "0" << endl;
	if (current_player == Colour::Red) outputFile << "1" << endl;
	if (current_player == Colour::Orange) outputFile << "2" << endl;
	if (current_player == Colour::Yellow) outputFile << "3" << endl;
	for (auto& [c, p] : players) outputFile << p.save_player_data() << endl;
	outputFile << board.board_save() << endl;
}

bool Game::run() {
	if (start_of_game) game_start();
	while (true) {
		turn_start();
		if (turn_middle()) break;
		current_player++;
	}
	cout << "Would you like to play again?" << endl;
	bool agreed;
	while (true) {
		try {
			agreed = req_bool();
			break;
		} catch (std::logic_error const& ex) {}
	}
	return agreed;
}

void Game::game_start() {

	// place the building and roads	
	for (const auto& [c, p] : players) {
        	cout << "Builder "<< c << ", where do you want to build a basement?"<< endl;
		while(true){
			try {
				int num = req_int();
				if (build_initial(c, num)) break;
			} catch (std::logic_error const& ex) {}
		} 
	}
	for (auto it = players.rbegin(); it != players.rend(); ++it) {
		cout << "Builder "<< it->first << ", where do you want to build a basement? "<< endl;
		while(true){
			try {
				int num = req_int();
				if (build_initial(it->first, num)) break;
			} catch (std::logic_error const& ex) {}
		} 
	}
	start_of_game = false;
}

void Game::turn_start() {
	td.print(cout);
	cout << "Builder " << current_player << "’s turn." <<endl;
	players.at(current_player).print_resources(cout);
	int num = roll_dice();
	if (num == 7) {
		geese();
	} else {
		obtain_resource(num);
	}
}

bool Game::turn_middle() {
	string command;
	while(cout << ">" and cin >> command) {
		try {
			for (auto [c, p] : players) {
				if (p.isWon()) {
					cout << "Builder " << c << " has won!" << endl;
					return true;
				}
			}
			if (command == "board") {
				td.print(cout);
			} else if (command == "status") {
				for (auto& [c, p] : players) p.print_resources(cout);
			} else if (command == "residences") {
				players.at(current_player).print_residences(cout);
			} else if (command == "build-road") {
				build_road(current_player, req_int());
			} else if (command == "build-res") {
				build_building(current_player, req_int());
			} else if (command == "improve") {
				improve(current_player, req_int());
			} else if (command == "trade") {
				Colour trader = req_colour();
				Resource give = req_resource();
				Resource take = req_resource();
				trade(trader, give, take);
			} else if (command == "next") {
				break;
			} else if (command == "save") {
				string filename;
				cin >> filename;
				save(filename);
			} else if (command == "help") {
				help();
			} else{
				throw std::logic_error("");
			}
		}
		catch (std::logic_error const& ex) {
			cout << "Invalid command." << endl;
		}
	}
	return false;
}

Colour Game::req_colour() {
	string s;
	cout << ">";
	cin >> s;
	if (s == "Blue") return Colour::Blue;
	if (s == "Orange") return Colour::Orange;
	if (s == "Red") return Colour::Red;
	if (s == "Yellow") return Colour::Yellow;
	else throw std::logic_error("");
}

bool Game::req_bool() {
	string s;
	cout << ">";
	cin >> s;
	if (s == "yes") return true;
	if (s == "no") return false;
	throw std::logic_error("");
}

Resource Game::req_resource() {
	string s;
	cout << ">";
	cin >> s;
	if (s == "brick") return Resource::BRICK;
	else if (s == "energy") return Resource::ENERGY;
	else if (s == "glass") return Resource::GLASS;
	else if (s == "heat") return Resource::HEAT;
	else if (s == "wifi") return Resource::WIFI;
	else throw std::logic_error("");
}

int Game::req_int() {
	int number;
	cout << ">";
	if (cin >> number) return number;
	cin.clear();  // Clear the error flag
	cin.ignore(256, '\n');  // Skip to the next line
	throw std::logic_error("");
	return number;
}

void Game::enforce_td() {
	td = &board;
}
