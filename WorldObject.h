#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <string>
#include <vector>
#include "constants.h"
#include "shaderprogram.h"
#include "lodepng.h"

enum objectType {FLAT ,SHINE, FLOOR};
/*struct Model {
	std::vector<float> vertices;
	std::vector<float> normals;
	std::vector<float> texCoords;
	int vertCount;
};*/

class WorldObject
{
	void loadModel(const char* path);
	void checkAttributes();
	GLuint readTexture(const char* filename);


public:
	//Model model;
	//constructors
	WorldObject(const char* path, const char* texPath);
	WorldObject(const char* path, glm::vec3 startingPos, const char* texPath);
	WorldObject(const char* path, glm::vec3 startingPos, const char* texPath, int type);
	~WorldObject() {
		glDeleteTextures(1, &tex);
	}
	
	std::string id;
	int drunkenness;
	glm::mat4 M;
	glm::vec3 position;
	GLuint tex;
	GLuint texNormal;
	int type;
	//model data
	std::vector<float> vertices;
	std::vector<float> normals;
	std::vector<float> texCoords;
	int vertCount;
	
	//methods
	glm::vec3 getPosition() const {
		return position;
	}

	void move(glm::vec3 where);
	void setPosition(glm::vec3 where);
	void draw(ShaderProgram* sp);
	std::string getPositionInfo();	
};

