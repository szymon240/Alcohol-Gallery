#pragma once

#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <string>
#include <vector>

/*struct Model {
	std::vector<float> vertices;
	std::vector<float> normals;
	std::vector<float> texCoords;
	int vertCount;
};*/

class WorldObject
{
public:
	//Model model;
	glm::mat4 M;
	WorldObject(const char* path);
	std::vector<float> vertices;
	std::vector<float> normals;
	std::vector<float> texCoords;
	int vertCount;
};

