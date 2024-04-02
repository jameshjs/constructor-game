#include "game.h"
using namespace std;

Game::Game(Board b) : board{b}, td{TextDisplay{&board}}, current_player{Colour::Blue}, start_of_game{true} {
	players.insert(make_pair(Colour::Blue, Player(Colour::Blue)));
	players.insert(make_pair(Colour::Red, Player(Colour::Red)));
	players.insert(make_pair(Colour::Orange, Player(Colour::Orange)));
	players.insert(make_pair(Colour::Yellow, Player(Colour::Yellow)));
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

int Game::roll_dice(Colour colour) {
	string decision;
	int roll_num;
	while (true) {
		cin >> decision;
		if (decision == "load") players.at(colour).set_fair_dice(false);
		if (decision == "fair") players.at(colour).set_fair_dice(true);
		if (decision == "roll") {
			if (not players.at(colour).get_fair_dice()) {
				roll_num = req_int();
				cout << roll_num << " has been rolled." << endl;
				break;
			} else {
				int roll1 = random(1, 6);
				int roll2 = random(1, 6);
				roll_num = roll1 + roll2;
				cout << roll_num << " has been rolled." << endl;
				break;
			}
		}
	}
	return roll_num;
}

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

void Game::computer_geese() {
	for (auto& [c, p] : players) p.lost_to_geese();

	cout << "Choose where to place the GEESE." << endl;
	int tile = board.random_tile();
	while (not board.move_geese(tile)) tile = board.random_tile();
	
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

	Colour steal_from = *can_steal.begin();
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
	for (auto& [c, p] : players) outputFile<<p.save_player_data()<<endl;
	outputFile<<board.board_save()<<endl;
}

void Game::run_io() {
	if (start_of_game) game_start();
	players.at(Colour::Red).set_computer(true);
	players.at(Colour::Orange).set_computer(true);
	players.at(Colour::Yellow).set_computer(true);
	while(true){
		for (const auto& [c, p] : players) {
			bool game_won;
			if(players.at(c).get_computer()==true){
				computer_turn_start(c);
				game_won = computer_turn_middle(c);
			}else{
				turn_start(c);
				game_won = turn_middle(c);
			}
			if (game_won == true) break;
			current_player++;
		}
	}
}

void Game::game_start() {

	// place the building and roads	
    for (const auto& [c, p] : players) {
        cout << "Builder "<< c << ", where do you want to build a basement? "<< endl;
	  if(players.at(current_player).get_computer()==true){
		while(true){
			int num = req_int();
			if(build_initial(c, num) == true) break;
			else cout << "enter a valid location" << endl;
		} 
	  }else{
		while(true){
			int num = board.random_vertex();
			if(build_initial(c, num) == true) break;
		}
	  } 
    }
    for (auto it = players.rbegin(); it != players.rend(); ++it) {
		cout << "Builder "<< it->first << ", where do you want to build a basement? "<< endl;
		if(players.at(current_player).get_computer()==true){
		while(true){
			int num = req_int();
			if(build_initial(it->first, num) == true) break;
			else cout << "enter a valid location" << endl;
		} 
	  	}else{
			while(true){
				int num = board.random_vertex();
				if(build_initial(it->first, num) == true) break;
			}
	  	} 
    }
	start_of_game = false;
}

void Game::computer_turn_start(Colour colour){
    cout << "Builder " << colour << "’s turn. (Computer)" <<endl;
    players.at(colour).print_resources(cout);

    int roll1 = random(1, 6);
    int roll2 = random(1, 6);
    int roll_num = roll1 + roll2;

	cout << roll_num << " has been rolled." << endl;

    if (roll_num == 7){
        computer_geese();
    }else{
        obtain_resource(roll_num);
    }
}
bool Game::computer_turn_middle(Colour colour){
    for (auto [v, b] : players.at(colour).get_buildings()) {
        if(players.at(colour).can_improve(v)){
			players.at(colour).improve(v);
			cout << "A building has been improved at vertex #" << v << endl;
			if(players.at(colour).isWon() == true){
				cout << "Won" << endl;
				return true;
			}
			break;
		}
    }
	if(players.at(colour).can_build_b()){
		for(auto [v, b] : players.at(colour).get_roads()){
			for (int neighbour : board.get_neighbour_vertex(v)) {
				if(build_building(colour, neighbour)==true){
					cout << "A basement has been built at vertex #" << neighbour << endl;
					if(players.at(colour).isWon() == true){
						cout << "Won" << endl;
						return true;
					}
					break;
				}
			}
			break;
		}
	}
	if(players.at(colour).can_build_r()){
		for(auto [v, b] : players.at(colour).get_roads()){
			for (int point : board.get_neighbour_vertex(v)) {
				for (int neighbour : board.get_neighbour_edge(point)) {
					if(build_road(colour, neighbour)==true){
						cout << "A road has been built at vertex #" << neighbour << endl;
					}
					break;
				}
				break;
			}
		}
	}
}

void Game::turn_start(Colour colour) {
	cout << "Builder " << colour << "’s turn." <<endl;
	players.at(colour).print_resources(cout);
	int num = roll_dice(colour);
	if (num == 7){
		geese();
	}else{
		obtain_resource(num);
	}
}

bool Game::turn_middle(Colour colour) {
	string command;
	while(true){
		cout << "Enter you command, type help to see list of commands: " << endl;
		if(cin >> command){
			if (command == "board") {
				td.print(cout);
			} else if (command == "status") {
				for (auto& [c, p] : players) p.print_resources(cout);
				for (auto& [c, p] : players) p.print_residences(cout);
			} else if (command == "residences") {
				players.at(colour).print_residences(cout);
				if(players.at(colour).isWon() == true){
					cout << "Won" << endl;
					return true;
				}
			} else if (command == "build-road") {
				int num = req_int();
				if(build_road(colour, num)==true){
					cout << "A road has been built at vertex #" << num << endl;
				}else{
					cout << "Road cannot be built" << endl;
				}
			} else if (command == "build-res") {
				int num = req_int();
				if(build_building(colour, num)==true){
					cout << "A basement has been built at vertex #" << num << endl;
				}else{
					cout << "Basement cannot be built" << endl;
				}
				// check if the player wins after building basement
				if(players.at(colour).isWon() == true){
					cout << "Won" << endl;
					return true;
				}
			} else if (command == "improve") {
				int num = req_int();
				if(build_building(colour, num)==true){
					cout << "A building has been built improved at vertex #" << num << endl;
				}else{
					cout << "This building cannot be improved" << endl;
				}
				// check if the player wins after improving building
				if(players.at(colour).isWon() == true){
					cout << "Won" << endl;
					return true;
				}
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
				cout << "Invalid command, please enter again." << endl;
			}
		} else{
			cout << "Please enter a string." << endl;
		}
	}
	return false;
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
	cin.exceptions(ios::eofbit|ios::failbit);
    try{
	while (true) {
        if (cin >> number) return number;
     	else cout << "Please enter an integer." << endl;
    }
	} catch (const std::ios_base::failure& e){}
}

string Game::req_string(){
	string word;
	cin.exceptions(ios::eofbit|ios::failbit);
	try{
    while (true) {
        if (cin >> word) return word;
     	else cout << "Please enter an string." << endl;
    }
	} catch (const std::ios_base::failure& e){}
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
