#include "WorldObject.h"

static
bool read_tiny_obj(const char* path, tinyObj* o)
{
	std::string err;
	std::string warn;
	return LoadObj(&o->attrib, &o->shapes, &o->materials, &warn, &err, path, 0, false);
}


WorldObject::WorldObject(char* path) {
	tinyObj o;
	read_tiny_obj("objects/Cubone/modell.obj", &o);
	std::vector<float> vert;

}