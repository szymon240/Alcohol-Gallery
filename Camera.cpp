#include "Camera.h"

Camera::Camera() {
	this->position = glm::vec3(0.0f, 4.0f, -5.0f);
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

Player::Player()
{
	cam = new Camera();
	drunkLevel = 0;
	pos = glm::vec3(0.0f, 0.0f, -5.0f);
	ws = 0;
	goSpeed = 5;
	turnSpeed = 2;
	isDrinking = false;
	wobbly = false;
	wobblyTicks = 0;
}

void Player::left(Player* player)
{
	int random = rand() % 150;
	if (player->drunkLevel <= random) {
		cam->speed_y = turnSpeed;
	} else {
			cam->speed_y = -1*turnSpeed;
	}
}

void Player::turnStop()
{
	cam->speed_y = 0;
}


void Player::right(Player* player)
{	
	int random = rand() % 150;
	if (player->drunkLevel <= random) {
		cam->speed_y = -1*turnSpeed;
	}
	else {
			cam->speed_y = turnSpeed;
	}
}

void Player::forward(Player* player)
{
	int random = rand() % 150;
	if (player->drunkLevel <= random) {
		this->ws = 1 * this->goSpeed;
	}
	else {
		this->ws = -1 * this->goSpeed;
	}
}

void Player::back(Player* player)
{	
	
	int random = rand() % 150;
	if (player->drunkLevel <= random) {
		this->ws = -1 * this->goSpeed;
	}
	else {
		this->ws = 1 * this->goSpeed;
	}
}

void Player::moveStop()
{
	this->ws = 0;
}


void Player::wobble() {
	if (drunkLevel >= 20 && !wobbly) {
		wobblyTicks = 300;
		wobbly = true;
	}
	if (wobblyTicks > 150) {
		cam->speed_x = 0.03;
		
		wobblyTicks--;
	}
	else if (wobblyTicks > 0) {
		cam->speed_x = -0.03;
		wobblyTicks--;
		if (wobblyTicks == 0) { wobbly = false; }
	}
}

void Player::update(double time)
{	
	glm::vec3 newPosition = cam->position + ws * (float)time * cam->update();

	// Check if the new position is within the allowed boundaries
	if (newPosition.x > -7.9f && newPosition.x < 7.9f &&
		newPosition.z > -19.9f && newPosition.z < 29.9f)
	{
		pos = newPosition;
		cam->position = newPosition;
	}
	
	wobble();
	
	cam->angle_x += cam->speed_x * time; 
	cam->angle_y += cam->speed_y * time;
		
}

