#pragma once
#include <vector>
#include "WorldObject.h"
#include <memory>
#include <iostream>
#include <map>


class Scene
{
	int size;
	std::string name;
	void printPositions();
public:
	std::map < std::string, glm::vec3 > objectPositions;
	std::vector<std::unique_ptr<WorldObject>> objects;
	std::unique_ptr<WorldObject> floor;
	Scene(std::string name);
	void draw(ShaderProgram *sp);
	void addObject(std::unique_ptr<WorldObject> ob);
	void loadLevel();
	void clean();
	
};

