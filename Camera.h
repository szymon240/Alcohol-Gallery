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

class Player
{
	float turnSpeed;
	float goSpeed;
public:
	glm::vec3 getPosition() const {
		return cam->position;
	}
	Player();
	Camera * cam;
	int drunkLevel;
	glm::vec3 pos;
	int ws;
	bool isDrinking;

	void left(Player* player);
	void turnStop();
	void right(Player* player);
	void forward(Player* player);
	void back(Player* player);
	void moveStop();
	void upAndDown(Player* player, bool isMoving);
	void update(double time);
};