#include <vector>
#include <iostream>
#include <string>

using namespace std;

enum class Resource {BRICK, ENERGY, GLASS, HEAT, WIFI};
enum class Colour {Blue, Red, Orange, Yellow};
enum class BuildingType{Basement, House, Tower};

// 1 instance
class Board {
private:
	vector<Tile> tiles; // 19 tiles in the vector, one for each on the map
	vector<Edge> edges; // 72 edges
	vector<Vertex> vertices; // 54 vertices
public:
	Board();
	~Board();
	void print();

	vector<Tile> getTiles(){return tiles;};
	vector<Edge> getEdges(){return edges;};
	vector<Vertex> getVertices(){return vertices;}
};

// 19 instances
class Tile {
private:
	int tile_number; // could be redundant
	int tile_value; // winning number for dice roll
	bool geese;
	Resource resource; // the resouce type that the tile gives
	// don't think these are needed
	// vector<Edge*> neighbouring_edges; 
	// vector<Vertex*> neighbouring_vertices;
public:
	Tile();
	~Tile();
};

// 72 instances
class Edge {
private:
	int edge_number; // could be redundant
	Road* road; //
	vector<Tile> neighbouring_tiles;
	vector<Edge> neighbouring_edges;
	vector<Vertex> neighbouring_vertices;	
public:
	Edge();
	~Edge();
	bool checkNeighbours();
};

// 54 instances
class Vertex {
private:
	int vertex_number; // could be redundant
	Building building;
	bool building_exist;
	vector<Tile> neighbouring_tiles; 
	vector<Edge> neighbouring_edges;
	vector<Vertex> neighbouring_vertices;
public:
	Vertex();
	~Vertex();
	int getNumber(){return vertex_number;}
	bool is_there_building(){
		return building_exist;
	}
	// returns true of the neighbours have residence, then building cannot be built here
	bool checkResidence(){
		for (Vertex item : neighbouring_vertices){
			if (item.is_there_building() == true){
				return true;
			} else {
				return false;
			}
		}
	};
};

// 4 instances, one for each player
class Player {
private:
	Colour colour; // player colour, cannot be Colour::None
	int building_points; // current number of building points
	int brick; // number of bricks the player currently has
	int energy; // number of energies the player currently has
	int glass;
	int heat;
	int wifi;
	vector<Building> buildings;
	vector<Road> roads;
public:
	Player(Colour colour);
	~Player();
	std::string stringColour();
	std::string stringResource(Resource res);
	std::string stringBuilding(BuildingType bui);
	void print_resources();
	void print_residences();
	void add_resource(Resource type, int num);
	void geese_remove_resource(Resource type, int num);
	bool on_the_road(int vertex_number, Board board); // returns true if the vertex is connected to the player's road
	bool add_initial_basement(int vertex_number);
	bool build_residence(int vertex_number); // active_player attempts to build residence at vertex_number, returns true if succeeds and returns false if fails
	bool improve_building(int vertex_number);
	bool build_road(int edge_number);
	bool request_trade(Colour colour, Resource give, Resource take); // true if trade agreed, false if declined
	void resolve_trade(Colour colour, Resource give, Resource take); // called if trade agreed
	bool place_geese(); // if trying to place geese at invalid location, call it again to make the player try again};
};

// 1 instance for each instance of vertex
class Building {
private:
	int vertex_number;
	Colour colour; // Colour::None if road isn't built. 
	BuildingType building_type;
public:
	Building(int vertex_num, Colour colour, BuildingType type);
	~Building();

	int getVertex();
	BuildingType getType();
	// upgrade the building: basement -> house, house -> tower
	void upgrade();
};

// 1 instance for each instance of edge
class Road {
private:
	int edge_number;
	vector<Edge> neighbouring_edges;
	vector<Vertex> neighbouring_vertices;
	Colour colour; // Colour::None if road isn't built. 
public:
	Road(int edge_num, Colour colour);
	bool check_neighbours(){}
};

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