#include "resource.h"

Resource translateResource(int i) {
	switch(i) {
		case 0 : return Resource::BRICK;
		case 1 : return Resource::ENERGY;
		case 2 : return Resource::GLASS;
		case 3 : return Resource::HEAT;
		case 4 : return Resource::WIFI;
		case 5 : return Resource::PARK;
	}
	return Resource::PARK;
}

string print_resource(Resource res){
	if(res == Resource::BRICK) return "brick";
	else if(res == Resource::ENERGY) return "energy";
	else if(res == Resource::GLASS) return "glass";
	else if(res == Resource::HEAT) return "heat";
	else if(res == Resource::WIFI) return "wifi";
}
