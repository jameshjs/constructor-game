#include <iostream>
#include "player.h"

// constructor
Player::Player(Colour colour): 
    colour(colour), building_points(0), brick(0), energy(0), glass(0), heat(0), wifi(0), 
    buildings(buildings), roads(roads){}
// destroyer
Player::~Player(){}

// returns the colour of the player in string
// status: done
std::string Player::stringColour(){
    if(colour == Colour::Blue) return "blue";
    else if(colour == Colour::Red) return "red";
    else if(colour == Colour::Orange) return "orange";
    else if(colour == Colour::Yellow) return "yellow";
}

// returns the colour of the player in string
// status: done
std::string Player::stringResource(Resource res){
    if(res == Resource::BRICK) return "brick";
    else if(res == Resource::ENERGY) return "energy";
    else if(res == Resource::GLASS) return "glass";
    else if(res == Resource::HEAT) return "heat";
    else if(res == Resource::WIFI) return "wifi";
}

// returns the building of the player in string
// status: done
std::string Player::stringBuilding(BuildingType bui){
    if(bui == BuildingType::Basement) return "basement";
    else if(bui == BuildingType::House) return "house";
    else if(bui == BuildingType::Tower) return "tower";
}

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
    for (Building item : buildings){
        // print out if it is a basement
        if(item.getType() == BuildingType::Basement) 
            std::cout << "Basement: " << item.getVertex() << std::endl;
        // print out if it is a house
        if(item.getType() == BuildingType::House)
            std::cout << "House: " << item.getVertex() << std::endl;
        // print out if it is a tower
        if(item.getType() == BuildingType::Tower)
            std::cout << "Tower: " << item.getVertex() << std::endl;
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
    std::cout << "Builder " << stringColour() << " gained: \n";
    std::cout << num << " " << stringResource(type) << std::endl;
}

// removing the resources to the current player
// status: done
void Player::geese_remove_resource(Resource type, int num){
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

// returns true if the vertex is connected to the player's road
// status: 
bool Player::on_the_road(int vertex_number, Board board){

}

// set up the initial basement
// status:
bool Player::add_initial_basement(int vertex_number){
    // check availability

    // check if adjacent vertex has residence

    buildings.push_back(Building(vertex_number, this->colour, BuildingType::Basement));
    // print out message of the build
    std::cout << stringColour() << " has built: \n";
    std::cout << vertex_number << " " << stringBuilding(BuildingType::Basement) << "\n";
    return true;
}

// building a residence at the given vertex point
// active_player attempts to build residence at vertex_number, returns true if succeeds and returns false if fails
// status:
bool Player::build_residence(int vertex_number){
    // building basement
    // check availability

     // check if adjacent vertex has residence
     // must be on the road

    
    if(brick >= 1 && energy >= 1 && glass >= 1 && wifi >= 1){
        // substract the resources
        brick --;
        energy --;
        glass --;
        wifi --;
        // add the new basement to the buildigns list
        buildings.push_back(Building(vertex_number, this->colour, BuildingType::Basement));
        // print out message of the build
        std::cout << stringColour() << " has built: \n";
        std::cout << vertex_number << " " << stringBuilding(BuildingType::Basement) << "\n";
        // adding one building point
        building_points++;
        return true;
    } else {
        // if the player does not have enough resource
        std::cout << "You do not have enough resources.\n";
        return false;
    }
} 

// improve the building at given vertext point
// status: done
bool Player::improve_building(int vertex_number){
    for (Building item : buildings){
        if(item.getVertex() == vertex_number){
            // potentially upgrade if it is a basement
            if(item.getType() == BuildingType::Basement){
                // upgrade to house if enough resources
                if(glass >= 2 && heat >= 3){ 
                    // substract the resources
                    glass -= 2;
                    heat -= 3;
                    // upgrade the building to the next level
                    item.upgrade();
                    // print out message of the build
                    std::cout << stringColour() << " has built: \n";
                    std::cout << vertex_number << " " << stringBuilding(BuildingType::House) << "\n";
                    // adding two building points
                    building_points+=2;
                    return true;
                }else{
                    // if the player does not have enough resources
                    std::cout << "You do not have enough resources.\n";
                    return false;
                }    
            }
                std::cout << "Basement: " << item.getVertex() << std::endl;
            // potentially upgrade if it is a house
            if(item.getType() == BuildingType::House){
                // upgrade to tower if enough resources
                if(brick >= 3 && energy >= 2 && glass >= 2 && heat >= 2 && wifi >= 1){
                    // subtract the resources
                    brick -= 3;
                    energy -= 2;
                    glass -= 2;
                    heat -= 2;
                    wifi -= 1;
                    // upgrade the building to the next level
                    item.upgrade();
                    // print out message of the build
                    std::cout << stringColour() << " has built: \n";
                    std::cout << vertex_number << " " << stringBuilding(BuildingType::Tower) << "\n";
                    // adding three building points
                    building_points+=3;
                }else{
                    // if the player does not have enough resources
                    std::cout << "You do not have enough resources.\n";
                    return false;
                }
            }
            // print out if it is a tower
            if(item.getType() == BuildingType::Tower){
                std::cout << "You cannot improve a tower.\n";
                return false;
            }
        }
    }
    // if the player doesn't having a building on this vertex
    std::cout << "You cannot build here.\n";
    return false;
}

// build a road at a given edge number
// status:
bool Player::build_road(int edge_number){
    // check availability

    //if there's adjacent road
    //if there's adjacent residence

    roads.push_back(Road(edge_number, this->colour));

    std::cout << "You do not have enough resrouces.\n";
}

// true if trade agreed, false if declined
// status:
bool Player::request_trade(Colour colour, Resource give, Resource take){

    std::cout << "<colour1> offers <colour2> one <resource1> for one <resource2>.\n";
    std::cout << "Does <colour2> accept this offer?\n";

} // true if trade agreed, false if declined

// resolve the trade if the trade is agreed
// status:
void Player::resolve_trade(Colour colour, Resource give, Resource take){

}

// if trying to place geese at invalid location, call it again to make the player try again
// status:
bool Player::place_geese(){

}
