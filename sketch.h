#include <vector>
#include <iostream>
#include <string>

using namespace std;

// 1. load the board - ie read from files
// 2. play the turn
// 3. keep track of who wins, start new game, etc
// 4. display the board
// 1 instance. creates the game and runs the loop. if a player wins, end the loop
class Game {
	Board board;
	vector<Player> players;
	Colour active_player; // the colour of the player to make moves
	bool dice_is_fair();
	Game(/*...*/); // constructor calls load_board() or random_board()
	void new_game(); // calls load_board() or random_board()
	void load_board(string filename);
	void random_board();
	void load_game(string filename);
	
	void set_dice_to_fair(); // can be called at beginning of turn
	void set_dice_to_loaded(); // can be called at beginning of turn
	int roll_dice(); // can be called at beginning of turn
	void distribute_resource(int dice_roll); // called after dice is rolled, give players resources
	void steal(Colour colour); // called after geese is placed
	void board(); // prints the board
	void status(); // prints status of all builders
	void next(); // pass turn
	void save(string filename); // save game to file
	void help(); // print list of commands
	void run(); // infinite loop that runs, asking for player to move
};

class wrapper {
	void init_game();
	void play_turn();
	void help();
	void save();
};

int main() {
	while(true) {
		Game game = Game(/*...*/);
		game.run();
		cout << "Would you like to play again?" << endl;
		//...
		// if yes, call constructor on game and run() again, else break and end program
	}
};