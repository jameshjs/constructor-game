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
	if(res == Resource::ENERGY) return "energy";
	if(res == Resource::GLASS) return "glass";
	if(res == Resource::HEAT) return "heat";
	if(res == Resource::WIFI) return "wifi";
	return "";
}
