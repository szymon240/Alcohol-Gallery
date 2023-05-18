#include "Camera.h"

Camera::Camera() {
	this->position = glm::vec3(0.0f, 0.0f, 3.0f);
	this->lookAt = glm::vec3(0.0f, 0.0f, 0.0f);
	this->cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);
}

Camera::Camera(glm::vec3 position, glm::vec3 lookAt, glm::vec3 cameraUp) {
	this->position = position;
	this->lookAt = lookAt;
	this->cameraUp = cameraUp;
}
