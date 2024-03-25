#include <iostream>
#include <string>
#include <fstream>
#include "player.h"

// constructor
Player::Player(Colour colour): 
    colour(colour), building_points(0), brick(0), energy(0), glass(0), heat(0), wifi(0){}

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
void Player::print_residences(Board b){
    // iterate through the list of buildings
    for (int item : buildings){
        // print out if it is a basement
        if(b.getVertices()[item].getBuilding().getType() == BuildingType::Basement) 
            std::cout << "Basement: " << item << std::endl;
        // print out if it is a house
        if(b.getVertices()[item].getBuilding().getType() == BuildingType::House)
            std::cout << "House: " << item << std::endl;
        // print out if it is a tower
        if(b.getVertices()[item].getBuilding().getType() == BuildingType::Tower)
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
    return false;

} // true if trade agreed, false if declined

// resolve the trade if the trade is agreed
// status:
void Player::resolve_trade(Colour colour, Resource give, Resource take){

}

// if trying to place geese at invalid location, call it again to make the player try again
// status:
bool Player::place_geese(){
return false;
}

// output the player data to the document to save file
// status: done
void Player::save_player_data(std::string filename, Board b) {
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
        if(b.getVertices()[item].getBuilding().getType() == BuildingType::Basement) 
            outputFile << item << " B ";
        // print out if it is a house
        if(b.getVertices()[item].getBuilding().getType() == BuildingType::House)
            outputFile << item << " T ";
        // print out if it is a tower
        if(b.getVertices()[item].getBuilding().getType() == BuildingType::Tower)
            outputFile << item << " H ";
    }
    outputFile << std::endl;
}



// building a residence at the given vertex point
// active_player attempts to build residence at vertex_number, returns true if succeeds and returns false if fails
// status: done
bool Player::build_residence(int vertex_number, Board b){
    // building basement
     // check if adjacent vertex has residence
     // must be on the road of the same colour
	if (b.can_i_build(vertex_number, colour) == true){
		if(brick >= 1 && energy >= 1 && glass >= 1 && wifi >= 1){
			// substract the resources
            brick--;
            energy--;
            glass--;
            wifi--;

			// add the new basement to the buildigns list
			buildings.push_back(vertex_number);
			// adding the new building to the vertex
			b.getVertices()[vertex_number].getBuilding() = Building(colour, BuildingType::Basement);
			b.getVertices()[vertex_number].add_building_exist(true);
			// print out message of the build
			std::cout << print_colour(colour) << " has built: " << std::endl;
			std::cout << vertex_number << " Basement" << std::endl;
			// adding one building point
			building_points++;
			return true;
		} else {
			// if the player does not have enough resource
			std::cout << "You do not have enough resources."<< std::endl;
			return false;
		}
	} else{
		// if the player does not have enough resource
		std::cout << "You cannot build here" << std::endl;
		return false;
	}
} 

// set up the initial basement
// status: done
bool Player::add_initial_basement(int vertex_number, Board b){
    // check availability
    if(b.can_i_build_initial(vertex_number, colour) == true){
        // add the new basement to the buildigns list
		buildings.push_back(vertex_number);
		// adding the new building to the vertex
		b.getVertices()[vertex_number].getBuilding() = Building(colour, BuildingType::Basement);
		b.getVertices()[vertex_number].add_building_exist(true);
        // print out message of the build
        std::cout << print_colour(colour) << " has built: "<< std::endl;
        std::cout << vertex_number << " Basement" << std::endl;
        return true;
    } else{
        std::cout << "You cannot build here."<< std::endl;
        return false;
    }
}

// build a road at a given edge number
// status:
bool Player::build_road(int edge_number, Board b){
    // check availability
	if (b.can_i_build_road(edge_number, colour) == true){
		if(heat >= 1 && wifi >= 1){
			// substract the resources
			heat--;
            wifi--;
			// add the new basement to the buildigns list
			roads.push_back(edge_number);
			// adding the new building to the vertex
			b.getEdges()[edge_number].getRoad() = Road(colour);
			b.getEdges()[edge_number].add_road_exist(true);
			// print out message of the build
			std::cout << print_colour(colour) << " has built: "<< std::endl;
			std::cout << edge_number << " " << " road" << std::endl;
			return true;
		} else {
			// if the player does not have enough resource
			std::cout << "You do not have enough resources."<< std::endl;
			return false;
		}
	} else {
        std::cout << "You cannot build here."<< std::endl;
        return false;
    }
}

// build a road at a given edge number
// status:
bool Player::add_initial_road(int edge_number, Board b){
    // check availability
	if (b.can_i_build_road(edge_number, colour) == true){
		// add the new basement to the buildigns list
		roads.push_back(edge_number);
		// adding the new building to the vertex
		b.getEdges()[edge_number].getRoad() = Road(colour);
		b.getEdges()[edge_number].add_road_exist(true);
        // print out message of the build
        std::cout << print_colour(colour) << " has built: "<< std::endl;
        std::cout << edge_number << " road" << std::endl;
        return true;
	} else {
        std::cout << "You cannot build here."<< std::endl;
        return false;
    }
}

// improve the building at given vertext point
// status: done
bool Player::improve_building(int vertex_number, Board b){
    for (int item : buildings){
        if(item == vertex_number){
            // potentially upgrade if it is a basement
            if(b.getVertices()[item].getBuilding().getType() == BuildingType::Basement){
                // upgrade to house if enough resources
                if(glass >= 2 && heat >= 3){ 
                    // substract the resources
					glass-=2;
                    heat-=3;
                    // adding the new building to the vertex
					b.getVertices()[vertex_number].getBuilding() = Building(colour, BuildingType::House);
                    // print out message of the build
                    std::cout << print_colour(colour) << " has built: "<< std::endl;
                    std::cout << vertex_number << " House" << std::endl;
					// adding two building point
                    building_points += 2;
                    return true;
                }else{
                    // if the player does not have enough resources
                    std::cout << "You do not have enough resources." << std::endl;
                    return false;
                }    
            }
            // potentially upgrade if it is a house
            if(b.getVertices()[item].getBuilding().getType() == BuildingType::House){
                // upgrade to tower if enough resources
                if(brick >= 3 && energy >= 2 && glass >= 2 && heat >= 2 && wifi >= 1){
                    // subtract the resources
                    brick -= 3;
                    energy -= 2;
                    glass -= 2;
                    heat -= 2;
                    wifi -= 1;
                    // upgrade the building to the next level
                    b.getVertices()[vertex_number].getBuilding() = Building(colour, BuildingType::Tower);
                    // print out message of the build
                    std::cout << print_colour(colour) << " has built: " << std::endl;
                    std::cout << vertex_number << " Tower" << std::endl;
                    // adding three building points
                    building_points += 3;
					return true;
                }else{
                    // if the player does not have enough resources
                    std::cout << "You do not have enough resources."<< std::endl;
                    return false;
                }
            }
            // print out if it is a tower
            if(b.getVertices()[item].getBuilding().getType() == BuildingType::Tower){
                std::cout << "You cannot improve a tower."<< std::endl;
                return false;
            }
        }
    }
    // if the player doesn't having a building on this vertex
    std::cout << "You cannot build here."<< std::endl;
    return false;
}