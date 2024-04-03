#ifndef __DISPLAY_H__
#define __DISPLAY_H__
#include "board.h"
#include <iostream>

class Display {
	public:
	virtual std::ostream& print(ostream& out) = 0;
};

#endif
