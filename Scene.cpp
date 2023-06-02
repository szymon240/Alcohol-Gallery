#include "Scene.h"

Scene::Scene(std::string name)
{
	this->name = name;
}

void Scene::draw(ShaderProgram *sp) {
	for (const auto& object : objects) {
		object->draw(sp);
	}
}

void Scene::addObject(WorldObject * ob)
{
	objects.push_back(ob);
	this->size = objects.size();
}

void Scene::loadLevel()
{
	WorldObject * ob = new WorldObject("objects/Cubone/modell.obj");
	objects.push_back(ob);

	WorldObject* ob1 = new WorldObject("objects/Cubone/modell.obj", glm::vec3(3.0f, 0.0f, 1.0f));
	objects.push_back(ob1);
	WorldObject* ob2 = new WorldObject("objects/Cubone/modell.obj", glm::vec3(-3.0f, 0.0f, 1.0f));
	objects.push_back(ob2);
}

void Scene::clean()
{
	for (const auto& object : objects) {
		delete object;
	}
	objects.clear();
}
