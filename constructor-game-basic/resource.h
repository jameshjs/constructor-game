#ifndef __RESOURCE_H__
#define __RESOURCE_H__

#include <string>
using namespace std;

enum class Resource {BRICK, ENERGY, GLASS, HEAT, WIFI, PARK};
Resource translateResource(int i);
string print_resource(Resource res);

#endif
