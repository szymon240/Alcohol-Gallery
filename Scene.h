#pragma once
#include <vector>
#include "WorldObject.h"
#include <memory>


class Scene
{
	int size;
	std::string name;
public:
	std::vector<std::unique_ptr<WorldObject>> objects;
	Scene(std::string name);
	void draw(ShaderProgram *sp);
	void addObject(std::unique_ptr<WorldObject> ob);
	void loadLevel();
	void clean();
};

