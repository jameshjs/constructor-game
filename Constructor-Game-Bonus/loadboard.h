#ifndef __READBOARD_H__
#define __READBOARD_H__

#include "board.h"

class LoadBoard {
	public:
		virtual Board create() = 0;
};

#endif
