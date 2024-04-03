#include "resource.h"

Resource translateResource(int i) {
	if (i == 0) return Resource::BRICK;
	if (i == 1) return Resource::ENERGY;
	if (i == 2) return Resource::GLASS;
	if (i == 3) return Resource::HEAT;
	if (i == 4) return Resource::WIFI;
	return Resource::PARK;
}

string print_resource(Resource res){
	if(res == Resource::BRICK) return "brick";
	if(res == Resource::ENERGY) return "energy";
	if(res == Resource::GLASS) return "glass";
	if(res == Resource::HEAT) return "heat";
	if(res == Resource::WIFI) return "wifi";
	return "park";
}
