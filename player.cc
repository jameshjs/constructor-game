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

map<int, Building> Player::get_buildings() {
	return buildings;
}

void Player::add_building(int index) {
	buildings[index] = Building{colour};
	return;
}

void Player::add_road(int index) {
	roads[index] = Road{colour};
	return;
}

void Player::build_building(int index) {
	buildings[index] = Building{colour};
	brick -= 1;
	energy -= 1;
	glass -= 1;
	return;
}

void Player::build_road(int index) {
	heat -= 1;
	wifi -= 1;
	roads[index] = Road{colour};
	return;
}

void Player::improve(int index) {
	if (buildings[index].getType() == BuildingType::Basement) {
		glass -= 2;
		heat -= 3;
	} else if (buildings[index].getType() == BuildingType::House) {
		brick -= 3;
		energy -= 2;
		glass -= 2;
		wifi -= 1;
		heat -= 2;
	}
	buildings[index].improve();
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

bool Player::can_improve(int index) const {
	if (buildings.count(index) == 0) return false;
	if (buildings.at(index).getType() == BuildingType::Basement) return can_improve_h();
	if (buildings.at(index).getType() == BuildingType::House) return can_improve_t();
	return false;
}

void Player::lost_to_geese() {
	return;
}

void Player::gain_resource(Resource resource, int num) {
	if (resource == Resource::BRICK) brick += num;
	if (resource == Resource::ENERGY) energy += num;
	if (resource == Resource::GLASS) glass += num;
	if (resource == Resource::HEAT) heat += num;
	if (resource == Resource::WIFI) wifi += num;
}

void Player::save_player_data() {}
