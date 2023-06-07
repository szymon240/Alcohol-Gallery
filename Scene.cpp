#include "Scene.h"

Scene::Scene(std::string name)
{
	this->name = name;
}

void Scene::draw(ShaderProgram *sp) {
	
	for (const auto& object : objects){
			object->draw(sp);
			
	}
	
	
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
	
	std::unique_ptr<WorldObject> ob = std::make_unique<WorldObject>("objects/potion/potion.obj", glm::vec3(-3.0f, 3.5f, 1.0f), "objects/metal.png");
	objects.push_back(std::move(ob));

	std::unique_ptr<WorldObject> pedestal = std::make_unique<WorldObject>("objects/pedestal/pedestal.obj", glm::vec3(-3.0f, -1.0f, 1.0f), "objects/pedestal/marmur2.png");
	objects.push_back(std::move(pedestal));

	std::unique_ptr<WorldObject> ob1 = std::make_unique<WorldObject>("objects/butelka/butelka.obj", glm::vec3(-3.0f, 3.0f, -5.0f), "objects/metal.png");
	objects.push_back(std::move(ob1));

	std::unique_ptr<WorldObject> pedestal1 = std::make_unique<WorldObject>("objects/pedestal/pedestal.obj", glm::vec3(-3.0f, -1.0f, -5.0f), "objects/pedestal/marmur2.png");
	objects.push_back(std::move(pedestal1));

	std::unique_ptr<WorldObject> ob2 = std::make_unique<WorldObject>("objects/wine/wine.obj", glm::vec3(-3.0f, 3.0f,-2.0f), "objects/wine/metal.png");
	objects.push_back(std::move(ob2));
	
	std::unique_ptr<WorldObject> pedestal2 = std::make_unique<WorldObject>("objects/pedestal/pedestal.obj", glm::vec3(-3.0f, -1.0f, -2.0f), "objects/pedestal/marmur2.png");
	objects.push_back(std::move(pedestal2));

	std::unique_ptr<WorldObject> ob3 = std::make_unique<WorldObject>("objects/potion/potion.obj", glm::vec3(3.0f, 3.5f, 1.0f), "objects/metal.png");
	objects.push_back(std::move(ob3));

	std::unique_ptr<WorldObject> pedestal3 = std::make_unique<WorldObject>("objects/pedestal/pedestal.obj", glm::vec3(3.0f, -1.0f, 1.0f), "objects/pedestal/marmur2.png");
	objects.push_back(std::move(pedestal3));

	std::unique_ptr<WorldObject> ob4 = std::make_unique<WorldObject>("objects/butelka/butelka.obj", glm::vec3(3.0f, 3.0f, -5.0f), "objects/metal.png");
	objects.push_back(std::move(ob4));

	std::unique_ptr<WorldObject> pedestal4 = std::make_unique<WorldObject>("objects/pedestal/pedestal.obj", glm::vec3(3.0f, -1.0f, -5.0f), "objects/pedestal/marmur2.png");
	objects.push_back(std::move(pedestal4));

	std::unique_ptr<WorldObject> ob5 = std::make_unique<WorldObject>("objects/wine/wine.obj", glm::vec3(3.0f, 3.0f,-2.0f), "objects/metal.png");
	objects.push_back(std::move(ob5));

	std::unique_ptr<WorldObject> pedestal5 = std::make_unique<WorldObject>("objects/pedestal/pedestal.obj", glm::vec3(3.0f, -1.0f, -2.0f), "objects/pedestal/marmur2.png");
	objects.push_back(std::move(pedestal5));

	std::unique_ptr<WorldObject> floorPtr = std::make_unique<WorldObject>("objects/plane.obj", glm::vec3(0.0f, -1.0f, 0.0f), "objects/wood.png");
	objects.push_back(std::move(floorPtr));

	std::unique_ptr<WorldObject> wall = std::make_unique<WorldObject>("objects/wall.obj", glm::vec3(-5.0f, 1.0f, 0.0f), "objects/wood.png");
	objects.push_back(std::move(wall));

	std::unique_ptr<WorldObject> wall2 = std::make_unique<WorldObject>("objects/wall.obj", glm::vec3(5.0f, 1.0f, 0.0f), "objects/wood.png");
	wall2->M = glm::rotate(wall2->M,PI,glm::vec3(0.0,1.0,0.0));
	objects.push_back(std::move(wall2));


	this->printPositions();
}
void Scene::clean()
{
	
}
