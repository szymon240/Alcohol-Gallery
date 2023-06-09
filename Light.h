#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class LightSource
{
public: 
	glm::vec3 position;
	LightSource(glm::vec3 pos){
		this->position = pos;
	}
};

