#include "Scene.h"
#include <thread>

Scene::Scene(std::string name)
{
	this->name = name;
}

void Scene::draw(ShaderProgram *sp) {
	
	for (const auto& object : objects){
			object->draw(sp);
			
	}
}

void Scene::printObjectID(Player* player) {
	float minDist = std::numeric_limits<float>::max();
	std::string closestID;
	int drunkenness;
	int index;
	for (int i = 0; i < objects.size(); i++) {
		float dist = glm::length(objects[i]->getPosition() - player->getPosition());
		if (dist < minDist) {
			minDist = dist;
			closestID = objects[i]->id;
			drunkenness = objects[i]->drunkenness;
			index = i;
		}
	}
	if (!closestID.empty()) {
		player->drunkLevel = player->drunkLevel + drunkenness;
		std::cout << player->drunkLevel << std::endl;
		moveBottle(index, player);
	}
}

void Scene::moveBottle(int i, Player* player) {
	if (player->isDrinking == true) return;
	player->isDrinking = true;
	glm::vec3 rotateVector =glm::normalize(glm::cross(objects[i]->position - player->pos , glm::vec3(0.0f,1.0f,0.0f))); //cross product for calculating perpendicular vector
	if (i < 6) {
		objects[i]->M = glm::rotate(objects[i]->M, PI / 4, rotateVector);
	}
	else {
		objects[i]->M = glm::rotate(objects[i]->M, PI / 4, rotateVector);
	}

	// Start a new thread to reverse the rotation after a delay
	std::thread reverseThread([this, i, player,rotateVector]() {
		std::this_thread::sleep_for(std::chrono::seconds(1));  // Delay for 5 seconds
		if (i < 6) {
			objects[i]->M = glm::rotate(objects[i]->M, -PI / 4, rotateVector);
		}
		else {
			objects[i]->M = glm::rotate(objects[i]->M, -PI / 4, rotateVector);
		}  
		player->isDrinking = false;
		});

	reverseThread.detach();
}

void Scene::printPositions() {
	
	for (const auto& object : objects) {
		std::cout << object->getPositionInfo();

	}
}

void Scene::addObject(std::unique_ptr<WorldObject> ob) {
	objects.push_back(std::move(ob));
	this->size = objects.size();
}



void Scene::loadLevel() {
	
	std::unique_ptr<WorldObject> ob = std::make_unique<WorldObject>("objects/potion/potion.obj", glm::vec3(-5.5f, 3.5f, 2.0f), "objects/potion/potion2.png");
	ob->id = "Potionek prawy";
	ob->drunkenness = 5;
	objects.push_back(std::move(ob));

	std::unique_ptr<WorldObject> pedestal = std::make_unique<WorldObject>("objects/pedestal/pedestal.obj", glm::vec3(-5.5f, -1.0f, 2.0f), "objects/pedestal/marmur2.png");
	objects.push_back(std::move(pedestal));

	std::unique_ptr<WorldObject> ob1 = std::make_unique<WorldObject>("objects/butelka/butelka.obj", glm::vec3(-5.5f, 3.0f, -7.0f), "objects/metal.png");
	ob1->id = "Butelka prawa";
	ob1->drunkenness = 3;
	objects.push_back(std::move(ob1));

	std::unique_ptr<WorldObject> pedestal1 = std::make_unique<WorldObject>("objects/pedestal/pedestal.obj", glm::vec3(-5.5f, -1.0f, -7.0f), "objects/pedestal/marmur2.png");
	objects.push_back(std::move(pedestal1));

	std::unique_ptr<WorldObject> ob2 = std::make_unique<WorldObject>("objects/wine/wine.obj", glm::vec3(-5.5f, 3.0f,-3.0f), "objects/metal.png");
	ob2->id = "Wino prawe";
	ob2->drunkenness = 1;
	objects.push_back(std::move(ob2));
	
	std::unique_ptr<WorldObject> pedestal2 = std::make_unique<WorldObject>("objects/pedestal/pedestal.obj", glm::vec3(-5.5f, -1.0f, -3.0f), "objects/pedestal/marmur2.png");
	objects.push_back(std::move(pedestal2));

	std::unique_ptr<WorldObject> ob3 = std::make_unique<WorldObject>("objects/potion/potion.obj", glm::vec3(5.5f, 3.5f, 2.0f), "objects/metal.png");
	ob3->id = "Potionek lewy";
	ob3->drunkenness = 5;
	objects.push_back(std::move(ob3));

	std::unique_ptr<WorldObject> pedestal3 = std::make_unique<WorldObject>("objects/pedestal/pedestal.obj", glm::vec3(5.5f, -1.0f, 2.0f), "objects/pedestal/marmur2.png");
	objects.push_back(std::move(pedestal3));

	std::unique_ptr<WorldObject> ob4 = std::make_unique<WorldObject>("objects/butelka/butelka.obj", glm::vec3(5.5f, 3.0f, -7.0f), "objects/metal.png");
	ob4->id = "Butelka lewa";
	ob4->drunkenness = 3;
	objects.push_back(std::move(ob4));

	std::unique_ptr<WorldObject> pedestal4 = std::make_unique<WorldObject>("objects/pedestal/pedestal.obj", glm::vec3(5.5f, -1.0f, -7.0f), "objects/pedestal/marmur2.png");
	objects.push_back(std::move(pedestal4));

	std::unique_ptr<WorldObject> ob5 = std::make_unique<WorldObject>("objects/wine/wine.obj", glm::vec3(5.5f, 3.0f,-3.0f), "objects/metal.png");
	ob5->id = "Wino lewe";
	ob5->drunkenness = 1;
	objects.push_back(std::move(ob5));

	std::unique_ptr<WorldObject> pedestal5 = std::make_unique<WorldObject>("objects/pedestal/pedestal.obj", glm::vec3(5.5f, -1.0f, -3.0f), "objects/pedestal/marmur2.png");
	objects.push_back(std::move(pedestal5));

	std::unique_ptr<WorldObject> floorPtr = std::make_unique<WorldObject>("objects/plane.obj", glm::vec3(0.0f, -1.0f, 0.0f), "objects/wood.png", FLOOR);
	objects.push_back(std::move(floorPtr));

	std::unique_ptr<WorldObject> wall = std::make_unique<WorldObject>("objects/wall.obj", glm::vec3(-8.0f, 1.0f, 0.0f), "objects/wall.png");
	objects.push_back(std::move(wall));

	std::unique_ptr<WorldObject> wall2 = std::make_unique<WorldObject>("objects/wall.obj", glm::vec3(8.0f, 1.0f, 0.0f), "objects/wall.png");
	wall2->M = glm::rotate(wall2->M,PI,glm::vec3(0.0,1.0,0.0));
	objects.push_back(std::move(wall2));

	std::unique_ptr<WorldObject> wall3 = std::make_unique<WorldObject>("objects/wall2.obj", glm::vec3(0.0f, 1.0f, 30.0f), "objects/wall.png");
	objects.push_back(std::move(wall3));

	std::unique_ptr<WorldObject> wall4 = std::make_unique<WorldObject>("objects/wall2.obj", glm::vec3(0.0f, 1.0f, -20.0f), "objects/wall.png");
	wall4->M = glm::rotate(wall4->M, PI, glm::vec3(0.0, 1.0, 0.0));
	objects.push_back(std::move(wall4));


	this->printPositions();
}
void Scene::clean()
{
	
}
