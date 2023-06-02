#include "Scene.h"

Scene::Scene(std::string name)
{
	this->name = name;
}

void Scene::draw(ShaderProgram *sp) {
	int i = 0;
	for (const auto& object : objects) {
		object->draw(sp, i);
	}
}

void Scene::addObject(std::unique_ptr<WorldObject> ob) {
	objects.push_back(std::move(ob));
	this->size = objects.size();
}

void Scene::loadLevel() {
	std::unique_ptr<WorldObject> ob = std::make_unique<WorldObject>("objects/Cubone/modell.obj", "objects/metal.png");
	objects.push_back(std::move(ob));

	std::unique_ptr<WorldObject> ob1 = std::make_unique<WorldObject>("objects/Cubone/modell.obj", glm::vec3(0.5f, 0.0f, 1.0f), "objects/bricks.png");
	objects.push_back(std::move(ob1));

	// Uncomment the following lines if you want to add another object
	// std::unique_ptr<WorldObject> ob2 = std::make_unique<WorldObject>("objects/Cubone/modell.obj", glm::vec3(-3.0f, 0.0f, 1.0f), "objects/bricks.png");
	// objects.push_back(std::move(ob2));
}
void Scene::clean()
{
	
}
