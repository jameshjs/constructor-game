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

int Game::roll_dice() {
	string decision;
	int roll_num;
	while (true) {
		cin >> decision;
		if (decision == "load") dice_fair.at(current_player) = false;
		if (decision == "fair") dice_fair.at(current_player) = true;
		if (decision == "roll") {
			if (not dice_fair.at(current_player)) {
				cout << "Input a roll between 2 and 12:" << endl;
				roll_num = req_int();
				while (roll_num < 2 or roll_num > 12) {
					cout << "Invalid roll." << endl;
					roll_num = req_int();
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
	if (not players.at(colour).can_improve(vertex)) {
		cout << "You do not have enough resources." << endl;
		return false;
	}
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
	current_player++;
	if (current_player == Colour::Blue) outputFile << "0" << endl;
	if (current_player == Colour::Red) outputFile << "1" << endl;
	if (current_player == Colour::Orange) outputFile << "2" << endl;
	if (current_player == Colour::Yellow) outputFile << "3" << endl;
	for (auto& [c, p] : players) outputFile << p.save_player_data() << endl;
	outputFile << board.board_save() << endl;
}

void Game::run_io() {
	if (start_of_game) game_start();
	while(true){
		for (const auto& [c, p] : players) {
			turn_start();
			bool game_won = turn_middle();
			if (game_won == true) break;
			current_player++;
		}
	}
}

void Game::game_start() {

	// place the building and roads	
	for (const auto& [c, p] : players) {
        	cout << "Builder "<< c << ", where do you want to build a basement?"<< endl;
		while(true){
			int num = req_int();
			if (build_initial(c, num)) break;
		} 
	}
	for (auto it = players.rbegin(); it != players.rend(); ++it) {
		cout << "Builder "<< it->first << ", where do you want to build a basement? "<< endl;
		while(true){
			int num = req_int();
			if (build_initial(it->first, num)) break;
		} 
	}
	start_of_game = false;
	td.print(cout);
}

void Game::turn_start() {
	cout << "Builder " << current_player << "’s turn." <<endl;
	players.at(current_player).print_resources(cout);
	int num = roll_dice();
	if (num == 7) {
		geese();
	} else {
		obtain_resource(num);
	}
}

void Game::turn_middle() {
	string line;
	while(getline(cin, line){
		string command;
		istringstream iss{command};
		iss >> command;
		if(players.at(current_player).isWon() == true){
			cout << "Builder " << current_player << "has won!" << endl;
			return;
		}
		if (command == "board") {
			td.print(cout);
		} else if (command == "status") {
			for (auto& [c, p] : players) p.print_resources(cout);
		} else if (command == "residences") {
			players.at(current_player).print_residences(cout);
		}
		} else if (command == "build-road") {
			iss >> command;
			build_road(current_player, stoi(command));
		} else if (command == "build-res") {
			iss >> command;
			board.build_building(current_player, stoi(command));
		} else if (command == "improve") {
			iss >> command;
			players.at(current_player).improve(stoi(command));
		} else if (command == "trade") {
			Colour trader = req_colour();
			Resource give = req_resource();
			Resource take = req_resource();
			trade(trader, give, take);
		} else if (command == "next") {
			break;
		} else if (command == "save") {
			string filename = req_string();
			save(filename);
		} else if (command == "help") {
			help();
		} else{
			cout << "Invalid command." << endl;
		}
	}
}

int Game::req_loaded_roll() {
	int roll;
	cout << "Input a roll between 2 and 12:" << endl;
	while (true) {
        if (cin >> roll){
			if (roll >=2 and roll <= 12) return roll;
			else cout << "Invalid roll." << endl;
		}
     	else cout << "Please enter an integer." << endl;
    }
}

int Game::req_int(){
        int number;
        while (true) {
                if (cin >> number) {
                        if (number < 0 || number > 19) {  // MAX_TILE_NUMBER = 19
                                cout << "Please enter a number in the valid range (0 to 19)." << endl;
                        } else {
                                return number;
                        }
                } else if (cin.eof()) {
                        // Handle EOF
                        cout << "EOF encountered. Exiting..." << endl;
                        exit(0);
                } else {
                        cout << "Invalid input. Please enter an integer." << endl;
                        cin.clear();  // Clear the error flag
                        cin.ignore();  // Skip to the next line
                }
        }
}

string Game::req_string(){
         string word;
         while (true) {
                if (cin >> word) {
                        return word;
                } else if (cin.eof()) {
                        // Handle EOF
                        cout << "EOF encountered. Exiting..." << endl;
                        exit(0);
                } else {
                        cout << "Invalid input. Please enter a string." << endl;
                        cin.clear();  // Clear the error flag
                        cin.ignore();  // Skip to the next line
                }
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
