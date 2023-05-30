#pragma once
#include <vector>
#include "WorldObject.h"

class Scene
{
	int size;
	std::string name;
public:
	std::vector<WorldObject*> objects;
	Scene(std::string name);
	void draw(ShaderProgram *sp);
	void addObject(WorldObject * ob);
	void loadLevel();
	void clean();
};

