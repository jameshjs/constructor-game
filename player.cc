#include "player.h"

Player::Player(Colour colour) : colour{colour}, building_points{0}, brick{0}, energy{0}, glass{0}, heat{0}, wifi{0} {}

int Player::resource_total() const {
	return brick + energy + glass + heat + wifi;
}

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

bool Player::have_resource(Resource r) const {
	if (r == Resource::BRICK) return brick > 0;
	if (r == Resource::ENERGY) return energy > 0;
	if (r == Resource::GLASS) return glass > 0;
	if (r == Resource::HEAT) return heat > 0;
	if (r == Resource::WIFI) return wifi > 0;
	return false;
}

map<int, Building> Player::get_buildings() {
	return buildings;
}

void Player::add_building(int index) {
	buildings[index] = Building{colour};
	++building_points;
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
	++building_points;
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
	++building_points;
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
	if (resource_total() < 10) return;
	int losses = resource_total() / 2;
	int lost = 0;
	int brick_lost = 0;
	int energy_lost = 0;
	int glass_lost = 0;
	int heat_lost = 0;
	int wifi_lost = 0;
	while (lost != losses) {
		int r = random(1, resource_total());
		if (r <= brick) {
			lose_resource(Resource::BRICK);
			++brick_lost;
		} else if (r <= energy + brick) {
			lose_resource(Resource::ENERGY);
			++energy_lost;
		} else if (r <= glass + energy + brick) {
			lose_resource(Resource::GLASS);
			++glass_lost;
		} else if (r <= heat + glass + energy + brick) {
			lose_resource(Resource::HEAT);
			++heat_lost;
		} else if (r <= wifi + heat + glass + energy + brick) {
			lose_resource(Resource::WIFI);
			++wifi_lost;
		} else {
			cerr << "GEESE LOST RNG IS NOT HAPPY" << endl;
		}
		++lost;
	}

	cout << "Builder " << colour << " loses " << losses << " resources to the geese. They lose:" << endl;
	if (brick_lost > 0) cout << brick_lost << " Brick" << endl;
	if (energy_lost > 0) cout << energy_lost << " Energy" << endl;
	if (glass_lost > 0) cout << glass_lost << " Glass" << endl;
	if (heat_lost > 0) cout << heat_lost << " Heat" << endl;
	if (wifi_lost > 0) cout << wifi_lost << " WiFi" << endl;
}

Resource Player::stolen() {
	int r = random(1, resource_total());
	if (r <= brick) {
		lose_resource(Resource::BRICK);
		return Resource::BRICK;
	} else if (r <= energy + brick) {
		lose_resource(Resource::ENERGY);
		return Resource::ENERGY;
	} else if (r <= glass + energy + brick) {
		lose_resource(Resource::GLASS);
		return Resource::GLASS;
	} else if (r <= heat + glass + energy + brick) {
		lose_resource(Resource::HEAT);
		return Resource::HEAT;
	} else if (r <= wifi + heat + glass + energy + brick) {
		lose_resource(Resource::WIFI);
		return Resource::WIFI;
	} else {
		cerr << "GEESE LOST RNG IS NOT HAPPY" << endl;
	}
}

void Player::gain_resource(Resource resource, int num) {
	if (resource == Resource::BRICK) brick += num;
	if (resource == Resource::ENERGY) energy += num;
	if (resource == Resource::GLASS) glass += num;
	if (resource == Resource::HEAT) heat += num;
	if (resource == Resource::WIFI) wifi += num;
}

void Player::lose_resource(Resource resource) {
	if (resource == Resource::BRICK) --brick;
	if (resource == Resource::ENERGY) --energy;
	if (resource == Resource::GLASS) --glass;
	if (resource == Resource::HEAT) --heat;
	if (resource == Resource::WIFI) --wifi;
}

string Player::save_player_data() {
	string player_data = to_string(brick)+" "+to_string(energy)+" "+to_string(glass)+" "
						+to_string(heat)+" "+to_string(wifi)+" r ";
	for (auto [key, value] : roads) player_data += key + " ";
	player_data += "h ";

	for (auto [key, value] : buildings){
		if (buildings.at(key).getType() == BuildingType::Tower) 
			player_data += key + " T ";
	}
	
	for (auto [key, value] : buildings){
		if (buildings.at(key).getType() == BuildingType::House) 
			player_data += key + " H ";
	} 

	for (auto [key, value] : buildings){
		if (buildings.at(key).getType() == BuildingType::Basement)
			player_data += key + " B ";
	} 

	return player_data;
}

bool Player::isWon(){
	if (building_points >= 10) return true;
	else return false;
}
