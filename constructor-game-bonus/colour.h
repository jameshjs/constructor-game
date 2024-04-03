#ifndef __COLOUR_H__
#define __COLOUR_H__

#include <iostream>
#include <string>
using namespace std;

enum class Colour {Blue, Red, Orange, Yellow};

string td_colour(Colour colour);
ostream& operator<<(ostream& out, const Colour colour);
Colour operator++(Colour& colour, int);
Colour colour_int(int i);
#endif
