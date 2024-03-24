#include <iostream>
#include <string>
#include <fstream>
#include "player.h"

// constructor
Player::Player(Colour colour): 
    colour(colour), building_points(0), brick(0), energy(0), glass(0), heat(0), wifi(0), 
    buildings(buildings), roads(roads){}
// destroyer
Player::~Player(){}

Colour Player::getColour(){return colour;}
int Player::getBrick(){return brick;}
int Player::getEnergy(){return energy;}
int Player::getGlass(){return glass;}
int Player::getHeat(){return heat;}
int Player::getWifi(){return wifi;}
std::vector<int> Player::getBuildings(){return buildings;}
std::vector<int> Player::getRoads(){return roads;}

void Player::changeBuildingPoint(int num){building_points+=num;}

// print the resources that the current player has
// status: done
void Player::print_resources(){
    std::cout << "Brick: "<< brick << std::endl;
    std::cout << "Energy: "<< energy << std::endl;
    std::cout << "Glass: "<< glass << std::endl;
    std::cout << "Heat: "<< heat << std::endl;
    std::cout << "Wifi: "<< wifi << std::endl;
}

// print the residences that the current player has
// status: done
void Player::print_residences(){
    // iterate through the list of buildings
    for (int item : buildings){
        // print out if it is a basement
        if(item.getType() == BuildingType::Basement) 
            std::cout << "Basement: " << item << std::endl;
        // print out if it is a house
        if(item.getType() == BuildingType::House)
            std::cout << "House: " << item << std::endl;
        // print out if it is a tower
        if(item.getType() == BuildingType::Tower)
            std::cout << "Tower: " << item << std::endl;
    }
}

// adding the resources fo the current player
// status: done
void Player::add_resource(Resource type, int num){
    if (type == Resource::BRICK) brick+=num;
    if (type == Resource::ENERGY) energy+=num;
    if (type == Resource::GLASS) glass+=num;
    if (type == Resource::HEAT) heat+=num;
    if (type == Resource::WIFI) wifi+=num;
    std::cout << "Builder " << print_colour(colour) << " gained: "<< std::endl;
    std::cout << num << " " << print_resource(type) << std::endl;
}

// removing the resources to the current player
// status: done
void Player::remove_resource(Resource type, int num){
    if (type == Resource::BRICK){
        brick-=num;
        if (brick < 0) brick = 0;}
    else if (type == Resource::ENERGY){
        energy-=num;
        if (energy < 0) energy = 0;}
    else if (type == Resource::GLASS){
        glass-=num;
        if (glass < 0) glass = 0;}
    else if (type == Resource::HEAT){
        heat-=num;
        if (heat < 0) heat = 0;}
    else if (type == Resource::WIFI){
        wifi-=num;
        if (heat < 0) heat = 0;}
}

// true if trade agreed, false if declined
// status:
bool Player::request_trade(Colour colour, Resource give, Resource take){

    std::cout << "<colour1> offers <colour2> one <resource1> for one <resource2>."<< std::endl;
    std::cout << "Does <colour2> accept this offer?" << std::endl;

} // true if trade agreed, false if declined

// resolve the trade if the trade is agreed
// status:
void Player::resolve_trade(Colour colour, Resource give, Resource take){

}

// if trying to place geese at invalid location, call it again to make the player try again
// status:
bool Player::place_geese(){

}

// output the player data to the document to save file
// status: done
void Player::save_player_data(std::string filename) {
    // Open a file for writing
    std::ofstream outputFile(filename);
    // output the resources to be saved
    outputFile<<" "<<brick<<" "<<energy<<" "<<glass<<" "<<heat<<" "<<wifi<<" ";
    // output the roads to be saved
    outputFile << "r";
    for (int item : roads){
        outputFile << " " << item;
    }
    // output the buildings to be saved
    outputFile << " h ";
    for (int item : buildings){
        // print out if it is a basement
        if(item.getType() == BuildingType::Basement) 
            outputFile << item << " B ";
        // print out if it is a house
        if(item.getType() == BuildingType::House)
            outputFile << item << " T ";
        // print out if it is a tower
        if(item.getType() == BuildingType::Tower)
            outputFile << item << " H ";
    }
    outputFile << std::endl;
}

