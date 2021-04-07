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
	if (!currentMap->done && currentMap->generations < 25) {
		generationTime++;
		if (generationTime > 30) {
			currentMap->Start();
			generationTime = 0;
		}
	}
	else if (currentMap->generations >= 25 && !currentMap->done) {
		currentMap->done = true;
		InitalizeRoom(10, 10);
	}
	if (currentMap->done) {
		currentRoom->Update();
		currentMap->playerX = currentRoom->pos.x;
		currentMap->playerY = currentRoom->pos.y;

		for (int i = 0; i < 4; i++) {
			if (currentRoom->doors[i].entered) {
				gameCore->deleteObject(currentRoom->doors[0].id);
				gameCore->deleteObject(currentRoom->doors[1].id);
				gameCore->deleteObject(currentRoom->doors[2].id);
				gameCore->deleteObject(currentRoom->doors[3].id);
				//std::cout << currentRoom->nbrsXY->x << " " << currentRoom->nbrsXY->x << "\n";
				InitalizeRoom(currentRoom->neighbors[i]->pos.x, currentRoom->neighbors[i]->pos.y);
				player->setPosition(Vector2f(560, 340));
			}
		}
	}
}

void GameManager::InitalizeRoom(int x, int y) {
	currentRoom = &currentMap->roomMap[x][y];
	std::cout << "\n";
	for (int ways = 0; ways < 4; ways++) {
		//Vector2f result = currentMap->getNeighborV(currentRoom->pos.x, currentRoom->pos.y, ways);
		int neighborX = 0; int neighborY = 0;
		switch (ways) {
		case 0:
			neighborX = x + 1;
			neighborY = y;
			break;
		case 1:
			neighborX = x;
			neighborY = y - 1;
			break;
		case 2:
			neighborX = x - 1;
			neighborY = y;
			break;
		case 3:
			neighborX = x;
			neighborY = y + 1;
			break;
		}
		currentRoom->neighbors[ways] = &currentMap->roomMap[neighborX][neighborY];
		std::cout << currentRoom->neighbors[ways]->pos.x << " " << currentRoom->neighbors[ways]->pos.y << "\n";
	}
	currentRoom->isVisible = true;
	currentRoom->sprite = sf::Sprite(gameCore->spriteSheet, sf::IntRect(0, 736, 512, 288));
	currentRoom->Activate(&gameCore->spriteSheet);
	for (int i = 0; i < 4; i++) {
		if (currentRoom->neighbors[i]->getState() != RoomState::Solid) {
			gameCore->addObject(&currentRoom->doors[i]);
		}
	}
	gameReady = true;
}

void GameManager::ClearRoom() {
}

void GameManager::Render(RenderWindow* window) {
	if (currentMap->done) {
		currentRoom->Render(window);
	}
	currentMap->ManagedRender(window);
	player->ManagedRender(window);
}