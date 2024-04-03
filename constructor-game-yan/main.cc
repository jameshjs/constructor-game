#include "creategame.h"
#include <iostream>
#include <ctime> // Include for time(nullptr)
#include <string>
#include <cstdlib> // Include for std::atoi
using namespace std;

int main(int argc, char* argv[]) {
	string filename = "layout.txt"; // Default layout file
	LoadType type = LoadType::Random; // Default load type
	uint32_t seed = static_cast<uint32_t>(time(nullptr)); // Use current time as default seed

	// Process command-line arguments
    	for (int i = 1; i < argc; ++i) {
        	string arg = argv[i];
        	if (arg == "-seed") {
            		if (i + 1 < argc && isdigit(argv[i + 1][0])) {
                		seed = static_cast<uint32_t>(atoi(argv[++i]));
            		} else {
                		cerr << "Seed value expected after -seed" << endl;
                		return 1; // Exit if seed value is not provided
            		}
        	} else if (arg == "-load") {
            		if (i + 1 < argc) {
                		filename = argv[++i];
                		type = LoadType::Save;
            		} else {
                		cerr << "Filename expected after -load" << endl;
                		return 1; // Exit if filename is not provided
            		}
        	} else if (arg == "-board") {
            		if (i + 1 < argc) {
                		filename = argv[++i];
                		type = LoadType::Board;
            		} else {
                		cerr << "Filename expected after -board" << endl;
                		return 1; // Exit if filename is not provided
            		}
        	} else if (arg == "-random-board") {
            	// Random board is the default, no additional action needed
        	} else {
            		cerr << "Unknown command-line argument: " << arg << endl;
            		return 1; // Exit on unrecognized argument
        	}
	}
	
	Game g = CreateGame{filename, type, seed}.create(); // Create game with processed arguments
    	g.run_io(); // Run the game in interactive mode

    	return 0;
}
