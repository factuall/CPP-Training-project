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
		for (int startClose = 0; startClose < 4; startClose++) {
			currentRoom->doors[startClose].doorAnimation->playReverse = true;
		}
	}
	if (currentMap->done) {
		currentRoom->Update();
		currentMap->playerX = currentRoom->pos.x;
		currentMap->playerY = currentRoom->pos.y;
		for (int doorsChecked = 0; doorsChecked < 4; doorsChecked++) {
			if (currentRoom->doors[doorsChecked].entered) {
				for (int doorsToDelete = 0; doorsToDelete < 4; doorsToDelete++) {
					gameCore->deleteObject(currentRoom->doors[doorsChecked].id);
				}
				player->setPosition(currentRoom->oppositeDoorPosition(doorsChecked));
				InitalizeRoom(currentRoom->neighbors[doorsChecked]->pos.x, currentRoom->neighbors[doorsChecked]->pos.y);
				
			}
		}
	}
}

void GameManager::InitalizeRoom(int x, int y) {
	currentRoom = &currentMap->roomMap[x][y];
	for (int ways = 0; ways < 4; ways++) {
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
	}
	currentRoom->sprite = sf::Sprite(gameCore->spriteSheet, sf::IntRect(0, 736, 512, 288));
	currentRoom->PlaceDoors(&gameCore->spriteSheet);
	for (int i = 0; i < 4; i++) {
		if (currentRoom->neighbors[i]->getState() != RoomState::Solid) {
			gameCore->addObject(&currentRoom->doors[i]);
		}
	}
}

void GameManager::Render(RenderWindow* window) {
	if (currentMap->done) {
		currentRoom->Render(window);
	}
	currentMap->ManagedRender(window);
	player->ManagedRender(window);
}