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
	
	objects[i]->M = glm::rotate(objects[i]->M, PI / 4, rotateVector);
	objects[i]->M = glm::translate(objects[i]->M, glm::vec3(0.0f, 0.5f, 0.0f));

	// Start a new thread to reverse the rotation after a delay
	std::thread reverseThread([this, i, player,rotateVector]() {
		std::this_thread::sleep_for(std::chrono::seconds(1));  
		objects[i]->M = glm::translate(objects[i]->M, glm::vec3(0.0f, -0.5f, 0.0f));
		objects[i]->M = glm::rotate(objects[i]->M, -PI / 4, rotateVector);
		
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
	//BUTELKI I PIEDESTA£Y
	std::unique_ptr<WorldObject> ob = std::make_unique<WorldObject>("objects/potion/potion.obj", glm::vec3(-5.5f, 3.5f, 8.0f), "objects/potion/potion2.png");
	ob->id = "Potionek prawy";
	ob->M = glm::scale(ob->M, glm::vec3(0.7f, 0.7f, 0.7f));
	ob->drunkenness = 5;
	objects.push_back(std::move(ob));

	std::unique_ptr<WorldObject> pedestal = std::make_unique<WorldObject>("objects/pedestal/pedestal.obj", glm::vec3(-5.5f, -1.0f, 8.0f), "objects/pedestal/marmur2.png");
	objects.push_back(std::move(pedestal));

	std::unique_ptr<WorldObject> ob1 = std::make_unique<WorldObject>("objects/butelka/butelka.obj", glm::vec3(-5.5f, 3.0f, -7.0f), "objects/butelka/szklo.png");
	ob1->id = "Butelka prawa";
	ob1->M = glm::scale(ob1->M, glm::vec3(0.5f, 0.5f, 0.5f));
	ob1->drunkenness = 3;
	objects.push_back(std::move(ob1));

	std::unique_ptr<WorldObject> pedestal1 = std::make_unique<WorldObject>("objects/pedestal/pedestal.obj", glm::vec3(-5.5f, -1.0f, -7.0f), "objects/pedestal/marmur2.png");
	objects.push_back(std::move(pedestal1));

	std::unique_ptr<WorldObject> ob2 = std::make_unique<WorldObject>("objects/wine/wine.obj", glm::vec3(-5.5f, 3.0f, 1.0f), "objects/wine/wino.png");
	ob2->id = "Wino prawe";
	ob2->M = glm::scale(ob2->M, glm::vec3(0.7f, 0.7f, 0.7f));
	ob2->drunkenness = 1;
	objects.push_back(std::move(ob2));
	
	std::unique_ptr<WorldObject> pedestal2 = std::make_unique<WorldObject>("objects/pedestal/pedestal.obj", glm::vec3(-5.5f, -1.0f, 1.0f), "objects/pedestal/marmur2.png");
	objects.push_back(std::move(pedestal2));

	std::unique_ptr<WorldObject> ob3 = std::make_unique<WorldObject>("objects/wierd_bottle/wierd2.obj", glm::vec3(5.5f, 3.5f, 8.0f), "objects/wierd_bottle/membrane.png");
	ob3->id = "Potionek lewy";
	ob3->M = glm::scale(ob3->M, glm::vec3(0.9f, 1.6f, 0.9f));
	ob3->drunkenness = 5;
	objects.push_back(std::move(ob3));

	std::unique_ptr<WorldObject> pedestal6 = std::make_unique<WorldObject>("objects/pedestal/pedestal.obj", glm::vec3(-5.5f, -1.0f, 15.0f), "objects/pedestal/marmur2.png");
	objects.push_back(std::move(pedestal6));

	std::unique_ptr<WorldObject> ob6 = std::make_unique<WorldObject>("objects/whiskey/bombai.obj", glm::vec3(5.5f, 3.2f, 15.0f), "objects/whiskey/tex.png");
	ob6->id = "bOMBAI";
	ob6->drunkenness = 3;
	objects.push_back(std::move(ob6));


	std::unique_ptr<WorldObject> pedestal3 = std::make_unique<WorldObject>("objects/pedestal/pedestal.obj", glm::vec3(5.5f, -1.0f, 8.0f), "objects/pedestal/marmur2.png");
	objects.push_back(std::move(pedestal3));

	std::unique_ptr<WorldObject> ob4 = std::make_unique<WorldObject>("objects/can/can.obj", glm::vec3(5.5f, 3.0f, -7.0f), "objects/can/tex.png");
	ob4->id = "PIWO";
	ob4->M = glm::scale(ob4->M, glm::vec3(0.7f, 0.7f, 0.7f));
	ob4->drunkenness = 1;
	objects.push_back(std::move(ob4));

	std::unique_ptr<WorldObject> pedestal4 = std::make_unique<WorldObject>("objects/pedestal/pedestal.obj", glm::vec3(5.5f, -1.0f, -7.0f), "objects/pedestal/marmur2.png");
	objects.push_back(std::move(pedestal4));

	std::unique_ptr<WorldObject> ob5 = std::make_unique<WorldObject>("objects/wine/wine.obj", glm::vec3(5.5f, 3.0f,1.0f), "objects/wine/wino_blanc.png");
	ob5->id = "Wino biale";
	ob5->M = glm::scale(ob5->M, glm::vec3(0.7f, 0.7f, 0.7f));
	ob5->drunkenness = 3;
	objects.push_back(std::move(ob5));

	std::unique_ptr<WorldObject> pedestal5 = std::make_unique<WorldObject>("objects/pedestal/pedestal.obj", glm::vec3(5.5f, -1.0f, 1.0f), "objects/pedestal/marmur2.png");
	objects.push_back(std::move(pedestal5));
	
	std::unique_ptr<WorldObject> ob7= std::make_unique<WorldObject>("objects/can/can.obj", glm::vec3(-5.5f, 3.0f, 15.0f), "objects/can/tex2.png");
	ob7->id = "PIWO2";
	ob7->M = glm::scale(ob7->M, glm::vec3(0.7f, 0.7f, 0.7f));
	ob7->drunkenness = 1;
	objects.push_back(std::move(ob7));

	std::unique_ptr<WorldObject> pedestal7 = std::make_unique<WorldObject>("objects/pedestal/pedestal.obj", glm::vec3(5.5f, -1.0f, 15.0f), "objects/pedestal/marmur2.png");
	objects.push_back(std::move(pedestal7));


	//DEKORACJE
	std::unique_ptr<WorldObject> dec = std::make_unique<WorldObject>("objects/decorations/decoration1.obj", glm::vec3(7.0f, -1.0f, 29.0f), "objects/decorations/marble.png");
	objects.push_back(std::move(dec));

	std::unique_ptr<WorldObject> dec1 = std::make_unique<WorldObject>("objects/decorations/decoration1.obj", glm::vec3(-7.0f, -1.0f, -19.0f), "objects/decorations/marble.png");
	objects.push_back(std::move(dec1));

	std::unique_ptr<WorldObject> dec2 = std::make_unique<WorldObject>("objects/decorations/decoration2.obj", glm::vec3(-7.0f, -1.0f, 29.0f), "objects/decorations/marble.png");
	objects.push_back(std::move(dec2));

	std::unique_ptr<WorldObject> dec3 = std::make_unique<WorldObject>("objects/decorations/decoration2.obj", glm::vec3(7.0f, -1.0f, -19.0f), "objects/decorations/marble.png");
	objects.push_back(std::move(dec3));

	//SUFIT I POD£OGA
	std::unique_ptr<WorldObject> floorPtr = std::make_unique<WorldObject>("objects/plane.obj", glm::vec3(0.0f, -1.0f, 0.0f), "objects/wood.png", FLOOR);
	objects.push_back(std::move(floorPtr));
	std::unique_ptr<WorldObject> celling = std::make_unique<WorldObject>("objects/plane.obj", glm::vec3(0.0f, 19.0f, 0.0f), "objects/wall.png", FLOOR);
	celling->M = glm::rotate(celling->M, PI, glm::vec3(1.0, 0.0, 0.0));
	objects.push_back(std::move(celling));

	//SCIANY
	std::unique_ptr<WorldObject> wall = std::make_unique<WorldObject>("objects/wall.obj", glm::vec3(-8.0f, 1.0f, 0.0f), "objects/wall.png");
	objects.push_back(std::move(wall));
	std::unique_ptr<WorldObject> wall2 = std::make_unique<WorldObject>("objects/wall.obj", glm::vec3(8.0f, 1.0f, 0.0f), "objects/wall.png");
	wall2->M = glm::rotate(wall2->M,PI,glm::vec3(0.0,1.0,0.0));
	objects.push_back(std::move(wall2));
	std::unique_ptr<WorldObject> wall3 = std::make_unique<WorldObject>("objects/wall.obj", glm::vec3(0.0f, 1.0f, 30.0f), "objects/wall.png");
	wall3->M = glm::rotate(wall3->M, PI/2, glm::vec3(0.0, 1.0, 0.0));
	objects.push_back(std::move(wall3));
	std::unique_ptr<WorldObject> wall4 = std::make_unique<WorldObject>("objects/wall.obj", glm::vec3(0.0f, 1.0f, -20.0f), "objects/wall.png");
	wall4->M = glm::rotate(wall4->M, -PI/2, glm::vec3(0.0, 1.0, 0.0));
	objects.push_back(std::move(wall4));
	
	//LAMPY
	std::unique_ptr<WorldObject> lamp = std::make_unique<WorldObject>("objects/lamp.obj", glm::vec3(0.0f, 15.0f, 20.0f), "objects/lampa.png");
	objects.push_back(std::move(lamp));
	std::unique_ptr<WorldObject> lamp2 = std::make_unique<WorldObject>("objects/lamp.obj", glm::vec3(0.0f, 15.0f, -10.0f), "objects/lampa.png");
	objects.push_back(std::move(lamp2));


	//DRZWI!
	std::unique_ptr<WorldObject> doors = std::make_unique<WorldObject>("objects/craftsmanDoorClosed.obj", glm::vec3(0.0f, 2.0f, 30.0f), "objects/biale_drewno.png");
	doors->M = glm::scale(doors->M, glm::vec3(1.5f, 3.0f, 1.5f));
	objects.push_back(std::move(doors));
	this->printPositions();
}
void Scene::clean()
{
	
}
