#include "WorldObject.h"
#define TINYOBJLOADER_IMPLEMENTATION
#include <tiny_obj_loader.h>
#include "myCube.h"
#include<iostream>
#include <cmath>

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
		this->texCoords.push_back(std::abs(o.attrib.texcoords[p.texcoord_index * 2]));
		this->texCoords.push_back(std::abs(o.attrib.texcoords[p.texcoord_index * 2 + 1]));
		this->normals.push_back(o.attrib.normals[p.normal_index * 3]);
		this->normals.push_back(o.attrib.normals[p.normal_index * 3 + 1]);
		this->normals.push_back(o.attrib.normals[p.normal_index * 3 + 2]);
		this->normals.push_back(0.0f);
	}
	vertCount = vertices.size() / 3;
}

WorldObject::WorldObject(const char* path, const char* texPath) {
	loadModel(path);
	M = glm::mat4(1.0f);
	tex = readTexture(texPath);
}


WorldObject::WorldObject(const char* path, glm::vec3 startingPos, const char* texPath) {
	loadModel(path);
	M = glm::mat4(1.0f);
	M = glm::translate(M, startingPos);
	tex = readTexture(texPath);
}

void WorldObject::move(glm::vec3 where)
{
	M = glm::translate(M, where);
}

void WorldObject::draw(ShaderProgram* sp,int i) {
	sp->use();
	
	glUniformMatrix4fv(sp->u("M"), 1, false, glm::value_ptr(this->M));

	glEnableVertexAttribArray(sp->a("vertex")); // Enable sending data to the attribute vertex
	glVertexAttribPointer(sp->a("vertex"), 4, GL_FLOAT, false, 0, static_cast<float*>(vertices.data())); // Specify source of the data for the attribute vertex

	glEnableVertexAttribArray(sp->a("normal")); // Enable sending data to the attribute normal
	glVertexAttribPointer(sp->a("normal"), 4, GL_FLOAT, false, 0,static_cast<float*>(normals.data())); // Specify source of the data for the attribute normal

	//glUniform4f(sp->u("color"), 0, 1, 0, 1);

	glEnableVertexAttribArray(sp->a("texCoord0"));  // Enable sending data to the attribute texCoord
	glVertexAttribPointer(sp->a("texCoord0"), 2, GL_FLOAT, false, 0,static_cast<float*>(texCoords.data())); // Specify source of the data for the attribute texCoord

	glUniform1i(sp->u("tex"),i);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, tex);

	glDrawArrays(GL_TRIANGLES, 0,vertCount);

	glDisableVertexAttribArray(sp->a("vertex"));
	glDisableVertexAttribArray(sp->a("normal"));
	glDisableVertexAttribArray(sp->a("texCoord0"));
}


GLuint WorldObject::readTexture(const char* filename) {
	GLuint tex;
	glActiveTexture(GL_TEXTURE0);

	//Wczytanie do pamiêci komputera
	std::vector<unsigned char> image;   //Alokuj wektor do wczytania obrazka
	unsigned width, height;   //Zmienne do których wczytamy wymiary obrazka
	//Wczytaj obrazek
	unsigned error = lodepng::decode(image, width, height, filename);
	printf("%u %u  %u", error,width,height);
	//Import do pamiêci karty graficznej
	glGenTextures(1, &tex); //Zainicjuj jeden uchwyt
	glBindTexture(GL_TEXTURE_2D, tex); //Uaktywnij uchwyt
	//Wczytaj obrazek do pamiêci KG skojarzonej z uchwytem
	glTexImage2D(GL_TEXTURE_2D, 0, 4, width, height, 0,
		GL_RGBA, GL_UNSIGNED_BYTE, (unsigned char*)image.data());

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	return tex;
}