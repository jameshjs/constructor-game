#include "tile.h"

Tile::Tile(int tile_number, int tile_value, bool geese, Resource resource) :
	tile_number{tile_number}, tile_value{tile_value}, geese{geese}, resource{resource} {}

string Tile::print_num() const {
	string padding = (tile_number < 10) ? " " : "";
	return "  " + padding + to_string(tile_number) + "  ";
}

string Tile::print_resource() const {
	if (resource == Resource::BRICK) return " BRICK";
	if (resource == Resource::ENERGY) return "ENERGY";
	if (resource == Resource::GLASS) return " GLASS";
	if (resource == Resource::HEAT) return " HEAT ";
	if (resource == Resource::WIFI) return " WIFI ";
	return " PARK ";
}

string Tile::print_value() const {
	if (tile_value == 7) return "      ";
	string padding = (tile_value < 10) ? " " : "";
	return "  " + padding + to_string(tile_value) + "  ";
}

string Tile::print_geese() const {
	if (geese) return " GEESE";
	return "      ";
}

bool Tile::have_geese() const {
	return geese;
}

void Tile::set_geese(bool value) {
	geese = value;
}

int Tile::get_num() const {
	return tile_number;
}

int Tile::get_value() const {
	return tile_value;
}

Resource Tile::get_resource() const {
	return resource;
}
