#include "GameManager.h"
#include <iostream>

using namespace sf;
using namespace fc;
GameManager::GameManager(Text txt, Core* gameCore) {
	//object
	id = 0;
	isNull = false;
	isVisible = false;
	isTrigger = false;
	this->gameCore = gameCore;
	collider = new Collider(Vector2f(-21, -37), Vector2f(0, 0));
	//map
	currentMap = new GameFloor(txt);
	gameCore->addObject(currentMap);
	currentMap->Start();
	
	//player
	player = new Player(560, 340, &gameCore->spriteSheet);
	gameCore->addObject(player);
};

int generationTime = 0;
void GameManager::Update() {

	if (!(currentMap->isDone) && currentMap->rooms < 25) {
		generationTime++;
		if (generationTime > 30) {
			currentMap->Start();
			generationTime = 0;
		}
	}
	else if(currentMap->rooms >= 25){
		currentMap->isDone = true;
		currentRoom = &currentMap->roomMap
			[currentMap->orderOfRooms[0].x]
			[currentMap->orderOfRooms[0].y];
			
			std::cout << currentRoom->pos.x << " " << currentRoom->pos.y << "\n";
			
			currentRoom->Enter();
			
	}

}

void GameManager::Render(RenderWindow* window) {
} 