#include "playertype.h"

HumanPlayer::HumanPlayer(Colour colour) : Player{colour}, fair_dice{true}{}
HumanPlayer::HumanPlayer(Colour colour, int brick, int energy, int glass, int heat, int wifi) : Player{colour, brick, energy, glass, heat, wifi}, fair_dice{true}{}

void HumanPlayer::set_fair_dice(bool state){
	fair_dice = state;
}

bool HumanPlayer::get_fair_dice(){
	return fair_dice;
}

int HumanPlayer::roll_dice(){
	string decision;
    int roll_num;

	while (true) {
		cin >> decision;
		if (decision == "load") set_fair_dice(false);
		if (decision == "fair") set_fair_dice(true);
		if (decision == "roll") {
			if (not get_fair_dice()) {

				cin.exceptions(ios::eofbit|ios::failbit);
				try{
				while (true) {
					if (cin >> roll_num){
						if (roll_num <= 12 && roll_num >=2) break;
					}
					else cout << "Please enter an integer." << endl;
				}
				} catch (const std::ios_base::failure& e){}
				cout << roll_num << " has been rolled." << endl;
				break;
			} else {
				int roll1 = random(1, 6);
				int roll2 = random(1, 6);
				roll_num = roll1 + roll2;
				cout << roll_num << " has been rolled." << endl;
				break;
			}
		}
	}
	return roll_num;
}

ComputerPlayer::ComputerPlayer(Colour colour) : Player{colour}{}
ComputerPlayer::ComputerPlayer(Colour colour, int brick, int energy, int glass, int heat, int wifi) : Player{colour, brick, energy, glass, heat, wifi}{}

int ComputerPlayer::roll_dice(){
	int roll1 = random(1, 6);
	int roll2 = random(1, 6);
	int roll_num = roll1 + roll2;

	cout << roll_num << " has been rolled." << endl;
	return roll_num;
}
