using namespace std;

enum class Resource {BRICK, ENERGY, GLASS, HEAT, WIFI}
enum class Colour {Blue, Red, Orange, Yellow}

// 1 instance
class Board {
	vector<Tile> tiles; // 19 tiles in the vector, one for each on the map
	vector<Edge> edges; // 72 edges
	vector<Vertex> vertices; // 54 vertices
	void print();
}

// 19 instances
class Tile {
	int tile_number; // could be redundant
	int tile_value; // winning number for dice roll
	bool geese;
	Resource resource; // the resouce type that the tile gives
	// don't think these are needed
	// vector<Edge*> neighbouring_edges; 
	// vector<Vertex*> neighbouring_vertices;

}

// 72 instances
class Edge {
	int edge_number; // could be redundant
	Road* road; //
	vector<int> neighbouring_tiles;
	vector<int> neighbouring_vertices;
	
}

// 54 instances
class Vertex {
	int vertex_number; // could be redundant
	Building* building;
	vector<int> neighbouring_tiles; 
	vector<int> neighbouring_edges; 
}

// 4 instances, one for each player
class Player {
	Colour colour; // player colour, cannot be Colour::None
	int building_points // current number of building points
	int brick; // number of bricks the player currently has
	int energy; // number of energies the player currently has
	int glass;
	int heat;
	int wifi;
	vector<Building> buildings;
	vector<Road> roads;
	void print();
	void print_residences();
}

// 1 instance for each instance of vertex
class Building {
	enum class BuildingType{Basement, House, Tower};
	int vertex_number;
	Colour colour; // Colour::None if road isn't built. 
	BuildingType building_type;
}

// 1 instance for each instance of edge
class Road {
	int edge_number;
	Colour colour; // Colour::None if road isn't built. 
}

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
	Game(...); // constructor calls load_board() or random_board()
	void new_game(); // calls load_board() or random_board()
	void load_board(string filename);
	void random_board();
	void load_game(string filename);
	
	bool build_residence(int vertex_number); // active_player attempts to build residence at vertex_number, returns true if succeeds and returns false if fails
	bool improve_building(int vertex_number);
	bool build_road(int edge_number);
	void set_dice_to_fair(); // can be called at beginning of turn
	void set_dice_to_loaded(); // can be called at beginning of turn
	int roll_dice(); // can be called at beginning of turn
	void distribute_resource(int dice_roll); // called after dice is rolled, give players resources
	bool place_geese(); // if trying to place geese at invalid location, call it again to make the player try again
	void steal(Colour colour); // called after geese is placed
	bool request_trade(Colour colour, Resource give, Resource take); // true if trade agreed, false if declined
	void resolve_trade(Colour colour, Resource give, Resource take); // called if trade agreed
	void board(); // prints the board
	void status(); // prints status of all builders
	void next(); // pass turn
	void save(string filename); // save game to file
	void help(); // print list of commands
	void run(); // infinite loop that runs, asking for player to move
}

class wrapper {
	void init_game();
	void play_turn();
	void help();
	void save();
}

int main() {
	while(true) {
		Game game = Game{...};
		game.run();
		cout << Would you like to play again? << endl;
		...
		// if yes, call constructor on game and run() again, else break and end program
	}
}