#include "Scene.h"

Scene::Scene(std::string name)
{
	this->name = name;
}

void Scene::draw(ShaderProgram *sp) {
	int i = 0;
	for (const auto& object : objects){
		if (object->vertices.size() != 0 || object->vertices.size()%3 != 0) {
			if (object != nullptr) {
				object->draw(sp, i);
			}
			else {

				printf("OBJEKT JEST PUSTY?");
			}
		}
		else
		{
			printf("No vertices loaded!!");
		}
		
	}
}

void Scene::addObject(std::unique_ptr<WorldObject> ob) {
	objects.push_back(std::move(ob));
	this->size = objects.size();
}

void Scene::loadLevel() {
	
	std::unique_ptr<WorldObject> ob = std::make_unique<WorldObject>("objects/potion/potion.obj", glm::vec3(-2.0f, 0.0f, 1.0f), "objects/metal.png");
	objects.push_back(std::move(ob));

	std::unique_ptr<WorldObject> ob1 = std::make_unique<WorldObject>("objects/butelka/butelka.obj", glm::vec3(0.0f, -0.5f, 1.0f), "objects/metal.png");
	objects.push_back(std::move(ob1));

	std::unique_ptr<WorldObject> ob2 = std::make_unique<WorldObject>("objects/wine/wine2.obj", glm::vec3(2.0f, -0.5f, 1.0f), "objects/metal.png");
	objects.push_back(std::move(ob2));

	std::unique_ptr<WorldObject> ob3 = std::make_unique<WorldObject>("objects/potion/potion.obj", glm::vec3(-2.0f, 0.0f, -1.0f), "objects/metal.png");
	objects.push_back(std::move(ob3));

	std::unique_ptr<WorldObject> ob4 = std::make_unique<WorldObject>("objects/butelka/butelka.obj", glm::vec3(0.0f, -0.5f, -1.0f), "objects/metal.png");
	objects.push_back(std::move(ob4));

	std::unique_ptr<WorldObject> ob5 = std::make_unique<WorldObject>("objects/wine/wine2.obj", glm::vec3(2.0f, -0.5f, -1.0f), "objects/metal.png");
	objects.push_back(std::move(ob5));
}
void Scene::clean()
{
	
}
