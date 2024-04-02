#ifndef __CREATEGAME_H__
#define __CREATEGAME_H__
#include "random.h"
#include "factory.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
using namespace std;

enum class LoadType {Save, Board, Random};

class CreateGame : public Factory {
	private:
		Random random;
		std::string filename;
		LoadType type;
		uint32_t seed;

		Board create_board();
	public:
		CreateGame(const std::string filename = "layout.txt", LoadType type = LoadType::Board, uint32_t seed = 362436069);
		Game create() override;
};

#endif
