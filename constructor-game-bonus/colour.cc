#include "colour.h"

string td_colour(Colour colour) {
	if (colour == Colour::Blue) return "B";
	if (colour == Colour::Red) return "R";
	if (colour == Colour::Orange) return "O";
	return "Y";
}

ostream& operator<<(ostream& out, const Colour colour) {
	if (colour == Colour::Blue) return out << "Blue";
	if (colour == Colour::Red) return out << "Red";
	if (colour == Colour::Orange) return out << "Orange";
	return out << "Yellow";
}

Colour operator++(Colour& colour, int) {
	if (colour == Colour::Blue) return Colour::Red;
	if (colour == Colour::Red) return Colour::Orange;
	if (colour == Colour::Orange) return Colour::Yellow;
	return Colour::Blue;
}

Colour colour_int(int i) {
	if (i == 0) return Colour::Blue;
	if (i == 1) return Colour::Red;
	if (i == 2) return Colour::Orange;
	return Colour::Yellow;
}
