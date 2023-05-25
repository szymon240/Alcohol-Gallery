#include "Camera.h"

Camera::Camera() {
	this->position = glm::vec3(0.0f, 1.0f, -5.0f);
	this->dir = glm::vec3(0.0f, 0.0f, 1.0f);
	this->cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);
	speed_x = 0;
	speed_y = 0;
	angle_x = 0;
	angle_y = 0;
}

Camera::Camera(glm::vec3 position, glm::vec3 lookAt, glm::vec3 cameraUp) {
	this->position = position;
	this->dir = lookAt;
	this->cameraUp = cameraUp;
	speed_x = 0;
	speed_y = 0;
	angle_x = 0;
	angle_y = 0;
}

glm::vec3 Camera::update() {
	glm::mat4 Mc = glm::rotate(glm::mat4(1.0f), angle_y, glm::vec3(0, 1, 0));
	Mc = glm::rotate(Mc, angle_x, glm::vec3(1, 0, 0));
	glm::vec4 dir_ = Mc * glm::vec4(0, 0, 1, 0);
	dir = glm::vec3(dir_);
	glm::vec3 mdir = glm::normalize(glm::vec3(dir.x, 0, dir.z));

	return mdir;
}