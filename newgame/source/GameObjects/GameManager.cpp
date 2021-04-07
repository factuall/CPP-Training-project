#include "GameManager.h"
#include <iostream>

using namespace sf;
using namespace fc;
GameManager::GameManager(Text txt, Core* gameCore) {
	//object
	id = 0;
	isNull = false;
	isVisible = true;
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
	if (!currentMap->isDone && currentMap->rooms < 25) {
		generationTime++;
		if (generationTime > 30) {
			currentMap->Start();
			generationTime = 0;
		}
	}
	else if(currentMap->rooms >= 25 && !currentMap->isDone){
		currentMap->isDone = true;
		currentRoom = &currentMap->roomMap[10][10];
		GameRoom* nbrs[4];
		for (int ways = 0; ways < 4; ways++) {
			nbrs[ways] = currentMap->getNeighbor(currentRoom->pos.x, currentRoom->pos.y, ways);
			currentRoom->nbrs[ways] = nbrs[ways];
			
		}
		currentRoom->isVisible = true;
		currentRoom->sprite = sf::Sprite(gameCore->spriteSheet, sf::IntRect(0, 736, 512, 288));
		currentRoom->Activate(&gameCore->spriteSheet);
	}
	if (currentMap->isDone) {
		currentRoom->Update();

	}
}

void GameManager::Render(RenderWindow* window) {
	if (currentMap->isDone) {
		currentRoom->Render(window);
	}
	currentMap->ManagedRender(window);
	player->ManagedRender(window);
} 