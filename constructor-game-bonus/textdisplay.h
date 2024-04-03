#ifndef __TEXTDISPLAY_H__
#define __TEXTDISPLAY_H__
#include "display.h"
#include <fstream>
#include <sstream>
#include <string>
#include <iostream>

class TextDisplay : public Display {
	private:
		Board* board;
		std::string horizontal_edge(int edge_number);
		std::string vertical_edge(int edge_number);
		std::string edge_filler();
		std::string vertex(int vertex_number);
		std::string tile_filler();
		std::string tile_num(int tile_number);
		std::string tile_resource(int tile_number);
		std::string tile_value(int tile_number);
		std::string tile_geese(int tile_number);
	public:
		TextDisplay(Board* board);
		std::ostream& print(std::ostream& out) override;
};

#endif
