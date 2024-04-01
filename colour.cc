#include "colour.h"

string td_colour(Colour colour) {
	switch(colour) {
		case Colour::Blue : return "B";
		case Colour::Red : return "R";
		case Colour::Orange : return "O";
		case Colour::Yellow : return "Y";
	}
	return "Y";
}

ostream& operator<<(ostream& out, const Colour colour) {
	switch(colour) {
		case Colour::Blue : return out << "Blue";
		case Colour::Red : return out << "Red";
		case Colour::Orange : return out << "Orange";
		case Colour::Yellow : return out << "Yellow";
	}
	return out;
}

Colour operator++(Colour& colour, int) {
	switch(colour) {
		case Colour::Blue : return Colour::Red;
		case Colour::Red : return Colour::Orange;
		case Colour::Orange : return Colour::Yellow;
		case Colour::Yellow : return Colour::Blue;
	}
	return colour;
}

Colour colour_int(int i) {
	if (i == 0) return Colour::Blue;
	if (i == 1) return Colour::Red;
	if (i == 2) return Colour::Orange;
	return Colour::Yellow;
}
