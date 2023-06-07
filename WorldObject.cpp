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
	vertCount = vertices.size() / 4;
}

void WorldObject::checkAttributes() {
	std::cout << "Wierzcholki\n";
	for (const auto& number : this->vertices) {
		std::cout << number << " ";
	}
	std::cout << "Textcoords: \n";
	bool t = false;
	for (const auto& number : this->texCoords) {
		std::cout << number << " ";
		if (t) { std::cout << "\n"; t = false; }
		else t = true;
	}
	std::cout << "textura: " << this->tex <<"\n";
	std::cout << "verts: " << vertCount << "\n";
	std::cout << "verts size: " << vertices.size() / 4 << "\n";
	std::cout << "verts normals: " << normals.size() / 4 << "\n";
	std::cout << "verts tex coords: " << texCoords.size() / 2 << "\n";
	
}

WorldObject::WorldObject(const char* path, const char* texPath) {
	loadModel(path);
	position = glm::vec3(0.0f, 0.0f, 0.0f);
	M = glm::mat4(1.0f);
	tex = readTexture(texPath);
	//this->checkAttributes();
	type = 0;
}


WorldObject::WorldObject(const char* path, glm::vec3 startingPos, const char* texPath) {
	loadModel(path);
	M = glm::mat4(1.0f);
	position = glm::vec3(0.0f, 0.0f, 0.0f);
	//M = glm::translate(M, startingPos);
	this->move(startingPos);
	tex = readTexture(texPath);
	type = 0;
	//this->checkAttributes();
}

WorldObject::WorldObject(const char* path, glm::vec3 startingPos, const char* texPath, int type) {
	loadModel(path);
	M = glm::mat4(1.0f);
	position = glm::vec3(0.0f, 0.0f, 0.0f);
	//M = glm::translate(M, startingPos);
	this->move(startingPos);
	tex = readTexture(texPath);
	this->type = type;
	if (type == FLOOR) {
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	//this->checkAttributes();
}

void WorldObject::move(glm::vec3 where)
{
	M = glm::translate(M, where);
	position += where;
}

std::string WorldObject::getPositionInfo() {
	std::string pos = "x:" + std::to_string( position[0]) +" y:" + std::to_string(position[1]) + " z:"+std::to_string(position[2])+ "\n";
	return pos;
}

void WorldObject::draw(ShaderProgram* sp) {
	sp->use();

	glUniformMatrix4fv(sp->u("M"), 1, GL_FALSE, glm::value_ptr(this->M));

	glEnableVertexAttribArray(sp->a("vertex"));
	glVertexAttribPointer(sp->a("vertex"), 4, GL_FLOAT, GL_FALSE, 0, static_cast<const void*>(vertices.data()));

	glEnableVertexAttribArray(sp->a("normal"));
	glVertexAttribPointer(sp->a("normal"), 4, GL_FLOAT, GL_FALSE, 0, static_cast<const void*>(normals.data()));

	glEnableVertexAttribArray(sp->a("texCoord0"));
	glVertexAttribPointer(sp->a("texCoord0"), 2, GL_FLOAT, GL_FALSE, 0, static_cast<const void*>(texCoords.data()));

	glUniform1i(sp->u("textureMap0"), 0); // Set the texture unit index to 0

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, tex);

	switch (type){
	case OBJECT:
		glDrawArrays(GL_TRIANGLES, 0, vertCount);
		break;
	case FLOOR:
		glTexParameteri(GL_TEXTURE_2D,
			GL_TEXTURE_WRAP_S,
			GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D,
			GL_TEXTURE_WRAP_T,
			GL_REPEAT);

		//draw floor
		glDrawArrays(GL_TRIANGLES,vertCount, 16);
	}
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
	//printf("%s", lodepng_error_text(error));
	//printf("%u %u  %u", error,width,height);
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