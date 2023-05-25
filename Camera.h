#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>

class Camera
{
public:
	glm::vec3 position;
	glm::vec3 dir;
	glm::vec3 cameraUp;
	Camera();
	Camera(glm::vec3 position, glm::vec3 dir, glm::vec3 cameraUp);
	glm::vec3 update();
	float angle_x;
	float angle_y;
	float speed_x;
	float speed_y;
};