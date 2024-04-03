#ifndef __PLAYERTYPE_H__
#define __PLAYERTYPE_H__

#include "player.h"
using namespace std;

class HumanPlayer : public Player{
	bool fair_dice;
	Random random;

public:
	HumanPlayer(Colour colour);
	HumanPlayer(Colour colour, int brick, int energy, int glass, int heat, int wifi);
	bool get_fair_dice();
	void set_fair_dice(bool state);
	virtual int roll_dice() override;
};

class ComputerPlayer : public Player{
    Random random;

public:
	ComputerPlayer(Colour colour);
	ComputerPlayer(Colour colour, int brick, int energy, int glass, int heat, int wifi);
	virtual int roll_dice() override;
};

#endif
