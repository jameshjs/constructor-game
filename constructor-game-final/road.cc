#include "road.h"

Road::Road() {}
Road::Road(Colour colour) : colour{colour} {}

string Road::print() const {return td_colour(colour) + "R";}

Colour Road::getColour() const {return colour;}
