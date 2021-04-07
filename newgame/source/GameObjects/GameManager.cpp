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
	else if (currentMap->rooms >= 25 && !currentMap->isDone) {
		currentMap->isDone = true;
		InitalizeRoom(10, 10);
	}
	if (currentMap->isDone) {
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
				InitalizeRoom(currentRoom->nbrs[i]->pos.x, currentRoom->nbrs[i]->pos.y);
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
		int nbrX = 0; int nbrY = 0;
		switch (ways) {
		case 0:
			nbrX = x + 1;
			nbrY = y;
			break;
		case 1:
			nbrX = x;
			nbrY = y - 1;
			break;
		case 2:
			nbrX = x - 1;
			nbrY = y;
			break;
		case 3:
			nbrX = x;
			nbrY = y + 1;
			break;
		}
		currentRoom->nbrs[ways] = &currentMap->roomMap[nbrX][nbrY];
		std::cout << currentRoom->nbrs[ways]->pos.x << " " << currentRoom->nbrs[ways]->pos.y << "\n";
	}
	currentRoom->isVisible = true;
	currentRoom->sprite = sf::Sprite(gameCore->spriteSheet, sf::IntRect(0, 736, 512, 288));
	currentRoom->Activate(&gameCore->spriteSheet);
	for (int i = 0; i < 4; i++) {
		if (currentRoom->nbrs[i]->getState() != RoomState::Solid) {
			gameCore->addObject(&currentRoom->doors[i]);
		}
	}
	gameReady = true;
}

void GameManager::ClearRoom() {
}

void GameManager::Render(RenderWindow* window) {
	if (currentMap->isDone) {
		currentRoom->Render(window);
	}
	currentMap->ManagedRender(window);
	player->ManagedRender(window);
}