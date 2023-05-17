#include "WorldObject.h"
#define TINYOBJLOADER_IMPLEMENTATION
#include <tiny_obj_loader.h>

#include<iostream>

struct tinyObj
{
	tinyobj::attrib_t                attrib;
	std::vector<tinyobj::shape_t>    shapes;
	std::vector<tinyobj::material_t> materials;
};


static
bool read_tiny_obj(const char* path, tinyObj* o)
{
	std::string err;
	std::string warn;
	return LoadObj(&o->attrib, &o->shapes, &o->materials, &warn, &err, path, 0, false);
}

template<typename T>
void printVector(const std::vector<T>& vec) {
	for (const T& value : vec) {
		std::cout << value << " ";
	}
	std::cout << std::endl;
}


WorldObject::WorldObject(const char* path) {
	tinyObj o;
	read_tiny_obj(path, &o); //"objects/Cubone/modell.obj"
	printVector<float>(o.attrib.vertices);
	//this->vertices.clear();
	int s = o.shapes[0].mesh.indices.size();
	std::cout << o.shapes[0].name << std::endl;
	for (int i = 0; i < s; i++) {
		tinyobj::index_t p;
		p = o.shapes[0].mesh.indices[i];
		this->vertices.push_back(o.attrib.vertices[p.vertex_index * 3]);
		this->vertices.push_back(o.attrib.vertices[p.vertex_index * 3 + 1]);
		this->vertices.push_back(o.attrib.vertices[p.vertex_index * 3 + 2]);		
		printf("%f %f %f %d %d\n", vertices[i], vertices[i+1], vertices[i+2], p.vertex_index, i % 3);
		this->texCoords.push_back(o.attrib.texcoords[p.texcoord_index]);
		this->normals.push_back(o.attrib.normals[p.normal_index]);
	}
	vertCount = vertices.size()/3;
	M = glm::mat4(1.0f);

}