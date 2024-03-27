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
