#ifndef __LOADBOARD_H__
#define __LOADBOARD_H__
#include "loadboard.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

class ReadBoard : public LoadBoard {
	private:
		std::string filename;
	public:
		ReadBoard(const std::string filename = "layout.txt");
		Board create() override;
};

#endif
