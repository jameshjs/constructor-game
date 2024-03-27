#include "player.h"

Player::Player(Colour colour) : colour{colour}, building_points{0}, brick{0}, energy{0}, glass{0}, heat{0}, wifi{0} {}

ostream& Player::print_resources(ostream& out) {
	out << colour << " has " << building_points << " building points, " << 
		brick << " brick, " <<
		energy << " energy, " <<
		glass << " glass, " <<
		heat << " heat, " <<
		wifi << " WiFi." << endl;
	return out;
}

ostream& Player::print_residences(ostream& out) {
	out << colour << " has built:" << endl;
	for (auto [key, value] : buildings) out << key << " " << value.getType() << endl;
	return out;
}

Colour Player::get_colour() const {
	return colour;
}

void Player::add_building(int index) {
	buildings[index] = Building{colour};
	return;
}

void Player::add_road(int index) {
	roads[index] = Road{colour};
	return;
}

void Player::improve(int index) {
	return;
}

bool Player::can_build_b() const {
	if (brick < 1) return false;
	if (energy < 1) return false;
	if (glass < 1) return false;
	return true;
}

bool Player::can_build_r() const {
	if (heat < 1) return false;
	if (wifi < 1) return false;
	return true;
}

bool Player::can_improve_h() const {
	if (glass < 2) return false;
	if (heat < 3) return false;
	return true;
}

bool Player::can_improve_t() const {
	if (brick < 3) return false;
	if (energy < 2) return false;
	if (glass < 2) return false;
	if (wifi < 1) return false;
	if (heat < 2) return false;
	return true;
}

void Player::lost_to_geese() {
	return;
}

void Player::gain_resource(Resource resource, int num) {}
void Player::lose_resource(Resource resource, int num) {}

void Player::save_player_data() {}
