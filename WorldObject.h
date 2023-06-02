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


/*struct Model {
	std::vector<float> vertices;
	std::vector<float> normals;
	std::vector<float> texCoords;
	int vertCount;
};*/

class WorldObject
{
	void loadModel(const char* path);
	GLuint readTexture(const char* filename);

public:
	//Model model;
	glm::mat4 M;
	WorldObject(const char* path, const char* texPath);
	WorldObject(const char* path, glm::vec3 startingPos, const char* texPath);
	~WorldObject() {
		glDeleteTextures(1, &tex);
	}
	void move(glm::vec3 where);
	
	std::vector<float> vertices;
	std::vector<float> normals;
	std::vector<float> texCoords;
	int vertCount;
	void draw(ShaderProgram* sp, int i);
	GLuint tex;
};

