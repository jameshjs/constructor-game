#ifndef __FACTORY_H__
#define __FACTORY_H__

#include "game.h"

class Factory {
	public:
		virtual Game create() = 0;
};

#endif
