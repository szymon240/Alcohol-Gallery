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

void WorldObject::loadModel(const char* path) {
	tinyObj o;
	read_tiny_obj(path, &o); //"objects/Cubone/modell.obj"
	//this->vertices.clear();
	int s = o.shapes[0].mesh.indices.size();
	for (int i = 0; i < s; i++) {
		tinyobj::index_t p;
		p = o.shapes[0].mesh.indices[i];
		this->vertices.push_back(o.attrib.vertices[p.vertex_index * 3]);
		this->vertices.push_back(o.attrib.vertices[p.vertex_index * 3 + 1]);
		this->vertices.push_back(o.attrib.vertices[p.vertex_index * 3 + 2]);
		this->vertices.push_back(1.0f);
		//printf("%f %f %f %d %d\n", vertices[i], vertices[i+1], vertices[i+2], p.vertex_index, i % 3);
		this->texCoords.push_back(o.attrib.texcoords[p.texcoord_index * 2]);
		this->texCoords.push_back(o.attrib.texcoords[p.texcoord_index * 2 + 1]);
		this->normals.push_back(o.attrib.normals[p.normal_index * 3]);
		this->normals.push_back(o.attrib.normals[p.normal_index * 3 + 1]);
		this->normals.push_back(o.attrib.normals[p.normal_index * 3 + 2]);
		this->normals.push_back(0.0f);
	}
	vertCount = vertices.size() / 3;
}

WorldObject::WorldObject(const char* path) {
	loadModel(path);
	M = glm::mat4(1.0f);
}


WorldObject::WorldObject(const char* path, glm::vec3 startingPos) {
	loadModel(path);
	M = glm::mat4(1.0f);
	M = glm::translate(M, startingPos);
}

void WorldObject::move(glm::vec3 where)
{
	M = glm::translate(M, where);
}

void WorldObject::draw(ShaderProgram* sp) {
	sp->use();

	
	glUniformMatrix4fv(sp->u("M"), 1, false, glm::value_ptr(this->M));

	glEnableVertexAttribArray(sp->a("vertex")); //Enable sending data to the attribute vertex
	glVertexAttribPointer(sp->a("vertex"), 4, GL_FLOAT, false, 0, static_cast<float*>(vertices.data())); //Specify source of the data for the attribute vertex
	glEnableVertexAttribArray(sp->a("mormal")); //Enable sending data to the attribute vertex
	glVertexAttribPointer(sp->a("normal"), 4, GL_FLOAT, false, 0, static_cast<float*>(normals.data())); //Specify source of the data for the attribute vertex
	glUniform4f(sp->u("color"), 0, 1, 0, 1);
	glDrawArrays(GL_TRIANGLES, 0, vertCount);

	glDisableVertexAttribArray(sp->a("vertex"));
	glDisableVertexAttribArray(sp->a("normal"));//Disable sending data to the attribute vertex
}